---
title: Heavy Light Decomposition
documentation_of: ../../tree/heavy_light_decomposition.hpp
---

## Overview

`m1une::tree::HeavyLightDecomposition<T>` decomposes a rooted tree into heavy
paths. It maps every vertex to a position `tin[v]` in a base array, which lets
path and subtree queries be answered by ordinary range data structures.

Use it with `data_structure::Segtree`, `LazySegtree`, or another range-query
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

| Member | Type | Description |
| --- | --- | --- |
| `parent`, `parent_edge` | `std::vector<int>` | Rooted parent and incoming edge id. |
| `depth`, `dist` | `std::vector<int>`, `std::vector<T>` | Root depth and weighted root distance. |
| `subtree_size` | `std::vector<int>` | Rooted subtree sizes. |
| `heavy` | `std::vector<int>` | Heavy child, or `-1`. |
| `head` | `std::vector<int>` | Head vertex of the heavy path. |
| `tin`, `tout`, `order` | `std::vector<int>` | HLD order and subtree intervals. |

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
#include "data_structure/segtree.hpp"
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
    m1une::data_structure::Segtree<m1une::monoid::Add<long long>> seg(base);

    long long sum = 0;
    hld.for_each_path(0, 2, [&](int l, int r, bool) {
        sum += seg.prod(l, r);
    });
    std::cout << sum << "\n"; // 3
}
```
