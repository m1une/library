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
  bundledCode: "#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
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
    \ m1une\n\n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>>\
    \ dist,\n                                           T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    int n = int(dist.size());\n    for (int k = 0; k < n; k++) {\n\
    \        for (int i = 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n\
    \            for (int j = 0; j < n; j++) {\n                if (dist[k][j] ==\
    \ inf) continue;\n                T nd = dist[i][k] + dist[k][j];\n          \
    \      if (nd < dist[i][j]) dist[i][j] = nd;\n            }\n        }\n    }\n\
    \    return dist;\n}\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(const\
    \ Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    std::vector<std::vector<T>> dist(n, std::vector<T>(n, inf));\n    for (int\
    \ i = 0; i < n; i++) dist[i][i] = T(0);\n    for (int v = 0; v < n; v++) {\n \
    \       for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n  \
    \          if (e.cost < dist[e.from][e.to]) dist[e.from][e.to] = e.cost;\n   \
    \     }\n    }\n    return warshall_floyd(std::move(dist), inf);\n}\n\ntemplate\
    \ <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_WARSHALL_FLOYD_HPP\n#define M1UNE_GRAPH_WARSHALL_FLOYD_HPP\
    \ 1\n\n#include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>> dist,\n\
    \                                           T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    int n = int(dist.size());\n    for (int k = 0; k < n; k++) {\n\
    \        for (int i = 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n\
    \            for (int j = 0; j < n; j++) {\n                if (dist[k][j] ==\
    \ inf) continue;\n                T nd = dist[i][k] + dist[k][j];\n          \
    \      if (nd < dist[i][j]) dist[i][j] = nd;\n            }\n        }\n    }\n\
    \    return dist;\n}\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(const\
    \ Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    std::vector<std::vector<T>> dist(n, std::vector<T>(n, inf));\n    for (int\
    \ i = 0; i < n; i++) dist[i][i] = T(0);\n    for (int v = 0; v < n; v++) {\n \
    \       for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n  \
    \          if (e.cost < dist[e.from][e.to]) dist[e.from][e.to] = e.cost;\n   \
    \     }\n    }\n    return warshall_floyd(std::move(dist), inf);\n}\n\ntemplate\
    \ <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_WARSHALL_FLOYD_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/warshall_floyd.hpp
  requiredBy:
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
documentation_of: graph/warshall_floyd.hpp
layout: document
title: Warshall-Floyd
---

## Overview

Warshall-Floyd computes shortest paths between every pair of vertices. It keeps
a distance matrix and tries each vertex `k` as an intermediate point, improving
`dist[i][j]` with `dist[i][k] + dist[k][j]`.

Use it when `N` is small enough for $O(N^3)$ time and you need many shortest
path queries after preprocessing. It can handle negative edge costs, but if a
negative cycle exists, shortest distances involving that cycle are not
well-defined.

For one-source shortest paths on larger graphs, use Dijkstra or Bellman-Ford.

## Graph Orientation

Direction is respected. `warshall_floyd` works on directed graphs as written,
and also on undirected graphs built with `add_edge`.

## How to Use It

There are two entry points:

* `warshall_floyd(g)` builds the initial matrix from a `Graph<T>`.
* `warshall_floyd(dist)` starts from a matrix you prepared yourself and runs
  the full $O(N^3)$ Floyd-Warshall transition on it.

For a custom matrix, initialize `dist[i][i] = 0`, unreachable entries to `inf`,
and direct edge costs to their minimum values.

This second overload is useful when your initial distances do not come directly
from `Graph<T>`, for example when you already have a dense matrix or want to
set some distances manually before running all-pairs shortest paths.

After running the algorithm, `dist[s][t]` is the shortest distance from `s` to
`t`, or `inf` if `t` is unreachable from `s`.

Use `has_negative_cycle(dist)` after the relaxation. It checks whether some
`dist[i][i]` became negative.

## Adding an Edge

After computing an all-pairs distance matrix, adding one edge can be applied in
$O(N^2)$.

The input matrix must already be the correct all-pairs shortest distance matrix
for the graph before adding the edge.

For a new directed edge `from -> to` with cost `cost`, every improved shortest
path has the form:

```cpp
i -> ... -> from -> to -> ... -> j
```

So the function checks:

```cpp
dist[i][j] = min(dist[i][j], dist[i][from] + cost + dist[to][j])
```

Use `warshall_floyd_add_directed_edge(dist, from, to, cost)` for a directed
edge and `warshall_floyd_add_undirected_edge(dist, u, v, cost)` for an
undirected edge. Adding a parallel edge with a smaller cost is the same
operation.

These functions modify `dist` in place and return `true` if at least one entry
changed.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `warshall_floyd` | `template <class T> std::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4))` | Builds and relaxes the distance matrix from a graph. | $O(N^3)$ |
| `warshall_floyd` | `template <class T> std::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>> dist, T inf = std::numeric_limits<T>::max() / T(4))` | Runs the full Floyd-Warshall transition on a matrix you initialized yourself. | $O(N^3)$ |
| `warshall_floyd_add_directed_edge` | `template <class T> bool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>& dist, int from, int to, T cost, T inf = std::numeric_limits<T>::max() / T(4))` | Adds one directed edge to an already-computed distance matrix. | $O(N^2)$ |
| `warshall_floyd_add_undirected_edge` | `template <class T> bool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>& dist, int u, int v, T cost, T inf = std::numeric_limits<T>::max() / T(4))` | Adds one undirected edge to an already-computed distance matrix. | $O(N^2)$ |
| `has_negative_cycle` | `template <class T> bool has_negative_cycle(const std::vector<std::vector<T>>& dist)` | Checks whether any diagonal entry is negative. | $O(N)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/warshall_floyd.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 5);
    g.add_directed_edge(1, 2, 7);
    g.add_directed_edge(0, 2, 20);

    auto dist = m1une::graph::warshall_floyd(g);
    std::cout << dist[0][2] << "\n";  // 12

    m1une::graph::warshall_floyd_add_directed_edge(dist, 0, 2, 4LL);
    std::cout << dist[0][2] << "\n";  // 4
}
```
