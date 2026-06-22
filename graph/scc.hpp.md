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
  bundledCode: "#line 1 \"graph/scc.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
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
    \ m1une\n\n\n#line 10 \"graph/scc.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct SccResult {\n    int count;\n    std::vector<int> comp;\n    std::vector<std::vector<int>>\
    \ groups;\n\n    bool same(int u, int v) const {\n        assert(0 <= u && u <\
    \ int(comp.size()));\n        assert(0 <= v && v < int(comp.size()));\n      \
    \  return comp[u] == comp[v];\n    }\n\n    template <class T>\n    Graph<int>\
    \ dag(const Graph<T>& g) const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int v = 0; v < g.size(); v++) {\n            for (const auto& e\
    \ : g[v]) {\n                if (!e.alive) continue;\n                int a =\
    \ comp[e.from], b = comp[e.to];\n                if (a != b) edges.emplace_back(a,\
    \ b);\n            }\n        }\n        std::sort(edges.begin(), edges.end());\n\
    \        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());\n\n\
    \        Graph<int> result(count);\n        for (auto [a, b] : edges) result.add_directed_edge(a,\
    \ b);\n        return result;\n    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> ord(n, -1), low(n,\
    \ 0), comp(n, -1), stack;\n    std::vector<char> in_stack(n, false);\n    std::vector<std::vector<int>>\
    \ groups;\n    int now = 0;\n\n    auto dfs = [&](auto self, int v) -> void {\n\
    \        ord[v] = low[v] = now++;\n        stack.push_back(v);\n        in_stack[v]\
    \ = true;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            int to = e.to;\n            if (ord[to] == -1) {\n              \
    \  self(self, to);\n                low[v] = std::min(low[v], low[to]);\n    \
    \        } else if (in_stack[to]) {\n                low[v] = std::min(low[v],\
    \ ord[to]);\n            }\n        }\n\n        if (low[v] != ord[v]) return;\n\
    \        std::vector<int> group;\n        while (true) {\n            int u =\
    \ stack.back();\n            stack.pop_back();\n            in_stack[u] = false;\n\
    \            group.push_back(u);\n            if (u == v) break;\n        }\n\
    \        groups.push_back(std::move(group));\n    };\n\n    for (int v = 0; v\
    \ < n; v++) {\n        if (ord[v] == -1) dfs(dfs, v);\n    }\n\n    std::reverse(groups.begin(),\
    \ groups.end());\n    for (int i = 0; i < int(groups.size()); i++) {\n       \
    \ for (int v : groups[i]) comp[v] = i;\n    }\n\n    return SccResult{int(groups.size()),\
    \ std::move(comp), std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_SCC_HPP\n#define M1UNE_GRAPH_SCC_HPP 1\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n#include \"graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct SccResult {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n\n    template <class T>\n    Graph<int> dag(const Graph<T>& g) const\
    \ {\n        std::vector<std::pair<int, int>> edges;\n        for (int v = 0;\
    \ v < g.size(); v++) {\n            for (const auto& e : g[v]) {\n           \
    \     if (!e.alive) continue;\n                int a = comp[e.from], b = comp[e.to];\n\
    \                if (a != b) edges.emplace_back(a, b);\n            }\n      \
    \  }\n        std::sort(edges.begin(), edges.end());\n        edges.erase(std::unique(edges.begin(),\
    \ edges.end()), edges.end());\n\n        Graph<int> result(count);\n        for\
    \ (auto [a, b] : edges) result.add_directed_edge(a, b);\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> ord(n, -1), low(n,\
    \ 0), comp(n, -1), stack;\n    std::vector<char> in_stack(n, false);\n    std::vector<std::vector<int>>\
    \ groups;\n    int now = 0;\n\n    auto dfs = [&](auto self, int v) -> void {\n\
    \        ord[v] = low[v] = now++;\n        stack.push_back(v);\n        in_stack[v]\
    \ = true;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            int to = e.to;\n            if (ord[to] == -1) {\n              \
    \  self(self, to);\n                low[v] = std::min(low[v], low[to]);\n    \
    \        } else if (in_stack[to]) {\n                low[v] = std::min(low[v],\
    \ ord[to]);\n            }\n        }\n\n        if (low[v] != ord[v]) return;\n\
    \        std::vector<int> group;\n        while (true) {\n            int u =\
    \ stack.back();\n            stack.pop_back();\n            in_stack[u] = false;\n\
    \            group.push_back(u);\n            if (u == v) break;\n        }\n\
    \        groups.push_back(std::move(group));\n    };\n\n    for (int v = 0; v\
    \ < n; v++) {\n        if (ord[v] == -1) dfs(dfs, v);\n    }\n\n    std::reverse(groups.begin(),\
    \ groups.end());\n    for (int i = 0; i < int(groups.size()); i++) {\n       \
    \ for (int v : groups[i]) comp[v] = i;\n    }\n\n    return SccResult{int(groups.size()),\
    \ std::move(comp), std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_SCC_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/scc.hpp
  requiredBy:
  - graph/all.hpp
  - graph/directed.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/scc.hpp
layout: document
title: Strongly Connected Components
---

## Overview

A strongly connected component is a maximal set of vertices where every vertex
can reach every other vertex in the same set. SCC decomposition compresses each
such set into one component, turning any directed graph into a DAG of
components.

Use SCC when you need to reason about mutual reachability, directed cycles,
2-SAT-style implications, or DP over the condensation graph.

This implementation is based on Tarjan's DFS lowlink method and runs in linear
time.

## Graph Orientation

Directed only. SCCs are about mutual reachability through directed edges. For
ordinary undirected components, use `connected_components`.

## How to Use It

Build a directed graph with `add_directed_edge`, then call
`strongly_connected_components(g)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `count` | `int` | Number of strongly connected components. |
| `comp` | `std::vector<int>` | `comp[v]` is the component id of vertex `v`. |
| `groups` | `std::vector<std::vector<int>>` | `groups[c]` is the list of vertices belonging to component `c`. |
| `same` | `bool same(int u, int v) const` | Returns whether `u` and `v` are in the same component. |
| `dag` | `template <class T> Graph<int> dag(const Graph<T>& g) const` | Builds the condensation DAG with duplicate component edges removed. |

Component ids are arranged in topological order of the condensation DAG: edges
between different components go from a smaller id to a larger id.

## What `dag(g)` Represents

`dag(g)` returns the condensation graph of `g`. Its vertices are SCC ids, not
original graph vertices.

Vertex `c` in the returned DAG represents `groups[c]`, the `c`-th strongly
connected component. In other words:

```cpp
v belongs to DAG vertex c  <=>  comp[v] == c
```

For example, if `groups[2] == {4, 6, 7}`, then vertex `2` of the returned DAG
represents original vertices `4`, `6`, and `7`.

An SCC is not necessarily a single simple cycle. A DAG vertex may represent a
single isolated original vertex, one directed cycle, or a larger mutually
reachable subgraph containing several cycles.

If the original graph has an edge `u -> v` and `comp[u] != comp[v]`, the
returned DAG has an edge `comp[u] -> comp[v]`. Therefore each DAG edge means
"there exists at least one original edge from some vertex in `groups[from]` to
some vertex in `groups[to]`".

Duplicate edges between the same pair of components are removed. The returned
graph has type `Graph<int>` and its edge costs are all `1`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `strongly_connected_components` | `template <class T> SccResult strongly_connected_components(const Graph<T>& g)` | Returns component ids and groups. | $O(N + M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/scc.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 0);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 3);
    g.add_directed_edge(3, 2);

    auto scc = m1une::graph::strongly_connected_components(g);
    std::cout << scc.count << "\n";       // 2
    std::cout << scc.same(0, 1) << "\n";  // 1
    std::cout << scc.same(0, 2) << "\n";  // 0

    auto dag = scc.dag(g);
    std::cout << dag.size() << "\n";      // 2
}
```
