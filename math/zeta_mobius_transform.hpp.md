---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bitwise_convolution.test.cpp
    title: verify/math/bitwise_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/zeta_mobius_transform.test.cpp
    title: verify/math/zeta_mobius_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace zeta_mobius_transform_detail {\n\ninline bool is_power_of_two(std::size_t\
    \ size) noexcept {\n    return size != 0 && (size & (size - 1)) == 0;\n}\n\ninline\
    \ std::vector<std::size_t> primes_up_to(std::size_t limit) {\n    std::vector<std::size_t>\
    \ primes;\n    std::vector<bool> is_prime(limit + 1, true);\n    if (!is_prime.empty())\
    \ is_prime[0] = false;\n    if (limit >= 1) is_prime[1] = false;\n    for (std::size_t\
    \ value = 2; value <= limit; ++value) {\n        if (!is_prime[value]) continue;\n\
    \        primes.emplace_back(value);\n        if (value > limit / value) continue;\n\
    \        for (\n            std::size_t multiple = value * value;\n          \
    \  multiple <= limit;\n            multiple += value\n        ) {\n          \
    \  is_prime[multiple] = false;\n        }\n    }\n    return primes;\n}\n\n} \
    \ // namespace zeta_mobius_transform_detail\n\ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>&\
    \ values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ += values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\n#define M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline\
    \ bool is_power_of_two(std::size_t size) noexcept {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/zeta_mobius_transform.hpp
  requiredBy:
  - math/bitwise_convolution.hpp
  - math/all.hpp
  timestamp: '2026-06-22 22:56:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/bitwise_convolution.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/zeta_mobius_transform.test.cpp
documentation_of: math/zeta_mobius_transform.hpp
layout: document
title: Zeta and Mobius Transform
---

## Overview

This header provides zeta transforms and their Mobius inverses for subsets,
supersets, divisors, and multiples.

```cpp
#include "math/zeta_mobius_transform.hpp"
```

All functions operate in place.

The functions are templates over the array's element type:

```cpp
template <typename T>
void subset_zeta_transform(std::vector<T>& values);

template <typename T>
void subset_mobius_transform(std::vector<T>& values);

template <typename T>
void superset_zeta_transform(std::vector<T>& values);

template <typename T>
void superset_mobius_transform(std::vector<T>& values);

template <typename T>
void divisor_zeta_transform(std::vector<T>& values);

template <typename T>
void divisor_mobius_transform(std::vector<T>& values);

template <typename T>
void multiple_zeta_transform(std::vector<T>& values);

template <typename T>
void multiple_mobius_transform(std::vector<T>& values);
```

`T` may be an integer, floating-point type, modular integer, or another
user-defined type. Zeta transforms require `T` to support `operator+=`, while
Mobius transforms require `operator-=`. No multiplication or division is
performed. The vector is modified directly and no value is returned.

## Subset and Superset Transforms

These transforms use each array index as a bit mask. The array length must be a
nonzero power of two.

| Function | Result at mask `S` |
| --- | --- |
| `subset_zeta_transform(values)` | Sum of the original values over all submasks of `S`. |
| `subset_mobius_transform(values)` | Inverse of the subset zeta transform. |
| `superset_zeta_transform(values)` | Sum of the original values over all supermasks of `S`. |
| `superset_mobius_transform(values)` | Inverse of the superset zeta transform. |

For an array of length $N$, each transform takes $O(N \log N)$ time and
$O(1)$ additional memory.

## Divisor and Multiple Transforms

An array of length `N + 1` represents values for the integers from `1` through
`N`; element `0` is left unchanged.

| Function | Result at index `x` |
| --- | --- |
| `divisor_zeta_transform(values)` | Sum of the original values at all divisors of `x`. |
| `divisor_mobius_transform(values)` | Inverse of the divisor zeta transform. |
| `multiple_zeta_transform(values)` | Sum of the original values at all multiples of `x` through `N`. |
| `multiple_mobius_transform(values)` | Inverse of the multiple zeta transform. |

More precisely, the divisor zeta transform computes

$$
F(x) = \sum_{d \mid x} f(d),
$$

and the multiple zeta transform computes

$$
F(x) = \sum_{\substack{m \leq N \\ x \mid m}} f(m).
$$

The corresponding Mobius transform recovers `f` from `F`. The element type
must support addition and subtraction.

### Complexity

Each transform first enumerates all primes through `N` with the sieve of
Eratosthenes, which takes $O(N \log \log N)$ time and $O(N)$ temporary memory.

For every prime $p$, the transform visits $\lfloor N/p \rfloor$ indices.
Therefore the number of additions or subtractions is

$$
\sum_{p \leq N} \left\lfloor \frac{N}{p} \right\rfloor
= O\left(N \sum_{p \leq N}\frac{1}{p}\right)
= O(N \log \log N).
$$

Thus each zeta or Mobius transform takes $O(N \log \log N)$ total time and
$O(N)$ temporary memory. In particular, this is not the
$O(N \log N)$ loop that visits every divisor or multiple directly; processing
only prime transitions is sufficient to represent the divisibility relation.

Empty arrays and arrays containing only indices `0` or `0, 1` are accepted and
remain unchanged.

## Example

```cpp
#include "math/zeta_mobius_transform.hpp"

#include <vector>

int main() {
    std::vector<long long> values{0, 1, 2, 3, 4, 5, 6};
    m1une::math::divisor_zeta_transform(values);
    // values[6] is now 1 + 2 + 3 + 6 = 12.

    m1une::math::divisor_mobius_transform(values);
    // values is restored to its original contents.
}
```
