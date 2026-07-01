---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_ap_add_range_sum.hpp
    title: Range AP Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_lazy_segtree.hpp
    title: Dynamic Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/dynamic_lazy_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#line\
    \ 1 \"ds/segtree/dynamic_lazy_segtree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstddef>\n#include <limits>\n#include <numeric>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\n// Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type\
    \ b, typename AM::operator_type f,\n                                 typename\
    \ AM::operator_type g) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \  // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n//\
    \ Concept for acted monoids whose value monoid is a commutative group.\n// The\
    \ value operation must obey commutativity and inverse laws.\ntemplate <typename\
    \ AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM> && requires(typename\
    \ AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename AM::value_type>;\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing\
    \ dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
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
    \n\n#line 15 \"ds/segtree/dynamic_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// A sparse lazy segment tree over an integral half-open interval.\n\
    template <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral Index\
    \ = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct\
    \ DynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n    using\
    \ F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n  \
    \  using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        bool has_lazy;\n\n        explicit Node(T value)\n            : val(std::move(value)),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(0),\n         \
    \     right(0),\n              has_lazy(false) {}\n    };\n\n    detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> _domain;\n    int _root;\n    std::vector<Node> _nodes;\n\n    int new_node(Index\
    \ left, Index right, int depth) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(_domain.default_product(depth, left, right));\n \
    \       return int(_nodes.size()) - 1;\n    }\n\n    const T& value(int t, Index\
    \ left, Index right, int depth) const {\n        if (t) return _nodes[t].val;\n\
    \        return _domain.default_product(depth, left, right);\n    }\n\n    void\
    \ all_apply(int& t, Index left, Index right, int depth, const F& f) {\n      \
    \  if (!t) t = new_node(left, right, depth);\n        Node& node = _nodes[t];\n\
    \        node.val = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n     \
    \   if (std::midpoint(left, right) != left) {\n            node.lazy = ActedMonoid::op_comp(f,\
    \ node.lazy);\n            node.has_lazy = true;\n        }\n    }\n\n    void\
    \ push(int t, Index left, Index right, int depth) {\n        if (!_nodes[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        F lazy = _nodes[t].lazy;\n        int left_child\
    \ = _nodes[t].left;\n        int right_child = _nodes[t].right;\n        all_apply(left_child,\
    \ left, middle, depth + 1, lazy);\n        all_apply(\n            right_child,\n\
    \            middle,\n            right,\n            depth + 1,\n           \
    \ detail::dynamic_shift<ActedMonoid>(lazy, detail::dynamic_distance(left, middle))\n\
    \        );\n\n        Node& node = _nodes[t];\n        node.left = left_child;\n\
    \        node.right = right_child;\n        node.lazy = ActedMonoid::op_id();\n\
    \        node.has_lazy = false;\n    }\n\n    void update(int t, Index left, Index\
    \ right, int depth) {\n        Index middle = std::midpoint(left, right);\n  \
    \      _nodes[t].val = ActedMonoid::op(\n            value(_nodes[t].left, left,\
    \ middle, depth + 1),\n            value(_nodes[t].right, middle, right, depth\
    \ + 1)\n        );\n    }\n\n    int set_node(int t, Index left, Index right,\
    \ int depth, Index p, T x) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ {\n            Node& node = _nodes[t];\n            node.val = std::move(x);\n\
    \            node.lazy = ActedMonoid::op_id();\n            node.has_lazy = false;\n\
    \            return t;\n        }\n\n        push(t, left, right, depth);\n  \
    \      if (p < middle) {\n            int child = set_node(_nodes[t].left, left,\
    \ middle, depth + 1, p, std::move(x));\n            _nodes[t].left = child;\n\
    \        } else {\n            int child = set_node(_nodes[t].right, middle, right,\
    \ depth + 1, p, std::move(x));\n            _nodes[t].right = child;\n       \
    \ }\n        update(t, left, right, depth);\n        return t;\n    }\n\n    int\
    \ apply_node(\n        int t,\n        Index left,\n        Index right,\n   \
    \     int depth,\n        Index query_left,\n        Index query_right,\n    \
    \    const F& f\n    ) {\n        if (query_right <= left || right <= query_left)\
    \ return t;\n        if (query_left <= left && right <= query_right) {\n     \
    \       all_apply(\n                t,\n                left,\n              \
    \  right,\n                depth,\n                detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left))\n            );\n            return\
    \ t;\n        }\n\n        if (!t) t = new_node(left, right, depth);\n       \
    \ push(t, left, right, depth);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node(_nodes[t].left, left, middle, depth + 1,\
    \ query_left, query_right, f);\n        int right_child = apply_node(_nodes[t].right,\
    \ middle, right, depth + 1, query_left, query_right, f);\n        _nodes[t].left\
    \ = left_child;\n        _nodes[t].right = right_child;\n        update(t, left,\
    \ right, depth);\n        return t;\n    }\n\n    F compose_for_child(const F&\
    \ inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !_nodes[t].has_lazy) return shifted;\n        return\
    \ ActedMonoid::op_comp(\n            shifted,\n            detail::dynamic_shift<ActedMonoid>(_nodes[t].lazy,\
    \ offset)\n        );\n    }\n\n    T prod_node(\n        int t,\n        Index\
    \ left,\n        Index right,\n        int depth,\n        Index query_left,\n\
    \        Index query_right,\n        const F& inherited\n    ) const {\n     \
    \   if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(\n                inherited,\n        \
    \        value(t, left, right, depth)\n            );\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        return ActedMonoid::op(\n    \
    \        prod_node(\n                t ? _nodes[t].left : 0,\n               \
    \ left,\n                middle,\n                depth + 1,\n               \
    \ query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ t, 0)\n            ),\n            prod_node(\n                t ? _nodes[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right,\n          \
    \      compose_for_child(inherited, t, detail::dynamic_distance(left, middle))\n\
    \            )\n        );\n    }\n\n    template <class G>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        const F& inherited,\n\
    \        G& predicate\n    ) const {\n        if (right <= query_left) return\
    \ right;\n        if (query_left <= left) {\n            T next = ActedMonoid::op(\n\
    \                product,\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                )\n            );\n            if (predicate(next)) {\n     \
    \           product = std::move(next);\n                return right;\n      \
    \      }\n            Index middle = std::midpoint(left, right);\n           \
    \ if (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(\n            t ? _nodes[t].left\
    \ : 0,\n            left,\n            middle,\n            depth + 1,\n     \
    \       query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, 0),\n            predicate\n        );\n        if (result < middle) return\
    \ result;\n        return max_right_node(\n            t ? _nodes[t].right : 0,\n\
    \            middle,\n            right,\n            depth + 1,\n           \
    \ query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n    }\n\n    template <class G>\n    Index min_left_node(\n        int t,\n\
    \        Index left,\n        Index right,\n        int depth,\n        Index\
    \ query_right,\n        T& product,\n        const F& inherited,\n        G& predicate\n\
    \    ) const {\n        if (query_right <= left) return left;\n        if (right\
    \ <= query_right) {\n            T next = ActedMonoid::op(\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                ),\n                product\n            );\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = min_left_node(\n            t ? _nodes[t].right\
    \ : 0,\n            middle,\n            right,\n            depth + 1,\n    \
    \        query_right,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n        if (middle < result) return result;\n        return min_left_node(\n\
    \            t ? _nodes[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_right,\n            product,\n    \
    \        compose_for_child(inherited, t, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    DynamicLazySegtree()\n        : DynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit DynamicLazySegtree(Index n)\n\
    \        : DynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n        if constexpr\
    \ (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n    DynamicLazySegtree(Index\
    \ left, Index right)\n        : DynamicLazySegtree(left, right, ActedMonoid::id())\
    \ {}\n\n    DynamicLazySegtree(Index left, Index right, T initial_value)\n   \
    \     : _domain(left, right, std::move(initial_value)), _root(0) {\n        _nodes.emplace_back(ActedMonoid::id());\n\
    \    }\n\n    size_type size() const {\n        return _domain.size();\n    }\n\
    \n    bool empty() const {\n        return _domain.empty();\n    }\n\n    Index\
    \ left_bound() const {\n        return _domain.left_bound();\n    }\n\n    Index\
    \ right_bound() const {\n        return _domain.right_bound();\n    }\n\n    const\
    \ T& initial_value() const {\n        return _domain.initial_value();\n    }\n\
    \n    void reserve(std::size_t node_capacity) {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _nodes.reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _nodes.size()\
    \ - 1;\n    }\n\n    void clear() {\n        _root = 0;\n        _nodes.erase(_nodes.begin()\
    \ + 1, _nodes.end());\n    }\n\n    void set(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        _root = set_node(_root, left_bound(), right_bound(),\
    \ 0, p, std::move(x));\n    }\n\n    T get(Index p) const {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        return prod(p, p + 1);\n    }\n\n    T\
    \ operator[](Index p) const {\n        return get(p);\n    }\n\n    T prod(Index\
    \ left, Index right) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return ActedMonoid::id();\n\
    \        return prod_node(\n            _root,\n            left_bound(),\n  \
    \          right_bound(),\n            0,\n            left,\n            right,\n\
    \            ActedMonoid::op_id()\n        );\n    }\n\n    T all_prod() const\
    \ {\n        return value(_root, left_bound(), right_bound(), 0);\n    }\n\n \
    \   void apply(Index p, const F& f) {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        apply(p, p + 1, f);\n    }\n\n    void apply(Index\
    \ left, Index right, const F& f) {\n        assert(left_bound() <= left && left\
    \ <= right && right <= right_bound());\n        if (left == right) return;\n \
    \       _root = apply_node(\n            _root,\n            left_bound(),\n \
    \           right_bound(),\n            0,\n            left,\n            right,\n\
    \            f\n        );\n    }\n\n    template <class G>\n    Index max_right(Index\
    \ left, G predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(\n            _root,\n            left_bound(),\n           \
    \ right_bound(),\n            0,\n            left,\n            product,\n  \
    \          ActedMonoid::op_id(),\n            predicate\n        );\n    }\n\n\
    \    template <class G>\n    Index min_left(Index right, G predicate) const {\n\
    \        assert(left_bound() <= right && right <= right_bound());\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ ActedMonoid::id();\n        return min_left_node(\n            _root,\n    \
    \        left_bound(),\n            right_bound(),\n            0,\n         \
    \   right,\n            product,\n            ActedMonoid::op_id(),\n        \
    \    predicate\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/segtree/dynamic_lazy_segtree.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/ds/segtree/dynamic_lazy_segtree.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 10 \"verify/ds/segtree/dynamic_lazy_segtree.test.cpp\"\
    \n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size};\n\
    \    }\n    static constexpr value_type inv(const value_type& x) {\n        return\
    \ {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n    static constexpr\
    \ operator_type op_id() {\n        return 0;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    // Mapping (sum + f * size)\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        return {x.sum\
    \ + f * x.size, x.size};\n    }\n\n    // Helper for initializing a leaf node\n\
    \    static constexpr value_type make(const T& val) {\n        return {val, 1};\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1\
    \ \"acted_monoid/range_affine_range_sum.hpp\"\n\n\n\n#line 5 \"acted_monoid/range_affine_range_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n};\n\n// Designed\
    \ to accept Modint or similar types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum\
    \ {\n    using value_type = RangeAffineRangeSumNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;  // {a, b} for ax + b\n\n    // Value Monoid\n    static\
    \ constexpr value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n\
    \    // f(x) = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) +\
    \ b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n\
    \        return {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first * g.first,\
    \ f.first * g.second + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i\
    \ + b) = a * \\sum x_i + b * size\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return {f.first * x.sum +\
    \ f.second * T(x.size), x.size};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n\
    #line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\n\n\n#line 5 \"acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n    T ord_sum;\n\
    };\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n    using value_type\
    \ = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0, T(0)};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size, a.ord_sum + b.ord_sum + T(a.size) * T(b.size)};\n\
    \    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return {T(0), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first + g.first,\
    \ f.second + g.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return mapping(f, x, 0);\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x, long long ord) {\n        return {x.sum + f.first * (x.ord_sum\
    \ + T(ord) * T(x.size)) + f.second * T(x.size), x.size, x.ord_sum};\n    }\n\n\
    \    static constexpr operator_type op_shift(const operator_type& f, long long\
    \ ord) {\n        return {f.first, f.second + f.first * T(ord)};\n    }\n\n  \
    \  static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        return {-f.first, f.second + f.first * T(size - 1)};\n    }\n\
    \n    static constexpr value_type make(const T& val) {\n        return {val, 1,\
    \ T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    \n#line 1 \"math/modint.hpp\"\n\n\n\n#line 8 \"math/modint.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n\
    \    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
    \    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod() {\n     \
    \   return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept\
    \ {\n        ModInt x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr\
    \ ModInt() noexcept : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 15 \"verify/ds/segtree/dynamic_lazy_segtree.test.cpp\"\n\n\
    namespace {\n\nvoid test_range_add() {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n    using Seg = m1une::ds::DynamicLazySegtree<AM>;\n\n    Seg seg(-1'000'000'000'000'000'000LL,\
    \ 1'000'000'000'000'000'000LL, AM::make(0));\n    assert(seg.size() == 2'000'000'000'000'000'000ULL);\n\
    \    assert(seg.node_count() == 0);\n    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);\n\
    \n    seg.reserve(1024);\n    seg.apply(-3, 5, 2);\n    assert(seg.prod(-10, 10).sum\
    \ == 16);\n    assert(seg.get(-3).sum == 2);\n    assert(seg.get(5).sum == 0);\n\
    \n    [[maybe_unused]] std::size_t nodes = seg.node_count();\n    seg.set(0, AM::make(10));\n\
    \    assert(seg.all_prod().sum == 24);\n    assert(seg.max_right(-10, [](const\
    \ AM::value_type& x) { return x.sum <= 5; }) == -1);\n    assert(seg.min_left(10,\
    \ [](const AM::value_type& x) { return x.sum <= 5; }) == 3);\n    assert(seg.node_count()\
    \ >= nodes);\n\n    seg.clear();\n    assert(seg.node_count() == 0);\n    assert(seg.all_prod().sum\
    \ == 0);\n    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);\n}\n\
    \nvoid test_arithmetic_progression() {\n    using AM = m1une::acted_monoid::RangeApAddRangeSum<long\
    \ long>;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(-20, 21, AM::make(0));\n\
    \n    AM::operator_type first;\n    first.first = 2;\n    first.second = 3;\n\
    \    seg.apply(-5, 6, first);\n    for (int p = -5; p < 6; p++) {\n        assert(seg.get(p).sum\
    \ == 2LL * (p + 5) + 3);\n    }\n\n    AM::operator_type second;\n    second.first\
    \ = -1;\n    second.second = 4;\n    seg.apply(-2, 4, second);\n    [[maybe_unused]]\
    \ long long expected = 0;\n    for (int p = -20; p < 21; p++) {\n        long\
    \ long value = 0;\n        if (-5 <= p && p < 6) value += 2LL * (p + 5) + 3;\n\
    \        if (-2 <= p && p < 4) value += -(p + 2) + 4;\n        expected += value;\n\
    \    }\n    assert(seg.all_prod().sum == expected);\n}\n\nvoid test_randomized()\
    \ {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;\n    constexpr\
    \ int left = -31;\n    constexpr int right = 38;\n    m1une::ds::DynamicLazySegtree<AM,\
    \ int> seg(left, right, AM::make(0));\n    std::vector<long long> a(right - left);\n\
    \n    std::uint64_t state = 1;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \    auto value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p\
    \ - left)];\n    };\n\n    for (int step = 0; step < 3000; step++) {\n       \
    \ int type = int(random() % 4);\n        int l = left + int(random() % (a.size()\
    \ + 1));\n        int r = left + int(random() % (a.size() + 1));\n        if (r\
    \ < l) std::swap(l, r);\n\n        if (type == 0) {\n            long long x =\
    \ static_cast<long long>(random() % 11);\n            seg.apply(l, r, x);\n  \
    \          for (int p = l; p < r; p++) value_at(p) += x;\n        } else if (type\
    \ == 1) {\n            int p = left + int(random() % a.size());\n            long\
    \ long x = static_cast<long long>(random() % 30);\n            seg.set(p, AM::make(x));\n\
    \            value_at(p) = x;\n        } else {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int p = l; p < r; p++) expected +=\
    \ value_at(p);\n            assert(seg.prod(l, r).sum == expected);\n        }\n\
    \n        long long limit = static_cast<long long>(random() % 150);\n        int\
    \ start = left + int(random() % (a.size() + 1));\n        int max_right = start;\n\
    \        long long sum = 0;\n        while (max_right < right && sum + value_at(max_right)\
    \ <= limit) {\n            sum += value_at(max_right);\n            max_right++;\n\
    \        }\n        assert(seg.max_right(start, [limit](const AM::value_type&\
    \ x) {\n            return x.sum <= limit;\n        }) == max_right);\n\n    \
    \    int finish = left + int(random() % (a.size() + 1));\n        int min_left\
    \ = finish;\n        sum = 0;\n        while (left < min_left && value_at(min_left\
    \ - 1) + sum <= limit) {\n            min_left--;\n            sum += value_at(min_left);\n\
    \        }\n        assert(seg.min_left(finish, [limit](const AM::value_type&\
    \ x) {\n            return x.sum <= limit;\n        }) == min_left);\n    }\n\
    }\n\nvoid test_affine_order() {\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    constexpr\
    \ int n = 37;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(0, n, AM::make(1));\n\
    \    std::vector<mint> a(n, 1);\n\n    std::uint64_t state = 11;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int step = 0; step < 1200; step++)\
    \ {\n        int l = int(random() % (n + 1));\n        int r = int(random() %\
    \ (n + 1));\n        if (r < l) std::swap(l, r);\n        mint b = mint(int(random()\
    \ % 7));\n        mint c = mint(int(random() % 7));\n        AM::operator_type\
    \ f;\n        f.first = b;\n        f.second = c;\n        seg.apply(l, r, f);\n\
    \        for (int p = l; p < r; p++) a[p] = b * a[p] + c;\n\n        int ql =\
    \ int(random() % (n + 1));\n        int qr = int(random() % (n + 1));\n      \
    \  if (qr < ql) std::swap(ql, qr);\n        mint expected = 0;\n        for (int\
    \ p = ql; p < qr; p++) expected += a[p];\n        assert(seg.prod(ql, qr).sum\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_range_add();\n    test_arithmetic_progression();\n\
    \    test_randomized();\n    test_affine_order();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(0,\
    \ n, AM::make(0));\n    seg.reserve(std::size_t(4) * std::size_t(n + q));\n\n\
    \    for (int i = 0; i < n; i++) {\n        long long x;\n        std::cin >>\
    \ x;\n        seg.set(i, AM::make(mint(x)));\n    }\n\n    for (int query = 0;\
    \ query < q; query++) {\n        int type;\n        std::cin >> type;\n      \
    \  if (type == 0) {\n            int l, r;\n            long long b, c;\n    \
    \        std::cin >> l >> r >> b >> c;\n            AM::operator_type f;\n   \
    \         f.first = mint(b);\n            f.second = mint(c);\n            seg.apply(l,\
    \ r, f);\n        } else {\n            int l, r;\n            std::cin >> l >>\
    \ r;\n            std::cout << seg.prod(l, r).sum << '\\n';\n        }\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../../ds/segtree/dynamic_lazy_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \n#include \"../../../acted_monoid/range_add_range_sum.hpp\"\n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\
    \n#include \"../../../acted_monoid/range_ap_add_range_sum.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nnamespace {\n\nvoid test_range_add() {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n    using Seg = m1une::ds::DynamicLazySegtree<AM>;\n\n    Seg seg(-1'000'000'000'000'000'000LL,\
    \ 1'000'000'000'000'000'000LL, AM::make(0));\n    assert(seg.size() == 2'000'000'000'000'000'000ULL);\n\
    \    assert(seg.node_count() == 0);\n    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);\n\
    \n    seg.reserve(1024);\n    seg.apply(-3, 5, 2);\n    assert(seg.prod(-10, 10).sum\
    \ == 16);\n    assert(seg.get(-3).sum == 2);\n    assert(seg.get(5).sum == 0);\n\
    \n    [[maybe_unused]] std::size_t nodes = seg.node_count();\n    seg.set(0, AM::make(10));\n\
    \    assert(seg.all_prod().sum == 24);\n    assert(seg.max_right(-10, [](const\
    \ AM::value_type& x) { return x.sum <= 5; }) == -1);\n    assert(seg.min_left(10,\
    \ [](const AM::value_type& x) { return x.sum <= 5; }) == 3);\n    assert(seg.node_count()\
    \ >= nodes);\n\n    seg.clear();\n    assert(seg.node_count() == 0);\n    assert(seg.all_prod().sum\
    \ == 0);\n    assert(seg.all_prod().size == 2'000'000'000'000'000'000LL);\n}\n\
    \nvoid test_arithmetic_progression() {\n    using AM = m1une::acted_monoid::RangeApAddRangeSum<long\
    \ long>;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(-20, 21, AM::make(0));\n\
    \n    AM::operator_type first;\n    first.first = 2;\n    first.second = 3;\n\
    \    seg.apply(-5, 6, first);\n    for (int p = -5; p < 6; p++) {\n        assert(seg.get(p).sum\
    \ == 2LL * (p + 5) + 3);\n    }\n\n    AM::operator_type second;\n    second.first\
    \ = -1;\n    second.second = 4;\n    seg.apply(-2, 4, second);\n    [[maybe_unused]]\
    \ long long expected = 0;\n    for (int p = -20; p < 21; p++) {\n        long\
    \ long value = 0;\n        if (-5 <= p && p < 6) value += 2LL * (p + 5) + 3;\n\
    \        if (-2 <= p && p < 4) value += -(p + 2) + 4;\n        expected += value;\n\
    \    }\n    assert(seg.all_prod().sum == expected);\n}\n\nvoid test_randomized()\
    \ {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;\n    constexpr\
    \ int left = -31;\n    constexpr int right = 38;\n    m1une::ds::DynamicLazySegtree<AM,\
    \ int> seg(left, right, AM::make(0));\n    std::vector<long long> a(right - left);\n\
    \n    std::uint64_t state = 1;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \    auto value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p\
    \ - left)];\n    };\n\n    for (int step = 0; step < 3000; step++) {\n       \
    \ int type = int(random() % 4);\n        int l = left + int(random() % (a.size()\
    \ + 1));\n        int r = left + int(random() % (a.size() + 1));\n        if (r\
    \ < l) std::swap(l, r);\n\n        if (type == 0) {\n            long long x =\
    \ static_cast<long long>(random() % 11);\n            seg.apply(l, r, x);\n  \
    \          for (int p = l; p < r; p++) value_at(p) += x;\n        } else if (type\
    \ == 1) {\n            int p = left + int(random() % a.size());\n            long\
    \ long x = static_cast<long long>(random() % 30);\n            seg.set(p, AM::make(x));\n\
    \            value_at(p) = x;\n        } else {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int p = l; p < r; p++) expected +=\
    \ value_at(p);\n            assert(seg.prod(l, r).sum == expected);\n        }\n\
    \n        long long limit = static_cast<long long>(random() % 150);\n        int\
    \ start = left + int(random() % (a.size() + 1));\n        int max_right = start;\n\
    \        long long sum = 0;\n        while (max_right < right && sum + value_at(max_right)\
    \ <= limit) {\n            sum += value_at(max_right);\n            max_right++;\n\
    \        }\n        assert(seg.max_right(start, [limit](const AM::value_type&\
    \ x) {\n            return x.sum <= limit;\n        }) == max_right);\n\n    \
    \    int finish = left + int(random() % (a.size() + 1));\n        int min_left\
    \ = finish;\n        sum = 0;\n        while (left < min_left && value_at(min_left\
    \ - 1) + sum <= limit) {\n            min_left--;\n            sum += value_at(min_left);\n\
    \        }\n        assert(seg.min_left(finish, [limit](const AM::value_type&\
    \ x) {\n            return x.sum <= limit;\n        }) == min_left);\n    }\n\
    }\n\nvoid test_affine_order() {\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    constexpr\
    \ int n = 37;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(0, n, AM::make(1));\n\
    \    std::vector<mint> a(n, 1);\n\n    std::uint64_t state = 11;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int step = 0; step < 1200; step++)\
    \ {\n        int l = int(random() % (n + 1));\n        int r = int(random() %\
    \ (n + 1));\n        if (r < l) std::swap(l, r);\n        mint b = mint(int(random()\
    \ % 7));\n        mint c = mint(int(random() % 7));\n        AM::operator_type\
    \ f;\n        f.first = b;\n        f.second = c;\n        seg.apply(l, r, f);\n\
    \        for (int p = l; p < r; p++) a[p] = b * a[p] + c;\n\n        int ql =\
    \ int(random() % (n + 1));\n        int qr = int(random() % (n + 1));\n      \
    \  if (qr < ql) std::swap(ql, qr);\n        mint expected = 0;\n        for (int\
    \ p = ql; p < qr; p++) expected += a[p];\n        assert(seg.prod(ql, qr).sum\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_range_add();\n    test_arithmetic_progression();\n\
    \    test_randomized();\n    test_affine_order();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n    m1une::ds::DynamicLazySegtree<AM, int> seg(0,\
    \ n, AM::make(0));\n    seg.reserve(std::size_t(4) * std::size_t(n + q));\n\n\
    \    for (int i = 0; i < n; i++) {\n        long long x;\n        std::cin >>\
    \ x;\n        seg.set(i, AM::make(mint(x)));\n    }\n\n    for (int query = 0;\
    \ query < q; query++) {\n        int type;\n        std::cin >> type;\n      \
    \  if (type == 0) {\n            int l, r;\n            long long b, c;\n    \
    \        std::cin >> l >> r >> b >> c;\n            AM::operator_type f;\n   \
    \         f.first = mint(b);\n            f.second = mint(c);\n            seg.apply(l,\
    \ r, f);\n        } else {\n            int l, r;\n            std::cin >> l >>\
    \ r;\n            std::cout << seg.prod(l, r).sum << '\\n';\n        }\n    }\n\
    }\n"
  dependsOn:
  - ds/segtree/dynamic_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - acted_monoid/range_add_range_sum.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - acted_monoid/range_ap_add_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dynamic_lazy_segtree.test.cpp
- /verify/verify/ds/segtree/dynamic_lazy_segtree.test.cpp.html
title: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
---
