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

## DP Meaning

Think of the tree as being cut at an edge. A `DP` value represents one connected
side of the cut, rooted at the vertex closest to the edge.

For a vertex `v`, each neighbor `to` gives one independent contribution:

```cpp
contribution_from_to = add_edge(dp_of_side_rooted_at_to, edge_v_to);
```

Then all neighbor contributions are merged, and `v` itself is added:

```cpp
answer[v] = add_vertex(merge(all neighbor contributions), v);
```

The library computes this for every `v`. When it sends information from `v` to
one child, it merges all contributions except that child, applies
`add_vertex(..., v)`, and passes that value across the edge later. This is the
usual rerooting trick; prefix and suffix products make the "all except one"
merge fast.

Most tree DPs use a commutative `merge`, such as `+`, `max`, or `min`. The
implementation applies `merge` in adjacency-list order, so non-commutative
operations are deterministic but depend on that order.

## How to Design the Callbacks

Use this checklist:

1. Decide what `DP` means for a rooted connected piece.
2. Choose `id`, the value for an empty set of neighbor contributions.
3. Define `merge(a, b)`, which combines two independent neighbor sides.
4. Define `add_edge(dp, e)`, which changes distances or values when the piece is
   viewed from the other endpoint of edge `e`.
5. Define `add_vertex(acc, v)`, which adds the current vertex after all neighbor
   sides have been merged.

If the final answer for root `v` is "the DP of the whole tree rooted at `v`",
then it is exactly `result[v]`.

## Complexity

`rerooting_dp` runs in $O(N)$ callback calls on a tree.

## Example: Farthest Distance

The following computes the eccentricity of each vertex: the maximum number of
edges from that vertex to any other vertex.

Here `DP` is one integer:

* Meaning: maximum distance from the current root of this piece to a vertex in
  the piece.
* `id = 0`: an empty set of children contributes distance `0`.
* `merge = max`: keep the farthest side.
* `add_edge(dp, e) = dp + 1`: crossing one unweighted edge increases every
  distance by `1`.
* `add_vertex(acc, v) = acc`: the current vertex has distance `0`, so it does
  not change the maximum.

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

## Example: Sum of Distances

The following computes, for every vertex `v`, the sum of distances from `v` to
all vertices.

Use a DP state with:

* `size`: number of vertices in this piece.
* `sum`: sum of distances from the current root of this piece to all vertices in
  the piece.

When crossing an edge of cost `w`, every distance increases by `w`, so
`sum += size * w`.

```cpp
#include "graph/graph.hpp"
#include "tree/rerooting_dp.hpp"
#include <iostream>

struct DP {
    long long size;
    long long sum;
};

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 1);

    auto res = m1une::tree::rerooting_dp(
        g,
        DP{0, 0},
        [](DP a, DP b) {
            return DP{a.size + b.size, a.sum + b.sum};
        },
        [](DP acc, int) {
            return DP{acc.size + 1, acc.sum};
        },
        [](DP dp, const auto& e) {
            return DP{dp.size, dp.sum + dp.size * e.cost};
        }
    );

    std::cout << res[0].sum << "\n"; // dist(0,0)+dist(0,1)+dist(0,2)+dist(0,3) = 5
}
```

## Common Patterns

For counting vertices:

```cpp
id = 0
merge(a, b) = a + b
add_vertex(acc, v) = acc + 1
add_edge(dp, e) = dp
```

For maximum weighted distance:

```cpp
id = 0
merge(a, b) = std::max(a, b)
add_vertex(acc, v) = acc
add_edge(dp, e) = dp + e.cost
```

For DP states with several fields, `merge` usually adds or takes the best of
each field, `add_edge` shifts the state across one edge, and `add_vertex`
accounts for the current vertex.
