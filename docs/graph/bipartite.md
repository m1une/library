---
title: Bipartite Graph
documentation_of: ../../graph/bipartite.hpp
---

## Overview

A graph is bipartite if its vertices can be colored with two colors so that
every edge connects vertices of different colors. Equivalently, the graph has
no odd-length cycle.

This function checks bipartiteness by BFS coloring. Edge direction is ignored:
each edge is treated as an undirected constraint between its endpoints. That
makes it useful for ordinary undirected graphs and also for directed graphs
where only the endpoint constraint matters.

Use this for two-team assignments, parity constraints, grid checkerboard
problems, and "does an odd cycle exist?" checks.

## How to Use It

Call `bipartite(g)` when you need both the yes/no answer and the colors. Call
`is_bipartite(g)` when you only need the boolean.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `is_bipartite` | `bool` | Whether a valid two-coloring exists. |
| `color` | `std::vector<int>` | `color[v]` is `0` or `1` for the assigned color, or `-1` before assignment. |

For a disconnected graph, every component is colored independently. The chosen
colors are not unique; flipping all colors in a component gives another valid
answer.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bipartite` | `template <class T> BipartiteResult bipartite(const Graph<T>& g)` | Returns a bipartite flag and colors. | $O(N+M)$ |
| `is_bipartite` | `template <class T> bool is_bipartite(const Graph<T>& g)` | Returns only the bipartite flag. | $O(N+M)$ |

## Example

```cpp
#include "graph/bipartite.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    auto res = m1une::graph::bipartite(g);
    std::cout << res.is_bipartite << "\n";  // 1
    std::cout << res.color[0] << " " << res.color[1] << "\n";
}
```
