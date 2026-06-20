---
title: Segment Tree
documentation_of: ../../../ds/segtree/segtree.hpp
---

## Overview

`m1une::ds::Segtree` is a generic segment tree for point updates and
range queries. The query operation is supplied by a monoid, so the same data
structure can handle sums, minimums, maximums, gcd, affine composition, and other
associative operations.

Use it when updates affect one position at a time. For range updates, use
`LazySegtree` with an acted monoid instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

Ready-made monoids are available in `monoid/`.

## Construction

* `Segtree()`: creates an empty tree.
* `Segtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `Segtree(const std::vector<T>& v)`: builds from monoid values.
* `Segtree(std::vector<T>&& v)`: builds from moved monoid values.
* `Segtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
  is available.

All non-empty constructors build the tree in $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(1)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(1)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(r - l)$ |
| `int max_right<F>(int l, F f)` | Returns the largest `r` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |
| `int min_left<F>(int r, F f)` | Returns the smallest `l` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::Segtree<Sum> seg(std::vector<long long>{0, 0, 0, 0, 0});

    seg.set(0, 10);
    seg.set(2, 20);

    std::cout << seg.prod(0, 3) << "\n";  // 30

    return 0;
}
```
