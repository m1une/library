---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_mst.hpp
    title: Manhattan Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/dsu.test.cpp
    title: verify/ds/dsu/dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/manhattan_mst.test.cpp
    title: verify/geometry/manhattan_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/manhattan_mst.test.cpp
    title: verify/geometry/manhattan_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n   private:\n\
    \    int _n;\n    // parent_or_size[i] is the parent of i if it's >= 0.\n    //\
    \ If it's < 0, then i is a root and -parent_or_size[i] is the size of the group.\n\
    \    std::vector<int> parent_or_size;\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        int x = leader(a),\
    \ y = leader(b);\n        if (x == y) return x;\n        // Union by size\n  \
    \      if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\n       \
    \ parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y] = x;\n  \
    \      return x;\n    }\n\n    // Returns true if 'a' and 'b' belong to the same\
    \ group.\n    bool same(int a, int b) {\n        return leader(a) == leader(b);\n\
    \    }\n\n    // Returns the leader (representative) of the group containing 'a'.\n\
    \    int leader(int a) {\n        if (parent_or_size[a] < 0) return a;\n     \
    \   // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DSU_HPP\n#define M1UNE_DSU_HPP 1\n\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    struct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent\
    \ of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/dsu.hpp
  requiredBy:
  - geometry/all.hpp
  - geometry/manhattan_mst.hpp
  - graph/kruskal.hpp
  - graph/connected_components.hpp
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-20 20:27:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/manhattan_mst.test.cpp
  - verify/geometry/manhattan_mst.test.cpp
  - verify/ds/dsu/dsu.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: ds/dsu/dsu.hpp
layout: document
title: DSU (Disjoint Set Union)
---

## Overview

A Disjoint Set Union (also known as Union-Find) data structure. It manages a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides near constant time operations to merge sets and find the representative of a set.

It is implemented using **Path Compression** and **Union by Size**, achieving an amortized time complexity of $O(\alpha(N))$ per operation, where $\alpha$ is the inverse Ackermann function.

## Complexity Notation

* `N` is the number of elements.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Dsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit Dsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int merge(int a, int b)` | Merges the sets containing `a` and `b`; returns the leader of the merged set. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int size(int a)` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Example

```cpp
#include "ds/dsu/dsu.hpp"
#include <iostream>

int main() {
    // Create DSU with 5 elements (0 to 4)
    m1une::ds::Dsu dsu(5);

    dsu.merge(0, 1);
    dsu.merge(2, 3);
    dsu.merge(1, 2);

    std::cout << (dsu.same(0, 3) ? "Same" : "Different") << "\n"; // Output: Same
    std::cout << (dsu.same(0, 4) ? "Same" : "Different") << "\n"; // Output: Different
    std::cout << "Size of group 0: " << dsu.size(0) << "\n";      // Output: 4

    return 0;
}
```
