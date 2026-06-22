---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bitwise_convolution.test.cpp
    title: verify/math/bitwise_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/bitwise_convolution.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <utility>\n#include <vector>\n\n#line 1 \"math/zeta_mobius_transform.hpp\"\
    \n\n\n\n#line 7 \"math/zeta_mobius_transform.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline bool is_power_of_two(std::size_t\
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
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/bitwise_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace bitwise_convolution_detail {\n\ninline std::size_t common_size(\n\
    \    std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid walsh_hadamard_transform(\n    std::vector<T>& values,\n\
    \    bool inverse = false\n) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t length = 1; length < values.size(); length <<= 1) {\n  \
    \      for (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += length << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < length; ++offset) {\n                T first = values[block +\
    \ offset];\n                T second = values[block + offset + length];\n    \
    \            values[block + offset] = first + second;\n                values[block\
    \ + offset + length] = first - second;\n            }\n        }\n    }\n    if\
    \ (inverse) {\n        T size = T(static_cast<long long>(values.size()));\n  \
    \      for (T& value : values) value /= size;\n    }\n}\n\ntemplate <typename\
    \ T>\nstd::vector<T> bitwise_or_convolution(\n    std::vector<T> first,\n    std::vector<T>\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ size = bitwise_convolution_detail::common_size(\n        first.size(),\n   \
    \     second.size()\n    );\n    first.resize(size);\n    second.resize(size);\n\
    \    subset_zeta_transform(first);\n    subset_zeta_transform(second);\n    first\
    \ = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    subset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_and_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    superset_zeta_transform(first);\n    superset_zeta_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    superset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_xor_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    walsh_hadamard_transform(first);\n    walsh_hadamard_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    walsh_hadamard_transform(first, true);\n    return\
    \ first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_BITWISE_CONVOLUTION_HPP\n#define M1UNE_MATH_BITWISE_CONVOLUTION_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#include \"zeta_mobius_transform.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nnamespace bitwise_convolution_detail {\n\ninline std::size_t common_size(\n\
    \    std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid walsh_hadamard_transform(\n    std::vector<T>& values,\n\
    \    bool inverse = false\n) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t length = 1; length < values.size(); length <<= 1) {\n  \
    \      for (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += length << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < length; ++offset) {\n                T first = values[block +\
    \ offset];\n                T second = values[block + offset + length];\n    \
    \            values[block + offset] = first + second;\n                values[block\
    \ + offset + length] = first - second;\n            }\n        }\n    }\n    if\
    \ (inverse) {\n        T size = T(static_cast<long long>(values.size()));\n  \
    \      for (T& value : values) value /= size;\n    }\n}\n\ntemplate <typename\
    \ T>\nstd::vector<T> bitwise_or_convolution(\n    std::vector<T> first,\n    std::vector<T>\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ size = bitwise_convolution_detail::common_size(\n        first.size(),\n   \
    \     second.size()\n    );\n    first.resize(size);\n    second.resize(size);\n\
    \    subset_zeta_transform(first);\n    subset_zeta_transform(second);\n    first\
    \ = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    subset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_and_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    superset_zeta_transform(first);\n    superset_zeta_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    superset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_xor_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    walsh_hadamard_transform(first);\n    walsh_hadamard_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    walsh_hadamard_transform(first, true);\n    return\
    \ first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_BITWISE_CONVOLUTION_HPP\n"
  dependsOn:
  - math/zeta_mobius_transform.hpp
  isVerificationFile: false
  path: math/bitwise_convolution.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-22 22:56:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/bitwise_convolution.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/bitwise_convolution.hpp
layout: document
title: Bitwise Convolution
---

## Overview

Bitwise convolutions indexed by masks:

- OR convolution groups pairs by `i | j`;
- AND convolution groups pairs by `i & j`;
- XOR convolution groups pairs by `i ^ j`.

The header also exposes the underlying subset, superset, and Walsh-Hadamard
transforms. The subset and superset transforms are defined in
`zeta_mobius_transform.hpp`, which this header includes.

```cpp
#include "math/bitwise_convolution.hpp"
```

All names are in `m1une::math`.

## Convolutions

For input arrays `a` and `b`, the functions compute:

$$
c_k = \sum_{i \mathbin{\mathrm{op}} j = k} a_i b_j.
$$

```cpp
template <typename T>
std::vector<T> bitwise_or_convolution(
    std::vector<T> first,
    std::vector<T> second
);

template <typename T>
std::vector<T> bitwise_and_convolution(
    std::vector<T> first,
    std::vector<T> second
);

template <typename T>
std::vector<T> bitwise_xor_convolution(
    std::vector<T> first,
    std::vector<T> second
);
```

The input vectors are passed by value, so they may be moved into the functions.
The originals passed by the caller are otherwise unchanged. The return type is
`std::vector<T>`.

| Function | Operation | Complexity |
| --- | --- | --- |
| `bitwise_or_convolution(a, b)` | `op` is bitwise OR. | $O(N \log N)$ |
| `bitwise_and_convolution(a, b)` | `op` is bitwise AND. | $O(N \log N)$ |
| `bitwise_xor_convolution(a, b)` | `op` is bitwise XOR. | $O(N \log N)$ |

If either input is empty, the result is empty. Otherwise both arrays are
zero-padded to the smallest power of two at least
`max(a.size(), b.size())`. The returned vector has that length.
Each function uses $O(N)$ additional memory.

The element type must support default construction, addition, subtraction, and
multiplication. XOR convolution additionally requires division by the transform
size and construction from that size. Integers work because the inverse
Walsh-Hadamard transform is exactly divisible; modular types require the
power-of-two transform size to be invertible.

## Transforms

All transforms operate in place and require a nonempty power-of-two length.

```cpp
template <typename T>
void walsh_hadamard_transform(
    std::vector<T>& values,
    bool inverse = false
);
```

The subset and superset transform signatures and their requirements on `T` are
documented in `zeta_mobius_transform.hpp`. The Walsh-Hadamard transform modifies
`values` directly and returns `void`.

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_zeta_transform(values)` | Replaces each mask with the sum over its submasks. | $O(N \log N)$ |
| `subset_mobius_transform(values)` | Inverts the subset zeta transform. | $O(N \log N)$ |
| `superset_zeta_transform(values)` | Replaces each mask with the sum over its supermasks. | $O(N \log N)$ |
| `superset_mobius_transform(values)` | Inverts the superset zeta transform. | $O(N \log N)$ |
| `walsh_hadamard_transform(values, inverse)` | Applies the XOR transform or its inverse. | $O(N \log N)$ |

For a mask $S$, subset zeta computes
$F(S) = \sum_{T \subseteq S} f(T)$, while superset zeta computes
$F(S) = \sum_{T \supseteq S} f(T)$. Their Möbius transforms recover $f$.

The Walsh-Hadamard transform computes
$F(S) = \sum_T (-1)^{\operatorname{popcount}(S \mathbin{\&} T)} f(T)$.
Passing `true` as the second argument applies the same butterflies and divides
every element by $N$, producing the inverse transform.

## Example

```cpp
#include "math/bitwise_convolution.hpp"
#include "math/modint.hpp"

#include <vector>

int main() {
    using mint = m1une::math::modint998244353;

    std::vector<mint> a{1, 2, 3, 4};
    std::vector<mint> b{5, 6, 7, 8};
    std::vector<mint> result =
        m1une::math::bitwise_xor_convolution(a, b);
}
```
