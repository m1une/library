---
title: Bipartite Graph
documentation_of: ../../graph/bipartite.hpp
---

## Overview

This header contains tools for bipartite graphs.

A graph is bipartite if its vertices can be colored with two colors so that
every edge connects vertices of different colors. Equivalently, the graph has
no odd-length cycle.

Use `bipartite(g)` or `is_bipartite(g)` when you have a `Graph<T>` and want to
check whether such a coloring exists.

Use `BipartiteMatching` when the two sides are already known and you want
matching-related algorithms:

* maximum bipartite matching;
* minimum vertex cover;
* maximum independent set;
* minimum edge cover.

Use `make_bipartite_matching(g)` when you have a `Graph<T>` and want to build
that matching graph from its two-coloring.

## Graph Orientation

For `bipartite(g)`, direction is ignored. Each edge is treated as an
undirected constraint between its endpoints.

For `BipartiteMatching`, the graph is represented by two index sets:

```cpp
left vertices:  0, 1, ..., left_size - 1
right vertices: 0, 1, ..., right_size - 1
```

Each edge connects one left vertex to one right vertex.

## How to Use It

Call `bipartite(g)` when you need both the yes/no answer and the colors. Call
`is_bipartite(g)` when you only need the boolean.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `is_bipartite` | `bool` | Whether a valid two-coloring exists. |
| `color` | `std::vector<int>` | `color[v]` is `0` or `1` for the assigned color, or `-1` before assignment. |
| `left_vertices` | `std::vector<int>` | Original graph vertices whose color is `0`; valid when `is_bipartite == true`. |
| `right_vertices` | `std::vector<int>` | Original graph vertices whose color is `1`; valid when `is_bipartite == true`. |
| `left_id` | `std::vector<int>` | `left_id[v]` is the index of original vertex `v` inside `left_vertices`, or `-1`. |
| `right_id` | `std::vector<int>` | `right_id[v]` is the index of original vertex `v` inside `right_vertices`, or `-1`. |

For a disconnected graph, every component is colored independently. The chosen
colors are not unique; flipping all colors in a component gives another valid
answer.

If you want to run `BipartiteMatching` on a `Graph<T>`, first call
`bipartite(g)`, then use `left_id` and `right_id` to convert original vertex
ids into side-local ids. Alternatively, call `make_bipartite_matching(g)` to
build the separated matching graph and keep mappings back to the original
vertices and edge ids.

## Bipartite Matching

`BipartiteMatching` stores a bipartite graph whose sides are already separated.
It uses Hopcroft-Karp to compute a maximum matching.

After maximum matching is known, Konig's theorem gives a minimum vertex cover:
in bipartite graphs, the size of a maximum matching equals the size of a
minimum vertex cover. The implementation finds alternating paths from
unmatched left vertices. If `Z` is the set of vertices reached by those
alternating paths, the minimum vertex cover is:

```cpp
(left vertices not in Z) + (right vertices in Z)
```

The maximum independent set is the complement of that minimum vertex cover.

The minimum edge cover starts from a maximum matching, then adds one incident
edge for every still-uncovered vertex. It exists only when every vertex has at
least one incident edge; otherwise the method returns `std::nullopt`.

## Matching Fields

`BipartiteMatching::Edge` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `left` | `int` | Left-side endpoint. |
| `right` | `int` | Right-side endpoint. |
| `id` | `int` | Edge id returned by `add_edge`. |
| `alive` | `bool` | Whether this edge is currently usable. |

`BipartiteMatching::Pair` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `left` | `int` | Matched left-side vertex. |
| `right` | `int` | Matched right-side vertex. |
| `edge_id` | `int` | Edge id used by this matched pair. |

`BipartiteVertexSet` contains these fields:

| Field / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `left` | `std::vector<int>` | Selected left-side vertices. |
| `right` | `std::vector<int>` | Selected right-side vertices. |
| `size` | `int size() const` | Returns `left.size() + right.size()`. |

`BipartiteMatchingGraph` contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `parts` | `BipartiteResult` | Two-coloring and side-local id conversion for the original graph. |
| `matching` | `BipartiteMatching` | Matching graph whose left/right ids come from `parts`. |
| `original_edge_id` | `std::vector<int>` | `original_edge_id[e]` is the original `Graph<T>` edge id for matching edge `e`. |
| `left_vertex` | `int left_vertex(int left) const` | Converts a left-side id back to the original graph vertex id. |
| `right_vertex` | `int right_vertex(int right) const` | Converts a right-side id back to the original graph vertex id. |
| `original_edge` | `int original_edge(int edge_id) const` | Converts a matching edge id back to the original graph edge id. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bipartite` | `template <class T> BipartiteResult bipartite(const Graph<T>& g)` | Returns a bipartite flag and colors. | $O(N+M)$ |
| `is_bipartite` | `template <class T> bool is_bipartite(const Graph<T>& g)` | Returns only the bipartite flag. | $O(N+M)$ |
| `make_bipartite_matching` | `template <class T> std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>& g)` | Builds a `BipartiteMatching` from a bipartite `Graph<T>`, or returns `std::nullopt`. | $O(N+M)$ |

## Matching Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BipartiteMatching()` | Creates an empty bipartite graph. | $O(1)$ |
| Constructor | `BipartiteMatching(int left_size, int right_size)` | Creates a bipartite graph with explicit side sizes. | $O(L+R)$ |
| `left_size` | `int left_size() const` | Returns the number of left-side vertices. | $O(1)$ |
| `right_size` | `int right_size() const` | Returns the number of right-side vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of registered edges. | $O(1)$ |
| `add_edge` | `int add_edge(int left, int right)` | Adds an edge and returns its edge id. | $O(1)$ amortized |
| `get_edge` | `Edge get_edge(int i) const` | Returns edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges(bool include_inactive = false) const` | Returns active edges, or all edges if `include_inactive` is true. | $O(M)$ |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Sets whether edge `id` is usable. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks edge `id` unusable. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks edge `id` usable again. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether edge `id` is usable. | $O(1)$ |
| `max_matching` | `int max_matching()` | Computes and stores a maximum matching. | $O(M\sqrt{L+R})$ |
| `matching_size` | `int matching_size()` | Returns the current maximum matching size, computing it if needed. | $O(M\sqrt{L+R})$ if not computed |
| `left_match` | `std::vector<int> left_match()` | Returns `right` matched to each left vertex, or `-1`. | $O(M\sqrt{L+R})$ if not computed |
| `right_match` | `std::vector<int> right_match()` | Returns `left` matched to each right vertex, or `-1`. | $O(M\sqrt{L+R})$ if not computed |
| `matching` | `std::vector<Pair> matching()` | Returns matched pairs and edge ids. | $O(M\sqrt{L+R})$ if not computed |
| `minimum_vertex_cover` | `BipartiteVertexSet minimum_vertex_cover()` | Returns a minimum vertex cover. | $O(M\sqrt{L+R})$ if not computed |
| `maximum_independent_set` | `BipartiteVertexSet maximum_independent_set()` | Returns a maximum independent set. | $O(M\sqrt{L+R})$ if not computed |
| `minimum_edge_cover` | `std::optional<std::vector<int>> minimum_edge_cover()` | Returns edge ids of a minimum edge cover, or `std::nullopt` if an isolated vertex exists. | $O(M\sqrt{L+R})$ if not computed |

## Example

```cpp
#include "graph/bipartite.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    auto res = m1une::graph::bipartite(g);
    std::cout << res.is_bipartite << "\n";  // 1
    std::cout << res.color[0] << " " << res.color[1] << "\n";

    auto built = m1une::graph::make_bipartite_matching(g);
    std::cout << built->matching.max_matching() << "\n";  // 2

    m1une::graph::BipartiteMatching bm(2, 2);
    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(1, 1);

    std::cout << bm.max_matching() << "\n";  // 2
    auto cover = bm.minimum_vertex_cover();
    std::cout << cover.size() << "\n";       // 2
}
```
