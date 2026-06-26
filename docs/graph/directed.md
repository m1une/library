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
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | BFS, 0-1 BFS, DAG shortest path, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and directed cycle check. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/two_sat.hpp` | Implication graph | 2-SAT clauses, satisfiability, and one assignment. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_directed_cycle(g)` for directed graphs. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
