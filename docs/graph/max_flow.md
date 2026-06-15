---
title: Max Flow
documentation_of: ../../graph/max_flow.hpp
---

## Overview

`MaxFlow<Cap>` computes the maximum amount of flow that can be sent from a
source vertex `s` to a sink vertex `t` in a directed capacitated graph.

This implementation uses Dinic's algorithm. It repeatedly builds a level graph
with BFS and sends blocking flow with DFS. It is the standard choice for many
competitive programming max-flow tasks, including bipartite matching,
edge-disjoint paths, and minimum `s-t` cut problems.

The graph is stateful. Running `max_flow` changes residual capacities and
stores the resulting flow. Use `get_edge` or `edges` after running it to inspect
how much flow passed through each original edge.

## How to Use It

Create `MaxFlow<Cap> mf(n)`, add directed edges with capacities, and call
`mf.max_flow(s, t)`.

Capacities must be non-negative. If you want an undirected capacity between
`u` and `v`, add two directed edges.

You can call `max_flow(s, t, flow_limit)` when only up to `flow_limit` units are
needed.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MaxFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MaxFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap cap)` | Adds a directed edge and returns its edge id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `change_edge` | `void change_edge(int i, Cap new_cap, Cap new_flow)` | Replaces edge `i`'s capacity and current flow. | $O(1)$ |
| `max_flow` | `Cap max_flow(int s, int t)` | Sends maximum flow from `s` to `t`. | $O(N^2M)$ general |
| `max_flow` | `Cap max_flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` additional flow. | $O(N^2M)$ general |
| `min_cut` | `std::vector<bool> min_cut(int s) const` | Returns vertices reachable from `s` in the residual graph. | $O(N+M)$ |

## Minimum Cut

After running max flow, `min_cut(s)` returns the source side of a minimum
`s-t` cut. An original edge crossing from `cut[u] == true` to
`cut[v] == false` is saturated and belongs to some minimum cut boundary.

## Example

```cpp
#include "graph/max_flow.hpp"
#include <iostream>

int main() {
    m1une::graph::MaxFlow<long long> mf(4);
    mf.add_edge(0, 1, 2);
    mf.add_edge(0, 2, 1);
    mf.add_edge(1, 2, 1);
    mf.add_edge(1, 3, 1);
    mf.add_edge(2, 3, 2);

    std::cout << mf.max_flow(0, 3) << "\n";  // 3

    for (const auto& e : mf.edges()) {
        std::cout << e.from << " -> " << e.to << ": " << e.flow << "/" << e.cap << "\n";
    }
}
```
