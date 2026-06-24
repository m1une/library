---
title: Tetration
documentation_of: ../../math/tetration.hpp
---

## Overview

This header computes power towers quickly under a modulus.

For a repeated base, tetration means:

```text
tetration(base, 0) = 1
tetration(base, 1) = base
tetration(base, 2) = base^base
tetration(base, 3) = base^(base^base)
```

The implementation works for non-prime and non-coprime moduli. It recursively
uses Euler's totient function and lifts the exponent when the true exponent is
large enough. Totients are computed with the existing 64-bit Pollard-Rho
factorization library.

The ordinary modular exponent convention `0^0 = 1` is used. Therefore, for
example, `power_tower_mod({2, 0}, mod)` is `1 mod mod`.

## Functions

All functions are in namespace `m1une::math`. Bases must be non-negative
integers. Signed input types are accepted, but negative values are invalid and
asserted against in debug builds.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `uint64_t tetration_mod(base, height, mod)` | Returns `base^^height mod mod`. | Totient-chain factorization and logarithmic modular powers |
| `uint64_t tetration_bounded(base, height, limit)` | Returns `min(base^^height, limit)`. | `O(log limit)` effective recursion for `base >= 2` |
| `uint64_t power_tower_mod(vector<T> bases, mod)` | Returns `bases[0]^(bases[1]^(...)) mod mod`. Empty tower is `1`. | Totient-chain factorization and logarithmic modular powers |
| `uint64_t power_tower_bounded(vector<T> bases, limit)` | Returns `min(tower, limit)`. Empty tower is `1`. | Bounded by the tower length and `log limit` |

`mod` must be positive. If `mod == 1`, modular functions return `0`.

The bounded functions are useful for comparisons without big integers. For
example, `tetration_bounded(3, 4, 1000000)` returns `1000000`, meaning the true
value is at least that limit.

## Example

```cpp
#include "math/tetration.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << m1une::math::tetration_mod(2ULL, 4, 1000) << '\n';  // 536
    std::cout << m1une::math::tetration_mod(3ULL, 3, 100) << '\n';   // 87

    std::vector<unsigned long long> bases;
    bases.push_back(2);
    bases.push_back(3);
    bases.push_back(4);
    std::cout << m1une::math::power_tower_mod(bases, 1000000007) << '\n';

    if (m1une::math::tetration_bounded(2ULL, 5, 1000000) == 1000000) {
        std::cout << "large\n";
    }
}
```

## Notes

- `height = 0` is defined as an empty tower and equals `1`.
- An empty vector passed to `power_tower_mod` or `power_tower_bounded` also
  represents an empty tower and equals `1`.
- The return type is always `uint64_t`.
- The modulus may be composite; coprimality between the base and modulus is not
  required.
