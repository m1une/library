---
title: Ordered Set
documentation_of: ../../data_structure/ordered_set.hpp
---

## Overview

`OrderedSet` is a randomized binary search tree for sets. It keeps unique keys only, like `std::set`, and also supports order-statistics queries such as k-th element and rank.

Pointers returned by bound and predecessor/successor methods remain valid until the set is modified.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

## Constructors

* `OrderedSet()`
  Constructs an empty set. ($O(1)$)

* `OrderedSet(Compare compare)`
  Constructs an empty set with a custom comparator. ($O(1)$)

* `OrderedSet(std::initializer_list<T> init)`
  Constructs a set from an initializer list. Duplicate keys are ignored. ($O(N \log N)$)

* `OrderedSet(Iterator first, Iterator last)`
  Constructs a set from a range. Duplicate keys are ignored. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of keys. | $O(1)$ |
| `int unique_size() const` | Alias for `size()`. | $O(1)$ |
| `bool empty() const` | Returns whether the set is empty. | $O(1)$ |
| `void clear()` | Removes all keys. | $O(1)$ |
| `bool insert(T key)` | Inserts `key`; returns whether a new key was inserted. | $O(\log N)$ |
| `bool erase(const T& key)` | Removes `key`; returns whether a key was removed. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns `1` if `key` exists, otherwise `0`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest key. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest key by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of keys strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of keys less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of keys strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of keys greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest key greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest key strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest key less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest key strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum key, or `nullptr` if the set is empty. | $O(\log N)$ |
| `std::vector<T> to_vector() const` | Returns all keys in sorted order. | $O(N)$ |

## Example

```cpp
#include "data_structure/ordered_set.hpp"

#include <iostream>

int main() {
    m1une::data_structure::OrderedSet<int> st = {3, 1, 3, 5};

    st.insert(2);
    st.erase(3);

    std::cout << st.kth(1) << "\n";           // 2
    std::cout << st.order_of_key(5) << "\n";  // 2

    if (auto p = st.max_le(4)) {
        std::cout << *p << "\n";              // 2
    }
}
```
