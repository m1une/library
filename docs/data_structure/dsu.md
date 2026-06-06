---
title: Disjoint Set Union (DSU)
documentation_of: ../../data_structure/dsu.hpp
---

## Overview

A Disjoint Set Union (also known as Union-Find) data structure. It manages a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides near constant time operations to merge sets and find the representative of a set.

It is implemented using **Path Compression** and **Union by Size**, achieving an amortized time complexity of $O(\alpha(N))$ per operation, where $\alpha$ is the inverse Ackermann function.

## Methods

* `Dsu(int n)`
  Constructs a DSU of size `n`, where each element is initially in its own subset. Time complexity: $O(N)$.

* `int merge(int a, int b)`
  Merges the subset containing `a` and the subset containing `b`. Returns the representative (leader) of the newly merged subset. Time complexity: $O(\alpha(N))$ amortized.

* `bool same(int a, int b)`
  Returns `true` if `a` and `b` are in the same subset, `false` otherwise. Time complexity: $O(\alpha(N))$ amortized.

* `int leader(int a)`
  Returns the representative (leader) of the subset containing `a`. Time complexity: $O(\alpha(N))$ amortized.

* `int size(int a)`
  Returns the size of the subset containing `a`. Time complexity: $O(\alpha(N))$ amortized.

* `std::vector<std::vector<int>> groups()`
  Returns a list of all subsets. Each subset is represented as a `std::vector<int>`. Time complexity: $O(N)$.

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
