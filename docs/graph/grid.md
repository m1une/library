---
title: Grid
documentation_of: ../../graph/grid.hpp
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
