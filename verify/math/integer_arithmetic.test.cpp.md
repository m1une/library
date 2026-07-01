---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/integer_arithmetic.hpp
    title: Integer Square Root and Power
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
  bundledCode: "#line 1 \"verify/math/integer_arithmetic.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/integer_arithmetic.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n\nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail\
    \ {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr std::optional<T> checked_multiply(T first, T second) {\n \
    \   constexpr T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum\
    \ = std::numeric_limits<T>::max();\n\n    if constexpr (std::unsigned_integral<T>)\
    \ {\n        if (second != 0 && maximum / second < first) return std::nullopt;\n\
    \    } else {\n        if (0 < first) {\n            if (0 < second) {\n     \
    \           if (maximum / second < first) return std::nullopt;\n            }\
    \ else if (second < minimum / first) {\n                return std::nullopt;\n\
    \            }\n        } else if (first < 0) {\n            if (0 < second) {\n\
    \                if (first < minimum / second) return std::nullopt;\n        \
    \    } else if (second < maximum / first) {\n                return std::nullopt;\n\
    \            }\n        }\n    }\n    return T(first * second);\n}\n\n}  // namespace\
    \ integer_arithmetic_detail\n\n// Returns floor(sqrt(value)) exactly, without\
    \ floating-point arithmetic.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ assert(0 <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n \
    \   T high = value / 2 + 1;\n    while (low < high) {\n        T middle = low\
    \ + (high - low + 1) / 2;\n        if (middle <= value / middle) {\n         \
    \   low = middle;\n        } else {\n            high = middle - 1;\n        }\n\
    \    }\n    return low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T floor_sqrt(T value) {\n    return isqrt(value);\n}\n\n//\
    \ Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nconstexpr\
    \ T ceil_sqrt(T value) {\n    T result = isqrt(value);\n    if (result == 0) return\
    \ 0;\n    if (result != 0 && value / result == result && value % result == 0)\
    \ {\n        return result;\n    }\n    return result + 1;\n}\n\n// Returns base^exponent,\
    \ or nullopt when the result does not fit in T.\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr std::optional<T> checked_ipow(T base, Exponent exponent)\
    \ {\n    T result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ {\n            auto product =\n                integer_arithmetic_detail::checked_multiply(result,\
    \ base);\n            if (!product.has_value()) return std::nullopt;\n       \
    \     result = *product;\n        }\n        exponent >>= 1;\n        if (exponent\
    \ != 0) {\n            auto square =\n                integer_arithmetic_detail::checked_multiply(base,\
    \ base);\n            if (!square.has_value()) return std::nullopt;\n        \
    \    base = *square;\n        }\n    }\n    return result;\n}\n\ntemplate <std::integral\
    \ T, std::unsigned_integral Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Exponent>, bool>\n)\nconstexpr\
    \ std::optional<T> checked_integer_pow(T base, Exponent exponent) {\n    return\
    \ checked_ipow(base, exponent);\n}\n\n// Returns base^exponent. The result must\
    \ be representable by T.\ntemplate <std::integral T, std::unsigned_integral Exponent>\n\
    requires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T ipow(T base, Exponent exponent) {\n    std::optional<T>\
    \ result = checked_ipow(base, exponent);\n    assert(result.has_value());\n  \
    \  return result.value_or(T());\n}\n\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T integer_pow(T base, Exponent exponent) {\n    return ipow(base,\
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/math/integer_arithmetic.test.cpp\"\n\n#include <algorithm>\n#line 7 \"\
    verify/math/integer_arithmetic.test.cpp\"\n#include <cstdint>\n#include <iostream>\n\
    #line 11 \"verify/math/integer_arithmetic.test.cpp\"\n\nnamespace {\n\ntemplate\
    \ <class T>\nvoid test_square_roots() {\n    using U = std::make_unsigned_t<T>;\n\
    \    U limit = std::min<U>(std::numeric_limits<T>::max(), U(100000));\n    for\
    \ (U value = 0;; ++value) {\n        T input = static_cast<T>(value);\n      \
    \  [[maybe_unused]] T floor = m1une::math::isqrt(input);\n        [[maybe_unused]]\
    \ T ceiling = m1une::math::ceil_sqrt(input);\n        assert(floor <= input /\
    \ (floor == 0 ? 1 : floor));\n        assert(floor == 0 || floor + 1 > input /\
    \ (floor + 1));\n        assert(ceiling == floor || ceiling == floor + 1);\n \
    \       assert(\n            ceiling == floor\n            ? floor * floor ==\
    \ input\n            : floor * floor < input\n        );\n        if (value ==\
    \ limit) break;\n    }\n}\n\nvoid test_boundaries() {\n    constexpr std::uint64_t\
    \ maximum =\n        std::numeric_limits<std::uint64_t>::max();\n    constexpr\
    \ std::uint64_t root = 4294967295ULL;\n    static_assert(m1une::math::isqrt(maximum)\
    \ == root);\n    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);\n\
    \    static_assert(m1une::math::isqrt(root * root) == root);\n\n    constexpr\
    \ long long signed_maximum =\n        std::numeric_limits<long long>::max();\n\
    \    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);\n    static_assert(m1une::math::ceil_sqrt(signed_maximum)\
    \ == 3037000500LL);\n}\n\nvoid test_powers() {\n    using m1une::math::checked_ipow;\n\
    \    using m1une::math::ipow;\n\n    static_assert(ipow(0LL, 0U) == 1);\n    static_assert(ipow(2LL,\
    \ 10U) == 1024);\n    static_assert(ipow(-3LL, 3U) == -27);\n    static_assert(ipow(-3LL,\
    \ 4U) == 81);\n    static_assert(\n        ipow(-2LL, 63U) == std::numeric_limits<long\
    \ long>::min()\n    );\n    static_assert(!checked_ipow(2LL, 63U).has_value());\n\
    \    static_assert(!checked_ipow(-2LL, 64U).has_value());\n    static_assert(!checked_ipow(10ULL,\
    \ 20U).has_value());\n    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));\n\
    \    static_assert(\n        checked_ipow(std::numeric_limits<long long>::min(),\
    \ 1U)\n        == std::optional(std::numeric_limits<long long>::min())\n    );\n\
    \    static_assert(\n        !checked_ipow(std::numeric_limits<long long>::min(),\
    \ 2U).has_value()\n    );\n\n    for (long long base = -20; base <= 20; ++base)\
    \ {\n        [[maybe_unused]] long long expected = 1;\n        for (unsigned exponent\
    \ = 0; exponent <= 8; ++exponent) {\n            assert(ipow(base, exponent) ==\
    \ expected);\n            expected *= base;\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_square_roots<signed char>();\n    test_square_roots<unsigned\
    \ char>();\n    test_square_roots<short>();\n    test_square_roots<unsigned short>();\n\
    \    test_square_roots<int>();\n    test_square_roots<unsigned int>();\n    test_square_roots<long\
    \ long>();\n    test_square_roots<unsigned long long>();\n    test_boundaries();\n\
    \    test_powers();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/integer_arithmetic.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n#include <optional>\n\
    \nnamespace {\n\ntemplate <class T>\nvoid test_square_roots() {\n    using U =\
    \ std::make_unsigned_t<T>;\n    U limit = std::min<U>(std::numeric_limits<T>::max(),\
    \ U(100000));\n    for (U value = 0;; ++value) {\n        T input = static_cast<T>(value);\n\
    \        [[maybe_unused]] T floor = m1une::math::isqrt(input);\n        [[maybe_unused]]\
    \ T ceiling = m1une::math::ceil_sqrt(input);\n        assert(floor <= input /\
    \ (floor == 0 ? 1 : floor));\n        assert(floor == 0 || floor + 1 > input /\
    \ (floor + 1));\n        assert(ceiling == floor || ceiling == floor + 1);\n \
    \       assert(\n            ceiling == floor\n            ? floor * floor ==\
    \ input\n            : floor * floor < input\n        );\n        if (value ==\
    \ limit) break;\n    }\n}\n\nvoid test_boundaries() {\n    constexpr std::uint64_t\
    \ maximum =\n        std::numeric_limits<std::uint64_t>::max();\n    constexpr\
    \ std::uint64_t root = 4294967295ULL;\n    static_assert(m1une::math::isqrt(maximum)\
    \ == root);\n    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);\n\
    \    static_assert(m1une::math::isqrt(root * root) == root);\n\n    constexpr\
    \ long long signed_maximum =\n        std::numeric_limits<long long>::max();\n\
    \    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);\n    static_assert(m1une::math::ceil_sqrt(signed_maximum)\
    \ == 3037000500LL);\n}\n\nvoid test_powers() {\n    using m1une::math::checked_ipow;\n\
    \    using m1une::math::ipow;\n\n    static_assert(ipow(0LL, 0U) == 1);\n    static_assert(ipow(2LL,\
    \ 10U) == 1024);\n    static_assert(ipow(-3LL, 3U) == -27);\n    static_assert(ipow(-3LL,\
    \ 4U) == 81);\n    static_assert(\n        ipow(-2LL, 63U) == std::numeric_limits<long\
    \ long>::min()\n    );\n    static_assert(!checked_ipow(2LL, 63U).has_value());\n\
    \    static_assert(!checked_ipow(-2LL, 64U).has_value());\n    static_assert(!checked_ipow(10ULL,\
    \ 20U).has_value());\n    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));\n\
    \    static_assert(\n        checked_ipow(std::numeric_limits<long long>::min(),\
    \ 1U)\n        == std::optional(std::numeric_limits<long long>::min())\n    );\n\
    \    static_assert(\n        !checked_ipow(std::numeric_limits<long long>::min(),\
    \ 2U).has_value()\n    );\n\n    for (long long base = -20; base <= 20; ++base)\
    \ {\n        [[maybe_unused]] long long expected = 1;\n        for (unsigned exponent\
    \ = 0; exponent <= 8; ++exponent) {\n            assert(ipow(base, exponent) ==\
    \ expected);\n            expected *= base;\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_square_roots<signed char>();\n    test_square_roots<unsigned\
    \ char>();\n    test_square_roots<short>();\n    test_square_roots<unsigned short>();\n\
    \    test_square_roots<int>();\n    test_square_roots<unsigned int>();\n    test_square_roots<long\
    \ long>();\n    test_square_roots<unsigned long long>();\n    test_boundaries();\n\
    \    test_powers();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - math/integer_arithmetic.hpp
  isVerificationFile: true
  path: verify/math/integer_arithmetic.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:33:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/integer_arithmetic.test.cpp
layout: document
redirect_from:
- /verify/verify/math/integer_arithmetic.test.cpp
- /verify/verify/math/integer_arithmetic.test.cpp.html
title: verify/math/integer_arithmetic.test.cpp
---
