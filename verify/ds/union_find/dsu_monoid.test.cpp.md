---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/union_find/dsu_monoid.hpp
    title: DSU with Monoid
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
  bundledCode: "#line 1 \"verify/ds/union_find/dsu_monoid.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/union_find/dsu_monoid.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\
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
    \ 12 \"ds/union_find/dsu_monoid.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct DsuMonoid {\n    using T = typename\
    \ Monoid::value_type;\n\n   private:\n    int _n;\n    std::vector<int> parent_or_size;\n\
    \    std::vector<T> _prod;\n\n    static int check_size(int n) {\n        assert(0\
    \ <= n);\n        return n;\n    }\n\n    template <typename U>\n    static T\
    \ make_value(const U& value, int index) {\n        if constexpr (requires(U x)\
    \ { Monoid::make(x); }) {\n            return Monoid::make(value);\n        }\
    \ else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n       \
    \     return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n   public:\n    DsuMonoid() : DsuMonoid(0)\
    \ {}\n\n    explicit DsuMonoid(int n) : DsuMonoid(n, Monoid::id()) {}\n\n    DsuMonoid(int\
    \ n, const T& value) : _n(check_size(n)), parent_or_size(_n, -1), _prod(_n, value)\
    \ {}\n\n    explicit DsuMonoid(const std::vector<T>& v) : _n(int(v.size())), parent_or_size(_n,\
    \ -1), _prod(v) {}\n\n    explicit DsuMonoid(std::vector<T>&& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(std::move(v)) {}\n\n    template <typename U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { Monoid::make(x);\
    \ } ||\n        requires(U x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DsuMonoid(const std::vector<U>& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(_n, Monoid::id()) {\n        for (int i = 0; i\
    \ < _n; i++) _prod[i] = make_value(v[i], i);\n    }\n\n    DsuMonoid(std::initializer_list<T>\
    \ init) : DsuMonoid(std::vector<T>(init)) {}\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int merge(int a, int b) {\n        assert(0 <= a && a < _n);\n  \
    \      assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return x;\n        T merged = Monoid::op(_prod[x], _prod[y]);\n\
    \        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\n     \
    \   parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y] = x;\n\
    \        _prod[x] = std::move(merged);\n        return x;\n    }\n\n    bool same(int\
    \ a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    bool same(int\
    \ a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n    int\
    \ leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return\
    \ a;\n    }\n\n    int group_size(int a) {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int size(int a) {\n        return group_size(a);\n    }\n\n    int\
    \ size(int a) const {\n        return group_size(a);\n    }\n\n    T prod(int\
    \ a) {\n        return _prod[leader(a)];\n    }\n\n    T prod(int a) const {\n\
    \        return _prod[leader(a)];\n    }\n\n    T get(int a) {\n        return\
    \ prod(a);\n    }\n\n    T get(int a) const {\n        return prod(a);\n    }\n\
    \n    void set(int a, T value) {\n        _prod[leader(a)] = std::move(value);\n\
    \    }\n\n    std::vector<std::vector<int>> groups() {\n        std::vector<int>\
    \ leader_buf(_n), group_size(_n);\n        for (int i = 0; i < _n; i++) {\n  \
    \          leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
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
    }  // namespace m1une\n\n\n#line 5 \"verify/ds/union_find/dsu_monoid.test.cpp\"\
    \n\n#line 7 \"verify/ds/union_find/dsu_monoid.test.cpp\"\n#include <iostream>\n\
    #include <string>\n#line 10 \"verify/ds/union_find/dsu_monoid.test.cpp\"\n\nstruct\
    \ StringMonoid {\n    using value_type = std::string;\n\n    static std::string\
    \ id() {\n        return \"\";\n    }\n\n    static std::string op(const std::string&\
    \ a, const std::string& b) {\n        return a + b;\n    }\n};\n\nint main() {\n\
    \    using Sum = m1une::monoid::Add<long long>;\n\n    m1une::ds::DsuMonoid<Sum>\
    \ dsu(std::vector<int>{1, 2, 3, 4, 5});\n    assert(dsu.size() == 5);\n    assert(!dsu.empty());\n\
    \    for (int i = 0; i < dsu.size(); i++) {\n        assert(dsu.size(i) == 1);\n\
    \        assert(dsu.prod(i) == i + 1);\n    }\n\n    dsu.merge(0, 1);\n    assert(dsu.same(0,\
    \ 1));\n    assert(dsu.size(0) == 2);\n    assert(dsu.prod(0) == 3);\n    assert(dsu.prod(1)\
    \ == 3);\n\n    dsu.merge(2, 3);\n    assert(dsu.prod(2) == 7);\n    dsu.merge(1,\
    \ 2);\n    assert(dsu.same(0, 3));\n    assert(!dsu.same(0, 4));\n    assert(dsu.size(3)\
    \ == 4);\n    assert(dsu.prod(3) == 10);\n\n    dsu.set(4, 100);\n    assert(dsu.prod(4)\
    \ == 100);\n    dsu.merge(4, 0);\n    assert(dsu.size(0) == 5);\n    assert(dsu.prod(0)\
    \ == 110);\n\n    std::vector<std::vector<int>> groups = dsu.groups();\n    std::vector<int>\
    \ all = {0, 1, 2, 3, 4};\n    assert(groups.size() == 1);\n    assert(groups[0]\
    \ == all);\n\n    m1une::ds::DsuMonoid<StringMonoid> words(std::vector<std::string>{\"\
    a\", \"b\", \"c\", \"d\"});\n    words.merge(2, 1);\n    assert(words.prod(1)\
    \ == \"cb\");\n    words.merge(0, 2);\n    assert(words.prod(2) == \"acb\");\n\
    \    words.set(3, \"x\");\n    words.merge(3, 0);\n    assert(words.prod(0) ==\
    \ \"xacb\");\n\n    m1une::ds::DsuMonoid<Sum> empty;\n    assert(empty.size()\
    \ == 0);\n    assert(empty.empty());\n\n    long long x, y;\n    std::cin >> x\
    \ >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ds/union_find/dsu_monoid.hpp\"\n#include \"monoid/add.hpp\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <string>\n#include <vector>\n\nstruct StringMonoid\
    \ {\n    using value_type = std::string;\n\n    static std::string id() {\n  \
    \      return \"\";\n    }\n\n    static std::string op(const std::string& a,\
    \ const std::string& b) {\n        return a + b;\n    }\n};\n\nint main() {\n\
    \    using Sum = m1une::monoid::Add<long long>;\n\n    m1une::ds::DsuMonoid<Sum>\
    \ dsu(std::vector<int>{1, 2, 3, 4, 5});\n    assert(dsu.size() == 5);\n    assert(!dsu.empty());\n\
    \    for (int i = 0; i < dsu.size(); i++) {\n        assert(dsu.size(i) == 1);\n\
    \        assert(dsu.prod(i) == i + 1);\n    }\n\n    dsu.merge(0, 1);\n    assert(dsu.same(0,\
    \ 1));\n    assert(dsu.size(0) == 2);\n    assert(dsu.prod(0) == 3);\n    assert(dsu.prod(1)\
    \ == 3);\n\n    dsu.merge(2, 3);\n    assert(dsu.prod(2) == 7);\n    dsu.merge(1,\
    \ 2);\n    assert(dsu.same(0, 3));\n    assert(!dsu.same(0, 4));\n    assert(dsu.size(3)\
    \ == 4);\n    assert(dsu.prod(3) == 10);\n\n    dsu.set(4, 100);\n    assert(dsu.prod(4)\
    \ == 100);\n    dsu.merge(4, 0);\n    assert(dsu.size(0) == 5);\n    assert(dsu.prod(0)\
    \ == 110);\n\n    std::vector<std::vector<int>> groups = dsu.groups();\n    std::vector<int>\
    \ all = {0, 1, 2, 3, 4};\n    assert(groups.size() == 1);\n    assert(groups[0]\
    \ == all);\n\n    m1une::ds::DsuMonoid<StringMonoid> words(std::vector<std::string>{\"\
    a\", \"b\", \"c\", \"d\"});\n    words.merge(2, 1);\n    assert(words.prod(1)\
    \ == \"cb\");\n    words.merge(0, 2);\n    assert(words.prod(2) == \"acb\");\n\
    \    words.set(3, \"x\");\n    words.merge(3, 0);\n    assert(words.prod(0) ==\
    \ \"xacb\");\n\n    m1une::ds::DsuMonoid<Sum> empty;\n    assert(empty.size()\
    \ == 0);\n    assert(empty.empty());\n\n    long long x, y;\n    std::cin >> x\
    \ >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/union_find/dsu_monoid.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/union_find/dsu_monoid.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/union_find/dsu_monoid.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/union_find/dsu_monoid.test.cpp
- /verify/verify/ds/union_find/dsu_monoid.test.cpp.html
title: verify/ds/union_find/dsu_monoid.test.cpp
---
