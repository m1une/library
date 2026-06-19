---
title: DAG Shortest Path
documentation_of: ../../graph/dag_shortest_path.hpp
---

## Overview

`dag_shortest_path` computes shortest paths in a directed acyclic graph. It
first obtains a topological order, then relaxes outgoing edges in that order.

Because a DAG has no directed cycles, this works even when edge costs are
negative. Use it when the graph is known to be a DAG; it is simpler and faster
than Bellman-Ford for this case.

## Graph Orientation

Directed only, and the graph must be acyclic. If the graph has a directed
cycle, the function returns `std::nullopt`.

An undirected graph built with `add_edge` usually contains a two-edge directed
cycle in the stored adjacency, so this algorithm is not for ordinary
undirected graphs.

## How to Use It

Call `dag_shortest_path(g, s)` for one source, or
`dag_shortest_path(g, sources)` for multiple sources. Multi-source mode sets
every source distance to `0`.

The return type is `std::optional<DagShortestPathResult<T>>`.

* If it has a value, the graph was a DAG and the result contains shortest
  paths.
* If it is `std::nullopt`, the graph was cyclic and DAG shortest paths were not
  computed.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<T>` | `dist[v]` is the shortest distance from the nearest source to `v`, or `inf` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on one shortest path, or `-1`. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `topological_order` | `std::vector<int>` | Topological order used for relaxation. |
| `inf` | `T` | The unreachable-distance sentinel used by this run. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `dag_shortest_path` | `template <class T> std::optional<DagShortestPathResult<T>> dag_shortest_path(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))` | Runs DAG shortest paths from one source. | $O(N + M)$ |
| `dag_shortest_path` | `template <class T> std::optional<DagShortestPathResult<T>> dag_shortest_path(const Graph<T>& g, const std::vector<int>& sources, T inf = std::numeric_limits<T>::max() / T(4))` | Runs multi-source DAG shortest paths. | $O(N + M)$ |

## Example

```cpp
#include "graph/dag_shortest_path.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(5);
    g.add_directed_edge(0, 1, 2);
    g.add_directed_edge(0, 2, 5);
    g.add_directed_edge(1, 2, -4);
    g.add_directed_edge(2, 3, 3);
    g.add_directed_edge(3, 4, 1);

    auto res = m1une::graph::dag_shortest_path(g, 0);
    if (!res) return 0;

    std::cout << res->dist[4] << "\n";  // 2
}
```
