---
title: Binary Trie with Monoid
documentation_of: ../../../ds/ordered_set/binary_trie_monoid.hpp
---

## Overview

`BinaryTrieMonoid` stores pairs `(key, value)`. For a query `(x, upper)`, it
returns the monoid product of every stored value whose key satisfies
`(key ^ x) < upper`.

This directly supports queries of the form

```text
prod(B_i) for every i such that (A_i ^ x) < a
```

by inserting each pair with `insert(A_i, B_i)` and calling
`prod_xor_less(x, a)`.

The monoid operation must be commutative because the selected entries do not
have an intrinsic order. Addition, multiplication, minimum, maximum, gcd, and
bitwise xor are suitable examples.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`. Its operation must
  also be commutative.
* `UInt`: An unsigned integer type used for keys. Defaults to `std::uint32_t`.
* `BitWidth`: The number of low key bits used by the trie. Defaults to all bits
  of `UInt`. Keys and xor operands must fit in these bits.

An exclusive `upper` bound may be larger than the largest representable
`BitWidth`-bit key when that value fits in `UInt`. For example, with
`BitWidth == 30`, passing `1U << 30` includes every possible key.

## Methods

Let $B$ be `BitWidth`.

| Method | Description | Complexity |
| --- | --- | --- |
| `BinaryTrieMonoid()` | Constructs an empty trie. | $O(1)$ |
| `BinaryTrieMonoid(init)` | Constructs from `(key, value)` pairs. | $O(NB)$ |
| `BinaryTrieMonoid(first, last)` | Constructs from a range of `(key, value)` pairs. | $O(NB)$ |
| `BinaryTrieMonoid(keys, values)` | Constructs from parallel key and value vectors. | $O(NB)$ |
| `int size() const` | Returns the number of inserted pairs. | $O(1)$ |
| `bool empty() const` | Returns whether the trie is empty. | $O(1)$ |
| `void clear()` | Removes every pair and resets the lazy xor. | $O(1)$ |
| `void insert(UInt key, const T& value)` | Inserts one `(key, value)` pair. Duplicate keys are allowed. | $O(B)$ |
| `int count(UInt key) const` | Returns the number of pairs with this key. | $O(B)$ |
| `bool contains(UInt key) const` | Returns whether this key exists. | $O(B)$ |
| `T prod(UInt key) const` | Returns the product of values with exactly this key. | $O(B)$ |
| `T all_prod() const` | Returns the product of all stored values. | $O(1)$ |
| `int erase_all(UInt key)` | Removes all pairs with this key and returns their count. | $O(B)$ |
| `void xor_all(UInt value)` | Applies xor with `value` to every stored key. | $O(1)$ |

### XOR order statistics

| Method | Description | Complexity |
| --- | --- | --- |
| `UInt kth_xor(int k, UInt x) const` | Returns the 0-indexed `k`-th smallest result among `key ^ x`, including duplicate keys. | $O(B)$ |
| `UInt kth(int k) const` | Returns the 0-indexed `k`-th smallest key. | $O(B)$ |
| `UInt min() const`, `UInt max() const` | Returns the smallest or largest key. Requires a nonempty trie. | $O(B)$ |
| `UInt min_xor(UInt x) const`, `UInt max_xor(UInt x) const` | Returns the minimum or maximum result among `key ^ x`. Requires a nonempty trie. | $O(B)$ |

### XOR counts

| Method | Description | Complexity |
| --- | --- | --- |
| `int count_xor_equal(UInt x, UInt target) const` | Counts pairs satisfying `(key ^ x) == target`. | $O(B)$ |
| `int count_xor_less(UInt x, UInt upper) const` | Counts pairs satisfying `(key ^ x) < upper`. | $O(B)$ |
| `int count_xor_less_equal(UInt x, UInt upper) const` | Counts pairs satisfying `(key ^ x) <= upper`. | $O(B)$ |
| `int count_xor_greater(UInt x, UInt lower) const` | Counts pairs satisfying `(key ^ x) > lower`. | $O(B)$ |
| `int count_xor_greater_equal(UInt x, UInt lower) const` | Counts pairs satisfying `(key ^ x) >= lower`. | $O(B)$ |
| `int count_xor_range(UInt x, UInt lower, UInt upper) const` | Counts pairs satisfying `lower <= (key ^ x) < upper`. | $O(B)$ |

`count_less_xor(x, upper)` is a compatibility alias for
`count_xor_less(x, upper)`. The methods `order_of_key`, `count_less`,
`count_less_equal`, `count_greater`, `count_greater_equal`, and `count_range`
provide the same comparisons without an xor operand.

### XOR products

| Method | Description | Complexity |
| --- | --- | --- |
| `T prod_xor_equal(UInt x, UInt target) const` | Returns the product for pairs satisfying `(key ^ x) == target`. | $O(B)$ |
| `T prod_xor_less(UInt x, UInt upper) const` | Returns the product for pairs satisfying `(key ^ x) < upper`. | $O(B)$ |
| `T prod_xor_less_equal(UInt x, UInt upper) const` | Returns the product for pairs satisfying `(key ^ x) <= upper`. | $O(B)$ |
| `T prod_xor_greater(UInt x, UInt lower) const` | Returns the product for pairs satisfying `(key ^ x) > lower`. | $O(B)$ |
| `T prod_xor_greater_equal(UInt x, UInt lower) const` | Returns the product for pairs satisfying `(key ^ x) >= lower`. | $O(B)$ |
| `T prod_xor_range(UInt x, UInt lower, UInt upper) const` | Returns the product for pairs satisfying `lower <= (key ^ x) < upper`. | $O(B)$ |

When no pair satisfies a product query, it returns `Monoid::id()`.
The methods `prod_less`, `prod_less_equal`, `prod_greater`,
`prod_greater_equal`, and `prod_range` provide the same comparisons without an
xor operand.

## Example

```cpp
#include "ds/ordered_set/binary_trie_monoid.hpp"
#include "monoid/mul.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::uint32_t> A = {1, 2, 7, 7};
    std::vector<long long> B = {2, 3, 5, 11};

    using Product = m1une::monoid::Mul<long long>;
    m1une::ds::BinaryTrieMonoid<Product, std::uint32_t, 30> trie(A, B);

    std::uint32_t x = 3;
    std::uint32_t a = 4;

    // 1 ^ 3 = 2 and 2 ^ 3 = 1 are less than 4.
    // The answer is B[0] * B[1] = 2 * 3 = 6.
    std::cout << trie.prod_xor_less(x, a) << "\n";

    // Product for 1 <= (A[i] ^ x) < 5.
    std::cout << trie.prod_xor_range(x, 1, 5) << "\n";
}
```
