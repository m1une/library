---
title: Stern-Brocot Tree
documentation_of: ../../math/stern_brocot_tree.hpp
---

## Overview

The Stern-Brocot tree contains every positive reduced rational exactly once.
It is useful when rational numbers must be handled by their position in the
tree instead of by floating point values: comparing continued-fraction-like
paths, finding the lowest common ancestor of two fractions, walking to a
parent/child, or representing a whole interval of fractions by one node.

The root is `1/1`. Each node represents the mediant of two boundary fractions
`L` and `R`; the left child replaces the right boundary by the current fraction,
and the right child replaces the left boundary by the current fraction.

This library stores a path from the root in run-length form, such as `L^3 R^2`,
rather than one direction per edge. Encoding a fraction is essentially the
Euclidean algorithm, so very deep paths such as `1/10^18` are represented by one
run instead of `10^18 - 1` individual moves.

All fraction-returning operations use `Rational<T>`.

## Model

The root path is empty and decodes to `1/1`.

For a path, `stern_brocot_bounds(path)` returns the open interval containing
exactly the fractions in the subtree rooted at that path. Boundaries are stored
as `(numerator, denominator)` pairs because the right boundary of the whole
tree is positive infinity, represented by `1/0`.

For example, the path to `5/3` is `R L^2`:

```text
1/1 --R--> 2/1 --L--> 3/2 --L--> 5/3
```

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

`push` accepts `count = 0` and does nothing. A valid stored run has positive
count; decoding or bound construction returns `nullopt` if a zero-count run is
manually inserted.

## Functions

All functions are in namespace `m1une::math`. Template parameter `T` must be a
signed integer type, such as `int`, `long long`, or `__int128_t`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class T>`<br>`SternBrocotPath stern_brocot_path(T p, T q)` | Encodes the positive reduced fraction `p/q`. | `O(log max(p,q))` runs |
| `template<class T = long long>`<br>`std::optional<Rational<T>> stern_brocot_decode(const SternBrocotPath& path)` | Decodes a path, or returns `nullopt` on overflow. | `O(number of runs)` |
| `template<class T>`<br>`uint64_t stern_brocot_depth(T p, T q)` | Returns the expanded tree depth. | `O(log max(p,q))` |
| `SternBrocotPath stern_brocot_lca_path(const SternBrocotPath& a, const SternBrocotPath& b)` | Returns the compressed common path prefix. | `O(number of runs)` |
| `template<class T>`<br>`Rational<T> stern_brocot_lca(T a, T b, T c, T d)` | Returns the LCA of `a/b` and `c/d`. | `O(log max values)` |
| `template<class T>`<br>`std::optional<Rational<T>> stern_brocot_ancestor(T p, T q, uint64_t up)` | Returns an ancestor or `nullopt` above the root. | `O(number of runs)` |
| `template<class T>`<br>`std::optional<Rational<T>> stern_brocot_parent(T p, T q)` | Returns the parent, or `nullopt` for `1/1`. | `O(log max(p,q))` |
| `template<class T>`<br>`std::optional<Rational<T>> stern_brocot_move(T p, T q, SternBrocotDirection direction, uint64_t count = 1)` | Descends repeatedly, or returns `nullopt` on overflow. | `O(log max(p,q))` |
| `template<class T = long long>`<br>`std::optional<SternBrocotBounds<T>> stern_brocot_bounds(const SternBrocotPath& path)` | Returns the open interval boundaries of the path subtree. | `O(number of runs)` |

Here `O(log max(p,q))` means the number of Euclidean divisions, not the expanded
tree depth. For example, `stern_brocot_path(1, 1000000000000000000)` creates one
run.

`SternBrocotBounds<T>` stores:

| Member | Type | Meaning |
| --- | --- | --- |
| `left` | `std::pair<T, T>` | Left boundary fraction `(numerator, denominator)`. |
| `right` | `std::pair<T, T>` | Right boundary fraction `(numerator, denominator)`. |

## Contracts and Overflow

Inputs to `stern_brocot_path` and functions that encode a fraction must satisfy:

- `p > 0`
- `q > 0`
- `gcd(p, q) = 1`

These conditions are asserted in debug builds.

Decoded numerators, denominators, and interval boundaries must fit in `T`.
Functions that may exceed `T` return `std::nullopt` instead of overflowing:

- `stern_brocot_decode<T>`
- `stern_brocot_ancestor`
- `stern_brocot_parent`
- `stern_brocot_move`
- `stern_brocot_bounds<T>`

`stern_brocot_lca` decodes a prefix of already-valid input fractions, so the
result also fits in the same type.

## Example

```cpp
#include "math/stern_brocot_tree.hpp"
#include <iostream>

int main() {
    auto path = m1une::math::stern_brocot_path(5LL, 3LL);
    std::cout << path.depth() << '\n';  // 3

    auto same = m1une::math::stern_brocot_decode<long long>(path);
    if (same) std::cout << *same << '\n';  // 5/3

    auto parent = m1une::math::stern_brocot_parent(5LL, 3LL);
    if (parent) std::cout << *parent << '\n';  // 3/2

    auto lca = m1une::math::stern_brocot_lca(5LL, 3LL, 7LL, 4LL);
    std::cout << lca << '\n';  // 3/2

    auto bounds = m1une::math::stern_brocot_bounds<long long>(path);
    if (bounds) {
        std::cout << bounds->left.first << '/' << bounds->left.second << '\n';    // 3/2
        std::cout << bounds->right.first << '/' << bounds->right.second << '\n';  // 2/1
    }
}
```

## Notes

- The order of paths is not lexicographic order of fractions. Use this library
  when tree structure matters; use `Rational<T>` comparisons when numeric order
  matters.
- The subtree interval is open: the boundary fractions themselves are not inside
  the subtree.
- Run-length paths make ancestor and LCA operations fast even for fractions with
  enormous expanded depth.
