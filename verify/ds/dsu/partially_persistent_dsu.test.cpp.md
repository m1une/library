---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/partially_persistent_dsu.hpp
    title: Partially Persistent DSU
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
  bundledCode: "#line 1 \"verify/ds/dsu/partially_persistent_dsu.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dsu/partially_persistent_dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ PartiallyPersistentDsu {\n   private:\n    static constexpr int never = std::numeric_limits<int>::max();\n\
    \n    int _n;\n    int _time;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_time;\n    std::vector<std::vector<std::pair<int, int>>> size_history;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n    void check_time(int t) const {\n        assert(0 <= t && t\
    \ <= _time);\n    }\n\n   public:\n    PartiallyPersistentDsu() : PartiallyPersistentDsu(0)\
    \ {}\n\n    explicit PartiallyPersistentDsu(int n)\n        : _n(check_size(n)),\
    \ _time(0), parent(_n, -1), parent_time(_n, never), size_history(_n) {\n     \
    \   for (int i = 0; i < _n; i++) size_history[i].emplace_back(0, 1);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    int time() const {\n        return _time;\n\
    \    }\n\n    int leader(int t, int a) const {\n        check_time(t);\n     \
    \   assert(0 <= a && a < _n);\n        while (parent_time[a] <= t) a = parent[a];\n\
    \        return a;\n    }\n\n    int leader(int a) const {\n        return leader(_time,\
    \ a);\n    }\n\n    bool same(int t, int a, int b) const {\n        check_time(t);\n\
    \        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n      \
    \  return leader(t, a) == leader(t, b);\n    }\n\n    bool same(int a, int b)\
    \ const {\n        return same(_time, a, b);\n    }\n\n    int group_size(int\
    \ t, int a) const {\n        int r = leader(t, a);\n        const auto& h = size_history[r];\n\
    \        auto it = std::upper_bound(h.begin(), h.end(), std::pair<int, int>(t,\
    \ never));\n        --it;\n        return it->second;\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent[leader(a)];\n    }\n\n    int size(int t,\
    \ int a) const {\n        return group_size(t, a);\n    }\n\n    int size(int\
    \ a) const {\n        return group_size(a);\n    }\n\n    bool merge(int a, int\
    \ b) {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n\
    \        ++_time;\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return false;\n        if (-parent[x] < -parent[y]) {\n            std::swap(x,\
    \ y);\n        }\n        parent[x] += parent[y];\n        parent[y] = x;\n  \
    \      parent_time[y] = _time;\n        size_history[x].emplace_back(_time, -parent[x]);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups(int t)\
    \ const {\n        check_time(t);\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(t,\
    \ i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        return groups(_time);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/dsu/partially_persistent_dsu.test.cpp\"\
    \n\n#line 7 \"verify/ds/dsu/partially_persistent_dsu.test.cpp\"\n#include <iostream>\n\
    #include <random>\n#line 11 \"verify/ds/dsu/partially_persistent_dsu.test.cpp\"\
    \n\nstruct NaiveDsu {\n    std::vector<int> parent_or_size;\n\n    explicit NaiveDsu(int\
    \ n = 0) : parent_or_size(n, -1) {}\n\n    int leader(int a) const {\n       \
    \ while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return a;\n \
    \   }\n\n    bool same(int a, int b) const {\n        return leader(a) == leader(b);\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    bool merge(int a, int b) {\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return false;\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return true;\n    }\n\n    std::vector<std::vector<int>> groups()\
    \ const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nint main()\
    \ {\n    using Dsu = m1une::ds::PartiallyPersistentDsu;\n\n    Dsu dsu(5);\n \
    \   assert(dsu.size() == 5);\n    assert(!dsu.empty());\n    assert(dsu.time()\
    \ == 0);\n\n    assert(dsu.merge(0, 1));\n    int t1 = dsu.time();\n    assert(dsu.merge(2,\
    \ 3));\n    int t2 = dsu.time();\n    assert(!dsu.merge(1, 0));\n    int t3 =\
    \ dsu.time();\n    assert(dsu.merge(1, 2));\n    int t4 = dsu.time();\n\n    assert(t1\
    \ == 1);\n    assert(t2 == 2);\n    assert(t3 == 3);\n    assert(t4 == 4);\n \
    \   assert(!dsu.same(0, 0, 1));\n    assert(dsu.same(t1, 0, 1));\n    assert(!dsu.same(t1,\
    \ 0, 2));\n    assert(dsu.same(t2, 2, 3));\n    assert(!dsu.same(t3, 0, 3));\n\
    \    assert(dsu.same(t4, 0, 3));\n    assert(dsu.size(t1, 0) == 2);\n    assert(dsu.size(t2,\
    \ 0) == 2);\n    assert(dsu.size(t2, 2) == 2);\n    assert(dsu.size(t4, 0) ==\
    \ 4);\n    assert(dsu.size(0) == 4);\n\n    std::vector<std::vector<int>> initial_groups;\n\
    \    initial_groups.emplace_back(std::vector<int>{0});\n    initial_groups.emplace_back(std::vector<int>{1});\n\
    \    initial_groups.emplace_back(std::vector<int>{2});\n    initial_groups.emplace_back(std::vector<int>{3});\n\
    \    initial_groups.emplace_back(std::vector<int>{4});\n    assert(dsu.groups(0)\
    \ == initial_groups);\n\n    Dsu empty;\n    assert(empty.size() == 0);\n    assert(empty.empty());\n\
    \    assert(empty.time() == 0);\n\n    std::mt19937 rng(1);\n    constexpr int\
    \ N = 30;\n    Dsu pp(N);\n    std::vector<NaiveDsu> states;\n    states.emplace_back(N);\n\
    \n    for (int step = 0; step < 500; step++) {\n        int u = int(rng() % N);\n\
    \        int v = int(rng() % N);\n        NaiveDsu next = states.back();\n   \
    \     bool expected_merged = next.merge(u, v);\n        bool merged = pp.merge(u,\
    \ v);\n        assert(merged == expected_merged);\n        states.push_back(next);\n\
    \        assert(pp.time() == int(states.size()) - 1);\n\n        for (int iter\
    \ = 0; iter < 5; iter++) {\n            int t = int(rng() % states.size());\n\
    \            const NaiveDsu& expected = states[t];\n            for (int i = 0;\
    \ i < N; i++) {\n                assert(pp.group_size(t, i) == expected.group_size(i));\n\
    \                for (int j = 0; j < N; j++) {\n                    assert(pp.same(t,\
    \ i, j) == expected.same(i, j));\n                }\n            }\n         \
    \   assert(pp.groups(t) == expected.groups());\n        }\n    }\n\n    long long\
    \ x, y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dsu/partially_persistent_dsu.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n#include\
    \ <vector>\n\nstruct NaiveDsu {\n    std::vector<int> parent_or_size;\n\n    explicit\
    \ NaiveDsu(int n = 0) : parent_or_size(n, -1) {}\n\n    int leader(int a) const\
    \ {\n        while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return\
    \ a;\n    }\n\n    bool same(int a, int b) const {\n        return leader(a) ==\
    \ leader(b);\n    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    bool merge(int a, int b) {\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return false;\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return true;\n    }\n\n    std::vector<std::vector<int>> groups()\
    \ const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nint main()\
    \ {\n    using Dsu = m1une::ds::PartiallyPersistentDsu;\n\n    Dsu dsu(5);\n \
    \   assert(dsu.size() == 5);\n    assert(!dsu.empty());\n    assert(dsu.time()\
    \ == 0);\n\n    assert(dsu.merge(0, 1));\n    int t1 = dsu.time();\n    assert(dsu.merge(2,\
    \ 3));\n    int t2 = dsu.time();\n    assert(!dsu.merge(1, 0));\n    int t3 =\
    \ dsu.time();\n    assert(dsu.merge(1, 2));\n    int t4 = dsu.time();\n\n    assert(t1\
    \ == 1);\n    assert(t2 == 2);\n    assert(t3 == 3);\n    assert(t4 == 4);\n \
    \   assert(!dsu.same(0, 0, 1));\n    assert(dsu.same(t1, 0, 1));\n    assert(!dsu.same(t1,\
    \ 0, 2));\n    assert(dsu.same(t2, 2, 3));\n    assert(!dsu.same(t3, 0, 3));\n\
    \    assert(dsu.same(t4, 0, 3));\n    assert(dsu.size(t1, 0) == 2);\n    assert(dsu.size(t2,\
    \ 0) == 2);\n    assert(dsu.size(t2, 2) == 2);\n    assert(dsu.size(t4, 0) ==\
    \ 4);\n    assert(dsu.size(0) == 4);\n\n    std::vector<std::vector<int>> initial_groups;\n\
    \    initial_groups.emplace_back(std::vector<int>{0});\n    initial_groups.emplace_back(std::vector<int>{1});\n\
    \    initial_groups.emplace_back(std::vector<int>{2});\n    initial_groups.emplace_back(std::vector<int>{3});\n\
    \    initial_groups.emplace_back(std::vector<int>{4});\n    assert(dsu.groups(0)\
    \ == initial_groups);\n\n    Dsu empty;\n    assert(empty.size() == 0);\n    assert(empty.empty());\n\
    \    assert(empty.time() == 0);\n\n    std::mt19937 rng(1);\n    constexpr int\
    \ N = 30;\n    Dsu pp(N);\n    std::vector<NaiveDsu> states;\n    states.emplace_back(N);\n\
    \n    for (int step = 0; step < 500; step++) {\n        int u = int(rng() % N);\n\
    \        int v = int(rng() % N);\n        NaiveDsu next = states.back();\n   \
    \     bool expected_merged = next.merge(u, v);\n        bool merged = pp.merge(u,\
    \ v);\n        assert(merged == expected_merged);\n        states.push_back(next);\n\
    \        assert(pp.time() == int(states.size()) - 1);\n\n        for (int iter\
    \ = 0; iter < 5; iter++) {\n            int t = int(rng() % states.size());\n\
    \            const NaiveDsu& expected = states[t];\n            for (int i = 0;\
    \ i < N; i++) {\n                assert(pp.group_size(t, i) == expected.group_size(i));\n\
    \                for (int j = 0; j < N; j++) {\n                    assert(pp.same(t,\
    \ i, j) == expected.same(i, j));\n                }\n            }\n         \
    \   assert(pp.groups(t) == expected.groups());\n        }\n    }\n\n    long long\
    \ x, y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/dsu/partially_persistent_dsu.hpp
  isVerificationFile: true
  path: verify/ds/dsu/partially_persistent_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 02:52:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/partially_persistent_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/partially_persistent_dsu.test.cpp
- /verify/verify/ds/dsu/partially_persistent_dsu.test.cpp.html
title: verify/ds/dsu/partially_persistent_dsu.test.cpp
---
