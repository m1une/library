---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/lucas.test.cpp
    title: verify/math/lucas.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/lucas.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\n\
    struct Lucas {\n   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint>\
    \ _inverse_factorial;\n\n    Mint small_binom(uint32_t n, uint32_t k) const {\n\
    \        if (k > n) return Mint(0);\n        return _factorial[n] * _inverse_factorial[k]\
    \ * _inverse_factorial[n - k];\n    }\n\n   public:\n    Lucas() {\n        const\
    \ uint32_t prime = Mint::mod();\n        assert(2 <= prime);\n        _factorial.resize(prime);\n\
    \        _inverse_factorial.resize(prime);\n        _factorial[0] = Mint(1);\n\
    \        for (uint32_t i = 1; i < prime; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[prime - 1] = _factorial[prime\
    \ - 1].inv();\n        for (uint32_t i = prime - 1; i > 0; i--) {\n          \
    \  _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);\n        }\n \
    \   }\n\n    uint32_t prime() const {\n        return Mint::mod();\n    }\n\n\
    \    Mint binom(uint64_t n, uint64_t k) const {\n        if (k > n) return Mint(0);\n\
    \        const uint64_t modulus = Mint::mod();\n        Mint result = Mint(1);\n\
    \        while (n > 0 || k > 0) {\n            uint32_t n_digit = uint32_t(n %\
    \ modulus);\n            uint32_t k_digit = uint32_t(k % modulus);\n         \
    \   if (k_digit > n_digit) return Mint(0);\n            result *= small_binom(n_digit,\
    \ k_digit);\n            n /= modulus;\n            k /= modulus;\n        }\n\
    \        return result;\n    }\n\n    Mint operator()(uint64_t n, uint64_t k)\
    \ const {\n        return binom(n, k);\n    }\n};\n\ntemplate <class Mint>\nusing\
    \ LucasTheorem = Lucas<Mint>;\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MATH_LUCAS_HPP\n#define M1UNE_MATH_LUCAS_HPP 1\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class Mint>\nstruct Lucas {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n    Mint small_binom(uint32_t\
    \ n, uint32_t k) const {\n        if (k > n) return Mint(0);\n        return _factorial[n]\
    \ * _inverse_factorial[k] * _inverse_factorial[n - k];\n    }\n\n   public:\n\
    \    Lucas() {\n        const uint32_t prime = Mint::mod();\n        assert(2\
    \ <= prime);\n        _factorial.resize(prime);\n        _inverse_factorial.resize(prime);\n\
    \        _factorial[0] = Mint(1);\n        for (uint32_t i = 1; i < prime; i++)\
    \ {\n            _factorial[i] = _factorial[i - 1] * Mint(i);\n        }\n   \
    \     _inverse_factorial[prime - 1] = _factorial[prime - 1].inv();\n        for\
    \ (uint32_t i = prime - 1; i > 0; i--) {\n            _inverse_factorial[i - 1]\
    \ = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    uint32_t prime()\
    \ const {\n        return Mint::mod();\n    }\n\n    Mint binom(uint64_t n, uint64_t\
    \ k) const {\n        if (k > n) return Mint(0);\n        const uint64_t modulus\
    \ = Mint::mod();\n        Mint result = Mint(1);\n        while (n > 0 || k >\
    \ 0) {\n            uint32_t n_digit = uint32_t(n % modulus);\n            uint32_t\
    \ k_digit = uint32_t(k % modulus);\n            if (k_digit > n_digit) return\
    \ Mint(0);\n            result *= small_binom(n_digit, k_digit);\n           \
    \ n /= modulus;\n            k /= modulus;\n        }\n        return result;\n\
    \    }\n\n    Mint operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\ntemplate <class Mint>\nusing LucasTheorem = Lucas<Mint>;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_LUCAS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/lucas.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-23 12:24:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/lucas.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/lucas.hpp
layout: document
title: Lucas's Theorem
---

## Overview

`Lucas<Mint>` computes binomial coefficients modulo a prime even when `n` and
`k` are much larger than the modulus.

Write the arguments in base `p`:

```text
n = n0 + n1 p + n2 p^2 + ...
k = k0 + k1 p + k2 p^2 + ...
```

Lucas's theorem states

```text
C(n, k) = product C(ni, ki) modulo p.
```

The class precomputes factorials and inverse factorials for every value below
`p`. Construction therefore costs `O(p)` time and memory, while each query
takes `O(log_p n)`.

`LucasTheorem<Mint>` is an alias for `Lucas<Mint>`.

## Requirements

`Mint` must provide the static-modulus interface used by `ModInt`, and its
modulus must be prime.

This implementation is intended for small or moderate primes because it stores
`2p` modular values. It is not appropriate for moduli such as `998244353` or
`1000000007`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Lucas()` | Precomputes factorial tables below the modulus. | `O(p)` |
| `uint32_t prime() const` | Returns the modulus. | `O(1)` |
| `Mint binom(uint64_t n, uint64_t k) const` | Returns `C(n, k)` modulo `p`; returns zero when `k > n`. | `O(log_p n)` |
| `Mint operator()(uint64_t n, uint64_t k) const` | Alias for `binom`. | `O(log_p n)` |

## Example

```cpp
#include "math/lucas.hpp"
#include "math/modint.hpp"
#include <iostream>

int main() {
    using Mint = m1une::math::ModInt<7>;
    m1une::math::Lucas<Mint> lucas;

    std::cout << lucas.binom(1000000000000000000ULL, 123456789ULL) << '\n';
    std::cout << lucas(100, 20) << '\n';
}
```
