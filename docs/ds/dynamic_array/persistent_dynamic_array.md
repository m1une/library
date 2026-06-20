---
title: Persistent Dynamic Array
documentation_of: ../../../ds/dynamic_array/persistent_dynamic_array.hpp
---

## Overview

`PersistentDynamicArray` is a path-copying implicit treap. It acts like a persistent version of `DynamicArray`: update operations return a new array and leave the old version available.

Nodes are stored in a shared block-contiguous pool and refer to children by integer index. This avoids per-node allocation and reference-counted child pointers while preserving stable references returned by `at`, `front`, and `back`.
The pool is append-only and is released when the last related version is destroyed.

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

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `PersistentDynamicArray clear() const` | Returns an empty version. | $O(1)$ |
| `PersistentDynamicArray insert(int pos, T val) const` | Returns a version with `val` inserted before index `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray insert(int pos, const std::vector<T>& v) const` | Returns a version with all elements of `v` inserted before index `pos`. | Expected $O(M + \log N)$ |
| `PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const` | Returns a version with `other` inserted before index `pos`. Versions sharing a pool reuse its nodes; an independently constructed array is copied into this pool. | Expected $O(\log N)$ with a shared pool; $O(M + \log N)$ otherwise |
| `PersistentDynamicArray push_back(T val) const`, `push_front(T val) const` | Returns a version with one element added. | Expected $O(\log N)$ |
| `PersistentDynamicArray append(...) const` | Appends a vector or another persistent dynamic array. | Expected $O(M + \log N)$ for a vector or independent array; $O(\log N)$ for a version sharing the pool |
| `PersistentDynamicArray erase(int pos) const` | Returns a version with the element at `pos` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray erase(int l, int r) const` | Returns a version with `[l, r)` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray pop_back() const`, `pop_front() const` | Returns a version with one element removed. | Expected $O(\log N)$ |
| `const T& at(int pos) const`, `operator[]` | Returns the element at `pos`. | Expected $O(\log N)$ |
| `T get(int pos) const` | Returns a copy of the element at `pos`. | Expected $O(\log N)$ |
| `const T& front() const`, `back() const` | Returns the first or last element. | Expected $O(\log N)$ |
| `PersistentDynamicArray set(int pos, T val) const` | Returns a version where index `pos` is overwritten by `val`. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse(int l, int r) const` | Returns a version with `[l, r)` reversed. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse() const` | Returns a version with the whole array reversed. | $O(1)$ |
| `PersistentDynamicArray rotate(int l, int m, int r) const` | Returns a version where `[m, r)` is moved before `[l, m)`, like `std::rotate`. | Expected $O(\log N)$ |
| `std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const` | Returns `{prefix, suffix}` split at `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray split_off(int pos) const` | Returns the suffix `[pos, N)` while leaving the current version unchanged. | Expected $O(\log N)$ |
| `std::vector<T> to_vector() const` | Dumps the entire array. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Dumps `[l, r)`, where `K = r - l`. | $O(K + \log N)$ |

## Example

```cpp
#include "ds/dynamic_array/persistent_dynamic_array.hpp"

#include <iostream>

using namespace m1une::ds;

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
