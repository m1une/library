---
title: Circles
documentation_of: ../../geometry/circle.hpp
---

## Overview

This header provides circle relationships, intersection points with lines,
rays, and other circles, and physical ray reflection. Constructed points use
`long double`.

## Types

```cpp
template <Coordinate T>
struct Circle {
    Point<T> center;
    T radius;
};
```

Radii must be nonnegative.

`CircleRelation` has these cases:

* `Separate`
* `ExternallyTangent`
* `Intersecting`
* `InternallyTangent`
* `Contained`
* `Coincident`

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `circle_relation(first, second, eps)` | Classifies two circles. | $O(1)$ |
| `circle_line_intersections(circle, line, eps)` | Returns zero, one, or two intersection points in lexicographic order. | $O(1)$ |
| `circle_ray_intersections(circle, ray, eps)` | Returns zero, one, or two intersections ordered from the ray origin. Both argument orders are supported. | $O(1)$ |
| `first_circle_ray_intersection(circle, ray, eps)` | Returns the first intersection along the ray, or `nullopt`. | $O(1)$ |
| `intersects(circle, ray, eps)` | Tests whether a circle boundary and ray intersect. Both argument orders are supported. | $O(1)$ |
| `reflected_ray(incoming, hit, circle, eps)` | Returns the outgoing ray after reflection from the circle at `hit`. | $O(1)$ |
| `circle_intersections(first, second, eps)` | Returns zero, one, or two intersection points in lexicographic order. Coincident circles return an empty vector because intersections are not unique. | $O(1)$ |

`circle_ray_intersections` intersects the ray with the circle boundary, not its
filled disk. A ray starting inside the circle therefore has one forward
intersection. A tangent has one intersection, and intersections behind the ray
origin are omitted.

`reflected_ray` reflects the incoming direction across the tangent line at
`hit`, so the angle of incidence equals the angle of reflection. `hit` must lie
on the circle. The radius must be positive because a zero-radius circle has no
defined tangent.

## Example

```cpp
#include "geometry/circle.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    Circle<double> circle;
    circle.center = Point<double>(0, 0);
    circle.radius = 2;

    Line<double> line;
    line.a = Point<double>(-3, 0);
    line.b = Point<double>(3, 0);

    auto intersections = circle_line_intersections(circle, line);
    std::cout << intersections.size() << "\n"; // 2
}
```
