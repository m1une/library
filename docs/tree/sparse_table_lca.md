---
title: Sparse Table LCA
documentation_of: ../../tree/sparse_table_lca.hpp
---

## Overview

`m1une::tree::SparseTableLca<T>` preprocesses an undirected rooted tree so that
`lca(u, v)` is answered in $O(1)$ time.

It uses the standard Euler-tour reduction:

1. Do a DFS from `root`.
2. Record a vertex every time the DFS enters a vertex or returns to a parent.
3. For each vertex `v`, store `first[v]`, its first position in this Euler tour.
4. The LCA of `u` and `v` is the minimum-depth vertex in the Euler interval
   between `first[u]` and `first[v]`.

That minimum-depth query is static RMQ, so this structure uses
`ds::SparseTable` internally.

Use this when you need many LCA queries and want $O(1)$ per query. If you also
need `kth_ancestor` or `jump`, use `RootedTree` instead.

The graph should be an undirected tree built with `add_edge`. Inactive edges are
ignored. If the graph is disconnected, only the component reachable from `root`
gets valid LCA data.

## Public Members

| Member | Type | What is stored |
| --- | --- | --- |
| `root` | `int` | The root used for the DFS, or `-1` for an empty graph. |
| `parent[v]` | `int` | Parent of `v` in the rooted tree. `parent[root] == -1`. |
| `parent_edge[v]` | `int` | Edge id connecting `parent[v]` to `v`, or `-1` at the root. |
| `depth[v]` | `int` | Number of edges from `root` to `v`. |
| `dist[v]` | `T` | Sum of edge costs from `root` to `v`. |
| `subtree_size[v]` | `int` | Number of vertices in the rooted subtree of `v`. |
| `tin[v]`, `tout[v]` | `int` | DFS preorder subtree interval `[tin[v], tout[v])`. |
| `order[i]` | `int` | Vertex at preorder index `i`. |
| `first[v]` | `int` | First position of `v` in the Euler tour used for RMQ. |
| `euler[i]` | `int` | Vertex recorded at Euler-tour position `i`. |

Do not confuse `tin[v]` and `first[v]`:

* `tin[v]` is a preorder index used for subtree intervals.
* `first[v]` is an Euler-tour index used for LCA RMQ.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SparseTableLca(g, root)` | Builds the Euler tour and sparse table. | $O(N \log N)$ |
| `void build(g, root)` | Rebuilds the structure. | $O(N \log N)$ |
| `int size()` | Returns the number of vertices in the source graph. | $O(1)$ |
| `bool empty()` | Returns whether the source graph is empty. | $O(1)$ |
| `bool is_ancestor(u, v)` | Returns whether `u` is an ancestor of `v`. | $O(1)$ |
| `bool in_subtree(v, u)` | Returns whether `v` is in the subtree of `u`. | $O(1)$ |
| `int lca(u, v)` | Returns the lowest common ancestor. | $O(1)$ |
| `int dist_edges(u, v)` | Returns the number of edges on the path. | $O(1)$ |
| `T dist_cost(u, v)` | Returns the sum of edge costs on the path. | $O(1)$ |
| `std::pair<int, int> subtree_range(v)` | Returns `[tin[v], tout[v])`. | $O(1)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/sparse_table_lca.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(5);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 3, 4);
    g.add_edge(1, 4, 5);

    m1une::tree::SparseTableLca<long long> lca(g, 0);

    std::cout << lca.lca(3, 4) << "\n";       // 1
    std::cout << lca.dist_cost(3, 2) << "\n"; // 4 + 2 + 3 = 9
}
```
