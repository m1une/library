---
title: Commutative Link-Cut Tree
documentation_of: ../../data_structure/commutative_link_cut_tree.hpp
---

## Overview

`m1une::data_structure::CommutativeLinkCutTree<Monoid>` is a link-cut tree with
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
    static T inverse(const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inverse(x)` must satisfy `op(x, inverse(x)) == id()`.

## Construction

```cpp
CommutativeLinkCutTree<Monoid> lct;
CommutativeLinkCutTree<Monoid> lct(n);
CommutativeLinkCutTree<Monoid> lct(values);
```

Construction and `add_vertex` follow `PathLinkCutTree`.

## Methods

All `PathLinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries: `prod`, `path_prod`, `path_size`, `kth_vertex`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Group product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |

## Example

```cpp
#include "data_structure/commutative_link_cut_tree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::CommutativeLinkCutTree<Sum> lct(std::vector<long long>{1, 2, 3, 4, 5});

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

This structure does not support non-commutative subtree products. A represented
subtree has no canonical linear order, and the virtual-child aggregate relies on
commutativity and `inverse`.
