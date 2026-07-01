---
title: ModInt
documentation_of: ../../math/modint.hpp
---

## Overview

A struct for automatic modular arithmetic. It wraps standard integer types to safely and automatically apply modulo operations during addition, subtraction, multiplication, and division. This is highly useful in competitive programming to prevent integer overflow and simplify code syntax.

Two integers represent the same modular value when their difference is
divisible by the modulus. For example, modulo `7`, the values `2`, `9`, and
`-5` are equivalent.

`ModInt<7>` stores all of them as the normalized representative `2`.

## Division and Modular Inverses

Modular division is not ordinary integer division. Dividing by `b` means
multiplying by a value `b.inv()` such that

$$
b \cdot b^{-1} \equiv 1 \pmod{\text{Modulus}}.
$$

For example, modulo `11`, the inverse of `3` is `4`, because
$3 \cdot 4 = 12$ has remainder `1`.

An inverse exists only when the value and modulus are coprime. In particular,
with a prime modulus, every nonzero value has an inverse. This is why prime
moduli such as `998244353` and `1000000007` are common in counting problems.

## Template Parameters

```cpp
template <uint32_t Modulus>
struct ModInt;
```

`Modulus` is a compile-time `uint32_t` value. `ModInt<Modulus>` is the value
type returned by arithmetic operators and by `pow`, `inv`, and `raw`.

## Type Aliases

For convenience, the library provides the following common type aliases:
* `using modint998244353 = ModInt<998244353>;`
* `using modint1000000007 = ModInt<1000000007>;`

## Constructors

| Constructor | Description | Complexity |
| --- | --- | --- |
| `ModInt()` | Initializes the value to `0`. | $O(1)$ |
| `template<class Integer> ModInt(Integer v)` | Initializes from any standard integral type. Negative values are normalized, and wide unsigned values are reduced without narrowing first. | $O(1)$ |

The integral constructor accepts types such as `int`, `long long`,
`unsigned long`, and `std::mt19937::result_type` without ambiguous overloads.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `uint32_t val() const` | Returns the stored value in `[0, Modulus - 1]`. | $O(1)$ |
| `ModInt pow(long long n) const` | Computes the `n`-th power by binary exponentiation. | $O(\log n)$ |
| `ModInt inv() const` | Computes the modular inverse by the extended Euclidean algorithm. The value and modulus must be coprime. | $O(\log(\text{Modulus}))$ |
| `static uint32_t mod()` | Returns the modulus associated with this type. | $O(1)$ |
| `static ModInt raw(uint32_t v)` | Constructs directly from `v` without applying `% Modulus`. Use only when `v < Modulus`. | $O(1)$ |

## Operators

Binary arithmetic and comparison operators take another
`const ModInt<Modulus>&`. Compound assignment returns `ModInt<Modulus>&`;
ordinary arithmetic returns a new `ModInt<Modulus>` by value. Prefix increment
and decrement return a reference, while postfix increment and decrement return
the previous value.

| Operators | Description | Complexity |
| --- | --- | --- |
| `+`, `-`, `*`, `+=`, `-=`, `*=` | Performs addition, subtraction, or multiplication with automatic modulo adjustment. | $O(1)$ |
| `/`, `/=` | Multiplies by the modular inverse of the right-hand side. | $O(\log(\text{Modulus}))$ |
| `++`, `--` | Increments or decrements while wrapping around `0` and `Modulus - 1`. | $O(1)$ |
| `==`, `!=` | Compares stored values. | $O(1)$ |
| `<<`, `>>` | Outputs the stored value or inputs a standard integer. | $O(1)$ |

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
