---
title: Centroid Decomposition
documentation_of: ../../tree/centroid_decomposition.hpp
---

## Overview

`m1une::tree::CentroidDecomposition<T>` builds the centroid tree of an
undirected tree. It also supports forests; each connected component contributes
one centroid-tree root.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive edges are ignored.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `n` | `int` | Number of vertices in the source graph. |
| `parent` | `std::vector<int>` | Parent in the centroid tree, or `-1` for a centroid root. |
| `depth` | `std::vector<int>` | Depth in the centroid tree. |
| `order` | `std::vector<int>` | Centroids in decomposition order. |
| `roots` | `std::vector<int>` | Centroid roots, one per connected component. |
| `children` | `std::vector<std::vector<int>>` | Children in the centroid tree. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `CentroidDecomposition(g)` | Builds the centroid decomposition. | $O(N \log N)$ |
| `void build(g)` | Rebuilds the decomposition. | $O(N \log N)$ |
| `int size()` | Returns `n`. | $O(1)$ |
| `bool empty()` | Returns whether `n == 0`. | $O(1)$ |
| `int root()` | Returns the first centroid root, or `-1`. | $O(1)$ |

## How to Use It in Problems

Centroid decomposition is useful when updates or queries are about distances to
many vertices on the original tree.

Typical examples:

* Turn a vertex on/off and query the nearest active vertex.
* Count active vertices within distance `K`.
* Add a value to one vertex and query a distance-dependent aggregate.
* Count pairs of vertices whose distance satisfies a condition.

The key idea is that every original vertex has only $O(\log N)$ ancestors in
the centroid tree. For a vertex `v`, climb:

```cpp
for (int c = v; c != -1; c = cd.parent[c]) {
    // c is a centroid ancestor of v, including v if v became a centroid.
}
```

If a query at `v` can be answered by combining information stored at each
centroid ancestor `c`, then each operation becomes $O(\log N)$ or
$O(\log^2 N)$ depending on how distances are obtained.

For repeated operations, precompute the centroid ancestors and their original
tree distances:

```cpp
m1une::tree::RootedTree<int> tree(g, 0);
m1une::tree::CentroidDecomposition<int> cd(g);

std::vector<std::vector<std::pair<int, int>>> centroid_path(n);
for (int v = 0; v < n; v++) {
    for (int c = v; c != -1; c = cd.parent[c]) {
        centroid_path[v].push_back({c, tree.dist_edges(v, c)});
    }
}
```

Now `centroid_path[v]` contains all relevant centroids for `v`, with distances
measured on the original tree.

## Dynamic Nearest Active Vertex

This is the most common centroid decomposition pattern.

Maintain `best[c]`: the minimum original-tree distance from centroid `c` to any
active vertex.

Activating a vertex `v` updates all centroid ancestors of `v`:

```cpp
const int INF = 1 << 30;
std::vector<int> best(n, INF);

auto activate = [&](int v) {
    for (auto [c, d] : centroid_path[v]) {
        best[c] = std::min(best[c], d);
    }
};
```

To query the nearest active vertex to `v`, try every centroid ancestor `c`.
Any active vertex `x` is represented at the first centroid that separates the
path between `v` and `x`, so checking all centroid ancestors is enough.

```cpp
auto query = [&](int v) {
    int ans = INF;
    for (auto [c, d] : centroid_path[v]) {
        ans = std::min(ans, best[c] + d);
    }
    return ans == INF ? -1 : ans;
};
```

Each `activate` and `query` is $O(\log N)$ after the preprocessing above.

For toggling vertices off, `best[c]` is not enough because the removed vertex may
have been the minimum. Use a `std::multiset<int>` for each centroid instead:

```cpp
std::vector<std::multiset<int>> distances(n);
std::vector<char> active(n, false);

auto activate = [&](int v) {
    if (active[v]) return;
    active[v] = true;
    for (auto [c, d] : centroid_path[v]) distances[c].insert(d);
};

auto deactivate = [&](int v) {
    if (!active[v]) return;
    active[v] = false;
    for (auto [c, d] : centroid_path[v]) {
        auto it = distances[c].find(d);
        distances[c].erase(it);
    }
};

auto query = [&](int v) {
    int ans = INF;
    for (auto [c, d] : centroid_path[v]) {
        if (!distances[c].empty()) ans = std::min(ans, d + *distances[c].begin());
    }
    return ans == INF ? -1 : ans;
};
```

This gives $O(\log^2 N)$ updates because each multiset operation costs
$O(\log N)$, and $O(\log N)$ queries.

## Counting Vertices Within Distance K

For queries like "how many active vertices are within distance `K` from `v`",
store distances at each centroid in sorted containers.

The usual static version keeps:

* `all[c]`: distances from centroid `c` to every active vertex whose
  `centroid_path` contains `c`.
* `sub[child]`: distances from `cd.parent[child]` to active vertices that lie in
  that centroid-child side.

When inserting an active vertex `x`, climb its centroid ancestors while
remembering the previous lower centroid:

```cpp
int prev = -1;
for (auto [c, d] : centroid_path[x]) {
    all[c].push_back(d);
    if (prev != -1) sub[prev].push_back(d);
    prev = c;
}
```

After sorting these vectors, query from `v` by climbing the same way. Add the
count from `all[c]` with distance at most `K - dist(v, c)`, then subtract the
count from the lower centroid side that also contains `v`.

This inclusion-exclusion pattern is the main trick for centroid decomposition
counting problems.

## Example

```cpp
#include "graph/graph.hpp"
#include "tree/centroid_decomposition.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);

    m1une::tree::CentroidDecomposition cd(g);
    std::cout << cd.root() << "\n";
}
```
