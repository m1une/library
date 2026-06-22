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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/dominator_tree.test.cpp
    title: verify/graph/dominator_tree.test.cpp
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
  bundledCode: "#line 1 \"graph/dominator_tree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
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
    \ m1une\n\n\n#line 9 \"graph/dominator_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct DominatorTree {\n    int root;\n    std::vector<int> immediate_dominator;\n\
    \    std::vector<std::vector<int>> children;\n    std::vector<int> dfs_order;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n\n    int size() const\
    \ {\n        return int(immediate_dominator.size());\n    }\n\n    bool reachable(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < size());\n        return\
    \ immediate_dominator[vertex] != -1;\n    }\n\n    bool dominates(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < size());\n \
    \       assert(0 <= vertex && vertex < size());\n        return\n            reachable(ancestor)\
    \ &&\n            reachable(vertex) &&\n            tin[ancestor] <= tin[vertex]\
    \ &&\n            tin[vertex] < tout[ancestor];\n    }\n};\n\n// Lengauer-Tarjan\
    \ immediate dominators from one start vertex.\ntemplate <class T>\nDominatorTree\
    \ dominator_tree(const Graph<T>& graph, int root) {\n    int n = graph.size();\n\
    \    assert(0 <= root && root < n);\n\n    std::vector<int> dfs_index(n, -1);\n\
    \    std::vector<int> vertex;\n    std::vector<int> parent_vertex(n, -1);\n  \
    \  std::vector<std::pair<int, int>> stack;\n    dfs_index[root] = 0;\n    vertex.push_back(root);\n\
    \    stack.emplace_back(root, 0);\n\n    while (!stack.empty()) {\n        int\
    \ current = stack.back().first;\n        int& edge_index = stack.back().second;\n\
    \        if (edge_index == int(graph[current].size())) {\n            stack.pop_back();\n\
    \            continue;\n        }\n        const auto& edge = graph[current][edge_index++];\n\
    \        if (!edge.alive || dfs_index[edge.to] != -1) continue;\n        parent_vertex[edge.to]\
    \ = current;\n        dfs_index[edge.to] = int(vertex.size());\n        vertex.push_back(edge.to);\n\
    \        stack.emplace_back(edge.to, 0);\n    }\n\n    int reachable_count = int(vertex.size());\n\
    \    std::vector<std::vector<int>> predecessor(reachable_count);\n    for (int\
    \ from : vertex) {\n        for (const auto& edge : graph[from]) {\n         \
    \   if (!edge.alive || dfs_index[edge.to] == -1) continue;\n            predecessor[dfs_index[edge.to]].push_back(dfs_index[from]);\n\
    \        }\n    }\n\n    std::vector<int> parent(reachable_count, -1);\n    for\
    \ (int index = 1; index < reachable_count; ++index) {\n        parent[index] =\
    \ dfs_index[parent_vertex[vertex[index]]];\n    }\n\n    std::vector<int> semi(reachable_count);\n\
    \    std::vector<int> idom(reachable_count, -1);\n    std::vector<int> ancestor(reachable_count,\
    \ -1);\n    std::vector<int> label(reachable_count);\n    std::vector<std::vector<int>>\
    \ bucket(reachable_count);\n    for (int index = 0; index < reachable_count; ++index)\
    \ {\n        semi[index] = index;\n        label[index] = index;\n    }\n\n  \
    \  auto compress = [&](int start) {\n        std::vector<int> path;\n        int\
    \ current = start;\n        while (\n            ancestor[current] != -1 &&\n\
    \            ancestor[ancestor[current]] != -1\n        ) {\n            path.push_back(current);\n\
    \            current = ancestor[current];\n        }\n        for (int index =\
    \ int(path.size()) - 1; index >= 0; --index) {\n            int node = path[index];\n\
    \            int parent_node = ancestor[node];\n            if (semi[label[parent_node]]\
    \ < semi[label[node]]) {\n                label[node] = label[parent_node];\n\
    \            }\n            ancestor[node] = ancestor[parent_node];\n        }\n\
    \    };\n\n    auto eval = [&](int node) {\n        if (ancestor[node] == -1)\
    \ return label[node];\n        compress(node);\n        int parent_node = ancestor[node];\n\
    \        if (semi[label[parent_node]] < semi[label[node]]) {\n            return\
    \ label[parent_node];\n        }\n        return label[node];\n    };\n\n    for\
    \ (int current = reachable_count - 1; current >= 1; --current) {\n        for\
    \ (int previous : predecessor[current]) {\n            semi[current] = std::min(semi[current],\
    \ semi[eval(previous)]);\n        }\n        bucket[semi[current]].push_back(current);\n\
    \        ancestor[current] = parent[current];\n\n        int parent_node = parent[current];\n\
    \        for (int node : bucket[parent_node]) {\n            int best = eval(node);\n\
    \            idom[node] =\n                semi[best] < semi[node] ? best : parent_node;\n\
    \        }\n        bucket[parent_node].clear();\n    }\n\n    for (int current\
    \ = 1; current < reachable_count; ++current) {\n        if (idom[current] != semi[current])\
    \ {\n            idom[current] = idom[idom[current]];\n        }\n    }\n    idom[0]\
    \ = 0;\n\n    DominatorTree result;\n    result.root = root;\n    result.immediate_dominator.assign(n,\
    \ -1);\n    result.children.assign(n, {});\n    result.dfs_order = vertex;\n \
    \   for (int index = 0; index < reachable_count; ++index) {\n        int current\
    \ = vertex[index];\n        int dominator = vertex[idom[index]];\n        result.immediate_dominator[current]\
    \ = dominator;\n        if (current != root) result.children[dominator].push_back(current);\n\
    \    }\n\n    result.tin.assign(n, -1);\n    result.tout.assign(n, -1);\n    int\
    \ timer = 0;\n    std::vector<std::pair<int, int>> tree_stack;\n    tree_stack.emplace_back(root,\
    \ 0);\n    result.tin[root] = timer++;\n    while (!tree_stack.empty()) {\n  \
    \      int current = tree_stack.back().first;\n        int& child_index = tree_stack.back().second;\n\
    \        if (child_index == int(result.children[current].size())) {\n        \
    \    result.tout[current] = timer;\n            tree_stack.pop_back();\n     \
    \       continue;\n        }\n        int child = result.children[current][child_index++];\n\
    \        result.tin[child] = timer++;\n        tree_stack.emplace_back(child,\
    \ 0);\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_DOMINATOR_TREE_HPP\n#define M1UNE_GRAPH_DOMINATOR_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#include \"\
    graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct DominatorTree {\n\
    \    int root;\n    std::vector<int> immediate_dominator;\n    std::vector<std::vector<int>>\
    \ children;\n    std::vector<int> dfs_order;\n    std::vector<int> tin;\n    std::vector<int>\
    \ tout;\n\n    int size() const {\n        return int(immediate_dominator.size());\n\
    \    }\n\n    bool reachable(int vertex) const {\n        assert(0 <= vertex &&\
    \ vertex < size());\n        return immediate_dominator[vertex] != -1;\n    }\n\
    \n    bool dominates(int ancestor, int vertex) const {\n        assert(0 <= ancestor\
    \ && ancestor < size());\n        assert(0 <= vertex && vertex < size());\n  \
    \      return\n            reachable(ancestor) &&\n            reachable(vertex)\
    \ &&\n            tin[ancestor] <= tin[vertex] &&\n            tin[vertex] < tout[ancestor];\n\
    \    }\n};\n\n// Lengauer-Tarjan immediate dominators from one start vertex.\n\
    template <class T>\nDominatorTree dominator_tree(const Graph<T>& graph, int root)\
    \ {\n    int n = graph.size();\n    assert(0 <= root && root < n);\n\n    std::vector<int>\
    \ dfs_index(n, -1);\n    std::vector<int> vertex;\n    std::vector<int> parent_vertex(n,\
    \ -1);\n    std::vector<std::pair<int, int>> stack;\n    dfs_index[root] = 0;\n\
    \    vertex.push_back(root);\n    stack.emplace_back(root, 0);\n\n    while (!stack.empty())\
    \ {\n        int current = stack.back().first;\n        int& edge_index = stack.back().second;\n\
    \        if (edge_index == int(graph[current].size())) {\n            stack.pop_back();\n\
    \            continue;\n        }\n        const auto& edge = graph[current][edge_index++];\n\
    \        if (!edge.alive || dfs_index[edge.to] != -1) continue;\n        parent_vertex[edge.to]\
    \ = current;\n        dfs_index[edge.to] = int(vertex.size());\n        vertex.push_back(edge.to);\n\
    \        stack.emplace_back(edge.to, 0);\n    }\n\n    int reachable_count = int(vertex.size());\n\
    \    std::vector<std::vector<int>> predecessor(reachable_count);\n    for (int\
    \ from : vertex) {\n        for (const auto& edge : graph[from]) {\n         \
    \   if (!edge.alive || dfs_index[edge.to] == -1) continue;\n            predecessor[dfs_index[edge.to]].push_back(dfs_index[from]);\n\
    \        }\n    }\n\n    std::vector<int> parent(reachable_count, -1);\n    for\
    \ (int index = 1; index < reachable_count; ++index) {\n        parent[index] =\
    \ dfs_index[parent_vertex[vertex[index]]];\n    }\n\n    std::vector<int> semi(reachable_count);\n\
    \    std::vector<int> idom(reachable_count, -1);\n    std::vector<int> ancestor(reachable_count,\
    \ -1);\n    std::vector<int> label(reachable_count);\n    std::vector<std::vector<int>>\
    \ bucket(reachable_count);\n    for (int index = 0; index < reachable_count; ++index)\
    \ {\n        semi[index] = index;\n        label[index] = index;\n    }\n\n  \
    \  auto compress = [&](int start) {\n        std::vector<int> path;\n        int\
    \ current = start;\n        while (\n            ancestor[current] != -1 &&\n\
    \            ancestor[ancestor[current]] != -1\n        ) {\n            path.push_back(current);\n\
    \            current = ancestor[current];\n        }\n        for (int index =\
    \ int(path.size()) - 1; index >= 0; --index) {\n            int node = path[index];\n\
    \            int parent_node = ancestor[node];\n            if (semi[label[parent_node]]\
    \ < semi[label[node]]) {\n                label[node] = label[parent_node];\n\
    \            }\n            ancestor[node] = ancestor[parent_node];\n        }\n\
    \    };\n\n    auto eval = [&](int node) {\n        if (ancestor[node] == -1)\
    \ return label[node];\n        compress(node);\n        int parent_node = ancestor[node];\n\
    \        if (semi[label[parent_node]] < semi[label[node]]) {\n            return\
    \ label[parent_node];\n        }\n        return label[node];\n    };\n\n    for\
    \ (int current = reachable_count - 1; current >= 1; --current) {\n        for\
    \ (int previous : predecessor[current]) {\n            semi[current] = std::min(semi[current],\
    \ semi[eval(previous)]);\n        }\n        bucket[semi[current]].push_back(current);\n\
    \        ancestor[current] = parent[current];\n\n        int parent_node = parent[current];\n\
    \        for (int node : bucket[parent_node]) {\n            int best = eval(node);\n\
    \            idom[node] =\n                semi[best] < semi[node] ? best : parent_node;\n\
    \        }\n        bucket[parent_node].clear();\n    }\n\n    for (int current\
    \ = 1; current < reachable_count; ++current) {\n        if (idom[current] != semi[current])\
    \ {\n            idom[current] = idom[idom[current]];\n        }\n    }\n    idom[0]\
    \ = 0;\n\n    DominatorTree result;\n    result.root = root;\n    result.immediate_dominator.assign(n,\
    \ -1);\n    result.children.assign(n, {});\n    result.dfs_order = vertex;\n \
    \   for (int index = 0; index < reachable_count; ++index) {\n        int current\
    \ = vertex[index];\n        int dominator = vertex[idom[index]];\n        result.immediate_dominator[current]\
    \ = dominator;\n        if (current != root) result.children[dominator].push_back(current);\n\
    \    }\n\n    result.tin.assign(n, -1);\n    result.tout.assign(n, -1);\n    int\
    \ timer = 0;\n    std::vector<std::pair<int, int>> tree_stack;\n    tree_stack.emplace_back(root,\
    \ 0);\n    result.tin[root] = timer++;\n    while (!tree_stack.empty()) {\n  \
    \      int current = tree_stack.back().first;\n        int& child_index = tree_stack.back().second;\n\
    \        if (child_index == int(result.children[current].size())) {\n        \
    \    result.tout[current] = timer;\n            tree_stack.pop_back();\n     \
    \       continue;\n        }\n        int child = result.children[current][child_index++];\n\
    \        result.tin[child] = timer++;\n        tree_stack.emplace_back(child,\
    \ 0);\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_DOMINATOR_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/dominator_tree.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-23 03:14:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/dominator_tree.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/dominator_tree.hpp
layout: document
title: Dominator Tree
---

## Overview

In a directed graph rooted at `root`, vertex `u` dominates vertex `v` when
every directed path from `root` to `v` passes through `u`.

`dominator_tree(graph, root)` computes immediate dominators with the
Lengauer-Tarjan algorithm. The immediate dominator of `v` is the closest strict
dominator of `v`; these edges form the dominator tree.

Only vertices reachable from `root` belong to the tree. Inactive edges are
ignored.

## Result

`DominatorTree` exposes:

| Member | Description |
| --- | --- |
| `root` | Start vertex used for the computation. |
| `immediate_dominator[v]` | Immediate dominator of `v`; the root dominates itself, and unreachable vertices store `-1`. |
| `children[v]` | Children of `v` in the dominator tree. |
| `dfs_order` | Reachable vertices in the original graph's DFS discovery order. |
| `tin`, `tout` | Euler intervals of the dominator tree; unreachable vertices store `-1`. |

Methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `size()` | Returns the original graph's vertex count. | $O(1)$ |
| `reachable(v)` | Returns whether `v` is reachable from the root. | $O(1)$ |
| `dominates(u, v)` | Returns whether `u` dominates `v`. | $O(1)$ |

## Complexity

The Lengauer-Tarjan algorithm runs in near-linear time,
$O((N+M)\alpha(N,M))$, and uses $O(N+M)$ memory.

The graph traversal and dominator-tree Euler traversal are iterative, avoiding
recursion-depth issues on long paths.

## Example

```cpp
#include "graph/dominator_tree.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 2);
    graph.add_directed_edge(1, 3);
    graph.add_directed_edge(2, 3);

    auto tree = m1une::graph::dominator_tree(graph, 0);
    std::cout << tree.immediate_dominator[3] << "\n"; // 0
    std::cout << tree.dominates(0, 3) << "\n";        // 1
}
```
