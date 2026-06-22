---
title: Zeta and Mobius Transform
documentation_of: ../../math/zeta_mobius_transform.hpp
---

## Overview

This header provides zeta transforms and their Mobius inverses for subsets,
supersets, divisors, and multiples.

```cpp
#include "math/zeta_mobius_transform.hpp"
```

All functions operate in place.

The functions are templates over the array's element type:

```cpp
template <typename T>
void subset_zeta_transform(std::vector<T>& values);

template <typename T>
void subset_mobius_transform(std::vector<T>& values);

template <typename T>
void superset_zeta_transform(std::vector<T>& values);

template <typename T>
void superset_mobius_transform(std::vector<T>& values);

template <typename T>
void divisor_zeta_transform(std::vector<T>& values);

template <typename T>
void divisor_mobius_transform(std::vector<T>& values);

template <typename T>
void multiple_zeta_transform(std::vector<T>& values);

template <typename T>
void multiple_mobius_transform(std::vector<T>& values);
```

`T` may be an integer, floating-point type, modular integer, or another
user-defined type. Zeta transforms require `T` to support `operator+=`, while
Mobius transforms require `operator-=`. No multiplication or division is
performed. The vector is modified directly and no value is returned.

## Subset and Superset Transforms

These transforms use each array index as a bit mask. The array length must be a
nonzero power of two.

| Function | Result at mask `S` |
| --- | --- |
| `subset_zeta_transform(values)` | Sum of the original values over all submasks of `S`. |
| `subset_mobius_transform(values)` | Inverse of the subset zeta transform. |
| `superset_zeta_transform(values)` | Sum of the original values over all supermasks of `S`. |
| `superset_mobius_transform(values)` | Inverse of the superset zeta transform. |

For an array of length $N$, each transform takes $O(N \log N)$ time and
$O(1)$ additional memory.

## Divisor and Multiple Transforms

An array of length `N + 1` represents values for the integers from `1` through
`N`; element `0` is left unchanged.

| Function | Result at index `x` |
| --- | --- |
| `divisor_zeta_transform(values)` | Sum of the original values at all divisors of `x`. |
| `divisor_mobius_transform(values)` | Inverse of the divisor zeta transform. |
| `multiple_zeta_transform(values)` | Sum of the original values at all multiples of `x` through `N`. |
| `multiple_mobius_transform(values)` | Inverse of the multiple zeta transform. |

More precisely, the divisor zeta transform computes

$$
F(x) = \sum_{d \mid x} f(d),
$$

and the multiple zeta transform computes

$$
F(x) = \sum_{\substack{m \leq N \\ x \mid m}} f(m).
$$

The corresponding Mobius transform recovers `f` from `F`. The element type
must support addition and subtraction.

### Complexity

Each transform first enumerates all primes through `N` with the sieve of
Eratosthenes, which takes $O(N \log \log N)$ time and $O(N)$ temporary memory.

For every prime $p$, the transform visits $\lfloor N/p \rfloor$ indices.
Therefore the number of additions or subtractions is

$$
\sum_{p \leq N} \left\lfloor \frac{N}{p} \right\rfloor
= O\left(N \sum_{p \leq N}\frac{1}{p}\right)
= O(N \log \log N).
$$

Thus each zeta or Mobius transform takes $O(N \log \log N)$ total time and
$O(N)$ temporary memory. In particular, this is not the
$O(N \log N)$ loop that visits every divisor or multiple directly; processing
only prime transitions is sufficient to represent the divisibility relation.

Empty arrays and arrays containing only indices `0` or `0, 1` are accepted and
remain unchanged.

## Example

```cpp
#include "math/zeta_mobius_transform.hpp"

#include <vector>

int main() {
    std::vector<long long> values{0, 1, 2, 3, 4, 5, 6};
    m1une::math::divisor_zeta_transform(values);
    // values[6] is now 1 + 2 + 3 + 6 = 12.

    m1une::math::divisor_mobius_transform(values);
    // values is restored to its original contents.
}
```
