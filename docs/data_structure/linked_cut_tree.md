---
title: Linked-Cut Tree
documentation_of: ../../data_structure/linked_cut_tree.hpp
---

## Overview

`m1une::data_structure::LinkedCutTree<Monoid>` is a link-cut tree with
the same path-query interface as `PathLinkCutTree`, plus rooted subtree queries.

The monoid operation must be commutative and must provide an inverse. This lets
the structure maintain aggregates of virtual child subtrees and update them in
constant time whenever `access` changes the preferred path. Path and subtree
queries are both amortized $O(\log N)$.

## Template Parameter

`Monoid` must satisfy `m1une::monoid::IsCommutativeGroup`:

```cpp
struct M {
    using value_type = T;
    static T id();
    static T op(const T& a, const T& b);
    static T inv(const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inv(x)` must satisfy `op(x, inv(x)) == id()`.

## Construction

```cpp
LinkedCutTree<Monoid> lct;
LinkedCutTree<Monoid> lct(n);
LinkedCutTree<Monoid> lct(values);
```

Construction and `add_vertex` follow `PathLinkCutTree`.

## Methods

Core methods:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `reroot`, `link`, `link_parent`, `link_edge`,
  `cut`, `cut_parent`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `root`, `lca`
* path queries: `prod`, `path_prod`, `path_size`, `kth_vertex`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `T component_prod(v)` | Group product of the whole connected component containing `v`. | Amortized $O(\log N)$ |
| `int component_size(v)` | Number of link-cut-tree vertices in the component containing `v`. | Amortized $O(\log N)$ |
| `int child_toward(root, v)` | Child of `root` lying on the path from `root` to `v`; requires `root != v`. | Amortized $O(\log N)$ |
| `T branch_prod(root, v)` | Group product of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int branch_size(root, v)` | Size of the entire branch of `root` that contains `v`. | Amortized $O(\log N)$ |
| `int parent(root, v)` | Parent of `v` when rooted at `root`, or `-1` if `root == v`. | Amortized $O(\log N)$ |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Group product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod_excluding_child(root, v, child)` | Product of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |
| `int subtree_size_excluding_child(root, v, child)` | Size of `v`'s rooted subtree excluding `child`'s subtree. | Amortized $O(\log N)$ |

## Example

```cpp
#include "data_structure/linked_cut_tree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::LinkedCutTree<Sum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    std::cout << lct.path_prod(2, 4) << "\n";     // 3 + 2 + 4 + 5 = 14
    std::cout << lct.subtree_prod(0, 1) << "\n";  // 2 + 3 + 4 + 5 = 14
}
```

## Notes

`link_edge` creates helper vertices exactly like `PathLinkCutTree`; subtree sizes
and products include those helper vertices. Initialize original vertices with
the group identity when you want subtree products over edge values only.

`evert(v)` and `reroot(v)` change the represented root of the component to `v`.
The APIs `link`, `cut`, `prod`, `path_prod`, `path_size`, `kth_vertex`,
`subtree_prod(root, v)`, and `subtree_size(root, v)` may internally call
`evert`, so they may also change represented-root orientation.

`cut_parent(v)` is different from `cut(u, v)`: it cuts the parent edge of `v`
with respect to the current represented-root orientation and does not call
`evert`.

This structure does not support non-commutative subtree products. A represented
subtree has no canonical linear order, and the virtual-child aggregate relies on
commutativity and `inv`.
