---
title: Dominator Tree
documentation_of: ../../graph/dominator_tree.hpp
---

## Overview

In a directed graph rooted at `root`, vertex `u` dominates vertex `v` when
every directed path from `root` to `v` passes through `u`.

`dominator_tree(graph, root)` computes immediate dominators with the
Lengauer-Tarjan algorithm. The immediate dominator of `v` is the closest strict
dominator of `v`; these edges form the dominator tree.

Only vertices reachable from `root` belong to the tree. Inactive edges are
ignored.

## Result

`DominatorTree` exposes:

| Member | Description |
| --- | --- |
| `root` | Start vertex used for the computation. |
| `immediate_dominator[v]` | Immediate dominator of `v`; the root dominates itself, and unreachable vertices store `-1`. |
| `children[v]` | Children of `v` in the dominator tree. |
| `dfs_order` | Reachable vertices in the original graph's DFS discovery order. |
| `tin`, `tout` | Euler intervals of the dominator tree; unreachable vertices store `-1`. |

Methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `size()` | Returns the original graph's vertex count. | $O(1)$ |
| `reachable(v)` | Returns whether `v` is reachable from the root. | $O(1)$ |
| `dominates(u, v)` | Returns whether `u` dominates `v`. | $O(1)$ |

## Complexity

The Lengauer-Tarjan algorithm runs in near-linear time,
$O((N+M)\alpha(N,M))$, and uses $O(N+M)$ memory.

The graph traversal and dominator-tree Euler traversal are iterative, avoiding
recursion-depth issues on long paths.

## Example

```cpp
#include "graph/dominator_tree.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 2);
    graph.add_directed_edge(1, 3);
    graph.add_directed_edge(2, 3);

    auto tree = m1une::graph::dominator_tree(graph, 0);
    std::cout << tree.immediate_dominator[3] << "\n"; // 0
    std::cout << tree.dominates(0, 3) << "\n";        // 1
}
```
