---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/rerooting_dp.hpp\"\n\n\n\n#include <vector>\n\n#line\
    \ 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n#line 7\
    \ \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
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
    \ m1une\n\n\n#line 7 \"tree/rerooting_dp.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T, class DP, class Merge, class AddVertex, class AddEdge>\n\
    std::vector<DP> rerooting_dp(const m1une::graph::Graph<T>& g, DP id, Merge merge,\
    \ AddVertex add_vertex,\n                             AddEdge add_edge) {\n  \
    \  int n = g.size();\n    std::vector<int> parent(n, -2), parent_edge(n, -1),\
    \ order;\n    order.reserve(n);\n    for (int root = 0; root < n; root++) {\n\
    \        if (parent[root] != -2) continue;\n        parent[root] = -1;\n     \
    \   std::vector<int> stack = {root};\n        while (!stack.empty()) {\n     \
    \       int v = stack.back();\n            stack.pop_back();\n            order.push_back(v);\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive) continue;\n\
    \                if (parent[e.to] != -2) continue;\n                parent[e.to]\
    \ = v;\n                parent_edge[e.to] = e.id;\n                stack.push_back(e.to);\n\
    \            }\n        }\n    }\n\n    std::vector<DP> down(n, id), outside(n,\
    \ id), answer(n, id);\n    for (int i = n - 1; i >= 0; i--) {\n        int v =\
    \ order[i];\n        DP acc = id;\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            if (parent[e.to] != v) continue;\n\
    \            acc = merge(acc, add_edge(down[e.to], e));\n        }\n        down[v]\
    \ = add_vertex(acc, v);\n    }\n\n    for (int v : order) {\n        int d = int(g[v].size());\n\
    \        std::vector<DP> contrib(d, id);\n        for (int i = 0; i < d; i++)\
    \ {\n            const auto& e = g[v][i];\n            if (!e.alive) continue;\n\
    \            if (parent[e.to] == v) {\n                contrib[i] = add_edge(down[e.to],\
    \ e);\n            } else if (parent[v] == e.to && parent_edge[v] == e.id) {\n\
    \                contrib[i] = add_edge(outside[v], e);\n            }\n      \
    \  }\n\n        std::vector<DP> pref(d + 1, id), suff(d + 1, id);\n        for\
    \ (int i = 0; i < d; i++) pref[i + 1] = merge(pref[i], contrib[i]);\n        for\
    \ (int i = d - 1; i >= 0; i--) suff[i] = merge(contrib[i], suff[i + 1]);\n   \
    \     answer[v] = add_vertex(pref[d], v);\n\n        for (int i = 0; i < d; i++)\
    \ {\n            const auto& e = g[v][i];\n            if (!e.alive) continue;\n\
    \            if (parent[e.to] != v) continue;\n            outside[e.to] = add_vertex(merge(pref[i],\
    \ suff[i + 1]), v);\n        }\n    }\n\n    return answer;\n}\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_REROOTING_DP_HPP\n#define M1UNE_TREE_REROOTING_DP_HPP\
    \ 1\n\n#include <vector>\n\n#include \"../graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\ntemplate <class T, class DP, class Merge, class AddVertex,\
    \ class AddEdge>\nstd::vector<DP> rerooting_dp(const m1une::graph::Graph<T>& g,\
    \ DP id, Merge merge, AddVertex add_vertex,\n                             AddEdge\
    \ add_edge) {\n    int n = g.size();\n    std::vector<int> parent(n, -2), parent_edge(n,\
    \ -1), order;\n    order.reserve(n);\n    for (int root = 0; root < n; root++)\
    \ {\n        if (parent[root] != -2) continue;\n        parent[root] = -1;\n \
    \       std::vector<int> stack = {root};\n        while (!stack.empty()) {\n \
    \           int v = stack.back();\n            stack.pop_back();\n           \
    \ order.push_back(v);\n            for (const auto& e : g[v]) {\n            \
    \    if (!e.alive) continue;\n                if (parent[e.to] != -2) continue;\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                stack.push_back(e.to);\n            }\n        }\n    }\n\n \
    \   std::vector<DP> down(n, id), outside(n, id), answer(n, id);\n    for (int\
    \ i = n - 1; i >= 0; i--) {\n        int v = order[i];\n        DP acc = id;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (parent[e.to] != v) continue;\n            acc = merge(acc, add_edge(down[e.to],\
    \ e));\n        }\n        down[v] = add_vertex(acc, v);\n    }\n\n    for (int\
    \ v : order) {\n        int d = int(g[v].size());\n        std::vector<DP> contrib(d,\
    \ id);\n        for (int i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n\
    \            if (!e.alive) continue;\n            if (parent[e.to] == v) {\n \
    \               contrib[i] = add_edge(down[e.to], e);\n            } else if (parent[v]\
    \ == e.to && parent_edge[v] == e.id) {\n                contrib[i] = add_edge(outside[v],\
    \ e);\n            }\n        }\n\n        std::vector<DP> pref(d + 1, id), suff(d\
    \ + 1, id);\n        for (int i = 0; i < d; i++) pref[i + 1] = merge(pref[i],\
    \ contrib[i]);\n        for (int i = d - 1; i >= 0; i--) suff[i] = merge(contrib[i],\
    \ suff[i + 1]);\n        answer[v] = add_vertex(pref[d], v);\n\n        for (int\
    \ i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n            if (!e.alive)\
    \ continue;\n            if (parent[e.to] != v) continue;\n            outside[e.to]\
    \ = add_vertex(merge(pref[i], suff[i + 1]), v);\n        }\n    }\n\n    return\
    \ answer;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_REROOTING_DP_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/rerooting_dp.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/rerooting_dp.hpp
layout: document
title: Rerooting DP
---

## Overview

`rerooting_dp` is a generic all-roots tree DP helper. It computes one DP value
for every possible root of an undirected tree, or for every vertex in each
component of a forest.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

## Function

```cpp
template <class T, class DP, class Merge, class AddVertex, class AddEdge>
std::vector<DP> rerooting_dp(
    const m1une::graph::Graph<T>& g,
    DP id,
    Merge merge,
    AddVertex add_vertex,
    AddEdge add_edge
);
```

The callbacks mean:

| Callback | Meaning |
| --- | --- |
| `id` | Identity DP value for `merge`. |
| `merge(a, b)` | Combines independent neighbor contributions. It should be associative. |
| `add_vertex(acc, v)` | Finalizes the merged contributions at vertex `v`. |
| `add_edge(dp, e)` | Converts a neighbor-side DP value through adjacency edge `e`. |

For an edge contribution used at vertex `v`, `e` is the adjacency edge from `v`
to that neighbor.

## DP Meaning

Think of the tree as being cut at an edge. A `DP` value represents one connected
side of the cut, rooted at the vertex closest to the edge.

For a vertex `v`, each neighbor `to` gives one independent contribution:

```cpp
contribution_from_to = add_edge(dp_of_side_rooted_at_to, edge_v_to);
```

Then all neighbor contributions are merged, and `v` itself is added:

```cpp
answer[v] = add_vertex(merge(all neighbor contributions), v);
```

The library computes this for every `v`. When it sends information from `v` to
one child, it merges all contributions except that child, applies
`add_vertex(..., v)`, and passes that value across the edge later. This is the
usual rerooting trick; prefix and suffix products make the "all except one"
merge fast.

Most tree DPs use a commutative `merge`, such as `+`, `max`, or `min`. The
implementation applies `merge` in adjacency-list order, so non-commutative
operations are deterministic but depend on that order.

## How to Design the Callbacks

Use this checklist:

1. Decide what `DP` means for a rooted connected piece.
2. Choose `id`, the value for an empty set of neighbor contributions.
3. Define `merge(a, b)`, which combines two independent neighbor sides.
4. Define `add_edge(dp, e)`, which changes distances or values when the piece is
   viewed from the other endpoint of edge `e`.
5. Define `add_vertex(acc, v)`, which adds the current vertex after all neighbor
   sides have been merged.

If the final answer for root `v` is "the DP of the whole tree rooted at `v`",
then it is exactly `result[v]`.

## Complexity

`rerooting_dp` runs in $O(N)$ callback calls on a tree.

## Example: Farthest Distance

The following computes the eccentricity of each vertex: the maximum number of
edges from that vertex to any other vertex.

Here `DP` is one integer:

* Meaning: maximum distance from the current root of this piece to a vertex in
  the piece.
* `id = 0`: an empty set of children contributes distance `0`.
* `merge = max`: keep the farthest side.
* `add_edge(dp, e) = dp + 1`: crossing one unweighted edge increases every
  distance by `1`.
* `add_vertex(acc, v) = acc`: the current vertex has distance `0`, so it does
  not change the maximum.

```cpp
#include "graph/graph.hpp"
#include "tree/rerooting_dp.hpp"
#include <algorithm>
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);

    auto ecc = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return std::max(a, b); },
        [](int acc, int) { return acc; },
        [](int dp, const auto&) { return dp + 1; }
    );

    std::cout << ecc[0] << "\n"; // 2
}
```

## Example: Sum of Distances

The following computes, for every vertex `v`, the sum of distances from `v` to
all vertices.

Use a DP state with:

* `size`: number of vertices in this piece.
* `sum`: sum of distances from the current root of this piece to all vertices in
  the piece.

When crossing an edge of cost `w`, every distance increases by `w`, so
`sum += size * w`.

```cpp
#include "graph/graph.hpp"
#include "tree/rerooting_dp.hpp"
#include <iostream>

struct DP {
    long long size;
    long long sum;
};

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 1);

    auto res = m1une::tree::rerooting_dp(
        g,
        DP{0, 0},
        [](DP a, DP b) {
            return DP{a.size + b.size, a.sum + b.sum};
        },
        [](DP acc, int) {
            return DP{acc.size + 1, acc.sum};
        },
        [](DP dp, const auto& e) {
            return DP{dp.size, dp.sum + dp.size * e.cost};
        }
    );

    std::cout << res[0].sum << "\n"; // dist(0,0)+dist(0,1)+dist(0,2)+dist(0,3) = 5
}
```

## Common Patterns

For counting vertices:

```cpp
id = 0
merge(a, b) = a + b
add_vertex(acc, v) = acc + 1
add_edge(dp, e) = dp
```

For maximum weighted distance:

```cpp
id = 0
merge(a, b) = std::max(a, b)
add_vertex(acc, v) = acc
add_edge(dp, e) = dp + e.cost
```

For DP states with several fields, `merge` usually adds or takes the best of
each field, `add_edge` shifts the state across one edge, and `add_vertex`
accounts for the current vertex.
