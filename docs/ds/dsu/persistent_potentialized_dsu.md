---
title: Persistent Potentialized DSU
documentation_of: ../../../ds/dsu/persistent_potentialized_dsu.hpp
---

## Overview

`PersistentPotentializedDsu` is a persistent weighted Union-Find over a
commutative group. Merge operations return a new version and leave the old
version available, while preserving potential differences inside each component.

The template parameter is a type satisfying
`m1une::monoid::IsCommutativeGroup`. The stored constraint for
`merge(a, b, w)` is `diff(a, b) == w`, where `diff(a, b)` is
`Group::op(Group::inv(potential(a)), potential(b))`.

For `m1une::monoid::Add<long long>`, this means:

```cpp
potential(b) - potential(a) == w
```

Absolute values returned by `potential(v)` are root-relative. Use `diff(a, b)`
for stable values.

## Complexity Notation

* `N` is the number of elements.

## Template Parameters

* `Group`: A type satisfying `m1une::monoid::IsCommutativeGroup`.

The group value type must be equality comparable so repeated constraints can be
checked for consistency.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentPotentializedDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PersistentPotentializedDsu(int n)` | Creates `n` singleton sets with identity potentials. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `std::pair<PersistentPotentializedDsu, bool> merge(int a, int b, const T& w) const` | Returns a new version with the constraint `diff(a, b) == w`, and whether the constraint is consistent. If the constraint contradicts an existing component, the returned version is unchanged. | $O(\log^2 N)$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | $O(\log^2 N)$ |
| `int leader(int a) const` | Returns the representative of the set containing `a`. | $O(\log^2 N)$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the size of the set containing `a`. | $O(\log^2 N)$ |
| `T potential(int a) const` | Returns the root-relative potential of `a`. | $O(\log^2 N)$ |
| `T diff(int a, int b) const` | Returns the potential difference from `a` to `b`. Requires `same(a, b)`. | $O(\log^2 N)$ |
| `Value get(int p) const` | Returns the internal value at index `p`. It has `parent_or_size` and `diff_to_parent` members. | $O(\log N)$ |
| `int parent_or_size(int p) const` | Returns the internal parent-or-size value at index `p`. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \log^2 N)$ |

## Example

```cpp
#include "ds/dsu/persistent_potentialized_dsu.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;

    Dsu dsu(3);

    auto [a, ok1] = dsu.merge(0, 1, 3);
    auto [b, ok2] = a.merge(1, 2, 4);
    auto [bad, ok3] = b.merge(0, 2, 8);

    std::cout << ok1 << "\n";          // 1
    std::cout << ok2 << "\n";          // 1
    std::cout << ok3 << "\n";          // 0
    std::cout << dsu.same(0, 2) << "\n"; // 0
    std::cout << b.diff(0, 2) << "\n"; // 7
}
```
