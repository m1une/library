---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/factorize.test.cpp
    title: verify/math/factorize.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/primality_test.test.cpp
    title: verify/math/primality_test.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prime_factorization.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal\
    \ {\n\ninline uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t mod) {\n\
    \    return static_cast<uint64_t>(static_cast<unsigned __int128>(a) * b % mod);\n\
    }\n\ninline uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t mod)\
    \ {\n    uint64_t result = 1;\n    while (exponent > 0) {\n        if (exponent\
    \ & 1) result = multiply_mod(result, base, mod);\n        base = multiply_mod(base,\
    \ base, mod);\n        exponent >>= 1;\n    }\n    return result;\n}\n\ninline\
    \ uint64_t pollard_random() {\n    static uint64_t state = 0x123456789abcdef0ULL;\n\
    \    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t value = state;\n    value =\
    \ (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n    value = (value ^ (value\
    \ >> 27)) * 0x94d049bb133111ebULL;\n    return value ^ (value >> 31);\n}\n\n}\
    \  // namespace internal\n\ninline bool is_prime(uint64_t value) {\n    if (value\
    \ < 2) return false;\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL,\
    \ 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime\
    \ == 0) return value == prime;\n    }\n\n    uint64_t odd_part = value - 1;\n\
    \    int power_of_two = 0;\n    while ((odd_part & 1) == 0) {\n        odd_part\
    \ >>= 1;\n        power_of_two++;\n    }\n\n    for (uint64_t base : {2ULL, 325ULL,\
    \ 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {\n        if (base\
    \ % value == 0) continue;\n        uint64_t x = internal::power_mod(base % value,\
    \ odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\n     \
    \   bool composite = true;\n        for (int i = 1; i < power_of_two; i++) {\n\
    \            x = internal::multiply_mod(x, x, value);\n            if (x == value\
    \ - 1) {\n                composite = false;\n                break;\n       \
    \     }\n        }\n        if (composite) return false;\n    }\n    return true;\n\
    }\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value) {\n \
    \   for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_MATH_PRIME_FACTORIZATION_HPP\n#define M1UNE_MATH_PRIME_FACTORIZATION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ math {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t a, uint64_t\
    \ b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(a)\
    \ * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t exponent,\
    \ uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0) {\n    \
    \    if (exponent & 1) result = multiply_mod(result, base, mod);\n        base\
    \ = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n    return\
    \ result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t state\
    \ = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime : {2ULL,\
    \ 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n\
    \        if (value % prime == 0) return value == prime;\n    }\n\n    uint64_t\
    \ odd_part = value - 1;\n    int power_of_two = 0;\n    while ((odd_part & 1)\
    \ == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n    }\n\n    for\
    \ (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})\
    \ {\n        if (base % value == 0) continue;\n        uint64_t x = internal::power_mod(base\
    \ % value, odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\
    \n        bool composite = true;\n        for (int i = 1; i < power_of_two; i++)\
    \ {\n            x = internal::multiply_mod(x, x, value);\n            if (x ==\
    \ value - 1) {\n                composite = false;\n                break;\n \
    \           }\n        }\n        if (composite) return false;\n    }\n    return\
    \ true;\n}\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value)\
    \ {\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    #endif  // M1UNE_MATH_PRIME_FACTORIZATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime_factorization.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-20 09:18:49+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/math/primality_test.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/factorize.test.cpp
documentation_of: math/prime_factorization.hpp
layout: document
title: 64-bit Prime Factorization
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
