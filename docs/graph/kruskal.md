---
title: Kruskal
documentation_of: ../../graph/kruskal.hpp
---

## Overview

Kruskal's algorithm for a minimum spanning forest of an undirected weighted
graph.

The algorithm sorts edges by cost and adds them one by one if they connect two
different DSU components. This greedily builds a minimum-cost set of edges that
connects each connected component.

Use it when you need a minimum spanning tree (connected graph) or minimum
spanning forest (possibly disconnected graph). It is especially convenient when
the input is an edge list or when $M \log M$ is acceptable.

## Graph Orientation

Undirected only. Build the graph with `add_edge`. A directed edge does not
represent the usual MST problem.

## How to Use It

Build an undirected weighted graph with `add_edge`, then call `kruskal(g)`.
Although the function only looks at edge endpoints and costs, using
`add_directed_edge` usually does not represent a normal MST problem.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `cost` | `T` | Total cost of the selected forest. |
| `edges` | `std::vector<Edge<T>>` | Selected edges. |
| `components` | `int` | Number of connected components left after selecting edges. |
| `is_spanning_tree` | `bool is_spanning_tree(int n) const` | Returns whether the result is one spanning tree on `n` vertices. |

If the graph is disconnected, the result is a minimum spanning forest and
`components` will be greater than `1`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `kruskal` | `template <class T> MinimumSpanningForest<T> kruskal(const Graph<T>& g)` | Returns total cost, selected edges, and component count. | $O(M \log M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/kruskal.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(0, 3, 10);

    auto mst = m1une::graph::kruskal(g);
    std::cout << mst.cost << "\n";  // 6
}
```
