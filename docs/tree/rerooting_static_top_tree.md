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

For low-level access, you can process the raw step stream:

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

For ordinary use, prefer `fold_rerooting(v, folder)`. It performs this dispatch
for you and passes already-oriented cluster values to the folder:

| Folder method | Called when |
| --- | --- |
| `start(v, value, local_point)` | Before processing the walk from `v`. |
| `compress_lower(path, edge)` | A lower path sibling is attached below the current path. |
| `compress_upper(path, edge)` | An upper path sibling is attached above the current path. |
| `add_edge(edge)` | The walk leaves a child path and moves toward its parent vertex. |
| `rake_left(point)` | A point sibling appears before the current rake range. |
| `rake_right(point)` | A point sibling appears after the current rake range. |
| `add_vertex(vertex, value)` | The walk reaches a parent `AddVertex` node. |
| `result()` | Returns the query answer after the walk. |

Here `compress_upper` and `add_edge` receive reversed edges, so the edge is
oriented in the direction the rerooting walk is moving.

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
| `fold_rerooting(v, folder)` | Runs the rerooting walk and calls the folder methods above. | `O(height)` |
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

## Example: ABC460 G - Vertex Flip Query

ABC460 G asks for dynamic updates on a colored, weighted tree:

* flip one vertex color,
* add to one vertex weight,
* for a vertex `v`, output the sum of weights in the connected component of
  `v` after deleting all vertices whose color differs from `color[v]`.

This can be seen as a rerooting DP query. If the tree is rooted at `v`, the
answer is the contribution of all neighbor-side components that can connect to
`v` through vertices of the same color.

One convenient state is:

```cpp
struct Vertex {
    long long weight;
    int color;
};

struct Point {
    long long sum[2];
};

struct Path {
    int first_color, last_color;
    long long first_sum, last_sum;
    bool connected;
};
```

The meaning is:

| State | Meaning |
| --- | --- |
| `Point::sum[c]` | For side components attached to a boundary vertex, total contribution reachable if the boundary vertex has color `c`. |
| `Path::first_color` | Color of the first boundary in the current orientation. |
| `Path::last_color` | Color of the last boundary in the current orientation. |
| `Path::first_sum` | Same-color component sum containing the first boundary, inside this path cluster. |
| `Path::last_sum` | Same-color component sum containing the last boundary, inside this path cluster. |
| `Path::connected` | Whether the first and last boundaries are in the same same-color component. |

The cluster operations are short:

```cpp
auto compress = [](Path a, Path b, const auto&) {
    bool join = a.last_color == b.first_color;
    Path res{a.first_color, b.last_color, a.first_sum, b.last_sum, false};
    if (join && a.connected) res.first_sum += b.first_sum;
    if (join && b.connected) res.last_sum += a.last_sum;
    res.connected = a.connected && b.connected && join;
    return res;
};

auto rake = [](Point a, Point b) {
    return Point{{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]}};
};

auto add_edge = [](Path path, const auto&) {
    Point res{{0, 0}};
    res.sum[path.first_color] = path.first_sum;
    return res;
};

auto add_vertex = [](Point side, Vertex value, int) {
    long long sum = value.weight + side.sum[value.color];
    return Path{value.color, value.color, sum, sum, true};
};
```

Here `compress` is orientation-relative, so it can be used for both
`compress_down` and `compress_up`. Likewise `add_edge` can be used for both
edge directions because the graph edge itself does not change the component
value; only endpoint colors decide whether the component can pass through the
next vertex.

Build the structure like this:

```cpp
auto stt = m1une::tree::RerootingStaticTopTree(
    g,
    values,
    Point{{0, 0}},
    compress,
    compress,
    rake,
    add_edge,
    add_edge,
    add_vertex
);
```

For query type `3 v`, define a folder and pass it to `fold_rerooting`. The
folder keeps the component containing the original query vertex and grows it
while the library climbs from `vertex_node(v)` to the expression root.

```cpp
using Stt = decltype(stt);

struct QueryFolder {
    const Stt& stt;
    int color = 0;
    long long answer = 0;
    bool touches_top = false;
    bool touches_bottom = false;
    bool pending_open = false;
    Point pending{{0, 0}};

    void start(int, const Vertex& value, const Point& local) {
        color = value.color;
        answer = value.weight + local.sum[color];
        touches_top = true;
        touches_bottom = true;
        pending_open = false;
        pending = stt.point_id();
    }

    void compress_lower(const Path& lower, Stt::edge_type) {
        bool connect = touches_bottom && lower.first_color == color;
        if (connect) answer += lower.first_sum;
        touches_bottom = connect && lower.connected;
    }

    void compress_upper(const Path& upper, Stt::edge_type) {
        bool connect = touches_top && upper.first_color == color;
        if (connect) answer += upper.first_sum;
        touches_top = connect && upper.connected;
    }

    void add_edge(Stt::edge_type) {
        pending_open = touches_top;
        pending = stt.point_id();
    }

    void rake_left(const Point& point) {
        if (pending_open) pending = stt.rake(point, pending);
    }

    void rake_right(const Point& point) {
        if (pending_open) pending = stt.rake(pending, point);
    }

    void add_vertex(int, const Vertex& value) {
        if (pending_open && value.color == color) {
            answer += value.weight + pending.sum[color];
            touches_top = true;
            touches_bottom = true;
        } else {
            touches_top = false;
            touches_bottom = false;
        }
        pending_open = false;
        pending = stt.point_id();
    }

    long long result() const {
        return answer;
    }
};

auto query = [&](int v) {
    return stt.fold_rerooting(v, QueryFolder{stt});
};
```

The flags have these roles:

| Variable | Meaning |
| --- | --- |
| `touches_top` | The query component reaches the current path cluster's top boundary. |
| `touches_bottom` | The query component reaches the current path cluster's bottom boundary. |
| `pending_open` | We have moved from a child path into a parent-side point/rake cluster, and the component can still reach the parent vertex. |
| `pending` | Other side components of that parent vertex collected while climbing through `Rake` nodes. |

For updates, keep the external `values` array in sync and call `set`:

```cpp
// type 1: flip color
values[v].color ^= 1;
stt.set(v, values[v]);

// type 2: add weight
values[v].weight += x;
stt.set(v, values[v]);

// type 3: answer
std::cout << query(v) << '\n';
```

The input vertices in ABC460 G are 1-indexed, so decrement `v` before using
these snippets.

The total complexity is `O(N log N)` construction callback work and
`O(log N)` per update/query, assuming the static top tree height is logarithmic.
The verification test `test_rerooting_static_top_tree_vertex_component`
contains a small brute-force-checked version of this pattern.

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
