---
title: Disjoint Set Union (DSU)
documentation_of: ../../data_structure/dsu.hpp
---

## Overview

A Disjoint Set Union (also known as Union-Find) data structure. It manages a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides near constant time operations to merge sets and find the representative of a set.

It is implemented using **Path Compression** and **Union by Size**, achieving an amortized time complexity of $O(\alpha(N))$ per operation, where $\alpha$ is the inverse Ackermann function.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Dsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int merge(int a, int b)` | Merges the sets containing `a` and `b`; returns the leader of the merged set. | $O(\alpha(N))$ amortized |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | $O(\alpha(N))$ amortized |
| `int leader(int a)` | Returns the representative of the set containing `a`. | $O(\alpha(N))$ amortized |
| `int size(int a)` | Returns the size of the set containing `a`. | $O(\alpha(N))$ amortized |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N)$ |

## Example

```cpp
#include "data_structure/dsu.hpp"
#include <iostream>

int main() {
    // Create DSU with 5 elements (0 to 4)
    m1une::data_structure::Dsu dsu(5);

    dsu.merge(0, 1);
    dsu.merge(2, 3);
    dsu.merge(1, 2);

    std::cout << (dsu.same(0, 3) ? "Same" : "Different") << "\n"; // Output: Same
    std::cout << (dsu.same(0, 4) ? "Same" : "Different") << "\n"; // Output: Different
    std::cout << "Size of group 0: " << dsu.size(0) << "\n";      // Output: 4

    return 0;
}
```
