---
title: Bitwise Convolution
documentation_of: ../../math/bitwise_convolution.hpp
---

## Overview

Bitwise convolutions indexed by masks:

- OR convolution groups pairs by `i | j`;
- AND convolution groups pairs by `i & j`;
- XOR convolution groups pairs by `i ^ j`.

The header also exposes the underlying subset, superset, and Walsh-Hadamard
transforms. The subset and superset transforms are defined in
`zeta_mobius_transform.hpp`, which this header includes.

```cpp
#include "math/bitwise_convolution.hpp"
```

All names are in `m1une::math`.

## Convolutions

For input arrays `a` and `b`, the functions compute:

$$
c_k = \sum_{i \mathbin{\mathrm{op}} j = k} a_i b_j.
$$

```cpp
template <typename T>
std::vector<T> bitwise_or_convolution(
    std::vector<T> first,
    std::vector<T> second
);

template <typename T>
std::vector<T> bitwise_and_convolution(
    std::vector<T> first,
    std::vector<T> second
);

template <typename T>
std::vector<T> bitwise_xor_convolution(
    std::vector<T> first,
    std::vector<T> second
);
```

The input vectors are passed by value, so they may be moved into the functions.
The originals passed by the caller are otherwise unchanged. The return type is
`std::vector<T>`.

| Function | Operation | Complexity |
| --- | --- | --- |
| `bitwise_or_convolution(a, b)` | `op` is bitwise OR. | $O(N \log N)$ |
| `bitwise_and_convolution(a, b)` | `op` is bitwise AND. | $O(N \log N)$ |
| `bitwise_xor_convolution(a, b)` | `op` is bitwise XOR. | $O(N \log N)$ |

If either input is empty, the result is empty. Otherwise both arrays are
zero-padded to the smallest power of two at least
`max(a.size(), b.size())`. The returned vector has that length.
Each function uses $O(N)$ additional memory.

The element type must support default construction, addition, subtraction, and
multiplication. XOR convolution additionally requires division by the transform
size and construction from that size. Integers work because the inverse
Walsh-Hadamard transform is exactly divisible; modular types require the
power-of-two transform size to be invertible.

## Transforms

All transforms operate in place and require a nonempty power-of-two length.

```cpp
template <typename T>
void walsh_hadamard_transform(
    std::vector<T>& values,
    bool inverse = false
);
```

The subset and superset transform signatures and their requirements on `T` are
documented in `zeta_mobius_transform.hpp`. The Walsh-Hadamard transform modifies
`values` directly and returns `void`.

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_zeta_transform(values)` | Replaces each mask with the sum over its submasks. | $O(N \log N)$ |
| `subset_mobius_transform(values)` | Inverts the subset zeta transform. | $O(N \log N)$ |
| `superset_zeta_transform(values)` | Replaces each mask with the sum over its supermasks. | $O(N \log N)$ |
| `superset_mobius_transform(values)` | Inverts the superset zeta transform. | $O(N \log N)$ |
| `walsh_hadamard_transform(values, inverse)` | Applies the XOR transform or its inverse. | $O(N \log N)$ |

For a mask $S$, subset zeta computes
$F(S) = \sum_{T \subseteq S} f(T)$, while superset zeta computes
$F(S) = \sum_{T \supseteq S} f(T)$. Their Möbius transforms recover $f$.

The Walsh-Hadamard transform computes
$F(S) = \sum_T (-1)^{\operatorname{popcount}(S \mathbin{\&} T)} f(T)$.
Passing `true` as the second argument applies the same butterflies and divides
every element by $N$, producing the inverse transform.

## Example

```cpp
#include "math/bitwise_convolution.hpp"
#include "math/modint.hpp"

#include <vector>

int main() {
    using mint = m1une::math::modint998244353;

    std::vector<mint> a{1, 2, 3, 4};
    std::vector<mint> b{5, 6, 7, 8};
    std::vector<mint> result =
        m1une::math::bitwise_xor_convolution(a, b);
}
```
