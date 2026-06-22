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
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"graph/cycle_detection.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n \
    \   int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge()\
    \ : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int\
    \ to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_),\
    \ to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int v) const\
    \ {\n        assert(v == from || v == to);\n        return from ^ to ^ v;\n  \
    \  }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n\
    \    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n  \
    \  }\n};\n\ninline Cycle restore_cycle(int from, int to, int closing_edge, const\
    \ std::vector<int>& parent,\n                           const std::vector<int>&\
    \ parent_edge) {\n    Cycle result;\n    result.vertices.push_back(to);\n\n  \
    \  std::vector<int> middle_vertices;\n    std::vector<int> middle_edges;\n   \
    \ for (int v = from; v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n\
    \        middle_edges.push_back(parent_edge[v]);\n    }\n    std::reverse(middle_vertices.begin(),\
    \ middle_vertices.end());\n    std::reverse(middle_edges.begin(), middle_edges.end());\n\
    \n    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());\n\
    \    result.vertices.push_back(to);\n    result.edge_ids.insert(result.edge_ids.end(),\
    \ middle_edges.begin(), middle_edges.end());\n    result.edge_ids.push_back(closing_edge);\n\
    \    return result;\n}\n\ntemplate <class T>\nCycle find_directed_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v) -> bool {\n        color[v] = 1;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (e.id == pe) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to, e.id)) return true;\n            } else\
    \ if (color[e.to] == 1) {\n                result = restore_cycle(v, e.to, e.id,\
    \ parent, parent_edge);\n                return true;\n            }\n       \
    \ }\n        color[v] = 2;\n        return false;\n    };\n\n    for (int v =\
    \ 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs, v, -1)) break;\n   \
    \ }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_GRAPH_CYCLE_DETECTION_HPP\n#define M1UNE_GRAPH_CYCLE_DETECTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct Cycle {\n    std::vector<int> vertices;\n\
    \    std::vector<int> edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\ninline Cycle restore_cycle(int from, int to, int closing_edge, const\
    \ std::vector<int>& parent,\n                           const std::vector<int>&\
    \ parent_edge) {\n    Cycle result;\n    result.vertices.push_back(to);\n\n  \
    \  std::vector<int> middle_vertices;\n    std::vector<int> middle_edges;\n   \
    \ for (int v = from; v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n\
    \        middle_edges.push_back(parent_edge[v]);\n    }\n    std::reverse(middle_vertices.begin(),\
    \ middle_vertices.end());\n    std::reverse(middle_edges.begin(), middle_edges.end());\n\
    \n    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());\n\
    \    result.vertices.push_back(to);\n    result.edge_ids.insert(result.edge_ids.end(),\
    \ middle_edges.begin(), middle_edges.end());\n    result.edge_ids.push_back(closing_edge);\n\
    \    return result;\n}\n\ntemplate <class T>\nCycle find_directed_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v) -> bool {\n        color[v] = 1;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (e.id == pe) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to, e.id)) return true;\n            } else\
    \ if (color[e.to] == 1) {\n                result = restore_cycle(v, e.to, e.id,\
    \ parent, parent_edge);\n                return true;\n            }\n       \
    \ }\n        color[v] = 2;\n        return false;\n    };\n\n    for (int v =\
    \ 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs, v, -1)) break;\n   \
    \ }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    #endif  // M1UNE_GRAPH_CYCLE_DETECTION_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/cycle_detection.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/cycle_detection.hpp
layout: document
title: Cycle Detection
---

## Overview

Cycle detection finds one cycle, if the graph contains any. A cycle is returned
as both vertices and edge ids, which is convenient for problems that ask you to
output the actual cycle.

There are separate functions for directed and undirected graphs because the DFS
rules are different:

* in a directed graph, an edge to a currently active DFS vertex forms a cycle;
* in an undirected graph, the DFS must ignore only the exact edge used to enter
  the current vertex.

## Graph Orientation

This header has both variants:

* `find_directed_cycle(g)` respects edge direction;
* `find_undirected_cycle(g)` treats edges as undirected and should be used with
  graphs built by `add_edge`.

## How to Use It

Use `find_directed_cycle(g)` for graphs built with `add_directed_edge`. Use
`find_undirected_cycle(g)` for graphs built with `add_edge`.

The result type is `Cycle`.

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Cycle vertices, with the first vertex repeated at the end. Empty if no cycle exists. |
| `edge_ids` | `std::vector<int>` | Edge ids used along the cycle. Its size is `vertices.size() - 1` when non-empty. |
| `empty` | `bool empty() const` | Returns whether no cycle was found. |

The returned cycle is not guaranteed to be the shortest one; it is simply the
first cycle found by the DFS.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `find_directed_cycle` | `template <class T> Cycle find_directed_cycle(const Graph<T>& g)` | Finds a directed cycle. | $O(N + M)$ |
| `find_undirected_cycle` | `template <class T> Cycle find_undirected_cycle(const Graph<T>& g)` | Finds an undirected cycle. | $O(N + M)$ |

## Example

```cpp
#include "graph/cycle_detection.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 0);

    auto cycle = m1une::graph::find_directed_cycle(g);
    if (!cycle.empty()) {
        for (int v : cycle.vertices) std::cout << v << " ";
        std::cout << "\n";
    }
}
```
