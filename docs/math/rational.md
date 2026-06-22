---
title: Rational Number
documentation_of: ../../math/rational.hpp
---

## Overview

`Rational<T>` represents an exact fraction using a signed integral type.

Every value is normalized:

* numerator and denominator are coprime,
* the denominator is positive,
* zero is represented as `0/1`.

The default underlying type is `long long`.

## Construction

```cpp
Rational<T>();
Rational<T>(integer);
Rational<T>(numerator, denominator);
```

The denominator must be nonzero. Integer construction is implicit, so ordinary
integers can be mixed with rationals in arithmetic expressions.

`T` must be a signed integral type no wider than `long long`.

## Methods

| Method | Description |
| --- | --- |
| `numerator()` | Returns the normalized numerator. |
| `denominator()` | Returns the positive normalized denominator. |
| `is_integer()` | Returns whether the denominator is one. |
| `sign()` | Returns `-1`, `0`, or `1`. |
| `reciprocal()` | Returns the reciprocal; requires a nonzero value. |
| `abs()` | Returns the absolute value. |
| `trunc()` | Rounds toward zero. |
| `floor()` | Returns the mathematical floor. |
| `ceil()` | Returns the mathematical ceiling. |
| `to_long_double()` | Returns a floating-point approximation. |

Arithmetic operators `+`, `-`, `*`, and `/`, their compound forms, unary signs,
equality, and three-way comparison are supported.

All operations use `__int128_t` intermediates and reduce cross factors before
multiplication when possible. The final normalized numerator and denominator,
and every intermediate widened calculation, must be representable.

## Input and Output

Output uses `numerator/denominator`, omitting `/1` for integers.

Input accepts either an integer or a fraction with no spaces around the slash:

```text
5
-7/12
```

## Example

```cpp
#include "math/rational.hpp"

#include <iostream>

int main() {
    using Fraction = m1une::math::Rational<long long>;

    Fraction first(2, 3);
    Fraction second(5, 6);
    Fraction result = first + second;

    std::cout << result << "\n";        // 3/2
    std::cout << result.floor() << "\n"; // 1
}
```
