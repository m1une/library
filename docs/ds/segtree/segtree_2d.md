---
title: Segtree 2D
documentation_of: ../../../ds/segtree/segtree_2d.hpp
---

## Overview

`m1une::ds::Segtree2D` is a static compressed two-dimensional segment tree.

It supports:

* point assignment on registered points
* point access
* rectangle product queries

The query rectangle is half-open:

[
[x_l, x_r) \times [y_l, y_r)
]

All points that may be updated must be registered before construction.

## Template Parameters

```cpp
template <class Monoid, class X = int, class Y = X>
struct Segtree2D;
```

* `Monoid`: the monoid used for aggregation.
* `X`: the type of x-coordinates.
* `Y`: the type of y-coordinates.

`Monoid` must satisfy `m1une::monoid::IsMonoid`.

The stored value type is:

```cpp
using T = typename Monoid::value_type;
```

## Coordinate Convention

This data structure is statically compressed.

That means every point `(x, y)` that may be updated must be given in the constructor or `build`.

For example, after constructing the data structure with points

```cpp
{(1, 2), (3, 4)}
```

you may call:

```cpp
seg.set(1, 2, value);
seg.set(3, 4, value);
```

but calling

```cpp
seg.set(5, 6, value);
```

is invalid.

## Construction

### Empty constructor

```cpp
Segtree2D()
```

Creates an empty data structure.

### From coordinates

```cpp
explicit Segtree2D(const std::vector<std::pair<X, Y>>& points)
explicit Segtree2D(std::vector<std::pair<X, Y>>&& points)
```

Creates a two-dimensional segment tree with the given registered points.

Duplicate points are removed automatically.

All values are initialized with `Monoid::id()`.

### From weighted points

```cpp
explicit Segtree2D(const std::vector<std::tuple<X, Y, T>>& points)
```

Creates a two-dimensional segment tree with the given weighted points.

Each tuple represents `(x, y, value)`.

If duplicate coordinates are given, the last `set` performed by the constructor determines the final value.

## Methods

Let:

* (N) be the number of registered distinct points
* (X_N) be the number of distinct x-coordinates
* (K_x) be the number of x-segment nodes visited by a query

Usually, (K_x = O(\log X_N)).

| Method                                                             | Description                                                                                 | Complexity      |
| ------------------------------------------------------------------ | ------------------------------------------------------------------------------------------- | --------------- |
| `void build(std::vector<std::pair<X, Y>> points)`                  | Rebuilds the data structure from registered points. All values are reset to `Monoid::id()`. | (O(N \log^2 N)) |
| `int size() const`                                                 | Returns the number of registered distinct points.                                           | (O(1))          |
| `bool empty() const`                                               | Returns whether no point is registered.                                                     | (O(1))          |
| `int x_size() const`                                               | Returns the number of distinct x-coordinates.                                               | (O(1))          |
| `const std::vector<X>& xs() const`                                 | Returns the compressed x-coordinates.                                                       | (O(1))          |
| `bool contains_point(const X& x, const Y& y) const`                | Returns whether `(x, y)` is registered.                                                     | (O(\log N))     |
| `void set(const X& x, const Y& y, T value)`                        | Assigns `value` to the registered point `(x, y)`. Requires that `(x, y)` is registered.     | (O(\log^2 N))   |
| `T get(const X& x, const Y& y) const`                              | Returns the value at `(x, y)`. If the point is not registered, returns `Monoid::id()`.      | (O(\log N))     |
| `T operator()(const X& x, const Y& y) const`                       | Alias of `get(x, y)`.                                                                       | (O(\log N))     |
| `T prod(const X& xl, const X& xr, const Y& yl, const Y& yr) const` | Returns the product over registered points inside `[xl, xr) x [yl, yr)`.                    | (O(\log^2 N))   |
| `T all_prod() const`                                               | Returns the product over all registered points.                                             | (O(1))          |
| `std::vector<std::tuple<X, Y, T>> to_vector() const`               | Returns all registered points with their current values.                                    | (O(N))          |

## Example

```cpp
#include "ds/segtree/segtree_2d.hpp"
#include "monoid/add.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;

    std::vector<std::pair<int, int>> points = {
        {1, 2},
        {1, 5},
        {3, 4},
        {7, 1},
    };

    m1une::ds::Segtree2D<Sum> seg(points);

    seg.set(1, 2, 10);
    seg.set(1, 5, 20);
    seg.set(3, 4, 30);
    seg.set(7, 1, 40);

    assert(seg.get(1, 2) == 10);
    assert(seg.get(2, 2) == 0);

    assert(seg.prod(0, 4, 0, 10) == 60);
    assert(seg.prod(1, 2, 0, 10) == 30);
    assert(seg.prod(0, 10, 0, 3) == 50);
    assert(seg.all_prod() == 100);

    return 0;
}
```

## Example: Static Rectangle Sum

This data structure can be used for static rectangle sum queries.

```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "../../../ds/segtree/segtree_2d.hpp"
#include "../../../monoid/add.hpp"

#include <iostream>
#include <tuple>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    using Sum = m1une::monoid::Add<long long>;

    std::vector<std::tuple<int, int, long long>> points;
    points.reserve(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        long long w;
        std::cin >> x >> y >> w;
        points.emplace_back(x, y, w);
    }

    m1une::ds::Segtree2D<Sum> seg(points);

    while (q--) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        std::cout << seg.prod(l, r, d, u) << '\n';
    }

    return 0;
}
```

## Notes

This data structure is designed for the following situation:

* all update positions are known in advance
* values are updated by point assignment
* queries are axis-aligned rectangle product queries

For point addition, use `get` and `set` together.

```cpp
auto current = seg.get(x, y);
seg.set(x, y, current + delta);
```

For rectangle updates and point queries, use
[`DualSegtree2D`](dual_segtree_2d.md).

Although the template only requires a monoid, rectangle aggregation is usually intended for commutative monoids such as sum, min, max, and gcd.
For non-commutative monoids, the result follows the internal traversal order and may not match a natural geometric interpretation.
