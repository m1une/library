---
title: Lagrange Inversion Formula
documentation_of: ../../fps/lagrange_inversion.hpp
---

## Overview

This header finds one coefficient of a formal power series that is defined
implicitly. You provide a series $\phi(t)$ and consider the unique series
$w(x)$ satisfying

$$w(x)=x\phi(w(x)).$$

The important point is that **`w` is defined by `phi`**. It is not another
function argument, and the library does not construct all of `w`. The Lagrange
inversion formula obtains the requested coefficient directly from $\phi$:

$$[x^n]w(x)=\frac{1}{n}[t^{n-1}]\phi(t)^n.$$

For example, if

$$\phi(t)=(1+t)^2,$$

then `w` means the solution of

$$w=x(1+w)^2=x+2x^2+5x^3+14x^4+\cdots.$$

The coefficient of $x^4$ is therefore `14`.

## Which Function Should I Use?

### Coefficient of `w`

```cpp
Mint lagrange_inversion_coefficient(const Fps& phi, int n);
```

Use this when `w` is defined by $w=x\phi(w)$ and you want $[x^n]w$.

```cpp
Fps phi = {1, 2, 1}; // phi(t) = (1+t)^2
mint answer = m1une::fps::lagrange_inversion_coefficient(phi, 4);
// answer = [x^4]w(x) = 14
```

### Coefficient after applying another series

```cpp
Mint lagrange_burmann_coefficient(
    const Fps& phi, const Fps& outer, int n);
```

This is the generalized form. As before, `phi` implicitly defines
$w=x\phi(w)$. The `outer` argument stores a second series $H(t)$. The function
returns

$$[x^n]H(w(x)).$$

It uses the Lagrange-Bürmann formula

$$[x^n]H(w(x))
=\frac{1}{n}[t^{n-1}]H'(t)\phi(t)^n.$$

For example:

```cpp
Fps phi = {1, 2, 1};  // w = x(1+w)^2
Fps outer = {0, 0, 1}; // H(t) = t^2

mint answer = m1une::fps::lagrange_burmann_coefficient(phi, outer, 5);
// answer = [x^5]H(w(x)) = [x^5]w(x)^2 = 48
```

The parameter correspondence is:

| C++ argument | Mathematical meaning |
| --- | --- |
| `phi` | Defines the otherwise-unwritten series `w` through $w=x\phi(w)$. |
| `outer` | Coefficients of $H(t)$. |
| `n` | The requested degree of $x$. |
| return value | $[x^n]H(w(x))$. |

### Coefficient of a compositional inverse

```cpp
Mint compositional_inverse_coefficient(const Fps& f, int n);
```

Use this when a series $f(t)$ is given directly and you want one coefficient
of its compositional inverse $g(x)$:

$$f(g(x))=x.$$

Internally, the function sets

$$\phi(t)=\frac{t}{f(t)},$$

so that $g=x\phi(g)$, and then applies the basic formula.

```cpp
Fps f = {0, 1, 1}; // f(t) = t+t^2
mint answer = m1une::fps::compositional_inverse_coefficient(f, 4);
// g(x) = x-x^2+2x^3-5x^4+...
// answer = -5 modulo mint::mod()
```

## Interface and Complexity

Let `Fps` denote `FormalPowerSeries<Mint>`.

| Function | Requirement | Result | Complexity |
| --- | --- | --- | --- |
| `Mint lagrange_inversion_coefficient(const Fps& phi, int n)` | `n > 0`, `phi[0] != 0` | $[x^n]w$, where $w=x\phi(w)$ | $O(n\log n)$ time, $O(n)$ memory |
| `Mint lagrange_burmann_coefficient(const Fps& phi, const Fps& outer, int n)` | `phi[0] != 0` when `n > 0` | $[x^n]H(w)$, where `outer` stores $H$ | $O(n\log n)$ time, $O(n)$ memory |
| `Mint compositional_inverse_coefficient(const Fps& f, int n)` | `f[0] == 0`, `f[1] != 0` | $[x^n]g$, where $f(g)=x$ | $O(n\log n)$ time, $O(n)$ memory |

Each call returns only one coefficient. Calling it separately for every degree
is not intended as a fast way to construct an entire compositional inverse.

For `n == 0`, `lagrange_burmann_coefficient` returns $H(0)$ and
`compositional_inverse_coefficient` returns zero.

## Requirements

`Mint` must satisfy the requirements of `FormalPowerSeries<Mint>`. The supplied
static modular integers are supported. The modulus is assumed to be prime, and
`n` must be smaller than the modulus so division by `n` is valid.

Missing coefficients above a series' stored size are treated as zero. None of
the input series are modified.

## Complete Example

```cpp
#include "fps/lagrange_inversion.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps phi = {1, 2, 1}; // phi(t) = (1+t)^2

    // Here w is implicitly defined as w = x(1+w)^2.
    mint coefficient_of_w =
        m1une::fps::lagrange_inversion_coefficient(phi, 4);

    Fps outer = {0, 0, 1}; // H(t) = t^2
    mint coefficient_of_w_squared =
        m1une::fps::lagrange_burmann_coefficient(phi, outer, 5);

    std::cout << coefficient_of_w << "\n";         // 14
    std::cout << coefficient_of_w_squared << "\n"; // 48
}
```
