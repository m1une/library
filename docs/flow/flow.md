---
title: Flow
documentation_of: ../../flow/flow.hpp
---

## Overview

`flow/flow.hpp` includes flow-network algorithms. Flow networks are directed:
an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, add two directed edges,
`u -> v` and `v -> u`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `flow/bounded_flow.hpp` | Directed flow network | Feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `flow/bounded_min_cost_flow.hpp` | Directed flow network | Minimum-cost feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `flow/max_flow.hpp` | Directed flow network | Dinic maximum flow and minimum cut. |
| `flow/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |
