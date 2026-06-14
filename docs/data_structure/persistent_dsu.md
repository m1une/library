---
title: Persistent Disjoint Set Union
documentation_of: ../../data_structure/persistent_dsu.hpp
---

## Overview

`PersistentDsu` is a persistent Union-Find data structure. Merge operations return a new version and leave the old version available.

It uses union by size without path compression, because path compression mutates the search path. Parent and size values are stored in a persistent array, so each merge shares most nodes with older versions.

## Complexity Notation

* `N` is the number of elements.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `PersistentDsu merge(int a, int b) const` | Returns a new version where the sets containing `a` and `b` are merged. | $O(\log^2 N)$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | $O(\log^2 N)$ |
| `int leader(int a) const` | Returns the representative of the set containing `a`. | $O(\log^2 N)$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the size of the set containing `a`. | $O(\log^2 N)$ |
| `int get(int p) const` | Returns the internal parent-or-size value at index `p`. Roots store negative component sizes; non-roots store parent indices. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \log^2 N)$ |

## Example

```cpp
#include "data_structure/persistent_dsu.hpp"

#include <iostream>

using namespace m1une::data_structure;

int main() {
    PersistentDsu dsu(5);

    PersistentDsu a = dsu.merge(0, 1);
    PersistentDsu b = a.merge(1, 2);

    std::cout << dsu.same(0, 2) << "\n"; // 0
    std::cout << a.same(0, 2) << "\n";   // 0
    std::cout << b.same(0, 2) << "\n";   // 1
    std::cout << b.size(0) << "\n";       // 3
}
```
