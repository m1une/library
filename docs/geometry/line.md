---
title: Lines and Segments
documentation_of: ../../geometry/line.hpp
---

## Overview

This header provides `Line<T>` and `Segment<T>` together with projection,
reflection, distances, intersection tests, and line intersection coordinates.

Segment predicates are exact for integral coordinates through 128-bit cross
products. Constructed coordinates are returned as `Point<long double>`.

## Types

```cpp
template <Coordinate T>
struct Line {
    Point<T> a;
    Point<T> b;
};

template <Coordinate T>
struct Segment {
    Point<T> a;
    Point<T> b;
};
```

A line requires distinct endpoints. A segment may be degenerate.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `on_line(line, point, eps)` | Tests whether a point lies on an infinite line. | $O(1)$ |
| `parallel(first, second, eps)` | Tests whether two lines are parallel. | $O(1)$ |
| `orthogonal(first, second, eps)` | Tests whether two lines are perpendicular. | $O(1)$ |
| `projection(line, point)` | Returns the orthogonal projection. | $O(1)$ |
| `reflection(line, point)` | Reflects a point across a line. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two infinite lines share a point, including coincidence. | $O(1)$ |
| `distance(line, point)` | Point-to-line distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Distance between two infinite lines. | $O(1)$ |
| `on_segment(segment, point, eps)` | Tests whether a point lies on a closed segment. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two closed segments intersect, including overlap. | $O(1)$ |
| `intersects(line, segment, eps)` | Tests whether an infinite line and a closed segment intersect. Both argument orders are supported. | $O(1)$ |
| `distance(segment, point)` | Point-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Segment-to-segment distance. | $O(1)$ |
| `distance(line, segment)` | Line-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `line_intersection(first, second, eps)` | Returns the unique line intersection, or `nullopt` for parallel/coincident lines. | $O(1)$ |
| `line_segment_intersection(line, segment, eps)` | Returns the unique intersection, or `nullopt` for no intersection or collinear overlap. Both argument orders are supported. | $O(1)$ |

For a degenerate segment, `line_segment_intersection` returns its endpoint when
that point lies on the line.

## Example

```cpp
#include "geometry/line.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    Segment<long long> first;
    first.a = Point<long long>(0, 0);
    first.b = Point<long long>(2, 2);

    Segment<long long> second;
    second.a = Point<long long>(0, 2);
    second.b = Point<long long>(2, 0);

    std::cout << intersects(first, second) << "\n"; // 1
}
```
