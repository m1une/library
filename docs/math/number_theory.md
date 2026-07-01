---
title: Number Theory
documentation_of: ../../math/number_theory.hpp
---

## Overview

Fast integer number-theory primitives for the extended Euclidean algorithm,
modular arithmetic, the Chinese remainder theorem, and floor sums. All
functions support 64-bit inputs and use wider intermediates where products
could overflow.

## Extended Greatest Common Divisor

`extended_gcd(a, b)` returns `(g, x, y)` satisfying Bézout's identity:

$$
g = \gcd(a,b) = ax + by.
$$

The returned gcd is nonnegative, and both inputs may be negative or zero. For
`a = b = 0`, the result is `(0, 0, 0)`. The coefficients are one valid
solution; they are not otherwise normalized.

The nonnegative gcd must fit in `long long`. In particular, an input whose gcd
is $2^{63}$ is outside the supported result range.

## Congruences and Modular Arithmetic

The notation

$$
x \equiv r \pmod m
$$

means that `x` and `r` have the same remainder when divided by `m`. Equivalently,
`x - r` is divisible by `m`.

For example, $23 \equiv 2 \pmod 7$ because both numbers leave remainder `2`,
and `23 - 2 = 21` is divisible by `7`.

### Modular Power

`pow_mod(x, exponent, mod)` computes

$$
x^{\text{exponent}} \bmod \text{mod}
$$

without constructing the enormous integer power first. Binary exponentiation
uses only logarithmically many multiplications, so even exponents near
$10^{18}$ are practical.

This is useful for modular counting answers, repeated transformations, and
number-theory algorithms such as primality testing.

### Modular Inverse

A modular inverse of `x` modulo `mod` is a number `y` satisfying

$$
x y \equiv 1 \pmod{\text{mod}}.
$$

For example, the inverse of `3` modulo `11` is `4`, because
$3 \cdot 4 = 12 \equiv 1 \pmod {11}$.

An inverse exists exactly when `x` and `mod` are coprime, meaning their greatest
common divisor is `1`. `inv_mod(x, mod)` requires this condition.

`inv_gcd(x, mod)` is the more general primitive. It returns `(g, y)`, where
`g = gcd(x, mod)` and

$$
x y \equiv g \pmod{\text{mod}}.
$$

For `inv_gcd(6, 15)`, one valid result is `(3, 3)` because
$6 \cdot 3 = 18 \equiv 3 \pmod {15}$.

## Chinese Remainder Theorem

The Chinese remainder theorem combines several remainder constraints into one.
For example:

$$
\begin{aligned}
x &\equiv 2 \pmod 3,\\
x &\equiv 3 \pmod 5,\\
x &\equiv 2 \pmod 7.
\end{aligned}
$$

The smallest nonnegative solution is `23`. Every other solution is
$23 + 105k$, because `105` is the least common multiple of the moduli.
Therefore `crt` returns `(23, 105)`.

The moduli do not need to be pairwise coprime. A solution merely needs to be
consistent. For example, `x` cannot be both even and congruent to `1` modulo
`4`, so constraints `x = 0 mod 2` and `x = 1 mod 4` cause `crt` to return
`(0, 0)`.

Typical uses include:

* combining answers computed under several moduli;
* finding the first time that several periodic events coincide;
* solving simultaneous divisibility or remainder constraints.

## Floor Sum

`floor_sum(n, mod, a, b)` computes

$$
\sum_{i=0}^{n-1}
\left\lfloor \frac{a i+b}{\text{mod}} \right\rfloor.
$$

For `n = 4`, `mod = 10`, `a = 6`, and `b = 3`, the terms are

$$
\left\lfloor\frac{3}{10}\right\rfloor +
\left\lfloor\frac{9}{10}\right\rfloor +
\left\lfloor\frac{15}{10}\right\rfloor +
\left\lfloor\frac{21}{10}\right\rfloor
= 0 + 0 + 1 + 2 = 3.
$$

A direct loop costs $O(n)$. This function repeatedly transforms the problem in
a Euclidean-algorithm-like way and costs only logarithmic time.

Floor sums appear when:

* counting lattice points below a line;
* summing quotient or remainder patterns;
* counting integers satisfying linear inequalities;
* optimizing periodic arithmetic sequences.

## API

```cpp
std::tuple<long long, long long, long long> extended_gcd(
    long long a,
    long long b
);

long long pow_mod(
    long long x,
    unsigned long long exponent,
    long long mod
);

std::pair<long long, long long> inv_gcd(
    long long x,
    long long mod
);

long long inv_mod(long long x, long long mod);

std::pair<long long, long long> crt(
    const std::vector<long long>& remainders,
    const std::vector<long long>& moduli
);

long long floor_sum(
    long long n,
    long long mod,
    long long a,
    long long b
);
```

All scalar inputs and outputs use `long long`, except that `pow_mod` accepts an
`unsigned long long` exponent. `extended_gcd` returns a three-element tuple;
the other multi-value functions return `std::pair<long long, long long>`. `crt`
reads its two vectors by const reference and does not modify them.

| Function | Description | Complexity |
| --- | --- | --- |
| `extended_gcd(a, b)` | Returns `(g, x, y)` with `g = gcd(a, b)` and `a * x + b * y = g`. | $O(\log(\max(|a|, |b|)+1))$ |
| `pow_mod(x, exponent, mod)` | Returns `x` raised to `exponent` modulo `mod`. | $O(\log(\text{exponent}))$ |
| `inv_gcd(x, mod)` | Returns the gcd and a normalized inverse of `x / gcd` modulo `mod / gcd`. | $O(\log(\text{mod}))$ |
| `inv_mod(x, mod)` | Returns the modular inverse of `x`. The arguments must be coprime. | $O(\log(\text{mod}))$ |
| `crt(remainders, moduli)` | Solves a possibly non-coprime system with the Chinese remainder theorem. | $O(k \log M)$ |
| `floor_sum(n, mod, a, b)` | Returns the sum of `floor((a * i + b) / mod)` over `0 <= i < n`. | $O(\log(\max(a, mod)))$ |

`crt` returns the smallest nonnegative solution and the least common multiple
of the moduli. It returns `(0, 0)` when no solution exists. The least common
multiple must fit in `long long`.

`floor_sum` accepts negative `a` and `b`; its result must fit in `long long`.

## Example

```cpp
#include "math/number_theory.hpp"

#include <iostream>
#include <vector>

int main() {
    auto [gcd, x, y] = m1une::math::extended_gcd(30, 18);
    std::cout << gcd << " " << x << " " << y << "\n"; // 6 -1 2

    auto solution = m1une::math::crt(
        std::vector<long long>{2, 3, 2},
        std::vector<long long>{3, 5, 7}
    );
    std::cout << solution.first << " " << solution.second << "\n";  // 23 105

    std::cout << m1une::math::inv_mod(3, 11) << "\n";  // 4
    std::cout << m1une::math::floor_sum(4, 10, 6, 3) << "\n";  // 3
}
```
