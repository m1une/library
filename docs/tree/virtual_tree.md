---
title: Virtual Tree
documentation_of: ../../tree/virtual_tree.hpp
---

## Overview

`VirtualTree<T>` preprocesses a rooted weighted tree and repeatedly builds the
minimal rooted tree containing a selected set of key vertices and all LCAs
needed to connect them.

If there are `K` distinct key vertices, the result contains at most `2K - 1`
vertices. Construction takes `O(K log K)` time for sorting; LCA queries are
`O(1)` through an internal `SparseTableLca`.

This is useful for tree DP when each query mentions only a small subset of the
original vertices.

## Result Representation

`build(keys)` returns `VirtualTreeResult<T>`. Every result array is indexed by a
compressed virtual-tree index.

| Field | Meaning |
| --- | --- |
| `vertex[i]` | Original-tree vertex represented by compressed index `i`. |
| `parent[i]` | Compressed parent index, or `-1` for the virtual root. |
| `parent_edge_count[i]` | Number of original edges from `parent[i]` to `i`. |
| `parent_cost[i]` | Original weighted path cost from `parent[i]` to `i`. |
| `children[i]` | Compressed child indices. |
| `is_key[i]` | Whether this original vertex appeared in the input key set. |

Vertices are stored in original-tree preorder. Therefore every parent appears
before its children, and the root has compressed index zero for a nonempty
result.

Duplicate keys are removed. An empty key set produces an empty result.

`result.size()` and `result.edge_count()` return the compressed vertex and edge
counts. `result.root()` returns compressed index zero, while
`result.root_vertex()` returns its original-tree vertex id. Both root methods
return `-1` for an empty result.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `VirtualTree()` | Creates an uninitialized builder. | `O(1)` |
| `VirtualTree(graph, root)` | Preprocesses the original tree. | `O(N log N)` |
| `void build_lca(graph, root)` | Replaces the original tree and preprocesses it. | `O(N log N)` |
| `int original_size() const` | Returns the original number of vertices. | `O(1)` |
| `const SparseTableLca<T>& lca_data() const` | Exposes original rooted-tree metadata. | `O(1)` |
| `result_type build(keys)` | Builds a virtual tree for the selected vertices. | `O(K log K)` |

All selected vertices must belong to the component reached from the
preprocessing root.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/virtual_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<long long> graph(5);
    graph.add_edge(0, 1, 3);
    graph.add_edge(0, 2, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(1, 4, 2);

    m1une::tree::VirtualTree<long long> builder(graph, 0);
    auto tree = builder.build(std::vector<int>{2, 3, 4});

    for (int i = 0; i < tree.size(); i++) {
        std::cout << tree.vertex[i] << ' ' << tree.parent[i] << ' '
                  << tree.parent_cost[i] << '\n';
    }
}
```
