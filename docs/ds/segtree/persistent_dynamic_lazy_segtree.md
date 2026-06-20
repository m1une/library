---
title: Persistent Dynamic Lazy Segment Tree
documentation_of: ../../../ds/segtree/persistent_dynamic_lazy_segtree.hpp
---

## Overview

`m1une::ds::PersistentDynamicLazySegtree` combines persistence, sparse
allocation, and lazy propagation over a fixed integer coordinate domain.
Assignments and range updates return new versions; previous versions remain
queryable.

Every coordinate begins with one uniform `initial_value`. Untouched segment
products are derived from that leaf without building the segment. For
size-aware acted monoids, pass a real leaf value such as
`RangeAddRangeSum<long long>::make(0)`, not the empty-product identity.

All versions derived from one tree share a contiguous node pool and immutable
domain metadata. Read-only queries allocate no nodes.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

Position-dependent acted monoids may provide `op_shift(f, offset)`. Existing
shifted acted monoids accept `long long`, so applied interval lengths must fit
in that type.

## Construction

* `PersistentDynamicLazySegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicLazySegtree(Index n)`: creates `[0, n)` with initial leaf
  `ActedMonoid::id()`.
* `PersistentDynamicLazySegtree(Index left, Index right)`: creates
  `[left, right)` with initial leaf `ActedMonoid::id()`.
* `PersistentDynamicLazySegtree(Index left, Index right, T initial_value)`:
  creates a domain with the specified uniform initial leaf.

Construction uses $O(\log U)$ metadata and $O(\log^2 U)$ monoid operations to
cache untouched products, where $U$ is the domain length. No tree node is
allocated initially.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns total nodes allocated across the shared version family. | $O(1)$ |
| `PersistentDynamicLazySegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `PersistentDynamicLazySegtree apply(Index p, F f)` | Returns a version applying `f` at `p`. | $O(\log U)$ |
| `PersistentDynamicLazySegtree apply(Index l, Index r, F f)` | Returns a version applying `f` over `[l, r)`. | $O(\log U)$ |
| `Index max_right(Index l, G g)` | Finds the largest valid right boundary. | $O(\log U)$ |
| `Index min_left(Index r, G g)` | Finds the smallest valid left boundary. | $O(\log U)$ |

Here $K$ counts allocations made by every version sharing the pool. Each new
update allocates $O(\log U)$ nodes in the worst case. Copying a version is
$O(1)$.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/persistent_dynamic_lazy_segtree.hpp"

#include <iostream>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, AM::make(0));
    Seg first = base.apply(-10, 20, 5);
    Seg second = first.set(0, AM::make(100));

    std::cout << base.all_prod().sum << "\n";    // 0
    std::cout << first.all_prod().sum << "\n";   // 150
    std::cout << second.all_prod().sum << "\n";  // 245
}
```
