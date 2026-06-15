---
title: Warshall-Floyd
documentation_of: ../../graph/warshall_floyd.hpp
---

## Overview

Warshall-Floyd computes shortest paths between every pair of vertices. It keeps
a distance matrix and tries each vertex `k` as an intermediate point, improving
`dist[i][j]` with `dist[i][k] + dist[k][j]`.

Use it when `N` is small enough for $O(N^3)$ time and you need many shortest
path queries after preprocessing. It can handle negative edge costs, but if a
negative cycle exists, shortest distances involving that cycle are not
well-defined.

For one-source shortest paths on larger graphs, use Dijkstra or Bellman-Ford.

## How to Use It

There are two entry points:

* `warshall_floyd(g)` builds the initial matrix from a `Graph<T>`.
* `warshall_floyd(dist)` starts from a matrix you prepared yourself and runs
  the full $O(N^3)$ Floyd-Warshall transition on it.

For a custom matrix, initialize `dist[i][i] = 0`, unreachable entries to `inf`,
and direct edge costs to their minimum values.

This second overload is useful when your initial distances do not come directly
from `Graph<T>`, for example when you already have a dense matrix or want to
set some distances manually before running all-pairs shortest paths.

After running the algorithm, `dist[s][t]` is the shortest distance from `s` to
`t`, or `inf` if `t` is unreachable from `s`.

Use `has_negative_cycle(dist)` after the relaxation. It checks whether some
`dist[i][i]` became negative.

## Adding an Edge

After computing an all-pairs distance matrix, adding one edge can be applied in
$O(N^2)$.

The input matrix must already be the correct all-pairs shortest distance matrix
for the graph before adding the edge.

For a new directed edge `from -> to` with cost `cost`, every improved shortest
path has the form:

```cpp
i -> ... -> from -> to -> ... -> j
```

So the function checks:

```cpp
dist[i][j] = min(dist[i][j], dist[i][from] + cost + dist[to][j])
```

Use `warshall_floyd_add_directed_edge(dist, from, to, cost)` for a directed
edge and `warshall_floyd_add_undirected_edge(dist, u, v, cost)` for an
undirected edge. Adding a parallel edge with a smaller cost is the same
operation.

These functions modify `dist` in place and return `true` if at least one entry
changed.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `warshall_floyd` | `template <class T> std::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf = std::numeric_limits<T>::max() / T(4))` | Builds and relaxes the distance matrix from a graph. | $O(N^3)$ |
| `warshall_floyd` | `template <class T> std::vector<std::vector<T>> warshall_floyd(std::vector<std::vector<T>> dist, T inf = std::numeric_limits<T>::max() / T(4))` | Runs the full Floyd-Warshall transition on a matrix you initialized yourself. | $O(N^3)$ |
| `warshall_floyd_add_directed_edge` | `template <class T> bool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>& dist, int from, int to, T cost, T inf = std::numeric_limits<T>::max() / T(4))` | Adds one directed edge to an already-computed distance matrix. | $O(N^2)$ |
| `warshall_floyd_add_undirected_edge` | `template <class T> bool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>& dist, int u, int v, T cost, T inf = std::numeric_limits<T>::max() / T(4))` | Adds one undirected edge to an already-computed distance matrix. | $O(N^2)$ |
| `has_negative_cycle` | `template <class T> bool has_negative_cycle(const std::vector<std::vector<T>>& dist)` | Checks whether any diagonal entry is negative. | $O(N)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/warshall_floyd.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 5);
    g.add_directed_edge(1, 2, 7);
    g.add_directed_edge(0, 2, 20);

    auto dist = m1une::graph::warshall_floyd(g);
    std::cout << dist[0][2] << "\n";  // 12

    m1une::graph::warshall_floyd_add_directed_edge(dist, 0, 2, 4LL);
    std::cout << dist[0][2] << "\n";  // 4
}
```
