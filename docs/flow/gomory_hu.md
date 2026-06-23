---
title: Gomory-Hu Tree
documentation_of: ../../flow/gomory_hu.hpp
---

## Overview

`GomoryHu<Cap>` builds a cut-equivalent tree of an undirected capacitated graph.
For every two distinct vertices `u` and `v`, their minimum-cut value in the
original graph equals the minimum edge capacity on the tree path from `u` to
`v`.

The implementation runs highest-label push-relabel maximum flow `N - 1` times.
Global relabeling periodically restores exact sink distances, and the gap
heuristic skips dead height ranges. The residual graph is allocated once,
undirected edges use a single pair of residual arcs, and each run resets
capacities in place. Parallel edges are coalesced before the flow runs. This is
particularly fast on dense graphs. After construction, binary lifting answers
pairwise minimum-cut queries in `O(log N)`.

Parallel edges, zero-capacity edges, self-loops, and disconnected graphs are
allowed. A disconnected pair has minimum-cut value zero.

## How to Use It

Create `GomoryHu<Cap> gh(n)`, add each undirected edge once with
`gh.add_edge(u, v, cap)`, and call `gh.build()`.

After building:

- `gh.tree_edges()` returns the `N - 1` edges of the cut tree.
- `gh.min_cut(u, v)` returns the minimum-cut value for distinct vertices.
- `gh.parent()` and `gh.cut_values()` expose the rooted tree representation.
  For `v > 0`, the edge from `v` to `parent()[v]` has capacity
  `cut_values()[v]`. The root is vertex zero.

Adding another edge invalidates the built tree; call `build()` again before
querying it.

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `GomoryHu()` | Creates an empty graph. | `O(1)` |
| Constructor | `explicit GomoryHu(int n)` | Creates a graph with `n` vertices. | `O(1)` |
| `size` | `int size() const` | Returns the number of vertices. | `O(1)` |
| `edge_count` | `int edge_count() const` | Returns the number of added undirected edges. | `O(1)` |
| `add_edge` | `int add_edge(int u, int v, Cap cap)` | Adds an undirected edge and returns its id. | Amortized `O(1)` |
| `build` | `void build()` | Builds the Gomory-Hu tree and query table. | `N - 1` maximum-flow runs plus `O(N log N)` |
| `tree_edges` | `const std::vector<Edge>& tree_edges() const` | Returns cut-tree edges `{u, v, cap}`. | `O(1)` |
| `parent` | `const std::vector<int>& parent() const` | Returns rooted cut-tree parents. | `O(1)` |
| `cut_values` | `const std::vector<Cap>& cut_values() const` | Returns capacities of edges to parents. | `O(1)` |
| `min_cut` | `Cap min_cut(int u, int v) const` | Returns the pairwise minimum-cut value. | `O(log N)` |

The maximum-flow phase uses highest-label push-relabel with a general
`O(N^2 M)` bound per run. Its global relabel and gap heuristics are intended to
make it substantially faster in practice than a plain Dinic-based Gomory-Hu
implementation.

All capacities and intermediate sums must fit in `Cap`. Signed integer types
such as `long long` are recommended.

## Example

```cpp
#include "flow/gomory_hu.hpp"
#include <iostream>

int main() {
    m1une::flow::GomoryHu<long long> gh(4);
    gh.add_edge(0, 1, 3);
    gh.add_edge(1, 2, 2);
    gh.add_edge(0, 2, 1);
    gh.add_edge(2, 3, 4);
    gh.build();

    std::cout << gh.min_cut(0, 2) << '\n';  // 3
    std::cout << gh.min_cut(0, 3) << '\n';  // 3

    for (const auto& edge : gh.tree_edges()) {
        std::cout << edge.u << ' ' << edge.v << ' ' << edge.cap << '\n';
    }
}
```
