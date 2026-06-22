---
title: Range Edge Graph
documentation_of: ../../graph/range_edge_graph.hpp
---

## Overview

`RangeEdgeGraph<T>` compactly represents directed edges whose endpoints are
points or contiguous ranges. It supports operations such as:

- add an edge from one point to every point in a range;
- add an edge from every point in a range to one point;
- add an edge from every point in one range to every point in another range.

Adding all conceptual edges explicitly can require quadratic space.
`RangeEdgeGraph` uses two segment-tree-shaped directed graphs and auxiliary
vertices, reducing each range operation to $O(\log N)$ actual edges.

This is the “representing intervals as edges” technique used in problems such
as [AtCoder ABC414 G](https://atcoder.jp/contests/abc414/editorial/14071) and
Codeforces 786B.

The represented graph is an ordinary `Graph<T>`, so it can be passed directly
to `dijkstra`, `bellman_ford`, or other compatible graph algorithms. Edge costs
added by this class may be arbitrary values of `T`; choose a shortest-path
algorithm that supports those costs.

## Vertex IDs

The original `N` point vertices always have IDs `0, 1, ..., N - 1`.
`point_vertex(i)` returns `i`.

The constructor adds internal segment-tree vertices after the original points.
Range-to-range operations add one auxiliary vertex each. Therefore, use
`range_graph.graph().size()` rather than `range_graph.size()` when iterating
over every vertex in the expanded graph.

| Method | Meaning |
| --- | --- |
| `size()` | Number of original point vertices. |
| `point_vertex(i)` | Expanded-graph vertex representing point `i`. |
| `add_vertex()` | Adds and returns a custom auxiliary vertex. |
| `graph()` | Returns the expanded `Graph<T>`. |

## Adding Edges

All ranges are half-open: `[left, right)`.

| Method | Conceptual edges added |
| --- | --- |
| `add_point_to_point(from, to, cost)` | `from -> to` with cost `cost`. |
| `add_point_to_range(from, left, right, cost)` | `from -> v` for every `v` in `[left, right)`, each with cost `cost`. |
| `add_range_to_point(left, right, to, cost)` | `v -> to` for every `v` in `[left, right)`, each with cost `cost`. |
| `add_range_to_range(from_left, from_right, to_left, to_right, cost)` | `u -> v` for every `u` in the first range and `v` in the second range, each with cost `cost`. |

Empty ranges add no edges. `add_range_to_range` returns its auxiliary vertex,
or `-1` if either range is empty.

These methods add directed edges. To represent both directions, call the
corresponding operation twice with the ranges reversed.

## Canonical Range Nodes

Some problems need a cost that depends on the boundary of a canonical segment,
as in the ABC414 G editorial. The following methods expose the $O(\log N)$
segment-tree nodes covering a range:

| Method | Property of each returned vertex |
| --- | --- |
| `from_range_nodes(left, right)` | Every point in the node's interval can reach the vertex with cost zero. |
| `to_range_nodes(left, right)` | The vertex can reach every point in the node's interval with cost zero. |

Both return `std::vector<RangeEdgeNode>`. Each node has:

| Member | Meaning |
| --- | --- |
| `vertex` | Vertex ID in the expanded graph. |
| `left`, `right` | Half-open interval represented by that vertex. |

The returned intervals are disjoint and partition the requested range. Custom
edges can be added through `graph().add_directed_edge`.

## Construction

For each segment-tree interval, the graph has two orientations:

- On the **from side**, point edges lead upward from children to parents. Thus
  every point can reach each covering interval vertex.
- On the **to side**, edges lead downward from parents to children. Thus each
  interval vertex can reach every point it contains.

All structural edges have cost zero. A range-to-range operation creates one
auxiliary vertex, adds the requested cost while leaving the source-side cover,
and then reaches the destination-side cover with zero-cost edges.

## Complexity

Let `N` be the number of original points.

| Operation | Added vertices | Added edges | Time |
| --- | --- | --- | --- |
| Constructor | At most $2N - 2$ internal | At most $4N - 4$ | $O(N)$ |
| Point to point | 0 | 1 | Amortized $O(1)$ |
| Point to range | 0 | $O(\log N)$ | $O(\log N)$ |
| Range to point | 0 | $O(\log N)$ | $O(\log N)$ |
| Range to range | 1 | $O(\log N)$ | $O(\log N)$ |
| Either cover query | 0 | 0 | $O(\log N)$ |

After `Q` range-to-range additions, the expanded graph has $O(N + Q)$
vertices and $O(N + Q\log N)$ edges.

## Example

```cpp
#include "graph/dijkstra.hpp"
#include "graph/range_edge_graph.hpp"
#include <iostream>

int main() {
    m1une::graph::RangeEdgeGraph<long long> graph(6);

    // Every point in [0, 2) has an edge of cost 7 to every point in [3, 6).
    graph.add_range_to_range(0, 2, 3, 6, 7);

    auto result = m1une::graph::dijkstra(graph.graph(), 1);
    for (int i = 0; i < graph.size(); i++) {
        std::cout << result.dist[i] << "\n";
    }
}
```
