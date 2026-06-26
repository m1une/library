---
title: DSU on Tree
documentation_of: ../../tree/dsu_on_tree.hpp
---

## Overview

`DsuOnTree<T>` implements the small-to-large subtree technique also known as
sack. It answers one query for every rooted subtree while maintaining a
user-defined data structure.

For each vertex, light-child data is discarded after processing, while the
largest child's data is kept and reused. If inserting and removing one vertex
cost $O(F)$, all callbacks together take $O(N\log N\cdot F)$ time.

The implementation uses an explicit action stack rather than recursion, so it
is safe on a path-shaped tree with many vertices.

## Complexity Notation

* `N` is the number of vertices.
* `F` is the cost of one user callback.

## Construction

```cpp
DsuOnTree(const Graph<T>& graph, int root = 0);
void build(const Graph<T>& graph, int root = 0);
```

The graph must be a connected undirected tree built with `add_edge`. Inactive
edges are ignored. The chosen root determines every queried subtree.

Construction takes $O(N)$ time and memory.

## Methods and Metadata

The object exposes:

| Member | Description |
| --- | --- |
| `n`, `root` | Number of vertices and chosen root. |
| `parent`, `parent_edge`, `depth` | Rooted-tree metadata. |
| `subtree_size` | Number of vertices in each subtree. |
| `heavy_child` | Largest child, or `-1` for a leaf. |
| `children` | Children in the rooted tree. |
| `tin`, `tout`, `order` | Preorder Euler intervals; subtree `v` is `order[tin[v]..tout[v])`. |

`size()`, `empty()`, and `subtree_range(v)` provide the corresponding basic
queries.

## Running the Algorithm

```cpp
dsu.run(add, remove, answer);
```

The callbacks receive a vertex index:

* `add(v)` inserts vertex `v` into the maintained state.
* `remove(v)` erases vertex `v`.
* `answer(v)` is called when the state contains exactly the vertices in the
  subtree of `v`.

The structure may call `add` and `remove` for the same vertex several times.
They must therefore be mutually inverse operations. After `run` finishes, the
state contains the whole tree because the root's sack is retained.

## Example

This computes the number of distinct colors in every subtree:

```cpp
#include "graph/graph.hpp"
#include "tree/dsu_on_tree.hpp"

#include <vector>

int main() {
    m1une::graph::Graph<int> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);

    std::vector<int> color = {0, 1, 0, 2};
    std::vector<int> frequency(3);
    std::vector<int> answer(4);
    int distinct = 0;

    m1une::tree::DsuOnTree dsu(graph, 0);
    dsu.run(
        [&](int vertex) {
            if (frequency[color[vertex]]++ == 0) distinct++;
        },
        [&](int vertex) {
            if (--frequency[color[vertex]] == 0) distinct--;
        },
        [&](int vertex) {
            answer[vertex] = distinct;
        }
    );
}
```
