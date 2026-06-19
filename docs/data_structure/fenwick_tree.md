---
title: Fenwick Tree (Binary Indexed Tree)
documentation_of: ../../data_structure/fenwick_tree.hpp
---

## Overview

A Fenwick tree, also called a binary indexed tree, supports point additions and
prefix-sum queries in logarithmic time.

Indices are zero-based and range queries use half-open intervals `[l, r)`.

## Template Parameters

* `T`: The underlying numeric type of the elements (e.g., `int`, `long long`, or a modular integer `modint`).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FenwickTree(int n)` | Initializes an array of size `n` with `0`s. | $O(N)$ |
| `FenwickTree(const std::vector<T>& a)` | Builds a tree from a given vector array `a`. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the tree is empty. | $O(1)$ |
| `void add(int p, const T& x)` | Adds `x` to the element at index `p`. | $O(\log N)$ |
| `T sum(int r) const` | Returns the sum of elements in the prefix `[0, r)`. | $O(\log N)$ |
| `T sum(int l, int r) const` | Returns the sum of elements in the interval `[l, r)`. | $O(\log N)$ |
| `int lower_bound(T w) const` | Returns the minimum `r` such that `sum(r) >= w`. Returns `0` when `w <= 0` and `size() + 1` when no such prefix exists. All values must be non-negative. | $O(\log N)$ |

## Example

```cpp
#include "data_structure/fenwick_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5};
    m1une::data_structure::FenwickTree<long long> tree(a);

    // Sum of [1, 4) which is elements at index 1, 2, 3 (2 + 3 + 4 = 9)
    std::cout << tree.sum(1, 4) << "\n"; // Output: 9

    // Add 10 to index 2
    tree.add(2, 10); // Array logically becomes: 1, 2, 13, 4, 5

    // Re-query the sum
    std::cout << tree.sum(1, 4) << "\n"; // Output: 19

    // Find the smallest prefix whose sum is >= 15
    // prefix [0, 3) = 1 + 2 + 13 = 16
    std::cout << tree.lower_bound(15) << "\n"; // Output: 3

    return 0;
}
```
