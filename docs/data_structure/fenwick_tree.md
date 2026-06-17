---
title: Fenwick Tree (Binary Indexed Tree)
documentation_of: ../../data_structure/fenwick_tree.hpp
---

## Overview

A Fenwick Tree (Binary Indexed Tree) is a data structure that can efficiently update elements and calculate prefix sums in an array. It takes significantly less code and less memory overhead than a full Segment Tree.

All indices provided to the API are `0`-indexed, adhering to standard C++ conventions, and the range query covers the half-open interval `[l, r)`.

## Template Parameters

* `T`: The underlying numeric type of the elements (e.g., `int`, `long long`, or a modular integer `modint`).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FenwickTree(int n)` | Initializes an array of size `n` with `0`s. | $O(N)$ |
| `FenwickTree(const std::vector<T>& a)` | Builds a tree from a given vector array `a`. | $O(N)$ |
| `void add(int p, T x)` | Adds `x` to the element at `0`-indexed position `p`. | $O(\log N)$ |
| `T sum(int r) const` | Returns the sum of elements in the prefix `[0, r)`. | $O(\log N)$ |
| `T sum(int l, int r) const` | Returns the sum of elements in the interval `[l, r)`. | $O(\log N)$ |
| `int lower_bound(T w) const` | Binary searches the tree in parallel. Returns the minimum length `r` such that `sum(r) >= w`. **Requires all values to be non-negative.** | $O(\log N)$ |

## Example

```cpp
#include "data_structure/fenwick_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5};
    m1une::data_structure::FenwickTree<long long> fenw(a);

    // Sum of [1, 4) which is elements at index 1, 2, 3 (2 + 3 + 4 = 9)
    std::cout << fenw.sum(1, 4) << "\n"; // Output: 9

    // Add 10 to index 2
    fenw.add(2, 10); // Array logically becomes: 1, 2, 13, 4, 5

    // Re-query the sum
    std::cout << fenw.sum(1, 4) << "\n"; // Output: 19

    // Find the smallest prefix whose sum is >= 15
    // prefix [0, 3) = 1 + 2 + 13 = 16
    std::cout << fenw.lower_bound(15) << "\n"; // Output: 3

    return 0;
}
```
