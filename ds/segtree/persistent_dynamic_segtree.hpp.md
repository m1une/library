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
    path: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/persistent_dynamic_segtree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n#include\
    \ <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n#line 11\
    \ \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing dynamic_size_type\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 16 \"ds/segtree/persistent_dynamic_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A persistent sparse segment tree over\
    \ an integral half-open interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct PersistentDynamicSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ left(0), right(0) {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<Monoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value)\n\
    \            : domain(left, right, std::move(initial_value)) {}\n    };\n\n  \
    \  std::shared_ptr<const Config> _config;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicSegtree(\n        std::shared_ptr<const\
    \ Config> config,\n        std::shared_ptr<std::vector<Node>> pool,\n        int\
    \ root\n    ) : _config(std::move(config)), _pool(std::move(pool)), _root(root)\
    \ {}\n\n    int new_node(T value) const {\n        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _pool->emplace_back(std::move(value));\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    const T& value(int t, Index left, Index right, int depth)\
    \ const {\n        if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    int set_node(int t, Index left, Index right, int\
    \ depth, Index p, T x) const {\n        Index middle = std::midpoint(left, right);\n\
    \        if (middle == left) return new_node(std::move(x));\n\n        int left_child\
    \ = t ? (*_pool)[t].left : 0;\n        int right_child = t ? (*_pool)[t].right\
    \ : 0;\n        if (p < middle) {\n            left_child = set_node(\n      \
    \          left_child,\n                left,\n                middle,\n     \
    \           depth + 1,\n                p,\n                std::move(x)\n   \
    \         );\n        } else {\n            right_child = set_node(\n        \
    \        right_child,\n                middle,\n                right,\n     \
    \           depth + 1,\n                p,\n                std::move(x)\n   \
    \         );\n        }\n\n        int result = new_node(Monoid::op(\n       \
    \     value(left_child, left, middle, depth + 1),\n            value(right_child,\
    \ middle, right, depth + 1)\n        ));\n        (*_pool)[result].left = left_child;\n\
    \        (*_pool)[result].right = right_child;\n        return result;\n    }\n\
    \n    T prod_node(\n        int t,\n        Index left,\n        Index right,\n\
    \        int depth,\n        Index query_left,\n        Index query_right\n  \
    \  ) const {\n        if (query_right <= left || right <= query_left) return Monoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ value(t, left, right, depth);\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        return Monoid::op(\n            prod_node(\n              \
    \  t ? (*_pool)[t].left : 0,\n                left,\n                middle,\n\
    \                depth + 1,\n                query_left,\n                query_right\n\
    \            ),\n            prod_node(\n                t ? (*_pool)[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right\n           \
    \ )\n        );\n    }\n\n    template <class F>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        F& predicate\n    ) const\
    \ {\n        if (right <= query_left) return right;\n        if (query_left <=\
    \ left) {\n            T next = Monoid::op(product, value(t, left, right, depth));\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return right;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return left;\n        }\n\n       \
    \ Index middle = std::midpoint(left, right);\n        Index result = max_right_node(\n\
    \            t ? (*_pool)[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_left,\n            product,\n     \
    \       predicate\n        );\n        if (result < middle) return result;\n \
    \       return max_right_node(\n            t ? (*_pool)[t].right : 0,\n     \
    \       middle,\n            right,\n            depth + 1,\n            query_left,\n\
    \            product,\n            predicate\n        );\n    }\n\n    template\
    \ <class F>\n    Index min_left_node(\n        int t,\n        Index left,\n \
    \       Index right,\n        int depth,\n        Index query_right,\n       \
    \ T& product,\n        F& predicate\n    ) const {\n        if (query_right <=\
    \ left) return left;\n        if (right <= query_right) {\n            T next\
    \ = Monoid::op(value(t, left, right, depth), product);\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n\n        Index middle =\
    \ std::midpoint(left, right);\n        Index result = min_left_node(\n       \
    \     t ? (*_pool)[t].right : 0,\n            middle,\n            right,\n  \
    \          depth + 1,\n            query_right,\n            product,\n      \
    \      predicate\n        );\n        if (middle < result) return result;\n  \
    \      return min_left_node(\n            t ? (*_pool)[t].left : 0,\n        \
    \    left,\n            middle,\n            depth + 1,\n            query_right,\n\
    \            product,\n            predicate\n        );\n    }\n\n   public:\n\
    \    PersistentDynamicSegtree()\n        : PersistentDynamicSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n\n    explicit PersistentDynamicSegtree(Index n)\n\
    \        : PersistentDynamicSegtree(Index(0), n, Monoid::id()) {\n        if constexpr\
    \ (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n    PersistentDynamicSegtree(Index\
    \ left, Index right)\n        : PersistentDynamicSegtree(left, right, Monoid::id())\
    \ {}\n\n    PersistentDynamicSegtree(Index left, Index right, T initial_value)\n\
    \        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),\n\
    \          _pool(std::make_shared<std::vector<Node>>()),\n          _root(0) {\n\
    \        _pool->emplace_back(Monoid::id());\n    }\n\n    size_type size() const\
    \ {\n        return _config->domain.size();\n    }\n\n    bool empty() const {\n\
    \        return _config->domain.empty();\n    }\n\n    Index left_bound() const\
    \ {\n        return _config->domain.left_bound();\n    }\n\n    Index right_bound()\
    \ const {\n        return _config->domain.right_bound();\n    }\n\n    const T&\
    \ initial_value() const {\n        return _config->domain.initial_value();\n \
    \   }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _pool->size()\
    \ - 1;\n    }\n\n    PersistentDynamicSegtree set(Index p, T x) const {\n    \
    \    assert(left_bound() <= p && p < right_bound());\n        return PersistentDynamicSegtree(\n\
    \            _config,\n            _pool,\n            set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x))\n        );\n    }\n\n    T get(Index p)\
    \ const {\n        assert(left_bound() <= p && p < right_bound());\n        int\
    \ t = _root;\n        Index left = left_bound();\n        Index right = right_bound();\n\
    \n        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) return (*_pool)[t].val;\n            if (p <\
    \ middle) {\n                t = (*_pool)[t].left;\n                right = middle;\n\
    \            } else {\n                t = (*_pool)[t].right;\n              \
    \  left = middle;\n            }\n        }\n        return initial_value();\n\
    \    }\n\n    T operator[](Index p) const {\n        return get(p);\n    }\n\n\
    \    T prod(Index left, Index right) const {\n        assert(left_bound() <= left\
    \ && left <= right && right <= right_bound());\n        if (left == right) return\
    \ Monoid::id();\n        return prod_node(\n            _root,\n            left_bound(),\n\
    \            right_bound(),\n            0,\n            left,\n            right\n\
    \        );\n    }\n\n    T all_prod() const {\n        return value(_root, left_bound(),\
    \ right_bound(), 0);\n    }\n\n    template <class F>\n    Index max_right(Index\
    \ left, F predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(Monoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = Monoid::id();\n        return max_right_node(\n\
    \            _root,\n            left_bound(),\n            right_bound(),\n \
    \           0,\n            left,\n            product,\n            predicate\n\
    \        );\n    }\n\n    template <class F>\n    Index min_left(Index right,\
    \ F predicate) const {\n        assert(left_bound() <= right && right <= right_bound());\n\
    \        assert(predicate(Monoid::id()));\n        if (right == left_bound())\
    \ return left_bound();\n        T product = Monoid::id();\n        return min_left_node(\n\
    \            _root,\n            left_bound(),\n            right_bound(),\n \
    \           0,\n            right,\n            product,\n            predicate\n\
    \        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"ds/segtree/dynamic_segtree_common.hpp\"\n#include\
    \ \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n// A persistent\
    \ sparse segment tree over an integral half-open interval.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid, std::integral Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct PersistentDynamicSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ left(0), right(0) {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<Monoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value)\n\
    \            : domain(left, right, std::move(initial_value)) {}\n    };\n\n  \
    \  std::shared_ptr<const Config> _config;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicSegtree(\n        std::shared_ptr<const\
    \ Config> config,\n        std::shared_ptr<std::vector<Node>> pool,\n        int\
    \ root\n    ) : _config(std::move(config)), _pool(std::move(pool)), _root(root)\
    \ {}\n\n    int new_node(T value) const {\n        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _pool->emplace_back(std::move(value));\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    const T& value(int t, Index left, Index right, int depth)\
    \ const {\n        if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    int set_node(int t, Index left, Index right, int\
    \ depth, Index p, T x) const {\n        Index middle = std::midpoint(left, right);\n\
    \        if (middle == left) return new_node(std::move(x));\n\n        int left_child\
    \ = t ? (*_pool)[t].left : 0;\n        int right_child = t ? (*_pool)[t].right\
    \ : 0;\n        if (p < middle) {\n            left_child = set_node(\n      \
    \          left_child,\n                left,\n                middle,\n     \
    \           depth + 1,\n                p,\n                std::move(x)\n   \
    \         );\n        } else {\n            right_child = set_node(\n        \
    \        right_child,\n                middle,\n                right,\n     \
    \           depth + 1,\n                p,\n                std::move(x)\n   \
    \         );\n        }\n\n        int result = new_node(Monoid::op(\n       \
    \     value(left_child, left, middle, depth + 1),\n            value(right_child,\
    \ middle, right, depth + 1)\n        ));\n        (*_pool)[result].left = left_child;\n\
    \        (*_pool)[result].right = right_child;\n        return result;\n    }\n\
    \n    T prod_node(\n        int t,\n        Index left,\n        Index right,\n\
    \        int depth,\n        Index query_left,\n        Index query_right\n  \
    \  ) const {\n        if (query_right <= left || right <= query_left) return Monoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ value(t, left, right, depth);\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        return Monoid::op(\n            prod_node(\n              \
    \  t ? (*_pool)[t].left : 0,\n                left,\n                middle,\n\
    \                depth + 1,\n                query_left,\n                query_right\n\
    \            ),\n            prod_node(\n                t ? (*_pool)[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right\n           \
    \ )\n        );\n    }\n\n    template <class F>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        F& predicate\n    ) const\
    \ {\n        if (right <= query_left) return right;\n        if (query_left <=\
    \ left) {\n            T next = Monoid::op(product, value(t, left, right, depth));\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return right;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return left;\n        }\n\n       \
    \ Index middle = std::midpoint(left, right);\n        Index result = max_right_node(\n\
    \            t ? (*_pool)[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_left,\n            product,\n     \
    \       predicate\n        );\n        if (result < middle) return result;\n \
    \       return max_right_node(\n            t ? (*_pool)[t].right : 0,\n     \
    \       middle,\n            right,\n            depth + 1,\n            query_left,\n\
    \            product,\n            predicate\n        );\n    }\n\n    template\
    \ <class F>\n    Index min_left_node(\n        int t,\n        Index left,\n \
    \       Index right,\n        int depth,\n        Index query_right,\n       \
    \ T& product,\n        F& predicate\n    ) const {\n        if (query_right <=\
    \ left) return left;\n        if (right <= query_right) {\n            T next\
    \ = Monoid::op(value(t, left, right, depth), product);\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n\n        Index middle =\
    \ std::midpoint(left, right);\n        Index result = min_left_node(\n       \
    \     t ? (*_pool)[t].right : 0,\n            middle,\n            right,\n  \
    \          depth + 1,\n            query_right,\n            product,\n      \
    \      predicate\n        );\n        if (middle < result) return result;\n  \
    \      return min_left_node(\n            t ? (*_pool)[t].left : 0,\n        \
    \    left,\n            middle,\n            depth + 1,\n            query_right,\n\
    \            product,\n            predicate\n        );\n    }\n\n   public:\n\
    \    PersistentDynamicSegtree()\n        : PersistentDynamicSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n\n    explicit PersistentDynamicSegtree(Index n)\n\
    \        : PersistentDynamicSegtree(Index(0), n, Monoid::id()) {\n        if constexpr\
    \ (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n    PersistentDynamicSegtree(Index\
    \ left, Index right)\n        : PersistentDynamicSegtree(left, right, Monoid::id())\
    \ {}\n\n    PersistentDynamicSegtree(Index left, Index right, T initial_value)\n\
    \        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),\n\
    \          _pool(std::make_shared<std::vector<Node>>()),\n          _root(0) {\n\
    \        _pool->emplace_back(Monoid::id());\n    }\n\n    size_type size() const\
    \ {\n        return _config->domain.size();\n    }\n\n    bool empty() const {\n\
    \        return _config->domain.empty();\n    }\n\n    Index left_bound() const\
    \ {\n        return _config->domain.left_bound();\n    }\n\n    Index right_bound()\
    \ const {\n        return _config->domain.right_bound();\n    }\n\n    const T&\
    \ initial_value() const {\n        return _config->domain.initial_value();\n \
    \   }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _pool->size()\
    \ - 1;\n    }\n\n    PersistentDynamicSegtree set(Index p, T x) const {\n    \
    \    assert(left_bound() <= p && p < right_bound());\n        return PersistentDynamicSegtree(\n\
    \            _config,\n            _pool,\n            set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x))\n        );\n    }\n\n    T get(Index p)\
    \ const {\n        assert(left_bound() <= p && p < right_bound());\n        int\
    \ t = _root;\n        Index left = left_bound();\n        Index right = right_bound();\n\
    \n        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) return (*_pool)[t].val;\n            if (p <\
    \ middle) {\n                t = (*_pool)[t].left;\n                right = middle;\n\
    \            } else {\n                t = (*_pool)[t].right;\n              \
    \  left = middle;\n            }\n        }\n        return initial_value();\n\
    \    }\n\n    T operator[](Index p) const {\n        return get(p);\n    }\n\n\
    \    T prod(Index left, Index right) const {\n        assert(left_bound() <= left\
    \ && left <= right && right <= right_bound());\n        if (left == right) return\
    \ Monoid::id();\n        return prod_node(\n            _root,\n            left_bound(),\n\
    \            right_bound(),\n            0,\n            left,\n            right\n\
    \        );\n    }\n\n    T all_prod() const {\n        return value(_root, left_bound(),\
    \ right_bound(), 0);\n    }\n\n    template <class F>\n    Index max_right(Index\
    \ left, F predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(Monoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = Monoid::id();\n        return max_right_node(\n\
    \            _root,\n            left_bound(),\n            right_bound(),\n \
    \           0,\n            left,\n            product,\n            predicate\n\
    \        );\n    }\n\n    template <class F>\n    Index min_left(Index right,\
    \ F predicate) const {\n        assert(left_bound() <= right && right <= right_bound());\n\
    \        assert(predicate(Monoid::id()));\n        if (right == left_bound())\
    \ return left_bound();\n        T product = Monoid::id();\n        return min_left_node(\n\
    \            _root,\n            left_bound(),\n            right_bound(),\n \
    \           0,\n            right,\n            product,\n            predicate\n\
    \        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP\n"
  dependsOn:
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/persistent_dynamic_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-21 02:09:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/persistent_dynamic_segtree.test.cpp
documentation_of: ds/segtree/persistent_dynamic_segtree.hpp
layout: document
title: Persistent Dynamic Segment Tree
---

## Overview

`m1une::ds::PersistentDynamicSegtree` is a persistent sparse segment tree over
a fixed integer coordinate domain. Point assignments return new versions while
older versions remain available. It supports monoid range products and boundary
searches without building the entire domain.

Every coordinate starts with the same `initial_value`. Products of untouched
segments are derived from that leaf value, so a large uniform array can remain
implicit. The default initial value is `Monoid::id()`, which gives the usual
sparse-map behavior.

All related versions share immutable domain metadata and one contiguous node
pool. Read-only queries do not allocate nodes. Products preserve coordinate
order, so non-commutative monoids are supported.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

## Construction

* `PersistentDynamicSegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicSegtree(Index n)`: creates `[0, n)` with identity values.
* `PersistentDynamicSegtree(Index left, Index right)`: creates
  `[left, right)` with identity values.
* `PersistentDynamicSegtree(Index left, Index right, T initial_value)`: creates
  a domain with the specified uniform initial leaf.

Construction caches the possible untouched segment products at each depth. It
uses $O(\log U)$ memory and $O(\log^2 U)$ monoid operations, where $U$ is the
domain length. No tree node is allocated initially.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns total nodes allocated by the shared version family. | $O(1)$ |
| `PersistentDynamicSegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `Index max_right(Index l, F f)` | Finds the largest `r` for which `f(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, F f)` | Finds the smallest `l` for which `f(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ counts allocations made by every version sharing the pool. Each
assignment allocates $O(\log U)$ nodes in the worst case. Copying a version is
$O(1)$.

For `max_right` and `min_left`, the identity must satisfy the predicate and the
predicate must be monotone along searched products.

## Example

```cpp
#include "ds/segtree/persistent_dynamic_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, 0);
    Seg first = base.set(-500'000'000LL, 7);
    Seg second = first.set(900'000'000LL, 11);

    std::cout << base.all_prod() << "\n";    // 0
    std::cout << first.all_prod() << "\n";   // 7
    std::cout << second.all_prod() << "\n";  // 18
}
```
