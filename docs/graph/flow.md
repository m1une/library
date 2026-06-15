---
title: Flow
documentation_of: ../../graph/flow.hpp
---

## Overview

`graph/flow.hpp` includes flow-network algorithms. Flow networks are directed:
an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, add two directed edges,
`u -> v` and `v -> u`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/bounded_flow.hpp` | Directed flow network | Feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/bounded_min_cost_flow.hpp` | Directed flow network | Minimum-cost feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/max_flow.hpp` | Directed flow network | Dinic maximum flow and minimum cut. |
| `graph/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |
