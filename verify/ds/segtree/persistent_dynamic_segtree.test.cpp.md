---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_segtree.hpp
    title: Persistent Dynamic Segment Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/segtree/persistent_dynamic_segtree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <limits>\n#include <memory>\n#include <numeric>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
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
    \        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 10 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\
    \n#include <string>\n#line 12 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n\n    // Returns the identity element for addition, which\
    \ is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    //\
    \ Returns the sum of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T& x)\
    \ {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 14 \"verify/ds/segtree/persistent_dynamic_segtree.test.cpp\"\
    \n\nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n  \
    \  static value_type id() {\n        return \"\";\n    }\n\n    static value_type\
    \ op(const value_type& a, const value_type& b) {\n        return a + b;\n    }\n\
    };\n\nvoid test_versions() {\n    using Sum = m1une::monoid::Add<long long>;\n\
    \    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;\n\n    Seg base(-1'000'000'000'000'000'000LL,\
    \ 1'000'000'000'000'000'000LL, 0);\n    base.reserve(4096);\n    Seg first = base.set(-3,\
    \ 2);\n    Seg second = first.set(2, 4);\n    Seg branch = base.set(7, 10);\n\n\
    \    assert(base.size() == 2'000'000'000'000'000'000ULL);\n    assert(base.node_count()\
    \ == branch.node_count());\n    assert(base.all_prod() == 0);\n    assert(first.all_prod()\
    \ == 2);\n    assert(second.all_prod() == 6);\n    assert(branch.all_prod() ==\
    \ 10);\n    assert(base.get(-3) == 0);\n    assert(first.get(-3) == 2);\n    assert(second.get(2)\
    \ == 4);\n    assert(branch.get(7) == 10);\n    assert(second.prod(-4, 3) == 6);\n\
    \    assert(second.max_right(-8, [](long long x) { return x <= 3; }) == 2);\n\
    \    assert(second.min_left(8, [](long long x) { return x <= 4; }) == -2);\n}\n\
    \nvoid test_uniform_and_non_commutative() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum, int>;\n\n \
    \   Seg uniform(-5, 6, 3);\n    assert(uniform.all_prod() == 33);\n    assert(uniform.prod(-2,\
    \ 4) == 18);\n    Seg changed = uniform.set(0, 10);\n    assert(uniform.all_prod()\
    \ == 33);\n    assert(changed.all_prod() == 40);\n\n    m1une::ds::PersistentDynamicSegtree<Concat,\
    \ int> text(-2, 3, \"x\");\n    auto first = text.set(1, \"a\");\n    auto second\
    \ = first.set(-1, \"b\");\n    assert(text.all_prod() == \"xxxxx\");\n    assert(first.all_prod()\
    \ == \"xxxax\");\n    assert(second.all_prod() == \"xbxax\");\n}\n\nvoid test_extreme_coordinates()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;\n\
    \n    constexpr long long left = std::numeric_limits<long long>::min();\n    constexpr\
    \ long long right = std::numeric_limits<long long>::max();\n    Seg base(left,\
    \ right);\n    Seg first = base.set(left, 3);\n    Seg second = first.set(right\
    \ - 1, 4);\n\n    assert(base.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(base.all_prod() == 0);\n    assert(first.get(left) == 3);\n    assert(second.get(right\
    \ - 1) == 4);\n    assert(second.all_prod() == 7);\n}\n\nvoid test_randomized()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum,\
    \ int>;\n    constexpr int left = -29;\n    constexpr int right = 37;\n\n    std::vector<Seg>\
    \ versions;\n    versions.emplace_back(left, right, 1);\n    std::vector<std::vector<long\
    \ long>> expected(\n        1,\n        std::vector<long long>(right - left, 1)\n\
    \    );\n\n    std::uint64_t state = 13;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 1500; step++) {\n        std::size_t\
    \ from = std::size_t(random() % versions.size());\n        int p = left + int(random()\
    \ % expected[from].size());\n        long long x = static_cast<long long>(random()\
    \ % 20);\n\n        versions.push_back(versions[from].set(p, x));\n        expected.push_back(expected[from]);\n\
    \        expected.back()[std::size_t(p - left)] = x;\n\n        std::size_t check\
    \ = std::size_t(random() % versions.size());\n        int l = left + int(random()\
    \ % (expected[check].size() + 1));\n        int r = left + int(random() % (expected[check].size()\
    \ + 1));\n        if (r < l) std::swap(l, r);\n        long long sum = 0;\n  \
    \      for (int i = l; i < r; i++) {\n            sum += expected[check][std::size_t(i\
    \ - left)];\n        }\n        assert(versions[check].prod(l, r) == sum);\n\n\
    \        long long limit = static_cast<long long>(random() % 100);\n        int\
    \ start = left + int(random() % (expected[check].size() + 1));\n        int max_right\
    \ = start;\n        sum = 0;\n        while (\n            max_right < right &&\n\
    \            sum + expected[check][std::size_t(max_right - left)] <= limit\n \
    \       ) {\n            sum += expected[check][std::size_t(max_right - left)];\n\
    \            max_right++;\n        }\n        assert(versions[check].max_right(start,\
    \ [limit](long long value) {\n            return value <= limit;\n        }) ==\
    \ max_right);\n\n        int finish = left + int(random() % (expected[check].size()\
    \ + 1));\n        int min_left = finish;\n        sum = 0;\n        while (\n\
    \            left < min_left &&\n            expected[check][std::size_t(min_left\
    \ - 1 - left)] + sum <= limit\n        ) {\n            min_left--;\n        \
    \    sum += expected[check][std::size_t(min_left - left)];\n        }\n      \
    \  assert(versions[check].min_left(finish, [limit](long long value) {\n      \
    \      return value <= limit;\n        }) == min_left);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_versions();\n    test_uniform_and_non_commutative();\n\
    \    test_extreme_coordinates();\n    test_randomized();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/segtree/persistent_dynamic_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <string>\n#include <vector>\n\n#include \"../../../monoid/add.hpp\"\n\
    \nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static\
    \ value_type id() {\n        return \"\";\n    }\n\n    static value_type op(const\
    \ value_type& a, const value_type& b) {\n        return a + b;\n    }\n};\n\n\
    void test_versions() {\n    using Sum = m1une::monoid::Add<long long>;\n    using\
    \ Seg = m1une::ds::PersistentDynamicSegtree<Sum>;\n\n    Seg base(-1'000'000'000'000'000'000LL,\
    \ 1'000'000'000'000'000'000LL, 0);\n    base.reserve(4096);\n    Seg first = base.set(-3,\
    \ 2);\n    Seg second = first.set(2, 4);\n    Seg branch = base.set(7, 10);\n\n\
    \    assert(base.size() == 2'000'000'000'000'000'000ULL);\n    assert(base.node_count()\
    \ == branch.node_count());\n    assert(base.all_prod() == 0);\n    assert(first.all_prod()\
    \ == 2);\n    assert(second.all_prod() == 6);\n    assert(branch.all_prod() ==\
    \ 10);\n    assert(base.get(-3) == 0);\n    assert(first.get(-3) == 2);\n    assert(second.get(2)\
    \ == 4);\n    assert(branch.get(7) == 10);\n    assert(second.prod(-4, 3) == 6);\n\
    \    assert(second.max_right(-8, [](long long x) { return x <= 3; }) == 2);\n\
    \    assert(second.min_left(8, [](long long x) { return x <= 4; }) == -2);\n}\n\
    \nvoid test_uniform_and_non_commutative() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum, int>;\n\n \
    \   Seg uniform(-5, 6, 3);\n    assert(uniform.all_prod() == 33);\n    assert(uniform.prod(-2,\
    \ 4) == 18);\n    Seg changed = uniform.set(0, 10);\n    assert(uniform.all_prod()\
    \ == 33);\n    assert(changed.all_prod() == 40);\n\n    m1une::ds::PersistentDynamicSegtree<Concat,\
    \ int> text(-2, 3, \"x\");\n    auto first = text.set(1, \"a\");\n    auto second\
    \ = first.set(-1, \"b\");\n    assert(text.all_prod() == \"xxxxx\");\n    assert(first.all_prod()\
    \ == \"xxxax\");\n    assert(second.all_prod() == \"xbxax\");\n}\n\nvoid test_extreme_coordinates()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;\n\
    \n    constexpr long long left = std::numeric_limits<long long>::min();\n    constexpr\
    \ long long right = std::numeric_limits<long long>::max();\n    Seg base(left,\
    \ right);\n    Seg first = base.set(left, 3);\n    Seg second = first.set(right\
    \ - 1, 4);\n\n    assert(base.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(base.all_prod() == 0);\n    assert(first.get(left) == 3);\n    assert(second.get(right\
    \ - 1) == 4);\n    assert(second.all_prod() == 7);\n}\n\nvoid test_randomized()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicSegtree<Sum,\
    \ int>;\n    constexpr int left = -29;\n    constexpr int right = 37;\n\n    std::vector<Seg>\
    \ versions;\n    versions.emplace_back(left, right, 1);\n    std::vector<std::vector<long\
    \ long>> expected(\n        1,\n        std::vector<long long>(right - left, 1)\n\
    \    );\n\n    std::uint64_t state = 13;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 1500; step++) {\n        std::size_t\
    \ from = std::size_t(random() % versions.size());\n        int p = left + int(random()\
    \ % expected[from].size());\n        long long x = static_cast<long long>(random()\
    \ % 20);\n\n        versions.push_back(versions[from].set(p, x));\n        expected.push_back(expected[from]);\n\
    \        expected.back()[std::size_t(p - left)] = x;\n\n        std::size_t check\
    \ = std::size_t(random() % versions.size());\n        int l = left + int(random()\
    \ % (expected[check].size() + 1));\n        int r = left + int(random() % (expected[check].size()\
    \ + 1));\n        if (r < l) std::swap(l, r);\n        long long sum = 0;\n  \
    \      for (int i = l; i < r; i++) {\n            sum += expected[check][std::size_t(i\
    \ - left)];\n        }\n        assert(versions[check].prod(l, r) == sum);\n\n\
    \        long long limit = static_cast<long long>(random() % 100);\n        int\
    \ start = left + int(random() % (expected[check].size() + 1));\n        int max_right\
    \ = start;\n        sum = 0;\n        while (\n            max_right < right &&\n\
    \            sum + expected[check][std::size_t(max_right - left)] <= limit\n \
    \       ) {\n            sum += expected[check][std::size_t(max_right - left)];\n\
    \            max_right++;\n        }\n        assert(versions[check].max_right(start,\
    \ [limit](long long value) {\n            return value <= limit;\n        }) ==\
    \ max_right);\n\n        int finish = left + int(random() % (expected[check].size()\
    \ + 1));\n        int min_left = finish;\n        sum = 0;\n        while (\n\
    \            left < min_left &&\n            expected[check][std::size_t(min_left\
    \ - 1 - left)] + sum <= limit\n        ) {\n            min_left--;\n        \
    \    sum += expected[check][std::size_t(min_left - left)];\n        }\n      \
    \  assert(versions[check].min_left(finish, [limit](long long value) {\n      \
    \      return value <= limit;\n        }) == min_left);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_versions();\n    test_uniform_and_non_commutative();\n\
    \    test_extreme_coordinates();\n    test_randomized();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/segtree/persistent_dynamic_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/persistent_dynamic_segtree.test.cpp
- /verify/verify/ds/segtree/persistent_dynamic_segtree.test.cpp.html
title: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
---
