---
title: Graph
documentation_of: ../../graph/graph.hpp
---

## Overview

`m1une::graph::Graph<T>` is an adjacency-list graph container for general
directed and undirected graphs. It is meant to be the common input format for
the graph algorithms in this directory.

The template parameter `T` is the edge-cost type. Use `Graph<>` when the graph
is unweighted; it is the same as `Graph<int>` and every omitted edge cost
defaults to `1`.

Undirected edges are stored as two adjacency entries with the same edge id, so
algorithms can distinguish logical edges from adjacency arcs.

## Graph Orientation

`Graph<T>` itself supports both directed and undirected graphs.

* `add_directed_edge(from, to, cost)` stores one directed arc.
* `add_edge(u, v, cost)` stores two arcs with one shared logical edge id.

Algorithm pages state whether they respect direction, require undirected edges,
or ignore direction.

## How to Use It

Create a graph with the number of vertices, then add edges.

* Use `add_directed_edge(from, to, cost)` for a one-way edge.
* Use `add_edge(u, v, cost)` for an undirected edge.
* Vertices are zero-indexed.
* The returned edge id is stable and shared by the two arcs of an undirected
  edge.

Most algorithms iterate over `g[v]`, where each element is an `Edge<T>` with
`from`, `to`, `cost`, and `id`.

Choose the cost type to match the algorithm. For example, use
`Graph<long long>` for shortest paths with large weights.

## Types

| Type | Description |
| --- | --- |
| `Edge<T>` | Stores `from`, `to`, `cost`, and `id`. |
| `Graph<T>` | Stores `std::vector<std::vector<Edge<T>>>`. |

## Edge Fields and Methods

| Member | Type / Signature | Description |
| --- | --- | --- |
| `from` | `int` | Source vertex of this adjacency arc. |
| `to` | `int` | Destination vertex of this adjacency arc. |
| `cost` | `T` | Edge cost. |
| `id` | `int` | Logical edge id. The two arcs of an undirected edge share one id. |
| `other` | `int other(int v) const` | Returns the other endpoint of this edge. Use it only when `v` is one endpoint. |

## Methods

| Method | Type / Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `Graph()` | Creates an empty graph. | $O(1)$ |
| Constructor | `explicit Graph(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the graph has no vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of logical edges added. | $O(1)$ |
| `add_vertex` | `int add_vertex()` | Adds one vertex and returns its index. | $O(1)$ amortized |
| `add_directed_edge` | `int add_directed_edge(int from, int to, T cost = T(1))` | Adds one directed edge and returns its id. | $O(1)$ amortized |
| `add_edge` | `int add_edge(int u, int v, T cost = T(1))` | Adds one undirected edge and returns its id. | $O(1)$ amortized |
| `operator[]` | `const std::vector<Edge<T>>& operator[](int v) const` | Returns immutable adjacency list of vertex `v`. | $O(1)$ |
| `operator[]` | `std::vector<Edge<T>>& operator[](int v)` | Returns mutable adjacency list of vertex `v`. | $O(1)$ |
| `adjacency` | `const std::vector<std::vector<Edge<T>>>& adjacency() const` | Returns immutable adjacency lists. | $O(1)$ |
| `adjacency` | `std::vector<std::vector<Edge<T>>>& adjacency()` | Returns mutable adjacency lists. | $O(1)$ |
| `edges` | `std::vector<Edge<T>> edges() const` | Returns one entry per logical edge id. | $O(N+M)$ |
| `reversed` | `Graph<T> reversed() const` | Returns the graph with all arcs reversed. | $O(N+M)$ |

## Notes

`edges()` returns each logical edge once. For an undirected edge, only one of
the two stored arcs is returned. This is useful for algorithms like Kruskal that
must not process the same undirected edge twice.

`reversed()` is mainly useful for directed graphs. It preserves edge ids and
costs while swapping every arc direction.

## Example

```cpp
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 5);
    g.add_directed_edge(1, 2, 7);

    for (const auto& e : g[0]) {
        std::cout << e.from << " -> " << e.to << " cost=" << e.cost << "\n";
    }
}
```
