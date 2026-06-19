---
title: Persistent Lazy Segment Tree
documentation_of: ../../data_structure/persistent_lazy_segtree.hpp
---

## Overview

A persistent lazy segment tree for any acted monoid satisfying
`m1une::acted_monoid::IsActedMonoid`. Point assignments and range updates return
new versions while older versions remain available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentLazySegtree(int n)` | Initializes `n` elements with the value monoid identity. | $O(N)$ |
| `PersistentLazySegtree(const std::vector<T>& v)` | Builds the tree from `v`. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `PersistentLazySegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the acted-monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r - l)$ |
| `PersistentLazySegtree apply(int p, F f)` | Returns a new version where `f` is applied to index `p`. | $O(\log N)$ |
| `PersistentLazySegtree apply(int l, int r, F f)` | Returns a new version where `f` is applied to every element in `[l, r)`. | $O(\log N)$ |
| `int max_right<G>(int l, G g)` | Returns the largest `r` such that `g(prod(l, r))` is `true`. | $O(\log N)$ |
| `int min_left<G>(int r, G g)` | Returns the smallest `l` such that `g(prod(l, r))` is `true`. | $O(\log N)$ |

## Example

```cpp
#include "data_structure/persistent_lazy_segtree.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::data_structure::PersistentLazySegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4});
    Seg next = seg.apply(1, 3, 10);

    std::cout << seg.prod(0, 4).sum << "\n";   // 10
    std::cout << next.prod(0, 4).sum << "\n";  // 30
}
```
