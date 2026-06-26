---
title: Monoid Power
documentation_of: ../../monoid/power.hpp
---

## Overview

A utility function that computes the $n$-th power of an element $a$ in a generic Monoid using binary exponentiation. It operates in $O(\log n)$ time.
This is highly useful for fast matrix exponentiation, string repetition, or finding the $n$-th composition of a function.

## Template Parameters

* `M`: A struct representing the mathematical monoid, satisfying the `m1une::monoid::IsMonoid` concept.

## Parameters

* `typename M::value_type a`: The base element.
* `long long n`: The exponent (number of times to apply the operation).

## Example

```cpp
#include "monoid/power.hpp"
#include "monoid/matrix.hpp"
#include <iostream>

using Mat = m1une::monoid::Matrix<long long, 2>;

int main() {
    Mat::value_type transition{};
    transition[0] = {1, 1};
    transition[1] = {1, 0};

    // Compute the 10th power of the Fibonacci transition matrix
    auto res = m1une::monoid::power<Mat>(transition, 10);

    std::cout << res[0][0] << "\n";
    return 0;
}
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
