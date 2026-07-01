---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/base_n.test.cpp
    title: verify/math/base_n.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/base_n.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <limits>\n#include <optional>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\n\
    // Returns the canonical most-significant-first base-n digits of a\n// nonnegative\
    \ integer. Zero is represented by one zero digit.\ntemplate <std::integral Integer>\n\
    requires(!std::same_as<std::remove_cv_t<Integer>, bool>)\nstd::vector<int> to_base_n(Integer\
    \ value, int base) {\n    assert(2 <= base);\n    if (base < 2) return {};\n \
    \   if constexpr (std::signed_integral<Integer>) {\n        assert(0 <= value);\n\
    \        if (value < 0) return {};\n    }\n\n    using Unsigned = std::make_unsigned_t<Integer>;\n\
    \    Unsigned remaining = static_cast<Unsigned>(value);\n    if (remaining ==\
    \ 0) return {0};\n\n    std::vector<int> digits;\n    const unsigned long long\
    \ unsigned_base = static_cast<unsigned int>(base);\n    while (remaining != 0)\
    \ {\n        digits.push_back(int(remaining % unsigned_base));\n        remaining\
    \ = Unsigned(remaining / unsigned_base);\n    }\n    std::reverse(digits.begin(),\
    \ digits.end());\n    return digits;\n}\n\n// Converts most-significant-first\
    \ base-n digits to an integer.\n// Returns nullopt for an invalid digit or when\
    \ the result does not fit.\ntemplate <std::integral Integer, class DigitSequence>\n\
    requires(!std::same_as<std::remove_cv_t<Integer>, bool>)\nstd::optional<Integer>\
    \ checked_from_base_n(const DigitSequence& digits,\n                         \
    \                  int base) {\n    assert(2 <= base);\n    if (base < 2) return\
    \ std::nullopt;\n\n    using Unsigned = std::make_unsigned_t<Integer>;\n    constexpr\
    \ Unsigned integer_limit = [] {\n        if constexpr (std::signed_integral<Integer>)\
    \ {\n            return Unsigned(std::numeric_limits<Integer>::max());\n     \
    \   } else {\n            return std::numeric_limits<Integer>::max();\n      \
    \  }\n    }();\n    const unsigned __int128 limit = integer_limit;\n    const\
    \ unsigned __int128 unsigned_base = static_cast<unsigned int>(base);\n\n    unsigned\
    \ __int128 value = 0;\n    for (const auto& digit_reference : digits) {\n    \
    \    using Digit = std::remove_cvref_t<decltype(digit_reference)>;\n        static_assert(std::integral<Digit>);\n\
    \        static_assert(!std::same_as<Digit, bool>);\n        Digit digit = digit_reference;\n\
    \        if constexpr (std::signed_integral<Digit>) {\n            if (digit <\
    \ 0) return std::nullopt;\n        }\n        using UnsignedDigit = std::make_unsigned_t<Digit>;\n\
    \        UnsignedDigit unsigned_digit = static_cast<UnsignedDigit>(digit);\n \
    \       unsigned __int128 converted_digit = unsigned_digit;\n        if (converted_digit\
    \ >= unsigned_base) {\n            return std::nullopt;\n        }\n\n       \
    \ if (converted_digit > limit ||\n            value > (limit - converted_digit)\
    \ / unsigned_base) {\n            return std::nullopt;\n        }\n        value\
    \ = value * unsigned_base + converted_digit;\n    }\n    return static_cast<Integer>(static_cast<Unsigned>(value));\n\
    }\n\n// Converts most-significant-first base-n digits to an integer.\n// Every\
    \ digit must be valid and the result must fit in Integer.\ntemplate <std::integral\
    \ Integer, class DigitSequence>\nrequires(!std::same_as<std::remove_cv_t<Integer>,\
    \ bool>)\nInteger from_base_n(const DigitSequence& digits, int base) {\n    std::optional<Integer>\
    \ result = checked_from_base_n<Integer>(digits, base);\n    assert(result.has_value());\n\
    \    return result.value_or(Integer(0));\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_BASE_N_HPP\n#define M1UNE_MATH_BASE_N_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include\
    \ <optional>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace math {\n\n// Returns the canonical most-significant-first base-n digits\
    \ of a\n// nonnegative integer. Zero is represented by one zero digit.\ntemplate\
    \ <std::integral Integer>\nrequires(!std::same_as<std::remove_cv_t<Integer>, bool>)\n\
    std::vector<int> to_base_n(Integer value, int base) {\n    assert(2 <= base);\n\
    \    if (base < 2) return {};\n    if constexpr (std::signed_integral<Integer>)\
    \ {\n        assert(0 <= value);\n        if (value < 0) return {};\n    }\n\n\
    \    using Unsigned = std::make_unsigned_t<Integer>;\n    Unsigned remaining =\
    \ static_cast<Unsigned>(value);\n    if (remaining == 0) return {0};\n\n    std::vector<int>\
    \ digits;\n    const unsigned long long unsigned_base = static_cast<unsigned int>(base);\n\
    \    while (remaining != 0) {\n        digits.push_back(int(remaining % unsigned_base));\n\
    \        remaining = Unsigned(remaining / unsigned_base);\n    }\n    std::reverse(digits.begin(),\
    \ digits.end());\n    return digits;\n}\n\n// Converts most-significant-first\
    \ base-n digits to an integer.\n// Returns nullopt for an invalid digit or when\
    \ the result does not fit.\ntemplate <std::integral Integer, class DigitSequence>\n\
    requires(!std::same_as<std::remove_cv_t<Integer>, bool>)\nstd::optional<Integer>\
    \ checked_from_base_n(const DigitSequence& digits,\n                         \
    \                  int base) {\n    assert(2 <= base);\n    if (base < 2) return\
    \ std::nullopt;\n\n    using Unsigned = std::make_unsigned_t<Integer>;\n    constexpr\
    \ Unsigned integer_limit = [] {\n        if constexpr (std::signed_integral<Integer>)\
    \ {\n            return Unsigned(std::numeric_limits<Integer>::max());\n     \
    \   } else {\n            return std::numeric_limits<Integer>::max();\n      \
    \  }\n    }();\n    const unsigned __int128 limit = integer_limit;\n    const\
    \ unsigned __int128 unsigned_base = static_cast<unsigned int>(base);\n\n    unsigned\
    \ __int128 value = 0;\n    for (const auto& digit_reference : digits) {\n    \
    \    using Digit = std::remove_cvref_t<decltype(digit_reference)>;\n        static_assert(std::integral<Digit>);\n\
    \        static_assert(!std::same_as<Digit, bool>);\n        Digit digit = digit_reference;\n\
    \        if constexpr (std::signed_integral<Digit>) {\n            if (digit <\
    \ 0) return std::nullopt;\n        }\n        using UnsignedDigit = std::make_unsigned_t<Digit>;\n\
    \        UnsignedDigit unsigned_digit = static_cast<UnsignedDigit>(digit);\n \
    \       unsigned __int128 converted_digit = unsigned_digit;\n        if (converted_digit\
    \ >= unsigned_base) {\n            return std::nullopt;\n        }\n\n       \
    \ if (converted_digit > limit ||\n            value > (limit - converted_digit)\
    \ / unsigned_base) {\n            return std::nullopt;\n        }\n        value\
    \ = value * unsigned_base + converted_digit;\n    }\n    return static_cast<Integer>(static_cast<Unsigned>(value));\n\
    }\n\n// Converts most-significant-first base-n digits to an integer.\n// Every\
    \ digit must be valid and the result must fit in Integer.\ntemplate <std::integral\
    \ Integer, class DigitSequence>\nrequires(!std::same_as<std::remove_cv_t<Integer>,\
    \ bool>)\nInteger from_base_n(const DigitSequence& digits, int base) {\n    std::optional<Integer>\
    \ result = checked_from_base_n<Integer>(digits, base);\n    assert(result.has_value());\n\
    \    return result.value_or(Integer(0));\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATH_BASE_N_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/base_n.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-01 22:19:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/base_n.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/base_n.hpp
layout: document
title: Base-N Numbers
---

## Overview

This header converts nonnegative integers to and from positional base-$N$
digits. Digits are stored most-significant first, matching the way numerals are
normally written.

The digit representation is independent of text formatting, so bases greater
than 36 are supported. For example, base 1000 simply uses integer digits from
`0` through `999`.

## Functions

```cpp
template <std::integral Integer>
std::vector<int> to_base_n(Integer value, int base);

template <std::integral Integer, class DigitSequence>
std::optional<Integer> checked_from_base_n(
    const DigitSequence& digits,
    int base);

template <std::integral Integer, class DigitSequence>
Integer from_base_n(
    const DigitSequence& digits,
    int base);
```

`Integer` may be any standard integral type except `bool`. `base` must be at
least 2, and `to_base_n` requires a nonnegative value.

`DigitSequence` must be iterable and contain integral values other than
`bool`. Leading zeroes are accepted, and an empty digit sequence represents
zero.

| Function | Description | Complexity |
| --- | --- | --- |
| `to_base_n(value, base)` | Returns the canonical most-significant-first digits. Zero becomes `{0}`. | $O(D)$ time and memory. |
| `checked_from_base_n<Integer>(digits, base)` | Returns the represented value, or `nullopt` for an invalid digit or overflow. | $O(D)$ time and $O(1)$ memory. |
| `from_base_n<Integer>(digits, base)` | Returns the represented value; validity and representability are required. | $O(D)$ time and $O(1)$ memory. |

Here $D$ is the number of digits. A digit is valid exactly when it belongs to
`[0, base)`.

## Example

```cpp
#include "math/base_n.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> digits = m1une::math::to_base_n(255, 16);
    for (int digit : digits) std::cout << digit << " ";
    std::cout << "\n"; // 15 15

    long long value = m1une::math::from_base_n<long long>(digits, 16);
    std::cout << value << "\n"; // 255
}
```
