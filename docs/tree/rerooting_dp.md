---
title: Rerooting DP
documentation_of: ../../tree/rerooting_dp.hpp
---

## Overview

`rerooting_dp` is a generic all-roots tree DP helper. It computes one DP value
for every possible root of an undirected tree, or for every vertex in each
component of a forest.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

## Function

```cpp
template <class T, class DP, class Merge, class AddVertex, class AddEdge>
std::vector<DP> rerooting_dp(
    const m1une::graph::Graph<T>& g,
    DP id,
    Merge merge,
    AddVertex add_vertex,
    AddEdge add_edge
);
```

The callbacks mean:

| Callback | Meaning |
| --- | --- |
| `id` | Identity DP value for `merge`. |
| `merge(a, b)` | Combines independent neighbor contributions. It should be associative. |
| `add_vertex(acc, v)` | Finalizes the merged contributions at vertex `v`. |
| `add_edge(dp, e)` | Converts a neighbor-side DP value through adjacency edge `e`. |

For an edge contribution used at vertex `v`, `e` is the adjacency edge from `v`
to that neighbor.

## Complexity

`rerooting_dp` runs in $O(N)$ callback calls on a tree.

## Example

The following computes the eccentricity of each vertex in an unweighted tree.

```cpp
#include "graph/graph.hpp"
#include "tree/rerooting_dp.hpp"
#include <algorithm>
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);

    auto ecc = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return std::max(a, b); },
        [](int acc, int) { return acc; },
        [](int dp, const auto&) { return dp + 1; }
    );

    std::cout << ecc[0] << "\n"; // 2
}
```
