---
title: Integer Square Root and Power
documentation_of: ../../math/integer_arithmetic.hpp
---

## Overview

This header provides exact integer square roots and powers without converting
through floating point.

```cpp
isqrt(value);
ceil_sqrt(value);
ipow(base, exponent);
checked_ipow(base, exponent);
```

The descriptive aliases `floor_sqrt`, `integer_pow`, and
`checked_integer_pow` are also available.

All functions accept standard integral types except `bool`. Square-root inputs
must be non-negative, and power exponents must be unsigned integers.

## Square Root

| Function | Result | Complexity |
| --- | --- | --- |
| `isqrt(value)` | $\lfloor\sqrt{\mathrm{value}}\rfloor$ | $O(\log \mathrm{value})$ |
| `floor_sqrt(value)` | Alias of `isqrt` | $O(\log \mathrm{value})$ |
| `ceil_sqrt(value)` | $\lceil\sqrt{\mathrm{value}}\rceil$ | $O(\log \mathrm{value})$ |

The implementation compares with division rather than multiplying candidate
roots, so it remains correct near the maximum value of the integer type.

## Integer Power

| Function | Result | Complexity |
| --- | --- | --- |
| `ipow(base, exponent)` | Exact `base` raised to `exponent` | $O(\log \mathrm{exponent})$ |
| `integer_pow(base, exponent)` | Alias of `ipow` | $O(\log \mathrm{exponent})$ |
| `checked_ipow(base, exponent)` | The power, or `std::nullopt` on overflow | $O(\log \mathrm{exponent})$ |
| `checked_integer_pow(base, exponent)` | Alias of `checked_ipow` | $O(\log \mathrm{exponent})$ |

`ipow` requires the result to fit in the base type and asserts this condition
in debug builds. Use `checked_ipow` when overflow is possible.

As usual, every nonzero integer to exponent zero is one. This library also
defines zero to exponent zero as one, which is convenient for binary
exponentiation and combinatorial formulas.

## Example

```cpp
#include "math/integer_arithmetic.hpp"

#include <iostream>

int main() {
    std::cout << m1une::math::isqrt(20LL) << "\n";      // 4
    std::cout << m1une::math::ceil_sqrt(20LL) << "\n"; // 5
    std::cout << m1une::math::ipow(3LL, 10U) << "\n";  // 59049

    auto large = m1une::math::checked_ipow(10LL, 19U);
    if (!large) std::cout << "overflow\n";
}
```
