---
title: Potentialized DSU
documentation_of: ../../data_structure/potentialized_dsu.hpp
---

## Overview

`PotentializedDsu` is a weighted Union-Find over a commutative group. It stores
relative potentials inside each connected component and can answer potential
differences between two vertices.

The template parameter is a type satisfying
`m1une::monoid::IsCommutativeGroup`, so the same data structure works with
addition, xor, and other invertible commutative operations.

The main operation is `merge(a, b, w)`, which adds the constraint
`diff(a, b) == w`. Here `diff(a, b)` is defined as
`Group::op(Group::inv(potential(a)), potential(b))`.

For `m1une::monoid::Add<long long>`, this means:

```cpp
potential(b) - potential(a) == w
```

Equivalently, `diff(a, b)` is `b - a` for addition.

For `m1une::monoid::Xor<int>`, this means:

```cpp
potential(a) ^ potential(b) == w
```

Absolute values returned by `potential(v)` are root-relative and may shift when
components are merged. Use `diff(a, b)` for stable values.

## Template Parameters

* `Group`: A type satisfying `m1une::monoid::IsCommutativeGroup`.

The group must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`
* `static constexpr T inv(const T& x)`

`T` must be equality comparable so repeated constraints can be checked for
consistency.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PotentializedDsu(int n)` | Creates `n` singleton sets with identity potentials. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the DSU has no elements. | $O(1)$ |
| `bool merge(int a, int b, T w)` | Adds the constraint `diff(a, b) == w`. Returns `false` only when `a` and `b` were already connected and the constraint contradicts the stored potentials. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int group_size(int a)`, `int size(int a)` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `T potential(int a)` | Returns the root-relative potential of `a`. | Amortized $O(\alpha(N))$ |
| `T diff(int a, int b)` | Returns the potential difference from `a` to `b`. Requires `same(a, b)`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Example

```cpp
#include "data_structure/potentialized_dsu.hpp"
#include "monoid/add.hpp"
#include "monoid/xor.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    m1une::data_structure::PotentializedDsu<Add> add_dsu(3);

    add_dsu.merge(0, 1, 3);
    add_dsu.merge(1, 2, 4);

    std::cout << add_dsu.diff(0, 2) << "\n";  // 7
    std::cout << add_dsu.merge(0, 2, 8) << "\n";  // 0, contradiction

    using Xor = m1une::monoid::Xor<int>;
    m1une::data_structure::PotentializedDsu<Xor> xor_dsu(3);

    xor_dsu.merge(0, 1, 5);
    xor_dsu.merge(1, 2, 6);

    std::cout << xor_dsu.diff(0, 2) << "\n";  // 3
}
```
