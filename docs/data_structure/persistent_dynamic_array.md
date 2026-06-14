---
title: Persistent Dynamic Array
documentation_of: ../../data_structure/persistent_dynamic_array.hpp
---

## Overview

`PersistentDynamicArray` is a path-copying implicit treap. It acts like a persistent version of `DynamicArray`: update operations return a new array and leave the old version available.

The structure supports index-based insertion, deletion, point assignment, reversal, rotation, splitting, and concatenation. Untouched subtrees are shared between versions.

## Complexity Notation

* `N` is the current number of elements in the array.
* `M` is the number of inserted or appended elements.
* `K` is the number of elements returned by `to_vector`.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors

* `PersistentDynamicArray()`
  Constructs an empty array. ($O(1)$)

* `PersistentDynamicArray(int n)`
  Constructs an array with `n` value-initialized elements. ($O(N)$)

* `PersistentDynamicArray(int n, const T& value)`
  Constructs an array with `n` copies of `value`. ($O(N)$)

* `PersistentDynamicArray(const std::vector<T>& v)`
  Constructs an array initialized with elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::vector<T>&& v)`
  Constructs an array by moving elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::initializer_list<T> init)`
  Constructs an array initialized with an initializer list. ($O(N)$)

## Methods

* `int size() const`
  Returns the number of elements. ($O(1)$)

* `bool empty() const`
  Returns whether the array is empty. ($O(1)$)

* `PersistentDynamicArray clear() const`
  Returns an empty version. ($O(1)$)

* `PersistentDynamicArray insert(int pos, T val) const`
  Returns a version with `val` inserted at `pos`. ($O(\log N)$ expected)

* `PersistentDynamicArray insert(int pos, const std::vector<T>& v) const`
  Returns a version with all elements of `v` inserted at `pos`. ($O(M + \log N)$ expected)

* `PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const`
  Returns a version with `other` inserted at `pos`. ($O(\log N)$ expected)

* `PersistentDynamicArray push_back(T val) const`, `push_front(T val) const`
  Returns a version with one element added. ($O(\log N)$ expected)

* `PersistentDynamicArray append(...) const`
  Appends a vector or another persistent dynamic array. ($O(M + \log N)$ expected for a vector, $O(\log N)$ expected for another array)

* `PersistentDynamicArray erase(int pos) const`
  Returns a version with the element at `pos` removed. ($O(\log N)$ expected)

* `PersistentDynamicArray erase(int l, int r) const`
  Returns a version with the half-open range $[l, r)$ removed. ($O(\log N)$ expected)

* `PersistentDynamicArray pop_back() const`, `pop_front() const`
  Returns a version with one element removed. ($O(\log N)$ expected)

* `const T& at(int pos) const`, `operator[]`
  Returns the element at `pos`. ($O(\log N)$ expected)

* `T get(int pos) const`
  Returns a copy of the element at `pos`. ($O(\log N)$ expected)

* `const T& front() const`, `back() const`
  Returns the first or last element. ($O(\log N)$ expected)

* `PersistentDynamicArray set(int pos, T val) const`
  Returns a version with the element at `pos` overwritten by `val`. ($O(\log N)$ expected)

* `PersistentDynamicArray reverse(int l, int r) const`
  Returns a version with $[l, r)$ reversed. ($O(\log N)$ expected)

* `PersistentDynamicArray reverse() const`
  Returns a version with the whole array reversed. ($O(1)$)

* `PersistentDynamicArray rotate(int l, int m, int r) const`
  Returns a version after `std::rotate`-style rotation of $[l, r)$. ($O(\log N)$ expected)

* `std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const`
  Returns `{prefix, suffix}` split at `pos`. ($O(\log N)$ expected)

* `PersistentDynamicArray split_off(int pos) const`
  Returns the suffix $[pos, N)$ while leaving the current version unchanged. ($O(\log N)$ expected)

* `std::vector<T> to_vector() const`
  Dumps the entire array. ($O(N)$)

* `std::vector<T> to_vector(int l, int r) const`
  Dumps the half-open range $[l, r)$. ($O(K + \log N)$)

## Example

```cpp
#include "data_structure/persistent_dynamic_array.hpp"

#include <iostream>

using namespace m1une::data_structure;

int main() {
    PersistentDynamicArray<int> a = {1, 2, 3, 4, 5};
    auto b = a.insert(2, 10);      // {1, 2, 10, 3, 4, 5}
    auto c = b.reverse(1, 5);      // {1, 4, 3, 10, 2, 5}
    auto d = c.erase(2).set(0, 7); // {7, 4, 10, 2, 5}

    for (int x : a.to_vector()) std::cout << x << " ";
    std::cout << "\n";
    for (int x : d.to_vector()) std::cout << x << " ";
    std::cout << "\n";
}
```
