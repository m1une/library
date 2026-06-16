---
title: Centroid Decomposition
documentation_of: ../../tree/centroid_decomposition.hpp
---

## Overview

`m1une::tree::CentroidDecomposition<T>` builds the centroid tree of an
undirected tree. It also supports forests; each connected component contributes
one centroid-tree root.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `n` | `int` | Number of vertices in the source graph. |
| `parent` | `std::vector<int>` | Parent in the centroid tree, or `-1` for a centroid root. |
| `depth` | `std::vector<int>` | Depth in the centroid tree. |
| `order` | `std::vector<int>` | Centroids in decomposition order. |
| `roots` | `std::vector<int>` | Centroid roots, one per connected component. |
| `children` | `std::vector<std::vector<int>>` | Children in the centroid tree. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `CentroidDecomposition(g)` | Builds the centroid decomposition. | $O(N \log N)$ |
| `void build(g)` | Rebuilds the decomposition. | $O(N \log N)$ |
| `int size()` | Returns `n`. | $O(1)$ |
| `bool empty()` | Returns whether `n == 0`. | $O(1)$ |
| `int root()` | Returns the first centroid root, or `-1`. | $O(1)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/centroid_decomposition.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);

    m1une::tree::CentroidDecomposition cd(g);
    std::cout << cd.root() << "\n";
}
```
