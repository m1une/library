---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_dual_segtree.hpp
    title: Persistent Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/update.hpp
    title: Update Monoid
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
  bundledCode: "#line 1 \"verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 16 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A persistent sparse dual segment tree\
    \ over an integral half-open interval.\ntemplate <m1une::monoid::IsMonoid Monoid,\
    \ std::integral Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct PersistentDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n        bool has_lazy;\n\n        Node() : val(Monoid::id()), left(0),\
    \ right(0), has_lazy(false) {}\n    };\n\n    struct Config {\n        Index left;\n\
    \        Index right;\n        T initial_value;\n\n        Config(Index left_bound,\
    \ Index right_bound, T value)\n            : left(left_bound), right(right_bound),\
    \ initial_value(std::move(value)) {\n            assert(left <= right);\n    \
    \    }\n    };\n\n    std::shared_ptr<const Config> _config;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicDualSegtree(\n        std::shared_ptr<const\
    \ Config> config,\n        std::shared_ptr<std::vector<Node>> pool,\n        int\
    \ root\n    ) : _config(std::move(config)), _pool(std::move(pool)), _root(root)\
    \ {}\n\n    int new_node() const {\n        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _pool->emplace_back();\n        return int(_pool->size()) - 1;\n    }\n\
    \n    int clone_or_new(int t) const {\n        if (!t) return new_node();\n  \
    \      assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _pool->push_back((*_pool)[t]);\n        return int(_pool->size()) - 1;\n\
    \    }\n\n    void all_apply_to_node(int t, Index left, Index right, const T&\
    \ x) const {\n        Node& node = (*_pool)[t];\n        if (std::midpoint(left,\
    \ right) == left) {\n            T value = node.has_lazy ? node.val : _config->initial_value;\n\
    \            node.val = Monoid::op(x, value);\n            node.has_lazy = true;\n\
    \        } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val)\
    \ : x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, const T& x) const {\n        int result = clone_or_new(t);\n\
    \        all_apply_to_node(result, left, right, x);\n        return result;\n\
    \    }\n\n    void push(int t, Index left, Index right) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        T lazy = (*_pool)[t].val;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, lazy);\n        int right_child\
    \ = all_apply_clone((*_pool)[t].right, middle, right, lazy);\n\n        Node&\
    \ node = (*_pool)[t];\n        node.left = left_child;\n        node.right = right_child;\n\
    \        node.val = Monoid::id();\n        node.has_lazy = false;\n    }\n\n \
    \   int set_node(int t, Index left, Index right, Index p, T x) const {\n     \
    \   t = clone_or_new(t);\n        Index middle = std::midpoint(left, right);\n\
    \        if (middle == left) {\n            Node& node = (*_pool)[t];\n      \
    \      node.val = std::move(x);\n            node.has_lazy = true;\n         \
    \   return t;\n        }\n\n        push(t, left, right);\n        if (p < middle)\
    \ {\n            int child = set_node((*_pool)[t].left, left, middle, p, std::move(x));\n\
    \            (*_pool)[t].left = child;\n        } else {\n            int child\
    \ = set_node((*_pool)[t].right, middle, right, p, std::move(x));\n           \
    \ (*_pool)[t].right = child;\n        }\n        return t;\n    }\n\n    int apply_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        Index query_left,\n\
    \        Index query_right,\n        const T& x\n    ) const {\n        if (query_right\
    \ <= left || right <= query_left) return t;\n        if (query_left <= left &&\
    \ right <= query_right) {\n            return all_apply_clone(t, left, right,\
    \ x);\n        }\n\n        t = clone_or_new(t);\n        push(t, left, right);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node(\n            (*_pool)[t].left,\n            left,\n            middle,\n\
    \            query_left,\n            query_right,\n            x\n        );\n\
    \        int right_child = apply_node(\n            (*_pool)[t].right,\n     \
    \       middle,\n            right,\n            query_left,\n            query_right,\n\
    \            x\n        );\n        (*_pool)[t].left = left_child;\n        (*_pool)[t].right\
    \ = right_child;\n        return t;\n    }\n\n    T compose(const T& inherited,\
    \ int t) const {\n        if (!t || !(*_pool)[t].has_lazy) return inherited;\n\
    \        return Monoid::op(inherited, (*_pool)[t].val);\n    }\n\n   public:\n\
    \    PersistentDynamicDualSegtree()\n        : PersistentDynamicDualSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n\n    explicit PersistentDynamicDualSegtree(Index\
    \ n)\n        : PersistentDynamicDualSegtree(Index(0), n, Monoid::id()) {\n  \
    \      if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n   \
    \ }\n\n    PersistentDynamicDualSegtree(Index left, Index right)\n        : PersistentDynamicDualSegtree(left,\
    \ right, Monoid::id()) {}\n\n    PersistentDynamicDualSegtree(Index left, Index\
    \ right, T initial_value)\n        : _config(std::make_shared<Config>(left, right,\
    \ std::move(initial_value))),\n          _pool(std::make_shared<std::vector<Node>>()),\n\
    \          _root(0) {\n        _pool->emplace_back();\n    }\n\n    size_type\
    \ size() const {\n        return detail::dynamic_distance(_config->left, _config->right);\n\
    \    }\n\n    bool empty() const {\n        return _config->left == _config->right;\n\
    \    }\n\n    Index left_bound() const {\n        return _config->left;\n    }\n\
    \n    Index right_bound() const {\n        return _config->right;\n    }\n\n \
    \   const T& initial_value() const {\n        return _config->initial_value;\n\
    \    }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _pool->size()\
    \ - 1;\n    }\n\n    PersistentDynamicDualSegtree set(Index p, T x) const {\n\
    \        assert(left_bound() <= p && p < right_bound());\n        return PersistentDynamicDualSegtree(\n\
    \            _config,\n            _pool,\n            set_node(_root, left_bound(),\
    \ right_bound(), p, std::move(x))\n        );\n    }\n\n    T get(Index p) const\
    \ {\n        assert(left_bound() <= p && p < right_bound());\n        int t =\
    \ _root;\n        Index left = left_bound();\n        Index right = right_bound();\n\
    \        T inherited = Monoid::id();\n\n        while (t) {\n            Index\
    \ middle = std::midpoint(left, right);\n            if (middle == left) {\n  \
    \              T value = (*_pool)[t].has_lazy ? (*_pool)[t].val : initial_value();\n\
    \                return Monoid::op(inherited, value);\n            }\n       \
    \     inherited = compose(inherited, t);\n            if (p < middle) {\n    \
    \            t = (*_pool)[t].left;\n                right = middle;\n        \
    \    } else {\n                t = (*_pool)[t].right;\n                left =\
    \ middle;\n            }\n        }\n        return Monoid::op(inherited, initial_value());\n\
    \    }\n\n    T operator[](Index p) const {\n        return get(p);\n    }\n\n\
    \    PersistentDynamicDualSegtree apply(Index p, const T& x) const {\n       \
    \ assert(left_bound() <= p && p < right_bound());\n        return apply(p, p +\
    \ 1, x);\n    }\n\n    PersistentDynamicDualSegtree apply(Index left, Index right,\
    \ const T& x) const {\n        assert(left_bound() <= left && left <= right &&\
    \ right <= right_bound());\n        if (left == right) return *this;\n       \
    \ return PersistentDynamicDualSegtree(\n            _config,\n            _pool,\n\
    \            apply_node(_root, left_bound(), right_bound(), left, right, x)\n\
    \        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 7 \"verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <optional>\n#line 11 \"verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n\n    // Returns the identity element for addition, which\
    \ is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    //\
    \ Returns the sum of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T& x)\
    \ {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/update.hpp\"\n\n\n\n#line 5 \"monoid/update.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for range updates/assignments.\n\
    // Uses std::optional to represent the presence of an assignment.\ntemplate <typename\
    \ T>\nstruct Update {\n    using value_type = std::optional<T>;\n\n    // The\
    \ identity element represents \"no operation\".\n    static constexpr value_type\
    \ id() {\n        return std::nullopt;\n    }\n\n    // Composes two updates.\
    \ The newer operation 'a' overwrites the older 'b'.\n    // If 'a' does not exist,\
    \ it falls back to 'b'.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return a.has_value() ? a : b;\n    }\n};\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 14 \"verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_versions() {\n    using Add = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add, int>;\n\
    \n    Seg base(-50, 60, 5);\n    base.reserve(20000);\n    Seg first = base.apply(-10,\
    \ 20, 3);\n    Seg second = first.set(0, 100);\n    Seg branch = base.apply(5,\
    \ 15, 7);\n\n    assert(base.get(0) == 5);\n    assert(first.get(0) == 8);\n \
    \   assert(second.get(0) == 100);\n    assert(branch.get(0) == 5);\n    assert(first.get(-20)\
    \ == 5);\n    assert(branch.get(10) == 12);\n    assert(base.node_count() == branch.node_count());\n\
    }\n\nvoid test_update_order() {\n    using Update = m1une::monoid::Update<int>;\n\
    \    using Seg = m1une::ds::PersistentDynamicDualSegtree<Update, int>;\n\n   \
    \ Seg base(-10, 11, std::optional<int>(1));\n    Seg first = base.apply(-5, 6,\
    \ std::optional<int>(2));\n    Seg second = first.apply(-2, 3, std::optional<int>(4));\n\
    \n    assert(base.get(0).value() == 1);\n    assert(first.get(0).value() == 2);\n\
    \    assert(second.get(0).value() == 4);\n    assert(second.get(4).value() ==\
    \ 2);\n    assert(second.get(8).value() == 1);\n}\n\nvoid test_randomized() {\n\
    \    using Add = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add,\
    \ int>;\n    constexpr int left = -23;\n    constexpr int right = 29;\n\n    std::vector<Seg>\
    \ versions;\n    versions.emplace_back(left, right, 4);\n    std::vector<std::vector<long\
    \ long>> expected(\n        1,\n        std::vector<long long>(right - left, 4)\n\
    \    );\n\n    std::uint64_t state = 9;\n    auto random = [&state]() {\n    \
    \    state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 1200; step++) {\n        std::size_t\
    \ from = std::size_t(random() % versions.size());\n        std::vector<long long>\
    \ next = expected[from];\n        Seg tree = versions[from];\n\n        if (random()\
    \ & 1) {\n            int l = left + int(random() % (next.size() + 1));\n    \
    \        int r = left + int(random() % (next.size() + 1));\n            if (r\
    \ < l) std::swap(l, r);\n            long long x = static_cast<long long>(random()\
    \ % 20);\n            tree = tree.apply(l, r, x);\n            for (int p = l;\
    \ p < r; p++) next[std::size_t(p - left)] += x;\n        } else {\n          \
    \  int p = left + int(random() % next.size());\n            long long x = static_cast<long\
    \ long>(random() % 100);\n            tree = tree.set(p, x);\n            next[std::size_t(p\
    \ - left)] = x;\n        }\n\n        versions.push_back(tree);\n        expected.push_back(next);\n\
    \        [[maybe_unused]] std::size_t check = std::size_t(random() % versions.size());\n\
    \        [[maybe_unused]] int p = left + int(random() % next.size());\n      \
    \  assert(versions[check].get(p) == expected[check][std::size_t(p - left)]);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_versions();\n    test_update_order();\n\
    \    test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <optional>\n\
    #include <vector>\n\n#include \"../../../monoid/add.hpp\"\n#include \"../../../monoid/update.hpp\"\
    \n\nnamespace {\n\nvoid test_versions() {\n    using Add = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add, int>;\n\
    \n    Seg base(-50, 60, 5);\n    base.reserve(20000);\n    Seg first = base.apply(-10,\
    \ 20, 3);\n    Seg second = first.set(0, 100);\n    Seg branch = base.apply(5,\
    \ 15, 7);\n\n    assert(base.get(0) == 5);\n    assert(first.get(0) == 8);\n \
    \   assert(second.get(0) == 100);\n    assert(branch.get(0) == 5);\n    assert(first.get(-20)\
    \ == 5);\n    assert(branch.get(10) == 12);\n    assert(base.node_count() == branch.node_count());\n\
    }\n\nvoid test_update_order() {\n    using Update = m1une::monoid::Update<int>;\n\
    \    using Seg = m1une::ds::PersistentDynamicDualSegtree<Update, int>;\n\n   \
    \ Seg base(-10, 11, std::optional<int>(1));\n    Seg first = base.apply(-5, 6,\
    \ std::optional<int>(2));\n    Seg second = first.apply(-2, 3, std::optional<int>(4));\n\
    \n    assert(base.get(0).value() == 1);\n    assert(first.get(0).value() == 2);\n\
    \    assert(second.get(0).value() == 4);\n    assert(second.get(4).value() ==\
    \ 2);\n    assert(second.get(8).value() == 1);\n}\n\nvoid test_randomized() {\n\
    \    using Add = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add,\
    \ int>;\n    constexpr int left = -23;\n    constexpr int right = 29;\n\n    std::vector<Seg>\
    \ versions;\n    versions.emplace_back(left, right, 4);\n    std::vector<std::vector<long\
    \ long>> expected(\n        1,\n        std::vector<long long>(right - left, 4)\n\
    \    );\n\n    std::uint64_t state = 9;\n    auto random = [&state]() {\n    \
    \    state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 1200; step++) {\n        std::size_t\
    \ from = std::size_t(random() % versions.size());\n        std::vector<long long>\
    \ next = expected[from];\n        Seg tree = versions[from];\n\n        if (random()\
    \ & 1) {\n            int l = left + int(random() % (next.size() + 1));\n    \
    \        int r = left + int(random() % (next.size() + 1));\n            if (r\
    \ < l) std::swap(l, r);\n            long long x = static_cast<long long>(random()\
    \ % 20);\n            tree = tree.apply(l, r, x);\n            for (int p = l;\
    \ p < r; p++) next[std::size_t(p - left)] += x;\n        } else {\n          \
    \  int p = left + int(random() % next.size());\n            long long x = static_cast<long\
    \ long>(random() % 100);\n            tree = tree.set(p, x);\n            next[std::size_t(p\
    \ - left)] = x;\n        }\n\n        versions.push_back(tree);\n        expected.push_back(next);\n\
    \        [[maybe_unused]] std::size_t check = std::size_t(random() % versions.size());\n\
    \        [[maybe_unused]] int p = left + int(random() % next.size());\n      \
    \  assert(versions[check].get(p) == expected[check][std::size_t(p - left)]);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_versions();\n    test_update_order();\n\
    \    test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/segtree/persistent_dynamic_dual_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - monoid/update.hpp
  isVerificationFile: true
  path: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
- /verify/verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp.html
title: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
---
