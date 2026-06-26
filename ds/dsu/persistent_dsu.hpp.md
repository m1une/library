---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu.test.cpp
    title: verify/ds/dsu/persistent_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
    title: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/persistent_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\nstruct PersistentDsu {\n   private:\n \
    \   struct Node {\n        int val;\n        int l, r;\n\n        Node() : val(0),\
    \ l(0), r(0) {}\n        explicit Node(int value) : val(value), l(0), r(0) {}\n\
    \        Node(int value, int left, int right) : val(value), l(left), r(right)\
    \ {}\n    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
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
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DSU_HPP\n#define M1UNE_PERSISTENT_DSU_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\nstruct PersistentDsu\
    \ {\n   private:\n    struct Node {\n        int val;\n        int l, r;\n\n \
    \       Node() : val(0), l(0), r(0) {}\n        explicit Node(int value) : val(value),\
    \ l(0), r(0) {}\n        Node(int value, int left, int right) : val(value), l(left),\
    \ r(right) {}\n    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
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
    \  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/persistent_dsu.hpp
  requiredBy: []
  timestamp: '2026-06-20 20:27:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/persistent_dsu.test.cpp
  - verify/ds/dsu/persistent_dsu_library_checker.test.cpp
documentation_of: ds/dsu/persistent_dsu.hpp
layout: document
title: Persistent DSU
---

## Overview

`PersistentDsu` is a persistent Union-Find data structure. Merge operations return a new version and leave the old version available.

It uses union by size without path compression, because path compression mutates the search path. Parent and size values are stored in a persistent array, so each merge shares most nodes with older versions.

## Complexity Notation

* `N` is the number of elements.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PersistentDsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `PersistentDsu merge(int a, int b) const` | Returns a new version where the sets containing `a` and `b` are merged. | $O(\log^2 N)$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | $O(\log^2 N)$ |
| `int leader(int a) const` | Returns the representative of the set containing `a`. | $O(\log^2 N)$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the size of the set containing `a`. | $O(\log^2 N)$ |
| `int get(int p) const` | Returns the internal parent-or-size value at index `p`. Roots store negative component sizes; non-roots store parent indices. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \log^2 N)$ |

## Example

```cpp
#include "ds/dsu/persistent_dsu.hpp"

#include <iostream>

using namespace m1une::ds;

int main() {
    PersistentDsu dsu(5);

    PersistentDsu a = dsu.merge(0, 1);
    PersistentDsu b = a.merge(1, 2);

    std::cout << dsu.same(0, 2) << "\n"; // 0
    std::cout << a.same(0, 2) << "\n";   // 0
    std::cout << b.same(0, 2) << "\n";   // 1
    std::cout << b.size(0) << "\n";       // 3
}
```
