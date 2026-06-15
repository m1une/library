---
title: Topological Sort
documentation_of: ../../graph/topological_sort.hpp
---

## Overview

Topological sort orders the vertices of a directed acyclic graph so that every
edge goes from an earlier vertex to a later vertex. It is the standard tool for
dependency graphs, prerequisite constraints, DAG dynamic programming, and
scheduling problems.

This implementation uses Kahn's algorithm. It repeatedly takes a vertex with
indegree `0`, removes it from the graph conceptually, and decreases the
indegree of its outgoing neighbors.

If the graph has a directed cycle, no topological order exists.

## How to Use It

Build a directed graph with `add_directed_edge`. Then call
`topological_sort(g)`.

The function returns `std::optional<std::vector<int>>`.

* If it has a value, the vector is one valid topological order.
* If it is `std::nullopt`, the graph contains a directed cycle.

The order is not unique. If several vertices have indegree `0`, the queue order
decides which one appears first.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `topological_sort` | `template <class T> std::optional<std::vector<int>> topological_sort(const Graph<T>& g)` | Returns an ordering, or `std::nullopt` if a cycle exists. | $O(N+M)$ |
| `is_dag` | `template <class T> bool is_dag(const Graph<T>& g)` | Returns whether the graph is acyclic. | $O(N+M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/topological_sort.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 2);

    auto order = m1une::graph::topological_sort(g);
    if (!order) return 0;

    for (int v : *order) std::cout << v << " ";
    std::cout << "\n";
}
```
