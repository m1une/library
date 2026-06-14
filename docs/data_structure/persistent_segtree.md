---
title: Persistent Segment Tree
documentation_of: ../../data_structure/persistent_segtree.hpp
---

## Overview

A persistent segment tree for any monoid satisfying `m1une::monoid::IsMonoid`.
Point updates return a new tree while keeping older versions available.

## Methods

* `PersistentSegtree(int n)`
  Initializes an array of size $n$ with the monoid identity. Time complexity: $O(N)$.

* `PersistentSegtree(const std::vector<T>& v)`
  Builds the tree from the given vector in $O(N)$ time.

* `int size()`
  Returns the number of elements. Time complexity: $O(1)$.

* `bool empty()`
  Returns whether the tree is empty. Time complexity: $O(1)$.

* `PersistentSegtree set(int p, T x)`
  Returns a new version where the $p$-th element is assigned $x$. Time complexity: $O(\log N)$.

* `T get(int p)`
  Returns the $p$-th element. Time complexity: $O(\log N)$.

* `T operator[](int p)`
  Returns the $p$-th element. Time complexity: $O(\log N)$.

* `T prod(int l, int r)`
  Returns the monoid product over $[l, r)$. Time complexity: $O(\log N)$.

* `T all_prod()`
  Returns the product of the entire array. Time complexity: $O(1)$.

* `std::vector<T> to_vector()`
  Returns all elements as a vector. Time complexity: $O(N)$.

* `std::vector<T> to_vector(int l, int r)`
  Returns the elements in $[l, r)$ as a vector. Time complexity: $O(\log N + r-l)$.

* `int max_right<F>(int l, F f)`
  Returns the largest index $r$ such that `f(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

* `int min_left<F>(int r, F f)`
  Returns the smallest index $l$ such that `f(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

## Example

```cpp
#include "data_structure/persistent_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Seg = m1une::data_structure::PersistentSegtree<m1une::monoid::Add<long long>>;

    Seg seg(std::vector<long long>{1, 2, 3});
    Seg next = seg.set(1, 10);

    std::cout << seg.prod(0, 3) << "\n";   // 6
    std::cout << next.prod(0, 3) << "\n";  // 14
}
```
