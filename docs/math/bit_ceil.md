---
title: Bit Ceil
documentation_of: ../../math/bit_ceil.hpp
---

## Overview

A math utility function that calculates the smallest power of two that is greater than or equal to a given number `n`.

This is frequently used internally to determine the optimal underlying array size for complete binary tree structures (like Segment Trees) so that their length is perfectly aligned to a power of 2.

## API

```cpp
template <typename T>
constexpr T bit_ceil(T n);
```

`T` is both the argument and return type. It must be an integer-like type that
supports comparison, left shift, and construction from `1`.

The function returns the smallest power of two greater than or equal to `n`.
If `n <= 1`, it returns `T(1)`. The result must be representable by `T`.

## Complexity

The running time is $O(\log n)$ and the additional memory usage is $O(1)$.

## Example

```cpp
#include "math/bit_ceil.hpp"

#include <iostream>

int main() {
    std::cout << m1une::math::bit_ceil(13) << "\n"; // 16
}
```
