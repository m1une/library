---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/angle_sort.test.cpp
    title: verify/geometry/angle_sort.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/angle_sort.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n\
    #include <concepts>\n#include <cassert>\n#include <type_traits>\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
    \ && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
    \ wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;\n\
    \ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\n    constexpr\
    \ Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value) : x(x_value),\
    \ y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr Point(const\
    \ Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 8 \"geometry/angle_sort.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nenum class AngleSortStart {\n    NegativeXAxis,\n    PositiveXAxis,\n\
    };\n\ntemplate <Coordinate T>\nstruct AngleLess {\n    Point<T> origin;\n    AngleSortStart\
    \ start;\n\n    constexpr explicit AngleLess(\n        Point<T> origin_value =\
    \ Point<T>(),\n        AngleSortStart start_value = AngleSortStart::NegativeXAxis\n\
    \    ) : origin(origin_value), start(start_value) {}\n\n    constexpr bool operator()(\n\
    \        const Point<T>& first,\n        const Point<T>& second\n    ) const {\n\
    \        using W = wide_type<T>;\n        W first_x = W(first.x) - W(origin.x);\n\
    \        W first_y = W(first.y) - W(origin.y);\n        W second_x = W(second.x)\
    \ - W(origin.x);\n        W second_y = W(second.y) - W(origin.y);\n        W first_distance\
    \ = first_x * first_x + first_y * first_y;\n        W second_distance = second_x\
    \ * second_x + second_y * second_y;\n\n        // atan2(0, 0) is treated as angle\
    \ zero.\n        if (first_distance == 0) first_x = 1;\n        if (second_distance\
    \ == 0) second_x = 1;\n\n        auto half = [this](W x, W y) {\n            if\
    \ (start == AngleSortStart::PositiveXAxis) {\n                return y < 0 ||\
    \ (y == 0 && x < 0);\n            }\n            return y > 0 || (y == 0 && x\
    \ < 0);\n        };\n\n        bool first_half = half(first_x, first_y);\n   \
    \     bool second_half = half(second_x, second_y);\n        if (first_half !=\
    \ second_half) return first_half < second_half;\n\n        W product = first_x\
    \ * second_y - first_y * second_x;\n        if (product != 0) return product >\
    \ 0;\n\n        return first_distance < second_distance;\n    }\n};\n\n// Sorts\
    \ points counterclockwise by angle around `origin`.\ntemplate <Coordinate T>\n\
    void sort_by_angle(\n    std::vector<Point<T>>& points,\n    Point<T> origin =\
    \ Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n) {\n\
    \    std::sort(points.begin(), points.end(), AngleLess<T>(origin, start));\n}\n\
    \n// Returns a counterclockwise angle-sorted copy.\ntemplate <Coordinate T>\n\
    std::vector<Point<T>> angle_sorted(\n    std::vector<Point<T>> points,\n    Point<T>\
    \ origin = Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n\
    ) {\n    sort_by_angle(points, origin, start);\n    return points;\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_ANGLE_SORT_HPP\n#define M1UNE_GEOMETRY_ANGLE_SORT_HPP\
    \ 1\n\n#include <algorithm>\n#include <vector>\n\n#include \"point.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nenum class AngleSortStart {\n    NegativeXAxis,\n\
    \    PositiveXAxis,\n};\n\ntemplate <Coordinate T>\nstruct AngleLess {\n    Point<T>\
    \ origin;\n    AngleSortStart start;\n\n    constexpr explicit AngleLess(\n  \
    \      Point<T> origin_value = Point<T>(),\n        AngleSortStart start_value\
    \ = AngleSortStart::NegativeXAxis\n    ) : origin(origin_value), start(start_value)\
    \ {}\n\n    constexpr bool operator()(\n        const Point<T>& first,\n     \
    \   const Point<T>& second\n    ) const {\n        using W = wide_type<T>;\n \
    \       W first_x = W(first.x) - W(origin.x);\n        W first_y = W(first.y)\
    \ - W(origin.y);\n        W second_x = W(second.x) - W(origin.x);\n        W second_y\
    \ = W(second.y) - W(origin.y);\n        W first_distance = first_x * first_x +\
    \ first_y * first_y;\n        W second_distance = second_x * second_x + second_y\
    \ * second_y;\n\n        // atan2(0, 0) is treated as angle zero.\n        if\
    \ (first_distance == 0) first_x = 1;\n        if (second_distance == 0) second_x\
    \ = 1;\n\n        auto half = [this](W x, W y) {\n            if (start == AngleSortStart::PositiveXAxis)\
    \ {\n                return y < 0 || (y == 0 && x < 0);\n            }\n     \
    \       return y > 0 || (y == 0 && x < 0);\n        };\n\n        bool first_half\
    \ = half(first_x, first_y);\n        bool second_half = half(second_x, second_y);\n\
    \        if (first_half != second_half) return first_half < second_half;\n\n \
    \       W product = first_x * second_y - first_y * second_x;\n        if (product\
    \ != 0) return product > 0;\n\n        return first_distance < second_distance;\n\
    \    }\n};\n\n// Sorts points counterclockwise by angle around `origin`.\ntemplate\
    \ <Coordinate T>\nvoid sort_by_angle(\n    std::vector<Point<T>>& points,\n  \
    \  Point<T> origin = Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n\
    ) {\n    std::sort(points.begin(), points.end(), AngleLess<T>(origin, start));\n\
    }\n\n// Returns a counterclockwise angle-sorted copy.\ntemplate <Coordinate T>\n\
    std::vector<Point<T>> angle_sorted(\n    std::vector<Point<T>> points,\n    Point<T>\
    \ origin = Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n\
    ) {\n    sort_by_angle(points, origin, start);\n    return points;\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_ANGLE_SORT_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/angle_sort.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-06-23 01:44:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/angle_sort.test.cpp
documentation_of: geometry/angle_sort.hpp
layout: document
title: Angle Sort
---

## Overview

This header sorts points counterclockwise by their angle around a chosen
origin, without calling `atan2`.

```cpp
sort_by_angle(points, origin, start);
auto sorted = angle_sorted(points, origin, start);
```

`sort_by_angle` modifies its argument. `angle_sorted` returns a sorted copy.
Both take $O(N\log N)$ time.

## Complexity Notation

* `N` is the number of points being sorted.

`sort_by_angle` and `angle_sorted` take $O(N\log N)$ time. The comparator uses
$O(1)$ additional memory per comparison.

## Ordering Convention

The default, `AngleSortStart::NegativeXAxis`, sorts by the usual `atan2(y, x)`
value from $-\pi$ to $\pi$. Imagine starting just below the negative x-axis
and rotating counterclockwise:

| Order | Direction | Angle |
| --- | --- | --- |
| 1 | down-left | close to $-\pi$ |
| 2 | down | $-\pi/2$ |
| 3 | right | $0$ |
| 4 | up | $\pi/2$ |
| 5 | left | $\pi$ |

In short:

```text
down-left -> down -> right -> up -> up-left -> left
```

The origin is treated as having angle zero, so it appears with points pointing
right. This convention matches Library Checker's Sort Points by Argument
problem.

`AngleSortStart::PositiveXAxis` uses the more common circular ordering that
starts on the positive x-axis:

```text
right -> up -> left -> down -> back to right
```

Points on the same ray are ordered by increasing distance from `origin`.
Equivalent duplicate points may appear in either relative order.

## Comparator

`AngleLess<T>` is the comparator used by the helpers:

```cpp
m1une::geometry::AngleLess<long long> less(origin);
std::sort(points.begin(), points.end(), less);
```

For integral coordinates, comparisons use signed 128-bit arithmetic. As with
the other exact geometry predicates, coordinate differences and products must
fit that type.

## Example

```cpp
#include "geometry/angle_sort.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(1, 0);
    points.emplace_back(0, 1);
    points.emplace_back(-1, 0);
    points.emplace_back(0, -1);

    m1une::geometry::sort_by_angle(
        points,
        Point(0, 0),
        m1une::geometry::AngleSortStart::PositiveXAxis
    );

    for (const Point& point : points) {
        std::cout << point.x << ' ' << point.y << "\n";
    }
}
```
