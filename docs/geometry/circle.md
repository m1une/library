---
title: Circles
documentation_of: ../../geometry/circle.hpp
---

## Overview

This header provides circle relationships and intersection points with lines
and other circles. Constructed points use `long double`.

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
| `circle_intersections(first, second, eps)` | Returns zero, one, or two intersection points in lexicographic order. Coincident circles return an empty vector because intersections are not unique. | $O(1)$ |

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
