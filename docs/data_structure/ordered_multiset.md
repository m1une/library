---
title: Ordered Multiset
documentation_of: ../../data_structure/ordered_multiset.hpp
---

## Overview

`OrderedMultiset` is a randomized binary search tree for multisets. It stores equal keys as one node with a multiplicity, so it supports standard multiset operations plus order-statistics queries such as k-th element and rank.

Pointers returned by bound and predecessor/successor methods remain valid until the multiset is modified.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

## Constructors

* `OrderedMultiset()`
  Constructs an empty multiset. ($O(1)$)

* `OrderedMultiset(Compare compare)`
  Constructs an empty multiset with a custom comparator. ($O(1)$)

* `OrderedMultiset(std::initializer_list<T> init)`
  Constructs a multiset from an initializer list. ($O(N \log N)$)

* `OrderedMultiset(Iterator first, Iterator last)`
  Constructs a multiset from a range. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the total number of elements, including duplicates. | $O(1)$ |
| `int unique_size() const` | Returns the number of distinct keys. | $O(1)$ |
| `bool empty() const` | Returns whether the multiset is empty. | $O(1)$ |
| `void clear()` | Removes all elements. | $O(1)$ |
| `void insert(T key, int multiplicity = 1)` | Inserts `multiplicity` copies of `key`. | $O(\log N)$ |
| `bool erase_one(const T& key)` | Removes one copy of `key`; returns whether an element was removed. | $O(\log N)$ |
| `bool erase(const T& key)` | Alias for `erase_one(key)`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Removes all copies of `key` and returns the number removed. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns the multiplicity of `key`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest element. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest element by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of elements strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of elements less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of elements strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of elements greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest element greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest element strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest element less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest element strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum element, or `nullptr` if the multiset is empty. | $O(\log N)$ |
| `std::vector<T> to_vector() const` | Returns all elements in sorted order, including duplicates. | $O(N)$ |

## Example

```cpp
#include "data_structure/ordered_multiset.hpp"

#include <iostream>

int main() {
    m1une::data_structure::OrderedMultiset<int> ms = {3, 1, 3, 5};

    ms.insert(2);
    ms.erase_one(3);

    std::cout << ms.kth(2) << "\n";           // 3
    std::cout << ms.order_of_key(4) << "\n";  // 3

    if (auto p = ms.max_le(4)) {
        std::cout << *p << "\n";              // 3
    }
}
```
