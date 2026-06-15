---
title: Undirected Graph Algorithms
documentation_of: ../../graph/undirected.hpp
---

## Overview

`graph/undirected.hpp` includes algorithms whose main interpretation is
undirected, plus the shortest-path bundle. In that bundle, use the
direction-respecting algorithms on graphs built with `add_edge`; the DAG
shortest-path helper is directed-only.

Use this header when edges represent two-way movement or an endpoint constraint
where direction should not matter.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Mixed shortest-path bundle | Use BFS, 0-1 BFS, Dijkstra, Bellman-Ford, and Warshall-Floyd on undirected graphs built with `add_edge`; DAG shortest path is directed-only. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |
