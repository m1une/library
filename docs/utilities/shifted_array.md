---
title: Shifted Array
documentation_of: ../../utilities/shifted_array.hpp
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
