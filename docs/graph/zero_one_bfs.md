---
title: 0-1 BFS
documentation_of: ../../graph/zero_one_bfs.hpp
---

## Overview

0-1 BFS computes shortest paths when every edge cost is either `0` or `1`.
It uses a deque instead of a priority queue: relaxing a `0`-cost edge pushes the
next vertex to the front, and relaxing a `1`-cost edge pushes it to the back.

Use it instead of Dijkstra when all costs are `0` or `1`. It gives the same
shortest distances for this special case in linear time.

## Graph Orientation

Direction is respected. `zero_one_bfs` works on directed graphs as written, and
also on undirected graphs built with `add_edge`.

Every edge cost must be exactly `0` or `1`.

## How to Use It

Call `zero_one_bfs(g, s)` for one source, or `zero_one_bfs(g, sources)` for
multiple sources. Multi-source mode sets every source distance to `0`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<int>` | `dist[v]` is the minimum total cost from the nearest source to `v`, or `inf` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on one shortest path, or `-1`. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `inf` | `int` | The unreachable-distance sentinel used by this run. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `zero_one_bfs` | `template <class T> ZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int s, int inf = std::numeric_limits<int>::max() / 2)` | Runs 0-1 BFS from one source. | $O(N + M)$ |
| `zero_one_bfs` | `template <class T> ZeroOneBfsResult zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources, int inf = std::numeric_limits<int>::max() / 2)` | Runs multi-source 0-1 BFS. | $O(N + M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/zero_one_bfs.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(4);
    g.add_directed_edge(0, 1, 1);
    g.add_directed_edge(0, 2, 0);
    g.add_directed_edge(2, 1, 0);
    g.add_directed_edge(1, 3, 1);

    auto res = m1une::graph::zero_one_bfs(g, 0);
    std::cout << res.dist[3] << "\n";  // 1
}
```
