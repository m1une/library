---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/shifted_array.test.cpp
    title: verify/utilities/shifted_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/shifted_array.hpp\"\n\n\n\n#include <stdexcept>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\n// `bool` is\
    \ not supported; use `char` for boolean-like arrays.\ntemplate <typename T>\n\
    struct ShiftedArray {\n   private:\n    long long _offset;\n    long long _step;\n\
    \    long long _size;\n    std::vector<T> _data;\n\n    static long long checked_size(long\
    \ long L, long long R, long long step) {\n        if (step <= 0) {\n         \
    \   throw std::invalid_argument(\"Step must be positive\");\n        }\n     \
    \   if (L > R) {\n            throw std::invalid_argument(\"Left bound must be\
    \ less than or equal to right bound\");\n        }\n        return (R - L) / step\
    \ + 1;\n    }\n\n    long long to_index(long long i) const {\n        if (i <\
    \ _offset) {\n            throw std::out_of_range(\"Index out of range\");\n \
    \       }\n        long long diff = i - _offset;\n        if (diff % _step !=\
    \ 0) {\n            throw std::out_of_range(\"Index is not aligned to the step\"\
    );\n        }\n        long long index = diff / _step;\n        if (index >= _size)\
    \ {\n            throw std::out_of_range(\"Index out of range\");\n        }\n\
    \        return index;\n    }\n\n   public:\n    // Creates an array on the closed\
    \ interval [L, R] using the given step.\n    ShiftedArray(long long L, long long\
    \ R, T init_value = T(), long long step = 1)\n        : _offset(L), _step(step),\
    \ _size(checked_size(L, R, step)), _data(_size, init_value) {}\n\n    T& operator[](long\
    \ long i) {\n        return _data[to_index(i)];\n    }\n\n    const T& operator[](long\
    \ long i) const {\n        return _data[to_index(i)];\n    }\n\n    long long\
    \ index(long long i) const {\n        return to_index(i);\n    }\n};\n\n}  //\
    \ namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SHIFTED_ARRAY_HPP\n#define M1UNE_SHIFTED_ARRAY_HPP 1\n\n#include\
    \ <stdexcept>\n#include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\
    \n// `bool` is not supported; use `char` for boolean-like arrays.\ntemplate <typename\
    \ T>\nstruct ShiftedArray {\n   private:\n    long long _offset;\n    long long\
    \ _step;\n    long long _size;\n    std::vector<T> _data;\n\n    static long long\
    \ checked_size(long long L, long long R, long long step) {\n        if (step <=\
    \ 0) {\n            throw std::invalid_argument(\"Step must be positive\");\n\
    \        }\n        if (L > R) {\n            throw std::invalid_argument(\"Left\
    \ bound must be less than or equal to right bound\");\n        }\n        return\
    \ (R - L) / step + 1;\n    }\n\n    long long to_index(long long i) const {\n\
    \        if (i < _offset) {\n            throw std::out_of_range(\"Index out of\
    \ range\");\n        }\n        long long diff = i - _offset;\n        if (diff\
    \ % _step != 0) {\n            throw std::out_of_range(\"Index is not aligned\
    \ to the step\");\n        }\n        long long index = diff / _step;\n      \
    \  if (index >= _size) {\n            throw std::out_of_range(\"Index out of range\"\
    );\n        }\n        return index;\n    }\n\n   public:\n    // Creates an array\
    \ on the closed interval [L, R] using the given step.\n    ShiftedArray(long long\
    \ L, long long R, T init_value = T(), long long step = 1)\n        : _offset(L),\
    \ _step(step), _size(checked_size(L, R, step)), _data(_size, init_value) {}\n\n\
    \    T& operator[](long long i) {\n        return _data[to_index(i)];\n    }\n\
    \n    const T& operator[](long long i) const {\n        return _data[to_index(i)];\n\
    \    }\n\n    long long index(long long i) const {\n        return to_index(i);\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_SHIFTED_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/shifted_array.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/shifted_array.test.cpp
documentation_of: utilities/shifted_array.hpp
layout: document
title: Shifted Array
---

## Overview

A convenient wrapper around `std::vector` that allows arbitrary index ranges, including negative indices or non-zero starting indices. It stores values for the closed interval $[L, R]$ at indices `L`, `L + step`, `L + 2 * step`, and so on.

## Template Parameters

* `T`: The underlying data type. `bool` is not supported; use `char` instead if you need a boolean-like array.

## Methods

### `ShiftedArray(long long L, long long R, T init_value = T(), long long step = 1)`
Constructs an array with indices ranging from `L` to `R` (inclusive).

* `L`: The left bound (inclusive).
* `R`: The right bound (inclusive).
* `init_value`: The default value for each stored element.
* `step`: The positive index step size.
* **Throws:** `std::invalid_argument` if `step <= 0` or `L > R`.

### `T &operator[](long long i)`
Accesses the element at the adjusted index `i`.
* **Complexity:** $O(1)$ time.
* **Throws:** `std::out_of_range` if `i` is outside the configured bounds or is not aligned to `step`.

### `long long index(long long i) const`
Returns the internal 0-based vector index corresponding to the shifted index `i`.
* **Throws:** `std::out_of_range` if `i` is outside the configured bounds or is not aligned to `step`.

## Example

```cpp
#include "utilities/shifted_array.hpp"
#include <iostream>

int main() {
    // Create an array with indices -4, -2, 0, 2, 4.
    m1une::utilities::ShiftedArray<int> arr(-4, 4, 0, 2);

    arr[-4] = 10;
    arr[0] = 50;
    arr[4] = 100;

    std::cout << arr[-4] << " " << arr[4] << "\n"; // Output: 10 100
    return 0;
}
```
