---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_segtree.test.cpp
    title: verify/ds/segtree/dynamic_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/dynamic_segtree.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral\
    \ Index>\nusing dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
    \ Index>\nconstexpr dynamic_size_type<Index> dynamic_distance(Index left, Index\
    \ right) {\n    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
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
    \n\n"
  code: "#ifndef M1UNE_DYNAMIC_SEGTREE_HPP\n#define M1UNE_DYNAMIC_SEGTREE_HPP 1\n\n\
    #include <array>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <limits>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"dynamic_segtree_common.hpp\"\n#include \"../../monoid/concept.hpp\"\
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
    \n#endif  // M1UNE_DYNAMIC_SEGTREE_HPP\n"
  dependsOn:
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/dynamic_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-23 01:19:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dynamic_segtree.test.cpp
documentation_of: ds/segtree/dynamic_segtree.hpp
layout: document
title: Dynamic Segment Tree
---

## Overview

`m1une::ds::DynamicSegtree` is a sparse segment tree for point assignments and
monoid products over a large integer coordinate range. Unlike `Segtree`, it does
not allocate storage for every coordinate. A node is created only when `set`
first visits its segment, so a domain such as $[-10^{18}, 10^{18})$ is practical
when only a small number of positions are updated.

The implementation uses one contiguous node pool rather than a separate heap
allocation per node. Call `reserve` when the approximate number of nodes is
known to avoid vector reallocations.

By default, unassigned coordinates have value `Monoid::id()`. A uniform
arbitrary initial value can instead be supplied to the constructor. Products
preserve coordinate order, so non-commutative monoids are supported.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

## Construction

* `DynamicSegtree()`: creates an empty tree over `[0, 0)`.
* `DynamicSegtree(Index n)`: creates a tree over `[0, n)`.
* `DynamicSegtree(Index left, Index right)`: creates a tree over
  `[left, right)`.
* `DynamicSegtree(Index left, Index right, T initial_value)`: creates a tree
  over `[left, right)` with every coordinate initialized to `initial_value`.

The coordinate domain is fixed at construction. Construction caches untouched
products for the possible segment lengths at each depth, using $O(\log U)$
memory and $O(\log^2 U)$ monoid operations. It does not create tree nodes.

## Methods

Let $U$ be the number of integer coordinates in the domain.

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the number of coordinates as the unsigned counterpart of `Index`. | $O(1)$ |
| `bool empty()` | Returns whether the coordinate domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint of the domain. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint of the domain. | $O(1)$ |
| `const T& initial_value()` | Returns the value assigned to untouched coordinates. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for `n` allocated nodes, excluding the sentinel. | $O(K)$ |
| `size_t node_count()` | Returns the number of nodes allocated by updates. | $O(1)$ |
| `void clear()` | Restores every coordinate to the initial value and keeps pool capacity. | $O(K)$ to destroy stored node values |
| `void set(Index p, T x)` | Assigns `x` to coordinate `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`, or the initial value if `p` was never assigned. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `Index max_right(Index l, F f)` | Returns the largest `r` for which `f(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, F f)` | Returns the smallest `l` for which `f(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ is the number of allocated nodes. After $Q$ assignments, memory usage
is $O(Q \log U)$ in the worst case. Updating an already allocated path does not
create more nodes.

For `max_right` and `min_left`, `f(Monoid::id())` must be true and `f` must be
monotone along the searched products, as with the ordinary `Segtree`.

## Example

```cpp
#include "ds/segtree/dynamic_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::DynamicSegtree<Sum>;

    Seg seg(-1'000'000'000LL, 1'000'000'001LL, 1);
    seg.reserve(256);

    seg.set(-500'000'000LL, 7);
    seg.set(900'000'000LL, 11);
    seg.set(-500'000'000LL, seg.get(-500'000'000LL) + 3);

    std::cout << seg.get(0) << "\n";                    // 1
    std::cout << seg.prod(-600'000'000LL, 0) << "\n";  // 600000009
}
```

## Notes

* `set` stores a monoid value directly. If the monoid has a `make` helper, call
  it before `set`.
* Assigning the identity does not reclaim nodes. `clear` releases all logical
  assignments at once and reuses the pool capacity.
* For versioned sparse point assignments and range products, use
  `PersistentDynamicSegtree`.
* For sparse range updates and range products, use `DynamicLazySegtree`. Its
  constructor accepts a uniform initial leaf so size-aware actions can account
  for untouched coordinates.
* For sparse range updates with point queries only, use `DynamicDualSegtree`.
