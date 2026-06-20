---
title: Persistent Dynamic Dual Segment Tree
documentation_of: ../../../ds/segtree/persistent_dynamic_dual_segtree.hpp
---

## Overview

`m1une::ds::PersistentDynamicDualSegtree` is a persistent sparse dual segment
tree for range monoid updates and point queries. Each assignment or update
returns a new version while preserving every earlier version.

`apply(l, r, x)` changes each point value `v` in `[l, r)` to
`Monoid::op(x, v)`. This order is preserved for non-commutative monoids.
Untouched coordinates have one uniform `initial_value`.

Versions derived from the same root share a contiguous node pool. Queries do
not push tags, mutate versions, or allocate nodes.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

## Construction

* `PersistentDynamicDualSegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicDualSegtree(Index n)`: creates `[0, n)` with identity
  values.
* `PersistentDynamicDualSegtree(Index left, Index right)`: creates
  `[left, right)` with identity values.
* `PersistentDynamicDualSegtree(Index left, Index right, T initial_value)`:
  creates a domain with the specified uniform initial point value.

Construction takes $O(1)$ time and storage.

## Methods

Let $U$ be the domain length and $K$ the number of nodes allocated by the shared
version family.

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial point value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns total nodes allocated across shared versions. | $O(1)$ |
| `PersistentDynamicDualSegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the current value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `PersistentDynamicDualSegtree apply(Index p, T x)` | Returns a version applying `x` at `p`. | $O(\log U)$ |
| `PersistentDynamicDualSegtree apply(Index l, Index r, T x)` | Returns a version applying `x` over `[l, r)`. | $O(\log U)$ |

Each new update allocates $O(\log U)$ nodes in the worst case. Copying a
version is $O(1)$.

## Example

```cpp
#include "ds/segtree/persistent_dynamic_dual_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, 0);
    Seg first = base.apply(-100, 200, 7);
    Seg second = first.apply(50, 60, 3);

    std::cout << base.get(55) << "\n";    // 0
    std::cout << first.get(55) << "\n";   // 7
    std::cout << second.get(55) << "\n";  // 10
}
```
