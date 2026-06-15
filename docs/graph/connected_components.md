---
title: Connected Components
documentation_of: ../../graph/connected_components.hpp
---

## Overview

Connected components with edge direction ignored. For directed graphs, this is
the weakly connected component decomposition. For strongly connected components,
use `strongly_connected_components`.

Two vertices are in the same connected component if there is a path between
them after ignoring edge directions. Internally this function uses DSU, merging
the endpoints of every logical edge.

Use this when you need to split a graph into independent pieces, count
components, check ordinary connectivity, or process each connected block
separately.

## How to Use It

Call `connected_components(g)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `count` | `int` | Number of connected components. |
| `comp` | `std::vector<int>` | `comp[v]` is the component id of vertex `v`. |
| `groups` | `std::vector<std::vector<int>>` | `groups[c]` is the list of vertices in component `c`. |
| `same` | `bool same(int u, int v) const` | Returns whether `u` and `v` are in the same component. |

For undirected graphs, build with `add_edge`. For directed graphs, remember that
the decomposition is weak connectivity; reachability direction is ignored.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `connected_components` | `template <class T> ConnectedComponents connected_components(const Graph<T>& g)` | Returns component ids and groups. | $O(N+M)$ |

## Example

```cpp
#include "graph/connected_components.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_edge(0, 1);
    g.add_edge(2, 3);

    auto cc = m1une::graph::connected_components(g);
    std::cout << cc.count << "\n";      // 3
    std::cout << cc.same(0, 1) << "\n"; // 1
    std::cout << cc.same(0, 2) << "\n"; // 0
}
```
