---
title: Trie
documentation_of: ../../string/trie.hpp
---

## Overview

`m1une::string::Trie` is a multiset of strings represented by a prefix tree.
It supports duplicate insertion, deletion, exact lookup, counting strings with
a given prefix, and enumerating stored strings that are prefixes of a query.

Nodes are stored in one contiguous vector. The alphabet must be a contiguous
range of character codes, making transitions constant-time without maps or
per-edge allocations.

## Template Parameters

* `AlphabetSize`: Number of symbols in the alphabet. Defaults to `26`.
* `FirstCharacter`: Character code corresponding to transition `0`. Defaults
  to `'a'`.

The default `Trie<>` accepts lowercase English letters. For decimal digits,
use `Trie<10, '0'>`.

Methods are generic over iterable sequences whose symbols can be converted to
integers, including `std::string`, `std::string_view`, and character vectors.
Every symbol must lie in the configured alphabet.

## Methods

Let $L$ be the sequence length.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of stored strings including duplicates. | $O(1)$ |
| `int distinct_size()` | Returns the number of distinct stored strings. | $O(1)$ |
| `bool empty()` | Returns whether no strings are stored. | $O(1)$ |
| `size_t node_count()` | Returns allocated nodes, including the root. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for approximately `n` nodes. | $O(K)$ |
| `void clear()` | Removes all strings. | $O(K)$ |
| `void insert(sequence, int multiplicity = 1)` | Inserts copies of `sequence`. | $O(L)$ |
| `int count(sequence)` | Returns the sequence multiplicity. | $O(L)$ |
| `bool contains(sequence)` | Returns whether the sequence is stored. | $O(L)$ |
| `int prefix_count(prefix)` | Counts stored strings beginning with `prefix`, including duplicates. | $O(L)$ |
| `bool starts_with(prefix)` | Returns whether any stored string begins with `prefix`. | $O(L)$ |
| `bool erase_one(sequence)`, `bool erase(sequence)` | Erases one copy and reports success. | $O(L)$ |
| `int erase_all(sequence)` | Erases all copies and returns the number erased. | $O(L)$ |
| `void for_each_prefix(sequence, callback)` | Calls `callback(length, multiplicity)` for each stored string that is a prefix of `sequence`. | $O(L)$ |
| `int longest_prefix(sequence)` | Returns the longest stored prefix length, or `-1` if none exists. | $O(L)$ |

Here $K$ is the allocated node count. Erasing does not reclaim nodes; `clear`
releases all logical contents at once.

The empty string is supported. When stored, it is reported by
`for_each_prefix` with length `0`, and `prefix_count("")` equals `size()`.

## Example

```cpp
#include "string/trie.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::string::Trie<> trie;
    trie.insert(std::string("app"));
    trie.insert(std::string("apple"));
    trie.insert(std::string("app"));

    std::cout << trie.count(std::string("app")) << "\n";       // 2
    std::cout << trie.prefix_count(std::string("app")) << "\n"; // 3
    std::cout << trie.longest_prefix(std::string("apples")) << "\n"; // 5
}
```
