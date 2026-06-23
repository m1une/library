---
title: Lucas's Theorem
documentation_of: ../../math/lucas.hpp
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
