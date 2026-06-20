---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/floor_sum.test.cpp
    title: verify/math/floor_sum.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/number_theory.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <limits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace internal {\n\ninline long long safe_mod(long\
    \ long x, long long mod) {\n    x %= mod;\n    if (x < 0) x += mod;\n    return\
    \ x;\n}\n\ninline unsigned __int128 floor_sum_unsigned(unsigned long long n, unsigned\
    \ long long mod, unsigned long long a,\n                                     \
    \       unsigned long long b) {\n    unsigned __int128 answer = 0;\n    while\
    \ (true) {\n        if (a >= mod) {\n            answer += static_cast<unsigned\
    \ __int128>(n) * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n\
    \        if (b >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (b / mod);\n            b %= mod;\n        }\n\n        const unsigned __int128\
    \ y_max = static_cast<unsigned __int128>(a) * n + b;\n        if (y_max < mod)\
    \ break;\n        n = static_cast<unsigned long long>(y_max / mod);\n        b\
    \ = static_cast<unsigned long long>(y_max % mod);\n        unsigned long long\
    \ tmp = mod;\n        mod = a;\n        a = tmp;\n    }\n    return answer;\n\
    }\n\n}  // namespace internal\n\ninline long long pow_mod(long long x, unsigned\
    \ long long exponent, long long mod) {\n    assert(mod >= 1);\n    if (mod ==\
    \ 1) return 0;\n\n    unsigned long long base = static_cast<unsigned long long>(internal::safe_mod(x,\
    \ mod));\n    unsigned long long result = 1;\n    const unsigned long long unsigned_mod\
    \ = static_cast<unsigned long long>(mod);\n    while (exponent > 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(result) * base % unsigned_mod);\n        }\n        base = static_cast<unsigned\
    \ long long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);\n  \
    \      exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n}\n\
    \n// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n//\
    \ modulo mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long\
    \ long, long long> inv_gcd(long long a, long long mod) {\n    assert(mod >= 1);\n\
    \    a = internal::safe_mod(a, mod);\n    if (a == 0) return {mod, 0};\n\n   \
    \ long long s = mod;\n    long long t = a;\n    long long m0 = 0;\n    long long\
    \ m1 = 1;\n    while (t > 0) {\n        const long long quotient = s / t;\n  \
    \      s -= t * quotient;\n        m0 -= m1 * quotient;\n\n        long long tmp\
    \ = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n\
    \        m1 = tmp;\n    }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n\
    }\n\ninline long long inv_mod(long long x, long long mod) {\n    const auto result\
    \ = inv_gcd(x, mod);\n    assert(result.first == 1);\n    return result.second;\n\
    }\n\n// Returns the smallest nonnegative solution and the least common multiple\
    \ of\n// the moduli. Returns {0, 0} when the system is inconsistent.\ninline std::pair<long\
    \ long, long long> crt(const std::vector<long long>& remainders,\n           \
    \                                const std::vector<long long>& moduli) {\n   \
    \ assert(remainders.size() == moduli.size());\n\n    long long r0 = 0;\n    long\
    \ long m0 = 1;\n    for (int i = 0; i < int(remainders.size()); i++) {\n     \
    \   assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
    \ moduli[i]);\n        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n \
    \           long long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n\
    \            tmp = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n\n        const auto inverse = inv_gcd(m0,\
    \ m1);\n        const long long gcd = inverse.first;\n        const long long\
    \ reduced_modulus = m1 / gcd;\n        const __int128 difference = static_cast<__int128>(r1)\
    \ - r0;\n        if (difference % gcd != 0) return {0, 0};\n\n        __int128\
    \ multiplier = difference / gcd % reduced_modulus;\n        multiplier = multiplier\
    \ * inverse.second % reduced_modulus;\n        if (multiplier < 0) multiplier\
    \ += reduced_modulus;\n\n        const __int128 new_modulus = static_cast<__int128>(m0)\
    \ * reduced_modulus;\n        assert(new_modulus <= std::numeric_limits<long long>::max());\n\
    \        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n\
    \        new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_NUMBER_THEORY_HPP\n#define M1UNE_MATH_NUMBER_THEORY_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal\
    \ {\n\ninline long long safe_mod(long long x, long long mod) {\n    x %= mod;\n\
    \    if (x < 0) x += mod;\n    return x;\n}\n\ninline unsigned __int128 floor_sum_unsigned(unsigned\
    \ long long n, unsigned long long mod, unsigned long long a,\n               \
    \                             unsigned long long b) {\n    unsigned __int128 answer\
    \ = 0;\n    while (true) {\n        if (a >= mod) {\n            answer += static_cast<unsigned\
    \ __int128>(n) * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n\
    \        if (b >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (b / mod);\n            b %= mod;\n        }\n\n        const unsigned __int128\
    \ y_max = static_cast<unsigned __int128>(a) * n + b;\n        if (y_max < mod)\
    \ break;\n        n = static_cast<unsigned long long>(y_max / mod);\n        b\
    \ = static_cast<unsigned long long>(y_max % mod);\n        unsigned long long\
    \ tmp = mod;\n        mod = a;\n        a = tmp;\n    }\n    return answer;\n\
    }\n\n}  // namespace internal\n\ninline long long pow_mod(long long x, unsigned\
    \ long long exponent, long long mod) {\n    assert(mod >= 1);\n    if (mod ==\
    \ 1) return 0;\n\n    unsigned long long base = static_cast<unsigned long long>(internal::safe_mod(x,\
    \ mod));\n    unsigned long long result = 1;\n    const unsigned long long unsigned_mod\
    \ = static_cast<unsigned long long>(mod);\n    while (exponent > 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(result) * base % unsigned_mod);\n        }\n        base = static_cast<unsigned\
    \ long long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);\n  \
    \      exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n}\n\
    \n// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n//\
    \ modulo mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long\
    \ long, long long> inv_gcd(long long a, long long mod) {\n    assert(mod >= 1);\n\
    \    a = internal::safe_mod(a, mod);\n    if (a == 0) return {mod, 0};\n\n   \
    \ long long s = mod;\n    long long t = a;\n    long long m0 = 0;\n    long long\
    \ m1 = 1;\n    while (t > 0) {\n        const long long quotient = s / t;\n  \
    \      s -= t * quotient;\n        m0 -= m1 * quotient;\n\n        long long tmp\
    \ = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n\
    \        m1 = tmp;\n    }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n\
    }\n\ninline long long inv_mod(long long x, long long mod) {\n    const auto result\
    \ = inv_gcd(x, mod);\n    assert(result.first == 1);\n    return result.second;\n\
    }\n\n// Returns the smallest nonnegative solution and the least common multiple\
    \ of\n// the moduli. Returns {0, 0} when the system is inconsistent.\ninline std::pair<long\
    \ long, long long> crt(const std::vector<long long>& remainders,\n           \
    \                                const std::vector<long long>& moduli) {\n   \
    \ assert(remainders.size() == moduli.size());\n\n    long long r0 = 0;\n    long\
    \ long m0 = 1;\n    for (int i = 0; i < int(remainders.size()); i++) {\n     \
    \   assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
    \ moduli[i]);\n        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n \
    \           long long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n\
    \            tmp = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n\n        const auto inverse = inv_gcd(m0,\
    \ m1);\n        const long long gcd = inverse.first;\n        const long long\
    \ reduced_modulus = m1 / gcd;\n        const __int128 difference = static_cast<__int128>(r1)\
    \ - r0;\n        if (difference % gcd != 0) return {0, 0};\n\n        __int128\
    \ multiplier = difference / gcd % reduced_modulus;\n        multiplier = multiplier\
    \ * inverse.second % reduced_modulus;\n        if (multiplier < 0) multiplier\
    \ += reduced_modulus;\n\n        const __int128 new_modulus = static_cast<__int128>(m0)\
    \ * reduced_modulus;\n        assert(new_modulus <= std::numeric_limits<long long>::max());\n\
    \        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n\
    \        new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_MATH_NUMBER_THEORY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/number_theory.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-20 09:18:49+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/math/floor_sum.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/number_theory.hpp
layout: document
title: Number Theory
---

## Overview

Fast integer number-theory primitives for modular arithmetic and floor sums.
All functions support 64-bit inputs and use wider intermediates where products
could overflow.

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

| Function | Description | Complexity |
| --- | --- | --- |
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
    auto solution = m1une::math::crt(
        std::vector<long long>{2, 3, 2},
        std::vector<long long>{3, 5, 7}
    );
    std::cout << solution.first << " " << solution.second << "\n";  // 23 105

    std::cout << m1une::math::inv_mod(3, 11) << "\n";  // 4
    std::cout << m1une::math::floor_sum(4, 10, 6, 3) << "\n";  // 3
}
```
