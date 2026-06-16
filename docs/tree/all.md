---
title: Tree All
documentation_of: ../../tree/all.hpp
---

## Overview

`tree/all.hpp` includes every tree header in this directory. The algorithms use
`m1une::graph::Graph<T>` as their input container, so they compose with the
existing graph library.

## Included Headers

| Header | Contents |
| --- | --- |
| `tree/tree.hpp` | Core rooted tree and diameter bundle. |
| `tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `tree/heavy_light_decomposition.hpp` | HLD order, path segments, subtree ranges, LCA, and jumps. |
| `tree/diameter.hpp` | Weighted tree/forest diameter path. |
| `tree/rerooting_dp.hpp` | Generic rerooting DP helper. |
| `tree/static_top_tree.hpp` | Dynamic one-root tree DP on a fixed tree using static top-tree clusters. |
| `tree/centroid_decomposition.hpp` | Centroid decomposition for trees and forests. |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    auto diameter = m1une::tree::tree_diameter(g);
    std::cout << diameter.edge_count << "\n";
}
```
