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
  bundledCode: "#line 1 \"tree/heavy_light_decomposition.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 10 \"tree/heavy_light_decomposition.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\nstruct HldPathSegment {\n    int l;\n    int r;\n   \
    \ bool reversed;\n};\n\ntemplate <class T = int>\nstruct HeavyLightDecomposition\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy;\n    std::vector<int> head;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n        assert(tin[v] != -1);\n    }\n\n    static void add_segment(std::vector<HldPathSegment>&\
    \ result, int l, int r, bool reversed) {\n        if (l < r) result.push_back({l,\
    \ r, reversed});\n    }\n\n   public:\n    HeavyLightDecomposition() : root(-1),\
    \ _n(0) {}\n    explicit HeavyLightDecomposition(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n = g.size();\n      \
    \  root = _n == 0 ? -1 : root_;\n        parent.assign(_n, -2);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 1);\n        heavy.assign(_n, -1);\n        head.assign(_n,\
    \ -1);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        if (_n == 0) return;\n        assert(0 <=\
    \ root && root < _n);\n\n        std::vector<int> dfs_order;\n        dfs_order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        parent[root] = -1;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            dfs_order.push_back(v);\n            for (const auto& e : g[v]) {\n\
    \                if (!e.alive) continue;\n                if (parent[e.to] !=\
    \ -2) continue;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                stack.push_back(e.to);\n            }\n\
    \        }\n\n        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n\
    \            int v = dfs_order[i];\n            if (parent[v] == -1) continue;\n\
    \            int p = parent[v];\n            subtree_size[p] += subtree_size[v];\n\
    \            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p]\
    \ = v;\n        }\n\n        order.assign(dfs_order.size(), -1);\n        int\
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {std::pair<int,\
    \ int>{root, root}};\n        while (!starts.empty()) {\n            auto [start,\
    \ h] = starts.back();\n            starts.pop_back();\n            for (int v\
    \ = start; v != -1; v = heavy[v]) {\n                head[v] = h;\n          \
    \      tin[v] = timer;\n                order[timer++] = v;\n                for\
    \ (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {\n                    if\
    \ (!it->alive) continue;\n                    int to = it->to;\n             \
    \       if (parent[to] != v || to == heavy[v]) continue;\n                   \
    \ starts.push_back({to, to});\n                }\n            }\n        }\n \
    \       for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n            int\
    \ v = dfs_order[i];\n            tout[v] = tin[v] + subtree_size[v];\n       \
    \ }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    int lca(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        while (head[u]\
    \ != head[v]) {\n            if (depth[head[u]] < depth[head[v]]) std::swap(u,\
    \ v);\n            u = parent[head[u]];\n        }\n        return depth[u] <\
    \ depth[v] ? u : v;\n    }\n\n    int dist_edges(int u, int v) const {\n     \
    \   int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n \
    \   }\n\n    T dist_cost(int u, int v) const {\n        int w = lca(u, v);\n \
    \       return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   while (v != -1) {\n            int h = head[v];\n            int len = depth[v]\
    \ - depth[h];\n            if (k <= len) return order[tin[v] - k];\n         \
    \   k -= len + 1;\n            v = parent[h];\n        }\n        return -1;\n\
    \    }\n\n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::pair<int, int> subtree_range(int v, bool\
    \ edge = false) const {\n        check_vertex(v);\n        return {tin[v] + (edge\
    \ ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment> path_segments(int\
    \ u, int v, bool edge = false) const {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        std::vector<HldPathSegment> result, down;\n        while (head[u] !=\
    \ head[v]) {\n            if (depth[head[u]] >= depth[head[v]]) {\n          \
    \      add_segment(result, tin[head[u]], tin[u] + 1, true);\n                u\
    \ = parent[head[u]];\n            } else {\n                add_segment(down,\
    \ tin[head[v]], tin[v] + 1, false);\n                v = parent[head[v]];\n  \
    \          }\n        }\n\n        if (depth[u] >= depth[v]) {\n            add_segment(result,\
    \ tin[v] + (edge ? 1 : 0), tin[u] + 1, true);\n        } else {\n            add_segment(down,\
    \ tin[u] + (edge ? 1 : 0), tin[v] + 1, false);\n        }\n        std::reverse(down.begin(),\
    \ down.end());\n        result.insert(result.end(), down.begin(), down.end());\n\
    \        return result;\n    }\n\n    template <class F>\n    void for_each_path(int\
    \ u, int v, F f, bool edge = false) const {\n        for (auto seg : path_segments(u,\
    \ v, edge)) f(seg.l, seg.r, seg.reversed);\n    }\n};\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP\n#define M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\nstruct HldPathSegment {\n    int l;\n    int r;\n    bool reversed;\n\
    };\n\ntemplate <class T = int>\nstruct HeavyLightDecomposition {\n    using cost_type\
    \ = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    std::vector<int> depth;\n  \
    \  std::vector<T> dist;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ heavy;\n    std::vector<int> head;\n    std::vector<int> tin;\n    std::vector<int>\
    \ tout;\n    std::vector<int> order;\n\n   private:\n    int _n;\n\n    void check_vertex(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        assert(tin[v] != -1);\n\
    \    }\n\n    static void add_segment(std::vector<HldPathSegment>& result, int\
    \ l, int r, bool reversed) {\n        if (l < r) result.push_back({l, r, reversed});\n\
    \    }\n\n   public:\n    HeavyLightDecomposition() : root(-1), _n(0) {}\n   \
    \ explicit HeavyLightDecomposition(const m1une::graph::Graph<T>& g, int root_\
    \ = 0) {\n        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        parent.assign(_n, -2);\n        parent_edge.assign(_n, -1);\n       \
    \ depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n        subtree_size.assign(_n,\
    \ 1);\n        heavy.assign(_n, -1);\n        head.assign(_n, -1);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n   \
    \     std::vector<int> dfs_order;\n        dfs_order.reserve(_n);\n        std::vector<int>\
    \ stack = {root};\n        parent[root] = -1;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      dfs_order.push_back(v);\n            for (const auto& e : g[v]) {\n   \
    \             if (!e.alive) continue;\n                if (parent[e.to] != -2)\
    \ continue;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                stack.push_back(e.to);\n            }\n\
    \        }\n\n        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n\
    \            int v = dfs_order[i];\n            if (parent[v] == -1) continue;\n\
    \            int p = parent[v];\n            subtree_size[p] += subtree_size[v];\n\
    \            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p]\
    \ = v;\n        }\n\n        order.assign(dfs_order.size(), -1);\n        int\
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {std::pair<int,\
    \ int>{root, root}};\n        while (!starts.empty()) {\n            auto [start,\
    \ h] = starts.back();\n            starts.pop_back();\n            for (int v\
    \ = start; v != -1; v = heavy[v]) {\n                head[v] = h;\n          \
    \      tin[v] = timer;\n                order[timer++] = v;\n                for\
    \ (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {\n                    if\
    \ (!it->alive) continue;\n                    int to = it->to;\n             \
    \       if (parent[to] != v || to == heavy[v]) continue;\n                   \
    \ starts.push_back({to, to});\n                }\n            }\n        }\n \
    \       for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n            int\
    \ v = dfs_order[i];\n            tout[v] = tin[v] + subtree_size[v];\n       \
    \ }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    int lca(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        while (head[u]\
    \ != head[v]) {\n            if (depth[head[u]] < depth[head[v]]) std::swap(u,\
    \ v);\n            u = parent[head[u]];\n        }\n        return depth[u] <\
    \ depth[v] ? u : v;\n    }\n\n    int dist_edges(int u, int v) const {\n     \
    \   int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n \
    \   }\n\n    T dist_cost(int u, int v) const {\n        int w = lca(u, v);\n \
    \       return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   while (v != -1) {\n            int h = head[v];\n            int len = depth[v]\
    \ - depth[h];\n            if (k <= len) return order[tin[v] - k];\n         \
    \   k -= len + 1;\n            v = parent[h];\n        }\n        return -1;\n\
    \    }\n\n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::pair<int, int> subtree_range(int v, bool\
    \ edge = false) const {\n        check_vertex(v);\n        return {tin[v] + (edge\
    \ ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment> path_segments(int\
    \ u, int v, bool edge = false) const {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        std::vector<HldPathSegment> result, down;\n        while (head[u] !=\
    \ head[v]) {\n            if (depth[head[u]] >= depth[head[v]]) {\n          \
    \      add_segment(result, tin[head[u]], tin[u] + 1, true);\n                u\
    \ = parent[head[u]];\n            } else {\n                add_segment(down,\
    \ tin[head[v]], tin[v] + 1, false);\n                v = parent[head[v]];\n  \
    \          }\n        }\n\n        if (depth[u] >= depth[v]) {\n            add_segment(result,\
    \ tin[v] + (edge ? 1 : 0), tin[u] + 1, true);\n        } else {\n            add_segment(down,\
    \ tin[u] + (edge ? 1 : 0), tin[v] + 1, false);\n        }\n        std::reverse(down.begin(),\
    \ down.end());\n        result.insert(result.end(), down.begin(), down.end());\n\
    \        return result;\n    }\n\n    template <class F>\n    void for_each_path(int\
    \ u, int v, F f, bool edge = false) const {\n        for (auto seg : path_segments(u,\
    \ v, edge)) f(seg.l, seg.r, seg.reversed);\n    }\n};\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n#endif  // M1UNE_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/heavy_light_decomposition.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
documentation_of: tree/heavy_light_decomposition.hpp
layout: document
title: Heavy Light Decomposition
---

## Overview

`m1une::tree::HeavyLightDecomposition<T>` decomposes a rooted tree into heavy
paths. It maps every vertex to a position `tin[v]` in a base array, which lets
path and subtree queries be answered by ordinary range data structures.

Use it with `ds::Segtree`, `LazySegtree`, or another range-query
structure over the HLD order.

Inactive graph edges are ignored.

## Path Segments

`path_segments(u, v, edge)` returns half-open base-array intervals covering the
path from `u` to `v`.

Each segment has:

| Field | Description |
| --- | --- |
| `l`, `r` | Half-open interval `[l, r)` in HLD order. |
| `reversed` | Whether the path direction traverses the interval from `r - 1` down to `l`. |

When `edge == false`, vertex positions are covered. When `edge == true`, edge
values are assumed to be stored at the child vertex position, so the LCA vertex
is excluded.

## Public Members

The input graph is first rooted at `root`. Then vertices are reordered into the
HLD base array. If you build a segment tree with HLD, position `tin[v]` is the
position corresponding to original vertex `v`.

For a connected tree, these arrays have size `N`, except `order`, which also
has size `N`. The graph is expected to be a tree. If the graph is disconnected,
only the component reachable from `root` gets valid HLD positions; vertices
outside that component keep `tin[v] == -1`.

| Member | Type | What is stored |
| --- | --- | --- |
| `root` | `int` | The root used to orient the tree. It is `-1` for an empty graph. |
| `parent[v]` | `int` | The parent of `v` in the rooted original tree. `parent[root] == -1`. |
| `parent_edge[v]` | `int` | The graph edge id connecting `parent[v]` to `v`. It is `-1` for the root. |
| `depth[v]` | `int` | Number of edges from `root` to `v`. |
| `dist[v]` | `T` | Sum of edge costs from `root` to `v`. For an unweighted tree, this is the same as `depth[v]` if all costs are `1`. |
| `subtree_size[v]` | `int` | Number of vertices in the rooted subtree of `v`, including `v` itself. |
| `heavy[v]` | `int` | The child of `v` with the largest subtree. This child continues the same heavy path. It is `-1` if `v` has no children. |
| `head[v]` | `int` | The top vertex of the heavy path containing `v`. If `head[v] == head[u]`, then `u` and `v` are on the same heavy path. |
| `tin[v]` | `int` | Position of original vertex `v` in the HLD base array. This is the index to use in segment trees. |
| `tout[v]` | `int` | One past the end of the rooted subtree interval of `v` in HLD order. The subtree is `[tin[v], tout[v])`. |
| `order[i]` | `int` | The original vertex stored at HLD base-array position `i`. This is the inverse of `tin`: `order[tin[v]] == v`. |

Important relationships:

* Vertex `v` is stored at base-array index `tin[v]`.
* `order[i]` converts a base-array index back to the original vertex.
* The rooted subtree of `v` occupies the contiguous interval
  `[tin[v], tout[v])`.
* If you store edge values instead of vertex values, store the edge
  `(parent[v], v)` at `tin[v]`. The root has no parent edge.
* Heavy paths are contiguous in the base array. That is why a path can be split
  into only $O(\log N)$ intervals.

For example, suppose the original tree is:

```text
0
|- 1
|  |- 3
|  `- 4
`- 2
```

If `1` is chosen as the heavy child of `0`, and `3` is chosen as the heavy child
of `1`, one possible HLD order is:

```text
index: 0  1  2  3  4
order: 0  1  3  4  2
```

Then:

```text
tin[0] = 0
tin[1] = 1
tin[3] = 2
tin[4] = 3
tin[2] = 4
head[0] = head[1] = head[3] = 0
head[4] = 4
head[2] = 2
```

The subtree of vertex `1` is vertices `{1, 3, 4}`, and it is stored
contiguously as `[tin[1], tout[1]) == [1, 4)`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `HeavyLightDecomposition(g, root)` | Builds HLD data. | $O(N)$ |
| `void build(g, root)` | Rebuilds the structure. | $O(N)$ |
| `int lca(u, v)` | Returns the lowest common ancestor. | $O(\log N)$ |
| `int dist_edges(u, v)` | Returns the number of edges on the path. | $O(\log N)$ |
| `T dist_cost(u, v)` | Returns the sum of edge costs on the path. | $O(\log N)$ |
| `int kth_ancestor(v, k)` | Returns the `k`-th ancestor, or `-1`. | $O(\log N)$ |
| `int jump(from, to, k)` | Returns the `k`-th vertex on the path, or `-1`. | $O(\log N)$ |
| `std::pair<int, int> subtree_range(v, edge)` | Returns the subtree interval. With `edge=true`, excludes `v`. | $O(1)$ |
| `std::vector<HldPathSegment> path_segments(u, v, edge)` | Returns path intervals in path order. | $O(\log N)$ intervals |
| `for_each_path(u, v, f, edge)` | Calls `f(l, r, reversed)` for each path segment. | $O(\log N)$ calls |

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "graph/graph.hpp"
#include "monoid/add.hpp"
#include "tree/heavy_light_decomposition.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    m1une::tree::HeavyLightDecomposition<int> hld(g, 0);
    std::vector<long long> base(3, 1);
    m1une::ds::Segtree<m1une::monoid::Add<long long>> seg(base);

    long long sum = 0;
    hld.for_each_path(0, 2, [&](int l, int r, bool) {
        sum += seg.prod(l, r);
    });
    std::cout << sum << "\n"; // 3
}
```
