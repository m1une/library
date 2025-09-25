---
title: Treap
documentation_of: ../../data_structure/treap.hpp
---

A randomized binary search tree that provides the functionality of an ordered set. It maintains the binary search tree property with respect to its keys and the heap property with respect to randomly assigned priorities. This combination ensures that the tree remains balanced with high probability.

### Methods

* `treap()`

  Constructs an empty treap.

  Time complexity: $O(1)$.

* `void insert(T key)`

  Inserts an element `key` into the treap. Does nothing if the key already exists.
  
  Time complexity: $O(\log N)$.

* `void erase(T key)`

  Removes the element `key` from the treap. Does nothing if the key does not exist.
  
  Time complexity: $O(\log N)$.

* `bool contains(T key)`

  Returns `true` if `key` is in the treap, `false` otherwise.
  
  Time complexity: $O(\log N)$.

* `T* lower_bound(T key)`

  Returns a pointer to the smallest element that is greater than or equal to `key`. Returns `nullptr` if no such element exists.
  
  Time complexity: $O(\log N)$.

* `T* upper_bound(T key)`

  Returns a pointer to the smallest element that is strictly greater than `key`. Returns `nullptr` if no such element exists.
  
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
