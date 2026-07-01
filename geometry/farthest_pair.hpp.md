---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/farthest_pair.test.cpp
    title: verify/geometry/farthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/farthest_pair.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cstddef>\n#include <map>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"geometry/convex_hull.hpp\"\n\n\n\n#line 8 \"geometry/convex_hull.hpp\"\
    \n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include <concepts>\n\
    #include <cassert>\n#include <type_traits>\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> &&\
    \ !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
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
    \ m1une\n\n\n#line 10 \"geometry/convex_hull.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\n// Returns the convex hull counterclockwise from its lexicographically\
    \ smallest\n// point. The first point is not repeated at the end.\ntemplate <Coordinate\
    \ T>\nstd::vector<Point<T>> convex_hull(\n    std::vector<Point<T>> points,\n\
    \    bool include_collinear = false\n) {\n    std::sort(points.begin(), points.end());\n\
    \    points.erase(std::unique(points.begin(), points.end()), points.end());\n\
    \    std::size_t size = points.size();\n    if (size <= 1) return points;\n\n\
    \    std::vector<Point<T>> hull;\n    hull.reserve(2 * size);\n    auto should_pop\
    \ = [include_collinear](\n        const Point<T>& first,\n        const Point<T>&\
    \ second,\n        const Point<T>& third\n    ) {\n        int turn = orientation(first,\
    \ second, third);\n        return include_collinear ? turn < 0 : turn <= 0;\n\
    \    };\n\n    for (const Point<T>& point : points) {\n        while (\n     \
    \       hull.size() >= 2 &&\n            should_pop(hull[hull.size() - 2], hull.back(),\
    \ point)\n        ) {\n            hull.pop_back();\n        }\n        hull.push_back(point);\n\
    \    }\n\n    std::size_t lower_size = hull.size();\n    for (std::size_t index\
    \ = size - 1; index-- > 0;) {\n        const Point<T>& point = points[index];\n\
    \        while (\n            hull.size() > lower_size &&\n            should_pop(hull[hull.size()\
    \ - 2], hull.back(), point)\n        ) {\n            hull.pop_back();\n     \
    \   }\n        hull.push_back(point);\n    }\n    hull.pop_back();\n\n    if (include_collinear\
    \ && hull.size() == 2 * points.size() - 2) {\n        hull = std::move(points);\n\
    \    }\n    return hull;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n\n#line 12 \"geometry/farthest_pair.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\ntemplate <Coordinate T>\nstruct FarthestPair {\n    int first;\n    int\
    \ second;\n    wide_type<T> distance_squared;\n};\n\n// Returns two distinct original\
    \ indices with maximum Euclidean distance.\ntemplate <Coordinate T>\nstd::optional<FarthestPair<T>>\
    \ farthest_pair(\n    const std::vector<Point<T>>& points\n) {\n    if (points.size()\
    \ < 2) return std::nullopt;\n\n    std::vector<Point<T>> hull = convex_hull(points);\n\
    \    if (hull.size() == 1) {\n        FarthestPair<T> result;\n        result.first\
    \ = 0;\n        result.second = 1;\n        result.distance_squared = 0;\n   \
    \     return result;\n    }\n\n    std::map<Point<T>, int> original_index;\n \
    \   for (int index = 0; index < int(points.size()); ++index) {\n        original_index.emplace(points[index],\
    \ index);\n    }\n\n    std::vector<int> hull_index;\n    hull_index.reserve(hull.size());\n\
    \    for (const Point<T>& point : hull) {\n        hull_index.push_back(original_index.find(point)->second);\n\
    \    }\n\n    std::optional<FarthestPair<T>> result;\n    auto consider = [&result,\
    \ &points](int first, int second) {\n        if (second < first) std::swap(first,\
    \ second);\n        wide_type<T> squared = distance2(points[first], points[second]);\n\
    \        if (\n            !result.has_value() ||\n            result->distance_squared\
    \ < squared ||\n            (\n                result->distance_squared == squared\
    \ &&\n                std::pair(first, second) <\n                    std::pair(result->first,\
    \ result->second)\n            )\n        ) {\n            result = FarthestPair<T>{first,\
    \ second, squared};\n        }\n    };\n\n    if (hull.size() == 2) {\n      \
    \  consider(hull_index[0], hull_index[1]);\n        return result;\n    }\n\n\
    \    std::size_t opposite = 1;\n    for (std::size_t index = 0; index < hull.size();\
    \ ++index) {\n        std::size_t next = (index + 1) % hull.size();\n        while\
    \ (true) {\n            std::size_t candidate = (opposite + 1) % hull.size();\n\
    \            auto current_area = cross(\n                hull[index],\n      \
    \          hull[next],\n                hull[opposite]\n            );\n     \
    \       auto candidate_area = cross(\n                hull[index],\n         \
    \       hull[next],\n                hull[candidate]\n            );\n       \
    \     if (candidate_area <= current_area) break;\n            opposite = candidate;\n\
    \        }\n        consider(hull_index[index], hull_index[opposite]);\n     \
    \   consider(hull_index[next], hull_index[opposite]);\n\n        std::size_t candidate\
    \ = (opposite + 1) % hull.size();\n        auto current_area = cross(hull[index],\
    \ hull[next], hull[opposite]);\n        auto candidate_area = cross(hull[index],\
    \ hull[next], hull[candidate]);\n        if (candidate_area == current_area) {\n\
    \            consider(hull_index[index], hull_index[candidate]);\n           \
    \ consider(hull_index[next], hull_index[candidate]);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nstd::optional<FarthestPair<T>> furthest_pair(\n\
    \    const std::vector<Point<T>>& points\n) {\n    return farthest_pair(points);\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_FARTHEST_PAIR_HPP\n#define M1UNE_GEOMETRY_FARTHEST_PAIR_HPP\
    \ 1\n\n#include <algorithm>\n#include <cstddef>\n#include <map>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\n#include \"convex_hull.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct FarthestPair\
    \ {\n    int first;\n    int second;\n    wide_type<T> distance_squared;\n};\n\
    \n// Returns two distinct original indices with maximum Euclidean distance.\n\
    template <Coordinate T>\nstd::optional<FarthestPair<T>> farthest_pair(\n    const\
    \ std::vector<Point<T>>& points\n) {\n    if (points.size() < 2) return std::nullopt;\n\
    \n    std::vector<Point<T>> hull = convex_hull(points);\n    if (hull.size() ==\
    \ 1) {\n        FarthestPair<T> result;\n        result.first = 0;\n        result.second\
    \ = 1;\n        result.distance_squared = 0;\n        return result;\n    }\n\n\
    \    std::map<Point<T>, int> original_index;\n    for (int index = 0; index <\
    \ int(points.size()); ++index) {\n        original_index.emplace(points[index],\
    \ index);\n    }\n\n    std::vector<int> hull_index;\n    hull_index.reserve(hull.size());\n\
    \    for (const Point<T>& point : hull) {\n        hull_index.push_back(original_index.find(point)->second);\n\
    \    }\n\n    std::optional<FarthestPair<T>> result;\n    auto consider = [&result,\
    \ &points](int first, int second) {\n        if (second < first) std::swap(first,\
    \ second);\n        wide_type<T> squared = distance2(points[first], points[second]);\n\
    \        if (\n            !result.has_value() ||\n            result->distance_squared\
    \ < squared ||\n            (\n                result->distance_squared == squared\
    \ &&\n                std::pair(first, second) <\n                    std::pair(result->first,\
    \ result->second)\n            )\n        ) {\n            result = FarthestPair<T>{first,\
    \ second, squared};\n        }\n    };\n\n    if (hull.size() == 2) {\n      \
    \  consider(hull_index[0], hull_index[1]);\n        return result;\n    }\n\n\
    \    std::size_t opposite = 1;\n    for (std::size_t index = 0; index < hull.size();\
    \ ++index) {\n        std::size_t next = (index + 1) % hull.size();\n        while\
    \ (true) {\n            std::size_t candidate = (opposite + 1) % hull.size();\n\
    \            auto current_area = cross(\n                hull[index],\n      \
    \          hull[next],\n                hull[opposite]\n            );\n     \
    \       auto candidate_area = cross(\n                hull[index],\n         \
    \       hull[next],\n                hull[candidate]\n            );\n       \
    \     if (candidate_area <= current_area) break;\n            opposite = candidate;\n\
    \        }\n        consider(hull_index[index], hull_index[opposite]);\n     \
    \   consider(hull_index[next], hull_index[opposite]);\n\n        std::size_t candidate\
    \ = (opposite + 1) % hull.size();\n        auto current_area = cross(hull[index],\
    \ hull[next], hull[opposite]);\n        auto candidate_area = cross(hull[index],\
    \ hull[next], hull[candidate]);\n        if (candidate_area == current_area) {\n\
    \            consider(hull_index[index], hull_index[candidate]);\n           \
    \ consider(hull_index[next], hull_index[candidate]);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nstd::optional<FarthestPair<T>> furthest_pair(\n\
    \    const std::vector<Point<T>>& points\n) {\n    return farthest_pair(points);\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_FARTHEST_PAIR_HPP\n"
  dependsOn:
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/farthest_pair.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-01 22:47:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/farthest_pair.test.cpp
documentation_of: geometry/farthest_pair.hpp
layout: document
title: Farthest Pair of Points
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
