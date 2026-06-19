---
title: Formal Power Series
documentation_of: ../../fps/formal_power_series.hpp
---

## Overview

`FormalPowerSeries<Mint>` is a vector-like polynomial and formal power
series type. Coefficients are stored from the constant term upward.

It provides the operations most often needed in polynomial problems:

* addition, subtraction, scalar multiplication, and fast multiplication;
* multiplication or division by a power of `x`;
* derivative, integral, and point evaluation;
* formal inverse, logarithm, exponential, integer power, and square root;
* polynomial quotient and remainder;
* Taylor shift from `f(x)` to `f(x + c)`.

## Type

```cpp
template <class Mint>
struct FormalPowerSeries : std::vector<Mint>;
```

`Mint` should be a static modular integer type with `mod()`, `val()`, `raw()`,
`pow()`, and `inv()`. The supplied `math/modint.hpp` types satisfy this
interface. Series functions assume a prime modulus, and degrees used by
integration must be smaller than the modulus.

## Basic Operations

Let `Fps` denote `FormalPowerSeries<Mint>`.
Here, `n` is the number of coefficients involved in the operation.

| Operation | Description | Complexity |
| --- | --- | --- |
| `f.shrink()` | Removes trailing zero coefficients. | $O(n)$ |
| `f.pre(n)` | Returns exactly the first `n` coefficients, padding with zero. | $O(n)$ |
| `f.reversed(n)` | Resizes to `n` when specified, then reverses coefficients. | $O(n)$ |
| `f + g`, `f - g` | Coefficient-wise addition or subtraction. | $O(n)$ |
| `f * g` | Polynomial convolution. | $O(n \log n)$ |
| `f * c`, `f / c` | Scalar multiplication or division. | $O(n)$ |
| `f << k` | Multiplies by $x^k$. | $O(n + k)$ |
| `f >> k` | Divides by $x^k$, discarding lower terms. | $O(n)$ |
| `f.derivative()` | Formal derivative. | $O(n)$ |
| `f.integral()` | Formal integral with constant term zero. | $O(n)$ |
| `f.evaluate(x)` | Evaluates by Horner's method. | $O(n)$ |

## Series Functions

| Method | Requirement | Result | Complexity |
| --- | --- | --- | --- |
| `f.inv(n)` | `f[0] != 0` | $1/f \pmod{x^n}$ | $O(n \log n)$ |
| `f.log(n)` | `f[0] == 1` | $\log f \pmod{x^n}$ | $O(n \log n)$ |
| `f.exp(n)` | `f[0] == 0` | $\exp f \pmod{x^n}$ | $O(n \log n)$ |
| `f.pow(k, n)` | `k >= 0` | $f^k \pmod{x^n}$ | $O(n \log n)$ |
| `f.sqrt(n)` | A square root exists | An optional $g$ with $g^2=f \pmod{x^n}$ | $O(n \log n)$ |

When `n` is omitted, the current series size is used. `sqrt` returns
`std::nullopt` if the leading degree is odd or its coefficient is not a
quadratic residue.

## Polynomial Operations

| Method | Description | Complexity |
| --- | --- | --- |
| `f.divmod(g)` | Returns the quotient and remainder of polynomial division. | $O(n \log n)$ |
| `f / g`, `f % g` | Returns only the quotient or remainder. | $O(n \log n)$ |
| `f.taylor_shift(c)` | Returns coefficients of `f(x + c)`. | $O(n \log n)$ |

The divisor must be nonzero. Taylor shift requires `f.size() < Mint::mod()`.

## Example

```cpp
#include "fps/formal_power_series.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};

    Fps inverse = f.inv(5);
    Fps logarithm = f.log(5);
    Fps cube = f.pow(3, 7);
    Fps shifted = f.taylor_shift(10);

    mint value = f.evaluate(4);
    std::cout << value << "\n";
}
```
