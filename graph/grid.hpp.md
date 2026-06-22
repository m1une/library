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
  bundledCode: "#line 1 \"graph/grid.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
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
    \ m1une\n\n\n#line 10 \"graph/grid.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct Grid {\n   private:\n    int _h;\n    int _w;\n\n   public:\n  \
    \  static constexpr std::array<int, 4> di4 = {-1, 0, 1, 0};\n    static constexpr\
    \ std::array<int, 4> dj4 = {0, 1, 0, -1};\n    static constexpr std::array<int,\
    \ 8> di8 = {-1, -1, -1, 0, 0, 1, 1, 1};\n    static constexpr std::array<int,\
    \ 8> dj8 = {-1, 0, 1, -1, 1, -1, 0, 1};\n\n    Grid() : _h(0), _w(0) {}\n    Grid(int\
    \ h, int w) : _h(h), _w(w) {\n        assert(0 <= h);\n        assert(0 <= w);\n\
    \    }\n\n    int height() const {\n        return _h;\n    }\n\n    int width()\
    \ const {\n        return _w;\n    }\n\n    int size() const {\n        return\
    \ _h * _w;\n    }\n\n    bool empty() const {\n        return size() == 0;\n \
    \   }\n\n    bool inside(int i, int j) const {\n        return 0 <= i && i < _h\
    \ && 0 <= j && j < _w;\n    }\n\n    int id(int i, int j) const {\n        assert(inside(i,\
    \ j));\n        return i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v)\
    \ const {\n        assert(0 <= v && v < size());\n        return {v / _w, v %\
    \ _w};\n    }\n\n    std::vector<std::pair<int, int>> adj4(int i, int j) const\
    \ {\n        assert(inside(i, j));\n        std::vector<std::pair<int, int>> result;\n\
    \        result.reserve(4);\n        for (int k = 0; k < 4; k++) {\n         \
    \   int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni, nj)) result.emplace_back(ni,\
    \ nj);\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj8(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(8);\n        for (int k = 0; k < 8; k++)\
    \ {\n            int ni = i + di8[k], nj = j + dj8[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<int> adj4_ids(int v) const {\n        auto [i, j] = pos(v);\n\
    \        std::vector<int> result;\n        result.reserve(4);\n        for (auto\
    \ [ni, nj] : adj4(i, j)) result.push_back(id(ni, nj));\n        return result;\n\
    \    }\n\n    std::vector<int> adj8_ids(int v) const {\n        auto [i, j] =\
    \ pos(v);\n        std::vector<int> result;\n        result.reserve(8);\n    \
    \    for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni, nj));\n        return\
    \ result;\n    }\n\n    Graph<int> graph4() const {\n        return graph4([](int,\
    \ int) { return true; });\n    }\n\n    Graph<int> graph8() const {\n        return\
    \ graph8([](int, int) { return true; });\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph4(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj4(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph8(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj8(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_GRID_HPP\n#define M1UNE_GRAPH_GRID_HPP 1\n\n#include\
    \ <array>\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct Grid {\n   private:\n\
    \    int _h;\n    int _w;\n\n   public:\n    static constexpr std::array<int,\
    \ 4> di4 = {-1, 0, 1, 0};\n    static constexpr std::array<int, 4> dj4 = {0, 1,\
    \ 0, -1};\n    static constexpr std::array<int, 8> di8 = {-1, -1, -1, 0, 0, 1,\
    \ 1, 1};\n    static constexpr std::array<int, 8> dj8 = {-1, 0, 1, -1, 1, -1,\
    \ 0, 1};\n\n    Grid() : _h(0), _w(0) {}\n    Grid(int h, int w) : _h(h), _w(w)\
    \ {\n        assert(0 <= h);\n        assert(0 <= w);\n    }\n\n    int height()\
    \ const {\n        return _h;\n    }\n\n    int width() const {\n        return\
    \ _w;\n    }\n\n    int size() const {\n        return _h * _w;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    bool inside(int\
    \ i, int j) const {\n        return 0 <= i && i < _h && 0 <= j && j < _w;\n  \
    \  }\n\n    int id(int i, int j) const {\n        assert(inside(i, j));\n    \
    \    return i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v) const {\n\
    \        assert(0 <= v && v < size());\n        return {v / _w, v % _w};\n   \
    \ }\n\n    std::vector<std::pair<int, int>> adj4(int i, int j) const {\n     \
    \   assert(inside(i, j));\n        std::vector<std::pair<int, int>> result;\n\
    \        result.reserve(4);\n        for (int k = 0; k < 4; k++) {\n         \
    \   int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni, nj)) result.emplace_back(ni,\
    \ nj);\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj8(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(8);\n        for (int k = 0; k < 8; k++)\
    \ {\n            int ni = i + di8[k], nj = j + dj8[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<int> adj4_ids(int v) const {\n        auto [i, j] = pos(v);\n\
    \        std::vector<int> result;\n        result.reserve(4);\n        for (auto\
    \ [ni, nj] : adj4(i, j)) result.push_back(id(ni, nj));\n        return result;\n\
    \    }\n\n    std::vector<int> adj8_ids(int v) const {\n        auto [i, j] =\
    \ pos(v);\n        std::vector<int> result;\n        result.reserve(8);\n    \
    \    for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni, nj));\n        return\
    \ result;\n    }\n\n    Graph<int> graph4() const {\n        return graph4([](int,\
    \ int) { return true; });\n    }\n\n    Graph<int> graph8() const {\n        return\
    \ graph8([](int, int) { return true; });\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph4(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj4(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph8(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj8(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GRAPH_GRID_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/grid.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/grid.hpp
layout: document
title: Grid
---

## Overview

`Grid` is a helper for treating an `H x W` grid as a graph with `H * W`
vertices. It centralizes the standard conversion:

```cpp
id(i, j) = i * W + j
pos(v) = {v / W, v % W}
```

Use it when a problem gives cells as `(i, j)` but graph algorithms expect a
single vertex id.

Blocked cells are not compressed away by the graph builders. The generated
graph always has `H * W` vertices, so `grid.id(i, j)` remains valid and stable
for every cell. Blocked cells simply become isolated if you use a passable
predicate.

## Graph Orientation

The graph builders create undirected grid graphs. Use `graph4` for four-way
movement and `graph8` for eight-way movement.

## How to Use It

Create `Grid grid(H, W)`, then use `id(i, j)` before calling graph algorithms
and `pos(v)` when you need to convert an answer back to grid coordinates.

For local movement without constructing a graph, use `adj4(i, j)` or
`adj8(i, j)`. These return only cells inside the grid.

For graph construction:

* `graph4()` builds an undirected 4-neighbor graph with every cell passable.
* `graph8()` builds an undirected 8-neighbor graph with every cell passable.
* `graph4(passable)` and `graph8(passable)` skip edges incident to blocked
  cells.

The passable predicate must be callable as `bool passable(int i, int j)`.

## Fields and Methods

| Member | Type / Signature | Meaning | Complexity |
| --- | --- | --- | --- |
| `di4` | `static constexpr std::array<int, 4>` | Row offsets for 4-neighbor movement. | $O(1)$ |
| `dj4` | `static constexpr std::array<int, 4>` | Column offsets for 4-neighbor movement. | $O(1)$ |
| `di8` | `static constexpr std::array<int, 8>` | Row offsets for 8-neighbor movement. | $O(1)$ |
| `dj8` | `static constexpr std::array<int, 8>` | Column offsets for 8-neighbor movement. | $O(1)$ |
| Constructor | `Grid()` | Creates an empty grid. | $O(1)$ |
| Constructor | `Grid(int h, int w)` | Creates an `h x w` grid. | $O(1)$ |
| `height` | `int height() const` | Returns `h`. | $O(1)$ |
| `width` | `int width() const` | Returns `w`. | $O(1)$ |
| `size` | `int size() const` | Returns `h * w`. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the grid has no cells. | $O(1)$ |
| `inside` | `bool inside(int i, int j) const` | Returns whether `(i, j)` is inside the grid. | $O(1)$ |
| `id` | `int id(int i, int j) const` | Converts cell `(i, j)` to vertex id. | $O(1)$ |
| `pos` | `std::pair<int, int> pos(int v) const` | Converts vertex id `v` to `(i, j)`. | $O(1)$ |
| `adj4` | `std::vector<std::pair<int, int>> adj4(int i, int j) const` | Returns inside 4-neighbor cells of `(i, j)`. | $O(1)$ |
| `adj8` | `std::vector<std::pair<int, int>> adj8(int i, int j) const` | Returns inside 8-neighbor cells of `(i, j)`. | $O(1)$ |
| `adj4_ids` | `std::vector<int> adj4_ids(int v) const` | Returns inside 4-neighbor vertex ids of `v`. | $O(1)$ |
| `adj8_ids` | `std::vector<int> adj8_ids(int v) const` | Returns inside 8-neighbor vertex ids of `v`. | $O(1)$ |
| `graph4` | `Graph<int> graph4() const` | Builds an undirected 4-neighbor graph with all cells passable. | $O(H \cdot W)$ |
| `graph8` | `Graph<int> graph8() const` | Builds an undirected 8-neighbor graph with all cells passable. | $O(H \cdot W)$ |
| `graph4` | `template <class Passable> Graph<int> graph4(Passable passable) const` | Builds an undirected 4-neighbor graph using a passable predicate. | $O(H \cdot W)$ |
| `graph8` | `template <class Passable> Graph<int> graph8(Passable passable) const` | Builds an undirected 8-neighbor graph using a passable predicate. | $O(H \cdot W)$ |

## Example

```cpp
#include "graph/bfs.hpp"
#include "graph/grid.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    int H = 3, W = 4;
    std::vector<std::string> S = {
        "....",
        ".##.",
        "....",
    };

    m1une::graph::Grid grid(H, W);
    auto passable = [&](int i, int j) {
        return S[i][j] != '#';
    };

    auto g = grid.graph4(passable);
    int s = grid.id(0, 0);
    int t = grid.id(2, 3);

    auto res = m1une::graph::bfs(g, s);
    std::cout << res.dist[t] << "\n";

    for (int v : res.path(t)) {
        auto [i, j] = grid.pos(v);
        std::cout << "(" << i << "," << j << ") ";
    }
    std::cout << "\n";
}
```
