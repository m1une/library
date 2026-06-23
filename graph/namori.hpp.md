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
    path: verify/graph/namori.test.cpp
    title: verify/graph/namori.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/namori.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int component_count;\n\
    \    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_NAMORI_HPP\n#define M1UNE_GRAPH_NAMORI_HPP 1\n\n#include\
    \ <cassert>\n#include <optional>\n#include <queue>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\
    \ntemplate <class T>\nstruct NamoriDecomposition {\n    int component_count;\n\
    \    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_NAMORI_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/namori.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-23 12:19:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/namori.test.cpp
documentation_of: graph/namori.hpp
layout: document
title: Namori Graph Decomposition
---

## Overview

`namori_decomposition(graph)` decomposes an undirected Namori graph: every
connected component must contain exactly one cycle. It restores each cycle in
order and roots every attached tree at the cycle vertex where it connects.

The algorithm repeatedly removes vertices of degree at most one. The remaining
2-core is the collection of cycles. It then traverses those cycles and grows
the attached forest outward.

Parallel edges are supported and form a cycle of length two. A self-loop forms
a cycle of length one. Inactive edges are ignored.

If any connected component is a tree or contains more than one cycle, the
function returns `std::nullopt`.

## Result

`NamoriDecomposition<T>` contains:

| Field | Meaning |
| --- | --- |
| `component_count` | Number of connected components and cycles. |
| `cycles[c]` | Cycle vertices of component `c` in cyclic order. |
| `cycle_edge_ids[c]` | Edge from `cycles[c][i]` to the next cycle vertex, wrapping around. |
| `cycle_edge_costs[c]` | Costs aligned with `cycle_edge_ids[c]`. |
| `on_cycle[v]` | Whether `v` lies on its component's cycle. |
| `component[v]` | Component and cycle id containing `v`. |
| `cycle_root[v]` | Cycle vertex at the root of `v`'s attached tree. |
| `cycle_position[v]` | Position of `cycle_root[v]` in `cycles[component[v]]`. |
| `parent[v]` | Parent toward the cycle, or `-1` for cycle vertices. |
| `parent_edge[v]` | Edge to `parent[v]`, or `-1` for cycle vertices. |
| `depth[v]` | Number of tree edges from `v` to the cycle. |
| `dist_to_cycle[v]` | Weighted distance from `v` to the cycle. |
| `children[v]` | Children directed away from the cycle. |

`same_component(u, v)` tests ordinary graph connectivity.
`same_tree(u, v)` tests whether the vertices attach to the same cycle vertex.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `namori_decomposition(graph)` | Returns the decomposition, or `nullopt` for a non-Namori component. | `O(N + M)` |
| `decompose_namori(graph)` | Alias for `namori_decomposition`. | `O(N + M)` |

The graph must be undirected and built with `Graph::add_edge`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/namori.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> graph(5);
    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(2, 0, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(3, 4, 6);

    auto decomposition = m1une::graph::namori_decomposition(graph);
    if (!decomposition) return 0;

    std::cout << decomposition->cycle_root[4] << '\n';
    std::cout << decomposition->dist_to_cycle[4] << '\n';  // 11
}
```
