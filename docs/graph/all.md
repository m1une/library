---
title: Graph All
documentation_of: ../../graph/all.hpp
---

## Overview

`graph/all.hpp` includes every general graph header in this directory. It is
convenient when writing quickly during a contest and you do not want to manage
individual graph includes.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/graph.hpp` | `Graph<T>` and `Edge<T>` adjacency-list container. |
| `graph/bfs.hpp` | Unweighted shortest paths. |
| `graph/dijkstra.hpp` | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Shortest paths with negative edges and negative-cycle marking. |
| `graph/warshall_floyd.hpp` | All-pairs shortest paths. |
| `graph/grid.hpp` | Helper for converting 2D grid cells to graph vertex ids. |
| `graph/topological_sort.hpp` | DAG ordering and cycle check. |
| `graph/scc.hpp` | Strongly connected components and condensation DAG. |
| `graph/lowlink.hpp` | Articulation points and bridges in undirected graphs. |
| `graph/bipartite.hpp` | Two-colorability check. |
| `graph/connected_components.hpp` | Weak connected components. |
| `graph/cycle_detection.hpp` | Finds one directed or undirected cycle. |
| `graph/kruskal.hpp` | Minimum spanning forest. |

## Example

```cpp
#include "graph/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    auto dist = m1une::graph::dijkstra(g, 0).dist;
    std::cout << dist[1] << "\n";
}
```
