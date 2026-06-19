---
title: Bounded Min Cost Flow
documentation_of: ../../flow/bounded_min_cost_flow.hpp
---

## Overview

`BoundedMinCostFlow<Cap, Cost>` finds a minimum-cost feasible flow with lower
and upper bounds on each edge. It is the costed version of `BoundedFlow<Cap>`.
`BMinCostFlow<Cap, Cost>` is an alias of
`BoundedMinCostFlow<Cap, Cost>`.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`. The cost is still `flow * cost`, so a negative flow can
contribute a negative or positive value depending on `cost`.

## Graph Orientation

Directed flow network. An edge added by
`add_edge(from, to, lower, upper, cost)` has the signed direction
`from -> to`.

## How It Works

First, lower bounds are subtracted. For an edge `u -> v` with lower bound `L`,
upper bound `U`, and cost `C`, the solver sends `L` units as a fixed part and
leaves residual capacity `U - L`.

Then it handles costs. If a residual edge has negative cost, the solver starts
by saturating it, because that can only improve the cost before balance
constraints are repaired. This may make vertex balances wrong, so the remaining
problem is solved on the residual graph with a super source and super sink.
All residual costs in that repair step are non-negative.

The returned `Result::cost` is the total cost on the original edges:

```cpp
sum(edge.flow * edge.cost)
```

If the balance constraints cannot be satisfied, the solver returns
`std::nullopt`.

## How to Use It

Use `add_edge(from, to, lower, upper, cost)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `min_cost_flow()`. It returns `std::nullopt` if no feasible flow
exists.

For an exact `s-t` flow of value `F`, call `min_cost_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`, then minimizes
the total cost among feasible flows with that exact value.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected minimum-cost flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `cost` | `Cost` | Total cost `sum(flow * cost)` of the selected flow. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected minimum-cost flow. |
| `cost` | `Cost` | Cost per unit of flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedMinCostFlow()` | Creates an empty bounded min-cost-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedMinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper, Cost cost)` | Adds an edge with bounds and cost, then returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow() const` | Solves using stored balances. | $O(N \cdot M + F \cdot M \log N)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const` | Solves using explicit balances. | $O(N \cdot M + F \cdot M \log N)$ |
| `min_cost_st_flow` | `std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | $O(N \cdot M + F \cdot M \log N)$ |

Here, `F` is the number of augmentations made by the internal
`MinCostFlow<Cap, Cost>` repair step.

## Alias

| Alias | Type |
| --- | --- |
| `BMinCostFlow<Cap, Cost>` | `BoundedMinCostFlow<Cap, Cost>` |

## Example

```cpp
#include "flow/bounded_min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::BoundedMinCostFlow<long long, long long> mcf(3);
    int e0 = mcf.add_edge(0, 1, 1, 3, 2);
    int e1 = mcf.add_edge(1, 2, 1, 3, 1);
    int e2 = mcf.add_edge(0, 2, 0, 3, 10);

    auto res = mcf.min_cost_st_flow(0, 2, 3);
    if (!res) return 0;

    std::cout << res->cost << "\n";     // 9
    std::cout << res->flow(e0) << "\n"; // 3
    std::cout << res->flow(e1) << "\n"; // 3
    std::cout << res->flow(e2) << "\n"; // 0
}
```
