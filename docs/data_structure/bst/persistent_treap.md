---
title: Persistent Treap
documentation_of: ../../../data_structure/persistent_treap.hpp
---

## Overview

A persistent version of the Treap data structure. Each modifying operation (e.g., `insert`, `erase`) does not change the original treap but instead returns a new treap representing the state after the modification. This is highly effective for problems involving versioning or querying historical states of a dataset.

## Methods

* `persistent_treap()`

  Constructs an empty persistent treap.

  Time complexity: $O(1)$.

* `persistent_treap insert(T key)`

  Returns a new treap with the element `key` inserted.
  
  Time complexity: $O(\log N)$.

* `persistent_treap erase(T key)`

  Returns a new treap with the element `key` removed.
  
  Time complexity: $O(\log N)$.

* `bool contains(T key)`

  Returns `true` if `key` is in the treap, `false` otherwise.
  
  Time complexity: $O(\log N)$.

* `std::optional<T> lower_bound(T key)`

  Returns the smallest element that is greater than or equal to `key`. Returns `std::nullopt` if no such element exists.
  
  Time complexity: $O(\log N)$.

* `std::optional<T> upper_bound(T key)`

  Returns the smallest element that is strictly greater than `key`. Returns `std::nullopt` if no such element exists.
  
  Time complexity: $O(\log N)$.

* `T find_by_order(int k)`

  Returns the k-th smallest element (0-indexed). `k` must be in the range `[0, size())`.
  
  Time complexity: $O(\log N)$.

* `int order_of_key(T key)`

  Returns the number of elements strictly less than `key`.
  
  Time complexity: $O(\log N)$.

* `int size()`

  Returns the number of elements in the treap.
  
  Time complexity: $O(1)$.
