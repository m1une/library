---
title: Multipoint Evaluation and Interpolation
documentation_of: ../../fps/multipoint_evaluation.hpp
---

## Overview

A subproduct tree supports fast evaluation of one polynomial at many points
and interpolation through many point-value pairs.

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

`product()` returns
$\prod_i (x-\mathrm{points}[i])$.

The free functions below are convenient when the tree is used once:

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

Interpolation requires all points to be distinct.

## Complexity

For `n` points, construction, evaluation, and interpolation each take
$O(n \log^2 n)$ time and $O(n \log n)$ temporary storage.

## Example

```cpp
#include "fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {3, 1, 4};
    std::vector<mint> points = {0, 2, 5};

    m1une::fps::SubproductTree<mint> tree(points);
    std::vector<mint> values = tree.evaluate(f);
    Fps restored = tree.interpolate(values);
}
```
