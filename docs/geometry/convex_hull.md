---
title: Convex Hull
documentation_of: ../../geometry/convex_hull.hpp
---

## Overview

`convex_hull` returns the smallest convex polygon containing a set of points.
It uses Andrew's monotone-chain algorithm.

The result is counterclockwise, starts at the lexicographically smallest point,
and does not repeat its first point at the end. Duplicate input points are
removed.

## Function

```cpp
template <Coordinate T>
std::vector<Point<T>> convex_hull(
    std::vector<Point<T>> points,
    bool include_collinear = false);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `convex_hull(points, include_collinear)` | Constructs the convex hull. | $O(N\log N)$ time and $O(N)$ memory. |

By default, points strictly between the endpoints of a hull edge are omitted.
Pass `true` to retain every distinct point on the hull boundary.

Degenerate inputs behave as follows:

* no points produce an empty hull;
* one distinct point produces that point;
* collinear points produce the two endpoints by default, or every point in
  lexicographic order when `include_collinear` is true.

Integral coordinates use signed 128-bit cross products. Floating-point
coordinates use the geometry module's default orientation tolerance.

## Example

```cpp
#include "geometry/convex_hull.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(2, 0);
    points.emplace_back(1, 1);
    points.emplace_back(1, 0);

    auto hull = m1une::geometry::convex_hull(points);
    for (const Point& point : hull) {
        std::cout << point.x << " " << point.y << "\n";
    }
}
```
