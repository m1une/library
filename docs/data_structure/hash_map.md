---
title: Hash Map
documentation_of: ../../data_structure/hash_map.hpp
---

## Overview

`HashMap` is a flat open-addressing hash map. It is intended as a faster and more hack-resistant replacement for `std::unordered_map` in competitive programming.

Hashes are passed through a salted splitmix64 mixer, which helps avoid adversarial collisions for common integral keys. The table uses linear probing and rebuilds before the load factor reaches about 70%.

Pointers and references returned by `find`, `at`, `operator[]`, `insert`, and `insert_or_assign` remain valid until the map is modified.

## Template Parameters

* `Key`: The key type.
* `T`: The mapped value type.
* `Hash`: Hash function. Defaults to `std::hash<Key>`.
* `KeyEqual`: Equality predicate. Defaults to `std::equal_to<Key>`.

## Constructors

* `HashMap()`
  Constructs an empty map. ($O(1)$)

* `HashMap(std::size_t reserve_count)`
  Constructs an empty map with enough buckets for about `reserve_count` keys. ($O(1)$)

* `HashMap(std::initializer_list<std::pair<Key, T>> init)`
  Constructs a map from an initializer list. Later duplicate keys are ignored. Expected $O(N)$

* `HashMap(Iterator first, Iterator last)`
  Constructs a map from a range of pair-like values. Later duplicate keys are ignored. Expected $O(N)$

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of key-value pairs. | $O(1)$ |
| `bool empty() const` | Returns whether the map is empty. | $O(1)$ |
| `std::size_t bucket_count() const` | Returns the number of buckets. | $O(1)$ |
| `double load_factor() const` | Returns `size() / bucket_count()`. | $O(1)$ |
| `void clear()` | Removes all key-value pairs. | $O(B)$ |
| `void reserve(std::size_t count)` | Reserves enough buckets for about `count` keys. | Expected $O(N)$ |
| `std::pair<T*, bool> insert(const Key& key, const T& value)` | Inserts a key-value pair; returns a pointer to the value and whether a new key was inserted. | Expected $O(1)$ |
| `std::pair<T*, bool> insert(Key&& key, T&& value)` | Move-inserts a key-value pair; returns a pointer to the value and whether a new key was inserted. | Expected $O(1)$ |
| `std::pair<T*, bool> insert(std::pair<Key, T> value)` | Inserts a key-value pair; returns a pointer to the value and whether a new key was inserted. | Expected $O(1)$ |
| `T* insert_or_assign(const Key& key, V&& value)` | Inserts or overwrites `key`; returns a pointer to the value. | Expected $O(1)$ |
| `bool erase(const Key& key)` | Removes `key`; returns whether a key was removed. | Expected $O(1)$ |
| `T* find(const Key& key)`, `const T* find(const Key& key) const` | Returns a pointer to the value, or `nullptr` if it does not exist. | Expected $O(1)$ |
| `bool contains(const Key& key) const` | Returns whether `key` exists. | Expected $O(1)$ |
| `int count(const Key& key) const` | Returns `1` if `key` exists, otherwise `0`. | Expected $O(1)$ |
| `T& at(const Key& key)` | Returns the value for `key`. Throws `std::out_of_range` if missing. | Expected $O(1)$ |
| `T& operator[](const Key& key)` | Returns the value for `key`, inserting `T()` if missing. | Expected $O(1)$ |
| `std::vector<std::pair<Key, T>> to_vector() const` | Returns all key-value pairs in bucket order. | $O(B)$ |

## Example

```cpp
#include "data_structure/hash_map.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::data_structure::HashMap<long long, std::string> mp;

    mp[10] = "ten";
    mp.insert_or_assign(20, "twenty");

    if (auto p = mp.find(10)) {
        std::cout << *p << "\n";  // ten
    }
    std::cout << mp.contains(30) << "\n";  // 0
}
```
