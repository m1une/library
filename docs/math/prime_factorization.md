---
title: 64-bit Prime Factorization
documentation_of: ../../math/prime_factorization.hpp
---

## Overview

Deterministic Miller-Rabin primality testing and Pollard-Rho factorization for
the full `uint64_t` range. This is the general-purpose choice when values are
too large for a sieve.

For example,

$$
360 = 2^3 \cdot 3^2 \cdot 5.
$$

`prime_factors(360)` returns `2, 2, 2, 3, 3, 5`, while
`prime_factorize(360)` returns the pairs `(2, 3)`, `(3, 2)`, and `(5, 1)`.

Use `PrimeSieve` instead when every query is bounded by a reasonably small
known limit. A sieve has a setup cost but answers many small queries faster.

## Euler's Totient Function

Euler's totient function $\varphi(n)$ counts the integers from `1` through `n`
that are coprime to `n`. Two integers are coprime when their greatest common
divisor is `1`.

For example, the integers coprime to `12` are

```text
1, 5, 7, 11
```

so $\varphi(12) = 4$.

If the distinct prime divisors of `n` are $p_1, p_2, \ldots, p_k$, then

$$
\varphi(n)
= n
\left(1-\frac{1}{p_1}\right)
\left(1-\frac{1}{p_2}\right)
\cdots
\left(1-\frac{1}{p_k}\right).
$$

The products in this displayed formula are multiplicative: each parenthesized
factor is multiplied with `n` and with the other factors.

Equivalently, and often more clearly for implementation:

$$
\varphi(n) = n \prod_{p \mid n}\frac{p-1}{p}.
$$

Common uses include:

* counting reduced fractions with denominator `n`;
* working with multiplicative groups modulo `n`;
* reducing exponents using Euler's theorem:
  $a^{\varphi(n)} \equiv 1 \pmod n$ when `a` and `n` are coprime.

The library names this function `euler_phi` in this header and `totient` in
`PrimeSieve`.

## Mobius Function

The Mobius function $\mu(n)$ is defined from the prime factorization of `n`:

* $\mu(1) = 1$;
* $\mu(n) = 0$ if some prime square divides `n`;
* otherwise, $\mu(n) = (-1)^k$, where `k` is the number of distinct prime
  factors.

Examples:

| Value | Factorization | Mobius value | Reason |
| --- | --- | --- | --- |
| `1` | empty product | `1` | Definition |
| `6` | `2 * 3` | `1` | Two distinct prime factors |
| `30` | `2 * 3 * 5` | `-1` | Three distinct prime factors |
| `12` | `2^2 * 3` | `0` | A prime square divides it |

Its main competitive-programming use is inclusion-exclusion over divisors.
Mobius inversion says that if

$$
F(n) = \sum_{d \mid n} f(d),
$$

then

$$
f(n) = \sum_{d \mid n} \mu(d) F(n/d).
$$

This often converts counts over divisors into counts with an exact gcd, or
counts all pairs into counts of coprime pairs.

The conventional spelling is “Möbius”; the API uses ASCII name `mobius`.

## How the Algorithms Fit Together

Miller-Rabin tests whether a number is prime without trying every possible
divisor. For 64-bit integers, the fixed witness set used here makes the result
deterministic rather than merely probable.

Pollard-Rho searches for a nontrivial divisor of a composite number using a
pseudo-random sequence and gcd computations. Once it finds a divisor, the
implementation recursively factors both pieces and uses Miller-Rabin to know
when a piece is already prime.

## API

```cpp
bool is_prime(uint64_t value);

std::vector<uint64_t> prime_factors(uint64_t value);

std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value);

std::vector<uint64_t> divisors(uint64_t value);

uint64_t euler_phi(uint64_t value);

int mobius(uint64_t value);
```

Inputs use `uint64_t`, so negative integers are not accepted.
`prime_factorize` stores each prime as `uint64_t` and its exponent as `int`.
The Mobius function returns `int` because its result is always `-1`, `0`, or
`1`; the other numeric result uses `uint64_t`.

| Function | Description |
| --- | --- |
| `is_prime(x)` | Deterministically tests whether `x` is prime. |
| `prime_factors(x)` | Returns prime factors with multiplicity in increasing order. |
| `prime_factorize(x)` | Returns `(prime, exponent)` pairs in increasing order. |
| `divisors(x)` | Returns all positive divisors in increasing order. |
| `euler_phi(x)` | Returns Euler's totient function. |
| `mobius(x)` | Returns the Mobius function. |

All functions except `is_prime` require `x >= 1`.

`divisors(x)` includes both `1` and `x`. For example, the divisors of `12` are
`1, 2, 3, 4, 6, 12`.

## Complexity

Miller-Rabin uses a fixed seven-base witness set and takes
$O(\log x)$ modular multiplications.

Pollard-Rho has probabilistic expected running time of roughly
$O(x^{1/4})$ for finding a factor, and is very fast for ordinary 64-bit
competitive-programming inputs. The returned result is deterministic in
content even though the search uses pseudo-random polynomial parameters.

## Example

```cpp
#include "math/prime_factorization.hpp"

#include <cstdint>
#include <iostream>

int main() {
    uint64_t value = 360;
    for (const auto& factor : m1une::math::prime_factorize(value)) {
        std::cout << factor.first << "^" << factor.second << "\n";
    }

    std::cout << m1une::math::euler_phi(12) << "\n";  // 4
    std::cout << m1une::math::mobius(30) << "\n";     // -1
}
```
