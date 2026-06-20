---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_dsu.hpp
    title: Persistent DSU
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"verify/ds/dsu/persistent_dsu_library_checker.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"ds/dsu/persistent_dsu.hpp\"\
    \n\n\n\n#line 9 \"ds/dsu/persistent_dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct PersistentDsu {\n   private:\n    struct Node {\n        int\
    \ val;\n        int l, r;\n\n        Node() : val(0), l(0), r(0) {}\n        explicit\
    \ Node(int value) : val(value), l(0), r(0) {}\n        Node(int value, int left,\
    \ int right) : val(value), l(left), r(right) {}\n    };\n\n    int _n;\n    int\
    \ _root;\n    std::shared_ptr<std::vector<Node>> _pool;\n\n    explicit PersistentDsu(int\
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
    \  // namespace m1une\n\n\n#line 7 \"verify/ds/dsu/persistent_dsu_library_checker.test.cpp\"\
    \nusing namespace m1une::ds;\n\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n    int N, Q;\n    cin >> N >> Q;\n    vector<PersistentDsu>\
    \ dsus;\n    dsus.push_back(PersistentDsu(N));\n    while (Q--) {\n        int\
    \ t, k, u, v;\n        cin >> t >> k >> u >> v;\n        if (t == 0) {\n     \
    \       dsus.push_back(dsus[k + 1].merge(u, v));\n        } else {\n         \
    \   cout << int(dsus[k + 1].same(u, v)) << '\\n';\n            dsus.push_back(PersistentDsu(0));\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../../ds/dsu/persistent_dsu.hpp\"\
    \nusing namespace m1une::ds;\n\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n    int N, Q;\n    cin >> N >> Q;\n    vector<PersistentDsu>\
    \ dsus;\n    dsus.push_back(PersistentDsu(N));\n    while (Q--) {\n        int\
    \ t, k, u, v;\n        cin >> t >> k >> u >> v;\n        if (t == 0) {\n     \
    \       dsus.push_back(dsus[k + 1].merge(u, v));\n        } else {\n         \
    \   cout << int(dsus[k + 1].same(u, v)) << '\\n';\n            dsus.push_back(PersistentDsu(0));\n\
    \        }\n    }\n}\n"
  dependsOn:
  - ds/dsu/persistent_dsu.hpp
  isVerificationFile: true
  path: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/persistent_dsu_library_checker.test.cpp
- /verify/verify/ds/dsu/persistent_dsu_library_checker.test.cpp.html
title: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
---
