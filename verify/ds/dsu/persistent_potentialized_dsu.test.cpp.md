---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_potentialized_dsu.hpp
    title: Persistent Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/xor.hpp
    title: Bitwise XOR Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
  bundledCode: "#line 1 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#line 1 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\n    requires std::equality_comparable<typename Group::value_type>\n\
    struct PersistentPotentializedDsu {\n    using T = typename Group::value_type;\n\
    \n    struct Value {\n        int parent_or_size;\n        T diff_to_parent;\n\
    \n        Value() : parent_or_size(0), diff_to_parent(Group::id()) {}\n      \
    \  Value(int parent_or_size_, const T& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(diff_to_parent_) {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n\
    \            : parent_or_size(parent_or_size_), diff_to_parent(std::move(diff_to_parent_))\
    \ {}\n    };\n\n   private:\n    struct Node {\n        Value val;\n        int\
    \ l, r;\n\n        Node() : val(), l(0), r(0) {}\n        explicit Node(const\
    \ Value& value) : val(value), l(0), r(0) {}\n        explicit Node(Value&& value)\
    \ : val(std::move(value)), l(0), r(0) {}\n        Node(const Value& value, int\
    \ left, int right) : val(value), l(left), r(right) {}\n        Node(Value&& value,\
    \ int left, int right) : val(std::move(value)), l(left), r(right) {}\n    };\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>> _pool;\n\
    \n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int build(int l, int r)\
    \ const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(Value(-1,\
    \ Group::id())));\n        int m = (l + r) >> 1;\n        int left = build(l,\
    \ m);\n        int right = build(m, r);\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    int set_node(int t, int l, int r, int p, Value\
    \ value) const {\n        if (r - l == 1) return new_node(Node(std::move(value)));\n\
    \        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int\
    \ right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, std::move(value));\n        } else {\n            right = set_node(right,\
    \ m, r, p, std::move(value));\n        }\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    Value get_value(int t, int l, int r, int p) const\
    \ {\n        while (r - l > 1) {\n            int m = (l + r) >> 1;\n        \
    \    if (p < m) {\n                t = (*_pool)[t].l;\n                r = m;\n\
    \            } else {\n                t = (*_pool)[t].r;\n                l =\
    \ m;\n            }\n        }\n        return (*_pool)[t].val;\n    }\n\n   \
    \ std::pair<int, T> leader_and_potential(int a) const {\n        T res = Group::id();\n\
    \        while (true) {\n            Value cur = get(a);\n            if (cur.parent_or_size\
    \ < 0) return {a, res};\n            res = Group::op(cur.diff_to_parent, res);\n\
    \            a = cur.parent_or_size;\n        }\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n     \
    \   assert(0 <= n);\n        _pool->reserve(n * 4 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       return leader_and_potential(a).first;\n    }\n\n    bool same(int a, int\
    \ b) const {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b <\
    \ _n);\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) const {\n        assert(0 <= a && a < _n);\n        return -get(leader(a)).parent_or_size;\n\
    \    }\n\n    int size(int a) const {\n        return group_size(a);\n    }\n\n\
    \    T potential(int a) const {\n        assert(0 <= a && a < _n);\n        return\
    \ leader_and_potential(a).second;\n    }\n\n    T diff(int a, int b) const {\n\
    \        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    Value get(int p) const {\n        assert(0 <= p\
    \ && p < _n);\n        return get_value(_root, 0, _n, p);\n    }\n\n    int parent_or_size(int\
    \ p) const {\n        return get(p).parent_or_size;\n    }\n\n    std::pair<PersistentPotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        assert(0 <= a && a <\
    \ _n);\n        assert(0 <= b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n\
    \        auto [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this,\
    \ Group::op(Group::inv(pa), pb) == w};\n\n        int sx = -get(x).parent_or_size;\n\
    \        int sy = -get(y).parent_or_size;\n        T y_from_x = Group::op(Group::op(pa,\
    \ w), Group::inv(pb));\n        if (sx < sy) {\n            std::swap(x, y);\n\
    \            std::swap(sx, sy);\n            y_from_x = Group::inv(y_from_x);\n\
    \        }\n        int root = set_node(_root, 0, _n, x, Value(-(sx + sy), Group::id()));\n\
    \        root = set_node(root, 0, _n, y, Value(x, std::move(y_from_x)));\n   \
    \     return {PersistentPotentializedDsu(_n, root, _pool), true};\n    }\n\n \
    \   std::vector<std::vector<int>> groups() const {\n        std::vector<int> leader_buf(_n),\
    \ group_size(_n);\n        for (int i = 0; i < _n; i++) {\n            leader_buf[i]\
    \ = leader(i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate <typename\
    \ T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/xor.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate <typename\
    \ T>\nstruct Xor {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for bitwise XOR, which is 0.\n    static constexpr T id() {\n        return\
    \ T(0);\n    }\n\n    // Returns the bitwise XOR of a and b.\n    static constexpr\
    \ T op(const T& a, const T& b) {\n        return a ^ b;\n    }\n\n    static constexpr\
    \ T inv(const T& x) {\n        return x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 6 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\
    \n\n#line 9 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\n#include\
    \ <iostream>\n#include <random>\n#line 13 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\
    \n\ntemplate <class Group>\nstruct NaivePotentializedDsu {\n    using T = typename\
    \ Group::value_type;\n\n    std::vector<int> parent_or_size;\n    std::vector<T>\
    \ diff_to_parent;\n\n    explicit NaivePotentializedDsu(int n = 0) : parent_or_size(n,\
    \ -1), diff_to_parent(n, Group::id()) {}\n\n    std::pair<int, T> leader_and_potential(int\
    \ a) const {\n        T res = Group::id();\n        while (parent_or_size[a] >=\
    \ 0) {\n            res = Group::op(diff_to_parent[a], res);\n            a =\
    \ parent_or_size[a];\n        }\n        return {a, res};\n    }\n\n    int leader(int\
    \ a) const {\n        return leader_and_potential(a).first;\n    }\n\n    bool\
    \ same(int a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n\
    \    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    T potential(int a) const {\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    std::pair<NaivePotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        NaivePotentializedDsu\
    \ res = *this;\n        auto [x, pa] = res.leader_and_potential(a);\n        auto\
    \ [y, pb] = res.leader_and_potential(b);\n        if (x == y) return {res, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -res.parent_or_size[x];\n        int sy = -res.parent_or_size[y];\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        res.parent_or_size[x]\
    \ += res.parent_or_size[y];\n        res.parent_or_size[y] = x;\n        res.diff_to_parent[y]\
    \ = y_from_x;\n        return {res, true};\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nvoid self_test()\
    \ {\n    using Add = m1une::monoid::Add<long long>;\n    using AddDsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    AddDsu base(5);\n    auto [a, ok1] = base.merge(0, 1, 3);\n    auto [b,\
    \ ok2] = a.merge(1, 2, 4);\n    auto [c, ok3] = b.merge(3, 4, -2);\n    auto [d,\
    \ ok4] = b.merge(2, 3, 5);\n    auto [bad, ok_bad] = b.merge(0, 2, 8);\n\n   \
    \ assert(ok1);\n    assert(ok2);\n    assert(ok3);\n    assert(ok4);\n    assert(!ok_bad);\n\
    \    assert(base.size() == 5);\n    assert(!base.empty());\n    assert(!base.same(0,\
    \ 2));\n    assert(a.same(0, 1));\n    assert(!a.same(0, 2));\n    assert(b.diff(0,\
    \ 2) == 7);\n    assert(b.diff(2, 0) == -7);\n    assert(c.diff(3, 4) == -2);\n\
    \    assert(!c.same(0, 4));\n    assert(d.diff(0, 3) == 12);\n    assert(bad.diff(0,\
    \ 2) == 7);\n    assert(d.group_size(0) == 4);\n    assert(d.size(0) == 4);\n\
    \    assert(base.group_size(0) == 1);\n    assert(base.parent_or_size(0) == -1);\n\
    \n    std::vector<std::vector<int>> base_groups;\n    base_groups.emplace_back(std::vector<int>{0});\n\
    \    base_groups.emplace_back(std::vector<int>{1});\n    base_groups.emplace_back(std::vector<int>{2});\n\
    \    base_groups.emplace_back(std::vector<int>{3});\n    base_groups.emplace_back(std::vector<int>{4});\n\
    \    assert(base.groups() == base_groups);\n\n    using Xor = m1une::monoid::Xor<int>;\n\
    \    m1une::ds::PersistentPotentializedDsu<Xor> xor_base(4);\n    auto [xor_a,\
    \ xor_ok1] = xor_base.merge(0, 1, 5);\n    auto [xor_b, xor_ok2] = xor_a.merge(1,\
    \ 2, 6);\n    auto [xor_bad, xor_ok_bad] = xor_b.merge(0, 2, 2);\n    assert(xor_ok1);\n\
    \    assert(xor_ok2);\n    assert(!xor_ok_bad);\n    assert(xor_b.diff(0, 2) ==\
    \ (5 ^ 6));\n    assert(xor_bad.diff(0, 2) == (5 ^ 6));\n\n    AddDsu empty;\n\
    \    assert(empty.size() == 0);\n    assert(empty.empty());\n\n    std::mt19937\
    \ rng(0);\n    constexpr int N = 25;\n    std::vector<std::pair<AddDsu, NaivePotentializedDsu<Add>>>\
    \ versions;\n    versions.emplace_back(AddDsu(N), NaivePotentializedDsu<Add>(N));\n\
    \n    for (int step = 0; step < 400; step++) {\n        int id = int(rng() % versions.size());\n\
    \        AddDsu cur = versions[id].first;\n        NaivePotentializedDsu<Add>\
    \ expected = versions[id].second;\n\n        for (int i = 0; i < N; i++) {\n \
    \           assert(cur.group_size(i) == expected.group_size(i));\n           \
    \ assert(cur.parent_or_size(i) == expected.parent_or_size[i]);\n            for\
    \ (int j = 0; j < N; j++) {\n                assert(cur.same(i, j) == expected.same(i,\
    \ j));\n                if (cur.same(i, j)) assert(cur.diff(i, j) == expected.diff(i,\
    \ j));\n            }\n        }\n        assert(cur.groups() == expected.groups());\n\
    \n        int u = int(rng() % N);\n        int v = int(rng() % N);\n        long\
    \ long w = int(rng() % 21) - 10;\n        if (expected.same(u, v) && (rng() &\
    \ 1)) w = expected.diff(u, v);\n\n        auto [next, ok] = cur.merge(u, v, w);\n\
    \        auto [next_expected, expected_ok] = expected.merge(u, v, w);\n      \
    \  assert(ok == expected_ok);\n\n        for (int i = 0; i < N; i++) {\n     \
    \       assert(cur.group_size(i) == expected.group_size(i));\n            assert(next.group_size(i)\
    \ == next_expected.group_size(i));\n            assert(next.parent_or_size(i)\
    \ == next_expected.parent_or_size[i]);\n        }\n\n        versions.emplace_back(next,\
    \ next_expected);\n    }\n}\n\nint main() {\n    self_test();\n\n    using Add\
    \ = m1une::monoid::Add<long long>;\n    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    Dsu dsu(n);\n\n    while (q--) {\n     \
    \   int type, x, y;\n        std::cin >> type >> x >> y;\n        if (type ==\
    \ 0) {\n            long long z;\n            std::cin >> z;\n            auto\
    \ [next, ok] = dsu.merge(x, y, z);\n            (void)ok;\n            dsu = next;\n\
    \        } else {\n            if (dsu.same(x, y)) {\n                std::cout\
    \ << dsu.diff(x, y) << '\\n';\n            } else {\n                std::cout\
    \ << \"?\\n\";\n            }\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include \"../../../ds/dsu/persistent_potentialized_dsu.hpp\"\n#include \"\
    ../../../monoid/add.hpp\"\n#include \"../../../monoid/xor.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\ntemplate <class Group>\nstruct NaivePotentializedDsu {\n\
    \    using T = typename Group::value_type;\n\n    std::vector<int> parent_or_size;\n\
    \    std::vector<T> diff_to_parent;\n\n    explicit NaivePotentializedDsu(int\
    \ n = 0) : parent_or_size(n, -1), diff_to_parent(n, Group::id()) {}\n\n    std::pair<int,\
    \ T> leader_and_potential(int a) const {\n        T res = Group::id();\n     \
    \   while (parent_or_size[a] >= 0) {\n            res = Group::op(diff_to_parent[a],\
    \ res);\n            a = parent_or_size[a];\n        }\n        return {a, res};\n\
    \    }\n\n    int leader(int a) const {\n        return leader_and_potential(a).first;\n\
    \    }\n\n    bool same(int a, int b) const {\n        return leader(a) == leader(b);\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    T potential(int a) const {\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    std::pair<NaivePotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        NaivePotentializedDsu\
    \ res = *this;\n        auto [x, pa] = res.leader_and_potential(a);\n        auto\
    \ [y, pb] = res.leader_and_potential(b);\n        if (x == y) return {res, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -res.parent_or_size[x];\n        int sy = -res.parent_or_size[y];\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        res.parent_or_size[x]\
    \ += res.parent_or_size[y];\n        res.parent_or_size[y] = x;\n        res.diff_to_parent[y]\
    \ = y_from_x;\n        return {res, true};\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nvoid self_test()\
    \ {\n    using Add = m1une::monoid::Add<long long>;\n    using AddDsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    AddDsu base(5);\n    auto [a, ok1] = base.merge(0, 1, 3);\n    auto [b,\
    \ ok2] = a.merge(1, 2, 4);\n    auto [c, ok3] = b.merge(3, 4, -2);\n    auto [d,\
    \ ok4] = b.merge(2, 3, 5);\n    auto [bad, ok_bad] = b.merge(0, 2, 8);\n\n   \
    \ assert(ok1);\n    assert(ok2);\n    assert(ok3);\n    assert(ok4);\n    assert(!ok_bad);\n\
    \    assert(base.size() == 5);\n    assert(!base.empty());\n    assert(!base.same(0,\
    \ 2));\n    assert(a.same(0, 1));\n    assert(!a.same(0, 2));\n    assert(b.diff(0,\
    \ 2) == 7);\n    assert(b.diff(2, 0) == -7);\n    assert(c.diff(3, 4) == -2);\n\
    \    assert(!c.same(0, 4));\n    assert(d.diff(0, 3) == 12);\n    assert(bad.diff(0,\
    \ 2) == 7);\n    assert(d.group_size(0) == 4);\n    assert(d.size(0) == 4);\n\
    \    assert(base.group_size(0) == 1);\n    assert(base.parent_or_size(0) == -1);\n\
    \n    std::vector<std::vector<int>> base_groups;\n    base_groups.emplace_back(std::vector<int>{0});\n\
    \    base_groups.emplace_back(std::vector<int>{1});\n    base_groups.emplace_back(std::vector<int>{2});\n\
    \    base_groups.emplace_back(std::vector<int>{3});\n    base_groups.emplace_back(std::vector<int>{4});\n\
    \    assert(base.groups() == base_groups);\n\n    using Xor = m1une::monoid::Xor<int>;\n\
    \    m1une::ds::PersistentPotentializedDsu<Xor> xor_base(4);\n    auto [xor_a,\
    \ xor_ok1] = xor_base.merge(0, 1, 5);\n    auto [xor_b, xor_ok2] = xor_a.merge(1,\
    \ 2, 6);\n    auto [xor_bad, xor_ok_bad] = xor_b.merge(0, 2, 2);\n    assert(xor_ok1);\n\
    \    assert(xor_ok2);\n    assert(!xor_ok_bad);\n    assert(xor_b.diff(0, 2) ==\
    \ (5 ^ 6));\n    assert(xor_bad.diff(0, 2) == (5 ^ 6));\n\n    AddDsu empty;\n\
    \    assert(empty.size() == 0);\n    assert(empty.empty());\n\n    std::mt19937\
    \ rng(0);\n    constexpr int N = 25;\n    std::vector<std::pair<AddDsu, NaivePotentializedDsu<Add>>>\
    \ versions;\n    versions.emplace_back(AddDsu(N), NaivePotentializedDsu<Add>(N));\n\
    \n    for (int step = 0; step < 400; step++) {\n        int id = int(rng() % versions.size());\n\
    \        AddDsu cur = versions[id].first;\n        NaivePotentializedDsu<Add>\
    \ expected = versions[id].second;\n\n        for (int i = 0; i < N; i++) {\n \
    \           assert(cur.group_size(i) == expected.group_size(i));\n           \
    \ assert(cur.parent_or_size(i) == expected.parent_or_size[i]);\n            for\
    \ (int j = 0; j < N; j++) {\n                assert(cur.same(i, j) == expected.same(i,\
    \ j));\n                if (cur.same(i, j)) assert(cur.diff(i, j) == expected.diff(i,\
    \ j));\n            }\n        }\n        assert(cur.groups() == expected.groups());\n\
    \n        int u = int(rng() % N);\n        int v = int(rng() % N);\n        long\
    \ long w = int(rng() % 21) - 10;\n        if (expected.same(u, v) && (rng() &\
    \ 1)) w = expected.diff(u, v);\n\n        auto [next, ok] = cur.merge(u, v, w);\n\
    \        auto [next_expected, expected_ok] = expected.merge(u, v, w);\n      \
    \  assert(ok == expected_ok);\n\n        for (int i = 0; i < N; i++) {\n     \
    \       assert(cur.group_size(i) == expected.group_size(i));\n            assert(next.group_size(i)\
    \ == next_expected.group_size(i));\n            assert(next.parent_or_size(i)\
    \ == next_expected.parent_or_size[i]);\n        }\n\n        versions.emplace_back(next,\
    \ next_expected);\n    }\n}\n\nint main() {\n    self_test();\n\n    using Add\
    \ = m1une::monoid::Add<long long>;\n    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    Dsu dsu(n);\n\n    while (q--) {\n     \
    \   int type, x, y;\n        std::cin >> type >> x >> y;\n        if (type ==\
    \ 0) {\n            long long z;\n            std::cin >> z;\n            auto\
    \ [next, ok] = dsu.merge(x, y, z);\n            (void)ok;\n            dsu = next;\n\
    \        } else {\n            if (dsu.same(x, y)) {\n                std::cout\
    \ << dsu.diff(x, y) << '\\n';\n            } else {\n                std::cout\
    \ << \"?\\n\";\n            }\n        }\n    }\n}\n"
  dependsOn:
  - ds/dsu/persistent_potentialized_dsu.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - monoid/xor.hpp
  isVerificationFile: true
  path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 02:52:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/persistent_potentialized_dsu.test.cpp
- /verify/verify/ds/dsu/persistent_potentialized_dsu.test.cpp.html
title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
---
