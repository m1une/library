---
title: Offline Dynamic Connectivity
documentation_of: ../../../ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
---

## Overview

`OfflineDynamicConnectivity` records edge insertions, edge deletions, and
connectivity queries in chronological order, then answers every query together
with `solve()`.

Each edge lifetime is inserted into a segment tree over time. A rollback DSU
traverses that tree, adding exactly the edges active at each query and restoring
its previous state when leaving a segment. Segment-tree edge lists use one
compact contiguous allocation instead of one allocation per node.

Parallel edges and self-loops are supported. Every insertion returns a distinct
edge id, and deletion refers to that id.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `OfflineDynamicConnectivity()` | Creates an empty graph. | `O(1)` |
| `OfflineDynamicConnectivity(int n)` | Creates `n` vertices. | `O(1)` |
| `int size() const` | Returns the number of vertices. | `O(1)` |
| `int edge_count() const` | Returns the number of inserted edge ids. | `O(1)` |
| `int query_count() const` | Returns the number of recorded queries. | `O(1)` |
| `int operation_count() const` | Returns the number of recorded operations. | `O(1)` |
| `void reserve_edges(int count)` | Reserves storage for inserted edges. | `O(L)` when reallocation occurs |
| `void reserve_queries(int count)` | Reserves storage for connectivity queries. | `O(K)` when reallocation occurs |
| `bool edge_alive(int id) const` | Returns whether edge `id` is active at the end of the log. | `O(1)` |
| `int add_edge(int u, int v)` | Records an insertion and returns its edge id. | Amortized `O(1)` |
| `bool erase_edge(int id)` | Records deletion of an active edge. Returns false if already erased. | `O(1)` |
| `int add_query(int u, int v)` | Records a query and returns its query id. | Amortized `O(1)` |
| `vector<bool> solve() const` | Returns answers in query-id order. | `O((Q + L log Q) log N)` |

Here `Q` is the number of recorded operations and `L` is the number of inserted
edges. The segment-tree storage uses `O(Q + L log Q)` memory. The extra
`log N` factor comes from rollback DSU leaders, which use union by size without
path compression.

Calling `solve()` does not modify the recorded log, so it may be called again.
More operations can also be appended afterward and solved as a longer log.

## Example

```cpp
#include "ds/dynamic_connectivity/offline_dynamic_connectivity.hpp"
#include <iostream>

int main() {
    m1une::ds::OfflineDynamicConnectivity graph(3);
    int e01 = graph.add_edge(0, 1);
    int first = graph.add_query(0, 2);
    int e12 = graph.add_edge(1, 2);
    int second = graph.add_query(0, 2);
    graph.erase_edge(e01);
    int third = graph.add_query(0, 2);

    std::vector<bool> answer = graph.solve();
    std::cout << answer[first] << '\n';   // 0
    std::cout << answer[second] << '\n';  // 1
    std::cout << answer[third] << '\n';   // 0

    (void)e12;
}
```
