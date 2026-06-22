---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/manhattan_mst.test.cpp
    title: verify/geometry/manhattan_mst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/manhattan_mst.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <limits>\n#include <map>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent of i\
    \ if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is\
    \ the size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n\
    #line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
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
    \ m1une\n\n\n#line 15 \"geometry/manhattan_mst.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <class T>\nstruct ManhattanMstEdge {\n    int from;\n\
    \    int to;\n    T cost;\n};\n\ntemplate <class T>\nstruct ManhattanMst {\n \
    \   T cost;\n    std::vector<ManhattanMstEdge<T>> edges;\n};\n\n// Returns O(n)\
    \ edges containing a Manhattan minimum spanning tree.\ntemplate <std::integral\
    \ T>\nstd::vector<ManhattanMstEdge<wide_type<T>>> manhattan_mst_edges(const std::vector<Point<T>>&\
    \ points) {\n    using W = wide_type<T>;\n    assert(points.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \    int n = int(points.size());\n    std::vector<Point<W>> transformed;\n   \
    \ transformed.reserve(points.size());\n    for (const auto& point : points) {\n\
    \        transformed.emplace_back(W(point.x), W(point.y));\n    }\n\n    std::vector<int>\
    \ order(n);\n    std::iota(order.begin(), order.end(), 0);\n    std::vector<ManhattanMstEdge<W>>\
    \ edges;\n    edges.reserve(std::size_t(4) * points.size());\n\n    for (int direction\
    \ = 0; direction < 4; direction++) {\n        std::sort(order.begin(), order.end(),\
    \ [&transformed](int i, int j) {\n            W first = transformed[i].x + transformed[i].y;\n\
    \            W second = transformed[j].x + transformed[j].y;\n            if (first\
    \ != second) return first < second;\n            if (transformed[i].x != transformed[j].x)\
    \ {\n                return transformed[i].x < transformed[j].x;\n           \
    \ }\n            return i < j;\n        });\n\n        std::map<W, int> sweep;\n\
    \        for (int i : order) {\n            auto it = sweep.lower_bound(-transformed[i].y);\n\
    \            while (it != sweep.end()) {\n                int j = it->second;\n\
    \                if (transformed[i].x - transformed[j].x < transformed[i].y -\
    \ transformed[j].y) {\n                    break;\n                }\n\n     \
    \           W dx = W(points[i].x) - W(points[j].x);\n                W dy = W(points[i].y)\
    \ - W(points[j].y);\n                if (dx < 0) dx = -dx;\n                if\
    \ (dy < 0) dy = -dy;\n                edges.push_back(ManhattanMstEdge<W>{i, j,\
    \ dx + dy});\n                it = sweep.erase(it);\n            }\n         \
    \   sweep[-transformed[i].y] = i;\n        }\n\n        for (auto& point : transformed)\
    \ {\n            if (direction & 1) {\n                point.x = -point.x;\n \
    \           } else {\n                std::swap(point.x, point.y);\n         \
    \   }\n        }\n    }\n    return edges;\n}\n\n// Returns a Manhattan minimum\
    \ spanning tree.\ntemplate <std::integral T>\nManhattanMst<wide_type<T>> manhattan_mst(const\
    \ std::vector<Point<T>>& points) {\n    using W = wide_type<T>;\n    auto candidates\
    \ = manhattan_mst_edges(points);\n    std::sort(candidates.begin(), candidates.end(),\
    \ [](const auto& a, const auto& b) { return a.cost < b.cost; });\n\n    m1une::ds::Dsu\
    \ dsu(int(points.size()));\n    ManhattanMst<W> result;\n    result.cost = W(0);\n\
    \    result.edges.reserve(points.empty() ? 0 : points.size() - 1);\n    for (const\
    \ auto& edge : candidates) {\n        if (dsu.same(edge.from, edge.to)) continue;\n\
    \        dsu.merge(edge.from, edge.to);\n        result.cost += edge.cost;\n \
    \       result.edges.push_back(edge);\n        if (result.edges.size() + 1 ==\
    \ points.size()) break;\n    }\n    assert(points.empty() || result.edges.size()\
    \ + 1 == points.size());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_MANHATTAN_MST_HPP\n#define M1UNE_GEOMETRY_MANHATTAN_MST_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <limits>\n#include <map>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n#include \"../ds/dsu/dsu.hpp\"\n#include \"point.hpp\"\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <class T>\nstruct ManhattanMstEdge {\n    int\
    \ from;\n    int to;\n    T cost;\n};\n\ntemplate <class T>\nstruct ManhattanMst\
    \ {\n    T cost;\n    std::vector<ManhattanMstEdge<T>> edges;\n};\n\n// Returns\
    \ O(n) edges containing a Manhattan minimum spanning tree.\ntemplate <std::integral\
    \ T>\nstd::vector<ManhattanMstEdge<wide_type<T>>> manhattan_mst_edges(const std::vector<Point<T>>&\
    \ points) {\n    using W = wide_type<T>;\n    assert(points.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \    int n = int(points.size());\n    std::vector<Point<W>> transformed;\n   \
    \ transformed.reserve(points.size());\n    for (const auto& point : points) {\n\
    \        transformed.emplace_back(W(point.x), W(point.y));\n    }\n\n    std::vector<int>\
    \ order(n);\n    std::iota(order.begin(), order.end(), 0);\n    std::vector<ManhattanMstEdge<W>>\
    \ edges;\n    edges.reserve(std::size_t(4) * points.size());\n\n    for (int direction\
    \ = 0; direction < 4; direction++) {\n        std::sort(order.begin(), order.end(),\
    \ [&transformed](int i, int j) {\n            W first = transformed[i].x + transformed[i].y;\n\
    \            W second = transformed[j].x + transformed[j].y;\n            if (first\
    \ != second) return first < second;\n            if (transformed[i].x != transformed[j].x)\
    \ {\n                return transformed[i].x < transformed[j].x;\n           \
    \ }\n            return i < j;\n        });\n\n        std::map<W, int> sweep;\n\
    \        for (int i : order) {\n            auto it = sweep.lower_bound(-transformed[i].y);\n\
    \            while (it != sweep.end()) {\n                int j = it->second;\n\
    \                if (transformed[i].x - transformed[j].x < transformed[i].y -\
    \ transformed[j].y) {\n                    break;\n                }\n\n     \
    \           W dx = W(points[i].x) - W(points[j].x);\n                W dy = W(points[i].y)\
    \ - W(points[j].y);\n                if (dx < 0) dx = -dx;\n                if\
    \ (dy < 0) dy = -dy;\n                edges.push_back(ManhattanMstEdge<W>{i, j,\
    \ dx + dy});\n                it = sweep.erase(it);\n            }\n         \
    \   sweep[-transformed[i].y] = i;\n        }\n\n        for (auto& point : transformed)\
    \ {\n            if (direction & 1) {\n                point.x = -point.x;\n \
    \           } else {\n                std::swap(point.x, point.y);\n         \
    \   }\n        }\n    }\n    return edges;\n}\n\n// Returns a Manhattan minimum\
    \ spanning tree.\ntemplate <std::integral T>\nManhattanMst<wide_type<T>> manhattan_mst(const\
    \ std::vector<Point<T>>& points) {\n    using W = wide_type<T>;\n    auto candidates\
    \ = manhattan_mst_edges(points);\n    std::sort(candidates.begin(), candidates.end(),\
    \ [](const auto& a, const auto& b) { return a.cost < b.cost; });\n\n    m1une::ds::Dsu\
    \ dsu(int(points.size()));\n    ManhattanMst<W> result;\n    result.cost = W(0);\n\
    \    result.edges.reserve(points.empty() ? 0 : points.size() - 1);\n    for (const\
    \ auto& edge : candidates) {\n        if (dsu.same(edge.from, edge.to)) continue;\n\
    \        dsu.merge(edge.from, edge.to);\n        result.cost += edge.cost;\n \
    \       result.edges.push_back(edge);\n        if (result.edges.size() + 1 ==\
    \ points.size()) break;\n    }\n    assert(points.empty() || result.edges.size()\
    \ + 1 == points.size());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_MANHATTAN_MST_HPP\n"
  dependsOn:
  - ds/dsu/dsu.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/manhattan_mst.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-06-23 01:30:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/manhattan_mst.test.cpp
documentation_of: geometry/manhattan_mst.hpp
layout: document
title: Manhattan Minimum Spanning Tree
---

## Overview

This header constructs a minimum spanning tree of two-dimensional integral
points under Manhattan distance:

$$
d(i,j)=|x_i-x_j|+|y_i-y_j|.
$$

It uses four coordinate sweeps to generate only $O(N)$ candidate edges, then
applies Kruskal's algorithm.

## Types

```cpp
template <class T>
struct ManhattanMstEdge {
    int from;
    int to;
    T cost;
};

template <class T>
struct ManhattanMst {
    T cost;
    std::vector<ManhattanMstEdge<T>> edges;
};
```

For integral input coordinates, the result uses `wide_type<T>`, which is
`__int128_t`. This prevents overflow during coordinate transformations and
distance calculations when the input type is a standard integer type.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `manhattan_mst_edges(points)` | Returns $O(N)$ candidate edges containing at least one Manhattan MST. | $O(N\log N)$ |
| `manhattan_mst(points)` | Returns the MST cost and its selected edges. | $O(N\log N)$ |

Vertices are identified by their indices in `points`. Duplicate points are
supported and may be joined by zero-cost edges. For zero or one point, the
result has cost zero and no edges.

## Example

```cpp
#include "geometry/manhattan_mst.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(2, 1);
    points.emplace_back(-1, 3);

    auto mst = m1une::geometry::manhattan_mst(points);
    long long cost = static_cast<long long>(mst.cost);
    std::cout << cost << "\n";
}
```
