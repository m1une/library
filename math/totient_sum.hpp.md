---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/totient_sum.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <unordered_map>\n#include <vector>\n\nnamespace m1une {\n\
    namespace math {\n\nstruct TotientSum {\n   private:\n    int _precalculation_limit;\n\
    \    std::vector<__uint128_t> _prefix_sum;\n    std::unordered_map<uint64_t, __uint128_t>\
    \ _memo;\n\n    __uint128_t solve(uint64_t n) {\n        if (n <= static_cast<uint64_t>(_precalculation_limit))\
    \ {\n            return _prefix_sum[static_cast<int>(n)];\n        }\n       \
    \ if (auto it = _memo.find(n); it != _memo.end()) {\n            return it->second;\n\
    \        }\n\n        const __uint128_t wide_n = n;\n        __uint128_t result\
    \ = wide_n * (wide_n + 1) / 2;\n        for (uint64_t left = 2; left <= n;) {\n\
    \            const uint64_t quotient = n / left;\n            const uint64_t right\
    \ = n / quotient;\n            result -= static_cast<__uint128_t>(right - left\
    \ + 1) * solve(quotient);\n            if (right == n) break;\n            left\
    \ = right + 1;\n        }\n\n        _memo.emplace(n, result);\n        return\
    \ result;\n    }\n\n   public:\n    explicit TotientSum(int precalculation_limit\
    \ = 1000000) : _precalculation_limit(precalculation_limit) {\n        assert(precalculation_limit\
    \ >= 0);\n\n        std::vector<uint64_t> phi(precalculation_limit + 1);\n   \
    \     std::vector<int> primes;\n        std::vector<bool> is_composite(precalculation_limit\
    \ + 1);\n        if (precalculation_limit >= 1) {\n            phi[1] = 1;\n \
    \       }\n        for (int value = 2; value <= precalculation_limit; value++)\
    \ {\n            if (!is_composite[value]) {\n                primes.push_back(value);\n\
    \                phi[value] = static_cast<uint64_t>(value - 1);\n            }\n\
    \            for (int prime : primes) {\n                if (value > precalculation_limit\
    \ / prime) break;\n                const int next = value * prime;\n         \
    \       is_composite[next] = true;\n                if (value % prime == 0) {\n\
    \                    phi[next] = phi[value] * static_cast<uint64_t>(prime);\n\
    \                    break;\n                }\n                phi[next] = phi[value]\
    \ * static_cast<uint64_t>(prime - 1);\n            }\n        }\n\n        _prefix_sum.assign(precalculation_limit\
    \ + 1, 0);\n        for (int value = 1; value <= precalculation_limit; value++)\
    \ {\n            _prefix_sum[value] = _prefix_sum[value - 1] + phi[value];\n \
    \       }\n    }\n\n    int precalculation_limit() const {\n        return _precalculation_limit;\n\
    \    }\n\n    // Returns sum_{i=1}^n phi(i).\n    __uint128_t prefix_sum(uint64_t\
    \ n) {\n        return solve(n);\n    }\n\n    __uint128_t operator()(uint64_t\
    \ n) {\n        return prefix_sum(n);\n    }\n};\n\ninline __uint128_t totient_sum(uint64_t\
    \ n, int precalculation_limit = 1000000) {\n    TotientSum solver(precalculation_limit);\n\
    \    return solver.prefix_sum(n);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_TOTIENT_SUM_HPP\n#define M1UNE_MATH_TOTIENT_SUM_HPP 1\n\
    \n#include <cassert>\n#include <cstdint>\n#include <unordered_map>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace math {\n\nstruct TotientSum {\n   private:\n  \
    \  int _precalculation_limit;\n    std::vector<__uint128_t> _prefix_sum;\n   \
    \ std::unordered_map<uint64_t, __uint128_t> _memo;\n\n    __uint128_t solve(uint64_t\
    \ n) {\n        if (n <= static_cast<uint64_t>(_precalculation_limit)) {\n   \
    \         return _prefix_sum[static_cast<int>(n)];\n        }\n        if (auto\
    \ it = _memo.find(n); it != _memo.end()) {\n            return it->second;\n \
    \       }\n\n        const __uint128_t wide_n = n;\n        __uint128_t result\
    \ = wide_n * (wide_n + 1) / 2;\n        for (uint64_t left = 2; left <= n;) {\n\
    \            const uint64_t quotient = n / left;\n            const uint64_t right\
    \ = n / quotient;\n            result -= static_cast<__uint128_t>(right - left\
    \ + 1) * solve(quotient);\n            if (right == n) break;\n            left\
    \ = right + 1;\n        }\n\n        _memo.emplace(n, result);\n        return\
    \ result;\n    }\n\n   public:\n    explicit TotientSum(int precalculation_limit\
    \ = 1000000) : _precalculation_limit(precalculation_limit) {\n        assert(precalculation_limit\
    \ >= 0);\n\n        std::vector<uint64_t> phi(precalculation_limit + 1);\n   \
    \     std::vector<int> primes;\n        std::vector<bool> is_composite(precalculation_limit\
    \ + 1);\n        if (precalculation_limit >= 1) {\n            phi[1] = 1;\n \
    \       }\n        for (int value = 2; value <= precalculation_limit; value++)\
    \ {\n            if (!is_composite[value]) {\n                primes.push_back(value);\n\
    \                phi[value] = static_cast<uint64_t>(value - 1);\n            }\n\
    \            for (int prime : primes) {\n                if (value > precalculation_limit\
    \ / prime) break;\n                const int next = value * prime;\n         \
    \       is_composite[next] = true;\n                if (value % prime == 0) {\n\
    \                    phi[next] = phi[value] * static_cast<uint64_t>(prime);\n\
    \                    break;\n                }\n                phi[next] = phi[value]\
    \ * static_cast<uint64_t>(prime - 1);\n            }\n        }\n\n        _prefix_sum.assign(precalculation_limit\
    \ + 1, 0);\n        for (int value = 1; value <= precalculation_limit; value++)\
    \ {\n            _prefix_sum[value] = _prefix_sum[value - 1] + phi[value];\n \
    \       }\n    }\n\n    int precalculation_limit() const {\n        return _precalculation_limit;\n\
    \    }\n\n    // Returns sum_{i=1}^n phi(i).\n    __uint128_t prefix_sum(uint64_t\
    \ n) {\n        return solve(n);\n    }\n\n    __uint128_t operator()(uint64_t\
    \ n) {\n        return prefix_sum(n);\n    }\n};\n\ninline __uint128_t totient_sum(uint64_t\
    \ n, int precalculation_limit = 1000000) {\n    TotientSum solver(precalculation_limit);\n\
    \    return solver.prefix_sum(n);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATH_TOTIENT_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/totient_sum.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-24 21:43:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
documentation_of: math/totient_sum.hpp
layout: document
title: Totient Sum
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
