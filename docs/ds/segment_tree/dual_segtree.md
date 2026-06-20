---
title: Dual Segment Tree
documentation_of: ../../../ds/segment_tree/dual_segtree.hpp
---

## Overview

`m1une::ds::DualSegtree` is a generic dual segment tree for range
updates and point queries. Both updates and stored point values are elements of
the same monoid.

Use it when you only need point queries after range updates. If you also need
range queries, use `LazySegtree` instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

`apply(l, r, x)` updates each point value `v` in `[l, r)` to
`Monoid::op(x, v)`.

## Construction

* `DualSegtree()`: creates an empty tree.
* `DualSegtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `DualSegtree(const std::vector<T>& v)`: builds from monoid values.
* `DualSegtree(std::vector<T>&& v)`: builds from moved monoid values.
* `DualSegtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or
  `static_cast<T>(value)` is available.

Construction takes $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Pushes pending updates on the path and assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Pushes pending updates on the path and returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `void apply(int p, T x)` | Applies `x` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, T x)` | Applies `x` to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r - l) \log N)$ |

## Example

```cpp
#include "ds/segment_tree/dual_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    m1une::ds::DualSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});

    seg.apply(1, 4, 10);

    std::cout << seg.get(0) << "\n";  // 1
    std::cout << seg.get(2) << "\n";  // 13

    return 0;
}
```
