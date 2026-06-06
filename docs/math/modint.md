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

* `ModInt()`
  Initializes the value to `0`.
  * **Time complexity:** $\mathcal{O}(1)$

* `ModInt(int v)` / `ModInt(long long v)` / `ModInt(unsigned int v)`
  Initializes the structure with the given integer value. Negative values are properly converted to their positive modulo equivalents (e.g., `-1` becomes `Modulus - 1`).
  * **Time complexity:** $\mathcal{O}(1)$

## Methods

* `uint32_t val() const`
  Returns the internal stored value (`_v`), which is guaranteed to be in the range `[0, Modulus - 1]`.
  * **Time complexity:** $\mathcal{O}(1)$

* `ModInt pow(long long n) const`
  Computes the $n$-th power of the current value using binary exponentiation.
  * **Time complexity:** $\mathcal{O}(\log n)$

* `ModInt inv() const`
  Computes the modular multiplicative inverse using the Extended Euclidean Algorithm. Note: The modulus must be coprime to the current value for a valid inverse to exist.
  * **Time complexity:** $\mathcal{O}(\log(\text{Modulus}))$

* `static uint32_t mod()`
  Returns the `Modulus` parameter associated with this type.
  * **Time complexity:** $\mathcal{O}(1)$

* `static ModInt raw(uint32_t v)`
  Constructs a `ModInt` directly from an unsigned integer without applying the modulo operator. This is faster and should only be used if `v` is strictly less than `Modulus`.
  * **Time complexity:** $\mathcal{O}(1)$

## Operators

* **Arithmetic (`+`, `-`, `*`, `+=`, `-=`, `*=`):** Performs basic addition, subtraction, or multiplication with automatic modulo adjustments.
  * **Time complexity:** $\mathcal{O}(1)$
* **Division (`/`, `/=`):** Multiplies by the modular inverse of the right-hand side.
  * **Time complexity:** $\mathcal{O}(\log(\text{Modulus}))$
* **Increment/Decrement (`++`, `--`):** Safely wraps values around $0$ and $Modulus - 1$.
  * **Time complexity:** $\mathcal{O}(1)$
* **Comparison (`==`, `!=`):** Compares the internal values.
  * **Time complexity:** $\mathcal{O}(1)$
* **Stream I/O (`<<`, `>>`):** Inputs standard integers or outputs the internal value.
  * **Time complexity:** $\mathcal{O}(1)$

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
