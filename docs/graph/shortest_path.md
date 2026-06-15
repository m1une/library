---
title: Shortest Path
documentation_of: ../../graph/shortest_path.hpp
---

## Overview

`graph/shortest_path.hpp` includes the shortest-path algorithms whose behavior
respects the adjacency stored in `Graph<T>`.

These algorithms can be used on directed graphs and on undirected graphs. For
undirected graphs, build edges with `add_edge`, which stores both directions.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/bfs.hpp` | Direction-respecting | Shortest paths by number of edges. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |
