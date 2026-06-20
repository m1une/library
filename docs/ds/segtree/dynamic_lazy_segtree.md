---
title: Dynamic Lazy Segment Tree
documentation_of: ../../../ds/segtree/dynamic_lazy_segtree.hpp
---

## Overview

`m1une::ds::DynamicLazySegtree` is a sparse lazy segment tree over a fixed
integer coordinate domain. It supports point assignment, range updates, range
products, and boundary searches without allocating a dense array for the whole
domain.

Nodes use one contiguous pool and are created only for segments touched by an
update or assignment. Read-only operations do not push lazy tags or allocate
nodes.

## Untouched Coordinates

Every coordinate starts with the same `initial_value`. The tree computes the
monoid product of untouched segments from that leaf value. This detail matters
for size-aware acted monoids:

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::DynamicLazySegtree<AM> seg(0, 1'000'000'000LL, AM::make(0));
```

`AM::make(0)` represents one zero-valued element. In contrast, `AM::id()` has
size zero and represents an empty product, so range additions would not affect
untouched coordinates.

Products preserve coordinate order, so non-commutative value monoids are
supported when the acted-monoid laws hold.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

Position-dependent operators may additionally provide `op_shift(f, offset)`,
with the same semantics used by `LazySegtree`. Existing shifted acted monoids
use a `long long` offset, so every applied interval length must fit in
`long long` when `op_shift` is present.

## Construction

* `DynamicLazySegtree()`: creates an empty domain `[0, 0)`.
* `DynamicLazySegtree(Index n)`: creates `[0, n)` with initial leaf
  `ActedMonoid::id()`.
* `DynamicLazySegtree(Index left, Index right)`: creates `[left, right)` with
  initial leaf `ActedMonoid::id()`.
* `DynamicLazySegtree(Index left, Index right, T initial_value)`: creates a
  domain with the specified uniform initial leaf.

Construction precomputes untouched products for the possible segment lengths
at each depth. It uses $O(\log U)$ memory and $O(\log^2 U)$ monoid operations,
where $U$ is the number of coordinates.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the coordinate domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the domain's left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the domain's right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves space for `n` allocated nodes. | $O(K)$ |
| `size_t node_count()` | Returns the number of allocated nodes. | $O(1)$ |
| `void clear()` | Restores the uniform initial state while retaining capacity. | $O(K)$ |
| `void set(Index p, T x)` | Assigns `x` to coordinate `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the value-monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `void apply(Index p, F f)` | Applies `f` at one coordinate. | $O(\log U)$ |
| `void apply(Index l, Index r, F f)` | Applies `f` over `[l, r)`. | $O(\log U)$ |
| `Index max_right(Index l, G g)` | Finds the largest `r` for which `g(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, G g)` | Finds the smallest `l` for which `g(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ is the current number of allocated nodes. After $Q$ updates, memory
usage is $O(Q \log U)$ in the worst case. `max_right` and `min_left` require the
same predicate conditions as `LazySegtree`: the identity must satisfy the
predicate, and the predicate must be monotone along searched products.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/dynamic_lazy_segtree.hpp"

#include <iostream>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::DynamicLazySegtree<AM>;

    Seg seg(-1'000'000'000LL, 1'000'000'001LL, AM::make(0));
    seg.reserve(512);

    seg.apply(-20, 30, 5);
    seg.set(0, AM::make(100));

    std::cout << seg.prod(-10, 10).sum << "\n";  // 195
}
```
