---
title: Heavy Light Decomposition
documentation_of: ../../tree/heavy_light_decomposition.hpp
---

## Overview

`m1une::tree::HeavyLightDecomposition<T>` decomposes a rooted tree into heavy
paths. It maps every vertex to a position `tin[v]` in a base array, which lets
path and subtree queries be answered by ordinary range data structures.

Use it with `ds::Segtree`, `LazySegtree`, or another range-query
structure over the HLD order.

Inactive graph edges are ignored.

## Path Segments

`path_segments(u, v, edge)` returns half-open base-array intervals covering the
path from `u` to `v`.

Each segment has:

| Field | Description |
| --- | --- |
| `l`, `r` | Half-open interval `[l, r)` in HLD order. |
| `reversed` | Whether the path direction traverses the interval from `r - 1` down to `l`. |

When `edge == false`, vertex positions are covered. When `edge == true`, edge
values are assumed to be stored at the child vertex position, so the LCA vertex
is excluded.

## Public Members

The input graph is first rooted at `root`. Then vertices are reordered into the
HLD base array. If you build a segment tree with HLD, position `tin[v]` is the
position corresponding to original vertex `v`.

For a connected tree, these arrays have size `N`, except `order`, which also
has size `N`. The graph is expected to be a tree. If the graph is disconnected,
only the component reachable from `root` gets valid HLD positions; vertices
outside that component keep `tin[v] == -1`.

| Member | Type | What is stored |
| --- | --- | --- |
| `root` | `int` | The root used to orient the tree. It is `-1` for an empty graph. |
| `parent[v]` | `int` | The parent of `v` in the rooted original tree. `parent[root] == -1`. |
| `parent_edge[v]` | `int` | The graph edge id connecting `parent[v]` to `v`. It is `-1` for the root. |
| `depth[v]` | `int` | Number of edges from `root` to `v`. |
| `dist[v]` | `T` | Sum of edge costs from `root` to `v`. For an unweighted tree, this is the same as `depth[v]` if all costs are `1`. |
| `subtree_size[v]` | `int` | Number of vertices in the rooted subtree of `v`, including `v` itself. |
| `heavy[v]` | `int` | The child of `v` with the largest subtree. This child continues the same heavy path. It is `-1` if `v` has no children. |
| `head[v]` | `int` | The top vertex of the heavy path containing `v`. If `head[v] == head[u]`, then `u` and `v` are on the same heavy path. |
| `tin[v]` | `int` | Position of original vertex `v` in the HLD base array. This is the index to use in segment trees. |
| `tout[v]` | `int` | One past the end of the rooted subtree interval of `v` in HLD order. The subtree is `[tin[v], tout[v])`. |
| `order[i]` | `int` | The original vertex stored at HLD base-array position `i`. This is the inverse of `tin`: `order[tin[v]] == v`. |

Important relationships:

* Vertex `v` is stored at base-array index `tin[v]`.
* `order[i]` converts a base-array index back to the original vertex.
* The rooted subtree of `v` occupies the contiguous interval
  `[tin[v], tout[v])`.
* If you store edge values instead of vertex values, store the edge
  `(parent[v], v)` at `tin[v]`. The root has no parent edge.
* Heavy paths are contiguous in the base array. That is why a path can be split
  into only $O(\log N)$ intervals.

For example, suppose the original tree is:

```text
0
|- 1
|  |- 3
|  `- 4
`- 2
```

If `1` is chosen as the heavy child of `0`, and `3` is chosen as the heavy child
of `1`, one possible HLD order is:

```text
index: 0  1  2  3  4
order: 0  1  3  4  2
```

Then:

```text
tin[0] = 0
tin[1] = 1
tin[3] = 2
tin[4] = 3
tin[2] = 4
head[0] = head[1] = head[3] = 0
head[4] = 4
head[2] = 2
```

The subtree of vertex `1` is vertices `{1, 3, 4}`, and it is stored
contiguously as `[tin[1], tout[1]) == [1, 4)`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `HeavyLightDecomposition(g, root)` | Builds HLD data. | $O(N)$ |
| `void build(g, root)` | Rebuilds the structure. | $O(N)$ |
| `int lca(u, v)` | Returns the lowest common ancestor. | $O(\log N)$ |
| `int dist_edges(u, v)` | Returns the number of edges on the path. | $O(\log N)$ |
| `T dist_cost(u, v)` | Returns the sum of edge costs on the path. | $O(\log N)$ |
| `int kth_ancestor(v, k)` | Returns the `k`-th ancestor, or `-1`. | $O(\log N)$ |
| `int jump(from, to, k)` | Returns the `k`-th vertex on the path, or `-1`. | $O(\log N)$ |
| `std::pair<int, int> subtree_range(v, edge)` | Returns the subtree interval. With `edge=true`, excludes `v`. | $O(1)$ |
| `std::vector<HldPathSegment> path_segments(u, v, edge)` | Returns path intervals in path order. | $O(\log N)$ intervals |
| `for_each_path(u, v, f, edge)` | Calls `f(l, r, reversed)` for each path segment. | $O(\log N)$ calls |

## Example

```cpp
#include "ds/segment_tree/segtree.hpp"
#include "graph/graph.hpp"
#include "monoid/add.hpp"
#include "tree/heavy_light_decomposition.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    m1une::tree::HeavyLightDecomposition<int> hld(g, 0);
    std::vector<long long> base(3, 1);
    m1une::ds::Segtree<m1une::monoid::Add<long long>> seg(base);

    long long sum = 0;
    hld.for_each_path(0, 2, [&](int l, int r, bool) {
        sum += seg.prod(l, r);
    });
    std::cout << sum << "\n"; // 3
}
```
