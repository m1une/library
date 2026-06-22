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
  bundledCode: "#line 1 \"graph/range_edge_graph.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 8 \"graph/range_edge_graph.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct RangeEdgeNode {\n    int vertex;\n    int left;\n    int right;\n\
    };\n\ntemplate <class T>\nclass RangeEdgeGraph {\n    struct SegmentNode {\n \
    \       int left = 0;\n        int right = 0;\n        int from_vertex = -1;\n\
    \        int to_vertex = -1;\n    };\n\n    int _n;\n    Graph<T> _graph;\n  \
    \  std::vector<SegmentNode> _segment;\n\n    void assert_point(int point) const\
    \ {\n        (void)point;\n        assert(0 <= point && point < _n);\n    }\n\n\
    \    void assert_range(int left, int right) const {\n        (void)left;\n   \
    \     (void)right;\n        assert(0 <= left && left <= right && right <= _n);\n\
    \    }\n\n    void build(int node, int left, int right) {\n        _segment[node].left\
    \ = left;\n        _segment[node].right = right;\n        if (right - left ==\
    \ 1) {\n            _segment[node].from_vertex = left;\n            _segment[node].to_vertex\
    \ = left;\n            return;\n        }\n\n        int middle = (left + right)\
    \ / 2;\n        build(node * 2, left, middle);\n        build(node * 2 + 1, middle,\
    \ right);\n\n        int from_vertex = _graph.add_vertex();\n        int to_vertex\
    \ = _graph.add_vertex();\n        _segment[node].from_vertex = from_vertex;\n\
    \        _segment[node].to_vertex = to_vertex;\n\n        _graph.add_directed_edge(_segment[node\
    \ * 2].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(_segment[node\
    \ * 2 + 1].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2].to_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2 + 1].to_vertex, T());\n    }\n\n    void collect(int node,\
    \ int left, int right, bool from_side,\n                 std::vector<RangeEdgeNode>&\
    \ result) const {\n        const auto& current = _segment[node];\n        if (right\
    \ <= current.left || current.right <= left) return;\n        if (left <= current.left\
    \ && current.right <= right) {\n            int vertex = from_side ? current.from_vertex\
    \ : current.to_vertex;\n            result.push_back(RangeEdgeNode{vertex, current.left,\
    \ current.right});\n            return;\n        }\n        collect(node * 2,\
    \ left, right, from_side, result);\n        collect(node * 2 + 1, left, right,\
    \ from_side, result);\n    }\n\n   public:\n    RangeEdgeGraph() : RangeEdgeGraph(0)\
    \ {}\n\n    explicit RangeEdgeGraph(int point_count)\n        : _n(point_count),\n\
    \          _graph(point_count),\n          _segment(point_count == 0 ? 1 : point_count\
    \ * 4) {\n        assert(point_count >= 0);\n        if (point_count != 0) build(1,\
    \ 0, point_count);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int point_vertex(int point) const {\n        assert_point(point);\n    \
    \    return point;\n    }\n\n    int add_vertex() {\n        return _graph.add_vertex();\n\
    \    }\n\n    Graph<T>& graph() {\n        return _graph;\n    }\n\n    const\
    \ Graph<T>& graph() const {\n        return _graph;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ from_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, true, result);\n        return result;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ to_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, false, result);\n        return result;\n    }\n\n    int add_point_to_point(int\
    \ from, int to, T cost) {\n        assert_point(from);\n        assert_point(to);\n\
    \        return _graph.add_directed_edge(from, to, cost);\n    }\n\n    void add_point_to_range(int\
    \ from, int left, int right, T cost) {\n        assert_point(from);\n        for\
    \ (const auto& node : to_range_nodes(left, right)) {\n            _graph.add_directed_edge(from,\
    \ node.vertex, cost);\n        }\n    }\n\n    void add_range_to_point(int left,\
    \ int right, int to, T cost) {\n        assert_point(to);\n        for (const\
    \ auto& node : from_range_nodes(left, right)) {\n            _graph.add_directed_edge(node.vertex,\
    \ to, cost);\n        }\n    }\n\n    int add_range_to_range(int from_left, int\
    \ from_right, int to_left, int to_right,\n                           T cost) {\n\
    \        assert_range(from_left, from_right);\n        assert_range(to_left, to_right);\n\
    \        if (from_left == from_right || to_left == to_right) return -1;\n\n  \
    \      int auxiliary = add_vertex();\n        for (const auto& node : from_range_nodes(from_left,\
    \ from_right)) {\n            _graph.add_directed_edge(node.vertex, auxiliary,\
    \ cost);\n        }\n        for (const auto& node : to_range_nodes(to_left, to_right))\
    \ {\n            _graph.add_directed_edge(auxiliary, node.vertex, T());\n    \
    \    }\n        return auxiliary;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP\n#define M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct RangeEdgeNode {\n    int vertex;\n    int\
    \ left;\n    int right;\n};\n\ntemplate <class T>\nclass RangeEdgeGraph {\n  \
    \  struct SegmentNode {\n        int left = 0;\n        int right = 0;\n     \
    \   int from_vertex = -1;\n        int to_vertex = -1;\n    };\n\n    int _n;\n\
    \    Graph<T> _graph;\n    std::vector<SegmentNode> _segment;\n\n    void assert_point(int\
    \ point) const {\n        (void)point;\n        assert(0 <= point && point < _n);\n\
    \    }\n\n    void assert_range(int left, int right) const {\n        (void)left;\n\
    \        (void)right;\n        assert(0 <= left && left <= right && right <= _n);\n\
    \    }\n\n    void build(int node, int left, int right) {\n        _segment[node].left\
    \ = left;\n        _segment[node].right = right;\n        if (right - left ==\
    \ 1) {\n            _segment[node].from_vertex = left;\n            _segment[node].to_vertex\
    \ = left;\n            return;\n        }\n\n        int middle = (left + right)\
    \ / 2;\n        build(node * 2, left, middle);\n        build(node * 2 + 1, middle,\
    \ right);\n\n        int from_vertex = _graph.add_vertex();\n        int to_vertex\
    \ = _graph.add_vertex();\n        _segment[node].from_vertex = from_vertex;\n\
    \        _segment[node].to_vertex = to_vertex;\n\n        _graph.add_directed_edge(_segment[node\
    \ * 2].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(_segment[node\
    \ * 2 + 1].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2].to_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2 + 1].to_vertex, T());\n    }\n\n    void collect(int node,\
    \ int left, int right, bool from_side,\n                 std::vector<RangeEdgeNode>&\
    \ result) const {\n        const auto& current = _segment[node];\n        if (right\
    \ <= current.left || current.right <= left) return;\n        if (left <= current.left\
    \ && current.right <= right) {\n            int vertex = from_side ? current.from_vertex\
    \ : current.to_vertex;\n            result.push_back(RangeEdgeNode{vertex, current.left,\
    \ current.right});\n            return;\n        }\n        collect(node * 2,\
    \ left, right, from_side, result);\n        collect(node * 2 + 1, left, right,\
    \ from_side, result);\n    }\n\n   public:\n    RangeEdgeGraph() : RangeEdgeGraph(0)\
    \ {}\n\n    explicit RangeEdgeGraph(int point_count)\n        : _n(point_count),\n\
    \          _graph(point_count),\n          _segment(point_count == 0 ? 1 : point_count\
    \ * 4) {\n        assert(point_count >= 0);\n        if (point_count != 0) build(1,\
    \ 0, point_count);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int point_vertex(int point) const {\n        assert_point(point);\n    \
    \    return point;\n    }\n\n    int add_vertex() {\n        return _graph.add_vertex();\n\
    \    }\n\n    Graph<T>& graph() {\n        return _graph;\n    }\n\n    const\
    \ Graph<T>& graph() const {\n        return _graph;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ from_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, true, result);\n        return result;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ to_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, false, result);\n        return result;\n    }\n\n    int add_point_to_point(int\
    \ from, int to, T cost) {\n        assert_point(from);\n        assert_point(to);\n\
    \        return _graph.add_directed_edge(from, to, cost);\n    }\n\n    void add_point_to_range(int\
    \ from, int left, int right, T cost) {\n        assert_point(from);\n        for\
    \ (const auto& node : to_range_nodes(left, right)) {\n            _graph.add_directed_edge(from,\
    \ node.vertex, cost);\n        }\n    }\n\n    void add_range_to_point(int left,\
    \ int right, int to, T cost) {\n        assert_point(to);\n        for (const\
    \ auto& node : from_range_nodes(left, right)) {\n            _graph.add_directed_edge(node.vertex,\
    \ to, cost);\n        }\n    }\n\n    int add_range_to_range(int from_left, int\
    \ from_right, int to_left, int to_right,\n                           T cost) {\n\
    \        assert_range(from_left, from_right);\n        assert_range(to_left, to_right);\n\
    \        if (from_left == from_right || to_left == to_right) return -1;\n\n  \
    \      int auxiliary = add_vertex();\n        for (const auto& node : from_range_nodes(from_left,\
    \ from_right)) {\n            _graph.add_directed_edge(node.vertex, auxiliary,\
    \ cost);\n        }\n        for (const auto& node : to_range_nodes(to_left, to_right))\
    \ {\n            _graph.add_directed_edge(auxiliary, node.vertex, T());\n    \
    \    }\n        return auxiliary;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/range_edge_graph.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-06-22 23:50:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/range_edge_graph.hpp
layout: document
title: Range Edge Graph
---

## Overview

`RangeEdgeGraph<T>` compactly represents directed edges whose endpoints are
points or contiguous ranges. It supports operations such as:

- add an edge from one point to every point in a range;
- add an edge from every point in a range to one point;
- add an edge from every point in one range to every point in another range.

Adding all conceptual edges explicitly can require quadratic space.
`RangeEdgeGraph` uses two segment-tree-shaped directed graphs and auxiliary
vertices, reducing each range operation to $O(\log N)$ actual edges.

This is the “representing intervals as edges” technique used in problems such
as [AtCoder ABC414 G](https://atcoder.jp/contests/abc414/editorial/14071) and
Codeforces 786B.

The represented graph is an ordinary `Graph<T>`, so it can be passed directly
to `dijkstra`, `bellman_ford`, or other compatible graph algorithms. Edge costs
added by this class may be arbitrary values of `T`; choose a shortest-path
algorithm that supports those costs.

## Vertex IDs

The original `N` point vertices always have IDs `0, 1, ..., N - 1`.
`point_vertex(i)` returns `i`.

The constructor adds internal segment-tree vertices after the original points.
Range-to-range operations add one auxiliary vertex each. Therefore, use
`range_graph.graph().size()` rather than `range_graph.size()` when iterating
over every vertex in the expanded graph.

| Method | Meaning |
| --- | --- |
| `size()` | Number of original point vertices. |
| `point_vertex(i)` | Expanded-graph vertex representing point `i`. |
| `add_vertex()` | Adds and returns a custom auxiliary vertex. |
| `graph()` | Returns the expanded `Graph<T>`. |

## Adding Edges

All ranges are half-open: `[left, right)`.

| Method | Conceptual edges added |
| --- | --- |
| `add_point_to_point(from, to, cost)` | `from -> to` with cost `cost`. |
| `add_point_to_range(from, left, right, cost)` | `from -> v` for every `v` in `[left, right)`, each with cost `cost`. |
| `add_range_to_point(left, right, to, cost)` | `v -> to` for every `v` in `[left, right)`, each with cost `cost`. |
| `add_range_to_range(from_left, from_right, to_left, to_right, cost)` | `u -> v` for every `u` in the first range and `v` in the second range, each with cost `cost`. |

Empty ranges add no edges. `add_range_to_range` returns its auxiliary vertex,
or `-1` if either range is empty.

These methods add directed edges. To represent both directions, call the
corresponding operation twice with the ranges reversed.

## Canonical Range Nodes

Some problems need a cost that depends on the boundary of a canonical segment,
as in the ABC414 G editorial. The following methods expose the $O(\log N)$
segment-tree nodes covering a range:

| Method | Property of each returned vertex |
| --- | --- |
| `from_range_nodes(left, right)` | Every point in the node's interval can reach the vertex with cost zero. |
| `to_range_nodes(left, right)` | The vertex can reach every point in the node's interval with cost zero. |

Both return `std::vector<RangeEdgeNode>`. Each node has:

| Member | Meaning |
| --- | --- |
| `vertex` | Vertex ID in the expanded graph. |
| `left`, `right` | Half-open interval represented by that vertex. |

The returned intervals are disjoint and partition the requested range. Custom
edges can be added through `graph().add_directed_edge`.

## Construction

For each segment-tree interval, the graph has two orientations:

- On the **from side**, point edges lead upward from children to parents. Thus
  every point can reach each covering interval vertex.
- On the **to side**, edges lead downward from parents to children. Thus each
  interval vertex can reach every point it contains.

All structural edges have cost zero. A range-to-range operation creates one
auxiliary vertex, adds the requested cost while leaving the source-side cover,
and then reaches the destination-side cover with zero-cost edges.

## Complexity

Let `N` be the number of original points.

| Operation | Added vertices | Added edges | Time |
| --- | --- | --- | --- |
| Constructor | At most $2N - 2$ internal | At most $4N - 4$ | $O(N)$ |
| Point to point | 0 | 1 | Amortized $O(1)$ |
| Point to range | 0 | $O(\log N)$ | $O(\log N)$ |
| Range to point | 0 | $O(\log N)$ | $O(\log N)$ |
| Range to range | 1 | $O(\log N)$ | $O(\log N)$ |
| Either cover query | 0 | 0 | $O(\log N)$ |

After `Q` range-to-range additions, the expanded graph has $O(N + Q)$
vertices and $O(N + Q\log N)$ edges.

## Example

```cpp
#include "graph/dijkstra.hpp"
#include "graph/range_edge_graph.hpp"
#include <iostream>

int main() {
    m1une::graph::RangeEdgeGraph<long long> graph(6);

    // Every point in [0, 2) has an edge of cost 7 to every point in [3, 6).
    graph.add_range_to_range(0, 2, 3, 6, 7);

    auto result = m1une::graph::dijkstra(graph.graph(), 1);
    for (int i = 0; i < graph.size(); i++) {
        std::cout << result.dist[i] << "\n";
    }
}
```
