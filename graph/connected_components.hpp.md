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
  bundledCode: "#line 1 \"graph/connected_components.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <numeric>\n#line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is\
    \ the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
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
    \  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\
    \n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct ConnectedComponents {\n    int count;\n    std::vector<int>\
    \ comp;\n    std::vector<std::vector<int>> groups;\n\n    bool same(int u, int\
    \ v) const {\n        assert(0 <= u && u < int(comp.size()));\n        assert(0\
    \ <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n    }\n\
    };\n\ntemplate <class T>\nConnectedComponents connected_components(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const auto&\
    \ e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP\n#define M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"../ds/dsu/dsu.hpp\"\
    \n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct ConnectedComponents\
    \ {\n    int count;\n    std::vector<int> comp;\n    std::vector<std::vector<int>>\
    \ groups;\n\n    bool same(int u, int v) const {\n        assert(0 <= u && u <\
    \ int(comp.size()));\n        assert(0 <= v && v < int(comp.size()));\n      \
    \  return comp[u] == comp[v];\n    }\n};\n\ntemplate <class T>\nConnectedComponents\
    \ connected_components(const Graph<T>& g) {\n    int n = g.size();\n    m1une::ds::Dsu\
    \ dsu(n);\n    for (const auto& e : g.edges()) dsu.merge(e.from, e.to);\n\n  \
    \  ConnectedComponents result;\n    result.comp.assign(n, 0);\n    std::vector<int>\
    \ leader_to_comp(n, -1);\n    for (int v = 0; v < n; v++) {\n        int leader\
    \ = dsu.leader(v);\n        if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader]\
    \ = int(result.groups.size());\n            result.groups.push_back({});\n   \
    \     }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP\n"
  dependsOn:
  - ds/dsu/dsu.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/connected_components.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/connected_components.hpp
layout: document
title: Connected Components
---

## Overview

Connected components with edge direction ignored. For directed graphs, this is
the weakly connected component decomposition. For strongly connected components,
use `strongly_connected_components`.

Two vertices are in the same connected component if there is a path between
them after ignoring edge directions. Internally this function uses DSU, merging
the endpoints of every logical edge.

Use this when you need to split a graph into independent pieces, count
components, check ordinary connectivity, or process each connected block
separately.

## Graph Orientation

Direction is ignored. On a directed graph, this computes weakly connected
components. For strongly connected components, use `strongly_connected_components`.

## How to Use It

Call `connected_components(g)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `count` | `int` | Number of connected components. |
| `comp` | `std::vector<int>` | `comp[v]` is the component id of vertex `v`. |
| `groups` | `std::vector<std::vector<int>>` | `groups[c]` is the list of vertices in component `c`. |
| `same` | `bool same(int u, int v) const` | Returns whether `u` and `v` are in the same component. |

For undirected graphs, build with `add_edge`. For directed graphs, remember that
the decomposition is weak connectivity; reachability direction is ignored.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `connected_components` | `template <class T> ConnectedComponents connected_components(const Graph<T>& g)` | Returns component ids and groups. | $O(N + M)$ |

## Example

```cpp
#include "graph/connected_components.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_edge(0, 1);
    g.add_edge(2, 3);

    auto cc = m1une::graph::connected_components(g);
    std::cout << cc.count << "\n";      // 3
    std::cout << cc.same(0, 1) << "\n"; // 1
    std::cout << cc.same(0, 2) << "\n"; // 0
}
```
