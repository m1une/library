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
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
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
  bundledCode: "#line 1 \"graph/topological_sort.hpp\"\n\n\n\n#include <optional>\n\
    #include <queue>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
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
    \ m1une\n\n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP\n#define M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP\
    \ 1\n\n#include <optional>\n#include <queue>\n#include <vector>\n\n#include \"\
    graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::optional<std::vector<int>>\
    \ topological_sort(const Graph<T>& g) {\n    int n = g.size();\n    std::vector<int>\
    \ indeg(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e\
    \ : g[v]) {\n            if (!e.alive) continue;\n            indeg[e.to]++;\n\
    \        }\n    }\n\n    std::queue<int> que;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (indeg[v] == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n\
    \    order.reserve(n);\n    while (!que.empty()) {\n        int v = que.front();\n\
    \        que.pop();\n        order.push_back(v);\n        for (const auto& e :\
    \ g[v]) {\n            if (!e.alive) continue;\n            indeg[e.to]--;\n \
    \           if (indeg[e.to] == 0) que.push(e.to);\n        }\n    }\n\n    if\
    \ (int(order.size()) != n) return std::nullopt;\n    return order;\n}\n\ntemplate\
    \ <class T>\nbool is_dag(const Graph<T>& g) {\n    return topological_sort(g).has_value();\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_TOPOLOGICAL_SORT_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/topological_sort.hpp
  requiredBy:
  - graph/dag_shortest_path.hpp
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  - graph/shortest_path.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/topological_sort.hpp
layout: document
title: Topological Sort
---

## Overview

Topological sort orders the vertices of a directed acyclic graph so that every
edge goes from an earlier vertex to a later vertex. It is the standard tool for
dependency graphs, prerequisite constraints, DAG dynamic programming, and
scheduling problems.

This implementation uses Kahn's algorithm. It repeatedly takes a vertex with
indegree `0`, removes it from the graph conceptually, and decreases the
indegree of its outgoing neighbors.

If the graph has a directed cycle, no topological order exists.

## Graph Orientation

Directed only. Topological sort is defined for directed acyclic graphs. For
undirected cycle checks, use `find_undirected_cycle` or LowLink-related tools
instead.

## How to Use It

Build a directed graph with `add_directed_edge`. Then call
`topological_sort(g)`.

The function returns `std::optional<std::vector<int>>`.

* If it has a value, the vector is one valid topological order.
* If it is `std::nullopt`, the graph contains a directed cycle.

The order is not unique. If several vertices have indegree `0`, the queue order
decides which one appears first.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `topological_sort` | `template <class T> std::optional<std::vector<int>> topological_sort(const Graph<T>& g)` | Returns an ordering, or `std::nullopt` if a cycle exists. | $O(N + M)$ |
| `is_dag` | `template <class T> bool is_dag(const Graph<T>& g)` | Returns whether the graph is acyclic. | $O(N + M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/topological_sort.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 2);

    auto order = m1une::graph::topological_sort(g);
    if (!order) return 0;

    for (int v : *order) std::cout << v << " ";
    std::cout << "\n";
}
```
