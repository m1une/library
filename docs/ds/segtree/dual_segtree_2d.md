---
title: Dual Segtree 2D
documentation_of: ../../../ds/segtree/dual_segtree_2d.hpp
---

## Overview

`DualSegtree2D` is a static compressed two-dimensional dual segment tree. It
applies a monoid value to every registered point in a half-open rectangle and
answers the current value of one registered point.

Use it when all point-query coordinates are known before processing updates.
Rectangle boundaries do not need to be registered.

## Requirements

```cpp
template <class Monoid, class X = int, class Y = X>
struct DualSegtree2D;
```

`Monoid` must satisfy `m1une::monoid::IsMonoid`, and its operation must be
commutative. Commutativity is necessary because one rectangle update is stored
in independently compressed x- and y-segment nodes whose values are combined
later at a point query.

`X` and `Y` must be ordered coordinate types. Rectangles use
`[x_lower, x_upper) x [y_lower, y_upper)`.

## Construction

```cpp
DualSegtree2D();
explicit DualSegtree2D(const std::vector<std::pair<X, Y>>& points);
explicit DualSegtree2D(std::vector<std::pair<X, Y>>&& points);
explicit DualSegtree2D(const std::vector<std::tuple<X, Y, T>>& points);
void build(std::vector<std::pair<X, Y>> points);
```

Coordinate constructors initialize every distinct point with `Monoid::id()`.
The weighted constructor combines values at duplicate coordinates with
`Monoid::op`. `build` discards all previous points, values, and updates.

Construction takes $O(N\log^2 N)$ time and $O(N\log N)$ memory.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of distinct registered points. | $O(1)$ |
| `bool empty() const` | Returns whether no point is registered. | $O(1)$ |
| `int x_size() const` | Returns the number of distinct registered x-coordinates. | $O(1)$ |
| `const std::vector<X>& xs() const` | Returns the sorted compressed x-coordinates. | $O(1)$ |
| `bool contains_point(const X& x, const Y& y) const` | Tests whether a point is registered. | $O(\log N)$ |
| `void apply(const X& x, const Y& y, const T& value)` | Applies `value` to one registered point. | $O(\log N)$ |
| `void apply(const X& xl, const X& xr, const Y& yl, const Y& yr, const T& value)` | Applies `value` to every registered point in the rectangle. | $O(\log^2 N)$ |
| `T get(const X& x, const Y& y) const` | Returns a point value, or `Monoid::id()` when unregistered. | $O(\log^2 N)$ |
| `T operator()(const X& x, const Y& y) const` | Alias of `get(x, y)`. | $O(\log^2 N)$ |
| `std::vector<std::tuple<X, Y, T>> to_vector() const` | Returns all registered points and values in coordinate order. | $O(N\log^2 N)$ |

For both `apply` overloads, a stored value `current` becomes
`Monoid::op(value, current)`.

## Example

```cpp
#include "ds/segtree/dual_segtree_2d.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <utility>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    std::vector<std::pair<int, int>> points = {
        {1, 2},
        {3, 4},
        {5, 1},
    };
    m1une::ds::DualSegtree2D<Add> seg(points);

    seg.apply(0, 4, 0, 5, 10);
    seg.apply(3, 4, 7);

    std::cout << seg.get(1, 2) << "\n"; // 10
    std::cout << seg.get(3, 4) << "\n"; // 17
    std::cout << seg.get(5, 1) << "\n"; // 0
}
```
