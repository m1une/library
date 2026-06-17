---
title: Rerooting Static Top Tree
documentation_of: ../../tree/rerooting_static_top_tree.hpp
---

## Overview

`m1une::tree::RerootingStaticTopTree` is the bidirectional cluster engine used
for static-top-tree solutions to dynamic rerooting DP problems.

Compared with `StaticTopTree`, it stores each path cluster in both directions:

* `path_down`: the cluster viewed from the ancestor-side boundary toward the
  descendant-side boundary.
* `path_up`: the same cluster viewed from the descendant-side boundary toward
  the ancestor-side boundary.

This is the extra information needed when a query asks for the DP value with an
arbitrary vertex `v` as the root. After removing `v`, the remaining connected
components can be represented by `O(log N)` static-top-tree clusters. Some of
those clusters are viewed in the original rooted direction, and some are viewed
in the reverse direction. Therefore forward and backward transitions are kept
separate.

This header maintains the decomposition and the cached directional cluster
values under vertex-value and edge-cost updates. It also exposes the
`O(log N)` rerooting walk around a query vertex with
`for_each_rerooting_step(v, f)` and `rerooting_steps(v)`.

There is deliberately no universal `prod(v)` member. For many static-top-tree
applications, `Path` is not just a plain subtree DP value; it may be a
directional transformation, a small automaton, or another problem-specific
object. The library therefore supplies the ordered clusters needed to reroot at
`v`, while your DP code decides how those clusters are folded and how the final
answer is read.

## Cluster Types

The structure uses three user-facing types:

| Type | Meaning |
| --- | --- |
| `Vertex` | Stored value of one original vertex. |
| `Path` | A connected cluster with two boundary vertices on one heavy path. |
| `Point` | A collection of completed side components attached to one boundary vertex. |

A `Path` cluster has an original orientation: top boundary first, bottom
boundary second. In the rooted tree, the top boundary is closer to `root`.

For one path cluster:

* `path_down` means "view the cluster starting from the top boundary".
* `path_up` means "view the cluster starting from the bottom boundary".

A `Point` cluster has only one boundary vertex, so it does not have a down/up
pair. It is the aggregate contribution of several independent components
attached to that one boundary.

## Operations

The constructor receives:

```cpp
RerootingStaticTopTree(
    g,
    values,
    point_id,
    compress_down,
    compress_up,
    rake,
    add_edge_down,
    add_edge_up,
    add_vertex,
    root
);
```

The callbacks are:

| Callback | Signature | Meaning |
| --- | --- | --- |
| `compress_down` | `Path compress_down(Path upper, Path lower, Edge e)` | Concatenate two adjacent path clusters in the rooted direction. `e` goes from `upper`'s bottom boundary to `lower`'s top boundary. |
| `compress_up` | `Path compress_up(Path lower, Path upper, Edge e)` | Concatenate the same two clusters in reverse. `e` goes from `lower`'s top boundary to `upper`'s bottom boundary, usually `reverse_edge(original_e)`. |
| `rake` | `Point rake(Point a, Point b)` | Merge two independent point clusters attached to the same boundary vertex. |
| `add_edge_down` | `Point add_edge_down(Path child, Edge e)` | Convert a child path into a point contribution viewed from the parent side. `e.from` is the parent-side boundary and `e.to` is the path top boundary. |
| `add_edge_up` | `Point add_edge_up(Path parent_side, Edge e)` | Convert a path into a point contribution viewed from the child side. `e.from` is the child-side boundary and `e.to` is the path bottom boundary. |
| `add_vertex` | `Path add_vertex(Point side, Vertex value, int v)` | Insert original vertex `v` and its side contributions, making a one-vertex path. |

`point_id` is the identity for `rake`.

In code examples, `const auto& e` is just a generic-lambda shorthand for the
edge type `m1une::graph::Edge<T>`. You can spell it explicitly, for example
`const m1une::graph::Edge<long long>& e`, if the graph cost type is
`long long`.

The important detail is that `compress_up` and `add_edge_up` are not just
aliases for the downward functions. They receive the path states in the opposite
order and receive an edge whose direction is also opposite. If your DP stores
direction-sensitive data, such as prefix/suffix values, hashes, affine
functions, or ordered endpoint states, the backward formulas are often different
from the forward formulas.

For a symmetric DP, the code may look almost the same, but it is still safer to
write the two callbacks separately:

```cpp
auto compress_down = [](Path upper, Path lower, const auto& e) {
    // Start from upper's top boundary, traverse upper downward,
    // cross e, then traverse lower downward.
};
auto compress_up = [](Path lower, Path upper, const auto& e) {
    // Start from lower's bottom boundary, traverse lower upward,
    // cross e, then traverse upper upward.
};
```

## What Is Stored

Internally the structure is a binary expression tree. Each expression node is
one of:

| Node type | Output | Stored value |
| --- | --- | --- |
| `AddVertex` | `Path` | `path_down` and `path_up` for one original vertex plus its raked side components. |
| `AddEdge` | `Point` | A child path converted through one rooted tree edge. |
| `Rake` | `Point` | The rake of two point clusters at the same boundary. |
| `Compress` | `Path` | The concatenation of two path clusters. |

For a `Compress` node with left child `upper`, right child `lower`, and edge
`e` from `upper` to `lower`, the cached values are:

```cpp
path_down = compress_down(upper.path_down, lower.path_down, e);
path_up = compress_up(lower.path_up, upper.path_up, reverse_edge(e));
```

For an `AddEdge` node built from a rooted child edge `e`, the cached point is:

```cpp
point = add_edge_down(child.path_down, e);
```

The upward edge conversion is not cached in `AddEdge`, because the rooted build
only needs the downward side contribution. It is exposed as `add_edge_up` for
rerooting query code that peels clusters from the opposite direction.

`all_prod_down()` is the whole tree viewed from `root` toward the bottom of the
root heavy path. `all_prod_up()` is the same whole-tree cluster viewed from that
bottom boundary back toward `root`. The bottom boundary is determined by the
heavy paths chosen during construction; it is not an arbitrary query vertex.

## Rerooting Steps

For a query vertex `v`, start with the original vertex node:

```cpp
int cur = stt.vertex_node(v);
Point side = stt.local_point(v);
```

`local_point(v)` is the raked contribution of the non-heavy child components
already stored inside the `AddVertex` node of `v`. If there are no such
components, it returns `point_id()`.

Then process the step stream:

```cpp
stt.for_each_rerooting_step(v, [&](const auto& step) {
    using Step = decltype(stt)::step_type;
    if (step.type == Step::CompressLower) {
        // The current path cluster was the upper/left child.
        // step.sibling is the lower/right path cluster.
        // stt.path_down(step.sibling) is viewed from the current side.
    } else if (step.type == Step::CompressUpper) {
        // The current path cluster was the lower/right child.
        // step.sibling is the upper/left path cluster.
        // stt.path_up(step.sibling) is viewed from the current side.
    } else if (step.type == Step::AddEdge) {
        // Leaving a child path through step.edge.
        // step.edge is oriented parent -> child; reverse it when viewing upward.
    } else if (step.type == Step::RakeLeft) {
        // A point sibling before the current rake range.
    } else if (step.type == Step::RakeRight) {
        // A point sibling after the current rake range.
    } else {
        // Reached an AddVertex node. step.vertex is that original vertex.
    }
});
```

The same data can be materialized with `rerooting_steps(v)` if storing the walk
is more convenient than visiting it online.

Each step has these fields:

| Field | Meaning |
| --- | --- |
| `type` | One of `CompressLower`, `CompressUpper`, `AddEdge`, `RakeLeft`, `RakeRight`, `AddVertex`. |
| `node` | The expression-tree parent node reached by this step. |
| `sibling` | The sibling cluster for compress/rake steps, otherwise `-1`. |
| `vertex` | The original vertex for an `AddVertex` step, otherwise `-1`. |
| `edge` | The rooted tree edge for compress/add-edge steps. |

This removes the error-prone part of rerooting queries: finding the sibling
clusters and keeping their order straight. The folder you write for a problem
only needs to say what each step means for that DP.

## Public Members

| Method | Description | Complexity |
| --- | --- | --- |
| `RerootingStaticTopTree(...)` | Builds the expression tree. | `O(N log N)` callback work |
| `int size()` | Number of original vertices. | `O(1)` |
| `bool empty()` | Whether the original tree is empty. | `O(1)` |
| `int root()` | Root used to orient the static decomposition. | `O(1)` |
| `int root_node()` | Expression-tree node id of the whole-tree path cluster. | `O(1)` |
| `int node_count()` | Number of expression-tree nodes. | `O(1)` |
| `int height()` | Height of the expression tree. Updates are proportional to this. | `O(1)` |
| `const std::vector<Node>& nodes()` | All expression-tree nodes. | `O(1)` |
| `const Node& node(id)` | One expression-tree node. | `O(1)` |
| `int parent_node(id)` | Parent expression node, or `-1` at the root. | `O(1)` |
| `int vertex_node(v)` | The `AddVertex` node corresponding to original vertex `v`. | `O(1)` |
| `int local_point_node(v)` | Rake node stored inside `AddVertex(v)`, or `-1`. | `O(1)` |
| `const Point& local_point(v)` | Raked non-heavy child contribution stored at `v`, or `point_id()`. | `O(1)` |
| `const Vertex& get(v)` | Stored value of original vertex `v`. | `O(1)` |
| `void set(v, value)` | Update one vertex value and recompute ancestors. | `O(height)` |
| `void set_edge_cost(edge_id, cost)` | Update one edge cost and recompute ancestors. | `O(height)` |
| `const Path& path_down(node_id)` | Downward path value of a path-output node. | `O(1)` |
| `const Path& path_up(node_id)` | Upward path value of a path-output node. | `O(1)` |
| `const Point& point(node_id)` | Point value of a point-output node. | `O(1)` |
| `const Path& all_prod_down()` | Whole-tree downward path value. | `O(1)` |
| `const Path& all_prod_up()` | Whole-tree upward path value. | `O(1)` |
| `const Point& point_id()` | Identity point value for `rake`. | `O(1)` |
| `for_each_rerooting_step(v, f)` | Visits rerooting steps from `vertex_node(v)` to `root_node()`. | `O(height)` |
| `std::vector<RerootingStep> rerooting_steps(v)` | Returns the same rerooting steps as a vector. | `O(height)` |
| `compress_down(...)`, `compress_up(...)` | Public wrappers around the directional path callbacks. | Callback cost |
| `rake(...)` | Public wrapper around the point merge callback. | Callback cost |
| `add_edge_down(...)`, `add_edge_up(...)` | Public wrappers around the directional edge callbacks. | Callback cost |
| `add_vertex(...)` | Public wrapper around the vertex callback. | Callback cost |
| `static reverse_edge(edge)` | Returns a copy of `edge` with `from` and `to` swapped. | `O(1)` |

Calling `path_down` or `path_up` on a point-output node, or `point` on a
path-output node, is a logic error and is checked by `assert`.

## Using It In Problems

For a rerooting-style static top tree solution:

1. Define `Point` as the DP aggregate for independent neighbor components
   attached to one vertex.
2. Define `Path` as the information needed to move that aggregate through a
   chain of vertices in both directions.
3. Implement the downward operations exactly as in an ordinary static top tree.
4. Implement the upward operations with the reverse argument order and reversed
   edge direction.
5. For a query vertex `v`, initialize the query state from `local_point(v)`,
   then process `for_each_rerooting_step(v, f)`. The siblings encountered on
   this walk form the `O(log N)` clusters needed for the rerooted answer.

The final fold depends on the DP. For example, a DP that stores path clusters
as functions usually applies the collected functions to a point state; a DP
that stores endpoint states may keep separate accumulators for the parent side
and child side before the final `add_vertex`. In problems such as ABC460 G,
the folder keeps the same-color component contribution around the query vertex
and reads the component sum after applying the steps.

For the same-color component-sum DP used by ABC460 G, one convenient state is:

```cpp
struct Vertex {
    long long weight;
    int color;
};

struct Point {
    long long sum[2]; // contribution if the boundary vertex has color 0/1
};

struct Path {
    int first_color, last_color;
    long long first_sum, last_sum;
    bool connected; // whether the two boundaries are in one same-color component
};
```

`add_edge` puts `path.first_sum` into `Point::sum[path.first_color]`.
`add_vertex` returns a one-vertex path whose component sum is
`weight + side.sum[color]`. `compress_down` and `compress_up` use the same
orientation-relative formula: if the adjacent boundary colors are equal, join
the two boundary components; otherwise keep them separate.

The query folder fixes `c = color[v]`, starts from
`weight[v] + local_point(v).sum[c]`, and tracks whether that component touches
the current top and bottom boundaries while processing `CompressLower` and
`CompressUpper` steps. `AddEdge`, `RakeLeft`/`RakeRight`, and `AddVertex` steps
handle moving through a non-heavy child edge into the parent vertex. The
verification test `test_rerooting_static_top_tree_vertex_component` contains a
small end-to-end version of this pattern.

The library guarantees that the cluster values you read during that fold are
kept up to date after `set` and `set_edge_cost`.

## Example: Directional Distance Aggregates

This example stores, for a path cluster:

* `count`: number of vertices in the cluster.
* `sum`: sum of distances from the current viewing boundary.
* `length`: distance between the two path boundaries.

The downward and upward formulas have the same shape for distances, but the
argument names and edge direction are intentionally different.

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

auto compress_down = [](Path upper, Path lower, const auto& e) {
    long long shift = upper.length + e.cost;
    return Path{
        upper.count + lower.count,
        upper.sum + lower.sum + lower.count * shift,
        upper.length + e.cost + lower.length
    };
};

auto compress_up = [](Path lower, Path upper, const auto& e) {
    long long shift = lower.length + e.cost;
    return Path{
        lower.count + upper.count,
        lower.sum + upper.sum + upper.count * shift,
        lower.length + e.cost + upper.length
    };
};

auto rake = [](Point a, Point b) {
    return Point{a.count + b.count, a.sum + b.sum};
};

auto add_edge_down = [](Path child, const auto& e) {
    return Point{child.count, child.sum + child.count * e.cost};
};

auto add_edge_up = [](Path parent_side, const auto& e) {
    return Point{parent_side.count, parent_side.sum + parent_side.count * e.cost};
};

auto add_vertex = [](Point side, long long weight, int) {
    return Path{side.count + weight, side.sum, 0};
};

auto stt = m1une::tree::RerootingStaticTopTree(
    g,
    weights,
    Point{0, 0},
    compress_down,
    compress_up,
    rake,
    add_edge_down,
    add_edge_up,
    add_vertex
);
```

For this DP, `stt.all_prod_down().sum` is the sum of distances from the build
root to all weighted vertices. `stt.all_prod_up().sum` is the sum of distances
from the bottom boundary of the root heavy path to all weighted vertices.

## Notes

The input graph should be an undirected connected tree built with `add_edge`.
Inactive edges are ignored during construction.

If the tree topology or the build root changes, rebuild the structure. Vertex
values and edge costs can be updated with `set` and `set_edge_cost`.
