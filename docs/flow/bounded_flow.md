---
title: Bounded Flow
documentation_of: ../../flow/bounded_flow.hpp
---

## Overview

`BoundedFlow<Cap>` finds a feasible flow with lower and upper bounds on each
edge. It also supports `b`-flow constraints by giving each vertex a required
balance. `BFlow<Cap>` is an alias of `BoundedFlow<Cap>`.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, lower, upper)` has
the signed direction `from -> to`.

## How It Works

The library reduces bounded flow to ordinary max flow.

For an edge `u -> v` with lower bound `L` and upper bound `U`, it sends
`L` first and leaves residual capacity `U - L`. This changes the vertex
balances, then a super source and super sink are added to check whether all
remaining balance constraints can be satisfied.

## How to Use It

Use `add_edge(from, to, lower, upper)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `feasible_flow()`. It returns `std::nullopt` if no feasible flow
exists.

For an exact `s-t` flow of value `F`, call `feasible_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected feasible flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected feasible flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedFlow()` | Creates an empty bounded-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper)` | Adds an edge with bounds and returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `feasible_flow` | `std::optional<Result> feasible_flow() const` | Solves using stored balances. | Max flow |
| `feasible_flow` | `std::optional<Result> feasible_flow(const std::vector<Cap>& balance) const` | Solves using explicit balances. | Max flow |
| `feasible_st_flow` | `std::optional<Result> feasible_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | Max flow |

## Alias

| Alias | Type |
| --- | --- |
| `BFlow<Cap>` | `BoundedFlow<Cap>` |

## Example

```cpp
#include "flow/bounded_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::BoundedFlow<long long> bf(3);
    int e0 = bf.add_edge(0, 1, 1, 3);
    int e1 = bf.add_edge(0, 2, 0, 2);
    int e2 = bf.add_edge(1, 2, -1, 2);  // negative flow is allowed

    bf.add_supply(0, 3);
    bf.add_demand(2, 3);

    auto res = bf.feasible_flow();
    if (!res) return 0;

    std::cout << res->flow(e0) << "\n";
    std::cout << res->flow(e1) << "\n";
    std::cout << res->flow(e2) << "\n";
}
```
