---
title: Lazy Linked-Cut Tree
documentation_of: ../../data_structure/lazy_linked_cut_tree.hpp
---

## Overview

`m1une::data_structure::LazyLinkedCutTree<ActedMonoid>` maintains a dynamic
forest. It supports linking two trees, cutting edges, rerooting represented
trees, querying path products, applying lazy updates on paths, and querying
rooted subtree products and sizes.

The value is stored on link-cut-tree vertices. If you need edge values, create
one extra link-cut-tree vertex for each original edge and connect it between the
two endpoints. The `link_edge` helper does this for you.

The value monoid must be commutative and must provide an inverse. The structure
keeps a cached aggregate of virtual child subtrees, while path lazy propagation
updates only preferred-path vertices. Path operations and subtree queries are
amortized $O(\log N)$.

## Template Parameter

`ActedMonoid` must satisfy
`m1une::acted_monoid::IsCommutativeActedGroup`:

```cpp
struct AM {
    using value_type = T;
    using operator_type = F;

    static T id();
    static T op(const T& a, const T& b);
    static T inv(const T& x);

    static F op_id();
    static F op_comp(const F& f, const F& g);

    static T mapping(const F& f, const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inv(x)` must satisfy `op(x, inv(x)) == id()`. As with
`LazyPathLinkCutTree`, `mapping` must distribute over `op`.

## Construction

```cpp
LazyLinkedCutTree<ActedMonoid> lct;
LazyLinkedCutTree<ActedMonoid> lct(n);
LazyLinkedCutTree<ActedMonoid> lct(values);
```

* `LazyLinkedCutTree(n)` creates `n` isolated vertices initialized with
  `ActedMonoid::id()`.
* `LazyLinkedCutTree(values)` creates one isolated vertex for each value.
* `add_vertex(value)` appends a new isolated vertex and returns its index.

Construction from `std::vector<U>` is supported when
`ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or
`static_cast<T>(value)` is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Number of link-cut-tree vertices, including helper edge nodes. | `O(1)` |
| `bool empty()` | Whether there are no vertices. | `O(1)` |
| `int add_vertex(value)` | Adds one isolated vertex and returns its id. | Amortized `O(1)` |
| `int edge_count()` | Number of edge helpers created by `link_edge`. | `O(1)` |
| `bool edge_alive(edge_id)` | Whether the helper edge is currently linked. | `O(1)` |
| `int edge_node(edge_id)` | Link-cut-tree vertex id storing this edge's value. | `O(1)` |
| `std::pair<int, int> edge_endpoints(edge_id)` | Original endpoints passed to `link_edge`. | `O(1)` |
| `T get(v)` | Pushes pending updates and returns the stored value of vertex `v`. | Amortized $O(\log N)$ |
| `T operator[](v)` | Alias for `get(v)`. | Amortized $O(\log N)$ |
| `void set(v, value)` | Updates the value of vertex `v`. | Amortized $O(\log N)$ |
| `void apply(v, f)` | Applies operator `f` to one vertex. | Amortized $O(\log N)$ |
| `void apply(u, v, f)` | Applies operator `f` to every link-cut-tree vertex on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `void evert(v)` | Makes `v` the represented root of its component. | Amortized $O(\log N)$ |
| `void reroot(v)` | Alias for `evert(v)`. | Amortized $O(\log N)$ |
| `int component_root(v)` | Returns the represented root of `v`'s component. | Amortized $O(\log N)$ |
| `int root(v)` | Alias for `component_root(v)`. | Amortized $O(\log N)$ |
| `bool connected(u, v)` | Returns whether `u` and `v` are in the same component. | Amortized $O(\log N)$ |
| `bool same(u, v)` | Alias for `connected(u, v)`. | Amortized $O(\log N)$ |
| `bool link(u, v)` | Adds edge `(u, v)` if they are in different components. Returns whether it was added. | Amortized $O(\log N)$ |
| `bool link_parent(child, parent)` | Rooted-tree spelling of `link(child, parent)`; after a successful link, the merged component keeps the original represented root of `parent`'s component. | Amortized $O(\log N)$ |
| `int link_edge(u, v, value)` | Adds an edge-value node between `u` and `v`. Returns an edge id, or `-1` if already connected. | Amortized $O(\log N)$ |
| `bool cut(u, v)` | Removes edge `(u, v)` if it exists. Returns whether it was removed. | Amortized $O(\log N)$ |
| `bool cut_parent(v)` | Removes the current parent edge of `v` with respect to the represented root. | Amortized $O(\log N)$ |
| `bool cut_edge(edge_id)` | Removes a helper edge created by `link_edge`. Returns whether it was removed. | Amortized $O(\log N)$ |
| `T get_edge(edge_id)` | Pushes pending updates and returns the value stored in the helper edge node. | Amortized $O(\log N)$ |
| `void set_edge(edge_id, value)` | Updates the value stored in the helper edge node. | Amortized $O(\log N)$ |
| `void apply_edge(edge_id, f)` | Applies operator `f` to one helper edge node. | Amortized $O(\log N)$ |
| `T prod(u, v)` | Value product on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `T path_prod(u, v)` | Alias for `prod(u, v)`. | Amortized $O(\log N)$ |
| `int path_size(u, v)` | Number of link-cut-tree vertices on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `int kth_vertex(u, v, k)` | Returns the `k`-th vertex on the path from `u` to `v`, zero-indexed. | Amortized $O(\log N)$ |
| `int lca(u, v)` | Returns the LCA with respect to the current represented root, or `-1` if disconnected. | Amortized $O(\log N)$ |
| `T component_prod(v)` | Value product of the whole connected component containing `v`. | Amortized $O(\log N)$ |
| `int component_size(v)` | Number of link-cut-tree vertices in the component containing `v`. | Amortized $O(\log N)$ |
| `int child_toward(root, v)` | Child of `root` lying on the path from `root` to `v`; requires `root != v`. | Amortized $O(\log N)$ |
| `T branch_prod(root, v)` | Value product of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int branch_size(root, v)` | Size of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int parent(root, v)` | Parent of `v` when rooted at `root`, or `-1` if `root == v`. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Value product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod_excluding_child(root, v, child)` | Product of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |
| `int subtree_size_excluding_child(root, v, child)` | Size of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |

Path and rooted-subtree queries assert that the queried vertices are connected.
`child_toward(root, v)`, `branch_prod(root, v)`, and `branch_size(root, v)`
also assert `root != v`. The excluding-child helpers assert that `child` is a
child of `v` when the represented tree is rooted at `root`.

Unlike non-lazy `LinkedCutTree::get`, `LazyLinkedCutTree::get` is not `const`,
because it must expose the vertex and push pending lazy operations first.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_linked_cut_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::LazyLinkedCutTree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    lct.apply(2, 4, 10);
    std::cout << lct.path_prod(2, 4).sum << "\n";     // 54
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 54

    lct.apply(0, 3, 5);
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 64
}
```

## Example: Rooted Tree Helpers

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::data_structure::LazyLinkedCutTree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

// Rooted shape:
// 0
// +- 1
// +- 2
//    +- 3
//    +- 4
lct.link_parent(1, 0);
lct.link_parent(2, 0);
lct.link_parent(3, 2);
lct.link_parent(4, 2);
lct.reroot(0);

lct.apply(3, 4, 10);  // adds 10 to vertices 3, 2, and 4

long long whole = lct.component_prod(0).sum;       // 45
long long branch = lct.branch_prod(0, 4).sum;      // 42
int p = lct.parent(0, 4);                          // 2
int c = lct.child_toward(0, 4);                    // 2
long long without_4 = lct.subtree_prod_excluding_child(0, 2, 4).sum;  // 27

lct.cut_parent(4);  // cuts edge 2-4 without changing the represented root first
```

## Notes

`link_edge` creates helper vertices for edge values. Subtree sizes and products
include those helper vertices. Initialize original vertices with
`ActedMonoid::id()` when you want subtree products over edge values only.

`evert(v)` and `reroot(v)` change the represented root of the component to `v`.
The APIs `link`, `link_parent`, `cut`, `prod`, `path_prod`, `apply(u, v, f)`,
`path_size`, `kth_vertex`, `subtree_prod(root, v)`, and
`subtree_size(root, v)` may internally call `evert`, so they may also change
represented-root orientation.

`link_parent(child, parent)` internally performs the same operation as
`link(child, parent)`. It reroots the child-side component at `child`, attaches
it under `parent`, and preserves the original represented root of the parent-side
component as the represented root of the merged component.

`cut_parent(v)` is different from `cut(u, v)`: it cuts the parent edge of `v`
with respect to the current represented-root orientation and does not call
`evert`.

This structure supports lazy path updates, but it does not provide subtree
updates. A path update must not touch virtual side subtrees, so the
implementation keeps preferred-path values and virtual-subtree aggregates as
separate cached values.

This structure does not support non-commutative subtree products. A represented
subtree has no canonical linear order, and the virtual-child aggregate relies on
commutativity and `inv`.
