---
title: Binary Trie
documentation_of: ../../../ds/ordered_set/binary_trie.hpp
---

## Overview

`BinaryTrie` is a multiset of unsigned integers represented by their binary
digits. It supports insertion, deletion, order statistics, and minimum or
maximum xor queries in time proportional to the configured bit width.

Duplicate values are stored separately. `xor_all(value)` lazily applies xor to
every value already in the trie.

## Template Parameters

* `UInt`: An unsigned integer type. Defaults to `std::uint32_t`.
* `BitWidth`: The number of low bits used by the trie. Defaults to all bits of
  `UInt`. Every inserted value and xor operand must fit in these bits.

## Methods

Let $B$ be `BitWidth`.

| Method | Description | Complexity |
| --- | --- | --- |
| `BinaryTrie()` | Constructs an empty trie. | $O(1)$ |
| `BinaryTrie(std::initializer_list<UInt> init)` | Constructs a trie containing `init`. | $O(NB)$ |
| `BinaryTrie(Iterator first, Iterator last)` | Constructs a trie from a range. | $O(NB)$ |
| `int size() const` | Returns the number of values, including duplicates. | $O(1)$ |
| `bool empty() const` | Returns whether the trie is empty. | $O(1)$ |
| `void clear()` | Removes every value and resets the lazy xor. | $O(1)$ |
| `void insert(UInt value, int multiplicity = 1)` | Inserts `multiplicity` copies of `value`. | $O(B)$ |
| `bool erase_one(UInt value)`, `bool erase(UInt value)` | Removes one copy and returns whether one existed. | $O(B)$ |
| `int erase_all(UInt value)` | Removes every copy and returns the number removed. | $O(B)$ |
| `int count(UInt value) const` | Returns the multiplicity of `value`. | $O(B)$ |
| `bool contains(UInt value) const` | Returns whether `value` exists. | $O(B)$ |
| `void xor_all(UInt value)` | Applies xor with `value` to every stored value. | $O(1)$ |
| `UInt kth(int k) const` | Returns the 0-indexed `k`-th smallest stored value. | $O(B)$ |
| `UInt min() const`, `UInt max() const` | Returns the smallest or largest value. Requires a nonempty trie. | $O(B)$ |
| `UInt kth_xor(int k, UInt value) const` | Returns the 0-indexed `k`-th smallest result among `stored_value ^ value`. | $O(B)$ |
| `UInt min_xor(UInt value) const`, `UInt max_xor(UInt value) const` | Returns the minimum or maximum result among `stored_value ^ value`. Requires a nonempty trie. | $O(B)$ |
| `int order_of_key(UInt value) const`, `int count_less(UInt value) const` | Returns the number of stored values strictly less than `value`. | $O(B)$ |
| `int count_less_equal(UInt value) const` | Returns the number of stored values less than or equal to `value`. | $O(B)$ |
| `int count_greater(UInt value) const` | Returns the number of stored values strictly greater than `value`. | $O(B)$ |
| `int count_greater_equal(UInt value) const` | Returns the number of stored values greater than or equal to `value`. | $O(B)$ |
| `int count_less_xor(UInt value, UInt upper) const` | Counts stored values for which `(stored_value ^ value) < upper`. | $O(B)$ |
| `std::vector<UInt> to_vector() const` | Returns all values in sorted order, including duplicates. | $O(NB)$ |

## Example

```cpp
#include "ds/ordered_set/binary_trie.hpp"

#include <cstdint>
#include <iostream>

int main() {
    m1une::ds::BinaryTrie<std::uint32_t, 20> trie;
    trie.insert(2);
    trie.insert(7);
    trie.insert(7);

    std::cout << trie.min_xor(5) << "\n";  // min(2 ^ 5, 7 ^ 5) = 2
    std::cout << trie.kth(1) << "\n";      // 7

    trie.xor_all(3);
    std::cout << trie.min() << "\n";       // min(2 ^ 3, 7 ^ 3) = 1
    std::cout << trie.count(4) << "\n";    // 2
}
```
