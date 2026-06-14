---
title: ModInt
documentation_of: ../../math/modint.hpp
---

## Overview

A struct for automatic modular arithmetic. It wraps standard integer types to safely and automatically apply modulo operations during addition, subtraction, multiplication, and division. This is highly useful in competitive programming to prevent integer overflow and simplify code syntax.

## Template Parameters

* `Modulus`: A `uint32_t` representing the modulo value (e.g., `998244353` or `1000000007`).

## Type Aliases

For convenience, the library provides the following common type aliases:
* `using modint998244353 = ModInt<998244353>;`
* `using modint1000000007 = ModInt<1000000007>;`

## Constructors

| Constructor | Description | Complexity |
| --- | --- | --- |
| `ModInt()` | Initializes the value to `0`. | $\mathcal{O}(1)$ |
| `ModInt(int v)`, `ModInt(long long v)`, `ModInt(unsigned int v)` | Initializes from an integer. Negative values are converted to their positive modulo equivalents. | $\mathcal{O}(1)$ |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `uint32_t val() const` | Returns the stored value in `[0, Modulus - 1]`. | $\mathcal{O}(1)$ |
| `ModInt pow(long long n) const` | Computes the `n`-th power by binary exponentiation. | $\mathcal{O}(\log n)$ |
| `ModInt inv() const` | Computes the modular inverse by the extended Euclidean algorithm. The value and modulus must be coprime. | $\mathcal{O}(\log(\text{Modulus}))$ |
| `static uint32_t mod()` | Returns the modulus associated with this type. | $\mathcal{O}(1)$ |
| `static ModInt raw(uint32_t v)` | Constructs directly from `v` without applying `% Modulus`. Use only when `v < Modulus`. | $\mathcal{O}(1)$ |

## Operators

| Operators | Description | Complexity |
| --- | --- | --- |
| `+`, `-`, `*`, `+=`, `-=`, `*=` | Performs addition, subtraction, or multiplication with automatic modulo adjustment. | $\mathcal{O}(1)$ |
| `/`, `/=` | Multiplies by the modular inverse of the right-hand side. | $\mathcal{O}(\log(\text{Modulus}))$ |
| `++`, `--` | Increments or decrements while wrapping around `0` and `Modulus - 1`. | $\mathcal{O}(1)$ |
| `==`, `!=` | Compares stored values. | $\mathcal{O}(1)$ |
| `<<`, `>>` | Outputs the stored value or inputs a standard integer. | $\mathcal{O}(1)$ |

## Example

```cpp
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;

int main() {
    mint a = 1000000000;
    mint b = 1000000000;

    // Automatic modulo arithmetic
    mint c = a * b; // Will not overflow and handles modulo automatically
    std::cout << "a * b = " << c << "\n";

    // Power
    mint d = a.pow(100);
    std::cout << "a^100 = " << d << "\n";

    // Modular inverse & Division
    mint e = mint(5).inv();
    mint f = a / 5; // Equivalently uses a * mint(5).inv()
    std::cout << "Inverse of 5 = " << e << "\n";
    std::cout << "a / 5 = " << f << "\n";

    return 0;
}
```
