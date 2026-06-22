---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
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
  bundledCode: "#line 1 \"graph/kruskal.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <vector>\n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 5 \"ds/dsu/dsu.hpp\"\n#include\
    \ <numeric>\n#line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent\
    \ of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        int x = leader(a), y = leader(b);\n        if (x == y) return x;\n  \
    \      // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n\
    #include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 9 \"graph/kruskal.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct MinimumSpanningForest {\n    T cost;\n    std::vector<Edge<T>>\
    \ edges;\n    int components;\n\n    bool is_spanning_tree(int n) const {\n  \
    \      return components <= 1 && int(edges.size()) == std::max(0, n - 1);\n  \
    \  }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T> kruskal(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    auto edges = g.edges();\n    std::sort(edges.begin(),\
    \ edges.end(), [](const auto& a, const auto& b) {\n        return a.cost < b.cost;\n\
    \    });\n\n    m1une::ds::Dsu dsu(n);\n    MinimumSpanningForest<T> result;\n\
    \    result.cost = T(0);\n    result.components = n;\n\n    for (const auto& e\
    \ : edges) {\n        if (dsu.same(e.from, e.to)) continue;\n        dsu.merge(e.from,\
    \ e.to);\n        result.cost += e.cost;\n        result.edges.push_back(e);\n\
    \        result.components--;\n    }\n\n    return result;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_KRUSKAL_HPP\n#define M1UNE_GRAPH_KRUSKAL_HPP 1\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include \"../ds/dsu/dsu.hpp\"\n#include \"\
    graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct\
    \ MinimumSpanningForest {\n    T cost;\n    std::vector<Edge<T>> edges;\n    int\
    \ components;\n\n    bool is_spanning_tree(int n) const {\n        return components\
    \ <= 1 && int(edges.size()) == std::max(0, n - 1);\n    }\n};\n\ntemplate <class\
    \ T>\nMinimumSpanningForest<T> kruskal(const Graph<T>& g) {\n    int n = g.size();\n\
    \    auto edges = g.edges();\n    std::sort(edges.begin(), edges.end(), [](const\
    \ auto& a, const auto& b) {\n        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu\
    \ dsu(n);\n    MinimumSpanningForest<T> result;\n    result.cost = T(0);\n   \
    \ result.components = n;\n\n    for (const auto& e : edges) {\n        if (dsu.same(e.from,\
    \ e.to)) continue;\n        dsu.merge(e.from, e.to);\n        result.cost += e.cost;\n\
    \        result.edges.push_back(e);\n        result.components--;\n    }\n\n \
    \   return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_GRAPH_KRUSKAL_HPP\n"
  dependsOn:
  - ds/dsu/dsu.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/kruskal.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/kruskal.hpp
layout: document
title: Kruskal
---

## Overview

Kruskal's algorithm for a minimum spanning forest of an undirected weighted
graph.

The algorithm sorts edges by cost and adds them one by one if they connect two
different DSU components. This greedily builds a minimum-cost set of edges that
connects each connected component.

Use it when you need a minimum spanning tree (connected graph) or minimum
spanning forest (possibly disconnected graph). It is especially convenient when
the input is an edge list or when $M \log M$ is acceptable.

## Graph Orientation

Undirected only. Build the graph with `add_edge`. A directed edge does not
represent the usual MST problem.

## How to Use It

Build an undirected weighted graph with `add_edge`, then call `kruskal(g)`.
Although the function only looks at edge endpoints and costs, using
`add_directed_edge` usually does not represent a normal MST problem.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `cost` | `T` | Total cost of the selected forest. |
| `edges` | `std::vector<Edge<T>>` | Selected edges. |
| `components` | `int` | Number of connected components left after selecting edges. |
| `is_spanning_tree` | `bool is_spanning_tree(int n) const` | Returns whether the result is one spanning tree on `n` vertices. |

If the graph is disconnected, the result is a minimum spanning forest and
`components` will be greater than `1`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `kruskal` | `template <class T> MinimumSpanningForest<T> kruskal(const Graph<T>& g)` | Returns total cost, selected edges, and component count. | $O(M \log M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/kruskal.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(0, 3, 10);

    auto mst = m1une::graph::kruskal(g);
    std::cout << mst.cost << "\n";  // 6
}
```
