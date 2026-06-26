---
title: Partially Persistent DSU
documentation_of: ../../../ds/dsu/partially_persistent_dsu.hpp
---

## Overview

`PartiallyPersistentDsu` is a Union-Find data structure that supports queries
against old times after merges are applied. The update history is linear:
`merge(a, b)` creates the next time, and queries can be asked at any time from
`0` through the current time.

Time `0` is the initial state. Each call to `merge`, including a no-op merge
inside one component, increases the time by one.

It uses union by size without path compression, because old parent paths must
remain queryable.

## Complexity Notation

* `N` is the number of elements.
* `Q` is the number of merge calls already made.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PartiallyPersistentDsu(int n)` | Creates `n` singleton sets at time `0`. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `int time() const` | Returns the current time. | $O(1)$ |
| `bool merge(int a, int b)` | Advances time by one and merges the current sets containing `a` and `b`. Returns whether two different sets were merged. | $O(\log N)$ |
| `bool same(int t, int a, int b) const` | Returns whether `a` and `b` were in the same set at time `t`. | $O(\log N)$ |
| `bool same(int a, int b) const` | Equivalent to `same(time(), a, b)`. | $O(\log N)$ |
| `int leader(int t, int a) const` | Returns the representative of the set containing `a` at time `t`. | $O(\log N)$ |
| `int leader(int a) const` | Equivalent to `leader(time(), a)`. | $O(\log N)$ |
| `int group_size(int t, int a) const`, `int size(int t, int a) const` | Returns the size of the set containing `a` at time `t`. | $O(\log N + \log Q)$ |
| `int group_size(int a) const`, `int size(int a) const` | Equivalent to querying at the current time. | $O(\log N + \log Q)$ |
| `std::vector<std::vector<int>> groups(int t) const` | Returns all sets at time `t` as vectors of element indices. | $O(N \log N)$ |
| `std::vector<std::vector<int>> groups() const` | Equivalent to `groups(time())`. | $O(N \log N)$ |

## Example

```cpp
#include "ds/dsu/partially_persistent_dsu.hpp"

#include <iostream>

int main() {
    m1une::ds::PartiallyPersistentDsu dsu(4);

    dsu.merge(0, 1); // time 1
    dsu.merge(2, 3); // time 2
    dsu.merge(1, 2); // time 3

    std::cout << dsu.same(1, 0, 2) << "\n"; // 0
    std::cout << dsu.same(3, 0, 2) << "\n"; // 1
    std::cout << dsu.size(2, 0) << "\n";    // 2
    std::cout << dsu.size(3, 0) << "\n";    // 4
}
```
