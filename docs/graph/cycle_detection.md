---
title: Cycle Detection
documentation_of: ../../graph/cycle_detection.hpp
---

## Overview

Cycle detection finds one cycle, if the graph contains any. A cycle is returned
as both vertices and edge ids, which is convenient for problems that ask you to
output the actual cycle.

There are separate functions for directed and undirected graphs because the DFS
rules are different:

* in a directed graph, an edge to a currently active DFS vertex forms a cycle;
* in an undirected graph, the DFS must ignore only the exact edge used to enter
  the current vertex.

## How to Use It

Use `find_directed_cycle(g)` for graphs built with `add_directed_edge`. Use
`find_undirected_cycle(g)` for graphs built with `add_edge`.

The result type is `Cycle`.

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Cycle vertices, with the first vertex repeated at the end. Empty if no cycle exists. |
| `edge_ids` | `std::vector<int>` | Edge ids used along the cycle. Its size is `vertices.size() - 1` when non-empty. |
| `empty` | `bool empty() const` | Returns whether no cycle was found. |

The returned cycle is not guaranteed to be the shortest one; it is simply the
first cycle found by the DFS.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `find_directed_cycle` | `template <class T> Cycle find_directed_cycle(const Graph<T>& g)` | Finds a directed cycle. | $O(N+M)$ |
| `find_undirected_cycle` | `template <class T> Cycle find_undirected_cycle(const Graph<T>& g)` | Finds an undirected cycle. | $O(N+M)$ |

## Example

```cpp
#include "graph/cycle_detection.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 0);

    auto cycle = m1une::graph::find_directed_cycle(g);
    if (!cycle.empty()) {
        for (int v : cycle.vertices) std::cout << v << " ";
        std::cout << "\n";
    }
}
```
