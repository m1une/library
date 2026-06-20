---
title: Polygons and Convex Hull
documentation_of: ../../geometry/polygon.hpp
---

## Overview

This header provides polygon area, monotone-chain convex hull, point
containment, and rotating-calipers convex diameter.

Polygons are represented by `std::vector<Point<T>>`. The first point must not be
repeated at the end.

## Point Containment

`point_in_polygon` returns:

* `PointInPolygon::Outside`
* `PointInPolygon::Boundary`
* `PointInPolygon::Inside`

The polygon may be clockwise or counterclockwise and may be non-convex.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `polygon_area2(polygon)` | Returns signed twice-area. Positive means counterclockwise. | $O(N)$ |
| `polygon_area(polygon)` | Returns absolute area as `long double`. | $O(N)$ |
| `convex_hull(points, include_collinear)` | Returns the hull counterclockwise from its lexicographically smallest point, without repeating the first point. | $O(N \log N)$ |
| `point_in_polygon(polygon, point, eps)` | Classifies a point against any simple polygon. | $O(N)$ |
| `convex_diameter2(polygon)` | Returns the maximum squared distance between vertices of a convex counterclockwise polygon. | $O(N)$ |

By default, `convex_hull` removes points lying strictly inside hull edges.
Passing `true` keeps boundary-collinear points. Duplicate input points are
removed.

## Example

```cpp
#include "geometry/polygon.hpp"

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
    std::cout << hull.size() << "\n"; // 3
}
```
