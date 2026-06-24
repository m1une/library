---
title: Primitive Root
documentation_of: ../../math/primitive_root.hpp
---

## Overview

This header finds a primitive root modulo `mod`.

A primitive root is a residue whose powers generate every invertible residue
modulo `mod`. Equivalently, its multiplicative order is Euler's totient
function $\varphi(\text{mod})$.

Primitive roots do not exist for every modulus. They exist exactly for

* `2`;
* `4`;
* `p^k`, where `p` is an odd prime and `k >= 1`;
* `2 * p^k`, where `p` is an odd prime and `k >= 1`.

## API

```cpp
bool has_primitive_root(uint64_t mod);

uint64_t primitive_root(uint64_t mod);
```

`has_primitive_root(mod)` returns whether a primitive root exists.

`primitive_root(mod)` requires `mod >= 2`. It returns the smallest positive
primitive root modulo `mod`, or `0` when no primitive root exists.

The return value `0` is only used as a sentinel: a primitive root is always
coprime to `mod` and lies in `[1, mod)`.

## Complexity

The modulus and $\varphi(\text{mod})$ are factored with Pollard-Rho, so this
supports the full `uint64_t` range.

After factorization, candidates are tested from small to large. Each candidate
uses one modular exponentiation for each distinct prime divisor of
$\varphi(\text{mod})$.

## Example

```cpp
#include "math/primitive_root.hpp"

#include <cstdint>
#include <iostream>

int main() {
    uint64_t mod = 998244353;
    uint64_t root = m1une::math::primitive_root(mod);
    std::cout << root << "\n";  // 3

    std::cout << m1une::math::primitive_root(8) << "\n";  // 0
}
```
