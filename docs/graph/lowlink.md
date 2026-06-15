---
title: LowLink
documentation_of: ../../graph/lowlink.hpp
---

## Overview

LowLink is a DFS technique for undirected graphs. It records, for each vertex,
the earliest DFS-order vertex reachable by going down zero or more tree edges
and then using at most one back edge.

This information identifies:

* articulation points: vertices whose removal increases the number of connected
  components;
* bridges: edges whose removal increases the number of connected components.

Use it for network vulnerability problems, bridge counting, biconnected
component preprocessing, and similar undirected connectivity tasks.

## How to Use It

Build the graph with `add_edge`, not two calls to `add_directed_edge`. The
shared edge id is what lets the DFS skip exactly the tree edge it came from,
while still handling parallel edges correctly.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `ord` | `std::vector<int>` | `ord[v]` is the DFS visit order of `v`. |
| `low` | `std::vector<int>` | `low[v]` is the minimum `ord` reachable from `v`'s DFS subtree using at most one back edge. |
| `articulation` | `std::vector<int>` | Sorted list of articulation point vertices. |
| `bridges` | `std::vector<Edge<T>>` | Bridge edges as `Edge<T>` values. |
| `bridge_ids` | `std::vector<int>` | Sorted list of bridge edge ids. |

For a DFS tree edge `v -> to`, it is a bridge when
`ord[v] < low[to]`. A non-root vertex `v` is an articulation point when some
child `to` has `ord[v] <= low[to]`. A DFS root is an articulation point when it
has at least two DFS children.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `lowlink` | `template <class T> LowLinkResult<T> lowlink(const Graph<T>& g)` | Computes `ord`, `low`, `articulation`, `bridges`, and `bridge_ids`. | $O(N+M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/lowlink.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    int bridge = g.add_edge(1, 3);
    g.add_edge(2, 0);

    auto res = m1une::graph::lowlink(g);
    std::cout << res.articulation[0] << "\n";  // 1
    std::cout << (res.bridge_ids[0] == bridge) << "\n";  // 1
}
```
