---
title: Tree Diameter
documentation_of: ../../tree/diameter.hpp
---

## Overview

`tree_diameter(g)` returns a longest path in an undirected tree. It also works
on a forest and returns the longest diameter among its connected components.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

For weighted trees, edge costs should be non-negative.

## Result

`TreeDiameter<T>` contains:

| Member | Description |
| --- | --- |
| `cost` | Sum of edge costs on the diameter path. |
| `edge_count` | Number of edges on the restored path. |
| `from`, `to` | Endpoints of the path, or `-1` for an empty graph. |
| `vertices` | Vertices on the path from `from` to `to`. |
| `edge_ids` | Edge ids on the path from `from` to `to`. |
| `empty()` | Returns whether no path vertices exist. |

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `tree_diameter(g)` | Finds a diameter path. | $O(N)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/diameter.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(4);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 2, 3);
    g.add_edge(1, 3, 4);

    auto diameter = m1une::tree::tree_diameter(g);
    std::cout << diameter.cost << "\n"; // 7
}
```
