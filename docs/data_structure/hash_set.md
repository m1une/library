---
title: Hash Set
documentation_of: ../../data_structure/hash_set.hpp
---

## Overview

`HashSet` is a flat open-addressing hash set. It is intended as a faster and more hack-resistant replacement for `std::unordered_set` in competitive programming.

Hashes are passed through a salted splitmix64 mixer, which helps avoid adversarial collisions for common integral keys. The table uses linear probing and rebuilds before the load factor reaches about 70%.

Pointers returned by `find` remain valid until the set is modified.

## Template Parameters

* `T`: The key type.
* `Hash`: Hash function. Defaults to `std::hash<T>`.
* `KeyEqual`: Equality predicate. Defaults to `std::equal_to<T>`.

## Constructors

* `HashSet()`
  Constructs an empty set. ($O(1)$)

* `HashSet(std::size_t reserve_count)`
  Constructs an empty set with enough buckets for about `reserve_count` keys. ($O(1)$)

* `HashSet(std::initializer_list<T> init)`
  Constructs a set from an initializer list. Duplicate keys are ignored. Expected $O(N)$

* `HashSet(Iterator first, Iterator last)`
  Constructs a set from a range. Duplicate keys are ignored. Expected $O(N)$

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of keys. | $O(1)$ |
| `bool empty() const` | Returns whether the set is empty. | $O(1)$ |
| `std::size_t bucket_count() const` | Returns the number of buckets. | $O(1)$ |
| `double load_factor() const` | Returns `size() / bucket_count()`. | $O(1)$ |
| `void clear()` | Removes all keys. | $O(B)$ |
| `void reserve(std::size_t count)` | Reserves enough buckets for about `count` keys. | Expected $O(N)$ |
| `bool insert(const T& key)`, `bool insert(T&& key)` | Inserts `key`; returns whether a new key was inserted. | Expected $O(1)$ |
| `bool erase(const T& key)` | Removes `key`; returns whether a key was removed. | Expected $O(1)$ |
| `const T* find(const T& key) const` | Returns a pointer to `key`, or `nullptr` if it does not exist. | Expected $O(1)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | Expected $O(1)$ |
| `int count(const T& key) const` | Returns `1` if `key` exists, otherwise `0`. | Expected $O(1)$ |
| `std::vector<T> to_vector() const` | Returns all keys in bucket order. | $O(B)$ |

## Example

```cpp
#include "data_structure/hash_set.hpp"

#include <iostream>

int main() {
    m1une::data_structure::HashSet<long long> st = {3, 1, 3, 5};

    st.insert(2);
    st.erase(3);

    std::cout << st.contains(5) << "\n";  // 1
    std::cout << st.count(3) << "\n";     // 0
}
```
