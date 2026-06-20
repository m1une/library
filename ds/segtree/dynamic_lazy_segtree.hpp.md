---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/dynamic_lazy_segtree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstddef>\n#include <limits>\n#include <numeric>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\
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
    \n\n"
  code: "#ifndef M1UNE_DYNAMIC_LAZY_SEGTREE_HPP\n#define M1UNE_DYNAMIC_LAZY_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#include \"acted_monoid/concept.hpp\"\n#include \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A sparse lazy segment tree over an\
    \ integral half-open interval.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid,\
    \ std::integral Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct DynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
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
    \n#endif  // M1UNE_DYNAMIC_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  isVerificationFile: false
  path: ds/segtree/dynamic_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-21 02:09:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dynamic_lazy_segtree.test.cpp
documentation_of: ds/segtree/dynamic_lazy_segtree.hpp
layout: document
title: Dynamic Lazy Segment Tree
---

## Overview

`m1une::ds::DynamicLazySegtree` is a sparse lazy segment tree over a fixed
integer coordinate domain. It supports point assignment, range updates, range
products, and boundary searches without allocating a dense array for the whole
domain.

Nodes use one contiguous pool and are created only for segments touched by an
update or assignment. Read-only operations do not push lazy tags or allocate
nodes.

## Untouched Coordinates

Every coordinate starts with the same `initial_value`. The tree computes the
monoid product of untouched segments from that leaf value. This detail matters
for size-aware acted monoids:

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::DynamicLazySegtree<AM> seg(0, 1'000'000'000LL, AM::make(0));
```

`AM::make(0)` represents one zero-valued element. In contrast, `AM::id()` has
size zero and represents an empty product, so range additions would not affect
untouched coordinates.

Products preserve coordinate order, so non-commutative value monoids are
supported when the acted-monoid laws hold.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

Position-dependent operators may additionally provide `op_shift(f, offset)`,
with the same semantics used by `LazySegtree`. Existing shifted acted monoids
use a `long long` offset, so every applied interval length must fit in
`long long` when `op_shift` is present.

## Construction

* `DynamicLazySegtree()`: creates an empty domain `[0, 0)`.
* `DynamicLazySegtree(Index n)`: creates `[0, n)` with initial leaf
  `ActedMonoid::id()`.
* `DynamicLazySegtree(Index left, Index right)`: creates `[left, right)` with
  initial leaf `ActedMonoid::id()`.
* `DynamicLazySegtree(Index left, Index right, T initial_value)`: creates a
  domain with the specified uniform initial leaf.

Construction precomputes untouched products for the possible segment lengths
at each depth. It uses $O(\log U)$ memory and $O(\log^2 U)$ monoid operations,
where $U$ is the number of coordinates.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the coordinate domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the domain's left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the domain's right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves space for `n` allocated nodes. | $O(K)$ |
| `size_t node_count()` | Returns the number of allocated nodes. | $O(1)$ |
| `void clear()` | Restores the uniform initial state while retaining capacity. | $O(K)$ |
| `void set(Index p, T x)` | Assigns `x` to coordinate `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the value-monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `void apply(Index p, F f)` | Applies `f` at one coordinate. | $O(\log U)$ |
| `void apply(Index l, Index r, F f)` | Applies `f` over `[l, r)`. | $O(\log U)$ |
| `Index max_right(Index l, G g)` | Finds the largest `r` for which `g(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, G g)` | Finds the smallest `l` for which `g(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ is the current number of allocated nodes. After $Q$ updates, memory
usage is $O(Q \log U)$ in the worst case. `max_right` and `min_left` require the
same predicate conditions as `LazySegtree`: the identity must satisfy the
predicate, and the predicate must be monotone along searched products.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/dynamic_lazy_segtree.hpp"

#include <iostream>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::DynamicLazySegtree<AM>;

    Seg seg(-1'000'000'000LL, 1'000'000'001LL, AM::make(0));
    seg.reserve(512);

    seg.apply(-20, 30, 5);
    seg.set(0, AM::make(100));

    std::cout << seg.prod(-10, 10).sum << "\n";  // 195
}
```
