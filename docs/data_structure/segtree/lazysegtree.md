---
title: Lazy Segment Tree
documentation_of: ../../../data_structure/segtree/lazysegtree.hpp
---

## Overview

A lazy segment tree is an advanced data structure that extends the functionality of a regular segment tree. It supports both range queries and range updates in logarithmic time. This is achieved by "lazily" propagating updates down the tree, applying them only when necessary.

This implementation is generic and designed to be used with the `acted_monoid` structures available in the library, which define the data, the actions, and the mapping between them.

## Methods

* `lazy_segment_tree()`

    Constructs an empty lazy segment tree.

    **Time complexity:** $O(1)$.

* `explicit lazy_segment_tree(int n)`

    Constructs a lazy segment tree of size `n`, initialized with the identity element of the data monoid.

    **Time complexity:** $O(N)$.

* `explicit lazy_segment_tree(const std::vector<S>& v)`

    Constructs a lazy segment tree from an initial vector `v`.

    **Time complexity:** $O(N)$.

* `void set(int p, S x)`

    Sets the value at position `p` (0-indexed) to `x`.

    **Time complexity:** $O(\log N)$.

* `S get(int p)`

    Returns the value at position `p` (0-indexed).

    **Time complexity:** $O(\log N)$.

* `S prod(int l, int r)`

    Calculates the result of the data monoid operation on the range `[l, r)` (0-indexed, half-open interval).

    **Time complexity:** $O(\log N)$.

* `S all_prod()`

    Calculates the result of the data monoid operation on the entire range `[0, n)`.

    **Time complexity:** $O(1)$.

* `void apply(int p, F f)`

    Applies the action `f` to the element at position `p` (0-indexed).

    **Time complexity:** $O(\log N)$.

* `void apply(int l, int r, F f)`

    Applies the action `f` to all elements in the range `[l, r)` (0-indexed, half-open interval).

    **Time complexity:** $O(\log N)$.

* `int max_right(int l, auto g)`

    Finds the largest `r` such that `l <= r <= n` and the predicate `g(prod(l, r))` is true. `g` must be a function that takes a data monoid value and returns a boolean.

    **Time complexity:** $O(\log N)$.

* `int min_left(int r, auto g)`

    Finds the smallest `l` such that `0 <= l <= r` and the predicate `g(prod(l, r))` is true. `g` must be a function that takes a data monoid value and returns a boolean.

    **Time complexity:** $O(\log N)$.
