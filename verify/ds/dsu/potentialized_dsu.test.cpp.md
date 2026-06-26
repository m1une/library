---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/potentialized_dsu.hpp
    title: Potentialized DSU
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
  bundledCode: "#line 1 \"verify/ds/dsu/potentialized_dsu.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\n\n#line\
    \ 1 \"ds/dsu/potentialized_dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <concepts>\n#include <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ group monoids.\n// A type satisfying this concept must also obey commutativity\
    \ and inverse laws.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 11 \"ds/dsu/potentialized_dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::monoid::IsCommutativeGroup Group>\nrequires std::equality_comparable<typename\
    \ Group::value_type>\nstruct PotentializedDsu {\n    using T = typename Group::value_type;\n\
    \n   private:\n    int _n;\n    std::vector<int> parent_or_size;\n    std::vector<T>\
    \ diff_to_parent;\n\n    static int check_size(int n) {\n        assert(0 <= n);\n\
    \        return n;\n    }\n\n   public:\n    PotentializedDsu() : PotentializedDsu(0)\
    \ {}\n\n    explicit PotentializedDsu(int n) : _n(check_size(n)), parent_or_size(_n,\
    \ -1), diff_to_parent(_n, Group::id()) {}\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        int p = parent_or_size[a];\n        int r = leader(p);\n\
    \        diff_to_parent[a] = Group::op(diff_to_parent[p], diff_to_parent[a]);\n\
    \        return parent_or_size[a] = r;\n    }\n\n    int leader(int a) const {\n\
    \        assert(0 <= a && a < _n);\n        while (parent_or_size[a] >= 0) a =\
    \ parent_or_size[a];\n        return a;\n    }\n\n    bool same(int a, int b)\
    \ {\n        return leader(a) == leader(b);\n    }\n\n    bool same(int a, int\
    \ b) const {\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent_or_size[leader(a)];\n    }\n\n    int size(int\
    \ a) {\n        return group_size(a);\n    }\n\n    int size(int a) const {\n\
    \        return group_size(a);\n    }\n\n    T potential(int a) {\n        leader(a);\n\
    \        return diff_to_parent[a];\n    }\n\n    T potential(int a) const {\n\
    \        assert(0 <= a && a < _n);\n        T res = Group::id();\n        while\
    \ (parent_or_size[a] >= 0) {\n            res = Group::op(diff_to_parent[a], res);\n\
    \            a = parent_or_size[a];\n        }\n        return res;\n    }\n\n\
    \    T diff(int a, int b) {\n        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    T diff(int a, int b) const {\n        assert(same(a,\
    \ b));\n        return Group::op(Group::inv(potential(a)), potential(b));\n  \
    \  }\n\n    bool merge(int a, int b, const T& w) {\n        assert(0 <= a && a\
    \ < _n);\n        assert(0 <= b && b < _n);\n        int x = leader(a);\n    \
    \    int y = leader(b);\n        T pa = diff_to_parent[a], pb = diff_to_parent[b];\n\
    \        if (x == y) return Group::op(Group::inv(pa), pb) == w;\n\n        T y_from_x\
    \ = Group::op(Group::op(pa, w), Group::inv(pb));\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) {\n            std::swap(x, y);\n            y_from_x\
    \ = Group::inv(y_from_x);\n        }\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        diff_to_parent[y] = std::move(y_from_x);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() {\n\
    \        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int i\
    \ = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n\
    \            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
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
    }  // namespace m1une\n\n\n#line 6 \"verify/ds/dsu/potentialized_dsu.test.cpp\"\
    \n\n#line 8 \"verify/ds/dsu/potentialized_dsu.test.cpp\"\n#include <iostream>\n\
    #line 10 \"verify/ds/dsu/potentialized_dsu.test.cpp\"\n\nvoid self_test() {\n\
    \    using Add = m1une::monoid::Add<long long>;\n\n    m1une::ds::PotentializedDsu<Add>\
    \ add_dsu(5);\n    assert(add_dsu.size() == 5);\n    assert(!add_dsu.empty());\n\
    \n    assert(add_dsu.merge(0, 1, 3));\n    assert(add_dsu.merge(1, 2, 4));\n \
    \   assert(add_dsu.same(0, 2));\n    assert(add_dsu.diff(0, 1) == 3);\n    assert(add_dsu.diff(1,\
    \ 2) == 4);\n    assert(add_dsu.diff(0, 2) == 7);\n    assert(add_dsu.diff(2,\
    \ 0) == -7);\n    assert(add_dsu.merge(0, 2, 7));\n    assert(!add_dsu.merge(0,\
    \ 2, 8));\n\n    assert(add_dsu.merge(4, 0, -1));\n    assert(add_dsu.diff(4,\
    \ 0) == -1);\n    assert(add_dsu.diff(0, 4) == 1);\n    assert(add_dsu.size(1)\
    \ == 4);\n\n    const auto& const_add_dsu = add_dsu;\n    assert(const_add_dsu.same(4,\
    \ 2));\n    assert(const_add_dsu.diff(4, 2) == 6);\n\n    std::vector<std::vector<int>>\
    \ groups = add_dsu.groups();\n    assert(groups.size() == 2);\n\n    using Xor\
    \ = m1une::monoid::Xor<int>;\n\n    m1une::ds::PotentializedDsu<Xor> xor_dsu(4);\n\
    \    assert(xor_dsu.merge(0, 1, 5));\n    assert(xor_dsu.merge(1, 2, 6));\n  \
    \  assert(xor_dsu.diff(0, 1) == 5);\n    assert(xor_dsu.diff(1, 2) == 6);\n  \
    \  assert(xor_dsu.diff(0, 2) == (5 ^ 6));\n    assert(xor_dsu.merge(0, 2, 5 ^\
    \ 6));\n    assert(!xor_dsu.merge(0, 2, 2));\n    assert(xor_dsu.merge(3, 0, 9));\n\
    \    assert(xor_dsu.diff(3, 2) == (9 ^ 5 ^ 6));\n\n    m1une::ds::PotentializedDsu<Add>\
    \ empty;\n    assert(empty.size() == 0);\n    assert(empty.empty());\n}\n\nint\
    \ main() {\n    self_test();\n\n    using Add = m1une::monoid::Add<long long>;\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    m1une::ds::PotentializedDsu<Add> dsu(n);\n\
    \n    while (q--) {\n        int type, x, y;\n        std::cin >> type >> x >>\
    \ y;\n        if (type == 0) {\n            long long z;\n            std::cin\
    \ >> z;\n            dsu.merge(x, y, z);\n        } else {\n            if (dsu.same(x,\
    \ y)) {\n                std::cout << dsu.diff(x, y) << '\\n';\n            }\
    \ else {\n                std::cout << \"?\\n\";\n            }\n        }\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include \"../../../ds/dsu/potentialized_dsu.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n#include \"../../../monoid/xor.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\nvoid self_test() {\n    using Add = m1une::monoid::Add<long\
    \ long>;\n\n    m1une::ds::PotentializedDsu<Add> add_dsu(5);\n    assert(add_dsu.size()\
    \ == 5);\n    assert(!add_dsu.empty());\n\n    assert(add_dsu.merge(0, 1, 3));\n\
    \    assert(add_dsu.merge(1, 2, 4));\n    assert(add_dsu.same(0, 2));\n    assert(add_dsu.diff(0,\
    \ 1) == 3);\n    assert(add_dsu.diff(1, 2) == 4);\n    assert(add_dsu.diff(0,\
    \ 2) == 7);\n    assert(add_dsu.diff(2, 0) == -7);\n    assert(add_dsu.merge(0,\
    \ 2, 7));\n    assert(!add_dsu.merge(0, 2, 8));\n\n    assert(add_dsu.merge(4,\
    \ 0, -1));\n    assert(add_dsu.diff(4, 0) == -1);\n    assert(add_dsu.diff(0,\
    \ 4) == 1);\n    assert(add_dsu.size(1) == 4);\n\n    const auto& const_add_dsu\
    \ = add_dsu;\n    assert(const_add_dsu.same(4, 2));\n    assert(const_add_dsu.diff(4,\
    \ 2) == 6);\n\n    std::vector<std::vector<int>> groups = add_dsu.groups();\n\
    \    assert(groups.size() == 2);\n\n    using Xor = m1une::monoid::Xor<int>;\n\
    \n    m1une::ds::PotentializedDsu<Xor> xor_dsu(4);\n    assert(xor_dsu.merge(0,\
    \ 1, 5));\n    assert(xor_dsu.merge(1, 2, 6));\n    assert(xor_dsu.diff(0, 1)\
    \ == 5);\n    assert(xor_dsu.diff(1, 2) == 6);\n    assert(xor_dsu.diff(0, 2)\
    \ == (5 ^ 6));\n    assert(xor_dsu.merge(0, 2, 5 ^ 6));\n    assert(!xor_dsu.merge(0,\
    \ 2, 2));\n    assert(xor_dsu.merge(3, 0, 9));\n    assert(xor_dsu.diff(3, 2)\
    \ == (9 ^ 5 ^ 6));\n\n    m1une::ds::PotentializedDsu<Add> empty;\n    assert(empty.size()\
    \ == 0);\n    assert(empty.empty());\n}\n\nint main() {\n    self_test();\n\n\
    \    using Add = m1une::monoid::Add<long long>;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    m1une::ds::PotentializedDsu<Add>\
    \ dsu(n);\n\n    while (q--) {\n        int type, x, y;\n        std::cin >> type\
    \ >> x >> y;\n        if (type == 0) {\n            long long z;\n           \
    \ std::cin >> z;\n            dsu.merge(x, y, z);\n        } else {\n        \
    \    if (dsu.same(x, y)) {\n                std::cout << dsu.diff(x, y) << '\\\
    n';\n            } else {\n                std::cout << \"?\\n\";\n          \
    \  }\n        }\n    }\n}\n"
  dependsOn:
  - ds/dsu/potentialized_dsu.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - monoid/xor.hpp
  isVerificationFile: true
  path: verify/ds/dsu/potentialized_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 02:52:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/potentialized_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/potentialized_dsu.test.cpp
- /verify/verify/ds/dsu/potentialized_dsu.test.cpp.html
title: verify/ds/dsu/potentialized_dsu.test.cpp
---
