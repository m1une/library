---
title: Lazy Segment Tree
documentation_of: ../../data_structure/lazy_segtree.hpp
---

## Overview

A highly generic Lazy Segment Tree that supports both range queries and range updates (modifications) in $O(\log N)$ time. It operates on any Acted Monoid structure that satisfies the `m1une::acted_monoid::IsActedMonoid` concept.

## Template Parameters

* `ActedMonoid`: A struct representing the mathematical acted monoid, combining the `value_type`, `operator_type`, algebraic identities, internal operations, and the cross-mapping function.

## Methods

* `LazySegtree(int n)`
  Initializes an array of size $n$ with the value monoid's identity element. Time complexity: $O(N)$.

* `LazySegtree(const std::vector<T>& v)`
  Builds the lazy segment tree from the given vector in $O(N)$ time.

* `void set(int p, T x)`
  Assigns $x$ to the $p$-th element. Time complexity: $O(\log N)$.

* `T get(int p)`
  Returns the $p$-th element. Time complexity: $O(\log N)$.

* `T prod(int l, int r)`
  Returns the result of the monoid operation over the range $[l, r)$. Time complexity: $O(\log N)$.

* `T all_prod()`
  Returns the product of the entire array. Time complexity: $O(1)$.

* `void apply(int p, F f)`
  Applies the operator $f$ to the $p$-th element. Time complexity: $O(\log N)$.

* `void apply(int l, int r, F f)`
  Applies the operator $f$ to all elements in the range $[l, r)$. Time complexity: $O(\log N)$.

* `int max_right<G>(int l, G g)`
  Returns the largest index $r$ such that `g(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

* `int min_left<G>(int r, G g)`
  Returns the smallest index $l$ such that `g(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

int main() {
    int n = 6;
    std::vector<long long> v = {1, 3, 2, 5, 4, 0};

    // Use Range Add Range Min acted monoid
    using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;
    m1une::data_structure::LazySegtree<AM> seg(v);

    // Get min of range [1, 5) -> min(3, 2, 5, 4) = 2
    std::cout << seg.prod(1, 5) << "\n";

    // Add 10 to all elements in range [1, 4) -> v becomes {1, 13, 12, 15, 4, 0}
    seg.apply(1, 4, 10);

    // Get min of range [1, 5) -> min(13, 12, 15, 4) = 4
    std::cout << seg.prod(1, 5) << "\n";

    return 0;
}
```
