---
title: Shortest Path
documentation_of: ../../graph/shortest_path.hpp
---

## Overview

`graph/shortest_path.hpp` includes the shortest-path algorithms whose behavior
respects the adjacency stored in `Graph<T>`.

Most of these algorithms are direction-respecting and can be used on directed
graphs as written or on undirected graphs built with `add_edge`. The exception
is `dag_shortest_path`, which is specifically for directed acyclic graphs.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/bfs.hpp` | Direction-respecting | Shortest paths by number of edges. |
| `graph/zero_one_bfs.hpp` | Direction-respecting | Shortest paths with edge costs `0` or `1`. |
| `graph/dag_shortest_path.hpp` | Directed DAG only | Shortest paths in a DAG, including negative edge costs. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
