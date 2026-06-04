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
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\n// bool is not\
    \ allowed\n// if you want to use bool, use char instead\ntemplate <typename T>\n\
    struct ShiftedArray {\n   private:\n    long long _offset;\n    long long _step;\n\
    \    int _size;\n    std::vector<T> _data;\n\n   public:\n    // make an array\
    \ with indices from L to R (including both L and R)\n    // [L, R] (closed interval)\n\
    \    ShiftedArray(long long L, long long R, T init_value = T(), long long step\
    \ = 1)\n        : _offset(L), _step(step), _size((R - L) / step + 1), _data(_size,\
    \ init_value) {\n        if (step <= 0) {\n            throw std::invalid_argument(\"\
    Step must be positive\");\n        }\n        if (L > R) {\n            throw\
    \ std::invalid_argument(\"Left bound must be less than or equal to right bound\"\
    );\n        }\n    }\n    T &operator[](long long i) {\n        int index = (i\
    \ - _offset) / _step;\n        if (index < 0 || index >= _size) {\n          \
    \  throw std::out_of_range(\"Index out of range\");\n        }\n        return\
    \ _data[index];\n    };\n    const T &operator[](long long i) const {\n      \
    \  int index = (i - _offset) / _step;\n        if (index < 0 || index >= _size)\
    \ {\n            throw std::out_of_range(\"Index out of range\");\n        }\n\
    \        return _data[index];\n    };\n    long long index(long long i) const\
    \ {\n        int index = (i - _offset) / _step;\n        if (index < 0 || index\
    \ >= _size) {\n            throw std::out_of_range(\"Index out of range\");\n\
    \        }\n        return index;\n    }\n};\n\n}  // namespace utilities\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SHIFTED_ARRAY_HPP\n#define M1UNE_SHIFTED_ARRAY_HPP 1\n\n#include\
    \ <stdexcept>\n#include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\
    \n// bool is not allowed\n// if you want to use bool, use char instead\ntemplate\
    \ <typename T>\nstruct ShiftedArray {\n   private:\n    long long _offset;\n \
    \   long long _step;\n    int _size;\n    std::vector<T> _data;\n\n   public:\n\
    \    // make an array with indices from L to R (including both L and R)\n    //\
    \ [L, R] (closed interval)\n    ShiftedArray(long long L, long long R, T init_value\
    \ = T(), long long step = 1)\n        : _offset(L), _step(step), _size((R - L)\
    \ / step + 1), _data(_size, init_value) {\n        if (step <= 0) {\n        \
    \    throw std::invalid_argument(\"Step must be positive\");\n        }\n    \
    \    if (L > R) {\n            throw std::invalid_argument(\"Left bound must be\
    \ less than or equal to right bound\");\n        }\n    }\n    T &operator[](long\
    \ long i) {\n        int index = (i - _offset) / _step;\n        if (index < 0\
    \ || index >= _size) {\n            throw std::out_of_range(\"Index out of range\"\
    );\n        }\n        return _data[index];\n    };\n    const T &operator[](long\
    \ long i) const {\n        int index = (i - _offset) / _step;\n        if (index\
    \ < 0 || index >= _size) {\n            throw std::out_of_range(\"Index out of\
    \ range\");\n        }\n        return _data[index];\n    };\n    long long index(long\
    \ long i) const {\n        int index = (i - _offset) / _step;\n        if (index\
    \ < 0 || index >= _size) {\n            throw std::out_of_range(\"Index out of\
    \ range\");\n        }\n        return index;\n    }\n};\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\n#endif  // M1UNE_SHIFTED_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/shifted_array.hpp
  requiredBy: []
  timestamp: '2026-05-29 01:41:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/shifted_array.test.cpp
documentation_of: utilities/shifted_array.hpp
layout: document
title: Shifted Array
---

## Overview

A convenient wrapper around `std::vector` that allows arbitrary index ranges, including negative indices or non-zero starting indices. It simulates closed intervals $[L, R]$ with custom step sizes.

## Template Parameters

* `T`: The underlying data type. 
  * **Note:** `bool` is not allowed; use `char` instead if you need a boolean-like array.

## Methods

### `ShiftedArray(long long L, long long R, T init_value = T(), long long step = 1)`
Constructs an array with indices ranging from `L` to `R` (inclusive).
* **Parameters:**
  * `L`: The left bound (inclusive).
  * `R`: The right bound (inclusive).
  * `init_value`: The default value to initialize the elements.
  * `step`: The index step size. Must be positive.

### `T &operator[](long long i)`
Accesses the element at the adjusted index `i`.
* **Complexity:** $O(1)$ time.
* **Throws:** `std::out_of_range` if `i` is outside the configured bounds.

### `long long index(long long i) const`
Returns the internal 0-based vector index corresponding to the shifted index `i`.

## Example

```cpp
#include "utilities/shifted_array.hpp"
#include <iostream>

int main() {
    // Create an array with indices from -5 to 5, initialized to 0
    m1une::utilities::ShiftedArray<int> arr(-5, 5, 0);

    arr[-5] = 10;
    arr[0] = 50;
    arr[5] = 100;

    std::cout << arr[-5] << " " << arr[5] << "\n"; // Output: 10 100
    return 0;
}
```
