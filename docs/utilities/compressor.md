---
title: Compressor
documentation_of: ../../utilities/compressor.hpp
---

## Overview

Coordinate compression helper. It stores sorted unique values and maps original values to dense zero-based indices.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Compressor()` | Creates an empty compressor. | $O(1)$ |
| `Compressor(vector<T> values)` | Builds from a vector. | $O(N \log N)$ |
| `Compressor(first, last)` | Builds from an iterator range. | $O(N \log N)$ |
| `void add(const T& value)` | Adds a value before rebuilding. | Amortized $O(1)$ |
| `void build()` | Sorts and removes duplicates. | $O(N \log N)$ |
| `int get(const T& value) const` | Returns the compressed index of an existing value. | $O(\log N)$ |
| `int lower_bound(const T& value) const` | Returns the first compressed index with value `>= value`. | $O(\log N)$ |
| `int upper_bound(const T& value) const` | Returns the first compressed index with value `> value`. | $O(\log N)$ |
| `bool contains(const T& value) const` | Returns whether the value exists. | $O(\log N)$ |
| `const T& operator[](int index) const` | Restores an original value from a compressed index. | $O(1)$ |
| `const vector<T>& values() const` | Returns all sorted unique values. | $O(1)$ |

## Example

```cpp
#include "utilities/compressor.hpp"
#include <vector>

int main() {
    std::vector<long long> xs = {100, -5, 100, 7};
    m1une::utilities::Compressor<long long> comp(xs);

    int id = comp.get(100);     // 2
    long long value = comp[id]; // 100
}
```
