---
title: Polygons
documentation_of: ../../geometry/polygon.hpp
---

## Overview

This header provides polygon area, point containment, rotating-calipers convex
diameter, ray queries, polygon intersection and distance, triangulation,
centroids, convex clipping, and Minkowski sums.

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
| `polygon_centroid(polygon, eps)` | Returns the centroid of a uniformly filled polygon, or `nullopt` for zero area. | $O(N)$ |
| `polygon_center_of_gravity(polygon, eps)` | Alias of `polygon_centroid`. | $O(N)$ |
| `is_simple_polygon(polygon, eps)` | Tests whether polygon edges only meet at adjacent endpoints. | $O(N^2)$ |
| `triangulate_polygon(polygon, eps)` | Ear-clips a simple polygon, or returns `nullopt` when triangulation fails. | $O(N^2)$ |
| `triangulate_convex_polygon(polygon, eps)` | Fan-triangulates a convex polygon. | $O(N)$ |
| `point_in_polygon(polygon, point, eps)` | Classifies a point against any simple polygon. | $O(N)$ |
| `convex_diameter2(polygon)` | Returns the maximum squared distance between vertices of a convex counterclockwise polygon. | $O(N)$ |
| `ray_polygon_intersections(ray, polygon, eps)` | Returns distinct boundary events ordered from the ray origin. | $O(N \log N)$ |
| `first_ray_polygon_intersection(ray, polygon, eps)` | Returns the first boundary event, or `nullopt`. | $O(N \log N)$ |
| `intersects(ray, polygon, eps)` | Tests intersection with the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `distance(ray, polygon)` | Minimum distance to the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `intersects(first, second, eps)` | Tests whether two closed filled simple polygons intersect. | $O(NM)$ |
| `distance(first, second)` | Minimum distance between two closed filled simple polygons. | $O(NM)$ |
| `convex_polygon_intersection(first, second, eps)` | Returns the intersection of two convex polygons. | $O(NM)$ |
| `minkowski_sum(first, second)` | Returns the Minkowski sum of two convex polygons. | $O(N+M)$ |

Polygon queries require at least three vertices unless stated otherwise.

## Centroid and center of gravity

`polygon_centroid` computes the center of gravity of a lamina with uniform
density over the polygon's filled area. It accepts clockwise or
counterclockwise simple polygons and returns `Point<long double>`.

A polygon with zero signed area has no area centroid, so the function returns
`std::nullopt`. This is different from the arithmetic mean of the vertices,
which generally is not the polygon's center of gravity.

## Triangulation

`triangulate_polygon` uses ear clipping and accepts clockwise or
counterclockwise simple polygons. It removes a repeated closing point,
consecutive duplicate points, and redundant collinear boundary vertices before
triangulation. The result contains counterclockwise triangles whose interiors
are disjoint and whose union is the polygon. An input with $K$ remaining
vertices produces $K-2$ triangles.

The return value is `std::nullopt` for fewer than three effective vertices,
zero area, self-intersection, or another failure to find a valid ear.

`triangulate_convex_polygon` is the faster fan construction. It has the same
vertex cleanup and orientation normalization, but assumes the input is convex;
violating that precondition can produce triangles outside the polygon.

## Ray intersections

`ray_polygon_intersections` reports polygon-boundary events, not the whole
filled interval inside the polygon. A collinear boundary overlap contributes
its finite endpoints and the ray origin when the overlap starts there. Shared
polygon vertices are deduplicated.

`intersects(ray, polygon)` instead treats the polygon as a closed filled region,
so a ray whose origin is inside the polygon intersects immediately.

## Polygon intersection

`intersects(first, second)` and `distance(first, second)` accept any simple
polygons, in clockwise or counterclockwise order.

`convex_polygon_intersection` constructs the overlap region and therefore
requires both inputs to be convex. The result uses `Point<long double>`, is
counterclockwise when it has area, and does not repeat its first point. A
touching intersection may contain one point or two segment endpoints.

## Minkowski sum

`minkowski_sum` requires nonempty convex polygons. Inputs may be clockwise or
counterclockwise and may contain redundant collinear vertices. The result is a
counterclockwise convex polygon without a repeated first point. Coordinates
retain type `T`; ensure additions fit that type.

For convex-hull construction, include
[`geometry/convex_hull.hpp`](convex_hull.md).

## Example

```cpp
#include "geometry/polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(2, 0);
    polygon.emplace_back(0, 2);

    std::cout << m1une::geometry::polygon_area(polygon) << "\n"; // 2
}
```
