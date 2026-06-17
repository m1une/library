---
title: Lazy Linked-Cut Tree
documentation_of: ../../data_structure/lazy_linked_cut_tree.hpp
---

## Overview

`m1une::data_structure::LazyLinkedCutTree<ActedMonoid>` is the subtree
query companion to `LazyPathLinkCutTree`. It keeps the same dynamic path query and
path update interface, and adds rooted subtree queries.

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
    static T inverse(const T& x);

    static F op_id();
    static F op_comp(const F& f, const F& g);

    static T mapping(const F& f, const T& x);
};
```

`op` must be associative and commutative, `id()` must be its identity, and
`inverse(x)` must satisfy `op(x, inverse(x)) == id()`. As with
`LazyPathLinkCutTree`, `mapping` must distribute over `op`.

## Construction

```cpp
LazyLinkedCutTree<ActedMonoid> lct;
LazyLinkedCutTree<ActedMonoid> lct(n);
LazyLinkedCutTree<ActedMonoid> lct(values);
```

Construction and `add_vertex` follow `LazyPathLinkCutTree`.

## Methods

All `LazyPathLinkCutTree` methods are available with the same meaning:

* vertex and edge-node value access: `get`, `set`, `get_edge`, `set_edge`
* dynamic forest operations: `evert`, `link`, `link_edge`, `cut`, `cut_edge`
* connectivity and roots: `connected`, `same`, `component_root`, `lca`
* path queries and updates: `prod`, `path_prod`, `path_size`, `kth_vertex`,
  `apply`, `apply_edge`

Additional subtree methods:

| Method | Description | Complexity |
| --- | --- | --- |
| `int subtree_size(root, v)` | Number of link-cut-tree vertices in the subtree of `v` when rooted at `root`. | Amortized $O(\log N)$ |
| `int subtree_size(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |
| `T subtree_prod(root, v)` | Acted-monoid value product of the rooted subtree. | Amortized $O(\log N)$ |
| `T subtree_prod(v)` | Uses the current represented root of `v`'s component. | Amortized $O(\log N)$ |

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

## Notes

This structure supports lazy path updates, but it does not provide subtree
updates. A path update must not touch virtual side subtrees, so the
implementation keeps preferred-path values and virtual-subtree aggregates as
separate cached values.
