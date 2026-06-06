---
title: Dynamic Array (Implicit Treap)
documentation_of: ../../data_structure/dynamic_array.hpp
---

## Overview

`DynamicArray` is an optimized implementation of an Implicit Treap, backed by a `std::vector` memory pool. It acts as a highly dynamic array, supporting $O(\log N)$ insertions and deletions at any index.

Because it relies on an array-based memory pool instead of standard pointers, deep copying the data structure via the copy constructor is exceptionally fast and automatically avoids heap fragmentation.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors and Assignment Operators

* `DynamicArray()`
  Constructs an empty dynamic array. ($O(1)$)

* `DynamicArray(const DynamicArray& other)`
  Copy constructor. Deep copies the array structure and memory pool. ($O(V)$ where $V$ is the capacity of the memory pool)

* `DynamicArray(DynamicArray&& other)`
  Move constructor. Takes ownership of the other array's memory pool without reallocating. ($O(1)$)

* `DynamicArray(const std::vector<T>& v)`
  Constructs the dynamic array initialized with elements from `v`. ($O(N \log N)$)

* `DynamicArray(std::vector<T>&& v)`
  Constructs the dynamic array by moving elements from an rvalue reference of a `std::vector`. This avoids deep copies of the individual elements, providing a massive performance boost when storing complex objects like strings or nested vectors. ($O(N \log N)$)

* `DynamicArray(std::initializer_list<T> init)`
  Constructs the dynamic array initialized with an initializer list. ($O(N \log N)$)

* `operator=`
  Supports both copy and move assignment.

## Methods

* `int size() const`
  Returns the number of elements currently in the array. ($O(1)$)

* `void push_back(T val)`
  Appends a new element `val` to the end of the array. ($O(\log N)$)

* `void insert(int pos, T val)`
  Inserts a new element `val` at the specified 0-based index `pos`. All subsequent elements shift right. ($O(\log N)$)

* `void erase(int pos)`
  Removes the element at the specified 0-based index `pos`. All subsequent elements shift left. ($O(\log N)$)

* `T get(int pos) const`
  Returns the element at the specified 0-based index `pos`. ($O(\log N)$)

* `void set(int pos, T val)`
  Overwrites the element at index `pos` with `val`. ($O(\log N)$)

* `std::vector<T> to_vector() const`
  Dumps the entire array state into a standard `std::vector`. ($O(N)$)

## Example

```cpp
#include "data_structure/dynamic_array.hpp"
#include <iostream>
#include <vector>

using namespace m1une::data_structure;

int main() {
    // Construct from initializer list
    DynamicArray<int> arr1 = {10, 20, 30};
    
    // Copy Constructor
    DynamicArray<int> arr2 = arr1; 
    arr2.insert(1, 15);

    // Move Assignment
    DynamicArray<int> arr3;
    arr3 = std::move(arr2);
    
    // Print arr3 -> 10 15 20 30
    for(int x : arr3.to_vector()) {
        std::cout << x << " "; 
    }
    std::cout << "\n";

    return 0;
}
```
