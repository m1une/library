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

## Complexity Notation

* `M` is the maximum absolute value among the numerator, denominator, and
  widened intermediate values before normalization.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `numerator() const` | Returns the normalized numerator. | $O(1)$ |
| `denominator() const` | Returns the positive normalized denominator. | $O(1)$ |
| `is_integer() const` | Returns whether the denominator is one. | $O(1)$ |
| `sign() const` | Returns `-1`, `0`, or `1`. | $O(1)$ |
| `reciprocal() const` | Returns the reciprocal; requires a nonzero value. | $O(1)$ |
| `abs() const` | Returns the absolute value. | $O(1)$ |
| `trunc() const` | Rounds toward zero. | $O(1)$ |
| `floor() const` | Returns the mathematical floor. | $O(1)$ |
| `ceil() const` | Returns the mathematical ceiling. | $O(1)$ |
| `to_long_double() const` | Returns a floating-point approximation. | $O(1)$ |

Arithmetic operators `+`, `-`, `*`, and `/`, their compound forms, unary signs,
equality, and three-way comparison are supported.

All operations use `__int128_t` intermediates and reduce cross factors before
multiplication when possible. The final normalized numerator and denominator,
and every intermediate widened calculation, must be representable.
Construction and arithmetic normalize with gcd computations and take
$O(\log M)$ time. Comparisons take $O(1)$ widened arithmetic.

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
