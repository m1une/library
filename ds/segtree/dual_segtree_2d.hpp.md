---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dual_segtree_2d.test.cpp
    title: verify/ds/segtree/dual_segtree_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/dual_segtree_2d.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/dual_segtree_2d.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A static compressed 2D dual segment\
    \ tree.\n// It supports rectangle monoid updates and point queries on registered\
    \ points.\n// Monoid::op must be commutative.\ntemplate <class Monoid, class X\
    \ = int, class Y = X>\nrequires m1une::monoid::IsMonoid<Monoid>\nstruct DualSegtree2D\
    \ {\n    using T = typename Monoid::value_type;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\nprivate:\n    int\
    \ _n;\n    int _size;\n    int _point_count;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _lazy;\n    std::vector<std::vector<T>>\
    \ _values;\n\n    static std::vector<point_type> normalize_points(std::vector<point_type>\
    \ points) {\n        std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    int x_index(const\
    \ X& x) const {\n        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);\n\
    \        if (it == _xs.end() || *it != x) return -1;\n        return int(it -\
    \ _xs.begin());\n    }\n\n    int y_index(int node, const Y& y) const {\n    \
    \    const auto& ys = _ys[node];\n        auto it = std::lower_bound(ys.begin(),\
    \ ys.end(), y);\n        if (it == ys.end() || *it != y) return -1;\n        return\
    \ int(it - ys.begin());\n    }\n\n    void apply_y(int node, const Y& lower, const\
    \ Y& upper, const T& value) {\n        const auto& ys = _ys[node];\n        if\
    \ (ys.empty()) return;\n        int left = int(std::lower_bound(ys.begin(), ys.end(),\
    \ lower) - ys.begin());\n        int right = int(std::lower_bound(ys.begin(),\
    \ ys.end(), upper) - ys.begin());\n        int size = int(ys.size());\n      \
    \  left += size;\n        right += size;\n        while (left < right) {\n   \
    \         if (left & 1) {\n                _lazy[node][left] = Monoid::op(value,\
    \ _lazy[node][left]);\n                left++;\n            }\n            if\
    \ (right & 1) {\n                --right;\n                _lazy[node][right]\
    \ = Monoid::op(value, _lazy[node][right]);\n            }\n            left >>=\
    \ 1;\n            right >>= 1;\n        }\n    }\n\n    T get_y(int node, const\
    \ Y& y) const {\n        int position = y_index(node, y);\n        assert(position\
    \ != -1);\n        int size = int(_ys[node].size());\n        T result = Monoid::id();\n\
    \        for (int index = size + position; index; index >>= 1) {\n           \
    \ result = Monoid::op(_lazy[node][index], result);\n        }\n        return\
    \ result;\n    }\n\npublic:\n    DualSegtree2D()\n        : _n(0), _size(1), _point_count(0),\
    \ _ys(2), _lazy(2) {}\n\n    explicit DualSegtree2D(const std::vector<point_type>&\
    \ points) {\n        build(points);\n    }\n\n    explicit DualSegtree2D(std::vector<point_type>&&\
    \ points) {\n        build(std::move(points));\n    }\n\n    explicit DualSegtree2D(const\
    \ std::vector<weighted_point_type>& points) {\n        std::vector<point_type>\
    \ coordinates;\n        coordinates.reserve(points.size());\n        for (const\
    \ auto& [x, y, value] : points) {\n            (void)value;\n            coordinates.emplace_back(x,\
    \ y);\n        }\n        build(std::move(coordinates));\n        for (const auto&\
    \ [x, y, value] : points) apply(x, y, value);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        points = normalize_points(std::move(points));\n        _point_count\
    \ = int(points.size());\n\n        _xs.clear();\n        _xs.reserve(points.size());\n\
    \        for (const auto& [x, y] : points) {\n            (void)y;\n         \
    \   if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n        }\n\n     \
    \   _n = int(_xs.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)std::max(1, _n)));\n        _ys.assign(2 * _size, {});\n        _lazy.assign(2\
    \ * _size, {});\n\n        for (const auto& [x, y] : points) {\n            int\
    \ x_position =\n                int(std::lower_bound(_xs.begin(), _xs.end(), x)\
    \ - _xs.begin());\n            for (int node = x_position + _size; node; node\
    \ >>= 1) {\n                _ys[node].push_back(y);\n            }\n        }\n\
    \n        for (int node = 1; node < 2 * _size; node++) {\n            auto& ys\
    \ = _ys[node];\n            std::sort(ys.begin(), ys.end());\n            ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n            _lazy[node].assign(2 * ys.size(), Monoid::id());\n\
    \        }\n\n        _values.resize(_n);\n        for (int x_position = 0; x_position\
    \ < _n; x_position++) {\n            _values[x_position].assign(_ys[x_position\
    \ + _size].size(), Monoid::id());\n        }\n    }\n\n    int size() const {\n\
    \        return _point_count;\n    }\n\n    bool empty() const {\n        return\
    \ _point_count == 0;\n    }\n\n    int x_size() const {\n        return _n;\n\
    \    }\n\n    const std::vector<X>& xs() const {\n        return _xs;\n    }\n\
    \n    bool contains_point(const X& x, const Y& y) const {\n        int x_position\
    \ = x_index(x);\n        if (x_position == -1) return false;\n        return y_index(x_position\
    \ + _size, y) != -1;\n    }\n\n    void apply(const X& x, const Y& y, const T&\
    \ value) {\n        int x_position = x_index(x);\n        assert(x_position !=\
    \ -1);\n        int y_position = y_index(x_position + _size, y);\n        assert(y_position\
    \ != -1);\n        _values[x_position][y_position] =\n            Monoid::op(value,\
    \ _values[x_position][y_position]);\n    }\n\n    void apply(const X& x_lower,\
    \ const X& x_upper, const Y& y_lower,\n               const Y& y_upper, const\
    \ T& value) {\n        assert(x_lower <= x_upper);\n        assert(y_lower <=\
    \ y_upper);\n        if (x_lower == x_upper || y_lower == y_upper || empty())\
    \ return;\n\n        int left = int(std::lower_bound(_xs.begin(), _xs.end(), x_lower)\
    \ - _xs.begin());\n        int right = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ x_upper) - _xs.begin());\n        left += _size;\n        right += _size;\n\
    \        while (left < right) {\n            if (left & 1) apply_y(left++, y_lower,\
    \ y_upper, value);\n            if (right & 1) apply_y(--right, y_lower, y_upper,\
    \ value);\n            left >>= 1;\n            right >>= 1;\n        }\n    }\n\
    \n    T get(const X& x, const Y& y) const {\n        int x_position = x_index(x);\n\
    \        if (x_position == -1) return Monoid::id();\n        int leaf = x_position\
    \ + _size;\n        int y_position = y_index(leaf, y);\n        if (y_position\
    \ == -1) return Monoid::id();\n\n        T result = _values[x_position][y_position];\n\
    \        for (int node = leaf; node; node >>= 1) {\n            result = Monoid::op(get_y(node,\
    \ y), result);\n        }\n        return result;\n    }\n\n    T operator()(const\
    \ X& x, const Y& y) const {\n        return get(x, y);\n    }\n\n    std::vector<weighted_point_type>\
    \ to_vector() const {\n        std::vector<weighted_point_type> result;\n    \
    \    result.reserve(_point_count);\n        for (int x_position = 0; x_position\
    \ < _n; x_position++) {\n            int leaf = x_position + _size;\n        \
    \    for (const Y& y : _ys[leaf]) {\n                result.emplace_back(_xs[x_position],\
    \ y, get(_xs[x_position], y));\n            }\n        }\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DUAL_SEGTREE_2D_HPP\n#define M1UNE_DUAL_SEGTREE_2D_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../math/bit_ceil.hpp\"\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A static compressed 2D dual segment\
    \ tree.\n// It supports rectangle monoid updates and point queries on registered\
    \ points.\n// Monoid::op must be commutative.\ntemplate <class Monoid, class X\
    \ = int, class Y = X>\nrequires m1une::monoid::IsMonoid<Monoid>\nstruct DualSegtree2D\
    \ {\n    using T = typename Monoid::value_type;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\nprivate:\n    int\
    \ _n;\n    int _size;\n    int _point_count;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _lazy;\n    std::vector<std::vector<T>>\
    \ _values;\n\n    static std::vector<point_type> normalize_points(std::vector<point_type>\
    \ points) {\n        std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    int x_index(const\
    \ X& x) const {\n        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);\n\
    \        if (it == _xs.end() || *it != x) return -1;\n        return int(it -\
    \ _xs.begin());\n    }\n\n    int y_index(int node, const Y& y) const {\n    \
    \    const auto& ys = _ys[node];\n        auto it = std::lower_bound(ys.begin(),\
    \ ys.end(), y);\n        if (it == ys.end() || *it != y) return -1;\n        return\
    \ int(it - ys.begin());\n    }\n\n    void apply_y(int node, const Y& lower, const\
    \ Y& upper, const T& value) {\n        const auto& ys = _ys[node];\n        if\
    \ (ys.empty()) return;\n        int left = int(std::lower_bound(ys.begin(), ys.end(),\
    \ lower) - ys.begin());\n        int right = int(std::lower_bound(ys.begin(),\
    \ ys.end(), upper) - ys.begin());\n        int size = int(ys.size());\n      \
    \  left += size;\n        right += size;\n        while (left < right) {\n   \
    \         if (left & 1) {\n                _lazy[node][left] = Monoid::op(value,\
    \ _lazy[node][left]);\n                left++;\n            }\n            if\
    \ (right & 1) {\n                --right;\n                _lazy[node][right]\
    \ = Monoid::op(value, _lazy[node][right]);\n            }\n            left >>=\
    \ 1;\n            right >>= 1;\n        }\n    }\n\n    T get_y(int node, const\
    \ Y& y) const {\n        int position = y_index(node, y);\n        assert(position\
    \ != -1);\n        int size = int(_ys[node].size());\n        T result = Monoid::id();\n\
    \        for (int index = size + position; index; index >>= 1) {\n           \
    \ result = Monoid::op(_lazy[node][index], result);\n        }\n        return\
    \ result;\n    }\n\npublic:\n    DualSegtree2D()\n        : _n(0), _size(1), _point_count(0),\
    \ _ys(2), _lazy(2) {}\n\n    explicit DualSegtree2D(const std::vector<point_type>&\
    \ points) {\n        build(points);\n    }\n\n    explicit DualSegtree2D(std::vector<point_type>&&\
    \ points) {\n        build(std::move(points));\n    }\n\n    explicit DualSegtree2D(const\
    \ std::vector<weighted_point_type>& points) {\n        std::vector<point_type>\
    \ coordinates;\n        coordinates.reserve(points.size());\n        for (const\
    \ auto& [x, y, value] : points) {\n            (void)value;\n            coordinates.emplace_back(x,\
    \ y);\n        }\n        build(std::move(coordinates));\n        for (const auto&\
    \ [x, y, value] : points) apply(x, y, value);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        points = normalize_points(std::move(points));\n        _point_count\
    \ = int(points.size());\n\n        _xs.clear();\n        _xs.reserve(points.size());\n\
    \        for (const auto& [x, y] : points) {\n            (void)y;\n         \
    \   if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n        }\n\n     \
    \   _n = int(_xs.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)std::max(1, _n)));\n        _ys.assign(2 * _size, {});\n        _lazy.assign(2\
    \ * _size, {});\n\n        for (const auto& [x, y] : points) {\n            int\
    \ x_position =\n                int(std::lower_bound(_xs.begin(), _xs.end(), x)\
    \ - _xs.begin());\n            for (int node = x_position + _size; node; node\
    \ >>= 1) {\n                _ys[node].push_back(y);\n            }\n        }\n\
    \n        for (int node = 1; node < 2 * _size; node++) {\n            auto& ys\
    \ = _ys[node];\n            std::sort(ys.begin(), ys.end());\n            ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n            _lazy[node].assign(2 * ys.size(), Monoid::id());\n\
    \        }\n\n        _values.resize(_n);\n        for (int x_position = 0; x_position\
    \ < _n; x_position++) {\n            _values[x_position].assign(_ys[x_position\
    \ + _size].size(), Monoid::id());\n        }\n    }\n\n    int size() const {\n\
    \        return _point_count;\n    }\n\n    bool empty() const {\n        return\
    \ _point_count == 0;\n    }\n\n    int x_size() const {\n        return _n;\n\
    \    }\n\n    const std::vector<X>& xs() const {\n        return _xs;\n    }\n\
    \n    bool contains_point(const X& x, const Y& y) const {\n        int x_position\
    \ = x_index(x);\n        if (x_position == -1) return false;\n        return y_index(x_position\
    \ + _size, y) != -1;\n    }\n\n    void apply(const X& x, const Y& y, const T&\
    \ value) {\n        int x_position = x_index(x);\n        assert(x_position !=\
    \ -1);\n        int y_position = y_index(x_position + _size, y);\n        assert(y_position\
    \ != -1);\n        _values[x_position][y_position] =\n            Monoid::op(value,\
    \ _values[x_position][y_position]);\n    }\n\n    void apply(const X& x_lower,\
    \ const X& x_upper, const Y& y_lower,\n               const Y& y_upper, const\
    \ T& value) {\n        assert(x_lower <= x_upper);\n        assert(y_lower <=\
    \ y_upper);\n        if (x_lower == x_upper || y_lower == y_upper || empty())\
    \ return;\n\n        int left = int(std::lower_bound(_xs.begin(), _xs.end(), x_lower)\
    \ - _xs.begin());\n        int right = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ x_upper) - _xs.begin());\n        left += _size;\n        right += _size;\n\
    \        while (left < right) {\n            if (left & 1) apply_y(left++, y_lower,\
    \ y_upper, value);\n            if (right & 1) apply_y(--right, y_lower, y_upper,\
    \ value);\n            left >>= 1;\n            right >>= 1;\n        }\n    }\n\
    \n    T get(const X& x, const Y& y) const {\n        int x_position = x_index(x);\n\
    \        if (x_position == -1) return Monoid::id();\n        int leaf = x_position\
    \ + _size;\n        int y_position = y_index(leaf, y);\n        if (y_position\
    \ == -1) return Monoid::id();\n\n        T result = _values[x_position][y_position];\n\
    \        for (int node = leaf; node; node >>= 1) {\n            result = Monoid::op(get_y(node,\
    \ y), result);\n        }\n        return result;\n    }\n\n    T operator()(const\
    \ X& x, const Y& y) const {\n        return get(x, y);\n    }\n\n    std::vector<weighted_point_type>\
    \ to_vector() const {\n        std::vector<weighted_point_type> result;\n    \
    \    result.reserve(_point_count);\n        for (int x_position = 0; x_position\
    \ < _n; x_position++) {\n            int leaf = x_position + _size;\n        \
    \    for (const Y& y : _ys[leaf]) {\n                result.emplace_back(_xs[x_position],\
    \ y, get(_xs[x_position], y));\n            }\n        }\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DUAL_SEGTREE_2D_HPP\n"
  dependsOn:
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/dual_segtree_2d.hpp
  requiredBy: []
  timestamp: '2026-07-01 22:04:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dual_segtree_2d.test.cpp
documentation_of: ds/segtree/dual_segtree_2d.hpp
layout: document
title: Dual Segtree 2D
---

## Overview

`DualSegtree2D` is a static compressed two-dimensional dual segment tree. It
applies a monoid value to every registered point in a half-open rectangle and
answers the current value of one registered point.

Use it when all point-query coordinates are known before processing updates.
Rectangle boundaries do not need to be registered.

## Requirements

```cpp
template <class Monoid, class X = int, class Y = X>
struct DualSegtree2D;
```

`Monoid` must satisfy `m1une::monoid::IsMonoid`, and its operation must be
commutative. Commutativity is necessary because one rectangle update is stored
in independently compressed x- and y-segment nodes whose values are combined
later at a point query.

`X` and `Y` must be ordered coordinate types. Rectangles use
`[x_lower, x_upper) x [y_lower, y_upper)`.

## Construction

```cpp
DualSegtree2D();
explicit DualSegtree2D(const std::vector<std::pair<X, Y>>& points);
explicit DualSegtree2D(std::vector<std::pair<X, Y>>&& points);
explicit DualSegtree2D(const std::vector<std::tuple<X, Y, T>>& points);
void build(std::vector<std::pair<X, Y>> points);
```

Coordinate constructors initialize every distinct point with `Monoid::id()`.
The weighted constructor combines values at duplicate coordinates with
`Monoid::op`. `build` discards all previous points, values, and updates.

Construction takes $O(N\log^2 N)$ time and $O(N\log N)$ memory.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of distinct registered points. | $O(1)$ |
| `bool empty() const` | Returns whether no point is registered. | $O(1)$ |
| `int x_size() const` | Returns the number of distinct registered x-coordinates. | $O(1)$ |
| `const std::vector<X>& xs() const` | Returns the sorted compressed x-coordinates. | $O(1)$ |
| `bool contains_point(const X& x, const Y& y) const` | Tests whether a point is registered. | $O(\log N)$ |
| `void apply(const X& x, const Y& y, const T& value)` | Applies `value` to one registered point. | $O(\log N)$ |
| `void apply(const X& xl, const X& xr, const Y& yl, const Y& yr, const T& value)` | Applies `value` to every registered point in the rectangle. | $O(\log^2 N)$ |
| `T get(const X& x, const Y& y) const` | Returns a point value, or `Monoid::id()` when unregistered. | $O(\log^2 N)$ |
| `T operator()(const X& x, const Y& y) const` | Alias of `get(x, y)`. | $O(\log^2 N)$ |
| `std::vector<std::tuple<X, Y, T>> to_vector() const` | Returns all registered points and values in coordinate order. | $O(N\log^2 N)$ |

For both `apply` overloads, a stored value `current` becomes
`Monoid::op(value, current)`.

## Example

```cpp
#include "ds/segtree/dual_segtree_2d.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <utility>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    std::vector<std::pair<int, int>> points = {
        {1, 2},
        {3, 4},
        {5, 1},
    };
    m1une::ds::DualSegtree2D<Add> seg(points);

    seg.apply(0, 4, 0, 5, 10);
    seg.apply(3, 4, 7);

    std::cout << seg.get(1, 2) << "\n"; // 10
    std::cout << seg.get(3, 4) << "\n"; // 17
    std::cout << seg.get(5, 1) << "\n"; // 0
}
```
