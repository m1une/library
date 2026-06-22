---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
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
  bundledCode: "#line 1 \"verify/math/rational.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/rational.hpp\"\n\n\n\n#include <cassert>\n#include <compare>\n\
    #include <concepts>\n#include <iostream>\n#include <limits>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral T = long\
    \ long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    using Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\
    \n    T _numerator;\n    T _denominator;\n\n    static constexpr UnsignedWide\
    \ magnitude(Wide value) {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
    \ + 1)) + 1;\n        }\n        return static_cast<UnsignedWide>(value);\n  \
    \  }\n\n    static constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide\
    \ second) {\n        while (second != 0) {\n            UnsignedWide remainder\
    \ = first % second;\n            first = second;\n            second = remainder;\n\
    \        }\n        return first;\n    }\n\n    static constexpr T narrow(Wide\
    \ value) {\n        assert(Wide(std::numeric_limits<T>::min()) <= value);\n  \
    \      assert(value <= Wide(std::numeric_limits<T>::max()));\n        return static_cast<T>(value);\n\
    \    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        UnsignedWide divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n   public:\n    constexpr Rational() : _numerator(0), _denominator(1)\
    \ {}\n\n    constexpr Rational(T integer) : _numerator(integer), _denominator(1)\
    \ {}\n\n    constexpr Rational(T numerator, T denominator) {\n        assign_normalized(Wide(numerator),\
    \ Wide(denominator));\n    }\n\n    constexpr T numerator() const {\n        return\
    \ _numerator;\n    }\n\n    constexpr T denominator() const {\n        return\
    \ _denominator;\n    }\n\n    constexpr bool is_integer() const {\n        return\
    \ _denominator == 1;\n    }\n\n    constexpr int sign() const {\n        return\
    \ (_numerator > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal()\
    \ const {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    explicit constexpr operator long double()\
    \ const {\n        return to_long_double();\n    }\n\n    constexpr T trunc()\
    \ const {\n        return _numerator / _denominator;\n    }\n\n    constexpr T\
    \ floor() const {\n        T quotient = _numerator / _denominator;\n        if\
    \ (_numerator < 0 && _numerator % _denominator != 0) --quotient;\n        return\
    \ quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient = _numerator\
    \ / _denominator;\n        if (0 < _numerator && _numerator % _denominator !=\
    \ 0) ++quotient;\n        return quotient;\n    }\n\n    constexpr Rational operator+()\
    \ const {\n        return *this;\n    }\n\n    constexpr Rational operator-()\
    \ const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  UnsignedWide common =\n            gcd(static_cast<UnsignedWide>(_denominator),\
    \ static_cast<UnsignedWide>(other._denominator));\n        Wide left_scale = Wide(other._denominator)\
    \ / static_cast<Wide>(common);\n        Wide right_scale = Wide(_denominator)\
    \ / static_cast<Wide>(common);\n        assign_normalized(Wide(_numerator) * left_scale\
    \ + Wide(other._numerator) * right_scale,\n                          Wide(_denominator)\
    \ * left_scale);\n        return *this;\n    }\n\n    constexpr Rational& operator-=(const\
    \ Rational& other) {\n        return *this += -other;\n    }\n\n    constexpr\
    \ Rational& operator*=(const Rational& other) {\n        UnsignedWide first_gcd\
    \ = gcd(magnitude(Wide(_numerator)), static_cast<UnsignedWide>(other._denominator));\n\
    \        UnsignedWide second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        T numerator;\n        if (!(input >> numerator))\
    \ return input;\n        T denominator = 1;\n        if (input.peek() == '/')\
    \ {\n            input.get();\n            if (!(input >> denominator)) return\
    \ input;\n        }\n        value = Rational(numerator, denominator);\n     \
    \   return input;\n    }\n};\n\ntemplate <std::signed_integral T>\nconstexpr Rational<T>\
    \ abs(const Rational<T>& value) {\n    return value.abs();\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 4 \"verify/math/rational.test.cpp\"\n\
    \n#line 7 \"verify/math/rational.test.cpp\"\n#include <cstdint>\n#line 10 \"verify/math/rational.test.cpp\"\
    \n#include <sstream>\n\nnamespace {\n\nusing Fraction = m1une::math::Rational<long\
    \ long>;\n\nvoid test_fixed() {\n    constexpr Fraction zero;\n    constexpr Fraction\
    \ half(2, 4);\n    constexpr Fraction negative(3, -6);\n    static_assert(zero.numerator()\
    \ == 0);\n    static_assert(zero.denominator() == 1);\n    static_assert(half\
    \ == Fraction(1, 2));\n    static_assert(negative == Fraction(-1, 2));\n    static_assert(half\
    \ + negative == 0);\n    static_assert(Fraction(2, 3) + Fraction(5, 6) == Fraction(3,\
    \ 2));\n    static_assert(Fraction(2, 3) * Fraction(9, 4) == Fraction(3, 2));\n\
    \    static_assert(Fraction(2, 3) / Fraction(4, 9) == Fraction(3, 2));\n    static_assert(Fraction(-7,\
    \ 3).floor() == -3);\n    static_assert(Fraction(-7, 3).ceil() == -2);\n    static_assert(Fraction(-7,\
    \ 3).trunc() == -2);\n    static_assert(Fraction(1, 3) < Fraction(1, 2));\n  \
    \  static_assert(m1une::math::abs(Fraction(-3, 4)) == Fraction(3, 4));\n\n   \
    \ [[maybe_unused]] Fraction large(\n        std::numeric_limits<long long>::max(),\n\
    \        std::numeric_limits<long long>::max() - 1\n    );\n    assert(large >\
    \ 1);\n\n    std::stringstream stream;\n    stream << Fraction(-6, 8) << ' ' <<\
    \ Fraction(5);\n    assert(stream.str() == \"-3/4 5\");\n    Fraction first;\n\
    \    Fraction second;\n    stream.seekg(0);\n    stream >> first >> second;\n\
    \    assert(first == Fraction(-3, 4));\n    assert(second == 5);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1301;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 100000; ++trial) {\n        long long\
    \ a = static_cast<long long>(random() % 2001) - 1000;\n        long long b = 1\
    \ + static_cast<long long>(random() % 1000);\n        long long c = static_cast<long\
    \ long>(random() % 2001) - 1000;\n        long long d = 1 + static_cast<long long>(random()\
    \ % 1000);\n        Fraction first(a, b);\n        Fraction second(c, d);\n\n\
    \        [[maybe_unused]] __int128_t left = __int128_t(a) * d;\n        [[maybe_unused]]\
    \ __int128_t right = __int128_t(c) * b;\n        assert((first <=> second) ==\
    \ (left <=> right));\n\n        [[maybe_unused]] Fraction sum = first + second;\n\
    \        assert(\n            __int128_t(sum.numerator()) * b * d\n          \
    \  == (__int128_t(a) * d + __int128_t(c) * b)\n                * sum.denominator()\n\
    \        );\n\n        [[maybe_unused]] Fraction product = first * second;\n \
    \       assert(\n            __int128_t(product.numerator()) * b * d\n       \
    \     == __int128_t(a) * c * product.denominator()\n        );\n\n        if (c\
    \ != 0) {\n            [[maybe_unused]] Fraction quotient = first / second;\n\
    \            assert(\n                __int128_t(quotient.numerator()) * b * c\n\
    \                == __int128_t(a) * d * quotient.denominator()\n            );\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n \
    \   test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/rational.hpp\"\n\n#include <cassert>\n#include <compare>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <limits>\n#include <sstream>\n\nnamespace\
    \ {\n\nusing Fraction = m1une::math::Rational<long long>;\n\nvoid test_fixed()\
    \ {\n    constexpr Fraction zero;\n    constexpr Fraction half(2, 4);\n    constexpr\
    \ Fraction negative(3, -6);\n    static_assert(zero.numerator() == 0);\n    static_assert(zero.denominator()\
    \ == 1);\n    static_assert(half == Fraction(1, 2));\n    static_assert(negative\
    \ == Fraction(-1, 2));\n    static_assert(half + negative == 0);\n    static_assert(Fraction(2,\
    \ 3) + Fraction(5, 6) == Fraction(3, 2));\n    static_assert(Fraction(2, 3) *\
    \ Fraction(9, 4) == Fraction(3, 2));\n    static_assert(Fraction(2, 3) / Fraction(4,\
    \ 9) == Fraction(3, 2));\n    static_assert(Fraction(-7, 3).floor() == -3);\n\
    \    static_assert(Fraction(-7, 3).ceil() == -2);\n    static_assert(Fraction(-7,\
    \ 3).trunc() == -2);\n    static_assert(Fraction(1, 3) < Fraction(1, 2));\n  \
    \  static_assert(m1une::math::abs(Fraction(-3, 4)) == Fraction(3, 4));\n\n   \
    \ [[maybe_unused]] Fraction large(\n        std::numeric_limits<long long>::max(),\n\
    \        std::numeric_limits<long long>::max() - 1\n    );\n    assert(large >\
    \ 1);\n\n    std::stringstream stream;\n    stream << Fraction(-6, 8) << ' ' <<\
    \ Fraction(5);\n    assert(stream.str() == \"-3/4 5\");\n    Fraction first;\n\
    \    Fraction second;\n    stream.seekg(0);\n    stream >> first >> second;\n\
    \    assert(first == Fraction(-3, 4));\n    assert(second == 5);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1301;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 100000; ++trial) {\n        long long\
    \ a = static_cast<long long>(random() % 2001) - 1000;\n        long long b = 1\
    \ + static_cast<long long>(random() % 1000);\n        long long c = static_cast<long\
    \ long>(random() % 2001) - 1000;\n        long long d = 1 + static_cast<long long>(random()\
    \ % 1000);\n        Fraction first(a, b);\n        Fraction second(c, d);\n\n\
    \        [[maybe_unused]] __int128_t left = __int128_t(a) * d;\n        [[maybe_unused]]\
    \ __int128_t right = __int128_t(c) * b;\n        assert((first <=> second) ==\
    \ (left <=> right));\n\n        [[maybe_unused]] Fraction sum = first + second;\n\
    \        assert(\n            __int128_t(sum.numerator()) * b * d\n          \
    \  == (__int128_t(a) * d + __int128_t(c) * b)\n                * sum.denominator()\n\
    \        );\n\n        [[maybe_unused]] Fraction product = first * second;\n \
    \       assert(\n            __int128_t(product.numerator()) * b * d\n       \
    \     == __int128_t(a) * c * product.denominator()\n        );\n\n        if (c\
    \ != 0) {\n            [[maybe_unused]] Fraction quotient = first / second;\n\
    \            assert(\n                __int128_t(quotient.numerator()) * b * c\n\
    \                == __int128_t(a) * d * quotient.denominator()\n            );\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n \
    \   test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - math/rational.hpp
  isVerificationFile: true
  path: verify/math/rational.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 03:01:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/rational.test.cpp
layout: document
redirect_from:
- /verify/verify/math/rational.test.cpp
- /verify/verify/math/rational.test.cpp.html
title: verify/math/rational.test.cpp
---
