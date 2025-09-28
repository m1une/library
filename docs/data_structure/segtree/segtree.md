---
title: Segment Tree
documentation_of: ../../../data_structure/segtree/segtree.hpp
---

## Overview

A segment tree is a versatile data structure that allows for efficient range queries on an array. It can compute the result of any associative operation (defined by a monoid) over a given range `[l, r)` in logarithmic time. It also supports updating individual elements.

This implementation is generic and designed to be used with the monoid structures available in the library.

## Methods

* `segment_tree()`

  Constructs an empty segment tree.

  Time complexity: $O(1)$.

* `explicit segment_tree(int n)`

  Constructs a segment tree of size `n`, initialized with the identity element of the monoid.

  Time complexity: $O(N)$.

* `explicit segment_tree(const std::vector<T>& v)`

  Constructs a segment tree from an initial vector `v`.

  Time complexity: $O(N)$.

* `void set(int p, T x)`

  Sets the value at position `p` (0-indexed) to `x`.

  Time complexity: $O(\log N)$.

* `T get(int p) const`

  Returns the value at position `p` (0-indexed).

  Time complexity: $O(1)$.

* `T prod(int l, int r) const`

  Calculates the result of the monoid operation on the range `[l, r)` (0-indexed, half-open interval).

  Time complexity: $O(\log N)$.

* `T all_prod() const`

  Calculates the result of the monoid operation on the entire range `[0, n)`.

  Time complexity: $O(1)$.

* `int max_right(int l, auto f) const`

  Finds the largest `r` such that `l <= r <= n` and the predicate `f(prod(l, r))` is true. `f` must be a function that takes a monoid value and returns a boolean.

  Time complexity: $O(\log N)$.

* `int min_left(int r, auto f) const`

  Finds the smallest `l` such that `0 <= l <= r` and the predicate `f(prod(l, r))` is true. `f` must be a function that takes a monoid value and returns a boolean.

  Time complexity: $O(\log N)$.
