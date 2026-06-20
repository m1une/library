---
title: DSU with Monoid
documentation_of: ../../../ds/union_find/dsu_monoid.hpp
---

## Overview

`DsuMonoid` is a Disjoint Set Union that stores one monoid aggregate for each
connected component. Each singleton starts with its own value, and `merge(a, b)`
combines the aggregate of `a`'s component with the aggregate of `b`'s component.

The structure uses path compression and union by size, so DSU operations are
near constant time. The aggregate order is independent of the root chosen by
union by size: for noncommutative monoids, `merge(a, b)` stores
`Monoid::op(prod(a), prod(b))`.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

## Construction

* `DsuMonoid()`: creates an empty DSU.
* `DsuMonoid(int n)`: creates `n` singleton sets initialized with
  `Monoid::id()`.
* `DsuMonoid(int n, const T& value)`: creates `n` singleton sets initialized
  with `value`.
* `DsuMonoid(const std::vector<T>& v)`: creates singleton sets from monoid
  values.
* `DsuMonoid(std::vector<T>&& v)`: creates singleton sets from moved monoid
  values.
* `DsuMonoid(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
  is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the DSU has no elements. | $O(1)$ |
| `int merge(int a, int b)` | Merges the sets containing `a` and `b`; returns the leader of the merged set. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int group_size(int a)`, `int size(int a)` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `T prod(int a)`, `T get(int a)` | Returns the aggregate of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `void set(int a, T value)` | Replaces the aggregate of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Example

```cpp
#include "ds/union_find/dsu_monoid.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::DsuMonoid<Sum> dsu(std::vector<long long>{1, 2, 3, 4, 5});

    dsu.merge(0, 1);
    dsu.merge(2, 3);
    dsu.merge(1, 2);

    std::cout << dsu.prod(0) << "\n";  // 10
    std::cout << dsu.size(0) << "\n";  // 4
    std::cout << dsu.prod(4) << "\n";  // 5
}
```
