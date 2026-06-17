---
title: Link-Cut Tree With Subtree
documentation_of: ../../data_structure/link_cut_tree_with_subtree.hpp
---

## Overview

`m1une::data_structure::LinkCutTreeWithSubtree<Monoid>` is a link-cut tree with
the same path-query interface as `LinkCutTree`, plus rooted subtree queries.

Path operations are delegated to `LinkCutTree`, so non-commutative monoids are
supported on paths in the usual path order. Subtree operations are folded over
an explicit copy of the represented forest. This keeps subtree products correct
for arbitrary monoids, including non-commutative and non-invertible monoids.

For non-commutative subtree products, the order is deterministic preorder in
the represented forest: visit the subtree root first, then visit active incident
edges in the order they were linked.

## Template Parameter

`Monoid` must satisfy `m1une::monoid::IsMonoid`:

```cpp
struct M {
    using value_type = T;
    static T id();
    static T op(const T& a, const T& b);
};
```

## Construction

```cpp
LinkCutTreeWithSubtree<Monoid> lct;
LinkCutTreeWithSubtree<Monoid> lct(n);
LinkCutTreeWithSubtree<Monoid> lct(values);
```

Construction and `add_vertex` follow `LinkCutTree`.

## Methods

All `LinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries: `prod`, `path_prod`, `path_size`, `kth_vertex`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> subtree_vertices(root, v)` | Vertices in the subtree of `v` when the represented tree is rooted at `root`. | `O(C)` |
| `std::vector<int> subtree_vertices(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the rooted subtree. | `O(C)` |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `T subtree_prod(root, v)` | Monoid product of the rooted subtree. | `O(C)` |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | `O(C)` |

Here `C` is the number of link-cut-tree vertices in the connected component.
The product itself folds only the reported subtree, but finding the parent of
`v` with respect to `root` may scan the component.

## Example

```cpp
#include "data_structure/link_cut_tree_with_subtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::data_structure::LinkCutTreeWithSubtree<Sum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    std::cout << lct.path_prod(2, 4) << "\n";     // 3 + 2 + 4 + 5 = 14
    std::cout << lct.subtree_prod(0, 1) << "\n";  // 2 + 3 + 4 + 5 = 14
}
```

## Notes

`link_edge` creates helper vertices exactly like `LinkCutTree`; subtree methods
therefore include those helper vertices. Initialize original vertices with the
monoid identity when you want subtree products over edge values only.

The traversal-based subtree layer is intentional. A fully logarithmic generic
subtree aggregate on top of a link-cut tree needs additional algebraic structure
or a richer top-tree style interface; otherwise path rerooting and lazy
preferred-path changes do not preserve a well-defined non-commutative subtree
order.
