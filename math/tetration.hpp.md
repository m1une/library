---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/tetration.test.cpp
    title: verify/math/tetration.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/tetration.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstdint>\n#include <type_traits>\n#include <vector>\n\n\
    #line 1 \"math/prime_factorization.hpp\"\n\n\n\n#include <algorithm>\n#line 7\
    \ \"math/prime_factorization.hpp\"\n#include <numeric>\n#include <utility>\n#line\
    \ 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t a, uint64_t b,\
    \ uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(a)\
    \ * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t exponent,\
    \ uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0) {\n    \
    \    if (exponent & 1) result = multiply_mod(result, base, mod);\n        base\
    \ = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n    return\
    \ result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t state\
    \ = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime : {2ULL,\
    \ 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n\
    \        if (value % prime == 0) return value == prime;\n    }\n\n    uint64_t\
    \ odd_part = value - 1;\n    int power_of_two = 0;\n    while ((odd_part & 1)\
    \ == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n    }\n\n    for\
    \ (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})\
    \ {\n        if (base % value == 0) continue;\n        uint64_t x = internal::power_mod(base\
    \ % value, odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\
    \n        bool composite = true;\n        for (int i = 1; i < power_of_two; i++)\
    \ {\n            x = internal::multiply_mod(x, x, value);\n            if (x ==\
    \ value - 1) {\n                composite = false;\n                break;\n \
    \           }\n        }\n        if (composite) return false;\n    }\n    return\
    \ true;\n}\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value)\
    \ {\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 11 \"math/tetration.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ tetration_detail {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t to_uint64(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ {\n        assert(value >= 0);\n    }\n    return static_cast<uint64_t>(value);\n\
    }\n\ninline uint64_t multiply_mod(uint64_t first, uint64_t second, uint64_t mod)\
    \ {\n    return static_cast<uint64_t>(\n        static_cast<__uint128_t>(first)\
    \ * second % mod\n    );\n}\n\ninline uint64_t pow_mod(uint64_t base, __uint128_t\
    \ exponent, uint64_t mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n\
    \    base %= mod;\n    uint64_t result = 1 % mod;\n    while (exponent > 0) {\n\
    \        if ((exponent & 1) != 0) result = multiply_mod(result, base, mod);\n\
    \        base = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n\
    \    return result;\n}\n\ninline uint64_t pow_bounded(uint64_t base, uint64_t\
    \ exponent, uint64_t limit) {\n    if (limit == 0) return 0;\n    __uint128_t\
    \ result = 1;\n    for (uint64_t i = 0; i < exponent; i++) {\n        result *=\
    \ base;\n        if (result >= limit) return limit;\n    }\n    return static_cast<uint64_t>(result);\n\
    }\n\ninline uint64_t exponent_threshold(uint64_t base, uint64_t limit) {\n   \
    \ assert(base >= 2);\n    if (limit <= 1) return 0;\n\n    uint64_t exponent =\
    \ 0;\n    uint64_t value = 1;\n    while (value < limit) {\n        exponent++;\n\
    \        if (value > limit / base) return exponent;\n        value *= base;\n\
    \    }\n    return exponent;\n}\n\ninline uint64_t tetration_bounded_unsigned(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return limit < 1 ? limit : 1;\n    if (height == 1) return\
    \ base < limit ? base : limit;\n\n    if (base == 0) {\n        const uint64_t\
    \ value = (height & 1) == 0 ? 1 : 0;\n        return value < limit ? value : limit;\n\
    \    }\n    if (base == 1) return limit < 1 ? limit : 1;\n\n    const uint64_t\
    \ threshold = exponent_threshold(base, limit);\n    const uint64_t exponent =\
    \ tetration_bounded_unsigned(base, height - 1, threshold);\n    if (exponent >=\
    \ threshold) return limit;\n    return pow_bounded(base, exponent, limit);\n}\n\
    \ninline uint64_t tetration_mod_unsigned(uint64_t base, uint64_t height, uint64_t\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    if (height ==\
    \ 0) return 1 % mod;\n    if (height == 1) return base % mod;\n    if (base ==\
    \ 0) return (height & 1) == 0 ? 1 % mod : 0;\n    if (base == 1) return 1 % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = tetration_mod_unsigned(base,\
    \ height - 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (tetration_bounded_unsigned(base,\
    \ height - 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(base,\
    \ exponent, mod);\n}\n\ninline uint64_t power_tower_bounded_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t limit\n) {\n   \
    \ if (limit == 0) return 0;\n    if (index == int(bases.size())) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t base = bases[index];\n    if (index +\
    \ 1 == int(bases.size())) return base < limit ? base : limit;\n\n    if (base\
    \ == 0) {\n        const uint64_t exponent = power_tower_bounded_unsigned(bases,\
    \ index + 1, 1);\n        const uint64_t value = exponent == 0 ? 1 : 0;\n    \
    \    return value < limit ? value : limit;\n    }\n    if (base == 1) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t threshold = exponent_threshold(base,\
    \ limit);\n    const uint64_t exponent = power_tower_bounded_unsigned(bases, index\
    \ + 1, threshold);\n    if (exponent >= threshold) return limit;\n    return pow_bounded(base,\
    \ exponent, limit);\n}\n\ninline uint64_t power_tower_mod_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    if (index == int(bases.size())) return\
    \ 1 % mod;\n    if (index + 1 == int(bases.size())) return bases[index] % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = power_tower_mod_unsigned(bases,\
    \ index + 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (power_tower_bounded_unsigned(bases,\
    \ index + 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(bases[index],\
    \ exponent, mod);\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstd::vector<uint64_t> normalize_bases(const std::vector<T>& bases) {\n\
    \    std::vector<uint64_t> result;\n    result.reserve(bases.size());\n    for\
    \ (T base : bases) result.push_back(to_uint64(base));\n    return result;\n}\n\
    \n}  // namespace tetration_detail\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_mod(T base, uint64_t height, uint64_t mod) {\n  \
    \  assert(mod >= 1);\n    return tetration_detail::tetration_mod_unsigned(\n \
    \       tetration_detail::to_uint64(base),\n        height,\n        mod\n   \
    \ );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_bounded(T base, uint64_t height, uint64_t limit)\
    \ {\n    return tetration_detail::tetration_bounded_unsigned(\n        tetration_detail::to_uint64(base),\n\
    \        height,\n        limit\n    );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t power_tower_mod(const std::vector<T>& bases, uint64_t mod)\
    \ {\n    assert(mod >= 1);\n    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_mod_unsigned(normalized, 0, mod);\n\
    }\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    uint64_t power_tower_bounded(const std::vector<T>& bases, uint64_t limit) {\n\
    \    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_bounded_unsigned(normalized, 0, limit);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_TETRATION_HPP\n#define M1UNE_MATH_TETRATION_HPP 1\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <type_traits>\n\
    #include <vector>\n\n#include \"prime_factorization.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace tetration_detail {\n\ntemplate <std::integral T>\n\
    requires(!std::same_as<std::remove_cv_t<T>, bool>)\nuint64_t to_uint64(T value)\
    \ {\n    if constexpr (std::signed_integral<T>) {\n        assert(value >= 0);\n\
    \    }\n    return static_cast<uint64_t>(value);\n}\n\ninline uint64_t multiply_mod(uint64_t\
    \ first, uint64_t second, uint64_t mod) {\n    return static_cast<uint64_t>(\n\
    \        static_cast<__uint128_t>(first) * second % mod\n    );\n}\n\ninline uint64_t\
    \ pow_mod(uint64_t base, __uint128_t exponent, uint64_t mod) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    base %= mod;\n    uint64_t result =\
    \ 1 % mod;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result\
    \ = multiply_mod(result, base, mod);\n        base = multiply_mod(base, base,\
    \ mod);\n        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t\
    \ pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {\n    if (limit\
    \ == 0) return 0;\n    __uint128_t result = 1;\n    for (uint64_t i = 0; i < exponent;\
    \ i++) {\n        result *= base;\n        if (result >= limit) return limit;\n\
    \    }\n    return static_cast<uint64_t>(result);\n}\n\ninline uint64_t exponent_threshold(uint64_t\
    \ base, uint64_t limit) {\n    assert(base >= 2);\n    if (limit <= 1) return\
    \ 0;\n\n    uint64_t exponent = 0;\n    uint64_t value = 1;\n    while (value\
    \ < limit) {\n        exponent++;\n        if (value > limit / base) return exponent;\n\
    \        value *= base;\n    }\n    return exponent;\n}\n\ninline uint64_t tetration_bounded_unsigned(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return limit < 1 ? limit : 1;\n    if (height == 1) return\
    \ base < limit ? base : limit;\n\n    if (base == 0) {\n        const uint64_t\
    \ value = (height & 1) == 0 ? 1 : 0;\n        return value < limit ? value : limit;\n\
    \    }\n    if (base == 1) return limit < 1 ? limit : 1;\n\n    const uint64_t\
    \ threshold = exponent_threshold(base, limit);\n    const uint64_t exponent =\
    \ tetration_bounded_unsigned(base, height - 1, threshold);\n    if (exponent >=\
    \ threshold) return limit;\n    return pow_bounded(base, exponent, limit);\n}\n\
    \ninline uint64_t tetration_mod_unsigned(uint64_t base, uint64_t height, uint64_t\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    if (height ==\
    \ 0) return 1 % mod;\n    if (height == 1) return base % mod;\n    if (base ==\
    \ 0) return (height & 1) == 0 ? 1 % mod : 0;\n    if (base == 1) return 1 % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = tetration_mod_unsigned(base,\
    \ height - 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (tetration_bounded_unsigned(base,\
    \ height - 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(base,\
    \ exponent, mod);\n}\n\ninline uint64_t power_tower_bounded_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t limit\n) {\n   \
    \ if (limit == 0) return 0;\n    if (index == int(bases.size())) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t base = bases[index];\n    if (index +\
    \ 1 == int(bases.size())) return base < limit ? base : limit;\n\n    if (base\
    \ == 0) {\n        const uint64_t exponent = power_tower_bounded_unsigned(bases,\
    \ index + 1, 1);\n        const uint64_t value = exponent == 0 ? 1 : 0;\n    \
    \    return value < limit ? value : limit;\n    }\n    if (base == 1) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t threshold = exponent_threshold(base,\
    \ limit);\n    const uint64_t exponent = power_tower_bounded_unsigned(bases, index\
    \ + 1, threshold);\n    if (exponent >= threshold) return limit;\n    return pow_bounded(base,\
    \ exponent, limit);\n}\n\ninline uint64_t power_tower_mod_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    if (index == int(bases.size())) return\
    \ 1 % mod;\n    if (index + 1 == int(bases.size())) return bases[index] % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = power_tower_mod_unsigned(bases,\
    \ index + 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (power_tower_bounded_unsigned(bases,\
    \ index + 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(bases[index],\
    \ exponent, mod);\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstd::vector<uint64_t> normalize_bases(const std::vector<T>& bases) {\n\
    \    std::vector<uint64_t> result;\n    result.reserve(bases.size());\n    for\
    \ (T base : bases) result.push_back(to_uint64(base));\n    return result;\n}\n\
    \n}  // namespace tetration_detail\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_mod(T base, uint64_t height, uint64_t mod) {\n  \
    \  assert(mod >= 1);\n    return tetration_detail::tetration_mod_unsigned(\n \
    \       tetration_detail::to_uint64(base),\n        height,\n        mod\n   \
    \ );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_bounded(T base, uint64_t height, uint64_t limit)\
    \ {\n    return tetration_detail::tetration_bounded_unsigned(\n        tetration_detail::to_uint64(base),\n\
    \        height,\n        limit\n    );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t power_tower_mod(const std::vector<T>& bases, uint64_t mod)\
    \ {\n    assert(mod >= 1);\n    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_mod_unsigned(normalized, 0, mod);\n\
    }\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    uint64_t power_tower_bounded(const std::vector<T>& bases, uint64_t limit) {\n\
    \    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_bounded_unsigned(normalized, 0, limit);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_TETRATION_HPP\n"
  dependsOn:
  - math/prime_factorization.hpp
  isVerificationFile: false
  path: math/tetration.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-24 14:35:02+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/tetration.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/tetration.hpp
layout: document
title: Tetration
---

## Overview

This header computes power towers quickly under a modulus.

For a repeated base, tetration means:

```text
tetration(base, 0) = 1
tetration(base, 1) = base
tetration(base, 2) = base^base
tetration(base, 3) = base^(base^base)
```

The implementation works for non-prime and non-coprime moduli. It recursively
uses Euler's totient function and lifts the exponent when the true exponent is
large enough. Totients are computed with the existing 64-bit Pollard-Rho
factorization library.

The ordinary modular exponent convention `0^0 = 1` is used. Therefore, for
example, `power_tower_mod({2, 0}, mod)` is `1 mod mod`.

## Functions

All functions are in namespace `m1une::math`. Bases must be non-negative
integers. Signed input types are accepted, but negative values are invalid and
asserted against in debug builds.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `uint64_t tetration_mod(base, height, mod)` | Returns `base^^height mod mod`. | Totient-chain factorization and logarithmic modular powers |
| `uint64_t tetration_bounded(base, height, limit)` | Returns `min(base^^height, limit)`. | `O(log limit)` effective recursion for `base >= 2` |
| `uint64_t power_tower_mod(vector<T> bases, mod)` | Returns `bases[0]^(bases[1]^(...)) mod mod`. Empty tower is `1`. | Totient-chain factorization and logarithmic modular powers |
| `uint64_t power_tower_bounded(vector<T> bases, limit)` | Returns `min(tower, limit)`. Empty tower is `1`. | Bounded by the tower length and `log limit` |

`mod` must be positive. If `mod == 1`, modular functions return `0`.

The bounded functions are useful for comparisons without big integers. For
example, `tetration_bounded(3, 4, 1000000)` returns `1000000`, meaning the true
value is at least that limit.

## Example

```cpp
#include "math/tetration.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << m1une::math::tetration_mod(2ULL, 4, 1000) << '\n';  // 536
    std::cout << m1une::math::tetration_mod(3ULL, 3, 100) << '\n';   // 87

    std::vector<unsigned long long> bases;
    bases.push_back(2);
    bases.push_back(3);
    bases.push_back(4);
    std::cout << m1une::math::power_tower_mod(bases, 1000000007) << '\n';

    if (m1une::math::tetration_bounded(2ULL, 5, 1000000) == 1000000) {
        std::cout << "large\n";
    }
}
```

## Notes

- `height = 0` is defined as an empty tower and equals `1`.
- An empty vector passed to `power_tower_mod` or `power_tower_bounded` also
  represents an empty tower and equals `1`.
- The return type is always `uint64_t`.
- The modulus may be composite; coprimality between the base and modulus is not
  required.
