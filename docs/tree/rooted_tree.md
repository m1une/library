---
title: Rooted Tree
documentation_of: ../../tree/rooted_tree.hpp
---

## Overview

`m1une::tree::RootedTree<T>` preprocesses an undirected tree for rooted-tree
queries. It uses the existing `m1une::graph::Graph<T>` container, so build the
input with `add_edge`.

The structure stores parent/depth/subtree metadata, Euler-tour intervals, binary
lifting tables, LCA queries, path restoration, and weighted distances.

Inactive graph edges are ignored.

## Construction

```cpp
m1une::graph::Graph<long long> g(n);
g.add_edge(u, v, w);

m1une::tree::RootedTree<long long> tree(g, 0);
```

The graph is expected to be an undirected tree. If the graph is disconnected,
only the component reachable from the selected root is represented.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `root` | `int` | Root vertex, or `-1` for an empty tree. |
| `parent` | `std::vector<int>` | Parent vertex, or `-1` at the root. |
| `parent_edge` | `std::vector<int>` | Edge id connecting the vertex to its parent, or `-1`. |
| `depth` | `std::vector<int>` | Number of edges from the root. |
| `dist` | `std::vector<T>` | Sum of edge costs from the root. |
| `subtree_size` | `std::vector<int>` | Number of vertices in each rooted subtree. |
| `tin`, `tout` | `std::vector<int>` | Euler-tour interval `[tin[v], tout[v])` for each subtree. |
| `order` | `std::vector<int>` | Vertices in DFS preorder. |
| `up` | `std::vector<std::vector<int>>` | Binary lifting table. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `RootedTree(g, root)` | Builds rooted-tree data. | $O(N \log N)$ |
| `void build(g, root)` | Rebuilds the structure. | $O(N \log N)$ |
| `int size()` | Returns the number of vertices in the source graph. | $O(1)$ |
| `bool empty()` | Returns whether the source graph is empty. | $O(1)$ |
| `int log()` | Returns the number of binary-lifting levels. | $O(1)$ |
| `bool is_ancestor(u, v)` | Returns whether `u` is an ancestor of `v`. | $O(1)$ |
| `bool in_subtree(v, u)` | Returns whether `v` is in the subtree of `u`. | $O(1)$ |
| `int kth_ancestor(v, k)` | Returns the `k`-th ancestor of `v`, or `-1`. | $O(\log N)$ |
| `int lca(u, v)` | Returns the lowest common ancestor. | $O(\log N)$ |
| `int dist_edges(u, v)` | Returns the number of edges on the path. | $O(\log N)$ |
| `T dist_cost(u, v)` | Returns the sum of edge costs on the path. | $O(\log N)$ |
| `int jump(from, to, k)` | Returns the `k`-th vertex on the path from `from` to `to`, or `-1`. | $O(\log N)$ |
| `std::vector<int> path(u, v)` | Restores the vertices on the path from `u` to `v`. | $O(\text{path length})$ |
| `std::vector<int> path_edges(u, v)` | Restores edge ids on the path from `u` to `v`. | $O(\text{path length})$ |
| `std::pair<int, int> subtree_range(v)` | Returns `[tin[v], tout[v])`. | $O(1)$ |
| `std::vector<int> subtree_vertices(v)` | Returns vertices in the rooted subtree of `v`. | $O(\text{subtree size})$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/rooted_tree.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 2, 3);
    g.add_edge(1, 3, 4);

    m1une::tree::RootedTree<long long> tree(g, 0);
    std::cout << tree.lca(2, 3) << "\n";       // 1
    std::cout << tree.dist_cost(2, 3) << "\n"; // 7
}
```
