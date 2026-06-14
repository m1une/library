---
title: Shifted Array
documentation_of: ../../utilities/shifted_array.hpp
---

## Overview

A convenient wrapper around `std::vector` that allows arbitrary index ranges, including negative indices or non-zero starting indices. It stores values for the closed interval $[L, R]$ at indices `L`, `L + step`, `L + 2 * step`, and so on.

## Template Parameters

* `T`: The underlying data type. `bool` is not supported; use `char` instead if you need a boolean-like array.

## Methods

| Method | Description | Complexity / Throws |
| --- | --- | --- |
| `ShiftedArray(long long L, long long R, T init_value = T(), long long step = 1)` | Constructs an array for indices `L, L + step, ... , R`. `init_value` is used for every stored element. | Throws `std::invalid_argument` if `step <= 0` or `L > R`. |
| `T& operator[](long long i)` | Accesses the element at shifted index `i`. | $O(1)$; throws `std::out_of_range` if `i` is outside the configured bounds or is not aligned to `step`. |
| `long long index(long long i) const` | Returns the internal 0-based vector index for shifted index `i`. | $O(1)$; throws `std::out_of_range` if `i` is outside the configured bounds or is not aligned to `step`. |

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
