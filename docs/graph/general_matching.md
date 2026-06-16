---
title: General Matching
documentation_of: ../../graph/general_matching.hpp
---

## Overview

`GeneralMatching` finds a maximum-cardinality matching in a general undirected
graph. Unlike `BipartiteMatching`, the graph does not need to be bipartite:
odd cycles are allowed.

A matching is a set of edges where no two selected edges share a vertex.
Maximum-cardinality matching means the solver maximizes the number of selected
edges. This is unweighted matching; edge costs are not used.

The implementation uses shortest-augmenting-path phases for general graphs
(the Micali-Vazirani/Gabow framework). Each phase builds the admissible graph
for the current shortest augmenting paths, finds a maximal vertex-disjoint set
of those paths, lifts them through recorded blossom bridges, and augments all
of them together. There are $O(\sqrt N)$ phases and each phase is linear in the
active graph size.

## Graph Orientation

Undirected only. An edge added by `add_edge(from, to)` connects `from` and
`to` symmetrically.

The helper `make_general_matching(g)` accepts a `Graph<T>` and ignores edge
direction: every active edge becomes one undirected matching edge.

Self-loops are not valid matching edges.

## How to Use It

Use `GeneralMatching gm(n)` when you already have vertex ids `0..n-1`, then
add undirected edges with `add_edge(from, to)`.

Call `max_matching()` to compute the maximum matching. After that, use
`matching()`, `mate()`, or `mate_edge()` to inspect the result.

Use `minimum_edge_cover()` when you want the smallest set of edges that covers
every vertex. It starts from a maximum matching and adds one incident edge for
each uncovered vertex. If an isolated vertex exists, no edge cover exists and
the method returns `std::nullopt`.

Use `make_general_matching(g)` when your graph is already stored as `Graph<T>`.
The returned `GeneralMatchingGraph` keeps the mapping from matching edge ids
back to the original `Graph<T>` edge ids.

## Fields

`GeneralMatching::Edge` contains these fields:

| Field / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `from` | `int` | One endpoint. |
| `to` | `int` | The other endpoint. |
| `id` | `int` | Edge id returned by `add_edge`. |
| `alive` | `bool` | Whether this edge is currently usable. |
| `other` | `int other(int v) const` | Returns the opposite endpoint of `v`. |

`GeneralMatching::Pair` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | One matched endpoint. |
| `to` | `int` | The other matched endpoint. |
| `edge_id` | `int` | Edge id used by this matched pair. |

`GeneralMatchingGraph` contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `matching` | `GeneralMatching` | Matching graph using the same vertex ids as the original graph. |
| `original_edge_id` | `std::vector<int>` | `original_edge_id[e]` is the original `Graph<T>` edge id for matching edge `e`. |
| `original_edge` | `int original_edge(int edge_id) const` | Converts a matching edge id back to the original graph edge id. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `GeneralMatching()` | Creates an empty matching graph. | $O(1)$ |
| Constructor | `explicit GeneralMatching(int n)` | Creates a matching graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of registered edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to)` | Adds an undirected edge and returns its id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges(bool include_inactive = false) const` | Returns active edges, or all edges if `include_inactive` is true. | $O(M)$ |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Sets whether edge `id` is usable. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks edge `id` unusable. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks edge `id` usable again. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether edge `id` is usable. | $O(1)$ |
| `max_matching` | `int max_matching()` | Computes and stores a maximum matching. | $O(M\sqrt N)$ |
| `matching_size` | `int matching_size()` | Returns the current maximum matching size, computing it if needed. | Same as `max_matching` if not computed |
| `mate` | `std::vector<int> mate()` | Returns the matched vertex of each vertex, or `-1`. | Same as `max_matching` if not computed |
| `mate_edge` | `std::vector<int> mate_edge()` | Returns the matched edge id of each vertex, or `-1`. | Same as `max_matching` if not computed |
| `matching` | `std::vector<Pair> matching()` | Returns matched pairs and edge ids. | Same as `max_matching` if not computed |
| `minimum_edge_cover` | `std::optional<std::vector<int>> minimum_edge_cover()` | Returns edge ids of a minimum edge cover, or `std::nullopt` if an isolated vertex exists. | Same as `max_matching` if not computed |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `make_general_matching` | `template <class T> GeneralMatchingGraph make_general_matching(const Graph<T>& g)` | Builds a `GeneralMatching` from active edges of `g` and stores original edge-id mapping. | $O(N+M)$ |

## Example

```cpp
#include "graph/general_matching.hpp"
#include <iostream>

int main() {
    m1une::graph::GeneralMatching gm(6);
    gm.add_edge(0, 1);
    gm.add_edge(1, 2);
    gm.add_edge(2, 3);
    gm.add_edge(3, 4);
    gm.add_edge(4, 0);
    gm.add_edge(1, 5);

    std::cout << gm.max_matching() << "\n";  // 3
    for (auto p : gm.matching()) {
        std::cout << p.from << " " << p.to << "\n";
    }
}
```
