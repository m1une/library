---
title: Bellman-Ford
documentation_of: ../../graph/bellman_ford.hpp
---

## Overview

Bellman-Ford shortest paths for graphs that may contain negative edge costs.
It also marks vertices reachable from a negative cycle that is reachable from
the source set.

The algorithm relaxes every edge up to `N` times. If a distance can still be
improved on the `N`-th relaxation, that improvement must come from a negative
cycle. Every vertex reachable from such a cycle is marked as `negative`.

Use Bellman-Ford when negative edge costs are possible. If all edge costs are
non-negative, Dijkstra is much faster.

## Graph Orientation

Direction is respected. `bellman_ford` works on directed graphs as written, and
also on undirected graphs built with `add_edge`.

## How to Use It

Call `bellman_ford(g, s)` for one source, or `bellman_ford(g, sources)` for
multiple starting vertices.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<T>` | `dist[v]` is the best finite distance found from the source set, or `inf` if unreachable. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on the stored path, or `-1`. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `negative` | `std::vector<bool>` | `negative[v]` is whether `v` is reachable from a reachable negative cycle. |
| `inf` | `T` | The unreachable-distance sentinel used by this run. |
| `has_negative_cycle` | `bool` | Whether any reachable vertex is affected by a negative cycle. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached at all. |
| `affected_by_negative_cycle` | `bool affected_by_negative_cycle(int v) const` | Returns `negative[v]`. |
| `path` | `std::vector<int> path(int t) const` | Restores a path to `t`. Requires that `t` is reachable and not negative. |

If `negative[v]` is true, the shortest distance to `v` is not well-defined
because it can be made arbitrarily small.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bellman_ford` | `template <class T> BellmanFordResult<T> bellman_ford(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))` | Runs from one source. | $O(NM)$ |
| `bellman_ford` | `template <class T> BellmanFordResult<T> bellman_ford(const Graph<T>& g, const std::vector<int>& sources, T inf = std::numeric_limits<T>::max() / T(4))` | Runs from multiple sources. | $O(NM)$ |

## Example

```cpp
#include "graph/bellman_ford.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_directed_edge(0, 1, 1);
    g.add_directed_edge(1, 2, -3);
    g.add_directed_edge(2, 1, 1);
    g.add_directed_edge(2, 3, 1);

    auto res = m1une::graph::bellman_ford(g, 0);
    std::cout << res.has_negative_cycle << "\n";        // 1
    std::cout << res.affected_by_negative_cycle(3) << "\n";  // 1
}
```
