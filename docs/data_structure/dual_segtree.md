---
title: Dual Segment Tree
documentation_of: ../../data_structure/dual_segtree.hpp
---

## Overview

`m1une::data_structure::DualSegtree` is a generic dual segment tree for range
updates and point queries. It is parameterized by an acted monoid and uses its
operator monoid for lazy tags and its `mapping` function to apply an operator to
one value.

Use it when you only need point queries after range updates. If you also need
range queries, use `LazySegtree` instead.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.

The acted monoid must provide:

* `using value_type = T`
* `using operator_type = F`
* `op_id()` and `op_comp(f, g)` for update operators
* `mapping(f, x)` to apply an operator to a value

The value monoid members required by `IsActedMonoid` are used for initialization
compatibility with the rest of the library. Ready-made acted monoids are
available in `acted_monoid/`.

## Construction

* `DualSegtree()`: creates an empty tree.
* `DualSegtree(int n)`: creates `n` elements initialized with
  `ActedMonoid::id()`.
* `DualSegtree(const std::vector<T>& v)`: builds from acted-monoid values.
* `DualSegtree(std::vector<T>&& v)`: builds from moved acted-monoid values.
* `DualSegtree(const std::vector<U>& v)`: builds from another value type when
  `ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or
  `static_cast<T>(value)` is available.

Construction takes $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Pushes pending updates on the path and assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Pushes pending updates on the path and returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `void apply(int p, F f)` | Applies operator `f` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, F f)` | Applies operator `f` to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r-l)\log N)$ |

## Example

```cpp
#include "data_structure/dual_segtree.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::DualSegtree<AM> seg(std::vector<long long>{1, 2, 3, 4});

    seg.apply(1, 4, 10);

    std::cout << seg.get(0).sum << "\n";  // 1
    std::cout << seg.get(2).sum << "\n";  // 13

    return 0;
}
```
