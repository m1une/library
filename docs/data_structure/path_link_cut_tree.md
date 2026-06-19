---
title: Path Link-Cut Tree
documentation_of: ../../data_structure/path_link_cut_tree.hpp
---

## Overview

`m1une::data_structure::PathLinkCutTree<Monoid>` maintains a dynamic forest. It
supports linking two trees, cutting an existing edge, rerooting a represented
tree, and querying a monoid product on a path.

The value is stored on vertices. If you need edge values, create one extra
link-cut-tree vertex for each original edge and connect it between the two
endpoints. The `link_edge` helper does this for you.

The implementation supports non-commutative monoids. `prod(u, v)` returns the
product in path order from `u` to `v`.

## Template Parameter

`Monoid` must satisfy `m1une::monoid::IsMonoid`:

```cpp
struct M {
    using value_type = T;
    static T id();
    static T op(const T& a, const T& b);
};
```

`op(a, b)` should be associative, and `id()` should be its identity.

## Construction

```cpp
PathLinkCutTree<Monoid> lct;
PathLinkCutTree<Monoid> lct(n);
PathLinkCutTree<Monoid> lct(values);
```

* `PathLinkCutTree(n)` creates `n` isolated vertices initialized with
  `Monoid::id()`.
* `PathLinkCutTree(values)` creates one isolated vertex for each value.
* `add_vertex(value)` appends a new isolated vertex and returns its index.

As with `Segtree`, construction from `std::vector<U>` is supported when
`Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Number of link-cut-tree vertices. | $O(1)$ |
| `bool empty()` | Whether there are no vertices. | $O(1)$ |
| `int add_vertex(value)` | Adds one isolated vertex and returns its id. | Amortized $O(1)$ |
| `int edge_count()` | Number of edge helpers created by `link_edge`. | $O(1)$ |
| `bool edge_alive(edge_id)` | Whether the helper edge is currently linked. | $O(1)$ |
| `int edge_node(edge_id)` | Link-cut-tree vertex id storing this edge's value. | $O(1)$ |
| `std::pair<int, int> edge_endpoints(edge_id)` | Original endpoints passed to `link_edge`. | $O(1)$ |
| `const T& get(v)` | Returns the stored value of vertex `v`. | $O(1)$ |
| `const T& operator[](v)` | Alias for `get(v)`. | $O(1)$ |
| `void set(v, value)` | Updates the value of vertex `v`. | Amortized $O(\log N)$ |
| `void evert(v)` | Makes `v` the represented root of its tree. | Amortized $O(\log N)$ |
| `int component_root(v)` | Returns the represented root of `v`'s tree. | Amortized $O(\log N)$ |
| `bool connected(u, v)` | Returns whether `u` and `v` are in the same tree. | Amortized $O(\log N)$ |
| `bool same(u, v)` | Alias for `connected(u, v)`. | Amortized $O(\log N)$ |
| `bool link(u, v)` | Adds edge `(u, v)` if they are in different trees. Returns whether it was added. | Amortized $O(\log N)$ |
| `int link_edge(u, v, value)` | Adds an edge-value node between `u` and `v`. Returns an edge id, or `-1` if `u` and `v` are already connected. | Amortized $O(\log N)$ |
| `bool cut(u, v)` | Removes edge `(u, v)` if it exists. On success, the resulting trees are rooted at `u` and `v`. | Amortized $O(\log N)$ |
| `bool cut_edge(edge_id)` | Removes a helper edge created by `link_edge`. On success, the endpoint trees are rooted at the stored endpoints. | Amortized $O(\log N)$ |
| `const T& get_edge(edge_id)` | Returns the value stored in the helper edge node. | $O(1)$ |
| `void set_edge(edge_id, value)` | Updates the value stored in the helper edge node. | Amortized $O(\log N)$ |
| `T prod(u, v)` | Returns the monoid product on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `T path_prod(u, v)` | Alias for `prod(u, v)`. | Amortized $O(\log N)$ |
| `int path_size(u, v)` | Number of link-cut-tree vertices on the path from `u` to `v`. | Amortized $O(\log N)$ |
| `int kth_vertex(u, v, k)` | Returns the `k`-th vertex on the path from `u` to `v`, zero-indexed. | Amortized $O(\log N)$ |
| `int lca(u, v)` | Returns the LCA with respect to the current represented root, or `-1` if disconnected. | Amortized $O(\log N)$ |

`prod`, `path_size`, and `kth_vertex` require `u` and `v` to be connected.
This is checked by `assert`.

## Path Order

For non-commutative monoids, order matters. If the represented path is:

```text
u - a - b - v
```

then:

```cpp
lct.prod(u, v) == op(op(op(value[u], value[a]), value[b]), value[v])
lct.prod(v, u) == op(op(op(value[v], value[b]), value[a]), value[u])
```

Internally the structure keeps both the normal and reversed aggregate of every
splay subtree, so path reversal by `evert` is safe for non-commutative monoids.

## Represented Roots And LCA

`evert(v)` changes the represented root of the tree containing `v`.

The following public methods reroot internally:

* `link(u, v)` first reroots `u`'s tree at `u`. If it succeeds, the merged tree
  keeps the original represented root of `v`'s tree. If it returns `false`
  because `u` and `v` were already connected, that tree may be left rooted at
  `u`.
* `link_edge(u, v, value)` uses `link` twice. If it succeeds, the merged tree
  keeps the original represented root of `v`'s tree.
* `cut(u, v)` first reroots at `u`. If it succeeds, the tree containing `u` is
  rooted at `u`, and the tree containing `v` is rooted at `v`. If it returns
  `false` after `u != v`, `u`'s tree may still be left rooted at `u`.
* `cut_edge(edge_id)` uses `cut` twice. If it succeeds, the original `u`-side
  tree is rooted at the stored `u` endpoint, the original `v`-side tree is
  rooted at the stored `v` endpoint, and the helper edge node is isolated.
* `prod(u, v)`, `path_prod(u, v)`, `path_size(u, v)`, and
  `kth_vertex(u, v, k)` reroot at `u`, so the represented root becomes `u`.

Other public methods may expose or splay vertices, but they do not change the
represented root.

`lca(u, v)` is computed with respect to the current represented root. If the
root matters, call `evert(r)` immediately before `lca`:

```cpp
lct.evert(r);
int x = lct.lca(u, v);
```

## Example: Vertex Path Sum

```cpp
#include "data_structure/path_link_cut_tree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::PathLinkCutTree<Sum> lct(std::vector<long long>{1, 2, 3, 4});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);

    std::cout << lct.prod(2, 3) << "\n"; // 3 + 2 + 4 = 9

    lct.set(1, 10);
    std::cout << lct.prod(2, 3) << "\n"; // 3 + 10 + 4 = 17
}
```

## Example: Edge Path Sum

Store original vertices with identity values. `link_edge` creates one extra
link-cut-tree vertex for the edge value and links it between the two endpoints.

```cpp
using Sum = m1une::monoid::Add<long long>;
m1une::data_structure::PathLinkCutTree<Sum> lct(n);

int edge_id = lct.link_edge(u, v, weight);

long long distance = lct.prod(a, b);
lct.set_edge(edge_id, new_weight);
```

This also makes `cut` easy:

```cpp
lct.cut_edge(edge_id);
```

## Notes

All complexities are amortized. The represented forest must remain a forest:
`link(u, v)` returns `false` if `u` and `v` are already connected,
`link_edge(u, v, value)` returns `-1` in that case, and `cut(u, v)` returns
`false` if `(u, v)` is not an existing represented edge.

`size()` includes helper edge nodes created by `link_edge`. The original vertex
ids remain unchanged.

This implementation maintains path aggregates only. It does not maintain
subtree aggregates of the represented tree. For a variant with subtree-query
helpers, use `LinkCutTree`.

For path updates with lazy propagation, use `LazyPathLinkCutTree`.
