---
title: Totient Sum
documentation_of: ../../math/totient_sum.hpp
---

## Overview

This header computes the summatory Euler totient function:

$$
\sum_{i=1}^{n} \varphi(i).
$$

It combines a linear sieve for small values with the standard identity

$$
\sum_{d \mid m} \varphi(d) = m.
$$

Summing this over every `m` from `1` through `n` gives

$$
\sum_{m=1}^{n} m
= \sum_{m=1}^{n} \sum_{d \mid m} \varphi(d).
$$

Now swap the order of summation. A fixed `d` divides exactly
`floor(n / d)` integers in `[1, n]`, namely `d, 2d, 3d, ...`, so

$$
\sum_{m=1}^{n} m
= \sum_{d=1}^{n} \varphi(d) \left\lfloor \frac{n}{d} \right\rfloor.
$$

If

$$
S(n) = \sum_{i=1}^{n} \varphi(i),
$$

then the previous formula can also be written as

$$
\sum_{m=1}^{n} m
= \sum_{k=1}^{n} S\left(\left\lfloor\frac{n}{k}\right\rfloor\right).
$$

This is the same count from the other direction: `S(floor(n / k))` adds
`phi(d)` for every `d` with `k * d <= n`.

Solving this equation for the `k = 1` term, which is `S(n)`, gives the
recurrence used by the implementation:

$$
S(n)
= \frac{n(n+1)}{2}
  - \sum_{k=2}^{n} S\left(\left\lfloor\frac{n}{k}\right\rfloor\right).
$$

The `TotientSum` object memoizes large recursive states, so it is suitable for
multiple queries.

## API

```cpp
struct TotientSum {
    explicit TotientSum(int precalculation_limit = 1000000);

    int precalculation_limit() const;
    __uint128_t prefix_sum(uint64_t n);
    __uint128_t operator()(uint64_t n);
};

__uint128_t totient_sum(
    uint64_t n,
    int precalculation_limit = 1000000
);
```

`prefix_sum(n)` and `operator()(n)` both return

$$
\varphi(1) + \varphi(2) + \cdots + \varphi(n).
$$

For `n = 0`, the result is `0`.

The return type is `__uint128_t` because the summatory totient function grows
quadratically. Include `utilities/int128.hpp` as well if you want stream
operators or string conversion for 128-bit integers.

## Complexity

Construction takes $O(B)$ time and memory, where `B` is
`precalculation_limit`.

For one query with value `n`, the memoized recursive states are among the
distinct values `floor(n / k)` that are larger than `B`, so there are
$O(n / B)$ such states. Each state `x` is processed by quotient grouping in
$O(\sqrt x)$ time. Summed over all newly computed states, one query takes

$$
O\left(B + \frac{n}{\sqrt B}\right)
$$

time including construction, and uses $O(B + n/B)$ memory.

Choosing `B` around $n^{2/3}$ gives the usual $O(n^{2/3})$ total time and
$O(n^{2/3})$ memory for a single large query. The default `B = 1000000` is a
practical fixed choice; tune it when `n` is known to be much larger.

Repeated queries on the same `TotientSum` object reuse the cached large states.

## Example

```cpp
#include "math/totient_sum.hpp"
#include "utilities/int128.hpp"

#include <cstdint>
#include <iostream>

int main() {
    m1une::math::TotientSum solver;

    uint64_t n = 100;
    std::cout << solver.prefix_sum(n) << "\n";  // 3044

    std::cout << m1une::math::totient_sum(10) << "\n";  // 32
}
```
