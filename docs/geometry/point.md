---
title: 2D Point and Predicates
documentation_of: ../../geometry/point.hpp
---

## Overview

`Point<T>` is the base type for the 2D geometry library. It provides vector
arithmetic, lexicographic comparison, dot and cross products, distances,
orientation, rotation, and normalization.

For integral coordinates, dot products, cross products, squared norms, and
orientation calculations use signed 128-bit arithmetic. For floating-point
coordinates, predicates use `long double` and accept an epsilon.

As with ordinary integer geometry code, inputs must be small enough that the
promoted 128-bit intermediate result does not overflow.

## Point

```cpp
template <Coordinate T>
struct Point {
    T x;
    T y;
};
```

`Point` supports equality, lexicographic `<`, unary signs, addition,
subtraction, scalar multiplication, and scalar division.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `dot(a, b)` | Dot product. | $O(1)$ |
| `cross(a, b)` | Cross product of two vectors. | $O(1)$ |
| `cross(origin, a, b)` | Cross product of vectors `a - origin` and `b - origin`. | $O(1)$ |
| `norm2(p)` | Squared Euclidean norm. | $O(1)$ |
| `distance2(a, b)` | Squared Euclidean distance. | $O(1)$ |
| `norm(p)` | Euclidean norm as `long double`. | $O(1)$ |
| `distance(a, b)` | Euclidean distance as `long double`. | $O(1)$ |
| `internal_division_point(a, b, m, n)` | Returns the point internally dividing `AB` in ratio `AP:PB = m:n`. | $O(1)$ |
| `external_division_point(a, b, m, n)` | Returns the point externally dividing `AB` in ratio `AP:PB = m:n`. | $O(1)$ |
| `orientation(a, b, c, eps)` | Returns `1` for counterclockwise, `-1` for clockwise, and `0` for collinear. | $O(1)$ |
| `collinear(a, b, c, eps)` | Returns whether three points are collinear. | $O(1)$ |
| `rotate(p, angle)` | Rotates `p` counterclockwise by radians. | $O(1)$ |
| `normalized(p)` | Returns a unit vector in `p`'s direction. | $O(1)$ |

`normalized` requires a nonzero vector.

## Internal and external division

For `internal_division_point(a, b, m, n)`, the returned point $P$ satisfies
$AP:PB=m:n$ and is computed as

$$
P = A + \frac{m}{m+n}(B-A).
$$

For positive `m` and `n`, `P` lies between `a` and `b`. The function requires
`m + n != 0`.

`external_division_point` uses the same ratio convention:

$$
P = A + \frac{m}{m-n}(B-A).
$$

For positive unequal ratios, the point lies outside the segment. It is beyond
`b` when `m > n` and beyond `a` when `m < n`. The function requires
`m != n`. Both functions return `Point<long double>`.

## Example

```cpp
#include "geometry/point.hpp"

#include <iostream>

int main() {
    using Point = m1une::geometry::Point<long long>;
    Point a(0, 0);
    Point b(3, 0);
    Point c(1, 2);

    std::cout << m1une::geometry::orientation(a, b, c) << "\n"; // 1
    std::cout << m1une::geometry::cross(a, b, c) << "\n";       // 6
}
```
