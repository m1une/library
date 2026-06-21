---
title: Rays
documentation_of: ../../geometry/ray.hpp
---

## Overview

`Ray<T>` represents a closed half-line and provides containment, projection,
intersection, intersection coordinates, and distances involving points, lines,
segments, and other rays.

```cpp
#include "geometry/ray.hpp"
```

Integral intersection predicates use signed 128-bit arithmetic. Constructed
points and distances use `long double`.

## Type

```cpp
template <Coordinate T>
struct Ray {
    Point<T> origin;
    Point<T> through;
};
```

The ray starts at `origin`, contains `through`, and continues indefinitely in
the direction `through - origin`. These two points must be distinct.

## Point operations

| Function | Description | Complexity |
| --- | --- | --- |
| `on_ray(ray, point, eps)` | Tests whether `point` belongs to the closed ray. The origin is included. | $O(1)$ |
| `projection(ray, point)` | Returns the closest point on the ray. A projection behind the origin is clamped to the origin. | $O(1)$ |
| `distance(ray, point)` | Returns the point-to-ray distance. The reversed argument order is also supported. | $O(1)$ |
| `reflection(line, ray)` | Reflects the complete ray across an infinite line. | $O(1)$ |
| `reflected_ray(incoming, hit, mirror, eps)` | Creates the outgoing ray after `incoming` hits `mirror` at `hit`. | $O(1)$ |

`reflected_ray` requires `hit` to lie on `mirror`. Its result starts at `hit`;
the angle of incidence equals the angle of reflection.

## Intersection predicates

| Function | Description | Complexity |
| --- | --- | --- |
| `intersects(ray, line, eps)` | Tests whether a ray and an infinite line share a point. | $O(1)$ |
| `intersects(ray, segment, eps)` | Tests whether a ray and a closed segment share a point. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two closed rays share a point. | $O(1)$ |

The line-ray and segment-ray reversed argument orders are also supported.
Collinear overlap counts as an intersection.

## Intersection coordinates

| Function | Description | Complexity |
| --- | --- | --- |
| `ray_line_intersection(ray, line, eps)` | Returns the unique intersection point. | $O(1)$ |
| `ray_segment_intersection(ray, segment, eps)` | Returns the unique intersection point. | $O(1)$ |
| `ray_intersection(first, second, eps)` | Returns the unique intersection point of two rays. | $O(1)$ |

The line-ray and segment-ray reversed argument orders are also supported.
These functions return `std::nullopt` when there is no intersection or when the
intersection is not unique, such as collinear overlap. A collinear segment that
only touches the ray origin and two opposite rays with the same origin do have
a unique intersection. Use `intersects` first when overlap and disjointness
must be distinguished.

## Distances

| Function | Description | Complexity |
| --- | --- | --- |
| `distance(ray, line)` | Minimum ray-to-line distance. | $O(1)$ |
| `distance(ray, segment)` | Minimum ray-to-segment distance. | $O(1)$ |
| `distance(first, second)` | Minimum distance between two rays. | $O(1)$ |

Line-ray and segment-ray reversed argument orders are supported. Intersecting
objects have distance zero.

## Example

```cpp
#include "geometry/ray.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    using P = Point<long long>;

    Ray<long long> ray;
    ray.origin = P(0, 0);
    ray.through = P(1, 0);

    Segment<long long> wall;
    wall.a = P(3, -2);
    wall.b = P(3, 2);

    auto hit = ray_segment_intersection(ray, wall);
    if (hit.has_value()) {
        std::cout << hit->x << " " << hit->y << "\n";
    }
}
```
