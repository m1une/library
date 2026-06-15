---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bipartite.hpp\"\n\n\n\n#include <queue>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#line 6 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1) : from(from_),\
    \ to(to_), cost(cost_), id(id_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int\
    \ n) : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost\
    \ = T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        _g[u].push_back(edge_type(u, v, cost,\
    \ id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        return id;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges() const {\n\
    \        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (0 <= e.id && e.id < _edge_count) {\n                    if (used[e.id]) continue;\n\
    \                    used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        for (int v = 0; v < _n; v++) {\n            for (const auto& e : _g[v])\
    \ {\n                result._g[e.to].push_back(edge_type(e.to, e.from, e.cost,\
    \ e.id));\n            }\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 8 \"graph/bipartite.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n\
    \    std::vector<int> color;\n};\n\ntemplate <class T>\nBipartiteResult bipartite(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite\
    \ = true;\n    result.color.assign(n, -1);\n\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (const auto& e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n\
    \        adjacency[e.to].push_back(e.from);\n    }\n\n    std::queue<int> que;\n\
    \    for (int s = 0; s < n; s++) {\n        if (result.color[s] != -1) continue;\n\
    \        result.color[s] = 0;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop();\n            for\
    \ (int to : adjacency[v]) {\n                if (result.color[to] == -1) {\n \
    \                   result.color[to] = result.color[v] ^ 1;\n                \
    \    que.push(to);\n                } else if (result.color[to] == result.color[v])\
    \ {\n                    result.is_bipartite = false;\n                    return\
    \ result;\n                }\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nbool is_bipartite(const Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_BIPARTITE_HPP\n#define M1UNE_GRAPH_BIPARTITE_HPP 1\n\n\
    #include <queue>\n#include <vector>\n\n#include \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n\
    \    std::vector<int> color;\n};\n\ntemplate <class T>\nBipartiteResult bipartite(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite\
    \ = true;\n    result.color.assign(n, -1);\n\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (const auto& e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n\
    \        adjacency[e.to].push_back(e.from);\n    }\n\n    std::queue<int> que;\n\
    \    for (int s = 0; s < n; s++) {\n        if (result.color[s] != -1) continue;\n\
    \        result.color[s] = 0;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop();\n            for\
    \ (int to : adjacency[v]) {\n                if (result.color[to] == -1) {\n \
    \                   result.color[to] = result.color[v] ^ 1;\n                \
    \    que.push(to);\n                } else if (result.color[to] == result.color[v])\
    \ {\n                    result.is_bipartite = false;\n                    return\
    \ result;\n                }\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nbool is_bipartite(const Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_BIPARTITE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/bipartite.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-16 01:54:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/bipartite.hpp
layout: document
title: Bipartite Graph
---

## Overview

A graph is bipartite if its vertices can be colored with two colors so that
every edge connects vertices of different colors. Equivalently, the graph has
no odd-length cycle.

This function checks bipartiteness by BFS coloring. Edge direction is ignored:
each edge is treated as an undirected constraint between its endpoints. That
makes it useful for ordinary undirected graphs and also for directed graphs
where only the endpoint constraint matters.

Use this for two-team assignments, parity constraints, grid checkerboard
problems, and "does an odd cycle exist?" checks.

## How to Use It

Call `bipartite(g)` when you need both the yes/no answer and the colors. Call
`is_bipartite(g)` when you only need the boolean.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `is_bipartite` | `bool` | Whether a valid two-coloring exists. |
| `color` | `std::vector<int>` | `color[v]` is `0` or `1` for the assigned color, or `-1` before assignment. |

For a disconnected graph, every component is colored independently. The chosen
colors are not unique; flipping all colors in a component gives another valid
answer.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bipartite` | `template <class T> BipartiteResult bipartite(const Graph<T>& g)` | Returns a bipartite flag and colors. | $O(N+M)$ |
| `is_bipartite` | `template <class T> bool is_bipartite(const Graph<T>& g)` | Returns only the bipartite flag. | $O(N+M)$ |

## Example

```cpp
#include "graph/bipartite.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    auto res = m1une::graph::bipartite(g);
    std::cout << res.is_bipartite << "\n";  // 1
    std::cout << res.color[0] << " " << res.color[1] << "\n";
}
```
