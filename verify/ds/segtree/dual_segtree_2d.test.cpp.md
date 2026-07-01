---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dual_segtree_2d.hpp
    title: Dual Segtree 2D
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_add_point_get
    links:
    - https://judge.yosupo.jp/problem/rectangle_add_point_get
  bundledCode: "#line 1 \"verify/ds/segtree/dual_segtree_2d.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\n\n#line 1 \"ds/segtree/dual_segtree_2d.hpp\"\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n\n  \
    \  // Returns the identity element for addition, which is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a + b;\n\
    \    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/segtree/dual_segtree_2d.test.cpp\"\
    \n\n#line 8 \"verify/ds/segtree/dual_segtree_2d.test.cpp\"\n#include <iostream>\n\
    #include <map>\n#include <random>\n#line 14 \"verify/ds/segtree/dual_segtree_2d.test.cpp\"\
    \n\nusing Add = m1une::monoid::Add<long long>;\n\nstruct Rectangle {\n    int\
    \ left;\n    int lower;\n    int right;\n    int upper;\n    long long value;\n\
    };\n\nstruct Operation {\n    int type;\n    Rectangle rectangle;\n    int x;\n\
    \    int y;\n};\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    m1une::ds::DualSegtree2D<Add>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n    empty.apply(-10,\
    \ 10, -10, 10, 5);\n    assert(empty.get(0, 0) == 0);\n    assert(empty.to_vector().empty());\n\
    \n    std::mt19937 random(271828182);\n    std::vector<std::pair<int, int>> points;\n\
    \    std::map<std::pair<int, int>, long long> expected;\n    for (int i = 0; i\
    \ < 50; i++) {\n        int x = int(random() % 17) - 8;\n        int y = int(random()\
    \ % 17) - 8;\n        points.emplace_back(x, y);\n        expected[{x, y}] = 0;\n\
    \    }\n\n    m1une::ds::DualSegtree2D<Add> seg(points);\n    assert(seg.size()\
    \ == int(expected.size()));\n    assert(!seg.contains_point(100, 100));\n    assert(seg.get(100,\
    \ 100) == 0);\n\n    std::vector<std::pair<int, int>> distinct_points;\n    for\
    \ (const auto& [point, value] : expected) {\n        (void)value;\n        distinct_points.push_back(point);\n\
    \    }\n\n    for (int operation = 0; operation < 1200; operation++) {\n     \
    \   if (random() % 4 == 0) {\n            auto point = distinct_points[random()\
    \ % distinct_points.size()];\n            long long value = int(random() % 101)\
    \ - 50;\n            seg.apply(point.first, point.second, value);\n          \
    \  expected[point] += value;\n        } else {\n            int x_lower = int(random()\
    \ % 21) - 10;\n            int x_upper = int(random() % 21) - 10;\n          \
    \  int y_lower = int(random() % 21) - 10;\n            int y_upper = int(random()\
    \ % 21) - 10;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ long long value = int(random() % 101) - 50;\n\n            seg.apply(x_lower,\
    \ x_upper, y_lower, y_upper, value);\n            for (auto& [point, current]\
    \ : expected) {\n                if (x_lower <= point.first && point.first < x_upper\
    \ &&\n                    y_lower <= point.second && point.second < y_upper) {\n\
    \                    current += value;\n                }\n            }\n   \
    \     }\n\n        auto point = distinct_points[random() % distinct_points.size()];\n\
    \        assert(seg.get(point.first, point.second) == expected[point]);\n    \
    \    assert(seg(point.first, point.second) == expected[point]);\n    }\n\n   \
    \ auto values = seg.to_vector();\n    assert(values.size() == expected.size());\n\
    \    for (const auto& [x, y, value] : values) {\n        std::pair<int, int> point(x,\
    \ y);\n        assert(expected[point] == value);\n    }\n\n    std::vector<std::tuple<int,\
    \ int, long long>> weighted;\n    weighted.emplace_back(1, 2, 3);\n    weighted.emplace_back(1,\
    \ 2, 4);\n    weighted.emplace_back(3, 4, 5);\n    m1une::ds::DualSegtree2D<Add>\
    \ initialized(weighted);\n    assert(initialized.get(1, 2) == 7);\n    assert(initialized.get(3,\
    \ 4) == 5);\n}\n#endif\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n#ifndef NDEBUG\n    randomized_test();\n#endif\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Rectangle> initial(n);\n\
    \    for (Rectangle& rectangle : initial) {\n        std::cin >> rectangle.left\
    \ >> rectangle.lower >> rectangle.right >> rectangle.upper\n                 >>\
    \ rectangle.value;\n    }\n\n    std::vector<Operation> operations(q);\n    std::vector<std::pair<int,\
    \ int>> points;\n    points.reserve(q);\n    for (Operation& operation : operations)\
    \ {\n        std::cin >> operation.type;\n        if (operation.type == 0) {\n\
    \            Rectangle& rectangle = operation.rectangle;\n            std::cin\
    \ >> rectangle.left >> rectangle.lower >> rectangle.right >> rectangle.upper\n\
    \                     >> rectangle.value;\n            operation.x = operation.y\
    \ = 0;\n        } else {\n            std::cin >> operation.x >> operation.y;\n\
    \            operation.rectangle = Rectangle{0, 0, 0, 0, 0};\n            points.emplace_back(operation.x,\
    \ operation.y);\n        }\n    }\n\n    m1une::ds::DualSegtree2D<Add> seg(std::move(points));\n\
    \    for (const Rectangle& rectangle : initial) {\n        seg.apply(rectangle.left,\
    \ rectangle.right, rectangle.lower, rectangle.upper,\n                  rectangle.value);\n\
    \    }\n\n    for (const Operation& operation : operations) {\n        if (operation.type\
    \ == 0) {\n            const Rectangle& rectangle = operation.rectangle;\n   \
    \         seg.apply(rectangle.left, rectangle.right, rectangle.lower, rectangle.upper,\n\
    \                      rectangle.value);\n        } else {\n            std::cout\
    \ << seg.get(operation.x, operation.y) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\
    \n\n#include \"../../../ds/segtree/dual_segtree_2d.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <map>\n\
    #include <random>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    using Add = m1une::monoid::Add<long long>;\n\nstruct Rectangle {\n    int left;\n\
    \    int lower;\n    int right;\n    int upper;\n    long long value;\n};\n\n\
    struct Operation {\n    int type;\n    Rectangle rectangle;\n    int x;\n    int\
    \ y;\n};\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    m1une::ds::DualSegtree2D<Add>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n    empty.apply(-10,\
    \ 10, -10, 10, 5);\n    assert(empty.get(0, 0) == 0);\n    assert(empty.to_vector().empty());\n\
    \n    std::mt19937 random(271828182);\n    std::vector<std::pair<int, int>> points;\n\
    \    std::map<std::pair<int, int>, long long> expected;\n    for (int i = 0; i\
    \ < 50; i++) {\n        int x = int(random() % 17) - 8;\n        int y = int(random()\
    \ % 17) - 8;\n        points.emplace_back(x, y);\n        expected[{x, y}] = 0;\n\
    \    }\n\n    m1une::ds::DualSegtree2D<Add> seg(points);\n    assert(seg.size()\
    \ == int(expected.size()));\n    assert(!seg.contains_point(100, 100));\n    assert(seg.get(100,\
    \ 100) == 0);\n\n    std::vector<std::pair<int, int>> distinct_points;\n    for\
    \ (const auto& [point, value] : expected) {\n        (void)value;\n        distinct_points.push_back(point);\n\
    \    }\n\n    for (int operation = 0; operation < 1200; operation++) {\n     \
    \   if (random() % 4 == 0) {\n            auto point = distinct_points[random()\
    \ % distinct_points.size()];\n            long long value = int(random() % 101)\
    \ - 50;\n            seg.apply(point.first, point.second, value);\n          \
    \  expected[point] += value;\n        } else {\n            int x_lower = int(random()\
    \ % 21) - 10;\n            int x_upper = int(random() % 21) - 10;\n          \
    \  int y_lower = int(random() % 21) - 10;\n            int y_upper = int(random()\
    \ % 21) - 10;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ long long value = int(random() % 101) - 50;\n\n            seg.apply(x_lower,\
    \ x_upper, y_lower, y_upper, value);\n            for (auto& [point, current]\
    \ : expected) {\n                if (x_lower <= point.first && point.first < x_upper\
    \ &&\n                    y_lower <= point.second && point.second < y_upper) {\n\
    \                    current += value;\n                }\n            }\n   \
    \     }\n\n        auto point = distinct_points[random() % distinct_points.size()];\n\
    \        assert(seg.get(point.first, point.second) == expected[point]);\n    \
    \    assert(seg(point.first, point.second) == expected[point]);\n    }\n\n   \
    \ auto values = seg.to_vector();\n    assert(values.size() == expected.size());\n\
    \    for (const auto& [x, y, value] : values) {\n        std::pair<int, int> point(x,\
    \ y);\n        assert(expected[point] == value);\n    }\n\n    std::vector<std::tuple<int,\
    \ int, long long>> weighted;\n    weighted.emplace_back(1, 2, 3);\n    weighted.emplace_back(1,\
    \ 2, 4);\n    weighted.emplace_back(3, 4, 5);\n    m1une::ds::DualSegtree2D<Add>\
    \ initialized(weighted);\n    assert(initialized.get(1, 2) == 7);\n    assert(initialized.get(3,\
    \ 4) == 5);\n}\n#endif\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n#ifndef NDEBUG\n    randomized_test();\n#endif\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Rectangle> initial(n);\n\
    \    for (Rectangle& rectangle : initial) {\n        std::cin >> rectangle.left\
    \ >> rectangle.lower >> rectangle.right >> rectangle.upper\n                 >>\
    \ rectangle.value;\n    }\n\n    std::vector<Operation> operations(q);\n    std::vector<std::pair<int,\
    \ int>> points;\n    points.reserve(q);\n    for (Operation& operation : operations)\
    \ {\n        std::cin >> operation.type;\n        if (operation.type == 0) {\n\
    \            Rectangle& rectangle = operation.rectangle;\n            std::cin\
    \ >> rectangle.left >> rectangle.lower >> rectangle.right >> rectangle.upper\n\
    \                     >> rectangle.value;\n            operation.x = operation.y\
    \ = 0;\n        } else {\n            std::cin >> operation.x >> operation.y;\n\
    \            operation.rectangle = Rectangle{0, 0, 0, 0, 0};\n            points.emplace_back(operation.x,\
    \ operation.y);\n        }\n    }\n\n    m1une::ds::DualSegtree2D<Add> seg(std::move(points));\n\
    \    for (const Rectangle& rectangle : initial) {\n        seg.apply(rectangle.left,\
    \ rectangle.right, rectangle.lower, rectangle.upper,\n                  rectangle.value);\n\
    \    }\n\n    for (const Operation& operation : operations) {\n        if (operation.type\
    \ == 0) {\n            const Rectangle& rectangle = operation.rectangle;\n   \
    \         seg.apply(rectangle.left, rectangle.right, rectangle.lower, rectangle.upper,\n\
    \                      rectangle.value);\n        } else {\n            std::cout\
    \ << seg.get(operation.x, operation.y) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/dual_segtree_2d.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dual_segtree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 22:04:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dual_segtree_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dual_segtree_2d.test.cpp
- /verify/verify/ds/segtree/dual_segtree_2d.test.cpp.html
title: verify/ds/segtree/dual_segtree_2d.test.cpp
---
