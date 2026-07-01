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
    path: verify/ds/segtree/segtree_2d.test.cpp
    title: verify/ds/segtree/segtree_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/segtree_2d.hpp\"\n\n\n\n#include <algorithm>\n\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/segtree_2d.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A static compressed 2D segment tree.\n\
    // It supports point assignment on registered points and rectangle product queries.\n\
    //\n// The query rectangle is [xl, xr) x [yl, yr).\n// All points that may be\
    \ updated must be registered before construction.\ntemplate <class Monoid, class\
    \ X = int, class Y = X>\nrequires m1une::monoid::IsMonoid<Monoid>\nstruct Segtree2D\
    \ {\n    using T = typename Monoid::value_type;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\nprivate:\n    int\
    \ _n;\n    int _size;\n    int _point_count;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _d;\n\n    static std::vector<point_type>\
    \ normalize_points(std::vector<point_type> points) {\n        std::sort(points.begin(),\
    \ points.end());\n        points.erase(std::unique(points.begin(), points.end()),\
    \ points.end());\n        return points;\n    }\n\n    int x_index(const X& x)\
    \ const {\n        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);\n  \
    \      if (it == _xs.end() || *it != x) return -1;\n        return int(it - _xs.begin());\n\
    \    }\n\n    int y_index(int k, const Y& y) const {\n        const auto& ys =\
    \ _ys[k];\n        auto it = std::lower_bound(ys.begin(), ys.end(), y);\n    \
    \    if (it == ys.end() || *it != y) return -1;\n        return int(it - ys.begin());\n\
    \    }\n\n    T get_exact(int k, const Y& y) const {\n        int pos = y_index(k,\
    \ y);\n        if (pos == -1) return Monoid::id();\n        int m = int(_ys[k].size());\n\
    \        return _d[k][m + pos];\n    }\n\n    void set_exact(int k, const Y& y,\
    \ T x) {\n        int pos = y_index(k, y);\n        assert(pos != -1);\n\n   \
    \     int m = int(_ys[k].size());\n        int p = m + pos;\n\n        _d[k][p]\
    \ = std::move(x);\n        while (1 < p) {\n            p >>= 1;\n           \
    \ _d[k][p] = Monoid::op(_d[k][2 * p], _d[k][2 * p + 1]);\n        }\n    }\n\n\
    \    T prod_y(int k, const Y& yl, const Y& yr) const {\n        assert(yl <= yr);\n\
    \        if (yl == yr || _ys[k].empty()) return Monoid::id();\n\n        const\
    \ auto& ys = _ys[k];\n        int l = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yl) - ys.begin());\n        int r = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yr) - ys.begin());\n\n        int m = int(ys.size());\n        l += m;\n   \
    \     r += m;\n\n        T sml = Monoid::id();\n        T smr = Monoid::id();\n\
    \n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _d[k][l++]);\n\
    \            if (r & 1) smr = Monoid::op(_d[k][--r], smr);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\npublic:\n    Segtree2D() : _n(0), _size(1), _point_count(0), _ys(2),\
    \ _d(2) {}\n\n    explicit Segtree2D(const std::vector<point_type>& points) {\n\
    \        build(points);\n    }\n\n    explicit Segtree2D(std::vector<point_type>&&\
    \ points) {\n        build(std::move(points));\n    }\n\n    explicit Segtree2D(const\
    \ std::vector<weighted_point_type>& points) {\n        std::vector<point_type>\
    \ coords;\n        coords.reserve(points.size());\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            (void)value;\n            coords.emplace_back(x,\
    \ y);\n        }\n\n        build(std::move(coords));\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            set(x, y, value);\n        }\n    }\n\
    \n    void build(std::vector<point_type> points) {\n        points = normalize_points(std::move(points));\n\
    \n        _point_count = int(points.size());\n\n        _xs.clear();\n       \
    \ _xs.reserve(points.size());\n\n        for (const auto& [x, y] : points) {\n\
    \            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        _n = int(_xs.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)std::max(1, _n)));\n\n        _ys.assign(2 * _size, {});\n        _d.assign(2\
    \ * _size, {});\n\n        for (const auto& [x, y] : points) {\n            int\
    \ xi = int(std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin());\n     \
    \       for (int k = xi + _size; k; k >>= 1) {\n                _ys[k].push_back(y);\n\
    \            }\n        }\n\n        for (int k = 1; k < 2 * _size; k++) {\n \
    \           auto& ys = _ys[k];\n            std::sort(ys.begin(), ys.end());\n\
    \            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n        \
    \    _d[k].assign(2 * ys.size(), Monoid::id());\n        }\n    }\n\n    int size()\
    \ const {\n        return _point_count;\n    }\n\n    bool empty() const {\n \
    \       return _point_count == 0;\n    }\n\n    int x_size() const {\n       \
    \ return _n;\n    }\n\n    const std::vector<X>& xs() const {\n        return\
    \ _xs;\n    }\n\n    bool contains_point(const X& x, const Y& y) const {\n   \
    \     int xi = x_index(x);\n        if (xi == -1) return false;\n        return\
    \ y_index(xi + _size, y) != -1;\n    }\n\n    void set(const X& x, const Y& y,\
    \ T value) {\n        int xi = x_index(x);\n        assert(xi != -1);\n      \
    \  assert(y_index(xi + _size, y) != -1);\n\n        int k = xi + _size;\n    \
    \    set_exact(k, y, std::move(value));\n\n        while (1 < k) {\n         \
    \   k >>= 1;\n            set_exact(k, y, Monoid::op(get_exact(2 * k, y), get_exact(2\
    \ * k + 1, y)));\n        }\n    }\n\n    T get(const X& x, const Y& y) const\
    \ {\n        int xi = x_index(x);\n        if (xi == -1) return Monoid::id();\n\
    \        return get_exact(xi + _size, y);\n    }\n\n    T operator()(const X&\
    \ x, const Y& y) const {\n        return get(x, y);\n    }\n\n    T prod(const\
    \ X& xl, const X& xr, const Y& yl, const Y& yr) const {\n        assert(xl <=\
    \ xr);\n        assert(yl <= yr);\n\n        if (xl == xr || yl == yr || empty())\
    \ return Monoid::id();\n\n        int l = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xl) - _xs.begin());\n        int r = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xr) - _xs.begin());\n\n        l += _size;\n        r += _size;\n\n        T\
    \ sml = Monoid::id();\n        T smr = Monoid::id();\n\n        while (l < r)\
    \ {\n            if (l & 1) sml = Monoid::op(sml, prod_y(l++, yl, yr));\n    \
    \        if (r & 1) smr = Monoid::op(prod_y(--r, yl, yr), smr);\n            l\
    \ >>= 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\n    T all_prod() const {\n        if (empty() || _d[1].empty()) return\
    \ Monoid::id();\n        return _d[1][1];\n    }\n\n    std::vector<weighted_point_type>\
    \ to_vector() const {\n        std::vector<weighted_point_type> res;\n       \
    \ res.reserve(_point_count);\n\n        for (int xi = 0; xi < _n; xi++) {\n  \
    \          int k = xi + _size;\n            int m = int(_ys[k].size());\n\n  \
    \          for (int j = 0; j < m; j++) {\n                res.emplace_back(_xs[xi],\
    \ _ys[k][j], _d[k][m + j]);\n            }\n        }\n\n        return res;\n\
    \    }\n};\n\n} // namespace ds\n} // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEGTREE_2D_HPP\n#define M1UNE_SEGTREE_2D_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../../math/bit_ceil.hpp\"\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A static compressed 2D segment tree.\n\
    // It supports point assignment on registered points and rectangle product queries.\n\
    //\n// The query rectangle is [xl, xr) x [yl, yr).\n// All points that may be\
    \ updated must be registered before construction.\ntemplate <class Monoid, class\
    \ X = int, class Y = X>\nrequires m1une::monoid::IsMonoid<Monoid>\nstruct Segtree2D\
    \ {\n    using T = typename Monoid::value_type;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\nprivate:\n    int\
    \ _n;\n    int _size;\n    int _point_count;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _d;\n\n    static std::vector<point_type>\
    \ normalize_points(std::vector<point_type> points) {\n        std::sort(points.begin(),\
    \ points.end());\n        points.erase(std::unique(points.begin(), points.end()),\
    \ points.end());\n        return points;\n    }\n\n    int x_index(const X& x)\
    \ const {\n        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);\n  \
    \      if (it == _xs.end() || *it != x) return -1;\n        return int(it - _xs.begin());\n\
    \    }\n\n    int y_index(int k, const Y& y) const {\n        const auto& ys =\
    \ _ys[k];\n        auto it = std::lower_bound(ys.begin(), ys.end(), y);\n    \
    \    if (it == ys.end() || *it != y) return -1;\n        return int(it - ys.begin());\n\
    \    }\n\n    T get_exact(int k, const Y& y) const {\n        int pos = y_index(k,\
    \ y);\n        if (pos == -1) return Monoid::id();\n        int m = int(_ys[k].size());\n\
    \        return _d[k][m + pos];\n    }\n\n    void set_exact(int k, const Y& y,\
    \ T x) {\n        int pos = y_index(k, y);\n        assert(pos != -1);\n\n   \
    \     int m = int(_ys[k].size());\n        int p = m + pos;\n\n        _d[k][p]\
    \ = std::move(x);\n        while (1 < p) {\n            p >>= 1;\n           \
    \ _d[k][p] = Monoid::op(_d[k][2 * p], _d[k][2 * p + 1]);\n        }\n    }\n\n\
    \    T prod_y(int k, const Y& yl, const Y& yr) const {\n        assert(yl <= yr);\n\
    \        if (yl == yr || _ys[k].empty()) return Monoid::id();\n\n        const\
    \ auto& ys = _ys[k];\n        int l = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yl) - ys.begin());\n        int r = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yr) - ys.begin());\n\n        int m = int(ys.size());\n        l += m;\n   \
    \     r += m;\n\n        T sml = Monoid::id();\n        T smr = Monoid::id();\n\
    \n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _d[k][l++]);\n\
    \            if (r & 1) smr = Monoid::op(_d[k][--r], smr);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\npublic:\n    Segtree2D() : _n(0), _size(1), _point_count(0), _ys(2),\
    \ _d(2) {}\n\n    explicit Segtree2D(const std::vector<point_type>& points) {\n\
    \        build(points);\n    }\n\n    explicit Segtree2D(std::vector<point_type>&&\
    \ points) {\n        build(std::move(points));\n    }\n\n    explicit Segtree2D(const\
    \ std::vector<weighted_point_type>& points) {\n        std::vector<point_type>\
    \ coords;\n        coords.reserve(points.size());\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            (void)value;\n            coords.emplace_back(x,\
    \ y);\n        }\n\n        build(std::move(coords));\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            set(x, y, value);\n        }\n    }\n\
    \n    void build(std::vector<point_type> points) {\n        points = normalize_points(std::move(points));\n\
    \n        _point_count = int(points.size());\n\n        _xs.clear();\n       \
    \ _xs.reserve(points.size());\n\n        for (const auto& [x, y] : points) {\n\
    \            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        _n = int(_xs.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)std::max(1, _n)));\n\n        _ys.assign(2 * _size, {});\n        _d.assign(2\
    \ * _size, {});\n\n        for (const auto& [x, y] : points) {\n            int\
    \ xi = int(std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin());\n     \
    \       for (int k = xi + _size; k; k >>= 1) {\n                _ys[k].push_back(y);\n\
    \            }\n        }\n\n        for (int k = 1; k < 2 * _size; k++) {\n \
    \           auto& ys = _ys[k];\n            std::sort(ys.begin(), ys.end());\n\
    \            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n        \
    \    _d[k].assign(2 * ys.size(), Monoid::id());\n        }\n    }\n\n    int size()\
    \ const {\n        return _point_count;\n    }\n\n    bool empty() const {\n \
    \       return _point_count == 0;\n    }\n\n    int x_size() const {\n       \
    \ return _n;\n    }\n\n    const std::vector<X>& xs() const {\n        return\
    \ _xs;\n    }\n\n    bool contains_point(const X& x, const Y& y) const {\n   \
    \     int xi = x_index(x);\n        if (xi == -1) return false;\n        return\
    \ y_index(xi + _size, y) != -1;\n    }\n\n    void set(const X& x, const Y& y,\
    \ T value) {\n        int xi = x_index(x);\n        assert(xi != -1);\n      \
    \  assert(y_index(xi + _size, y) != -1);\n\n        int k = xi + _size;\n    \
    \    set_exact(k, y, std::move(value));\n\n        while (1 < k) {\n         \
    \   k >>= 1;\n            set_exact(k, y, Monoid::op(get_exact(2 * k, y), get_exact(2\
    \ * k + 1, y)));\n        }\n    }\n\n    T get(const X& x, const Y& y) const\
    \ {\n        int xi = x_index(x);\n        if (xi == -1) return Monoid::id();\n\
    \        return get_exact(xi + _size, y);\n    }\n\n    T operator()(const X&\
    \ x, const Y& y) const {\n        return get(x, y);\n    }\n\n    T prod(const\
    \ X& xl, const X& xr, const Y& yl, const Y& yr) const {\n        assert(xl <=\
    \ xr);\n        assert(yl <= yr);\n\n        if (xl == xr || yl == yr || empty())\
    \ return Monoid::id();\n\n        int l = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xl) - _xs.begin());\n        int r = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xr) - _xs.begin());\n\n        l += _size;\n        r += _size;\n\n        T\
    \ sml = Monoid::id();\n        T smr = Monoid::id();\n\n        while (l < r)\
    \ {\n            if (l & 1) sml = Monoid::op(sml, prod_y(l++, yl, yr));\n    \
    \        if (r & 1) smr = Monoid::op(prod_y(--r, yl, yr), smr);\n            l\
    \ >>= 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\n    T all_prod() const {\n        if (empty() || _d[1].empty()) return\
    \ Monoid::id();\n        return _d[1][1];\n    }\n\n    std::vector<weighted_point_type>\
    \ to_vector() const {\n        std::vector<weighted_point_type> res;\n       \
    \ res.reserve(_point_count);\n\n        for (int xi = 0; xi < _n; xi++) {\n  \
    \          int k = xi + _size;\n            int m = int(_ys[k].size());\n\n  \
    \          for (int j = 0; j < m; j++) {\n                res.emplace_back(_xs[xi],\
    \ _ys[k][j], _d[k][m + j]);\n            }\n        }\n\n        return res;\n\
    \    }\n};\n\n} // namespace ds\n} // namespace m1une\n\n#endif // M1UNE_SEGTREE_2D_HPP\n"
  dependsOn:
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/segtree_2d.hpp
  requiredBy: []
  timestamp: '2026-06-21 13:49:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/segtree_2d.test.cpp
documentation_of: ds/segtree/segtree_2d.hpp
layout: document
title: Segtree 2D
---

## Overview

`m1une::ds::Segtree2D` is a static compressed two-dimensional segment tree.

It supports:

* point assignment on registered points
* point access
* rectangle product queries

The query rectangle is half-open:

[
[x_l, x_r) \times [y_l, y_r)
]

All points that may be updated must be registered before construction.

## Template Parameters

```cpp
template <class Monoid, class X = int, class Y = X>
struct Segtree2D;
```

* `Monoid`: the monoid used for aggregation.
* `X`: the type of x-coordinates.
* `Y`: the type of y-coordinates.

`Monoid` must satisfy `m1une::monoid::IsMonoid`.

The stored value type is:

```cpp
using T = typename Monoid::value_type;
```

## Coordinate Convention

This data structure is statically compressed.

That means every point `(x, y)` that may be updated must be given in the constructor or `build`.

For example, after constructing the data structure with points

```cpp
{(1, 2), (3, 4)}
```

you may call:

```cpp
seg.set(1, 2, value);
seg.set(3, 4, value);
```

but calling

```cpp
seg.set(5, 6, value);
```

is invalid.

## Construction

### Empty constructor

```cpp
Segtree2D()
```

Creates an empty data structure.

### From coordinates

```cpp
explicit Segtree2D(const std::vector<std::pair<X, Y>>& points)
explicit Segtree2D(std::vector<std::pair<X, Y>>&& points)
```

Creates a two-dimensional segment tree with the given registered points.

Duplicate points are removed automatically.

All values are initialized with `Monoid::id()`.

### From weighted points

```cpp
explicit Segtree2D(const std::vector<std::tuple<X, Y, T>>& points)
```

Creates a two-dimensional segment tree with the given weighted points.

Each tuple represents `(x, y, value)`.

If duplicate coordinates are given, the last `set` performed by the constructor determines the final value.

## Methods

Let:

* (N) be the number of registered distinct points
* (X_N) be the number of distinct x-coordinates
* (K_x) be the number of x-segment nodes visited by a query

Usually, (K_x = O(\log X_N)).

| Method                                                             | Description                                                                                 | Complexity      |
| ------------------------------------------------------------------ | ------------------------------------------------------------------------------------------- | --------------- |
| `void build(std::vector<std::pair<X, Y>> points)`                  | Rebuilds the data structure from registered points. All values are reset to `Monoid::id()`. | (O(N \log^2 N)) |
| `int size() const`                                                 | Returns the number of registered distinct points.                                           | (O(1))          |
| `bool empty() const`                                               | Returns whether no point is registered.                                                     | (O(1))          |
| `int x_size() const`                                               | Returns the number of distinct x-coordinates.                                               | (O(1))          |
| `const std::vector<X>& xs() const`                                 | Returns the compressed x-coordinates.                                                       | (O(1))          |
| `bool contains_point(const X& x, const Y& y) const`                | Returns whether `(x, y)` is registered.                                                     | (O(\log N))     |
| `void set(const X& x, const Y& y, T value)`                        | Assigns `value` to the registered point `(x, y)`. Requires that `(x, y)` is registered.     | (O(\log^2 N))   |
| `T get(const X& x, const Y& y) const`                              | Returns the value at `(x, y)`. If the point is not registered, returns `Monoid::id()`.      | (O(\log N))     |
| `T operator()(const X& x, const Y& y) const`                       | Alias of `get(x, y)`.                                                                       | (O(\log N))     |
| `T prod(const X& xl, const X& xr, const Y& yl, const Y& yr) const` | Returns the product over registered points inside `[xl, xr) x [yl, yr)`.                    | (O(\log^2 N))   |
| `T all_prod() const`                                               | Returns the product over all registered points.                                             | (O(1))          |
| `std::vector<std::tuple<X, Y, T>> to_vector() const`               | Returns all registered points with their current values.                                    | (O(N))          |

## Example

```cpp
#include "ds/segtree/segtree_2d.hpp"
#include "monoid/add.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;

    std::vector<std::pair<int, int>> points = {
        {1, 2},
        {1, 5},
        {3, 4},
        {7, 1},
    };

    m1une::ds::Segtree2D<Sum> seg(points);

    seg.set(1, 2, 10);
    seg.set(1, 5, 20);
    seg.set(3, 4, 30);
    seg.set(7, 1, 40);

    assert(seg.get(1, 2) == 10);
    assert(seg.get(2, 2) == 0);

    assert(seg.prod(0, 4, 0, 10) == 60);
    assert(seg.prod(1, 2, 0, 10) == 30);
    assert(seg.prod(0, 10, 0, 3) == 50);
    assert(seg.all_prod() == 100);

    return 0;
}
```

## Example: Static Rectangle Sum

This data structure can be used for static rectangle sum queries.

```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "../../../ds/segtree/segtree_2d.hpp"
#include "../../../monoid/add.hpp"

#include <iostream>
#include <tuple>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    using Sum = m1une::monoid::Add<long long>;

    std::vector<std::tuple<int, int, long long>> points;
    points.reserve(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        long long w;
        std::cin >> x >> y >> w;
        points.emplace_back(x, y, w);
    }

    m1une::ds::Segtree2D<Sum> seg(points);

    while (q--) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        std::cout << seg.prod(l, r, d, u) << '\n';
    }

    return 0;
}
```

## Notes

This data structure is designed for the following situation:

* all update positions are known in advance
* values are updated by point assignment
* queries are axis-aligned rectangle product queries

For point addition, use `get` and `set` together.

```cpp
auto current = seg.get(x, y);
seg.set(x, y, current + delta);
```

For rectangle updates and point queries, use
[`DualSegtree2D`](dual_segtree_2d.md).

Although the template only requires a monoid, rectangle aggregation is usually intended for commutative monoids such as sum, min, max, and gcd.
For non-commutative monoids, the result follows the internal traversal order and may not match a natural geometric interpretation.
