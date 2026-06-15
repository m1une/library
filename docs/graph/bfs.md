---
title: BFS
documentation_of: ../../graph/bfs.hpp
---

## Overview

Breadth-first search computes shortest paths in an unweighted graph, where every
edge has the same cost. It expands vertices in increasing distance order:
first the source, then all vertices one edge away, then all vertices two edges
away, and so on.

Use BFS when the answer is measured by the number of edges, not by edge
weights. For weighted shortest paths, use Dijkstra or Bellman-Ford instead.

## Graph Orientation

Direction is respected. `bfs` works on directed graphs as written, and also on
undirected graphs built with `add_edge`.

## How to Use It

Call `bfs(g, s)` for one source, or `bfs(g, sources)` when several vertices
should start at distance `0`. Multi-source BFS is useful for problems like
"distance to the nearest special vertex".

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<int>` | `dist[v]` is the number of edges from the nearest source to `v`, or `-1` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on the restored BFS tree path, or `-1` for a source/unreachable vertex. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bfs` | `template <class T> BfsResult bfs(const Graph<T>& g, int s)` | Runs BFS from one source. | $O(N+M)$ |
| `bfs` | `template <class T> BfsResult bfs(const Graph<T>& g, const std::vector<int>& sources)` | Runs multi-source BFS. | $O(N+M)$ |

## Example

```cpp
#include "graph/bfs.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);

    auto res = m1une::graph::bfs(g, 0);
    std::cout << res.dist[2] << "\n";  // 2

    for (int v : res.path(2)) {
        std::cout << v << " ";         // 0 1 2
    }
    std::cout << "\n";
}
```
