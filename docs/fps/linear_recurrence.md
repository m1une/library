---
title: Linear Recurrence and Bostan-Mori
documentation_of: ../../fps/linear_recurrence.hpp
---

## Overview

Computes a distant coefficient of a rational generating function with the
Bostan-Mori algorithm. A convenience wrapper finds a term of a linear
recurrence without constructing all preceding terms.

## API

```cpp
template <class Mint>
Mint coefficient_of_rational(
    FormalPowerSeries<Mint> numerator,
    FormalPowerSeries<Mint> denominator,
    uint64_t index);
```

Returns the coefficient of $x^\mathrm{index}$ in
`numerator / denominator`. The denominator's constant term must be nonzero.

```cpp
template <class Mint>
Mint linear_recurrence_kth(
    const std::vector<Mint>& initial,
    const std::vector<Mint>& recurrence,
    uint64_t index);
```

For recurrence order `d`, the convention is:

```text
a[n] = recurrence[0] * a[n - 1]
     + recurrence[1] * a[n - 2]
     + ...
     + recurrence[d - 1] * a[n - d]
```

`initial` contains `a[0]` through `a[d - 1]`.

## Complexity

For recurrence order `d`, the running time is
$O(d \log d \log \mathrm{index})$ and the working memory is
$O(d)$ apart from convolution buffers.

## Example

```cpp
#include "fps/linear_recurrence.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<mint> initial = {0, 1};
    std::vector<mint> recurrence = {1, 1};
    mint fibonacci_100 = m1une::fps::linear_recurrence_kth(
        initial, recurrence, 100);
    std::cout << fibonacci_100 << "\n";
}
```
