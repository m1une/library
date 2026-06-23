---
title: Online Dynamic Connectivity
documentation_of: ../../../ds/dynamic_connectivity/online_dynamic_connectivity.hpp
---

## Overview

`OnlineDynamicConnectivity` maintains connectivity in an undirected multigraph
while edges are inserted and erased. Every operation is processed immediately;
the complete operation sequence does not need to be known in advance.

The structure maintains a spanning forest with a link-cut tree. Non-tree edges
are stored in intrusive per-vertex lists, so insertion, deletion, and promotion
between edge classes do not allocate or perform balanced-tree operations. When
a tree edge is erased, it enumerates the smaller resulting tree and searches
its incident non-tree edges for a replacement.

Parallel edges and self-loops are supported. Edges are erased by the id returned
from `add_edge`, so parallel copies remain distinct.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `OnlineDynamicConnectivity()` | Creates an empty graph. | `O(1)` |
| `OnlineDynamicConnectivity(int n)` | Creates `n` isolated vertices. | `O(N)` |
| `int size() const` | Returns the number of vertices. | `O(1)` |
| `int edge_count() const` | Returns the number of edge ids ever created. | `O(1)` |
| `int active_edge_count() const` | Returns the number of currently active edges. | `O(1)` |
| `int component_count() const` | Returns the current number of connected components. | `O(1)` |
| `void reserve_edges(int count)` | Reserves storage for edge ids. | `O(M)` when reallocation occurs |
| `bool edge_alive(int id) const` | Returns whether edge `id` is active. | `O(1)` |
| `pair<int, int> edge_endpoints(int id) const` | Returns the endpoints of edge `id`. | `O(1)` |
| `bool connected(int u, int v)` | Returns whether `u` and `v` are connected. | Amortized `O(log N)` |
| `bool same(int u, int v)` | Alias for `connected`. | Amortized `O(log N)` |
| `int component_size(int v)` | Returns the number of vertices in `v`'s component. | Amortized `O(log N)` |
| `int add_edge(int u, int v)` | Inserts an edge and returns its id. | Amortized `O(log N)` |
| `bool erase_edge(int id)` | Erases an active edge. Returns false if it was already erased. | See below |

Deleting a non-tree edge costs logarithmic set maintenance. If a tree edge is
deleted, let `S` be the smaller resulting component and let `I` be the number
of non-tree-edge incidences touching vertices of `S`. Replacement search costs
`O(|S| + I + log N)`.

This deterministic strategy is compact and fast for typical sparse competitive
programming workloads. When all operations are known beforehand, prefer
`OfflineDynamicConnectivity`, whose deletion handling has a stronger batch
bound.

## Example

```cpp
#include "ds/dynamic_connectivity/online_dynamic_connectivity.hpp"
#include <iostream>

int main() {
    m1une::ds::OnlineDynamicConnectivity graph(4);
    int e01 = graph.add_edge(0, 1);
    int e12 = graph.add_edge(1, 2);
    int e02 = graph.add_edge(0, 2);

    std::cout << graph.connected(0, 2) << '\n';  // 1
    graph.erase_edge(e12);
    std::cout << graph.connected(0, 2) << '\n';  // 1, through e02
    graph.erase_edge(e02);
    std::cout << graph.connected(0, 2) << '\n';  // 0

    graph.erase_edge(e01);
}
```
