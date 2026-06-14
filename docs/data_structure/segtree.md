---
title: Segment Tree
documentation_of: ../../data_structure/segtree.hpp
---

## Overview

A highly generic Segment Tree that operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept. It allows for point updates and range queries in $O(\log N)$ time, as well as binary search on the tree (`max_right`, `min_left`) in $O(\log N)$ time.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`. You can find standard monoids in the `monoid/` directory.

## Methods

* `Segtree(int n)`
  Initializes an array of size $n$ with the monoid's identity element. Time complexity: $O(N)$.

* `Segtree(const std::vector<T>& v)`
  Builds the segment tree from the given vector in $O(N)$ time.

* `int size()`
  Returns the number of elements. Time complexity: $O(1)$.

* `bool empty()`
  Returns whether the tree is empty. Time complexity: $O(1)$.

* `void set(int p, T x)`
  Assigns $x$ to the $p$-th element. Time complexity: $O(\log N)$.

* `T get(int p)`
  Returns the $p$-th element. Time complexity: $O(1)$.

* `T operator[](int p)`
  Returns the $p$-th element. Time complexity: $O(1)$.

* `T prod(int l, int r)`
  Returns the result of the monoid operation over the range $[l, r)$. Time complexity: $O(\log N)$.

* `T all_prod()`
  Returns the product of the entire array. Time complexity: $O(1)$.

* `std::vector<T> to_vector()`
  Returns all elements as a vector. Time complexity: $O(N)$.

* `std::vector<T> to_vector(int l, int r)`
  Returns the elements in $[l, r)$ as a vector. Time complexity: $O(r-l)$.

* `int max_right<F>(int l, F f)`
  Returns the largest index $r$ such that `f(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

* `int min_left<F>(int r, F f)`
  Returns the smallest index $l$ such that `f(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>

int main() {
    int n = 5;
    m1une::data_structure::Segtree<m1une::monoid::Add<long long>> seg(n);

    seg.set(0, 10);
    seg.set(2, 20);

    // Get sum of range [0, 3) -> 10 + 0 + 20 = 30
    std::cout << seg.prod(0, 3) << "\n"; 

    return 0;
}
```
