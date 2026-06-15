---
title: Maximum Clique and Independent Set
documentation_of: ../../graph/maximum_clique.hpp
---

## Overview

This header solves two exact NP-hard problems on general undirected graphs:

* maximum clique;
* maximum independent set.

A clique is a vertex set where every pair of vertices has an edge. An
independent set is a vertex set where no pair of vertices has an edge.

These problems are still exponential in the worst case. The implementation is
not a naive `2^N` subset scan: it uses a bitset branch-and-bound maximum clique
solver with greedy coloring as an upper bound. The maximum independent set is
computed as a maximum clique in the complement graph.

## Graph Orientation

Direction is ignored. Every active edge of `Graph<T>` is treated as an
undirected edge between its endpoints. Self-loops are ignored because they do
not help a clique or an independent set.

## How It Works

The maximum clique solver keeps a current clique and a candidate set. At each
recursive step, it greedily colors the candidate subgraph. A clique can contain
at most one vertex from each color class, so the number of colors is an upper
bound on how much the current clique can still grow. If that upper bound cannot
beat the best answer, the branch is skipped.

Candidate sets and adjacency are stored as machine-word bitsets, so
intersection with a neighborhood is fast.

For maximum independent set, the solver builds the complement graph: two
vertices are connected in the complement exactly when they are not connected in
the original graph. A clique in the complement is an independent set in the
original graph.

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

Returned vertices are sorted in increasing order.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `maximum_clique` | `template <class T> MaximumCliqueResult maximum_clique(const Graph<T>& g)` | Returns one maximum clique. | Exponential worst case |
| `maximum_clique_size` | `template <class T> int maximum_clique_size(const Graph<T>& g)` | Returns the size of a maximum clique. | Exponential worst case |
| `maximum_independent_set` | `template <class T> MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g)` | Returns one maximum independent set. | Exponential worst case |
| `maximum_independent_set_size` | `template <class T> int maximum_independent_set_size(const Graph<T>& g)` | Returns the size of a maximum independent set. | Exponential worst case |
| `is_clique` | `template <class T> bool is_clique(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a clique. | $O(N+M+K^2)$ |
| `is_independent_set` | `template <class T> bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is an independent set. | $O(N+M+K^2)$ |

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

    std::cout << clique.size() << "\n";       // 3
    std::cout << independent.size() << "\n";  // 2
}
```
