---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/data_structure/fenwick_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#line 1 \"data_structure/fenwick_tree.hpp\"\
    \n\n\n\n#line 6 \"data_structure/fenwick_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\ntemplate <typename T>\nstruct FenwickTree {\n   private:\n\
    \    int _n;\n    std::vector<T> _data;\n\n   public:\n    FenwickTree() : _n(0)\
    \ {}\n\n    explicit FenwickTree(int n) : _n(n), _data(n + 1, T{}) {}\n\n    explicit\
    \ FenwickTree(const std::vector<T>& a)\n        : _n(int(a.size())), _data(a.size()\
    \ + 1, T{}) {\n        for (int i = 1; i <= _n; ++i) {\n            _data[i] +=\
    \ a[i - 1];\n            const int p = i + (i & -i);\n            if (p <= _n)\
    \ {\n                _data[p] += _data[i];\n            }\n        }\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    // Adds `x` to the element at zero-based\
    \ index `p`.\n    void add(int p, const T& x) {\n        assert(0 <= p && p <\
    \ _n);\n        ++p;\n        while (p <= _n) {\n            _data[p] += x;\n\
    \            p += p & -p;\n        }\n    }\n\n    // Returns the sum of elements\
    \ in the range [0, r).\n    T sum(int r) const {\n        assert(0 <= r && r <=\
    \ _n);\n        T result{};\n        while (r > 0) {\n            result += _data[r];\n\
    \            r -= r & -r;\n        }\n        return result;\n    }\n\n    //\
    \ Returns the sum of elements in the range [l, r).\n    T sum(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        return sum(r) - sum(l);\n\
    \    }\n\n    // Returns the minimum index `r` such that the sum of [0, r) >=\
    \ w.\n    // Requires all elements in the tree to be non-negative.\n    int lower_bound(T\
    \ w) const {\n        if (w <= 0) return 0;\n        int x = 0;\n        int k\
    \ = 1;\n        while (k <= _n) k <<= 1;\n        for (k >>= 1; k > 0; k >>= 1)\
    \ {\n            if (x + k <= _n && _data[x + k] < w) {\n                w -=\
    \ _data[x + k];\n                x += k;\n            }\n        }\n        return\
    \ x + 1;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\
    \n\n#line 8 \"verify/data_structure/fenwick_tree.test.cpp\"\n\nvoid test_fenwick_tree()\
    \ {\n    const std::vector<long long> values = {1, 2, 3};\n    m1une::data_structure::FenwickTree<long\
    \ long> tree(values);\n\n    assert(tree.size() == 3);\n    assert(!tree.empty());\n\
    \    assert(tree.sum(0) == 0);\n    assert(tree.sum(3) == 6);\n    assert(tree.sum(1,\
    \ 3) == 5);\n    assert(tree.lower_bound(0) == 0);\n    assert(tree.lower_bound(1)\
    \ == 1);\n    assert(tree.lower_bound(3) == 2);\n    assert(tree.lower_bound(6)\
    \ == 3);\n    assert(tree.lower_bound(7) == 4);\n\n    m1une::data_structure::FenwickTree<long\
    \ long> empty;\n    assert(empty.empty());\n    assert(empty.lower_bound(1) ==\
    \ 1);\n}\n\nint main() {\n    test_fenwick_tree();\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<long long> values(n);\n    for (long long& value\
    \ : values) {\n        std::cin >> value;\n    }\n\n    m1une::data_structure::FenwickTree<long\
    \ long> tree(values);\n    for (int query = 0; query < q; ++query) {\n       \
    \ int type;\n        std::cin >> type;\n        if (type == 0) {\n           \
    \ int p;\n            long long x;\n            std::cin >> p >> x;\n        \
    \    tree.add(p, x);\n        } else {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            std::cout << tree.sum(l, r) << '\\n';\n        }\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <cassert>\n#include <iostream>\n#include <vector>\n\n#include \"data_structure/fenwick_tree.hpp\"\
    \n\nvoid test_fenwick_tree() {\n    const std::vector<long long> values = {1,\
    \ 2, 3};\n    m1une::data_structure::FenwickTree<long long> tree(values);\n\n\
    \    assert(tree.size() == 3);\n    assert(!tree.empty());\n    assert(tree.sum(0)\
    \ == 0);\n    assert(tree.sum(3) == 6);\n    assert(tree.sum(1, 3) == 5);\n  \
    \  assert(tree.lower_bound(0) == 0);\n    assert(tree.lower_bound(1) == 1);\n\
    \    assert(tree.lower_bound(3) == 2);\n    assert(tree.lower_bound(6) == 3);\n\
    \    assert(tree.lower_bound(7) == 4);\n\n    m1une::data_structure::FenwickTree<long\
    \ long> empty;\n    assert(empty.empty());\n    assert(empty.lower_bound(1) ==\
    \ 1);\n}\n\nint main() {\n    test_fenwick_tree();\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<long long> values(n);\n    for (long long& value\
    \ : values) {\n        std::cin >> value;\n    }\n\n    m1une::data_structure::FenwickTree<long\
    \ long> tree(values);\n    for (int query = 0; query < q; ++query) {\n       \
    \ int type;\n        std::cin >> type;\n        if (type == 0) {\n           \
    \ int p;\n            long long x;\n            std::cin >> p >> x;\n        \
    \    tree.add(p, x);\n        } else {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            std::cout << tree.sum(l, r) << '\\n';\n        }\n \
    \   }\n}\n"
  dependsOn:
  - data_structure/fenwick_tree.hpp
  isVerificationFile: true
  path: verify/data_structure/fenwick_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/fenwick_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/fenwick_tree.test.cpp
- /verify/verify/data_structure/fenwick_tree.test.cpp.html
title: verify/data_structure/fenwick_tree.test.cpp
---
