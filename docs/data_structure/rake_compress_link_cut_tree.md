---
title: Rake-Compress Link-Cut Tree
documentation_of: ../../data_structure/rake_compress_link_cut_tree.hpp
---

## Overview

`m1une::data_structure::RakeCompressLinkCutTree<TreeDPInfo>` maintains a
dynamic forest together with a tree DP. It separates the two aggregates needed
by subtree-aware link-cut trees:

* `Point` is a commutative group used to rake independent virtual children.
* `Path` is an ordered cluster used to compress a preferred path.

Only `Point` needs an inverse. In particular, affine functions on a path do not
need to be invertible, and `Path` does not need an identity or inverse.

All dynamic-forest operations take amortized $O(\log N)$ time, where $N$ is
the number of link-cut-tree nodes, including helper edge nodes. The structure
uses $O(N)$ space.

## Tree DP Interface

`TreeDPInfo` provides three types:

```cpp
using Point = ...;
using Path = ...;
using Vertex = ...;
```

These types describe three different levels of the tree DP:

![Relationship between Vertex, Point, and Path](../assets/rake_compress_link_cut_tree_types.png)

The three panels show the core conversions: `add_vertex` combines local
`Vertex` data with raked virtual-child `Point` data, `compress` concatenates
ordered `Path` clusters, and `add_edge` turns a child `Path` into the `Point`
contribution attached to its parent.

### `Vertex`

`Vertex` is the local data stored at one link-cut-tree node. It is not an
aggregate. For example, it may store the value of an original tree vertex, or
the affine function of an original edge when that edge is represented by a
helper node.

`set(v, vertex)` replaces this local data. `add_vertex(point, vertex)` combines
it with the already-aggregated virtual children to create a one-node `Path`
cluster.

### `Point`

`Point` represents zero or more independent child-side clusters attached at
the same path node. These are the virtual children: represented-tree edges
which are not currently part of the preferred path.

Their order has no meaning, so `rake` must be associative and commutative.
`Point::id()` represents no virtual children. `Point::inv()` lets `access`
remove a child contribution when that child enters the preferred path.

Conceptually, a node maintains:

```cpp
Point virtual_children = Point::id();
virtual_children = rake(virtual_children, add_edge(child_path));
```

`Point` does not include the local `Vertex` at the attachment node.

### `Path`

`Path` represents an ordered, nonempty preferred-path cluster. It contains the
nodes on that path together with all `Point` contributions raked into those
nodes. Its two ends have an order: the parent-side end comes before the
child-side end in the current represented-root orientation.

`compress(parent_side, child_side)` concatenates two adjacent path clusters in
that order. It must be associative, but does not need to be commutative.
Reversing a represented path may change the aggregate, so each link-cut-tree
node maintains both the forward and reverse `Path` products.

`add_edge(path)` closes the child-side path cluster and converts it into the
one-boundary `Point` contribution seen by its parent. A `Path` needs neither an
identity nor an inverse.

At a link-cut-tree node, the aggregate is formed schematically as:

```cpp
Path self = add_vertex(virtual_children, vertex);
Path whole = self;
if (left_path_exists) whole = compress(left_path, whole);
if (right_path_exists) whole = compress(whole, right_path);
```

`Point` provides:

```cpp
static Point id();
Point inv() const;
```

`TreeDPInfo` provides:

```cpp
static Path add_vertex(const Point& virtual_children, const Vertex& vertex);
static Point add_edge(const Path& path);
static Point rake(const Point& a, const Point& b);
static Path compress(const Path& parent_side, const Path& child_side);
```

The operations have the following meanings:

* `rake(a, b)` merges independent virtual-subtree contributions. It must be
  associative and commutative.
* `compress(p, c)` joins an upper parent-side path cluster with a lower
  child-side path cluster. It must be associative, but need not be commutative.
* `add_vertex(point, vertex)` combines one node with its virtual children.
* `add_edge(path)` converts a represented child cluster into the contribution
  seen by its parent.

The inverse of `add_edge(path)` is used only when `access` changes a preferred
child back into a virtual child or vice versa.

## Main Methods

| Method | Description | Time |
| --- | --- | --- |
| `int add_vertex(vertex)` | Adds an isolated node and returns its index. | Amortized $O(1)$ |
| `const Vertex& get(v)` | Returns the information stored at node `v`. | $O(1)$ |
| `void set(v, vertex)` | Replaces the information at node `v`. | Amortized $O(\log N)$ |
| `void evert(v)` | Makes `v` the represented root. | Amortized $O(\log N)$ |
| `bool connected(u, v)` | Tests whether two nodes are in the same component. | Amortized $O(\log N)$ |
| `bool link(u, v)` | Links two different components. | Amortized $O(\log N)$ |
| `bool cut(u, v)` | Cuts the represented-tree edge between adjacent nodes. | Amortized $O(\log N)$ |
| `bool cut_parent(v)` | Cuts the parent edge of `v` in the current root orientation. | Amortized $O(\log N)$ |
| `Path component_prod(v)` | Reroots at `v` and returns the whole-component cluster. | Amortized $O(\log N)$ |

`query_component(v)` is an alias for `component_prod(v)`.

## Edge Values

`link_edge(u, v, vertex)` creates a helper node between `u` and `v`, stores
`vertex` on it, and returns an edge id. The helper methods `edge_node`,
`edge_endpoints`, `get_edge`, `set_edge`, and `cut_edge` use that id.

`link_edge`, `set_edge`, and `cut_edge` take amortized $O(\log N)$ time.
`edge_node`, `edge_endpoints`, `get_edge`, `edge_count`, and `edge_alive` take
$O(1)$ time.

This is useful when original vertices and original edges use different cases of
the same `Vertex` type. The Point Set Tree Path Composite Sum verification uses
vertex nodes for point values and helper edge nodes for affine functions.

## Example

The following DP stores an integer on every original vertex and an affine
function $f(t) = at + b$ on every original edge. The query returns the sum of
all vertex values after each value is transported toward the chosen root by the
edge functions on its path.

```cpp
#include <iostream>

#include "data_structure/rake_compress_link_cut_tree.hpp"

struct AffineTreeSum {
    struct Point {
        long long sum;
        long long count;

        static Point id() {
            return Point{0, 0};
        }

        Point inv() const {
            return Point{-sum, -count};
        }
    };

    struct Path {
        long long a;
        long long b;
        long long sum;
        long long count;
    };

    struct Vertex {
        bool is_vertex;
        long long a;
        long long b;
    };

    static Path add_vertex(const Point& children, const Vertex& vertex) {
        if (vertex.is_vertex) {
            return Path{1, 0, children.sum + vertex.a, children.count + 1};
        }
        return Path{
            vertex.a,
            vertex.b,
            children.sum * vertex.a + children.count * vertex.b,
            children.count
        };
    }

    static Point add_edge(const Path& path) {
        return Point{path.sum, path.count};
    }

    static Point rake(const Point& x, const Point& y) {
        return Point{x.sum + y.sum, x.count + y.count};
    }

    static Path compress(const Path& parent, const Path& child) {
        return Path{
            parent.a * child.a,
            parent.a * child.b + parent.b,
            parent.sum + parent.a * child.sum + parent.b * child.count,
            parent.count + child.count
        };
    }
};

int main() {
    using LCT =
        m1une::data_structure::RakeCompressLinkCutTree<AffineTreeSum>;

    LCT lct;
    int u = lct.add_vertex(AffineTreeSum::Vertex{true, 2, 0});
    int v = lct.add_vertex(AffineTreeSum::Vertex{true, 3, 0});
    int w = lct.add_vertex(AffineTreeSum::Vertex{true, 5, 0});

    // u --(t -> 2t + 1)--> v --(t -> 3t)--> w
    int uv = lct.link_edge(u, v, AffineTreeSum::Vertex{false, 2, 1});
    lct.link_edge(v, w, AffineTreeSum::Vertex{false, 3, 0});

    long long rooted_at_u = lct.component_prod(u).sum;
    long long rooted_at_w = lct.component_prod(w).sum;
    std::cout << rooted_at_u << '\n';  // 40
    std::cout << rooted_at_w << '\n';  // 29

    lct.set(v, AffineTreeSum::Vertex{true, 7, 0});
    lct.set_edge(uv, AffineTreeSum::Vertex{false, 0, 4});
}
```

`compress(parent, child)` is ordered: reversing its arguments generally
changes the result. The affine coefficient may be zero because only `Point`
requires an inverse.

## Notes

`component_prod(v)` changes the represented root to `v`. Its returned `Path`
contains the whole component, including all virtual branches attached to the
preferred path exposed by rerooting.

The structure assumes that the supplied rake/compress operations describe a
valid associative tree DP. It does not require affine coefficients or other
path transitions to be invertible.
