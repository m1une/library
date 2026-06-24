---
title: Stern-Brocot Tree
documentation_of: ../../math/stern_brocot_tree.hpp
---

## Overview

The Stern-Brocot tree contains every positive reduced rational exactly once.
Its root is `1/1`. Moving left or right replaces the current fraction with the
corresponding mediant child.

This library stores a path in run-length form, such as `L^3 R^2`, rather than
one direction per edge. Encoding a fraction uses the Euclidean algorithm, so
very deep paths such as `1/10^18` remain compact.

All fraction-returning operations use `Rational<T>`.

## Path Types

`SternBrocotDirection` has values `Left` and `Right`.

`SternBrocotRun` stores a direction and positive repetition count.

`SternBrocotPath` exposes:

| Method | Description |
| --- | --- |
| `bool empty() const` | Whether the path denotes the root. |
| `uint64_t depth() const` | Expanded edge count. |
| `void push(direction, count)` | Appends moves and merges equal adjacent directions. |
| `bool move_up(count)` | Removes edges; returns false if the ancestor is above the root. |
| `SternBrocotPath ancestor(count) const` | Returns an ancestor path; requires sufficient depth. |

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `stern_brocot_path(p, q)` | Encodes the positive reduced fraction `p/q`. | `O(log max(p,q))` runs |
| `stern_brocot_decode<T>(path)` | Decodes a path, or returns `nullopt` on overflow. | `O(number of runs)` |
| `stern_brocot_depth(p, q)` | Returns the expanded tree depth. | `O(log max(p,q))` |
| `stern_brocot_lca_path(a, b)` | Returns the compressed common path prefix. | `O(number of runs)` |
| `stern_brocot_lca(a, b, c, d)` | Returns the LCA of `a/b` and `c/d`. | `O(log max values)` |
| `stern_brocot_ancestor(p, q, up)` | Returns an ancestor or `nullopt` above the root. | `O(number of runs)` |
| `stern_brocot_parent(p, q)` | Returns the parent, or `nullopt` for `1/1`. | `O(log max(p,q))` |
| `stern_brocot_move(p, q, direction, count)` | Descends repeatedly, or returns `nullopt` on overflow. | `O(log max(p,q))` |
| `stern_brocot_bounds<T>(path)` | Returns the open interval boundaries of the path subtree. | `O(number of runs)` |

Inputs to `stern_brocot_path` must be positive and coprime. This is asserted in
debug builds through the Euclidean reduction ending at one.

Bounds are stored as `(numerator, denominator)` pairs because the root's right
boundary is positive infinity, represented by `1/0`.

The final numerator and denominator must fit in `T`. Decoding, movement, and
bound construction return `nullopt` if they do not.

## Example

```cpp
#include "math/stern_brocot_tree.hpp"
#include <iostream>

int main() {
    auto path = m1une::math::stern_brocot_path(5LL, 3LL);
    std::cout << path.depth() << '\n';  // 3

    auto parent = m1une::math::stern_brocot_parent(5LL, 3LL);
    if (parent) std::cout << *parent << '\n';  // 3/2

    auto lca = m1une::math::stern_brocot_lca(5LL, 3LL, 7LL, 4LL);
    std::cout << lca << '\n';
}
```
