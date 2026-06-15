---
title: Maximum Clique, Independent Set, and Vertex Cover
documentation_of: ../../graph/maximum_clique.hpp
---

## Overview

This header solves three exact NP-hard problems on general undirected graphs:

* maximum clique;
* maximum independent set;
* minimum vertex cover.

A clique is a vertex set where every pair of vertices has an edge. An
independent set is a vertex set where no pair of vertices has an edge.
A vertex cover is a vertex set that touches every edge.

These problems are still exponential in the worst case. The implementation is
not a naive `2^N` subset scan: it uses a branching maximum independent set
solver. Maximum clique is computed as maximum independent set in the complement
graph.

## Graph Orientation

Direction is ignored. Every active edge of `Graph<T>` is treated as an
undirected edge between its endpoints. Self-loops are ignored because they do
not help a clique or an independent set.

## How It Works

The core solver is for maximum independent set.

If every remaining vertex has degree at most `2`, each connected component is a
path, a cycle, or an isolated vertex. Those components are solved directly by
dynamic programming.

Otherwise, let `v` be a maximum-degree vertex. Since the maximum degree is at
least `3`, the solver branches into these two cases:

* do not use `v`, so only `v` is removed;
* use `v`, so `v` and all its neighbors are removed.

The second branch removes at least `4` vertices.

For maximum clique, the solver builds the complement graph: two vertices are
connected in the complement exactly when they are not connected in the original
graph. An independent set in the complement is a clique in the original graph.

For minimum vertex cover, the solver uses the fact that a set `C` is a vertex
cover exactly when its complement `V - C` is an independent set. Therefore, the
minimum vertex cover is the complement of a maximum independent set.

## Complexity Note

Let `N` be the number of vertices. This implementation is exact and has
exponential worst-case complexity. The branching step gives the recurrence

```cpp
T(N) <= T(N - 1) + T(N - 4)
```

The positive root of `x^4 = x^3 + 1` is about `1.381`, so the search tree is
bounded by `O(1.381^N)`. With the polynomial work in each node, the usual bound
for this branching algorithm is written as `O(1.381^N * N)` when adjacency
bookkeeping is implemented linearly.

The implementation follows that branching algorithm. It stores adjacency lists
and copies the active-vertex set during recursion, so the simple header
implementation may have a slightly larger polynomial constant than a
hand-tuned contest implementation with incremental degree bookkeeping, but the
exponential part is the `1.381^N` branching bound.

## Result Types

`MaximumCliqueResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum clique. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

`MaximumIndependentSetResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum independent set. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

`MinimumVertexCoverResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one minimum vertex cover. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

Returned vertices are sorted in increasing order.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `maximum_clique` | `template <class T> MaximumCliqueResult maximum_clique(const Graph<T>& g)` | Returns one maximum clique. | `O(1.381^N * N)` branching bound |
| `maximum_clique_size` | `template <class T> int maximum_clique_size(const Graph<T>& g)` | Returns the size of a maximum clique. | `O(1.381^N * N)` branching bound |
| `maximum_independent_set` | `template <class T> MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g)` | Returns one maximum independent set. | `O(1.381^N * N)` branching bound |
| `maximum_independent_set_size` | `template <class T> int maximum_independent_set_size(const Graph<T>& g)` | Returns the size of a maximum independent set. | `O(1.381^N * N)` branching bound |
| `minimum_vertex_cover` | `template <class T> MinimumVertexCoverResult minimum_vertex_cover(const Graph<T>& g)` | Returns one minimum vertex cover. | `O(1.381^N * N)` branching bound |
| `minimum_vertex_cover_size` | `template <class T> int minimum_vertex_cover_size(const Graph<T>& g)` | Returns the size of a minimum vertex cover. | `O(1.381^N * N)` branching bound |
| `is_clique` | `template <class T> bool is_clique(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a clique. | $O(N+M+K^2)$ |
| `is_independent_set` | `template <class T> bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is an independent set. | $O(N+M+K^2)$ |
| `is_vertex_cover` | `template <class T> bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a vertex cover. | $O(N+M+K)$ |

Here, `K = vertices.size()`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/maximum_clique.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    auto clique = m1une::graph::maximum_clique(g);
    auto independent = m1une::graph::maximum_independent_set(g);
    auto cover = m1une::graph::minimum_vertex_cover(g);

    std::cout << clique.size() << "\n";       // 3
    std::cout << independent.size() << "\n";  // 2
    std::cout << cover.size() << "\n";        // 2
}
```
