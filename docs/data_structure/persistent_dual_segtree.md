---
title: Persistent Dual Segment Tree
documentation_of: ../../data_structure/persistent_dual_segtree.hpp
---

## Overview

A persistent dual segment tree for any acted monoid satisfying
`m1une::acted_monoid::IsActedMonoid`. Range updates and point assignments return
new versions while older versions remain available.

Use it when you need versioned range updates and point queries. If you also need
range products on each version, use `PersistentLazySegtree`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDualSegtree(int n)` | Initializes `n` elements with the value monoid identity. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<T>& v)` | Builds the tree from acted-monoid values. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<U>& v)` | Builds from another value type when `ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or `static_cast<T>(value)` is available. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `PersistentDualSegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int p, F f)` | Returns a new version where `f` is applied to index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int l, int r, F f)` | Returns a new version where `f` is applied to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r-l)$ |

## Example

```cpp
#include "data_structure/persistent_dual_segtree.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::data_structure::PersistentDualSegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4});
    Seg next = seg.apply(1, 3, 10);

    std::cout << seg.get(2).sum << "\n";   // 3
    std::cout << next.get(2).sum << "\n";  // 13
}
```
