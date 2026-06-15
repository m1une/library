---
title: Strongly Connected Components
documentation_of: ../../graph/scc.hpp
---

## Overview

A strongly connected component is a maximal set of vertices where every vertex
can reach every other vertex in the same set. SCC decomposition compresses each
such set into one component, turning any directed graph into a DAG of
components.

Use SCC when you need to reason about mutual reachability, directed cycles,
2-SAT-style implications, or DP over the condensation graph.

This implementation is based on Tarjan's DFS lowlink method and runs in linear
time.

## How to Use It

Build a directed graph with `add_directed_edge`, then call
`strongly_connected_components(g)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `count` | `int` | Number of strongly connected components. |
| `comp` | `std::vector<int>` | `comp[v]` is the component id of vertex `v`. |
| `groups` | `std::vector<std::vector<int>>` | `groups[c]` is the list of vertices belonging to component `c`. |
| `same` | `bool same(int u, int v) const` | Returns whether `u` and `v` are in the same component. |
| `dag` | `template <class T> Graph<int> dag(const Graph<T>& g) const` | Builds the condensation DAG with duplicate component edges removed. |

Component ids are arranged in topological order of the condensation DAG: edges
between different components go from a smaller id to a larger id.

## What `dag(g)` Represents

`dag(g)` returns the condensation graph of `g`. Its vertices are SCC ids, not
original graph vertices.

Vertex `c` in the returned DAG represents `groups[c]`, the `c`-th strongly
connected component. In other words:

```cpp
v belongs to DAG vertex c  <=>  comp[v] == c
```

For example, if `groups[2] == {4, 6, 7}`, then vertex `2` of the returned DAG
represents original vertices `4`, `6`, and `7`.

An SCC is not necessarily a single simple cycle. A DAG vertex may represent a
single isolated original vertex, one directed cycle, or a larger mutually
reachable subgraph containing several cycles.

If the original graph has an edge `u -> v` and `comp[u] != comp[v]`, the
returned DAG has an edge `comp[u] -> comp[v]`. Therefore each DAG edge means
"there exists at least one original edge from some vertex in `groups[from]` to
some vertex in `groups[to]`".

Duplicate edges between the same pair of components are removed. The returned
graph has type `Graph<int>` and its edge costs are all `1`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `strongly_connected_components` | `template <class T> SccResult strongly_connected_components(const Graph<T>& g)` | Returns component ids and groups. | $O(N+M)$ |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/scc.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 0);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 3);
    g.add_directed_edge(3, 2);

    auto scc = m1une::graph::strongly_connected_components(g);
    std::cout << scc.count << "\n";       // 2
    std::cout << scc.same(0, 1) << "\n";  // 1
    std::cout << scc.same(0, 2) << "\n";  // 0

    auto dag = scc.dag(g);
    std::cout << dag.size() << "\n";      // 2
}
```
