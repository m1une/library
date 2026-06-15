---
title: Undirected Graph Algorithms
documentation_of: ../../graph/undirected.hpp
---

## Overview

`graph/undirected.hpp` includes algorithms whose main interpretation is
undirected, plus direction-respecting shortest paths that also work on graphs
built with `add_edge`.

Use this header when edges represent two-way movement or an endpoint constraint
where direction should not matter.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Direction-respecting | Works on undirected graphs built with `add_edge`. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/bipartite.hpp` | Direction ignored | Two-colorability of endpoint constraints. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |
