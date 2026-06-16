---
title: Min Cost Flow
documentation_of: ../../flow/min_cost_flow.hpp
---

## Overview

`MinCostFlow<Cap, Cost>` sends flow from a source `s` to a sink `t` while
minimizing total cost. Each edge has a capacity and a cost per unit of flow.

This implementation uses the successive shortest augmenting path method with
potentials. It first computes initial potentials with Bellman-Ford, so negative
edge costs are allowed as long as there is no reachable negative-cost cycle
with residual capacity.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap, cost)` can
send flow only from `from` to `to`. For an undirected capacity, add both
directions with the desired costs.

The graph is stateful. Running `flow` or `slope` changes residual capacities and
stores the chosen flow. Use `get_edge` or `edges` afterward to inspect the
result.

## How to Use It

Create `MinCostFlow<Cap, Cost> mcf(n)`, add directed edges with capacity and
cost, and call `mcf.flow(s, t, flow_limit)`.

The returned pair is `{sent_flow, minimum_cost}`. If the requested
`flow_limit` cannot be fully sent, `sent_flow` will be smaller.

Use `slope(s, t, flow_limit)` when you need the minimum cost for every
breakpoint of the amount of flow. The returned vector starts with `{0, 0}` and
then adds one entry after each augmentation.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |
| `cost` | `Cost` | Cost per unit of flow on this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MinCostFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap cap, Cost cost)` | Adds a directed edge and returns its edge id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t)` | Sends as much flow as possible with minimum cost. | $O(NM + FM\log N)$ |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` flow with minimum cost. | $O(NM + FM\log N)$ |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t)` | Returns flow-cost breakpoints while sending as much as possible. | $O(NM + FM\log N)$ |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)` | Returns flow-cost breakpoints up to `flow_limit`. | $O(NM + FM\log N)$ |

Here, `F` is the number of augmentations. The first term initializes potentials
with Bellman-Ford.

## Notes

Costs may be negative, but the residual graph must not contain a reachable
negative-cost cycle. If such a cycle exists, the minimum cost is not
well-defined.

Calling `flow` or `slope` a second time continues from the current residual
state and sends additional flow.

## Example

```cpp
#include "flow/min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto [flow, cost] = mcf.flow(0, 3, 2);
    std::cout << flow << " " << cost << "\n";  // 2 5
}
```
