---
title: Parser
documentation_of: ../../utilities/parser.hpp
---

## Overview

`Parser` is a lightweight cursor over a `std::string_view` for recursive-descent
parsing. It is useful when a problem's input is an expression, nested notation,
command language, encoded tree, or another format that is awkward to read with
`operator>>`.

The parser does not own or copy its input. Most successful operations return
`std::string_view`, and ordinary parsing performs no allocation. Failed
`try_...` operations restore the cursor to where the operation started.

```cpp
#include "utilities/parser.hpp"
```

All names are in `m1une::utilities`.

## Cursor operations

| Operation | Description | Complexity |
| --- | --- | --- |
| `Parser(input)` | Creates a parser over `input`. The input must outlive the parser and returned views. | $O(1)$ |
| `source()` | Returns the complete input. | $O(1)$ |
| `size()` / `position()` | Returns the input size or current cursor position. | $O(1)$ |
| `eof()` | Tests whether the cursor is at the end. | $O(1)$ |
| `remaining()` | Returns the unparsed suffix. | $O(1)$ |
| `peek(offset)` | Returns the character at the cursor plus `offset`, or `std::nullopt`. | $O(1)$ |
| `mark()` / `restore(mark)` | Saves and restores a cursor position. | $O(1)$ |
| `checkpoint()` | Creates an automatic rollback point. | $O(1)$ |
| `skip_whitespace()` | Skips characters recognized by `std::isspace`. | Linear in the skipped length. |

`Checkpoint` restores the old position when it leaves scope. Call `commit()` to
keep the new position, or `rollback()` to restore it immediately. It is useful
for alternatives with several parsing steps:

```cpp
auto attempt = parser.checkpoint();
if (parser.consume("min") && parser.consume('(')) {
    // Parse the rest of this alternative.
    attempt.commit();
}
```

## Exact parsing primitives

These operations start exactly at the current cursor; they do not skip
whitespace.

| Operation | Description |
| --- | --- |
| `consume(character)` | Consumes one matching character and returns whether it matched. |
| `consume(text)` | Consumes a matching string and returns whether it matched. |
| `consume_if(predicate)` | Consumes one character accepted by `predicate`. |
| `expect(character)` / `expect(text)` | Consumes the expected input or throws `ParseError`. |
| `take(count)` | Consumes exactly `count` characters, or returns `std::nullopt` without moving. |
| `read_while(predicate)` | Consumes and returns the longest prefix accepted by `predicate`. |
| `read_until(delimiter, consume_delimiter)` | Returns text up to the delimiter or end of input. |

`ParseError::position()` reports the byte position where the failed expectation
was made. Its `what()` message also includes that position.

## Token-level readers

The following readers first skip whitespace:

| Trying operation | Throwing operation | Accepted input |
| --- | --- | --- |
| `try_token()` | `token()` | One or more non-whitespace characters. |
| `try_identifier()` | `identifier()` | `[A-Za-z_][A-Za-z0-9_]*`, using the corresponding character classification functions. |
| `try_integer<T>(base)` | `integer<T>(base)` | An optional sign and digits in base 2 through 36, checked for overflow. |
| `try_real()` | `real()` | A decimal number with an optional sign, fractional part, and exponent. |
| `try_balanced(open, close)` | `balanced(open, close)` | A nested delimiter pair; the returned view excludes the outer pair. |

Trying operations return `std::nullopt` and restore the cursor when parsing
fails. Throwing operations throw `ParseError`. Integer overflow is considered a
parse failure. `try_balanced` only tracks its two delimiter characters; it does
not give quotes or escape sequences special meaning.

All operations are linear in the number of characters they inspect.

## Recursive-descent example

This parser evaluates integers, parentheses, addition, and subtraction:

```cpp
#include "utilities/parser.hpp"

using m1une::utilities::Parser;

long long expression(Parser& parser);

long long atom(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('(')) {
        long long value = expression(parser);
        parser.skip_whitespace();
        parser.expect(')');
        return value;
    }
    return parser.integer<long long>();
}

long long expression(Parser& parser) {
    long long value = atom(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('+')) {
            value += atom(parser);
        } else if (parser.consume('-')) {
            value -= atom(parser);
        } else {
            return value;
        }
    }
}

int main() {
    Parser parser("10 - (3 + -2)");
    long long answer = expression(parser);
    parser.skip_whitespace();
    if (!parser.eof()) {
        throw m1une::utilities::ParseError(
            parser.position(),
            "unexpected trailing input"
        );
    }
}
```

## Building a parsing tree

A parsing tree stores the structure of the input instead of immediately
evaluating it. This is useful when later steps need to inspect, transform, or
evaluate the expression more than once.

In practice, competitive-programming solutions usually build an **abstract
syntax tree (AST)**. A concrete parse tree would also contain punctuation and
grammar-only nodes, while an AST keeps only meaningful operations and values.
For example, the parentheses in `2 * (3 + 4)` affect the shape of the AST but do
not need their own nodes.

Start by writing a grammar whose functions correspond to precedence levels:

```text
expression := product (('+' | '-') product)*
product    := unary (('*' | '/') unary)*
unary      := ('+' | '-') unary | atom
atom       := integer | '(' expression ')'
```

Calling lower lines from higher lines gives multiplication and division higher
precedence than addition and subtraction. The loops make binary operators
left-associative, so `8 - 3 - 2` is parsed as `(8 - 3) - 2`.

The following node type owns its children with `std::unique_ptr`. This avoids
pointer invalidation and automatically destroys the complete tree:

```cpp
#include "utilities/parser.hpp"

#include <memory>

enum class NodeKind {
    number,
    negate,
    add,
    subtract,
    multiply,
    divide
};

struct Node {
    NodeKind kind = NodeKind::number;
    long long value = 0;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

std::unique_ptr<Node> make_number(long long value) {
    auto node = std::make_unique<Node>();
    node->value = value;
    return node;
}

std::unique_ptr<Node> make_unary(
    NodeKind kind,
    std::unique_ptr<Node> child
) {
    auto node = std::make_unique<Node>();
    node->kind = kind;
    node->left = std::move(child);
    return node;
}

std::unique_ptr<Node> make_binary(
    NodeKind kind,
    std::unique_ptr<Node> left,
    std::unique_ptr<Node> right
) {
    auto node = std::make_unique<Node>();
    node->kind = kind;
    node->left = std::move(left);
    node->right = std::move(right);
    return node;
}
```

Each parsing function consumes exactly one grammar rule and returns the root of
the subtree it built:

```cpp
using m1une::utilities::Parser;

std::unique_ptr<Node> parse_expression(Parser& parser);

std::unique_ptr<Node> parse_atom(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('(')) {
        std::unique_ptr<Node> node = parse_expression(parser);
        parser.skip_whitespace();
        parser.expect(')');
        return node;
    }
    return make_number(parser.integer<long long>());
}

std::unique_ptr<Node> parse_unary(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('+')) {
        return parse_unary(parser);
    }
    if (parser.consume('-')) {
        return make_unary(NodeKind::negate, parse_unary(parser));
    }
    return parse_atom(parser);
}

std::unique_ptr<Node> parse_product(Parser& parser) {
    std::unique_ptr<Node> node = parse_unary(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('*')) {
            node = make_binary(
                NodeKind::multiply,
                std::move(node),
                parse_unary(parser)
            );
        } else if (parser.consume('/')) {
            node = make_binary(
                NodeKind::divide,
                std::move(node),
                parse_unary(parser)
            );
        } else {
            return node;
        }
    }
}

std::unique_ptr<Node> parse_expression(Parser& parser) {
    std::unique_ptr<Node> node = parse_product(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('+')) {
            node = make_binary(
                NodeKind::add,
                std::move(node),
                parse_product(parser)
            );
        } else if (parser.consume('-')) {
            node = make_binary(
                NodeKind::subtract,
                std::move(node),
                parse_product(parser)
            );
        } else {
            return node;
        }
    }
}
```

Always check for trailing input after constructing the root. Without this check,
a valid prefix such as `1 + 2` could hide an invalid suffix.

```cpp
Parser parser("2 * (3 + 4)");
std::unique_ptr<Node> root = parse_expression(parser);
parser.skip_whitespace();
if (!parser.eof()) {
    throw m1une::utilities::ParseError(
        parser.position(),
        "unexpected trailing input"
    );
}
```

For very large trees, allocating each node separately can be slower than using a
node pool. Store nodes in a pre-reserved `std::vector<Node>` and use integer
indices as child links when performance or memory locality matters. If a node
stores an identifier as `std::string_view`, the parser's original input must
remain alive for as long as the tree.
