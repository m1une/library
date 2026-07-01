---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_2d.hpp
    title: Segtree 2D
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"verify/ds/segtree/segtree_2d.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line 1 \"ds/segtree/segtree_2d.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if\
    \ (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
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
    \    }\n};\n\n} // namespace ds\n} // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n\n  \
    \  // Returns the identity element for addition, which is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a + b;\n\
    \    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/segtree/segtree_2d.test.cpp\"\
    \n\n#line 8 \"verify/ds/segtree/segtree_2d.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#include <map>\n#include <random>\n#line 15 \"verify/ds/segtree/segtree_2d.test.cpp\"\
    \n\nusing Sum = m1une::monoid::Add<long long>;\n\nstruct Query {\n    int type;\n\
    \    int first;\n    int second;\n    int third;\n    int fourth;\n    long long\
    \ value;\n};\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    std::mt19937 random(314159265);\n\
    \    std::vector<std::pair<int, int>> points;\n    std::map<std::pair<int, int>,\
    \ long long> expected;\n    for (int i = 0; i < 40; i++) {\n        int x = int(random()\
    \ % 15) - 7;\n        int y = int(random() % 15) - 7;\n        points.emplace_back(x,\
    \ y);\n        expected[{x, y}] = 0;\n    }\n\n    m1une::ds::Segtree2D<Sum> seg(points);\n\
    \    assert(seg.size() == int(expected.size()));\n    assert(!seg.contains_point(100,\
    \ 100));\n    assert(seg.get(100, 100) == 0);\n\n    std::vector<std::pair<int,\
    \ int>> distinct_points;\n    for (const auto& [point, value] : expected) {\n\
    \        (void)value;\n        distinct_points.push_back(point);\n    }\n\n  \
    \  for (int operation = 0; operation < 1000; operation++) {\n        if (random()\
    \ % 3 == 0) {\n            auto point = distinct_points[random() % distinct_points.size()];\n\
    \            long long value = int(random() % 101) - 50;\n            seg.set(point.first,\
    \ point.second, value);\n            expected[point] = value;\n            assert(seg(point.first,\
    \ point.second) == value);\n        } else {\n            int x_lower = int(random()\
    \ % 19) - 9;\n            int x_upper = int(random() % 19) - 9;\n            int\
    \ y_lower = int(random() % 19) - 9;\n            int y_upper = int(random() %\
    \ 19) - 9;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n\n         \
    \   long long answer = 0;\n            for (const auto& [point, value] : expected)\
    \ {\n                if (x_lower <= point.first && point.first < x_upper &&\n\
    \                    y_lower <= point.second && point.second < y_upper) {\n  \
    \                  answer += value;\n                }\n            }\n      \
    \      assert(seg.prod(x_lower, x_upper, y_lower, y_upper) == answer);\n     \
    \   }\n    }\n\n    long long total = 0;\n    for (const auto& [point, value]\
    \ : expected) {\n        (void)point;\n        total += value;\n    }\n    assert(seg.all_prod()\
    \ == total);\n    auto values = seg.to_vector();\n    assert(values.size() ==\
    \ expected.size());\n    for (const auto& [x, y, value] : values) {\n        std::pair<int,\
    \ int> point(x, y);\n        assert(expected[point] == value);\n    }\n}\n#endif\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n#ifndef NDEBUG\n    randomized_test();\n#endif\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<std::tuple<int, int, long long>> initial(n);\n \
    \   std::vector<std::pair<int, int>> points;\n    points.reserve(n + q);\n   \
    \ for (auto& [x, y, weight] : initial) {\n        std::cin >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(q);\n\
    \    for (Query& query : queries) {\n        std::cin >> query.type;\n       \
    \ if (query.type == 0) {\n            std::cin >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            std::cin >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::Segtree2D<Sum> seg(std::move(points));\n    for (const\
    \ auto& [x, y, weight] : initial) {\n        seg.set(x, y, seg.get(x, y) + weight);\n\
    \    }\n\n    for (const Query& query : queries) {\n        if (query.type ==\
    \ 0) {\n            long long current = seg.get(query.first, query.second);\n\
    \            seg.set(query.first, query.second, current + query.value);\n    \
    \    } else {\n            std::cout << seg.prod(query.first, query.third, query.second,\
    \ query.fourth)\n                      << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../../ds/segtree/segtree_2d.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n\
    #include <map>\n#include <random>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nusing Sum = m1une::monoid::Add<long long>;\n\nstruct Query {\n \
    \   int type;\n    int first;\n    int second;\n    int third;\n    int fourth;\n\
    \    long long value;\n};\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    std::mt19937\
    \ random(314159265);\n    std::vector<std::pair<int, int>> points;\n    std::map<std::pair<int,\
    \ int>, long long> expected;\n    for (int i = 0; i < 40; i++) {\n        int\
    \ x = int(random() % 15) - 7;\n        int y = int(random() % 15) - 7;\n     \
    \   points.emplace_back(x, y);\n        expected[{x, y}] = 0;\n    }\n\n    m1une::ds::Segtree2D<Sum>\
    \ seg(points);\n    assert(seg.size() == int(expected.size()));\n    assert(!seg.contains_point(100,\
    \ 100));\n    assert(seg.get(100, 100) == 0);\n\n    std::vector<std::pair<int,\
    \ int>> distinct_points;\n    for (const auto& [point, value] : expected) {\n\
    \        (void)value;\n        distinct_points.push_back(point);\n    }\n\n  \
    \  for (int operation = 0; operation < 1000; operation++) {\n        if (random()\
    \ % 3 == 0) {\n            auto point = distinct_points[random() % distinct_points.size()];\n\
    \            long long value = int(random() % 101) - 50;\n            seg.set(point.first,\
    \ point.second, value);\n            expected[point] = value;\n            assert(seg(point.first,\
    \ point.second) == value);\n        } else {\n            int x_lower = int(random()\
    \ % 19) - 9;\n            int x_upper = int(random() % 19) - 9;\n            int\
    \ y_lower = int(random() % 19) - 9;\n            int y_upper = int(random() %\
    \ 19) - 9;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n\n         \
    \   long long answer = 0;\n            for (const auto& [point, value] : expected)\
    \ {\n                if (x_lower <= point.first && point.first < x_upper &&\n\
    \                    y_lower <= point.second && point.second < y_upper) {\n  \
    \                  answer += value;\n                }\n            }\n      \
    \      assert(seg.prod(x_lower, x_upper, y_lower, y_upper) == answer);\n     \
    \   }\n    }\n\n    long long total = 0;\n    for (const auto& [point, value]\
    \ : expected) {\n        (void)point;\n        total += value;\n    }\n    assert(seg.all_prod()\
    \ == total);\n    auto values = seg.to_vector();\n    assert(values.size() ==\
    \ expected.size());\n    for (const auto& [x, y, value] : values) {\n        std::pair<int,\
    \ int> point(x, y);\n        assert(expected[point] == value);\n    }\n}\n#endif\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n#ifndef NDEBUG\n    randomized_test();\n#endif\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<std::tuple<int, int, long long>> initial(n);\n \
    \   std::vector<std::pair<int, int>> points;\n    points.reserve(n + q);\n   \
    \ for (auto& [x, y, weight] : initial) {\n        std::cin >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(q);\n\
    \    for (Query& query : queries) {\n        std::cin >> query.type;\n       \
    \ if (query.type == 0) {\n            std::cin >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            std::cin >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::Segtree2D<Sum> seg(std::move(points));\n    for (const\
    \ auto& [x, y, weight] : initial) {\n        seg.set(x, y, seg.get(x, y) + weight);\n\
    \    }\n\n    for (const Query& query : queries) {\n        if (query.type ==\
    \ 0) {\n            long long current = seg.get(query.first, query.second);\n\
    \            seg.set(query.first, query.second, current + query.value);\n    \
    \    } else {\n            std::cout << seg.prod(query.first, query.third, query.second,\
    \ query.fourth)\n                      << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/segtree_2d.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/segtree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 22:04:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/segtree_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/segtree_2d.test.cpp
- /verify/verify/ds/segtree/segtree_2d.test.cpp.html
title: verify/ds/segtree/segtree_2d.test.cpp
---
