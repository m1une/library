---
title: Dynamic Dual Segment Tree
documentation_of: ../../../ds/segtree/dynamic_dual_segtree.hpp
---

## Overview

`m1une::ds::DynamicDualSegtree` is a sparse dual segment tree for range monoid
updates and point queries over a fixed integer coordinate domain. It is useful
when the domain is large but range products are unnecessary.

`apply(l, r, x)` changes each point value `v` in `[l, r)` to
`Monoid::op(x, v)`. Composition order is preserved for non-commutative monoids.
Nodes are stored in a contiguous pool and are allocated only for touched
segments. Point queries are read-only and allocate nothing.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

Every untouched coordinate has the uniform `initial_value`. The default is
`Monoid::id()`.

## Construction

* `DynamicDualSegtree()`: creates an empty domain `[0, 0)`.
* `DynamicDualSegtree(Index n)`: creates `[0, n)` with identity values.
* `DynamicDualSegtree(Index left, Index right)`: creates `[left, right)` with
  identity values.
* `DynamicDualSegtree(Index left, Index right, T initial_value)`: creates a
  domain with the specified uniform initial point value.

All constructors use $O(1)$ time and storage.

## Methods

Let $U$ be the number of coordinates and $K$ the number of allocated nodes.

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the coordinate domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial point value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves space for `n` allocated nodes. | $O(K)$ |
| `size_t node_count()` | Returns the number of allocated nodes. | $O(1)$ |
| `void clear()` | Restores the initial state while retaining pool capacity. | $O(K)$ |
| `void set(Index p, T x)` | Assigns `x` to coordinate `p` after earlier updates. | $O(\log U)$ |
| `T get(Index p)` | Returns the current value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `void apply(Index p, T x)` | Applies `x` to one coordinate. | $O(\log U)$ |
| `void apply(Index l, Index r, T x)` | Applies `x` over `[l, r)`. | $O(\log U)$ |

After $Q$ updates, memory usage is $O(Q \log U)$ in the worst case.

## Example

```cpp
#include "ds/segtree/dynamic_dual_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::DynamicDualSegtree<Add>;

    Seg seg(-1'000'000'000LL, 1'000'000'001LL, 0);
    seg.apply(-100, 200, 7);
    seg.apply(50, 60, 3);

    std::cout << seg.get(0) << "\n";   // 7
    std::cout << seg.get(55) << "\n";  // 10
}
```
