---
title: Directed Graph Algorithms
documentation_of: ../../graph/directed.hpp
---

## Overview

`graph/directed.hpp` includes algorithms whose main interpretation is directed,
plus direction-respecting shortest paths.

Use this header when the input edges are one-way, or when reachability/order
depends on edge direction.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | BFS, DAG shortest path, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and directed cycle check. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_directed_cycle(g)` for directed graphs. |
| `graph/flow.hpp` | Directed flow network | Max flow and min-cost flow. |
