---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dynamic_array.hpp
    title: Dynamic Array (Implicit Treap)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C
  bundledCode: "#line 1 \"verify/data_structure/dynamic_array.test.cpp\"\n#define\
    \ PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#line 1 \"data_structure/dynamic_array.hpp\"\n\n\n\n#line\
    \ 6 \"data_structure/dynamic_array.hpp\"\n#include <initializer_list>\n#line 10\
    \ \"data_structure/dynamic_array.hpp\"\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\ntemplate <typename T>\nstruct DynamicArray {\n   private:\n    struct Node\
    \ {\n        T val;\n        int priority;\n        int count;\n        int l,\
    \ r;\n        bool rev;\n\n        Node() : val(T()), priority(0), count(0), l(0),\
    \ r(0), rev(false) {}\n        Node(T value, int node_priority)\n            :\
    \ val(std::move(value)), priority(node_priority), count(1), l(0), r(0), rev(false)\
    \ {}\n    };\n\n    std::vector<Node> pool;\n    int root;\n    std::mt19937 rng;\n\
    \n    int new_node(T val) {\n        pool.push_back(Node(std::move(val), rng()));\n\
    \        return pool.size() - 1;\n    }\n\n    void update(int t) {\n        if\
    \ (t) {\n            pool[t].count = 1 + pool[pool[t].l].count + pool[pool[t].r].count;\n\
    \        }\n    }\n\n    void apply_reverse(int t) {\n        if (t) {\n     \
    \       pool[t].rev = !pool[t].rev;\n        }\n    }\n\n    void push(int t)\
    \ {\n        if (!t || !pool[t].rev) return;\n        std::swap(pool[t].l, pool[t].r);\n\
    \        apply_reverse(pool[t].l);\n        apply_reverse(pool[t].r);\n      \
    \  pool[t].rev = false;\n    }\n\n    void split(int t, int pos, int& l, int&\
    \ r) {\n        if (!t) {\n            l = r = 0;\n            return;\n     \
    \   }\n        push(t);\n        int left_count = pool[pool[t].l].count;\n   \
    \     if (pos <= left_count) {\n            split(pool[t].l, pos, l, pool[t].l);\n\
    \            r = t;\n        } else {\n            split(pool[t].r, pos - left_count\
    \ - 1, pool[t].r, r);\n            l = t;\n        }\n        update(t);\n   \
    \ }\n\n    int merge(int l, int r) {\n        if (!l || !r) return l ? l : r;\n\
    \        push(l);\n        push(r);\n        if (pool[l].priority > pool[r].priority)\
    \ {\n            pool[l].r = merge(pool[l].r, r);\n            update(l);\n  \
    \          return l;\n        } else {\n            pool[r].l = merge(l, pool[r].l);\n\
    \            update(r);\n            return r;\n        }\n    }\n\n    int find_node(int\
    \ t, int pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = pool[pool[t].l].count;\n            if (pos < left_count) {\n            \
    \    t = pool[t].l;\n            } else if (pos == left_count) {\n           \
    \     return t;\n            } else {\n                pos -= left_count + 1;\n\
    \                t = pool[t].r;\n            }\n        }\n        return 0;\n\
    \    }\n\n    int find_node(int t, int pos, bool reversed) const {\n        while\
    \ (t) {\n            bool cur_reversed = reversed ^ pool[t].rev;\n           \
    \ int left = cur_reversed ? pool[t].r : pool[t].l;\n            int right = cur_reversed\
    \ ? pool[t].l : pool[t].r;\n            int left_count = pool[left].count;\n \
    \           if (pos < left_count) {\n                t = left;\n             \
    \   reversed = cur_reversed;\n            } else if (pos == left_count) {\n  \
    \              return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = right;\n                reversed = cur_reversed;\n\
    \            }\n        }\n        return 0;\n    }\n\n    void dump_dfs(int t,\
    \ std::vector<T>& res, bool reversed = false) const {\n        if (!t) return;\n\
    \        bool cur_reversed = reversed ^ pool[t].rev;\n        int left = cur_reversed\
    \ ? pool[t].r : pool[t].l;\n        int right = cur_reversed ? pool[t].l : pool[t].r;\n\
    \        dump_dfs(left, res, cur_reversed);\n        res.push_back(pool[t].val);\n\
    \        dump_dfs(right, res, cur_reversed);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const\
    \ {\n        if (!t || qr <= offset || offset + pool[t].count <= ql) return;\n\
    \        bool cur_reversed = reversed ^ pool[t].rev;\n        int left = cur_reversed\
    \ ? pool[t].r : pool[t].l;\n        int right = cur_reversed ? pool[t].l : pool[t].r;\n\
    \        int left_count = pool[left].count;\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(left, ql, qr, offset, res, cur_reversed);\n        if\
    \ (ql <= node_pos && node_pos < qr) {\n            res.push_back(pool[t].val);\n\
    \        }\n        dump_range_dfs(right, ql, qr, node_pos + 1, res, cur_reversed);\n\
    \    }\n\n    int clone_subtree_from(const DynamicArray& other, int t) {\n   \
    \     if (!t) return 0;\n        int res = static_cast<int>(pool.size());\n  \
    \      pool.push_back(other.pool[t]);\n        pool[res].l = clone_subtree_from(other,\
    \ other.pool[t].l);\n        pool[res].r = clone_subtree_from(other, other.pool[t].r);\n\
    \        return res;\n    }\n\n    int build_from_vector(const std::vector<T>&\
    \ v) {\n        int res = 0;\n        for (const T& x : v) {\n            res\
    \ = merge(res, new_node(x));\n        }\n        return res;\n    }\n\n    int\
    \ build_from_vector(std::vector<T>&& v) {\n        int res = 0;\n        for (T&\
    \ x : v) {\n            res = merge(res, new_node(std::move(x)));\n        }\n\
    \        return res;\n    }\n\n    void reset_to_empty() {\n        pool.clear();\n\
    \        pool.push_back(Node());\n        root = 0;\n    }\n\n   public:\n   \
    \ DynamicArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {\n        pool.push_back(Node());\n    }\n\n    DynamicArray(const DynamicArray&\
    \ other) : pool(other.pool), root(other.root), rng(other.rng) {}\n\n    DynamicArray(DynamicArray&&\
    \ other) noexcept\n        : pool(std::move(other.pool)), root(other.root), rng(std::move(other.rng))\
    \ {\n        other.reset_to_empty();\n    }\n\n    DynamicArray& operator=(const\
    \ DynamicArray& other) {\n        if (this != &other) {\n            pool = other.pool;\n\
    \            root = other.root;\n            rng = other.rng;\n        }\n   \
    \     return *this;\n    }\n\n    DynamicArray& operator=(DynamicArray&& other)\
    \ noexcept {\n        if (this != &other) {\n            pool = std::move(other.pool);\n\
    \            root = other.root;\n            rng = std::move(other.rng);\n   \
    \         other.reset_to_empty();\n        }\n        return *this;\n    }\n\n\
    \    explicit DynamicArray(int n) : DynamicArray(n, T()) {}\n\n    DynamicArray(int\
    \ n, const T& value) : DynamicArray() {\n        assert(0 <= n);\n        pool.reserve(n\
    \ + 1);\n        for (int i = 0; i < n; i++) {\n            root = merge(root,\
    \ new_node(value));\n        }\n    }\n\n    explicit DynamicArray(const std::vector<T>&\
    \ v) : DynamicArray() {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit DynamicArray(std::vector<T>&& v) : DynamicArray() {\n \
    \       pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    DynamicArray(std::initializer_list<T> init) : DynamicArray() {\n\
    \        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T val) {\n \
    \       assert(0 <= pos && pos <= size());\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, new_node(std::move(val))), r);\n\
    \    }\n\n    void insert(int pos, const std::vector<T>& v) {\n        assert(0\
    \ <= pos && pos <= size());\n        pool.reserve(pool.size() + v.size());\n \
    \       int mid = build_from_vector(v);\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::vector<T>&& v) {\n        assert(0 <= pos && pos <= size());\n   \
    \     pool.reserve(pool.size() + v.size());\n        int mid = build_from_vector(std::move(v));\n\
    \        int l, r;\n        split(root, pos, l, r);\n        root = merge(merge(l,\
    \ mid), r);\n    }\n\n    void insert(int pos, std::initializer_list<T> init)\
    \ {\n        insert(pos, std::vector<T>(init));\n    }\n\n    void insert(int\
    \ pos, const DynamicArray& other) {\n        assert(0 <= pos && pos <= size());\n\
    \        if (other.empty()) return;\n        pool.reserve(pool.size() + other.size());\n\
    \        int mid = clone_subtree_from(other, other.root);\n        int l, r;\n\
    \        split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n  \
    \  }\n\n    void push_back(T val) {\n        insert(size(), std::move(val));\n\
    \    }\n\n    void push_front(T val) {\n        insert(0, std::move(val));\n \
    \   }\n\n    void append(const std::vector<T>& v) {\n        insert(size(), v);\n\
    \    }\n\n    void append(std::vector<T>&& v) {\n        insert(size(), std::move(v));\n\
    \    }\n\n    void append(const DynamicArray& other) {\n        insert(size(),\
    \ other);\n    }\n\n    void erase(int pos) {\n        assert(0 <= pos && pos\
    \ < size());\n        erase(pos, pos + 1);\n    }\n\n    void erase(int l, int\
    \ r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r)\
    \ return;\n        int a, b, c;\n        split(root, l, a, b);\n        split(b,\
    \ r - l, b, c);\n        root = merge(a, c);\n    }\n\n    void pop_back() {\n\
    \        assert(!empty());\n        erase(size() - 1);\n    }\n\n    void pop_front()\
    \ {\n        assert(!empty());\n        erase(0);\n    }\n\n    T& at(int pos)\
    \ {\n        assert(0 <= pos && pos < size());\n        return pool[find_node(root,\
    \ pos)].val;\n    }\n\n    const T& at(int pos) const {\n        assert(0 <= pos\
    \ && pos < size());\n        return pool[find_node(root, pos, false)].val;\n \
    \   }\n\n    T& operator[](int pos) {\n        return at(pos);\n    }\n\n    const\
    \ T& operator[](int pos) const {\n        return at(pos);\n    }\n\n    T& front()\
    \ {\n        assert(!empty());\n        return at(0);\n    }\n\n    const T& front()\
    \ const {\n        assert(!empty());\n        return at(0);\n    }\n\n    T& back()\
    \ {\n        assert(!empty());\n        return at(size() - 1);\n    }\n\n    const\
    \ T& back() const {\n        assert(!empty());\n        return at(size() - 1);\n\
    \    }\n\n    void reverse(int l, int r) {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return;\n        int a, b, c;\n        split(root,\
    \ l, a, b);\n        split(b, r - l, b, c);\n        apply_reverse(b);\n     \
    \   root = merge(merge(a, b), c);\n    }\n\n    void reverse() {\n        apply_reverse(root);\n\
    \    }\n\n    void rotate(int l, int m, int r) {\n        assert(0 <= l && l <=\
    \ m && m <= r && r <= size());\n        if (l == m || m == r) return;\n      \
    \  int a, b, c, d;\n        split(root, l, a, b);\n        split(b, m - l, b,\
    \ c);\n        split(c, r - m, c, d);\n        root = merge(merge(a, c), merge(b,\
    \ d));\n    }\n\n    T get(int pos) const {\n        return at(pos);\n    }\n\n\
    \    void set(int pos, T val) {\n        at(pos) = std::move(val);\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicArray split_off(int pos) {\n        assert(0 <= pos && pos\
    \ <= size());\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = l;\n\n        DynamicArray res;\n        res.pool.reserve(pool[r].count +\
    \ 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return res;\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n#line\
    \ 7 \"verify/data_structure/dynamic_array.test.cpp\"\n\nint main() {\n    int\
    \ cursor = 0;\n    m1une::data_structure::DynamicArray<int> L;\n    int q;\n \
    \   cin >> q;\n    while (q--) {\n        int t;\n        cin >> t;\n        if\
    \ (t == 0) {\n            int x;\n            cin >> x;\n            L.insert(cursor,\
    \ x);\n        } else if (t == 1) {\n            int d;\n            cin >> d;\n\
    \            cursor += d;\n        } else {\n            L.erase(cursor);\n  \
    \      }\n    }\n    vector<int> ans = L.to_vector();\n    for (int x : ans) {\n\
    \        cout << x << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C\"\n\n\
    #include <bits/stdc++.h>\nusing namespace std;\n\n#include \"data_structure/dynamic_array.hpp\"\
    \n\nint main() {\n    int cursor = 0;\n    m1une::data_structure::DynamicArray<int>\
    \ L;\n    int q;\n    cin >> q;\n    while (q--) {\n        int t;\n        cin\
    \ >> t;\n        if (t == 0) {\n            int x;\n            cin >> x;\n  \
    \          L.insert(cursor, x);\n        } else if (t == 1) {\n            int\
    \ d;\n            cin >> d;\n            cursor += d;\n        } else {\n    \
    \        L.erase(cursor);\n        }\n    }\n    vector<int> ans = L.to_vector();\n\
    \    for (int x : ans) {\n        cout << x << '\\n';\n    }\n}\n"
  dependsOn:
  - data_structure/dynamic_array.hpp
  isVerificationFile: true
  path: verify/data_structure/dynamic_array.test.cpp
  requiredBy: []
  timestamp: '2026-06-14 03:55:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/dynamic_array.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/dynamic_array.test.cpp
- /verify/verify/data_structure/dynamic_array.test.cpp.html
title: verify/data_structure/dynamic_array.test.cpp
---
