---
title: Dynamic Segment Tree
documentation_of: ../../../ds/segtree/dynamic_segtree.hpp
---

## Overview

`m1une::ds::DynamicSegtree` is a sparse segment tree for point assignments and
monoid products over a large integer coordinate range. Unlike `Segtree`, it does
not allocate storage for every coordinate. A node is created only when `set`
first visits its segment, so a domain such as $[-10^{18}, 10^{18})$ is practical
when only a small number of positions are updated.

The implementation uses one contiguous node pool rather than a separate heap
allocation per node. Call `reserve` when the approximate number of nodes is
known to avoid vector reallocations.

By default, unassigned coordinates have value `Monoid::id()`. A uniform
arbitrary initial value can instead be supplied to the constructor. Products
preserve coordinate order, so non-commutative monoids are supported.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

## Construction

* `DynamicSegtree()`: creates an empty tree over `[0, 0)`.
* `DynamicSegtree(Index n)`: creates a tree over `[0, n)`.
* `DynamicSegtree(Index left, Index right)`: creates a tree over
  `[left, right)`.
* `DynamicSegtree(Index left, Index right, T initial_value)`: creates a tree
  over `[left, right)` with every coordinate initialized to `initial_value`.

The coordinate domain is fixed at construction. Construction caches untouched
products for the possible segment lengths at each depth, using $O(\log U)$
memory and $O(\log^2 U)$ monoid operations. It does not create tree nodes.

## Methods

Let $U$ be the number of integer coordinates in the domain.

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the number of coordinates as the unsigned counterpart of `Index`. | $O(1)$ |
| `bool empty()` | Returns whether the coordinate domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint of the domain. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint of the domain. | $O(1)$ |
| `const T& initial_value()` | Returns the value assigned to untouched coordinates. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for `n` allocated nodes, excluding the sentinel. | $O(K)$ |
| `size_t node_count()` | Returns the number of nodes allocated by updates. | $O(1)$ |
| `void clear()` | Restores every coordinate to the initial value and keeps pool capacity. | $O(K)$ to destroy stored node values |
| `void set(Index p, T x)` | Assigns `x` to coordinate `p`. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`, or the initial value if `p` was never assigned. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `Index max_right(Index l, F f)` | Returns the largest `r` for which `f(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, F f)` | Returns the smallest `l` for which `f(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ is the number of allocated nodes. After $Q$ assignments, memory usage
is $O(Q \log U)$ in the worst case. Updating an already allocated path does not
create more nodes.

For `max_right` and `min_left`, `f(Monoid::id())` must be true and `f` must be
monotone along the searched products, as with the ordinary `Segtree`.

## Example

```cpp
#include "ds/segtree/dynamic_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::DynamicSegtree<Sum>;

    Seg seg(-1'000'000'000LL, 1'000'000'001LL, 1);
    seg.reserve(256);

    seg.set(-500'000'000LL, 7);
    seg.set(900'000'000LL, 11);
    seg.set(-500'000'000LL, seg.get(-500'000'000LL) + 3);

    std::cout << seg.get(0) << "\n";                    // 1
    std::cout << seg.prod(-600'000'000LL, 0) << "\n";  // 600000009
}
```

## Notes

* `set` stores a monoid value directly. If the monoid has a `make` helper, call
  it before `set`.
* Assigning the identity does not reclaim nodes. `clear` releases all logical
  assignments at once and reuses the pool capacity.
* For versioned sparse point assignments and range products, use
  `PersistentDynamicSegtree`.
* For sparse range updates and range products, use `DynamicLazySegtree`. Its
  constructor accepts a uniform initial leaf so size-aware actions can account
  for untouched coordinates.
* For sparse range updates with point queries only, use `DynamicDualSegtree`.
