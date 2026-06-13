---
title: Dynamic Array (Implicit Treap)
documentation_of: ../../data_structure/dynamic_array.hpp
---

## Overview

`DynamicArray` is an optimized implementation of an implicit treap, backed by a `std::vector` memory pool. It acts as a highly dynamic array, supporting index-based insertion, deletion, reversal, rotation, splitting, and concatenation.

Because it relies on an array-based memory pool instead of standard pointers, copying the data structure copies one contiguous pool and avoids per-node heap allocation.

## Complexity Notation

In this document:

* `N` is the current number of elements in the array.
* `M` is the number of elements inserted or appended from another container.
* `K` is the number of elements returned or moved into a newly returned array.
* `V` is the current size of the internal memory pool, including erased nodes that have not been reused.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors and Assignment Operators

* `DynamicArray()`
  Constructs an empty dynamic array. ($O(1)$)

* `DynamicArray(const DynamicArray& other)`
  Copy constructor. Deep copies the array structure and memory pool. ($O(V)$)

* `DynamicArray(DynamicArray&& other)`
  Move constructor. Takes ownership of the other array's memory pool without reallocating. ($O(1)$)

* `DynamicArray(const std::vector<T>& v)`
  Constructs the dynamic array initialized with elements from `v`. ($O(N \log N)$)

* `DynamicArray(std::vector<T>&& v)`
  Constructs the dynamic array by moving elements from an rvalue reference of a `std::vector`. ($O(N \log N)$)

* `DynamicArray(std::initializer_list<T> init)`
  Constructs the dynamic array initialized with an initializer list. ($O(N \log N)$)

* `operator=`
  Supports both copy and move assignment.

## Methods

* `int size() const`
  Returns the number of elements currently in the array. ($O(1)$)

* `bool empty() const`
  Returns whether the array is empty. ($O(1)$)

* `void clear()`
  Removes all elements. ($O(1)$)

* `void push_back(T val)`
  Appends a new element `val` to the end of the array. ($O(\log N)$)

* `void push_front(T val)`
  Inserts a new element `val` at the beginning of the array. ($O(\log N)$)

* `void append(const std::vector<T>& v)`
  Appends every element in `v`. ($O(M \log M + \log N)$)

* `void append(const DynamicArray& other)`
  Appends a copy of another dynamic array. ($O(M + \log N)$)

* `void insert(int pos, T val)`
  Inserts a new element `val` at the specified 0-based index `pos`. All subsequent elements shift right. ($O(\log N)$)

* `void insert(int pos, const std::vector<T>& v)`
  Inserts all elements of `v` at `pos`. ($O(M \log M + \log N)$)

* `void insert(int pos, const DynamicArray& other)`
  Inserts a copy of another dynamic array at `pos`. ($O(M + \log N)$)

* `void erase(int pos)`
  Removes the element at the specified 0-based index `pos`. All subsequent elements shift left. ($O(\log N)$)

* `void erase(int l, int r)`
  Removes the half-open range $[l, r)$. ($O(\log N)$)

* `void pop_back()`, `void pop_front()`
  Removes one element from the back or front. ($O(\log N)$)

* `T& at(int pos)`, `const T& at(int pos) const`
  Returns a reference to the element at `pos`. ($O(\log N)$)

* `operator[]`
  Alias for `at(pos)`. ($O(\log N)$)

* `T& front()`, `T& back()`
  Returns a reference to the first or last element. ($O(\log N)$)

* `T get(int pos) const`
  Returns the element at the specified 0-based index `pos`. ($O(\log N)$)

* `void set(int pos, T val)`
  Overwrites the element at index `pos` with `val`. ($O(\log N)$)

* `void reverse(int l, int r)`
  Reverses the half-open range $[l, r)$ using lazy propagation. ($O(\log N)$)

* `void reverse()`
  Reverses the entire array. ($O(1)$ amortized through lazy propagation)

* `void rotate(int l, int m, int r)`
  Applies `std::rotate`-style rotation to $[l, r)$, moving $[m, r)$ before $[l, m)$. ($O(\log N)$)

* `std::vector<T> to_vector() const`
  Dumps the entire array state into a standard `std::vector`. ($O(N)$)

* `std::vector<T> to_vector(int l, int r) const`
  Dumps the half-open range $[l, r)$ into a standard `std::vector`, where `K = r - l`. ($O(K + \log N)$)

* `DynamicArray split_off(int pos)`
  Removes $[pos, N)$ from the current array and returns it as a new `DynamicArray`, where `K = N - pos`. Because each `DynamicArray` owns its own memory pool, the returned suffix is copied into a new pool. ($O(K + \log N)$)

## Example

```cpp
#include "data_structure/dynamic_array.hpp"
#include <iostream>
#include <vector>

using namespace m1une::data_structure;

int main() {
    DynamicArray<int> arr = {1, 2, 3, 4, 5};

    arr.reverse(1, 4);          // {1, 4, 3, 2, 5}
    arr.rotate(1, 3, 5);        // {1, 2, 5, 4, 3}
    arr.insert(2, {10, 11});    // {1, 2, 10, 11, 5, 4, 3}
    arr.erase(3, 5);            // {1, 2, 10, 4, 3}
    arr.push_front(0);          // {0, 1, 2, 10, 4, 3}

    DynamicArray<int> tail = arr.split_off(3);
    arr.append(tail);           // {0, 1, 2, 10, 4, 3}

    for (int x : arr.to_vector()) {
        std::cout << x << " "; 
    }
    std::cout << "\n";

    return 0;
}
```
