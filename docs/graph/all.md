---
title: Graph All
documentation_of: ../../graph/all.hpp
---

## Overview

`graph/all.hpp` includes every general graph header in this directory. It is
convenient when writing quickly during a contest and you do not want to manage
individual graph includes.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/graph.hpp` | Container | `Graph<T>` and `Edge<T>` adjacency-list container. |
| `graph/shortest_path.hpp` | Direction-respecting | BFS, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/directed.hpp` | Directed-oriented bundle | Directed algorithms plus shortest paths and flow. |
| `graph/undirected.hpp` | Undirected-oriented bundle | Undirected algorithms plus shortest paths and grid helpers. |
| `graph/flow.hpp` | Directed flow network | Max flow and min-cost flow. |
| `graph/bfs.hpp` | Direction-respecting | Unweighted shortest paths. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges and negative-cycle marking. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |
| `graph/grid.hpp` | Undirected graph builder | Helper for converting 2D grid cells to graph vertex ids. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and cycle check. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/bipartite.hpp` | Direction ignored | Two-colorability check. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Finds one cycle with the matching function. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/max_flow.hpp` | Directed flow network | Dinic maximum flow and minimum cut. |
| `graph/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |

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
