---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroid_intersection.test.cpp
    title: verify/matroid/matroid_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/weighted_matroid_intersection.test.cpp
    title: verify/matroid/weighted_matroid_intersection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/graphic_matroid.hpp\"\n\n\n\n#include <cassert>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace matroid {\n\nclass GraphicMatroid {\n   private:\n    int _vertex_count;\n\
    \    std::vector<std::pair<int, int>> _edges;\n\n   public:\n    GraphicMatroid()\
    \ : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count, std::vector<std::pair<int,\
    \ int>> edges)\n        : _vertex_count(vertex_count), _edges(std::move(edges))\
    \ {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n        for (auto [u,\
    \ v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n         \
    \   assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n    int\
    \ size() const {\n        return int(_edges.size());\n    }\n\n    int vertex_count()\
    \ const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATROID_GRAPHIC_MATROID_HPP\n#define M1UNE_MATROID_GRAPHIC_MATROID_HPP\
    \ 1\n\n#include <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace matroid {\n\nclass GraphicMatroid {\n   private:\n\
    \    int _vertex_count;\n    std::vector<std::pair<int, int>> _edges;\n\n   public:\n\
    \    GraphicMatroid() : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count,\
    \ std::vector<std::pair<int, int>> edges)\n        : _vertex_count(vertex_count),\
    \ _edges(std::move(edges)) {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n\
    \        for (auto [u, v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n\
    \            assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n\
    \    int size() const {\n        return int(_edges.size());\n    }\n\n    int\
    \ vertex_count() const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n#endif  // M1UNE_MATROID_GRAPHIC_MATROID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/graphic_matroid.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/matroids.test.cpp
  - verify/matroid/matroid_intersection.test.cpp
  - verify/matroid/weighted_matroid_intersection.test.cpp
documentation_of: matroid/graphic_matroid.hpp
layout: document
title: Graphic Matroid
---

## Overview

`GraphicMatroid` uses the edges of an undirected graph as its ground set. A
subset is independent exactly when the selected edges form a forest.

Element `i` corresponds to `edges()[i]`. Parallel edges are supported; loops
are always dependent.

Oracle inputs must contain distinct valid edge indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `GraphicMatroid(int vertex_count, std::vector<std::pair<int, int>> edges)` | Stores the graph. | $O(E)$ |
| `int size() const` | Returns the number of ground elements (edges). | $O(1)$ |
| `int vertex_count() const` | Returns the graph's vertex count. | $O(1)$ |
| `const std::vector<std::pair<int, int>>& edges() const` | Returns the indexed edge list. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Checks whether the selected edges are acyclic. | $O(V+|S|\alpha(V))$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(V+|S|\alpha(V))$ |

## Example

```cpp
#include "matroid/graphic_matroid.hpp"
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> edges = {
    {0, 1}, {1, 2}, {2, 0}, {2, 3}
};
m1une::matroid::GraphicMatroid matroid(4, edges);

bool forest = matroid(std::vector<int>{0, 1, 3}); // true
bool cycle = matroid(std::vector<int>{0, 1, 2});  // false
```
