---
title: Multipoint Evaluation and Interpolation
documentation_of: ../../fps/multipoint_evaluation.hpp
---

## Overview

This header provides a subproduct tree for two related polynomial operations:

* multipoint evaluation computes $f(x_i)$ for many points $x_i$;
* interpolation constructs the unique polynomial $f$ of degree less than $N$
  such that $f(x_i) = y_i$ for every point-value pair.

Building `SubproductTree` once is useful when several polynomials are evaluated
at the same points. The free functions provide the same operations when the
tree is needed only once.

## Complexity Notation

* `N` is the number of points.
* `D` is the number of coefficients in the polynomial being evaluated.

Polynomial multiplication uses the NTT-based convolution from
`fps/convolution.hpp`.

## Subproduct Tree

For each point $x_i$, a leaf stores the polynomial

$$
P_i(x) = x - x_i.
$$

Each internal node stores the product of its two children. Therefore, the root
contains

$$
P(x) = \prod_{i=0}^{N-1}(x - x_i).
$$

The tree stores $O(N \log N)$ coefficients in total.

### Multipoint Evaluation

Evaluation propagates polynomial remainders from the root toward the leaves.
If a node represents polynomial $P_v(x)$, it receives

$$
f(x) \bmod P_v(x).
$$

The remainder is reduced modulo each child polynomial and passed downward. At
leaf $i$, the modulus is $x - x_i$, so the constant remainder is exactly
$f(x_i)$.

This evaluates all points together instead of applying Horner's method
independently at every point.

### Interpolation

Interpolation requires the points to be distinct. Let

$$
P(x) = \prod_{i=0}^{N-1}(x - x_i).
$$

The tree first evaluates $P'(x)$ at every point and computes the leaf weights

$$
w_i = \frac{y_i}{P'(x_i)}.
$$

For an internal node with left and right product polynomials $P_L$ and $P_R$,
the corresponding interpolation polynomials are combined as

$$
F = F_L P_R + F_R P_L.
$$

At the root, this is the Lagrange interpolation polynomial through all
$(x_i, y_i)$. Distinct points guarantee that every $P'(x_i)$ is nonzero and
invertible.

## API

```cpp
template <class Mint>
struct SubproductTree {
    explicit SubproductTree(const std::vector<Mint>& points);

    int size() const;
    const FormalPowerSeries<Mint>& product() const;
    std::vector<Mint> evaluate(
        const FormalPowerSeries<Mint>& polynomial) const;
    FormalPowerSeries<Mint> interpolate(
        const std::vector<Mint>& values) const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `SubproductTree(points)` | Builds the product tree for `points`. | $O(N \log^2 N)$ |
| `int size() const` | Returns the number of points. | $O(1)$ |
| `const Fps& product() const` | Returns $\prod_i (x - x_i)$. For no points, returns the constant polynomial $1$. | $O(1)$ |
| `evaluate(polynomial) const` | Returns `polynomial(points[i])` for every point. | $O(D \log D + N \log^2 N)$ |
| `interpolate(values) const` | Returns the polynomial of degree less than `N` whose value at `points[i]` is `values[i]`. | $O(N \log^2 N)$ |

If `D <= N`, evaluation simplifies to $O(N \log^2 N)$. The tree itself uses
$O(N \log N)$ memory. Evaluation and interpolation use
$O(N \log N + D)$ auxiliary memory.

`interpolate` requires `values.size() == size()` and pairwise distinct points.
For an empty point set, evaluation returns an empty vector and interpolation
returns an empty polynomial.

## Free Functions

```cpp
template <class Mint>
std::vector<Mint> multipoint_evaluate(
    const FormalPowerSeries<Mint>& polynomial,
    const std::vector<Mint>& points);

template <class Mint>
FormalPowerSeries<Mint> polynomial_interpolate(
    const std::vector<Mint>& points,
    const std::vector<Mint>& values);
```

Each free function constructs a temporary `SubproductTree` and performs the
corresponding operation. Their bounds are therefore:

| Function | Complexity |
| --- | --- |
| `multipoint_evaluate` | $O(D \log D + N \log^2 N)$ |
| `polynomial_interpolate` | $O(N \log^2 N)$ |

## Reusing a Subproduct Tree

```cpp
#include "fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {3, 1, 4};
    std::vector<mint> points = {0, 2, 5};

    m1une::fps::SubproductTree<mint> tree(points);
    std::vector<mint> values = tree.evaluate(f);

    assert(values[0] == mint(3));
    assert(values[1] == mint(21));
    assert(values[2] == mint(108));

    Fps restored = tree.interpolate(values);
    assert(restored == f);
}
```

## One-Shot Multipoint Evaluation

Use `multipoint_evaluate` when the points are needed for only one polynomial.

```cpp
#include "fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    // f(x) = 2x^3 - x + 5
    Fps f = {5, -1, 0, 2};
    std::vector<mint> points = {-2, 0, 3};

    std::vector<mint> values =
        m1une::fps::multipoint_evaluate(f, points);

    assert(values[0] == mint(-9));
    assert(values[1] == mint(5));
    assert(values[2] == mint(56));
}
```

## One-Shot Polynomial Interpolation

Use `polynomial_interpolate` to recover the unique polynomial of degree less
than the number of distinct points.

```cpp
#include "fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    // The points lie on f(x) = x^2 + 2x + 3.
    std::vector<mint> points = {-1, 0, 2};
    std::vector<mint> values = {2, 3, 11};

    Fps f = m1une::fps::polynomial_interpolate(points, values);

    Fps expected = {3, 2, 1};
    assert(f == expected);
}
```

## Empty Inputs

Both free functions accept an empty point set.

```cpp
#include "fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};
    std::vector<mint> points;
    std::vector<mint> values;

    assert(m1une::fps::multipoint_evaluate(f, points).empty());
    assert(m1une::fps::polynomial_interpolate(points, values).empty());
}
```
