---
title: Namori Graph Decomposition
documentation_of: ../../graph/namori.hpp
---

## Overview

`namori_decomposition(graph)` decomposes an undirected Namori graph: every
connected component must contain exactly one cycle. It restores each cycle in
order and roots every attached tree at the cycle vertex where it connects.

The algorithm repeatedly removes vertices of degree at most one. The remaining
2-core is the collection of cycles. It then traverses those cycles and grows
the attached forest outward.

Parallel edges are supported and form a cycle of length two. A self-loop forms
a cycle of length one. Inactive edges are ignored.

If any connected component is a tree or contains more than one cycle, the
function returns `std::nullopt`.

## Result

`NamoriDecomposition<T>` contains:

| Field | Meaning |
| --- | --- |
| `component_count` | Number of connected components and cycles. |
| `cycles[c]` | Cycle vertices of component `c` in cyclic order. |
| `cycle_edge_ids[c]` | Edge from `cycles[c][i]` to the next cycle vertex, wrapping around. |
| `cycle_edge_costs[c]` | Costs aligned with `cycle_edge_ids[c]`. |
| `on_cycle[v]` | Whether `v` lies on its component's cycle. |
| `component[v]` | Component and cycle id containing `v`. |
| `cycle_root[v]` | Cycle vertex at the root of `v`'s attached tree. |
| `cycle_position[v]` | Position of `cycle_root[v]` in `cycles[component[v]]`. |
| `parent[v]` | Parent toward the cycle, or `-1` for cycle vertices. |
| `parent_edge[v]` | Edge to `parent[v]`, or `-1` for cycle vertices. |
| `depth[v]` | Number of tree edges from `v` to the cycle. |
| `dist_to_cycle[v]` | Weighted distance from `v` to the cycle. |
| `children[v]` | Children directed away from the cycle. |

`same_component(u, v)` tests ordinary graph connectivity.
`same_tree(u, v)` tests whether the vertices attach to the same cycle vertex.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `namori_decomposition(graph)` | Returns the decomposition, or `nullopt` for a non-Namori component. | `O(N + M)` |
| `decompose_namori(graph)` | Alias for `namori_decomposition`. | `O(N + M)` |

The graph must be undirected and built with `Graph::add_edge`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/namori.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> graph(5);
    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(2, 0, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(3, 4, 6);

    auto decomposition = m1une::graph::namori_decomposition(graph);
    if (!decomposition) return 0;

    std::cout << decomposition->cycle_root[4] << '\n';
    std::cout << decomposition->dist_to_cycle[4] << '\n';  // 11
}
```
