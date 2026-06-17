---
title: Static Top Tree
documentation_of: ../../tree/static_top_tree.hpp
---

## Overview

`m1une::tree::StaticTopTree` builds a fixed binary expression tree over a rooted
tree. After preprocessing, changing one vertex payload or one edge cost only
requires recomputing the clusters on the path to the expression root.

Use it for dynamic tree DP problems where:

* The tree shape is fixed.
* Vertex payloads or edge costs change.
* After each update, you need the DP value for the whole tree rooted at `root`.

This is the online-update counterpart of many one-root tree DPs. If the tree
does not change and there are no updates, ordinary DFS DP or `rerooting_dp` is
usually simpler.

The input uses `m1une::graph::Graph<T>` and should be an undirected connected
tree built with `add_edge`. Inactive edges are ignored while building.

## Cluster Types

The structure uses two user-defined cluster types:

| Type | Meaning |
| --- | --- |
| `Path` | A vertical cluster whose top boundary is an ancestor and whose bottom boundary is a descendant on one heavy path. |
| `Point` | A collection of side subtrees attached to the same path vertex. |

The library balances and recomputes these clusters. You provide the four
operations that describe your DP.

More precisely:

* A `Path` cluster represents a connected part of the original tree that has a
  distinguished top boundary vertex and bottom boundary vertex. These two
  boundary vertices lie on one heavy path. The cluster also includes side
  subtrees that have already been attached to vertices on that path.
* A `Point` cluster represents zero or more completed child subtrees attached to
  one vertex of a heavy path. It has only one boundary: the parent-side vertex
  where those side subtrees attach.

The final value `all_prod()` is a `Path` cluster whose top boundary is `root`
and whose covered vertices are the whole tree.

## How This Implementation Builds the Tree

This implementation first roots the original tree at `root`, then chooses the
heavy child of each vertex as the child with largest subtree size. It then builds
a binary expression tree from four kinds of nodes:

| Internal node kind | Output type | Meaning |
| --- | --- | --- |
| `AddVertex` | `Path` | Make a one-vertex path cluster from a vertex payload and all raked side children. |
| `AddEdge` | `Point` | Attach a child path through one tree edge, turning it into a side contribution. |
| `Rake` | `Point` | Merge two side contributions attached to the same path vertex. |
| `Compress` | `Path` | Concatenate two adjacent path clusters along a heavy path. |

For every original vertex `v`:

1. Each light child subtree is built recursively as a `Path`.
2. That child path is converted to a side contribution with `AddEdge`.
3. All side contributions of `v` are merged with `Rake`.
4. The vertex payload and merged side contribution are converted into a one-vertex
   `Path` with `AddVertex`.

For every heavy path, these one-vertex `Path` clusters are merged from top to
bottom with `Compress`.

The `Rake` and `Compress` trees are balanced by subtree sizes. This is what
makes a single vertex or edge-cost update recompute only a logarithmic number of
clusters in typical use.

For example, if the rooted tree is:

```text
0
|- 1
|  |- 3
|  `- 4
`- 2
```

and the heavy path is `0 -> 1 -> 3`, then conceptually:

```text
Path(2) --AddEdge--> side contribution attached to 0
Path(4) --AddEdge--> side contribution attached to 1

AddVertex(0 side, values[0]) gives one-vertex Path(0)
AddVertex(1 side, values[1]) gives one-vertex Path(1)
AddVertex(3 side, values[3]) gives one-vertex Path(3)

Compress(Path(0), Path(1), edge 0-1)
Compress(result, Path(3), edge 1-3)
```

The actual expression tree may be parenthesized differently because it is
balanced, but the meaning is this top-to-bottom concatenation.

## Operations

The constructor receives:

```cpp
StaticTopTree(
    g,
    values,
    point_id,
    compress,
    rake,
    add_edge,
    add_vertex,
    root
);
```

The constructor arguments are:

| Argument | Meaning |
| --- | --- |
| `g` | The fixed tree shape. It must be an undirected connected `m1une::graph::Graph<T>` with `g.size()` vertices and `g.size() - 1` edges. |
| `values` | The initial payload of each original vertex. Its type is `std::vector<Vertex>`, it must have size `g.size()`, and `values[v]` is passed to `add_vertex(side, values[v], v)`. These payloads are returned by `get(v)` and updated by `set(v, value)`. |
| `point_id` | The identity element of the `Point` type for `rake`. It represents "no side subtrees" and is used for vertices with no light children. This is not a vertex id; it is a DP value such as `0`, `Point{0, 0}`, or any other neutral `Point` state. |
| `compress`, `rake`, `add_edge`, `add_vertex` | The four DP callbacks described below. |
| `root` | The original vertex used as the tree root. It defaults to `0`. |

`Vertex` is a user-defined payload type, independent of `Path` and `Point`.
It is the type stored in the `values` vector, not the integer id of a graph
vertex. The integer vertex id is the third argument `v` passed to
`add_vertex`.

For example:

* If each vertex has a weight, `Vertex` can be `long long` and `values[v]` is
  the weight of vertex `v`.
* If each vertex has several attributes, `Vertex` can be your own struct, such
  as `struct Vertex { int color; long long weight; };`.
* If the DP does not need any vertex payload, pass a dummy vector such as
  `std::vector<int>(g.size(), 0)` and ignore the `value` argument in
  `add_vertex`.

The three DP-related types are therefore:

| Type | Where it comes from | Role |
| --- | --- | --- |
| `Vertex` | The element type of `values` | Original per-vertex input payload. |
| `Point` | The type of `point_id` | Aggregate of side subtrees attached to one boundary vertex. |
| `Path` | The return type of `add_vertex` | Aggregate for a vertical path cluster. |

The callbacks are:

| Callback | Signature | Meaning |
| --- | --- | --- |
| `compress` | `Path compress(Path top, Path bottom, Edge e)` | Combines two vertical path clusters through the tree edge `e` from the bottom of `top` to the top of `bottom`. |
| `rake` | `Point rake(Point a, Point b)` | Combines independent side-subtree clusters attached to the same path vertex. |
| `add_edge` | `Point add_edge(Path child, Edge e)` | Converts a child path cluster into a side-subtree contribution viewed from its parent through edge `e`. |
| `add_vertex` | `Path add_vertex(Point side, Vertex value, int v)` | Adds original vertex `v` and its raked side subtrees, producing a path cluster whose top and bottom are both `v`. |

Here `Edge` is `m1une::graph::Edge<T>`. For both `compress` and `add_edge`,
`e.from` is the parent side and `e.to` is the child side in the rooted tree.

The expected algebraic behavior is:

* `rake(point_id, x) == x` and `rake(x, point_id) == x`.
* `rake` should be associative because side contributions are grouped in a
  balanced binary tree.
* `compress` should behave like path concatenation from top to bottom.
* `compress` does not need to be commutative. The first argument is always the
  upper path cluster, and the second argument is always the lower path cluster.
* `add_edge` sees a completed child `Path` and should shift it across `e.cost`
  or otherwise account for the edge from parent to child.
* `add_vertex` is where the original vertex payload is inserted.

## Designing a DP

A good way to design a static top tree DP is to write down what information is
needed at each boundary.

For `Path`, ask:

* If this cluster starts at its top boundary, what answer do I need for all
  vertices inside it?
* What extra information is needed to concatenate another path below it?

For `Point`, ask:

* If these side subtrees are attached to one parent-side vertex, what aggregate
  contribution do they make to that vertex?
* What is the empty contribution? That is `point_id`.

Then define the operations:

* `add_vertex(side, value, v)`: add vertex `v` and its payload `value` to the
  side contribution.
* `add_edge(child_path, e)`: view a completed child path from its parent through
  edge `e`.
* `rake(a, b)`: combine independent side subtrees.
* `compress(top, bottom, e)`: concatenate adjacent path clusters through edge
  `e`.

If the answer for the whole rooted tree is stored in the `Path` cluster viewed
from its top boundary, read it from `all_prod()`.

## Update Flow

`set(v, value)` updates the stored payload of one original vertex. The
corresponding `AddVertex` node is recomputed, then its parent expression node is
recomputed, and so on until the expression root.

`set_edge_cost(edge_id, cost)` updates the stored cost in the expression node
that owns that tree edge, then recomputes ancestors in the same way.

No tree topology changes happen during updates. Only cached cluster values are
recomputed.

The update cost is proportional to the height of the expression tree. The
balanced construction is intended to keep that height logarithmic for normal
tree shapes.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `StaticTopTree(g, values, point_id, compress, rake, add_edge, add_vertex, root)` | Builds the expression tree. | $O(N \log N)$ callback work |
| `int size()` | Returns the number of original vertices. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `int root()` | Returns the root used to orient the tree. | $O(1)$ |
| `int node_count()` | Returns the number of internal expression nodes. | $O(1)$ |
| `int height()` | Returns the height of the expression tree. | $O(1)$ |
| `const Vertex& get(v)` | Returns the stored vertex payload. | $O(1)$ |
| `const Vertex& operator[](v)` | Returns the stored vertex payload. | $O(1)$ |
| `void set(v, value)` | Updates the payload of vertex `v` and recomputes affected clusters. | $O(\text{height})$ |
| `void set_edge_cost(edge_id, cost)` | Updates one tree-edge cost and recomputes affected clusters. | $O(\text{height})$ |
| `const Path& all_prod()` | Returns the `Path` cluster for the whole rooted tree. | $O(1)$ |
| `const Path& query()` | Alias for `all_prod()`. | $O(1)$ |

The tree is static: adding/removing edges or changing the root requires
rebuilding.

## Example: Dynamic Vertex Sum

This example maintains the sum of all vertex values. This DP is intentionally
simple, so all four operations are easy to see.

```cpp
#include "graph/graph.hpp"
#include "tree/static_top_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    std::vector<long long> a = {10, 20, 30};

    auto stt = m1une::tree::StaticTopTree(
        g,
        a,
        0LL,
        [](long long top, long long bottom, const auto&) {
            return top + bottom;
        },
        [](long long x, long long y) {
            return x + y;
        },
        [](long long child, const auto&) {
            return child;
        },
        [](long long side, long long value, int) {
            return side + value;
        }
    );

    std::cout << stt.all_prod() << "\n"; // 60
    stt.set(1, 100);
    std::cout << stt.all_prod() << "\n"; // 140
}
```

## Example: Sum of Distances from the Root

This example maintains the sum of weighted distances from `root` to all
vertices. It supports edge-cost updates.

`Path` needs three fields:

* `count`: number of vertices in the path cluster.
* `sum`: sum of distances from the top boundary to all vertices in the cluster.
* `length`: distance from the top boundary to the bottom boundary.

`Point` only needs `count` and `sum`, because side clusters have one boundary.

The operations mean:

* `add_vertex`: the current vertex contributes one vertex at distance `0` from
  itself, so `count` increases by `1`.
* `add_edge`: a child cluster is viewed from its parent, so every distance
  inside that child cluster increases by `e.cost`.
* `rake`: side subtrees are independent, so counts and sums are added.
* `compress`: the lower path is viewed from the top path's top boundary. Every
  distance inside `bottom` increases by `top.length + e.cost`.

```cpp
struct Path {
    long long count;
    long long sum;
    long long length;
};

struct Point {
    long long count;
    long long sum;
};

auto stt = m1une::tree::StaticTopTree(
    g,
    std::vector<int>(n, 0),
    Point{0, 0},
    [](Path top, Path bottom, const auto& e) {
        long long shift = top.length + e.cost;
        return Path{
            top.count + bottom.count,
            top.sum + bottom.sum + bottom.count * shift,
            top.length + e.cost + bottom.length
        };
    },
    [](Point a, Point b) {
        return Point{a.count + b.count, a.sum + b.sum};
    },
    [](Path child, const auto& e) {
        return Point{child.count, child.sum + child.count * e.cost};
    },
    [](Point side, int, int) {
        return Path{side.count + 1, side.sum, 0};
    }
);

long long answer = stt.all_prod().sum;
```

## Notes

`StaticTopTree` computes the DP for one fixed root. It is not an all-roots
rerooting helper. For all-roots static answers, use `rerooting_dp`.

For edge values that are not stored in `Edge::cost`, store them in the child
vertex payload or in your own arrays captured by the callbacks, then call
`set(child, new_value)` when they change.
