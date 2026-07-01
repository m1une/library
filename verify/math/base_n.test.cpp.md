---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/base_n.hpp
    title: Base-N Numbers
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/math/base_n.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/base_n.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <concepts>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\n// Returns the canonical\
    \ most-significant-first base-n digits of a\n// nonnegative integer. Zero is represented\
    \ by one zero digit.\ntemplate <std::integral Integer>\nrequires(!std::same_as<std::remove_cv_t<Integer>,\
    \ bool>)\nstd::vector<int> to_base_n(Integer value, int base) {\n    assert(2\
    \ <= base);\n    if (base < 2) return {};\n    if constexpr (std::signed_integral<Integer>)\
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
    \ m1une\n\n\n#line 4 \"verify/math/base_n.test.cpp\"\n\n#line 6 \"verify/math/base_n.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 10 \"verify/math/base_n.test.cpp\"\
    \n#include <random>\n#line 12 \"verify/math/base_n.test.cpp\"\n\nvoid fixed_tests()\
    \ {\n    using m1une::math::checked_from_base_n;\n    using m1une::math::from_base_n;\n\
    \    using m1une::math::to_base_n;\n\n    assert(to_base_n(0, 2) == std::vector<int>({0}));\n\
    \    assert(to_base_n(255, 16) == std::vector<int>({15, 15}));\n    assert(to_base_n(1002003,\
    \ 1000) == std::vector<int>({1, 2, 3}));\n    assert(from_base_n<long long>(std::vector<int>({1,\
    \ 2, 3}), 1000) == 1002003);\n    assert(from_base_n<int>(std::vector<int>(),\
    \ 10) == 0);\n    assert(from_base_n<int>(std::vector<int>({0, 0, 7}), 10) ==\
    \ 7);\n\n    assert(!checked_from_base_n<int>(std::vector<int>({1, -1}), 10).has_value());\n\
    \    assert(!checked_from_base_n<int>(std::vector<int>({1, 10}), 10).has_value());\n\
    \    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({2, 5, 6}), 10)\n\
    \                .has_value());\n    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({256}),\
    \ 1000)\n                .has_value());\n    assert(checked_from_base_n<std::uint8_t>(std::vector<int>({2,\
    \ 5, 5}), 10) ==\n           std::optional<std::uint8_t>(255));\n}\n\nvoid randomized_tests()\
    \ {\n    std::mt19937_64 random(987654321);\n    for (int trial = 0; trial < 100000;\
    \ trial++) {\n        std::uint64_t value = random();\n        int base = int(random()\
    \ % 1000000) + 2;\n        std::vector<int> digits = m1une::math::to_base_n(value,\
    \ base);\n        assert(!digits.empty());\n        assert(digits.size() == 1\
    \ || digits.front() != 0);\n        for (int digit : digits) {\n            (void)digit;\n\
    \            assert(0 <= digit && digit < base);\n        }\n        assert(m1une::math::from_base_n<std::uint64_t>(digits,\
    \ base) == value);\n    }\n\n    for (int base = 2; base <= 50; base++) {\n  \
    \      for (int value = 0; value <= 10000; value++) {\n            std::vector<int>\
    \ digits = m1une::math::to_base_n(value, base);\n            assert(m1une::math::from_base_n<int>(digits,\
    \ base) == value);\n        }\n    }\n\n    std::vector<int> maximum_digits =\n\
    \        m1une::math::to_base_n(std::numeric_limits<std::uint64_t>::max(), 2);\n\
    \    assert(m1une::math::from_base_n<std::uint64_t>(maximum_digits, 2) ==\n  \
    \         std::numeric_limits<std::uint64_t>::max());\n    maximum_digits.push_back(0);\n\
    \    assert(!m1une::math::checked_from_base_n<std::uint64_t>(maximum_digits, 2)\n\
    \                .has_value());\n}\n\nint main() {\n    fixed_tests();\n    randomized_tests();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/base_n.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n\
    #include <limits>\n#include <optional>\n#include <random>\n#include <vector>\n\
    \nvoid fixed_tests() {\n    using m1une::math::checked_from_base_n;\n    using\
    \ m1une::math::from_base_n;\n    using m1une::math::to_base_n;\n\n    assert(to_base_n(0,\
    \ 2) == std::vector<int>({0}));\n    assert(to_base_n(255, 16) == std::vector<int>({15,\
    \ 15}));\n    assert(to_base_n(1002003, 1000) == std::vector<int>({1, 2, 3}));\n\
    \    assert(from_base_n<long long>(std::vector<int>({1, 2, 3}), 1000) == 1002003);\n\
    \    assert(from_base_n<int>(std::vector<int>(), 10) == 0);\n    assert(from_base_n<int>(std::vector<int>({0,\
    \ 0, 7}), 10) == 7);\n\n    assert(!checked_from_base_n<int>(std::vector<int>({1,\
    \ -1}), 10).has_value());\n    assert(!checked_from_base_n<int>(std::vector<int>({1,\
    \ 10}), 10).has_value());\n    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({2,\
    \ 5, 6}), 10)\n                .has_value());\n    assert(!checked_from_base_n<std::uint8_t>(std::vector<int>({256}),\
    \ 1000)\n                .has_value());\n    assert(checked_from_base_n<std::uint8_t>(std::vector<int>({2,\
    \ 5, 5}), 10) ==\n           std::optional<std::uint8_t>(255));\n}\n\nvoid randomized_tests()\
    \ {\n    std::mt19937_64 random(987654321);\n    for (int trial = 0; trial < 100000;\
    \ trial++) {\n        std::uint64_t value = random();\n        int base = int(random()\
    \ % 1000000) + 2;\n        std::vector<int> digits = m1une::math::to_base_n(value,\
    \ base);\n        assert(!digits.empty());\n        assert(digits.size() == 1\
    \ || digits.front() != 0);\n        for (int digit : digits) {\n            (void)digit;\n\
    \            assert(0 <= digit && digit < base);\n        }\n        assert(m1une::math::from_base_n<std::uint64_t>(digits,\
    \ base) == value);\n    }\n\n    for (int base = 2; base <= 50; base++) {\n  \
    \      for (int value = 0; value <= 10000; value++) {\n            std::vector<int>\
    \ digits = m1une::math::to_base_n(value, base);\n            assert(m1une::math::from_base_n<int>(digits,\
    \ base) == value);\n        }\n    }\n\n    std::vector<int> maximum_digits =\n\
    \        m1une::math::to_base_n(std::numeric_limits<std::uint64_t>::max(), 2);\n\
    \    assert(m1une::math::from_base_n<std::uint64_t>(maximum_digits, 2) ==\n  \
    \         std::numeric_limits<std::uint64_t>::max());\n    maximum_digits.push_back(0);\n\
    \    assert(!m1une::math::checked_from_base_n<std::uint64_t>(maximum_digits, 2)\n\
    \                .has_value());\n}\n\nint main() {\n    fixed_tests();\n    randomized_tests();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/base_n.hpp
  isVerificationFile: true
  path: verify/math/base_n.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 22:19:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/base_n.test.cpp
layout: document
redirect_from:
- /verify/verify/math/base_n.test.cpp
- /verify/verify/math/base_n.test.cpp.html
title: verify/math/base_n.test.cpp
---
