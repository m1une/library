---
title: Dijkstra
documentation_of: ../../graph/dijkstra.hpp
---

## Overview

Dijkstra's algorithm computes shortest paths from one or more sources when all
edge costs are non-negative. It repeatedly fixes the unreached vertex with the
smallest tentative distance, using a priority queue.

Use it for typical weighted shortest path problems with costs like time,
distance, or price. Do not use it if a reachable edge can have a negative cost;
use Bellman-Ford in that case.

## Graph Orientation

Direction is respected. `dijkstra` works on directed graphs as written, and
also on undirected graphs built with `add_edge`.

## How to Use It

Use `Graph<T>` with a numeric cost type, usually `long long`.

The optional `inf` argument is the value used for unreachable vertices. The
default is `std::numeric_limits<T>::max() / 4`, which leaves room for additions
without overflowing in ordinary use. Pass your own `inf` if edge costs or path
costs can be close to that value.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<T>` | `dist[v]` is the shortest distance from the nearest source to `v`, or `inf` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on one shortest path, or `-1`. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `inf` | `T` | The unreachable-distance sentinel used by this run. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))` | Runs from one source. | $O((N + M) \log N)$ |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, const std::vector<int>& sources, T inf = std::numeric_limits<T>::max() / T(4))` | Runs from multiple sources. | $O((N + M) \log N)$ |

## Example

```cpp
#include "graph/dijkstra.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    g.add_directed_edge(0, 2, 3);
    g.add_directed_edge(2, 1, 4);

    auto res = m1une::graph::dijkstra(g, 0);
    std::cout << res.dist[1] << "\n";  // 7
}
```
