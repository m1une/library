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
  bundledCode: "#line 1 \"graph/lowlink.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include\
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
    \ m1une\n\n\n#line 8 \"graph/lowlink.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct LowLinkResult {\n    std::vector<int> ord;\n\
    \    std::vector<int> low;\n    std::vector<int> articulation;\n    std::vector<Edge<T>>\
    \ bridges;\n    std::vector<int> bridge_ids;\n};\n\ntemplate <class T>\nLowLinkResult<T>\
    \ lowlink(const Graph<T>& g) {\n    int n = g.size();\n    LowLinkResult<T> result;\n\
    \    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n    int now = 0;\n\
    \n    auto dfs = [&](auto self, int v, int parent_edge) -> void {\n        result.ord[v]\
    \ = result.low[v] = now++;\n        int child_count = 0;\n        bool is_articulation\
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            if (e.id == parent_edge) continue;\n            int to\
    \ = e.to;\n            if (result.ord[to] == -1) {\n                child_count++;\n\
    \                self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
    \ result.low[to]);\n                if (parent_edge != -1 && result.ord[v] <=\
    \ result.low[to]) is_articulation = true;\n                if (result.ord[v] <\
    \ result.low[to]) {\n                    result.bridges.push_back(e);\n      \
    \              result.bridge_ids.push_back(e.id);\n                }\n       \
    \     } else {\n                result.low[v] = std::min(result.low[v], result.ord[to]);\n\
    \            }\n        }\n\n        if (parent_edge == -1 && child_count >= 2)\
    \ is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_LOWLINK_HPP\n#define M1UNE_GRAPH_LOWLINK_HPP 1\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T>\nstruct LowLinkResult {\n    std::vector<int>\
    \ ord;\n    std::vector<int> low;\n    std::vector<int> articulation;\n    std::vector<Edge<T>>\
    \ bridges;\n    std::vector<int> bridge_ids;\n};\n\ntemplate <class T>\nLowLinkResult<T>\
    \ lowlink(const Graph<T>& g) {\n    int n = g.size();\n    LowLinkResult<T> result;\n\
    \    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n    int now = 0;\n\
    \n    auto dfs = [&](auto self, int v, int parent_edge) -> void {\n        result.ord[v]\
    \ = result.low[v] = now++;\n        int child_count = 0;\n        bool is_articulation\
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            if (e.id == parent_edge) continue;\n            int to\
    \ = e.to;\n            if (result.ord[to] == -1) {\n                child_count++;\n\
    \                self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
    \ result.low[to]);\n                if (parent_edge != -1 && result.ord[v] <=\
    \ result.low[to]) is_articulation = true;\n                if (result.ord[v] <\
    \ result.low[to]) {\n                    result.bridges.push_back(e);\n      \
    \              result.bridge_ids.push_back(e.id);\n                }\n       \
    \     } else {\n                result.low[v] = std::min(result.low[v], result.ord[to]);\n\
    \            }\n        }\n\n        if (parent_edge == -1 && child_count >= 2)\
    \ is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_LOWLINK_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/lowlink.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/lowlink.hpp
layout: document
title: LowLink
---

## Overview

LowLink is a DFS technique for undirected graphs. It records, for each vertex,
the earliest DFS-order vertex reachable by going down zero or more tree edges
and then using at most one back edge.

This information identifies:

* articulation points: vertices whose removal increases the number of connected
  components;
* bridges: edges whose removal increases the number of connected components.

Use it for network vulnerability problems, bridge counting, biconnected
component preprocessing, and similar undirected connectivity tasks.

## Graph Orientation

Undirected only. Build the graph with `add_edge`. LowLink is not the right tool
for directed bridges or directed articulation-like notions.

## How to Use It

Build the graph with `add_edge`, not two calls to `add_directed_edge`. The
shared edge id is what lets the DFS skip exactly the tree edge it came from,
while still handling parallel edges correctly.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `ord` | `std::vector<int>` | `ord[v]` is the DFS visit order of `v`. |
| `low` | `std::vector<int>` | `low[v]` is the minimum `ord` reachable from `v`'s DFS subtree using at most one back edge. |
| `articulation` | `std::vector<int>` | Sorted list of articulation point vertices. |
| `bridges` | `std::vector<Edge<T>>` | Bridge edges as `Edge<T>` values. |
| `bridge_ids` | `std::vector<int>` | Sorted list of bridge edge ids. |

For a DFS tree edge `v -> to`, it is a bridge when
`ord[v] < low[to]`. A non-root vertex `v` is an articulation point when some
child `to` has `ord[v] <= low[to]`. A DFS root is an articulation point when it
has at least two DFS children.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `lowlink` | `template <class T> LowLinkResult<T> lowlink(const Graph<T>& g)` | Computes `ord`, `low`, `articulation`, `bridges`, and `bridge_ids`. | $O(N + M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/lowlink.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    int bridge = g.add_edge(1, 3);
    g.add_edge(2, 0);

    auto res = m1une::graph::lowlink(g);
    std::cout << res.articulation[0] << "\n";  // 1
    std::cout << (res.bridge_ids[0] == bridge) << "\n";  // 1
}
```
