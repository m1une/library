---
title: Lazy Link-Cut Tree With Subtree
documentation_of: ../../data_structure/lazy_link_cut_tree_with_subtree.hpp
---

## Overview

`m1une::data_structure::LazyLinkCutTreeWithSubtree<ActedMonoid>` is the subtree
query companion to `LazyLinkCutTree`. It keeps the same dynamic path query and
path update interface, and adds rooted subtree queries and subtree updates.

Path operations are delegated to `LazyLinkCutTree`. Subtree operations use an
explicit copy of the represented forest and visit vertices in deterministic
preorder, so they remain correct for arbitrary acted monoids. Pending path lazy
updates are pushed by reading each visited vertex before it is folded into a
subtree product.

## Template Parameter

`ActedMonoid` must satisfy `m1une::acted_monoid::IsActedMonoid`:

```cpp
struct AM {
    using value_type = T;
    using operator_type = F;

    static T id();
    static T op(const T& a, const T& b);

    static F op_id();
    static F op_comp(const F& f, const F& g);

    static T mapping(const F& f, const T& x);
};
```

## Construction

```cpp
LazyLinkCutTreeWithSubtree<ActedMonoid> lct;
LazyLinkCutTreeWithSubtree<ActedMonoid> lct(n);
LazyLinkCutTreeWithSubtree<ActedMonoid> lct(values);
```

Construction and `add_vertex` follow `LazyLinkCutTree`.

## Methods

All `LazyLinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries and updates: `prod`, `path_prod`, `path_size`, `kth_vertex`,
  `apply`, `apply_edge`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> subtree_vertices(root, v)` | Vertices in the subtree of `v` when the represented tree is rooted at `root`. | `O(C)` |
| `std::vector<int> subtree_vertices(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the rooted subtree. | `O(C)` |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | `O(C)` |
| `T subtree_prod(root, v)` | Acted-monoid value product of the rooted subtree. | `O(C + S log N)` |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | `O(C + S log N)` |
| `void apply_subtree(root, v, f)` | Applies `f` to every link-cut-tree vertex in the rooted subtree. | `O(C + S log N)` |
| `void apply_subtree(v, f)` | Uses the current represented root of `v`'s component. | `O(C + S log N)` |

Here `C` is the number of link-cut-tree vertices in the connected component and
`S` is the number of vertices in the requested subtree.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree_with_subtree.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::LazyLinkCutTreeWithSubtree<AM> lct(std::vector<long long>{1, 2, 3, 4, 5});

    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(1, 3);
    lct.link(3, 4);

    lct.apply(2, 4, 10);
    std::cout << lct.path_prod(2, 4).sum << "\n";     // 54
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 54

    lct.apply_subtree(0, 1, 5);
    std::cout << lct.subtree_prod(0, 1).sum << "\n";  // 74
}
```

## Notes

For non-commutative value monoids, subtree products use deterministic preorder:
visit the subtree root first, then active incident edges in link order.

The subtree layer is traversal-based by design. With the current acted-monoid
interface, a path lazy update cannot be applied to a cached subtree aggregate
without also updating virtual side subtrees that are not on the path. Visiting
the requested subtree keeps the semantics simple and correct for general acted
monoids.
