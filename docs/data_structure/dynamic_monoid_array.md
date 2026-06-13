---
title: Dynamic Monoid Array
documentation_of: ../../data_structure/dynamic_monoid_array.hpp
---

## Overview

`DynamicMonoidArray` is an implicit treap for dynamic sequences with range product queries. It supports indexed insertion, deletion, reversal, rotation, splitting, concatenation, and monoid products over half-open ranges.

Each node stores both forward and reversed products, so `reverse(l, r)` works correctly even when the monoid operation is not commutative.

## Complexity Notation

In this document:

* `N` is the current number of elements in the sequence.
* `M` is the number of elements inserted or appended from another container.
* `K` is the number of elements returned or moved into a newly returned sequence.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`.

## Constructors

* `DynamicMonoidArray()`
  Constructs an empty sequence. ($O(1)$)

* `DynamicMonoidArray(int n)`
  Constructs a sequence with `n` copies of `Monoid::id()`. ($O(N \log N)$)

* `DynamicMonoidArray(int n, const T& value)`
  Constructs a sequence with `n` copies of `value`, like `std::vector<T>(n, value)`. ($O(N \log N)$)

* `DynamicMonoidArray(const std::vector<T>& v)`
  Constructs the sequence from monoid values. ($O(N \log N)$)

* `DynamicMonoidArray(std::vector<T>&& v)`
  Constructs the sequence by moving monoid values. ($O(N \log N)$)

* `DynamicMonoidArray(const std::vector<U>& v)`
  Constructs the sequence from another type using `Monoid::make(x)` if available, otherwise `static_cast<T>(x)`. ($O(N \log N)$)

* `DynamicMonoidArray(std::initializer_list<T> init)`
  Constructs the sequence from an initializer list of monoid values. ($O(N \log N)$)

## Methods

* `int size() const`
  Returns the number of elements. ($O(1)$)

* `bool empty() const`
  Returns whether the sequence is empty. ($O(1)$)

* `void clear()`
  Removes all elements. ($O(1)$)

* `void insert(int pos, T value)`
  Inserts `value` before index `pos`. ($O(\log N)$)

* `void insert(int pos, const std::vector<T>& v)`
  Inserts every value in `v` before index `pos`. ($O(M \log M + \log N)$)

* `void insert(int pos, const DynamicMonoidArray& other)`
  Inserts a copy of another sequence before index `pos`. ($O(M + \log N)$)

* `void push_back(T value)`, `void push_front(T value)`
  Inserts one value at the end or beginning. ($O(\log N)$)

* `void append(const std::vector<T>& v)`
  Appends all values in `v`. ($O(M \log M + \log N)$)

* `void append(const DynamicMonoidArray& other)`
  Appends a copy of another sequence. ($O(M + \log N)$)

* `void erase(int pos)`
  Removes the value at index `pos`. ($O(\log N)$)

* `void erase(int l, int r)`
  Removes the half-open range $[l, r)$. ($O(\log N)$)

* `void pop_back()`, `void pop_front()`
  Removes one value from the end or beginning. ($O(\log N)$)

* `T get(int pos) const`
  Returns the value at index `pos`. ($O(\log N)$)

* `void set(int pos, T value)`
  Replaces the value at index `pos` and rebuilds affected products. ($O(\log N)$)

* `void reverse(int l, int r)`
  Reverses the half-open range $[l, r)$. ($O(\log N)$)

* `void reverse()`
  Reverses the entire sequence. ($O(1)$)

* `void rotate(int l, int m, int r)`
  Applies `std::rotate`-style rotation to $[l, r)$, moving $[m, r)$ before $[l, m)$. ($O(\log N)$)

* `T prod(int l, int r)`
  Returns the monoid product over $[l, r)$. ($O(\log N)$)

* `T all_prod() const`
  Returns the monoid product over the whole sequence. ($O(1)$)

* `std::vector<T> to_vector() const`
  Dumps the sequence into a standard vector. ($O(N)$)

* `std::vector<T> to_vector(int l, int r) const`
  Dumps the half-open range $[l, r)$ into a standard vector, where `K = r - l`. ($O(K + \log N)$)

* `DynamicMonoidArray split_off(int pos)`
  Removes $[pos, N)$ from the current sequence and returns it as a new sequence, where `K = N - pos`. Because each sequence owns its memory pool, the returned suffix is copied into a new pool. ($O(K + \log N)$)

## Notes

Unlike `DynamicArray`, this structure does not expose mutable references to elements. Use `set(pos, value)` to update a value so that stored monoid products remain correct.

For monoids whose element depends on the global index, such as an arg-min monoid storing positions, insertions and deletions change indices and require a different design.

## Example

```cpp
#include "data_structure/dynamic_monoid_array.hpp"
#include "monoid/add.hpp"
#include <iostream>

using Monoid = m1une::monoid::Add<long long>;
using Array = m1une::data_structure::DynamicMonoidArray<Monoid>;

int main() {
    Array a = {1, 2, 3, 4, 5};

    std::cout << a.prod(1, 4) << "\n"; // 2 + 3 + 4 = 9

    a.reverse(1, 5);                   // {1, 5, 4, 3, 2}
    a.set(2, 10);                      // {1, 5, 10, 3, 2}
    a.insert(3, 7);                    // {1, 5, 10, 7, 3, 2}

    std::cout << a.prod(0, 4) << "\n"; // 1 + 5 + 10 + 7 = 23

    return 0;
}
```
