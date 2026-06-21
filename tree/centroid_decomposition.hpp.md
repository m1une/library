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
  bundledCode: "#line 1 \"tree/centroid_decomposition.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include\
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
    \ m1une\n\n\n#line 8 \"tree/centroid_decomposition.hpp\"\n\nnamespace m1une {\n\
    namespace tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition {\n\
    \    int n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n    std::vector<int>\
    \ order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>> children;\n\
    \n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int> _work_parent;\n\
    \    std::vector<char> _removed;\n\n    void build_component(const m1une::graph::Graph<T>&\
    \ g, int start, int p, int d) {\n        std::vector<int> nodes;\n        std::vector<int>\
    \ stack = {start};\n        _work_parent[start] = -2;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      nodes.push_back(v);\n            for (const auto& e : g[v]) {\n       \
    \         if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ != -1) continue;\n                _work_parent[e.to] = v;\n                stack.push_back(e.to);\n\
    \            }\n        }\n\n        for (int v : nodes) _subtree_size[v] = 1;\n\
    \        for (int i = int(nodes.size()) - 1; i >= 0; i--) {\n            int v\
    \ = nodes[i];\n            if (_work_parent[v] >= 0) _subtree_size[_work_parent[v]]\
    \ += _subtree_size[v];\n        }\n\n        int total = int(nodes.size());\n\
    \        int centroid = start;\n        int best = total + 1;\n        for (int\
    \ v : nodes) {\n            int largest = total - _subtree_size[v];\n        \
    \    for (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to])\
    \ continue;\n                if (_work_parent[e.to] == v) largest = std::max(largest,\
    \ _subtree_size[e.to]);\n            }\n            if (largest < best) {\n  \
    \              best = largest;\n                centroid = v;\n            }\n\
    \        }\n\n        for (int v : nodes) _work_parent[v] = -1;\n\n        parent[centroid]\
    \ = p;\n        depth[centroid] = d;\n        order.push_back(centroid);\n   \
    \     if (p == -1) {\n            roots.push_back(centroid);\n        } else {\n\
    \            children[p].push_back(centroid);\n        }\n        _removed[centroid]\
    \ = true;\n\n        for (const auto& e : g[centroid]) {\n            if (!e.alive\
    \ || _removed[e.to]) continue;\n            build_component(g, e.to, centroid,\
    \ d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition() : n(0)\
    \ {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>& g) {\n\
    \        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>& g) {\n\
    \        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_CENTROID_DECOMPOSITION_HPP\n#define M1UNE_TREE_CENTROID_DECOMPOSITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <vector>\n\n#include \"../graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition\
    \ {\n    int n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n \
    \   std::vector<int> order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>>\
    \ children;\n\n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _work_parent;\n    std::vector<char> _removed;\n\n    void build_component(const\
    \ m1une::graph::Graph<T>& g, int start, int p, int d) {\n        std::vector<int>\
    \ nodes;\n        std::vector<int> stack = {start};\n        _work_parent[start]\
    \ = -2;\n        while (!stack.empty()) {\n            int v = stack.back();\n\
    \            stack.pop_back();\n            nodes.push_back(v);\n            for\
    \ (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to]) continue;\n\
    \                if (_work_parent[e.to] != -1) continue;\n                _work_parent[e.to]\
    \ = v;\n                stack.push_back(e.to);\n            }\n        }\n\n \
    \       for (int v : nodes) _subtree_size[v] = 1;\n        for (int i = int(nodes.size())\
    \ - 1; i >= 0; i--) {\n            int v = nodes[i];\n            if (_work_parent[v]\
    \ >= 0) _subtree_size[_work_parent[v]] += _subtree_size[v];\n        }\n\n   \
    \     int total = int(nodes.size());\n        int centroid = start;\n        int\
    \ best = total + 1;\n        for (int v : nodes) {\n            int largest =\
    \ total - _subtree_size[v];\n            for (const auto& e : g[v]) {\n      \
    \          if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ == v) largest = std::max(largest, _subtree_size[e.to]);\n            }\n   \
    \         if (largest < best) {\n                best = largest;\n           \
    \     centroid = v;\n            }\n        }\n\n        for (int v : nodes) _work_parent[v]\
    \ = -1;\n\n        parent[centroid] = p;\n        depth[centroid] = d;\n     \
    \   order.push_back(centroid);\n        if (p == -1) {\n            roots.push_back(centroid);\n\
    \        } else {\n            children[p].push_back(centroid);\n        }\n \
    \       _removed[centroid] = true;\n\n        for (const auto& e : g[centroid])\
    \ {\n            if (!e.alive || _removed[e.to]) continue;\n            build_component(g,\
    \ e.to, centroid, d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition()\
    \ : n(0) {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>&\
    \ g) {\n        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g) {\n        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_CENTROID_DECOMPOSITION_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/centroid_decomposition.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/centroid_decomposition.hpp
layout: document
title: Centroid Decomposition
---

## Overview

`m1une::tree::CentroidDecomposition<T>` builds the centroid tree of an
undirected tree. It also supports forests; each connected component contributes
one centroid-tree root.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `n` | `int` | Number of vertices in the source graph. |
| `parent` | `std::vector<int>` | Parent in the centroid tree, or `-1` for a centroid root. |
| `depth` | `std::vector<int>` | Depth in the centroid tree. |
| `order` | `std::vector<int>` | Centroids in decomposition order. |
| `roots` | `std::vector<int>` | Centroid roots, one per connected component. |
| `children` | `std::vector<std::vector<int>>` | Children in the centroid tree. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `CentroidDecomposition(g)` | Builds the centroid decomposition. | $O(N \log N)$ |
| `void build(g)` | Rebuilds the decomposition. | $O(N \log N)$ |
| `int size()` | Returns `n`. | $O(1)$ |
| `bool empty()` | Returns whether `n == 0`. | $O(1)$ |
| `int root()` | Returns the first centroid root, or `-1`. | $O(1)$ |

## How to Use It in Problems

Centroid decomposition is useful when updates or queries are about distances to
many vertices on the original tree.

Typical examples:

* Turn a vertex on/off and query the nearest active vertex.
* Count active vertices within distance `K`.
* Add a value to one vertex and query a distance-dependent aggregate.
* Count pairs of vertices whose distance satisfies a condition.

The key idea is that every original vertex has only $O(\log N)$ ancestors in
the centroid tree. For a vertex `v`, climb:

```cpp
for (int c = v; c != -1; c = cd.parent[c]) {
    // c is a centroid ancestor of v, including v if v became a centroid.
}
```

If a query at `v` can be answered by combining information stored at each
centroid ancestor `c`, then each operation becomes $O(\log N)$ or
$O(\log^2 N)$ depending on how distances are obtained.

For repeated operations, precompute the centroid ancestors and their original
tree distances:

```cpp
m1une::tree::RootedTree<int> tree(g, 0);
m1une::tree::CentroidDecomposition<int> cd(g);

std::vector<std::vector<std::pair<int, int>>> centroid_path(n);
for (int v = 0; v < n; v++) {
    for (int c = v; c != -1; c = cd.parent[c]) {
        centroid_path[v].push_back({c, tree.dist_edges(v, c)});
    }
}
```

Now `centroid_path[v]` contains all relevant centroids for `v`, with distances
measured on the original tree.

## Dynamic Nearest Active Vertex

This is the most common centroid decomposition pattern.

Maintain `best[c]`: the minimum original-tree distance from centroid `c` to any
active vertex.

Activating a vertex `v` updates all centroid ancestors of `v`:

```cpp
const int INF = 1 << 30;
std::vector<int> best(n, INF);

auto activate = [&](int v) {
    for (auto [c, d] : centroid_path[v]) {
        best[c] = std::min(best[c], d);
    }
};
```

To query the nearest active vertex to `v`, try every centroid ancestor `c`.
Any active vertex `x` is represented at the first centroid that separates the
path between `v` and `x`, so checking all centroid ancestors is enough.

```cpp
auto query = [&](int v) {
    int ans = INF;
    for (auto [c, d] : centroid_path[v]) {
        ans = std::min(ans, best[c] + d);
    }
    return ans == INF ? -1 : ans;
};
```

Each `activate` and `query` is $O(\log N)$ after the preprocessing above.

For toggling vertices off, `best[c]` is not enough because the removed vertex may
have been the minimum. Use a `std::multiset<int>` for each centroid instead:

```cpp
std::vector<std::multiset<int>> distances(n);
std::vector<char> active(n, false);

auto activate = [&](int v) {
    if (active[v]) return;
    active[v] = true;
    for (auto [c, d] : centroid_path[v]) distances[c].insert(d);
};

auto deactivate = [&](int v) {
    if (!active[v]) return;
    active[v] = false;
    for (auto [c, d] : centroid_path[v]) {
        auto it = distances[c].find(d);
        distances[c].erase(it);
    }
};

auto query = [&](int v) {
    int ans = INF;
    for (auto [c, d] : centroid_path[v]) {
        if (!distances[c].empty()) ans = std::min(ans, d + *distances[c].begin());
    }
    return ans == INF ? -1 : ans;
};
```

This gives $O(\log^2 N)$ updates because each multiset operation costs
$O(\log N)$, and $O(\log N)$ queries.

## Counting Vertices Within Distance K

For queries like "how many active vertices are within distance `K` from `v`",
store distances at each centroid in sorted containers.

The usual static version keeps:

* `all[c]`: distances from centroid `c` to every active vertex whose
  `centroid_path` contains `c`.
* `sub[child]`: distances from `cd.parent[child]` to active vertices that lie in
  that centroid-child side.

When inserting an active vertex `x`, climb its centroid ancestors while
remembering the previous lower centroid:

```cpp
int prev = -1;
for (auto [c, d] : centroid_path[x]) {
    all[c].push_back(d);
    if (prev != -1) sub[prev].push_back(d);
    prev = c;
}
```

After sorting these vectors, query from `v` by climbing the same way. Add the
count from `all[c]` with distance at most `K - dist(v, c)`, then subtract the
count from the lower centroid side that also contains `v`.

This inclusion-exclusion pattern is the main trick for centroid decomposition
counting problems.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/centroid_decomposition.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);

    m1une::tree::CentroidDecomposition cd(g);
    std::cout << cd.root() << "\n";
}
```
