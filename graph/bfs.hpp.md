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
  bundledCode: "#line 1 \"graph/bfs.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <queue>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ m1une\n\n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct BfsResult {\n    std::vector<int> dist;\n    std::vector<int> parent;\n\
    \    std::vector<int> parent_edge;\n\n    bool reachable(int v) const {\n    \
    \    assert(0 <= v && v < int(dist.size()));\n        return dist[v] != -1;\n\
    \    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nBfsResult bfs(const\
    \ Graph<T>& g, const std::vector<int>& sources) {\n    int n = g.size();\n   \
    \ BfsResult result;\n    result.dist.assign(n, -1);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n\n    std::queue<int> que;\n  \
    \  for (int s : sources) {\n        assert(0 <= s && s < n);\n        if (result.dist[s]\
    \ != -1) continue;\n        result.dist[s] = 0;\n        que.push(s);\n    }\n\
    \n    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.dist[e.to] != -1) continue;\n            result.dist[e.to]\
    \ = result.dist[v] + 1;\n            result.parent[e.to] = v;\n            result.parent_edge[e.to]\
    \ = e.id;\n            que.push(e.to);\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return\
    \ bfs(g, std::vector<int>{s});\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_GRAPH_BFS_HPP\n#define M1UNE_GRAPH_BFS_HPP 1\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <vector>\n\n#include \"graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct BfsResult {\n    std::vector<int>\
    \ dist;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\n \
    \   bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != -1;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nBfsResult\
    \ bfs(const Graph<T>& g, const std::vector<int>& sources) {\n    int n = g.size();\n\
    \    BfsResult result;\n    result.dist.assign(n, -1);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n\n    std::queue<int> que;\n  \
    \  for (int s : sources) {\n        assert(0 <= s && s < n);\n        if (result.dist[s]\
    \ != -1) continue;\n        result.dist[s] = 0;\n        que.push(s);\n    }\n\
    \n    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.dist[e.to] != -1) continue;\n            result.dist[e.to]\
    \ = result.dist[v] + 1;\n            result.parent[e.to] = v;\n            result.parent_edge[e.to]\
    \ = e.id;\n            que.push(e.to);\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return\
    \ bfs(g, std::vector<int>{s});\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n#endif  // M1UNE_GRAPH_BFS_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/bfs.hpp
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
documentation_of: graph/bfs.hpp
layout: document
title: BFS
---

## Overview

Breadth-first search computes shortest paths in an unweighted graph, where every
edge has the same cost. It expands vertices in increasing distance order:
first the source, then all vertices one edge away, then all vertices two edges
away, and so on.

Use BFS when the answer is measured by the number of edges, not by edge
weights. For weighted shortest paths, use Dijkstra or Bellman-Ford instead.

## Graph Orientation

Direction is respected. `bfs` works on directed graphs as written, and also on
undirected graphs built with `add_edge`.

## How to Use It

Call `bfs(g, s)` for one source, or `bfs(g, sources)` when several vertices
should start at distance `0`. Multi-source BFS is useful for problems like
"distance to the nearest special vertex".

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<int>` | `dist[v]` is the number of edges from the nearest source to `v`, or `-1` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on the restored BFS tree path, or `-1` for a source/unreachable vertex. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bfs` | `template <class T> BfsResult bfs(const Graph<T>& g, int s)` | Runs BFS from one source. | $O(N + M)$ |
| `bfs` | `template <class T> BfsResult bfs(const Graph<T>& g, const std::vector<int>& sources)` | Runs multi-source BFS. | $O(N + M)$ |

## Example

```cpp
#include "graph/bfs.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);

    auto res = m1une::graph::bfs(g, 0);
    std::cout << res.dist[2] << "\n";  // 2

    for (int v : res.path(2)) {
        std::cout << v << " ";         // 0 1 2
    }
    std::cout << "\n";
}
```
