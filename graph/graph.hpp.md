---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.hpp
    title: General Matching
  - icon: ':heavy_check_mark:'
    path: graph/grid.hpp
    title: Grid
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: graph/maximum_clique.hpp
    title: Maximum Clique, Independent Set, and Vertex Cover
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/library_checker_general_matching.test.cpp
    title: verify/graph/library_checker_general_matching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()),\
    \ id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_\
    \ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_),\
    \ alive(alive_) {}\n\n    int other(int v) const {\n        assert(v == from ||\
    \ v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\n\
    struct Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n \
    \  private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.push_back({{from,\
    \ idx}});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost\
    \ = T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.push_back({{u,\
    \ u_idx}, {v, v_idx}});\n        return id;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < _edge_count);\n        for\
    \ (auto [v, idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n\
    \        }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id,\
    \ false);\n    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id,\
    \ true);\n    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <=\
    \ id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n  \
    \      auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_GRAPH_HPP\n#define M1UNE_GRAPH_GRAPH_HPP 1\n\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type = T;\n\
    \n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\n  \
    \  Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
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
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.push_back({{from,\
    \ idx}});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost\
    \ = T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.push_back({{u,\
    \ u_idx}, {v, v_idx}});\n        return id;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < _edge_count);\n        for\
    \ (auto [v, idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n\
    \        }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id,\
    \ false);\n    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id,\
    \ true);\n    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <=\
    \ id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n  \
    \      auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
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
    \ m1une\n\n#endif  // M1UNE_GRAPH_GRAPH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/graph.hpp
  requiredBy:
  - graph/maximum_clique.hpp
  - graph/dijkstra.hpp
  - graph/scc.hpp
  - graph/kruskal.hpp
  - graph/bipartite.hpp
  - graph/bellman_ford.hpp
  - graph/dag_shortest_path.hpp
  - graph/connected_components.hpp
  - graph/all.hpp
  - graph/lowlink.hpp
  - graph/zero_one_bfs.hpp
  - graph/grid.hpp
  - graph/topological_sort.hpp
  - graph/cycle_detection.hpp
  - graph/bfs.hpp
  - graph/warshall_floyd.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  - graph/shortest_path.hpp
  - graph/general_matching.hpp
  timestamp: '2026-06-16 02:32:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/library_checker_general_matching.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/graph.hpp
layout: document
title: Graph
---

## Overview

`m1une::graph::Graph<T>` is an adjacency-list graph container for general
directed and undirected graphs. It is meant to be the common input format for
the graph algorithms in this directory.

The template parameter `T` is the edge-cost type. Use `Graph<>` when the graph
is unweighted; it is the same as `Graph<int>` and every omitted edge cost
defaults to `1`.

Undirected edges are stored as two adjacency entries with the same edge id, so
algorithms can distinguish logical edges from adjacency arcs.

Each edge also has an `alive` flag. Built-in graph algorithms ignore edges with
`alive == false`, so you can logically delete an edge without physically
removing it from the adjacency list.

## Graph Orientation

`Graph<T>` itself supports both directed and undirected graphs.

* `add_directed_edge(from, to, cost)` stores one directed arc.
* `add_edge(u, v, cost)` stores two arcs with one shared logical edge id.

Algorithm pages state whether they respect direction, require undirected edges,
or ignore direction.

## How to Use It

Create a graph with the number of vertices, then add edges.

* Use `add_directed_edge(from, to, cost)` for a one-way edge.
* Use `add_edge(u, v, cost)` for an undirected edge.
* Vertices are zero-indexed.
* The returned edge id is stable and shared by the two arcs of an undirected
  edge.

Most algorithms iterate over `g[v]`, where each element is an `Edge<T>` with
`from`, `to`, `cost`, `id`, and `alive`.

Choose the cost type to match the algorithm. For example, use
`Graph<long long>` for shortest paths with large weights.

## Types

| Type | Description |
| --- | --- |
| `Edge<T>` | Stores `from`, `to`, `cost`, `id`, and `alive`. |
| `Graph<T>` | Stores `std::vector<std::vector<Edge<T>>>`. |

## Edge Fields and Methods

| Member | Type / Signature | Description |
| --- | --- | --- |
| `from` | `int` | Source vertex of this adjacency arc. |
| `to` | `int` | Destination vertex of this adjacency arc. |
| `cost` | `T` | Edge cost. |
| `id` | `int` | Logical edge id. The two arcs of an undirected edge share one id. |
| `alive` | `bool` | Whether this edge is active. Built-in algorithms skip inactive edges. |
| `other` | `int other(int v) const` | Returns the other endpoint of this edge. Use it only when `v` is one endpoint. |

## Methods

| Method | Type / Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `Graph()` | Creates an empty graph. | $O(1)$ |
| Constructor | `explicit Graph(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the graph has no vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of logical edges added. | $O(1)$ |
| `add_vertex` | `int add_vertex()` | Adds one vertex and returns its index. | $O(1)$ amortized |
| `add_directed_edge` | `int add_directed_edge(int from, int to, T cost = T(1))` | Adds one directed edge and returns its id. | $O(1)$ amortized |
| `add_edge` | `int add_edge(int u, int v, T cost = T(1))` | Adds one undirected edge and returns its id. | $O(1)$ amortized |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Sets the alive flag of every adjacency arc with edge id `id`. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks edge id `id` as inactive. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks edge id `id` as active. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether edge id `id` is active. | $O(1)$ |
| `operator[]` | `const std::vector<Edge<T>>& operator[](int v) const` | Returns immutable adjacency list of vertex `v`. | $O(1)$ |
| `operator[]` | `std::vector<Edge<T>>& operator[](int v)` | Returns mutable adjacency list of vertex `v`. | $O(1)$ |
| `adjacency` | `const std::vector<std::vector<Edge<T>>>& adjacency() const` | Returns immutable adjacency lists. | $O(1)$ |
| `adjacency` | `std::vector<std::vector<Edge<T>>>& adjacency()` | Returns mutable adjacency lists. | $O(1)$ |
| `edges` | `std::vector<Edge<T>> edges(bool include_inactive = false) const` | Returns one entry per logical edge id. Inactive edges are skipped unless `include_inactive` is true. | $O(N+M)$ |
| `reversed` | `Graph<T> reversed() const` | Returns the graph with all arcs reversed. | $O(N+M)$ |

## Notes

`edges()` returns each logical edge once. For an undirected edge, only one of
the two stored arcs is returned. This is useful for algorithms like Kruskal that
must not process the same undirected edge twice.

`erase_edge(id)` is a logical deletion. The adjacency entries remain in memory,
but built-in algorithms skip them. `edge_count()` still includes inactive
edges. Use `edges(true)` if you need to inspect inactive edges too.

`reversed()` is mainly useful for directed graphs. It preserves edge ids and
costs and alive flags while swapping every arc direction.

## Example

```cpp
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 5);
    int e = g.add_directed_edge(1, 2, 7);
    g.erase_edge(e);

    for (const auto& e : g[0]) {
        if (!e.alive) continue;
        std::cout << e.from << " -> " << e.to << " cost=" << e.cost << "\n";
    }
}
```
