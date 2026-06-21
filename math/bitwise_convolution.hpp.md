---
data:
  _extendedDependsOn: []
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
    #include <cstddef>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace bitwise_convolution_detail {\n\ninline bool is_power_of_two(std::size_t\
    \ size) noexcept {\n    return size != 0 && (size & (size - 1)) == 0;\n}\n\ninline\
    \ std::size_t common_size(\n    std::size_t first_size,\n    std::size_t second_size\n\
    ) {\n    std::size_t required = first_size > second_size\n        ? first_size\n\
    \        : second_size;\n    std::size_t size = 1;\n    while (size < required)\
    \ size <<= 1;\n    return size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n\
    \    std::vector<T> first,\n    const std::vector<T>& second\n) {\n    assert(first.size()\
    \ == second.size());\n    for (std::size_t index = 0; index < first.size(); ++index)\
    \ {\n        first[index] *= second[index];\n    }\n    return first;\n}\n\n}\
    \  // namespace bitwise_convolution_detail\n\ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>&\
    \ values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ += values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void walsh_hadamard_transform(\n    std::vector<T>& values,\n    bool inverse\
    \ = false\n) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
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
    \nnamespace m1une {\nnamespace math {\n\nnamespace bitwise_convolution_detail\
    \ {\n\ninline bool is_power_of_two(std::size_t size) noexcept {\n    return size\
    \ != 0 && (size & (size - 1)) == 0;\n}\n\ninline std::size_t common_size(\n  \
    \  std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n   \
    \ for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void walsh_hadamard_transform(\n    std::vector<T>& values,\n    bool inverse\
    \ = false\n) {\n    assert(bitwise_convolution_detail::is_power_of_two(values.size()));\n\
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
  dependsOn: []
  isVerificationFile: false
  path: math/bitwise_convolution.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-21 17:44:01+09:00'
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

The header also exposes the underlying subset, superset, and
Walsh-Hadamard transforms.

```cpp
#include "math/bitwise_convolution.hpp"
```

All names are in `m1une::math`.

## Convolutions

For input arrays `a` and `b`, the functions compute:

$$
c_k = \sum_{i \mathbin{\mathrm{op}} j = k} a_i b_j.
$$

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
