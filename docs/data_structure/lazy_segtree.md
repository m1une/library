---
title: Lazy Segment Tree
documentation_of: ../../data_structure/lazy_segtree.hpp
---

## Overview

`m1une::data_structure::LazySegtree` is a generic lazy segment tree for range
queries and range updates. It is parameterized by an acted monoid: one monoid
describes how values are combined for queries, and another monoid describes how
lazy update operators are composed.

Use it when updates affect a whole interval. For point updates only, `Segtree`
is simpler.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.

The acted monoid must provide:

* `using value_type = T`
* `using operator_type = F`
* `id()` and `op(a, b)` for query values
* `op_id()` and `op_comp(f, g)` for lazy operators
* `mapping(f, x)` to apply an operator to a value

Ready-made acted monoids are available in `acted_monoid/`.

## Construction

* `LazySegtree()`: creates an empty tree.
* `LazySegtree(int n)`: creates `n` elements initialized with
  `ActedMonoid::id()`.
* `LazySegtree(const std::vector<T>& v)`: builds from acted-monoid values.
* `LazySegtree(std::vector<T>&& v)`: builds from moved acted-monoid values.
* `LazySegtree(const std::vector<U>& v)`: builds from another value type when
  `ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or
  `static_cast<T>(value)` is available.

All non-empty constructors build the tree in $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Pushes pending lazy updates on the path and returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the value monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r - l) \log N)$ |
| `void apply(int p, F f)` | Applies operator `f` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, F f)` | Applies operator `f` to every element in `[l, r)`. | $O(\log N)$ |
| `int max_right<G>(int l, G g)` | Returns the largest `r` such that `g(prod(l, r))` is `true`. Requires `g(ActedMonoid::id())`. | $O(\log N)$ |
| `int min_left<G>(int r, G g)` | Returns the smallest `l` such that `g(prod(l, r))` is `true`. Requires `g(ActedMonoid::id())`. | $O(\log N)$ |

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> v = {1, 3, 2, 5, 4, 0};

    using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;
    m1une::data_structure::LazySegtree<AM> seg(v);

    std::cout << seg.prod(1, 5) << "\n";  // 2

    seg.apply(1, 4, 10);

    std::cout << seg.prod(1, 5) << "\n";  // 4

    return 0;
}
```
