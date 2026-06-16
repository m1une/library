---
title: Lazy Link-Cut Tree
documentation_of: ../../data_structure/lazy_link_cut_tree.hpp
---

## Overview

`m1une::data_structure::LazyLinkCutTree<ActedMonoid>` maintains a dynamic
forest with path queries and path updates.

It is the lazy-propagation version of `LinkCutTree`. The value monoid gives the
path query, and the operator monoid gives the path update. This matches the
same acted-monoid style used by `LazySegtree`.

Typical examples:

* path add, path sum
* path affine update, path sum
* path assign, path max
* edge path updates by storing each edge as an extra node

## Template Parameter

`ActedMonoid` must satisfy `m1une::acted_monoid::IsActedMonoid`:

```cpp
struct AM {
    using value_type = T;
    using operator_type = F;

    static T id();
    static T op(const T& a, const T& b);

    static F op_id();
    static F op_comp(const F& f, const F& g); // f(g(x))

    static T mapping(const F& f, const T& x);
};
```

The important law is that `mapping` must distribute over the value monoid:

```cpp
mapping(f, op(a, b)) == op(mapping(f, a), mapping(f, b))
```

The implementation does not support position-dependent lazy operators such as
arithmetic-progression updates. There is no `op_shift` hook here, because a
link-cut tree reverses preferred paths dynamically.

## Construction

```cpp
LazyLinkCutTree<ActedMonoid> lct;
LazyLinkCutTree<ActedMonoid> lct(n);
LazyLinkCutTree<ActedMonoid> lct(values);
```

* `LazyLinkCutTree(n)` creates `n` isolated vertices initialized with
  `ActedMonoid::id()`.
* `LazyLinkCutTree(values)` creates one isolated vertex for each value.
* `add_vertex(value)` appends a new isolated vertex and returns its index.

Construction from `std::vector<U>` is supported when
`ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or
`static_cast<T>(value)` is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Number of link-cut-tree vertices. | `O(1)` |
| `bool empty()` | Whether there are no vertices. | `O(1)` |
| `int add_vertex(value)` | Adds one isolated vertex and returns its id. | Amortized `O(1)` |
| `int edge_count()` | Number of edge helpers created by `link_edge`. | `O(1)` |
| `bool edge_alive(edge_id)` | Whether the helper edge is currently linked. | `O(1)` |
| `int edge_node(edge_id)` | Link-cut-tree vertex id storing this edge's value. | `O(1)` |
| `std::pair<int, int> edge_endpoints(edge_id)` | Original endpoints passed to `link_edge`. | `O(1)` |
| `T get(v)` | Pushes pending updates and returns the stored value of vertex `v`. | Amortized `O(log N)` |
| `T operator[](v)` | Alias for `get(v)`. | Amortized `O(log N)` |
| `void set(v, value)` | Updates the value of vertex `v`. | Amortized `O(log N)` |
| `void apply(v, f)` | Applies operator `f` to one vertex. | Amortized `O(log N)` |
| `void apply(u, v, f)` | Applies operator `f` to every link-cut-tree vertex on the path from `u` to `v`. | Amortized `O(log N)` |
| `void evert(v)` | Makes `v` the represented root of its tree. | Amortized `O(log N)` |
| `int component_root(v)` | Returns the represented root of `v`'s tree. | Amortized `O(log N)` |
| `bool connected(u, v)` | Returns whether `u` and `v` are in the same tree. | Amortized `O(log N)` |
| `bool same(u, v)` | Alias for `connected(u, v)`. | Amortized `O(log N)` |
| `bool link(u, v)` | Adds edge `(u, v)` if they are in different trees. Returns whether it was added. | Amortized `O(log N)` |
| `int link_edge(u, v, value)` | Adds an edge-value node between `u` and `v`. Returns an edge id, or `-1` if `u` and `v` are already connected. | Amortized `O(log N)` |
| `bool cut(u, v)` | Removes edge `(u, v)` if it exists. Returns whether it was removed. | Amortized `O(log N)` |
| `bool cut_edge(edge_id)` | Removes a helper edge created by `link_edge`. Returns whether it was removed. | Amortized `O(log N)` |
| `T get_edge(edge_id)` | Returns the value stored in the helper edge node. | Amortized `O(log N)` |
| `void set_edge(edge_id, value)` | Updates the value stored in the helper edge node. | Amortized `O(log N)` |
| `void apply_edge(edge_id, f)` | Applies operator `f` to one helper edge node. | Amortized `O(log N)` |
| `T prod(u, v)` | Returns the monoid product on the path from `u` to `v`. | Amortized `O(log N)` |
| `T path_prod(u, v)` | Alias for `prod(u, v)`. | Amortized `O(log N)` |
| `int path_size(u, v)` | Number of link-cut-tree vertices on the path from `u` to `v`. | Amortized `O(log N)` |
| `int kth_vertex(u, v, k)` | Returns the `k`-th vertex on the path from `u` to `v`, zero-indexed. | Amortized `O(log N)` |
| `int lca(u, v)` | Returns the LCA with respect to the current represented root, or `-1` if disconnected. | Amortized `O(log N)` |

`prod`, `apply(u, v, f)`, `path_size`, and `kth_vertex` require `u` and `v` to
be connected. This is checked by `assert`.

Unlike `LinkCutTree::get`, `LazyLinkCutTree::get` is not `const`, because it
must expose the vertex and push pending lazy operations first.

## Path Order

`prod(u, v)` returns the value monoid product in path order from `u` to `v`.
The implementation stores both forward and reversed products, so
non-commutative value monoids are supported as long as the lazy mapping
distributes over that monoid.

## Represented Roots And LCA

`link`, `cut`, `prod`, `apply(u, v, f)`, `path_size`, and `kth_vertex` use
rerooting internally. They may change the represented root of the affected
tree.

`lca(u, v)` is computed with respect to the current represented root. If the
root matters, call `evert(r)` immediately before `lca`:

```cpp
lct.evert(r);
int x = lct.lca(u, v);
```

## Example: Path Add, Path Sum

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::LazyLinkCutTree<AM> lct(std::vector<long long>{1, 2, 3, 4});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);

    std::cout << lct.prod(2, 3).sum << "\n"; // 3 + 2 + 4 = 9

    lct.apply(2, 3, 10);
    std::cout << lct.prod(2, 3).sum << "\n"; // 13 + 12 + 14 = 39
}
```

## Example: Edge Path Add, Edge Path Sum

Initialize original vertices with `ActedMonoid::id()`, whose size is `0` for
`RangeAddRangeSum`. Then edge nodes are the only values affected by path
updates and path sums.

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::data_structure::LazyLinkCutTree<AM> lct(n);

int edge_id = lct.link_edge(u, v, weight);

lct.apply(a, b, 5);              // add 5 to every edge on path a-b
long long distance = lct.prod(a, b).sum;

lct.set_edge(edge_id, new_weight);
lct.cut_edge(edge_id);
```

## Notes

All complexities are amortized. `size()` includes helper edge nodes created by
`link_edge`; original vertex ids remain unchanged.

This implementation maintains path aggregates only. It does not maintain
subtree aggregates of the represented tree.
