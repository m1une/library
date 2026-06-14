---
title: Persistent Segment Tree
documentation_of: ../../data_structure/persistent_segtree.hpp
---

## Overview

A persistent segment tree for any monoid satisfying `m1une::monoid::IsMonoid`.
Point updates return a new tree while keeping older versions available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentSegtree(int n)` | Initializes `n` elements with the monoid identity. | $O(N)$ |
| `PersistentSegtree(const std::vector<T>& v)` | Builds the tree from `v`. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `PersistentSegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r-l)$ |
| `int max_right<F>(int l, F f)` | Returns the largest `r` such that `f(prod(l, r))` is `true`. | $O(\log N)$ |
| `int min_left<F>(int r, F f)` | Returns the smallest `l` such that `f(prod(l, r))` is `true`. | $O(\log N)$ |

## Example

```cpp
#include "data_structure/persistent_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Seg = m1une::data_structure::PersistentSegtree<m1une::monoid::Add<long long>>;

    Seg seg(std::vector<long long>{1, 2, 3});
    Seg next = seg.set(1, 10);

    std::cout << seg.prod(0, 3) << "\n";   // 6
    std::cout << next.prod(0, 3) << "\n";  // 14
}
```
