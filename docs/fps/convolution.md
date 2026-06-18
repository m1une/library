---
title: Convolution
documentation_of: ../../fps/convolution.hpp
---

## Overview

Fast polynomial convolution for static modular integer types such as
`m1une::math::modint998244353`.

The implementation automatically chooses between:

* a quadratic loop for small inputs;
* one NTT convolution when the modulus supports the required transform length;
* three NTT convolutions plus CRT reconstruction for moduli such as
  `1000000007`.

## API

```cpp
template <class Mint>
std::vector<Mint> convolution(
    const std::vector<Mint>& a,
    const std::vector<Mint>& b);

template <class Mint>
std::vector<Mint> convolution_naive(
    const std::vector<Mint>& a,
    const std::vector<Mint>& b);
```

`convolution(a, b)[k]` is the sum of `a[i] * b[j]` over all `i + j = k`.
If either input is empty, the result is empty.

## Complexity

Let `n = a.size() + b.size()`.

* `convolution`: $\mathcal{O}(n \log n)$ for large inputs.
* `convolution_naive`: $\mathcal{O}(|a||b|)$.

For an NTT-friendly modulus, the transform length must divide
`Mint::mod() - 1`. The CRT fallback supports transform lengths up to
$2^{24}$ and requires the exact integer coefficient bound to fit in the
product of its three internal primes. These conditions cover ordinary
competitive-programming use with modulus `1000000007`.

## Example

```cpp
#include "fps/convolution.hpp"
#include "math/modint.hpp"

#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<mint> a = {1, 2, 3};
    std::vector<mint> b = {4, 5};
    std::vector<mint> c = m1une::fps::convolution(a, b);
    // c is 4, 13, 22, 15.
}
```
