---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
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
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include\
    \ <queue>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 6 \"\
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
    \ namespace graph\n}  // namespace m1une\n\n\n#line 11 \"graph/bellman_ford.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<bool> negative;\n    T inf;\n    bool has_negative_cycle;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    bool affected_by_negative_cycle(int\
    \ v) const {\n        assert(0 <= v && v < int(negative.size()));\n        return\
    \ negative[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        assert(!affected_by_negative_cycle(t));\n        std::vector<int> result;\n\
    \        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g,\
    \ const std::vector<int>& sources,\n                                  T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    BellmanFordResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.negative.assign(n, false);\n\
    \    result.inf = inf;\n    result.has_negative_cycle = false;\n\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n\
    \    }\n\n    std::vector<int> relaxed_vertices;\n    for (int iter = 0; iter\
    \ < n; iter++) {\n        bool updated = false;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (result.dist[v] == inf) continue;\n            for (const\
    \ auto& e : g[v]) {\n                T nd = result.dist[v] + e.cost;\n       \
    \         if (result.dist[e.to] <= nd) continue;\n                result.dist[e.to]\
    \ = nd;\n                result.parent[e.to] = v;\n                result.parent_edge[e.to]\
    \ = e.id;\n                updated = true;\n                if (iter == n - 1)\
    \ relaxed_vertices.push_back(e.to);\n            }\n        }\n        if (!updated)\
    \ break;\n    }\n\n    std::queue<int> que;\n    for (int v : relaxed_vertices)\
    \ {\n        if (result.negative[v]) continue;\n        result.negative[v] = true;\n\
    \        que.push(v);\n    }\n    while (!que.empty()) {\n        int v = que.front();\n\
    \        que.pop();\n        for (const auto& e : g[v]) {\n            if (result.negative[e.to])\
    \ continue;\n            result.negative[e.to] = true;\n            que.push(e.to);\n\
    \        }\n    }\n\n    for (bool x : result.negative) result.has_negative_cycle\
    \ = result.has_negative_cycle || x;\n    return result;\n}\n\ntemplate <class\
    \ T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n\
    #line 8 \"graph/bfs.hpp\"\n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct BfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n\n    bool reachable(int v) const\
    \ {\n        assert(0 <= v && v < int(dist.size()));\n        return dist[v] !=\
    \ -1;\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nBfsResult bfs(const\
    \ Graph<T>& g, const std::vector<int>& sources) {\n    int n = g.size();\n   \
    \ BfsResult result;\n    result.dist.assign(n, -1);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n\n    std::queue<int> que;\n  \
    \  for (int s : sources) {\n        assert(0 <= s && s < n);\n        if (result.dist[s]\
    \ != -1) continue;\n        result.dist[s] = 0;\n        que.push(s);\n    }\n\
    \n    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dijkstra.hpp\"\
    \n\n\n\n#line 6 \"graph/dijkstra.hpp\"\n#include <functional>\n#line 9 \"graph/dijkstra.hpp\"\
    \n#include <utility>\n#line 11 \"graph/dijkstra.hpp\"\n\n#line 13 \"graph/dijkstra.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DijkstraResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    T inf;\n\n    bool reachable(int v) const {\n        assert(0\
    \ <= v && v < int(dist.size()));\n        return dist[v] != inf;\n    }\n\n  \
    \  std::vector<int> path(int t) const {\n        assert(reachable(t));\n     \
    \   std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T> dijkstra(const\
    \ Graph<T>& g, const std::vector<int>& sources,\n                           T\
    \ inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    DijkstraResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using P =\
    \ std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            T nd = d + e.cost;\n      \
    \      if (result.dist[e.to] <= nd) continue;\n            result.dist[e.to] =\
    \ nd;\n            result.parent[e.to] = v;\n            result.parent_edge[e.to]\
    \ = e.id;\n            que.emplace(nd, e.to);\n        }\n    }\n\n    return\
    \ result;\n}\n\ntemplate <class T>\nDijkstraResult<T> dijkstra(const Graph<T>&\
    \ g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return dijkstra(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8 \"graph/warshall_floyd.hpp\"\
    \n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>>\
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
    \       for (const auto& e : g[v]) {\n            if (e.cost < dist[e.from][e.to])\
    \ dist[e.from][e.to] = e.cost;\n        }\n    }\n    return warshall_floyd(std::move(dist),\
    \ inf);\n}\n\ntemplate <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
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
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 8 \"graph/shortest_path.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_SHORTEST_PATH_HPP

    #define M1UNE_GRAPH_SHORTEST_PATH_HPP 1


    #include "graph/bellman_ford.hpp"

    #include "graph/bfs.hpp"

    #include "graph/dijkstra.hpp"

    #include "graph/warshall_floyd.hpp"


    #endif  // M1UNE_GRAPH_SHORTEST_PATH_HPP

    '
  dependsOn:
  - graph/bellman_ford.hpp
  - graph/graph.hpp
  - graph/bfs.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  isVerificationFile: false
  path: graph/shortest_path.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  timestamp: '2026-06-16 02:16:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/shortest_path.hpp
layout: document
title: Shortest Path
---

## Overview

`graph/shortest_path.hpp` includes the shortest-path algorithms whose behavior
respects the adjacency stored in `Graph<T>`.

These algorithms can be used on directed graphs and on undirected graphs. For
undirected graphs, build edges with `add_edge`, which stores both directions.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/bfs.hpp` | Direction-respecting | Shortest paths by number of edges. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |
