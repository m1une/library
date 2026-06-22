---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree.hpp
    title: Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#line 1 \"ds/segtree/dynamic_segtree.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <limits>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n\
    #line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing dynamic_size_type\
    \ = std::make_unsigned_t<Index>;\n\ntemplate <std::integral Index>\nconstexpr\
    \ dynamic_size_type<Index> dynamic_distance(Index left, Index right) {\n    return\
    \ static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
    }\n\ntemplate <class Monoid, class Size>\ntypename Monoid::value_type monoid_repeat(typename\
    \ Monoid::value_type value, Size count) {\n    typename Monoid::value_type result\
    \ = Monoid::id();\n    while (count != 0) {\n        if (count & 1) result = Monoid::op(result,\
    \ value);\n        count >>= 1;\n        if (count != 0) value = Monoid::op(value,\
    \ value);\n    }\n    return result;\n}\n\ntemplate <class ActedMonoid>\ntypename\
    \ ActedMonoid::value_type dynamic_mapping(\n    const typename ActedMonoid::operator_type&\
    \ f,\n    const typename ActedMonoid::value_type& value\n) {\n    using F = typename\
    \ ActedMonoid::operator_type;\n    using T = typename ActedMonoid::value_type;\n\
    \    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g,\
    \ x, ord); }) {\n        return ActedMonoid::mapping(f, value, 0);\n    } else\
    \ {\n        return ActedMonoid::mapping(f, value);\n    }\n}\n\ntemplate <class\
    \ ActedMonoid, class Size>\ntypename ActedMonoid::operator_type dynamic_shift(\n\
    \    const typename ActedMonoid::operator_type& f,\n    Size offset\n) {\n   \
    \ using F = typename ActedMonoid::operator_type;\n    if constexpr (requires(F\
    \ g, long long ord) { ActedMonoid::op_shift(g, ord); }) {\n        assert(offset\
    \ <= static_cast<Size>(std::numeric_limits<long long>::max()));\n        return\
    \ ActedMonoid::op_shift(f, static_cast<long long>(offset));\n    } else {\n  \
    \      return f;\n    }\n}\n\ntemplate <class Monoid, std::integral Index>\nclass\
    \ UniformMonoidDomain {\n   public:\n    using T = typename Monoid::value_type;\n\
    \    using size_type = dynamic_size_type<Index>;\n\n   private:\n    struct Level\
    \ {\n        size_type small_length;\n        T small_value;\n        T large_value;\n\
    \    };\n\n    Index _left;\n    Index _right;\n    T _initial_value;\n    std::vector<Level>\
    \ _levels;\n\n   public:\n    UniformMonoidDomain(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        size_type n = size();\n        constexpr\
    \ int digits = std::numeric_limits<size_type>::digits;\n        _levels.reserve(digits\
    \ + 1);\n        for (int depth = 0; depth <= digits; depth++) {\n           \
    \ size_type small = depth == digits ? 0 : n >> depth;\n            size_type large\
    \ = small;\n            if (depth != 0) {\n                bool has_remainder;\n\
    \                if (depth == digits) {\n                    has_remainder = n\
    \ != 0;\n                } else {\n                    size_type mask = (size_type(1)\
    \ << depth) - 1;\n                    has_remainder = (n & mask) != 0;\n     \
    \           }\n                if (has_remainder) large++;\n            }\n  \
    \          _levels.push_back(Level{\n                small,\n                monoid_repeat<Monoid>(_initial_value,\
    \ small),\n                monoid_repeat<Monoid>(_initial_value, large),\n   \
    \         });\n        }\n    }\n\n    Index left_bound() const {\n        return\
    \ _left;\n    }\n\n    Index right_bound() const {\n        return _right;\n \
    \   }\n\n    size_type size() const {\n        return dynamic_distance(_left,\
    \ _right);\n    }\n\n    bool empty() const {\n        return _left == _right;\n\
    \    }\n\n    const T& initial_value() const {\n        return _initial_value;\n\
    \    }\n\n    const T& default_product(int depth, Index left, Index right) const\
    \ {\n        assert(0 <= depth && depth < int(_levels.size()));\n        const\
    \ Level& level = _levels[depth];\n        size_type length = dynamic_distance(left,\
    \ right);\n        if (length == level.small_length) return level.small_value;\n\
    \        assert(length == level.small_length + 1);\n        return level.large_value;\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 16 \"ds/segtree/dynamic_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A sparse segment tree over an integral\
    \ half-open interval.\n// Nodes are allocated from a contiguous pool only when\
    \ a position is touched.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct DynamicSegtree {\n    using T = typename Monoid::value_type;\n    using\
    \ index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n\n        Node() : val(Monoid::id()), left(0), right(0) {}\n    };\n\
    \n    static constexpr int path_capacity = std::numeric_limits<size_type>::digits\
    \ + 1;\n\n    detail::UniformMonoidDomain<Monoid, Index> _domain;\n    int _root;\n\
    \    std::vector<Node> _nodes;\n\n    int new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    const T& value(int t, Index\
    \ left, Index right, int depth) const {\n        if (t) return _nodes[t].val;\n\
    \        return _domain.default_product(depth, left, right);\n    }\n\n    void\
    \ update(int t, Index left, Index right, int depth) {\n        Index middle =\
    \ std::midpoint(left, right);\n        _nodes[t].val = Monoid::op(\n         \
    \   value(_nodes[t].left, left, middle, depth + 1),\n            value(_nodes[t].right,\
    \ middle, right, depth + 1)\n        );\n    }\n\n    T prod_node(int t, Index\
    \ l, Index r, int depth, Index ql, Index qr) const {\n        if (qr <= l || r\
    \ <= ql) return Monoid::id();\n        if (ql <= l && r <= qr) return value(t,\
    \ l, r, depth);\n        Index m = std::midpoint(l, r);\n        return Monoid::op(\n\
    \            prod_node(t ? _nodes[t].left : 0, l, m, depth + 1, ql, qr),\n   \
    \         prod_node(t ? _nodes[t].right : 0, m, r, depth + 1, ql, qr)\n      \
    \  );\n    }\n\n    template <class F>\n    Index max_right_node(\n        int\
    \ t,\n        Index l,\n        Index r,\n        int depth,\n        Index ql,\n\
    \        T& sm,\n        F& f\n    ) const {\n        if (r <= ql) return r;\n\
    \        if (ql <= l) {\n            T next = Monoid::op(sm, value(t, l, r, depth));\n\
    \            if (f(next)) {\n                sm = std::move(next);\n         \
    \       return r;\n            }\n            Index m = std::midpoint(l, r);\n\
    \            if (m == l) return l;\n        }\n        Index m = std::midpoint(l,\
    \ r);\n        Index res = max_right_node(\n            t ? _nodes[t].left : 0,\n\
    \            l,\n            m,\n            depth + 1,\n            ql,\n   \
    \         sm,\n            f\n        );\n        if (res < m) return res;\n \
    \       return max_right_node(\n            t ? _nodes[t].right : 0,\n       \
    \     m,\n            r,\n            depth + 1,\n            ql,\n          \
    \  sm,\n            f\n        );\n    }\n\n    template <class F>\n    Index\
    \ min_left_node(\n        int t,\n        Index l,\n        Index r,\n       \
    \ int depth,\n        Index qr,\n        T& sm,\n        F& f\n    ) const {\n\
    \        if (qr <= l) return l;\n        if (r <= qr) {\n            T next =\
    \ Monoid::op(value(t, l, r, depth), sm);\n            if (f(next)) {\n       \
    \         sm = std::move(next);\n                return l;\n            }\n  \
    \          Index m = std::midpoint(l, r);\n            if (m == l) return r;\n\
    \        }\n        Index m = std::midpoint(l, r);\n        Index res = min_left_node(\n\
    \            t ? _nodes[t].right : 0,\n            m,\n            r,\n      \
    \      depth + 1,\n            qr,\n            sm,\n            f\n        );\n\
    \        if (m < res) return res;\n        return min_left_node(\n           \
    \ t ? _nodes[t].left : 0,\n            l,\n            m,\n            depth +\
    \ 1,\n            qr,\n            sm,\n            f\n        );\n    }\n\n \
    \  public:\n    // Constructs an empty tree over [0, 0).\n    DynamicSegtree()\
    \ : DynamicSegtree(Index(0), Index(0)) {}\n\n    // Constructs a tree over [0,\
    \ n).\n    explicit DynamicSegtree(Index n) : DynamicSegtree(Index(0), n) {\n\
    \        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n \
    \   }\n\n    // Constructs a tree over [left, right).\n    DynamicSegtree(Index\
    \ left, Index right)\n        : DynamicSegtree(left, right, Monoid::id()) {}\n\
    \n    // Constructs a tree over [left, right) with every coordinate initialized\
    \ to\n    // `initial_value`.\n    DynamicSegtree(Index left, Index right, T initial_value)\n\
    \        : _domain(left, right, std::move(initial_value)), _root(0), _nodes(1)\
    \ {}\n\n    // Returns the number of coordinates in the domain.\n    size_type\
    \ size() const {\n        return _domain.size();\n    }\n\n    // Returns whether\
    \ the coordinate domain is empty.\n    bool empty() const {\n        return _domain.empty();\n\
    \    }\n\n    // Returns the left endpoint of the coordinate domain.\n    Index\
    \ left_bound() const {\n        return _domain.left_bound();\n    }\n\n    //\
    \ Returns the right endpoint of the coordinate domain.\n    Index right_bound()\
    \ const {\n        return _domain.right_bound();\n    }\n\n    // Returns the\
    \ value assigned to untouched coordinates.\n    const T& initial_value() const\
    \ {\n        return _domain.initial_value();\n    }\n\n    // Reserves space for\
    \ `node_capacity` allocated nodes.\n    void reserve(std::size_t node_capacity)\
    \ {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _nodes.reserve(node_capacity + 1);\n    }\n\n    // Returns the number\
    \ of allocated nodes, excluding the sentinel.\n    std::size_t node_count() const\
    \ {\n        return _nodes.size() - 1;\n    }\n\n    // Restores every coordinate\
    \ to the initial value while preserving capacity.\n    void clear() {\n      \
    \  _root = 0;\n        _nodes.resize(1);\n    }\n\n    // Sets the value at coordinate\
    \ `p` to `x`.\n    void set(Index p, T x) {\n        assert(left_bound() <= p\
    \ && p < right_bound());\n        if (!_root) _root = new_node();\n\n        std::array<int,\
    \ path_capacity> path;\n        std::array<Index, path_capacity> path_left;\n\
    \        std::array<Index, path_capacity> path_right;\n        int depth = 0;\n\
    \        int t = _root;\n        Index l = left_bound();\n        Index r = right_bound();\n\
    \n        while (true) {\n            assert(depth < path_capacity);\n       \
    \     path[depth] = t;\n            path_left[depth] = l;\n            path_right[depth]\
    \ = r;\n            depth++;\n            Index m = std::midpoint(l, r);\n   \
    \         if (m == l) break;\n\n            if (p < m) {\n                int\
    \ child = _nodes[t].left;\n                if (!child) {\n                   \
    \ child = new_node();\n                    _nodes[t].left = child;\n         \
    \       }\n                t = child;\n                r = m;\n            } else\
    \ {\n                int child = _nodes[t].right;\n                if (!child)\
    \ {\n                    child = new_node();\n                    _nodes[t].right\
    \ = child;\n                }\n                t = child;\n                l =\
    \ m;\n            }\n        }\n\n        _nodes[t].val = std::move(x);\n    \
    \    for (int i = depth - 2; i >= 0; i--) {\n            update(path[i], path_left[i],\
    \ path_right[i], i);\n        }\n    }\n\n    // Returns the value at coordinate\
    \ `p`.\n    T get(Index p) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        int t = _root;\n        Index l = left_bound();\n        Index r = right_bound();\n\
    \        int depth = 0;\n\n        while (t) {\n            Index m = std::midpoint(l,\
    \ r);\n            if (m == l) return value(t, l, r, depth);\n            if (p\
    \ < m) {\n                t = _nodes[t].left;\n                r = m;\n      \
    \      } else {\n                t = _nodes[t].right;\n                l = m;\n\
    \            }\n            depth++;\n        }\n        return initial_value();\n\
    \    }\n\n    // Returns the value at coordinate `p`.\n    T operator[](Index\
    \ p) const {\n        return get(p);\n    }\n\n    // Returns the monoid product\
    \ over [l, r).\n    T prod(Index l, Index r) const {\n        assert(left_bound()\
    \ <= l && l <= r && r <= right_bound());\n        if (l == r) return Monoid::id();\n\
    \        return prod_node(_root, left_bound(), right_bound(), 0, l, r);\n    }\n\
    \n    // Returns the monoid product over the entire coordinate domain.\n    T\
    \ all_prod() const {\n        return value(_root, left_bound(), right_bound(),\
    \ 0);\n    }\n\n    // Finds the largest r such that f(prod(l, r)) is true.\n\
    \    template <class F>\n    Index max_right(Index l, F f) const {\n        assert(left_bound()\
    \ <= l && l <= right_bound());\n        assert(f(Monoid::id()));\n        if (l\
    \ == right_bound()) return right_bound();\n        T sm = Monoid::id();\n    \
    \    return max_right_node(\n            _root,\n            left_bound(),\n \
    \           right_bound(),\n            0,\n            l,\n            sm,\n\
    \            f\n        );\n    }\n\n    // Finds the smallest l such that f(prod(l,\
    \ r)) is true.\n    template <class F>\n    Index min_left(Index r, F f) const\
    \ {\n        assert(left_bound() <= r && r <= right_bound());\n        assert(f(Monoid::id()));\n\
    \        if (r == left_bound()) return left_bound();\n        T sm = Monoid::id();\n\
    \        return min_left_node(\n            _root,\n            left_bound(),\n\
    \            right_bound(),\n            0,\n            r,\n            sm,\n\
    \            f\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 10 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n#include\
    \ <string>\n#line 12 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n\n#line 1\
    \ \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid\
    \ for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type\
    \ = T;\n\n    // Returns the identity element for addition, which is 0.\n    static\
    \ constexpr T id() {\n        return T(0);\n    }\n\n    // Returns the sum of\
    \ a and b.\n    static constexpr T op(const T& a, const T& b) {\n        return\
    \ a + b;\n    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 14 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\
    \n\nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n  \
    \  static value_type id() {\n        return \"\";\n    }\n\n    static value_type\
    \ op(const value_type& a, const value_type& b) {\n        return a + b;\n    }\n\
    };\n\nvoid test_library_features() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::DynamicSegtree<Sum>;\n\n    Seg empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.all_prod()\
    \ == 0);\n\n    Seg seg(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL);\n\
    \    assert(!seg.empty());\n    assert(seg.left_bound() == -1'000'000'000'000'000'000LL);\n\
    \    assert(seg.right_bound() == 1'000'000'000'000'000'000LL);\n    assert(seg.size()\
    \ == 2'000'000'000'000'000'000ULL);\n\n    seg.reserve(256);\n    seg.set(-3,\
    \ 2);\n    seg.set(2, 4);\n    seg.set(7, 1);\n\n    assert(seg.get(-3) == 2);\n\
    \    assert(seg[-2] == 0);\n    assert(seg.prod(-4, 3) == 6);\n    assert(seg.prod(3,\
    \ 7) == 0);\n    assert(seg.all_prod() == 7);\n    assert(seg.max_right(-8, [](long\
    \ long x) { return x <= 5; }) == 2);\n    assert(seg.min_left(8, [](long long\
    \ x) { return x <= 4; }) == 3);\n\n    [[maybe_unused]] std::size_t nodes = seg.node_count();\n\
    \    seg.set(-3, 5);\n    assert(seg.node_count() == nodes);\n    assert(seg.all_prod()\
    \ == 10);\n\n    seg.clear();\n    assert(seg.node_count() == 0);\n    assert(seg.all_prod()\
    \ == 0);\n    assert(seg.get(-3) == 0);\n\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> uniform(-5, 6, 3);\n    assert(uniform.initial_value() == 3);\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \    assert(uniform.prod(-2, 4) == 18);\n    assert(uniform.max_right(-5, [](long\
    \ long x) { return x <= 14; }) == -1);\n    assert(uniform.min_left(6, [](long\
    \ long x) { return x <= 14; }) == 2);\n    uniform.set(0, 10);\n    assert(uniform.all_prod()\
    \ == 40);\n    assert(uniform.prod(-2, 4) == 25);\n    uniform.clear();\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \n    m1une::ds::DynamicSegtree<Concat, int> text(-4, 5);\n    text.set(2, \"\
    b\");\n    text.set(-1, \"a\");\n    assert(text.prod(-4, 5) == \"ab\");\n\n \
    \   m1une::ds::DynamicSegtree<Concat, int> uniform_text(-2, 3, \"x\");\n    assert(uniform_text.all_prod()\
    \ == \"xxxxx\");\n    uniform_text.set(1, \"a\");\n    uniform_text.set(-1, \"\
    b\");\n    assert(uniform_text.all_prod() == \"xbxax\");\n\n    Seg extreme(std::numeric_limits<long\
    \ long>::min(), std::numeric_limits<long long>::max());\n    extreme.set(std::numeric_limits<long\
    \ long>::min(), 3);\n    extreme.set(std::numeric_limits<long long>::max() - 1,\
    \ 4);\n    assert(extreme.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(extreme.get(std::numeric_limits<long long>::min()) == 3);\n    assert(extreme.get(std::numeric_limits<long\
    \ long>::max() - 1) == 4);\n    assert(extreme.all_prod() == 7);\n\n    constexpr\
    \ int left = -37;\n    constexpr int right = 42;\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> small(left, right);\n    std::vector<long long> a(right - left);\n    auto\
    \ value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p - left)];\n\
    \    };\n    std::uint64_t state = 1;\n    auto random = [&state]() {\n      \
    \  state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 2000; step++) {\n        int p = left\
    \ + int(random() % a.size());\n        long long x = static_cast<long long>(random()\
    \ % 10);\n        small.set(p, x);\n        value_at(p) = x;\n\n        int l\
    \ = left + int(random() % (a.size() + 1));\n        int r = left + int(random()\
    \ % (a.size() + 1));\n        if (r < l) std::swap(l, r);\n        [[maybe_unused]]\
    \ long long expected = 0;\n        for (int i = l; i < r; i++) expected += value_at(i);\n\
    \        assert(small.prod(l, r) == expected);\n\n        long long limit = static_cast<long\
    \ long>(random() % 100);\n        int max_right = l;\n        long long sum =\
    \ 0;\n        while (max_right < right && sum + value_at(max_right) <= limit)\
    \ {\n            sum += value_at(max_right);\n            max_right++;\n     \
    \   }\n        assert(small.max_right(l, [limit](long long value) { return value\
    \ <= limit; }) == max_right);\n\n        int min_left = r;\n        sum = 0;\n\
    \        while (left < min_left && value_at(min_left - 1) + sum <= limit) {\n\
    \            min_left--;\n            sum += value_at(min_left);\n        }\n\
    \        assert(small.min_left(r, [limit](long long value) { return value <= limit;\
    \ }) == min_left);\n    }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_library_features();\n\n    int n, q;\n\
    \    std::cin >> n >> q;\n\n    using Sum = m1une::monoid::Add<long long>;\n \
    \   m1une::ds::DynamicSegtree<Sum, int> seg(n);\n    seg.reserve(std::size_t(2)\
    \ * std::size_t(n));\n\n    for (int i = 0; i < n; i++) {\n        long long x;\n\
    \        std::cin >> x;\n        seg.set(i, x);\n    }\n\n    for (int query =\
    \ 0; query < q; query++) {\n        int type;\n        std::cin >> type;\n   \
    \     if (type == 0) {\n            int p;\n            long long x;\n       \
    \     std::cin >> p >> x;\n            seg.set(p, seg.get(p) + x);\n        }\
    \ else {\n            int l, r;\n            std::cin >> l >> r;\n           \
    \ std::cout << seg.prod(l, r) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../../../ds/segtree/dynamic_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <string>\n#include <vector>\n\n#include \"../../../monoid/add.hpp\"\n\
    \nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static\
    \ value_type id() {\n        return \"\";\n    }\n\n    static value_type op(const\
    \ value_type& a, const value_type& b) {\n        return a + b;\n    }\n};\n\n\
    void test_library_features() {\n    using Sum = m1une::monoid::Add<long long>;\n\
    \    using Seg = m1une::ds::DynamicSegtree<Sum>;\n\n    Seg empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n    assert(empty.all_prod() == 0);\n\n    Seg\
    \ seg(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL);\n    assert(!seg.empty());\n\
    \    assert(seg.left_bound() == -1'000'000'000'000'000'000LL);\n    assert(seg.right_bound()\
    \ == 1'000'000'000'000'000'000LL);\n    assert(seg.size() == 2'000'000'000'000'000'000ULL);\n\
    \n    seg.reserve(256);\n    seg.set(-3, 2);\n    seg.set(2, 4);\n    seg.set(7,\
    \ 1);\n\n    assert(seg.get(-3) == 2);\n    assert(seg[-2] == 0);\n    assert(seg.prod(-4,\
    \ 3) == 6);\n    assert(seg.prod(3, 7) == 0);\n    assert(seg.all_prod() == 7);\n\
    \    assert(seg.max_right(-8, [](long long x) { return x <= 5; }) == 2);\n   \
    \ assert(seg.min_left(8, [](long long x) { return x <= 4; }) == 3);\n\n    [[maybe_unused]]\
    \ std::size_t nodes = seg.node_count();\n    seg.set(-3, 5);\n    assert(seg.node_count()\
    \ == nodes);\n    assert(seg.all_prod() == 10);\n\n    seg.clear();\n    assert(seg.node_count()\
    \ == 0);\n    assert(seg.all_prod() == 0);\n    assert(seg.get(-3) == 0);\n\n\
    \    m1une::ds::DynamicSegtree<Sum, int> uniform(-5, 6, 3);\n    assert(uniform.initial_value()\
    \ == 3);\n    assert(uniform.node_count() == 0);\n    assert(uniform.get(0) ==\
    \ 3);\n    assert(uniform.all_prod() == 33);\n    assert(uniform.prod(-2, 4) ==\
    \ 18);\n    assert(uniform.max_right(-5, [](long long x) { return x <= 14; })\
    \ == -1);\n    assert(uniform.min_left(6, [](long long x) { return x <= 14; })\
    \ == 2);\n    uniform.set(0, 10);\n    assert(uniform.all_prod() == 40);\n   \
    \ assert(uniform.prod(-2, 4) == 25);\n    uniform.clear();\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \n    m1une::ds::DynamicSegtree<Concat, int> text(-4, 5);\n    text.set(2, \"\
    b\");\n    text.set(-1, \"a\");\n    assert(text.prod(-4, 5) == \"ab\");\n\n \
    \   m1une::ds::DynamicSegtree<Concat, int> uniform_text(-2, 3, \"x\");\n    assert(uniform_text.all_prod()\
    \ == \"xxxxx\");\n    uniform_text.set(1, \"a\");\n    uniform_text.set(-1, \"\
    b\");\n    assert(uniform_text.all_prod() == \"xbxax\");\n\n    Seg extreme(std::numeric_limits<long\
    \ long>::min(), std::numeric_limits<long long>::max());\n    extreme.set(std::numeric_limits<long\
    \ long>::min(), 3);\n    extreme.set(std::numeric_limits<long long>::max() - 1,\
    \ 4);\n    assert(extreme.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(extreme.get(std::numeric_limits<long long>::min()) == 3);\n    assert(extreme.get(std::numeric_limits<long\
    \ long>::max() - 1) == 4);\n    assert(extreme.all_prod() == 7);\n\n    constexpr\
    \ int left = -37;\n    constexpr int right = 42;\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> small(left, right);\n    std::vector<long long> a(right - left);\n    auto\
    \ value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p - left)];\n\
    \    };\n    std::uint64_t state = 1;\n    auto random = [&state]() {\n      \
    \  state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 2000; step++) {\n        int p = left\
    \ + int(random() % a.size());\n        long long x = static_cast<long long>(random()\
    \ % 10);\n        small.set(p, x);\n        value_at(p) = x;\n\n        int l\
    \ = left + int(random() % (a.size() + 1));\n        int r = left + int(random()\
    \ % (a.size() + 1));\n        if (r < l) std::swap(l, r);\n        [[maybe_unused]]\
    \ long long expected = 0;\n        for (int i = l; i < r; i++) expected += value_at(i);\n\
    \        assert(small.prod(l, r) == expected);\n\n        long long limit = static_cast<long\
    \ long>(random() % 100);\n        int max_right = l;\n        long long sum =\
    \ 0;\n        while (max_right < right && sum + value_at(max_right) <= limit)\
    \ {\n            sum += value_at(max_right);\n            max_right++;\n     \
    \   }\n        assert(small.max_right(l, [limit](long long value) { return value\
    \ <= limit; }) == max_right);\n\n        int min_left = r;\n        sum = 0;\n\
    \        while (left < min_left && value_at(min_left - 1) + sum <= limit) {\n\
    \            min_left--;\n            sum += value_at(min_left);\n        }\n\
    \        assert(small.min_left(r, [limit](long long value) { return value <= limit;\
    \ }) == min_left);\n    }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_library_features();\n\n    int n, q;\n\
    \    std::cin >> n >> q;\n\n    using Sum = m1une::monoid::Add<long long>;\n \
    \   m1une::ds::DynamicSegtree<Sum, int> seg(n);\n    seg.reserve(std::size_t(2)\
    \ * std::size_t(n));\n\n    for (int i = 0; i < n; i++) {\n        long long x;\n\
    \        std::cin >> x;\n        seg.set(i, x);\n    }\n\n    for (int query =\
    \ 0; query < q; query++) {\n        int type;\n        std::cin >> type;\n   \
    \     if (type == 0) {\n            int p;\n            long long x;\n       \
    \     std::cin >> p >> x;\n            seg.set(p, seg.get(p) + x);\n        }\
    \ else {\n            int l, r;\n            std::cin >> l >> r;\n           \
    \ std::cout << seg.prod(l, r) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/dynamic_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 01:19:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dynamic_segtree.test.cpp
- /verify/verify/ds/segtree/dynamic_segtree.test.cpp.html
title: verify/ds/segtree/dynamic_segtree.test.cpp
---
