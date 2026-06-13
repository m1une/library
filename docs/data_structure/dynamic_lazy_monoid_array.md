---
title: Dynamic Lazy Monoid Array
documentation_of: ../../data_structure/dynamic_lazy_monoid_array.hpp
---

## Overview

`DynamicLazyMonoidArray` is an implicit treap for dynamic sequences with range products and lazy range actions. It supports indexed insertion, deletion, reversal, rotation, splitting, concatenation, range updates, and range product queries.

Each node stores both forward and reversed products, so `reverse(l, r)` works correctly for non-commutative value monoids when the acted monoid action is compatible with the value operation.

## Complexity Notation

In this document:

* `N` is the current number of elements in the sequence.
* `M` is the number of elements inserted or appended from another container.
* `K` is the number of elements returned or moved into a newly returned sequence.

## Template Parameters

* `ActedMonoid`: An acted monoid satisfying `m1une::acted_monoid::IsActedMonoid`.

## Constructors

* `DynamicLazyMonoidArray()`
  Constructs an empty sequence. ($O(1)$)

* `DynamicLazyMonoidArray(int n)`
  Constructs a sequence with `n` copies of `ActedMonoid::id()`. ($O(N \log N)$)

* `DynamicLazyMonoidArray(int n, const T& value)`
  Constructs a sequence with `n` copies of `value`. ($O(N \log N)$)

* `DynamicLazyMonoidArray(const std::vector<T>& v)`
  Constructs the sequence from acted-monoid values. ($O(N \log N)$)

* `DynamicLazyMonoidArray(std::vector<T>&& v)`
  Constructs the sequence by moving acted-monoid values. ($O(N \log N)$)

* `DynamicLazyMonoidArray(const std::vector<U>& v)`
  Constructs the sequence from another type using `ActedMonoid::make(x)` if available, otherwise `static_cast<T>(x)`. ($O(N \log N)$)

* `DynamicLazyMonoidArray(std::initializer_list<T> init)`
  Constructs the sequence from an initializer list of acted-monoid values. ($O(N \log N)$)

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

* `void insert(int pos, const DynamicLazyMonoidArray& other)`
  Inserts a copy of another sequence before index `pos`. ($O(M + \log N)$)

* `void push_back(T value)`, `void push_front(T value)`
  Inserts one value at the end or beginning. ($O(\log N)$)

* `void append(const std::vector<T>& v)`
  Appends all values in `v`. ($O(M \log M + \log N)$)

* `void append(const DynamicLazyMonoidArray& other)`
  Appends a copy of another sequence. ($O(M + \log N)$)

* `void erase(int pos)`
  Removes the value at index `pos`. ($O(\log N)$)

* `void erase(int l, int r)`
  Removes the half-open range $[l, r)$. ($O(\log N)$)

* `void pop_back()`, `void pop_front()`
  Removes one value from the end or beginning. ($O(\log N)$)

* `T get(int pos)`
  Returns the value at index `pos`, pushing lazy tags on the path. ($O(\log N)$)

* `void set(int pos, T value)`
  Replaces the value at index `pos` and rebuilds affected products. ($O(\log N)$)

* `void reverse(int l, int r)`
  Reverses the half-open range $[l, r)$. ($O(\log N)$)

* `void reverse()`
  Reverses the entire sequence. ($O(1)$)

* `void rotate(int l, int m, int r)`
  Applies `std::rotate`-style rotation to $[l, r)$, moving $[m, r)$ before $[l, m)$. ($O(\log N)$)

* `void apply(int pos, const F& f)`
  Applies the lazy operator `f` to the value at index `pos`. ($O(\log N)$)

* `void apply(int l, int r, const F& f)`
  Applies the lazy operator `f` to all values in $[l, r)$. ($O(\log N)$)

* `T prod(int l, int r)`
  Returns the acted monoid product over $[l, r)$. ($O(\log N)$)

* `T all_prod() const`
  Returns the acted monoid product over the whole sequence. ($O(1)$)

* `std::vector<T> to_vector()`
  Dumps the sequence into a standard vector, pushing lazy tags. ($O(N)$)

* `std::vector<T> to_vector(int l, int r)`
  Dumps the half-open range $[l, r)$ into a standard vector, where `K = r - l`. ($O(K + \log N)$)

* `DynamicLazyMonoidArray split_off(int pos)`
  Removes $[pos, N)$ from the current sequence and returns it as a new sequence, where `K = N - pos`. Because each sequence owns its memory pool, the returned suffix is copied into a new pool. ($O(K + \log N)$)

## Notes

`get`, `prod`, and `to_vector` are non-const because they may push pending lazy tags while walking the treap.

For size-aware acted monoids such as `RangeAddRangeSum`, `ActedMonoid::id()` often has size `0`. In that case, prefer constructing from raw values or from explicit leaf values:

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::data_structure::DynamicLazyMonoidArray<AM>;

Array a(std::vector<long long>(n, 0)); // uses AM::make(x)
Array b(n, AM::make(0));               // explicit leaf value
```

For acted monoids whose value depends on the global index, such as arithmetic-progression actions storing positions, insertions and deletions change indices and require a different design.

## Example

```cpp
#include "data_structure/dynamic_lazy_monoid_array.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::data_structure::DynamicLazyMonoidArray<AM>;

int main() {
    Array a(std::vector<long long>{1, 2, 3, 4, 5});

    a.apply(1, 4, 10);                 // {1, 12, 13, 14, 5}
    std::cout << a.prod(0, 5).sum << "\n";

    a.reverse(1, 5);                   // {1, 5, 14, 13, 12}
    a.set(2, AM::make(100));           // {1, 5, 100, 13, 12}

    std::cout << a.prod(1, 4).sum << "\n";

    return 0;
}
```
