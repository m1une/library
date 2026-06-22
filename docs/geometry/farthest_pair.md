---
title: Farthest Pair of Points
documentation_of: ../../geometry/farthest_pair.hpp
---

## Overview

`farthest_pair(points)` returns two distinct input points whose Euclidean
distance is maximum. It first constructs the convex hull, then examines
antipodal hull vertices with rotating calipers.

`furthest_pair(points)` is an alias with identical behavior.

## Result

```cpp
template <Coordinate T>
struct FarthestPair {
    int first;
    int second;
    wide_type<T> distance_squared;
};
```

`first` and `second` are indices in the original input, ordered so that
`first < second`. The distance is squared, avoiding a square root and retaining
exact arithmetic for integral coordinates.

Both functions return `std::nullopt` when fewer than two points are supplied.
Duplicate points are supported. If all points coincide, two distinct input
indices are returned with squared distance zero.

When several pairs have the same maximum distance, the lexicographically
smallest index pair is returned.

## Complexity

The time complexity is $O(N\log N)$ and the memory usage is $O(N)$.

## Example

```cpp
#include "geometry/farthest_pair.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(3, 0);
    points.emplace_back(1, 2);

    auto result = m1une::geometry::farthest_pair(points);
    if (result) {
        std::cout << result->first << ' ' << result->second << "\n";
        std::cout << static_cast<long long>(result->distance_squared) << "\n";
    }
}
```
