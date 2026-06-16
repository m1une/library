---
title: Tree
documentation_of: ../../tree/tree.hpp
---

## Overview

`tree/tree.hpp` is a small tree bundle containing the core rooted-tree helper
and diameter routine.

For the full tree toolbox, include `tree/all.hpp`.

## Included Headers

| Header | Contents |
| --- | --- |
| `tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `tree/diameter.hpp` | Weighted tree/forest diameter path. |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/tree.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    m1une::tree::RootedTree tree(g, 0);
    std::cout << tree.lca(0, 2) << "\n";
}
```
