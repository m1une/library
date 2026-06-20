---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/union_find/persistent_dsu.hpp
    title: Persistent DSU
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
  bundledCode: "#line 1 \"verify/ds/union_find/persistent_dsu.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/union_find/persistent_dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <memory>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ PersistentDsu {\n   private:\n    struct Node {\n        int val;\n        int\
    \ l, r;\n\n        Node() : val(0), l(0), r(0) {}\n        explicit Node(int value)\
    \ : val(value), l(0), r(0) {}\n        Node(int value, int left, int right) :\
    \ val(value), l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n  \
    \  std::shared_ptr<std::vector<Node>> _pool;\n\n    explicit PersistentDsu(int\
    \ n, int root, std::shared_ptr<std::vector<Node>> pool)\n        : _n(n), _root(root),\
    \ _pool(std::move(pool)) {}\n\n    int new_node(const Node& node) const {\n  \
    \      _pool->push_back(node);\n        return int(_pool->size()) - 1;\n    }\n\
    \n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int build(int l, int r)\
    \ const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(-1));\n\
    \        int m = (l + r) >> 1;\n        int left = build(l, m);\n        int right\
    \ = build(m, r);\n        return new_node(Node(0, left, right));\n    }\n\n  \
    \  int set_node(int t, int l, int r, int p, int value) const {\n        if (r\
    \ - l == 1) return new_node(Node(value));\n        int m = (l + r) >> 1;\n   \
    \     int left = (*_pool)[t].l;\n        int right = (*_pool)[t].r;\n        if\
    \ (p < m) {\n            left = set_node(left, l, m, p, value);\n        } else\
    \ {\n            right = set_node(right, m, r, p, value);\n        }\n       \
    \ return new_node(Node(0, left, right));\n    }\n\n    int get_node(int t, int\
    \ l, int r, int p) const {\n        while (r - l > 1) {\n            int m = (l\
    \ + r) >> 1;\n            if (p < m) {\n                t = (*_pool)[t].l;\n \
    \               r = m;\n            } else {\n                t = (*_pool)[t].r;\n\
    \                l = m;\n            }\n        }\n        return (*_pool)[t].val;\n\
    \    }\n\n   public:\n    PersistentDsu() : PersistentDsu(0) {}\n\n    explicit\
    \ PersistentDsu(int n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        assert(0 <= n);\n        _pool->reserve(n * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       int x = a;\n        int p = get(x);\n        while (p >= 0) {\n      \
    \      x = p;\n            p = get(x);\n        }\n        return x;\n    }\n\n\
    \    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n    \
    \    assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n    }\n\
    \n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n     \
    \   return -get(leader(a));\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    int get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return get_node(_root, 0, _n, p);\n    }\n\n    PersistentDsu\
    \ merge(int a, int b) const {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return *this;\n        int sx = -get(x), sy = -get(y);\n        if (sx <\
    \ sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n      \
    \  }\n        int root = set_node(_root, 0, _n, x, -(sx + sy));\n        root\
    \ = set_node(root, 0, _n, y, x);\n        return PersistentDsu(_n, root, _pool);\n\
    \    }\n\n    std::vector<std::vector<int>> groups() const {\n        std::vector<int>\
    \ leader_buf(_n), group_size(_n);\n        for (int i = 0; i < _n; i++) {\n  \
    \          leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 4 \"verify/ds/union_find/persistent_dsu.test.cpp\"\
    \n\n#line 7 \"verify/ds/union_find/persistent_dsu.test.cpp\"\n#include <iostream>\n\
    #include <random>\n#line 11 \"verify/ds/union_find/persistent_dsu.test.cpp\"\n\
    \nstruct NaiveDsu {\n    std::vector<int> parent_or_size;\n\n    explicit NaiveDsu(int\
    \ n = 0) : parent_or_size(n, -1) {}\n\n    int leader(int a) const {\n       \
    \ while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return a;\n \
    \   }\n\n    bool same(int a, int b) const {\n        return leader(a) == leader(b);\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    NaiveDsu merge(int a, int b) const {\n        NaiveDsu res = *this;\n\
    \        int x = res.leader(a), y = res.leader(b);\n        if (x == y) return\
    \ res;\n        if (-res.parent_or_size[x] < -res.parent_or_size[y]) std::swap(x,\
    \ y);\n        res.parent_or_size[x] += res.parent_or_size[y];\n        res.parent_or_size[y]\
    \ = x;\n        return res;\n    }\n\n    std::vector<std::vector<int>> groups()\
    \ const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nint main()\
    \ {\n    using Dsu = m1une::ds::PersistentDsu;\n\n    Dsu dsu(5);\n    Dsu a =\
    \ dsu.merge(0, 1);\n    Dsu b = a.merge(2, 3);\n    Dsu c = b.merge(1, 2);\n \
    \   Dsu d = c.merge(3, 4);\n\n    assert(dsu.size() == 5);\n    assert(!dsu.empty());\n\
    \    assert(dsu.same(0, 1) == false);\n    assert(a.same(0, 1) == true);\n   \
    \ assert(a.same(0, 2) == false);\n    assert(b.same(2, 3) == true);\n    assert(c.same(0,\
    \ 3) == true);\n    assert(c.same(0, 4) == false);\n    assert(d.same(0, 4) ==\
    \ true);\n    assert(d.group_size(0) == 5);\n    assert(d.size(0) == 5);\n   \
    \ assert(a.group_size(0) == 2);\n    assert(dsu.group_size(0) == 1);\n    std::vector<std::vector<int>>\
    \ singleton_groups = {\n        std::vector<int>{0}, std::vector<int>{1}, std::vector<int>{2},\
    \ std::vector<int>{3}, std::vector<int>{4},\n    };\n    std::vector<std::vector<int>>\
    \ merged_groups = {std::vector<int>{0, 1, 2, 3}, std::vector<int>{4}};\n    assert(dsu.groups()\
    \ == singleton_groups);\n    assert(c.groups() == merged_groups);\n\n    Dsu empty;\n\
    \    assert(empty.size() == 0);\n    assert(empty.empty());\n\n    std::mt19937\
    \ rng(0);\n    constexpr int N = 30;\n    std::vector<std::pair<Dsu, NaiveDsu>>\
    \ versions;\n    versions.push_back({Dsu(N), NaiveDsu(N)});\n\n    for (int step\
    \ = 0; step < 500; step++) {\n        int id = int(rng() % versions.size());\n\
    \        const Dsu cur = versions[id].first;\n        const NaiveDsu expected\
    \ = versions[id].second;\n\n        for (int i = 0; i < N; i++) {\n          \
    \  assert(cur.group_size(i) == expected.group_size(i));\n            assert(cur.get(i)\
    \ == expected.parent_or_size[i]);\n            for (int j = 0; j < N; j++) {\n\
    \                assert(cur.same(i, j) == expected.same(i, j));\n            }\n\
    \        }\n        assert(cur.groups() == expected.groups());\n\n        int\
    \ u = int(rng() % N);\n        int v = int(rng() % N);\n        Dsu next = cur.merge(u,\
    \ v);\n        NaiveDsu next_expected = expected.merge(u, v);\n\n        for (int\
    \ i = 0; i < N; i++) {\n            assert(cur.group_size(i) == expected.group_size(i));\n\
    \            assert(next.group_size(i) == next_expected.group_size(i));\n    \
    \        assert(next.get(i) == next_expected.parent_or_size[i]);\n        }\n\n\
    \        versions.push_back({next, next_expected});\n    }\n\n    long long x,\
    \ y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ds/union_find/persistent_dsu.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \nstruct NaiveDsu {\n    std::vector<int> parent_or_size;\n\n    explicit NaiveDsu(int\
    \ n = 0) : parent_or_size(n, -1) {}\n\n    int leader(int a) const {\n       \
    \ while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return a;\n \
    \   }\n\n    bool same(int a, int b) const {\n        return leader(a) == leader(b);\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    NaiveDsu merge(int a, int b) const {\n        NaiveDsu res = *this;\n\
    \        int x = res.leader(a), y = res.leader(b);\n        if (x == y) return\
    \ res;\n        if (-res.parent_or_size[x] < -res.parent_or_size[y]) std::swap(x,\
    \ y);\n        res.parent_or_size[x] += res.parent_or_size[y];\n        res.parent_or_size[y]\
    \ = x;\n        return res;\n    }\n\n    std::vector<std::vector<int>> groups()\
    \ const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nint main()\
    \ {\n    using Dsu = m1une::ds::PersistentDsu;\n\n    Dsu dsu(5);\n    Dsu a =\
    \ dsu.merge(0, 1);\n    Dsu b = a.merge(2, 3);\n    Dsu c = b.merge(1, 2);\n \
    \   Dsu d = c.merge(3, 4);\n\n    assert(dsu.size() == 5);\n    assert(!dsu.empty());\n\
    \    assert(dsu.same(0, 1) == false);\n    assert(a.same(0, 1) == true);\n   \
    \ assert(a.same(0, 2) == false);\n    assert(b.same(2, 3) == true);\n    assert(c.same(0,\
    \ 3) == true);\n    assert(c.same(0, 4) == false);\n    assert(d.same(0, 4) ==\
    \ true);\n    assert(d.group_size(0) == 5);\n    assert(d.size(0) == 5);\n   \
    \ assert(a.group_size(0) == 2);\n    assert(dsu.group_size(0) == 1);\n    std::vector<std::vector<int>>\
    \ singleton_groups = {\n        std::vector<int>{0}, std::vector<int>{1}, std::vector<int>{2},\
    \ std::vector<int>{3}, std::vector<int>{4},\n    };\n    std::vector<std::vector<int>>\
    \ merged_groups = {std::vector<int>{0, 1, 2, 3}, std::vector<int>{4}};\n    assert(dsu.groups()\
    \ == singleton_groups);\n    assert(c.groups() == merged_groups);\n\n    Dsu empty;\n\
    \    assert(empty.size() == 0);\n    assert(empty.empty());\n\n    std::mt19937\
    \ rng(0);\n    constexpr int N = 30;\n    std::vector<std::pair<Dsu, NaiveDsu>>\
    \ versions;\n    versions.push_back({Dsu(N), NaiveDsu(N)});\n\n    for (int step\
    \ = 0; step < 500; step++) {\n        int id = int(rng() % versions.size());\n\
    \        const Dsu cur = versions[id].first;\n        const NaiveDsu expected\
    \ = versions[id].second;\n\n        for (int i = 0; i < N; i++) {\n          \
    \  assert(cur.group_size(i) == expected.group_size(i));\n            assert(cur.get(i)\
    \ == expected.parent_or_size[i]);\n            for (int j = 0; j < N; j++) {\n\
    \                assert(cur.same(i, j) == expected.same(i, j));\n            }\n\
    \        }\n        assert(cur.groups() == expected.groups());\n\n        int\
    \ u = int(rng() % N);\n        int v = int(rng() % N);\n        Dsu next = cur.merge(u,\
    \ v);\n        NaiveDsu next_expected = expected.merge(u, v);\n\n        for (int\
    \ i = 0; i < N; i++) {\n            assert(cur.group_size(i) == expected.group_size(i));\n\
    \            assert(next.group_size(i) == next_expected.group_size(i));\n    \
    \        assert(next.get(i) == next_expected.parent_or_size[i]);\n        }\n\n\
    \        versions.push_back({next, next_expected});\n    }\n\n    long long x,\
    \ y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/union_find/persistent_dsu.hpp
  isVerificationFile: true
  path: verify/ds/union_find/persistent_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/union_find/persistent_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/union_find/persistent_dsu.test.cpp
- /verify/verify/ds/union_find/persistent_dsu.test.cpp.html
title: verify/ds/union_find/persistent_dsu.test.cpp
---
