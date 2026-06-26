---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/rational.test.cpp
    title: verify/math/rational.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stern_brocot_tree.test.cpp
    title: verify/math/stern_brocot_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/yosupo_stern_brocot_tree.test.cpp
    title: verify/math/yosupo_stern_brocot_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/rational.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <compare>\n#include <concepts>\n#include <iostream>\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long\
    \ long));\n\n   private:\n    using Wide = __int128_t;\n    using UnsignedWide\
    \ = __uint128_t;\n\n    T _numerator;\n    T _denominator;\n\n    static constexpr\
    \ UnsignedWide magnitude(Wide value) {\n        if (value < 0) {\n           \
    \ return static_cast<UnsignedWide>(-(value + 1)) + 1;\n        }\n        return\
    \ static_cast<UnsignedWide>(value);\n    }\n\n    static constexpr UnsignedWide\
    \ gcd(UnsignedWide first, UnsignedWide second) {\n        while (second != 0)\
    \ {\n            UnsignedWide remainder = first % second;\n            first =\
    \ second;\n            second = remainder;\n        }\n        return first;\n\
    \    }\n\n    static constexpr T narrow(Wide value) {\n        assert(Wide(std::numeric_limits<T>::min())\
    \ <= value);\n        assert(value <= Wide(std::numeric_limits<T>::max()));\n\
    \        return static_cast<T>(value);\n    }\n\n    constexpr void assign_normalized(Wide\
    \ numerator, Wide denominator) {\n        assert(denominator != 0);\n        if\
    \ (numerator == 0) {\n            _numerator = 0;\n            _denominator =\
    \ 1;\n            return;\n        }\n\n        UnsignedWide divisor = gcd(magnitude(numerator),\
    \ magnitude(denominator));\n        numerator /= static_cast<Wide>(divisor);\n\
    \        denominator /= static_cast<Wide>(divisor);\n        if (denominator <\
    \ 0) {\n            numerator = -numerator;\n            denominator = -denominator;\n\
    \        }\n        _numerator = narrow(numerator);\n        _denominator = narrow(denominator);\n\
    \    }\n\n    static constexpr Rational from_wide(Wide numerator, Wide denominator)\
    \ {\n        Rational result;\n        result.assign_normalized(numerator, denominator);\n\
    \        return result;\n    }\n\n   public:\n    constexpr Rational() : _numerator(0),\
    \ _denominator(1) {}\n\n    constexpr Rational(T integer) : _numerator(integer),\
    \ _denominator(1) {}\n\n    constexpr Rational(T numerator, T denominator) {\n\
    \        assign_normalized(Wide(numerator), Wide(denominator));\n    }\n\n   \
    \ constexpr T numerator() const {\n        return _numerator;\n    }\n\n    constexpr\
    \ T denominator() const {\n        return _denominator;\n    }\n\n    constexpr\
    \ bool is_integer() const {\n        return _denominator == 1;\n    }\n\n    constexpr\
    \ int sign() const {\n        return (_numerator > 0) - (_numerator < 0);\n  \
    \  }\n\n    constexpr Rational reciprocal() const {\n        assert(_numerator\
    \ != 0);\n        return from_wide(Wide(_denominator), Wide(_numerator));\n  \
    \  }\n\n    constexpr Rational abs() const {\n        return _numerator < 0 ?\
    \ -*this : *this;\n    }\n\n    constexpr long double to_long_double() const {\n\
    \        return static_cast<long double>(_numerator) / static_cast<long double>(_denominator);\n\
    \    }\n\n    explicit constexpr operator long double() const {\n        return\
    \ to_long_double();\n    }\n\n    constexpr T trunc() const {\n        return\
    \ _numerator / _denominator;\n    }\n\n    constexpr T floor() const {\n     \
    \   T quotient = _numerator / _denominator;\n        if (_numerator < 0 && _numerator\
    \ % _denominator != 0) --quotient;\n        return quotient;\n    }\n\n    constexpr\
    \ T ceil() const {\n        T quotient = _numerator / _denominator;\n        if\
    \ (0 < _numerator && _numerator % _denominator != 0) ++quotient;\n        return\
    \ quotient;\n    }\n\n    constexpr Rational operator+() const {\n        return\
    \ *this;\n    }\n\n    constexpr Rational operator-() const {\n        return\
    \ from_wide(-Wide(_numerator), Wide(_denominator));\n    }\n\n    constexpr Rational&\
    \ operator+=(const Rational& other) {\n        UnsignedWide common =\n       \
    \     gcd(static_cast<UnsignedWide>(_denominator), static_cast<UnsignedWide>(other._denominator));\n\
    \        Wide left_scale = Wide(other._denominator) / static_cast<Wide>(common);\n\
    \        Wide right_scale = Wide(_denominator) / static_cast<Wide>(common);\n\
    \        assign_normalized(Wide(_numerator) * left_scale + Wide(other._numerator)\
    \ * right_scale,\n                          Wide(_denominator) * left_scale);\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator-=(const Rational&\
    \ other) {\n        return *this += -other;\n    }\n\n    constexpr Rational&\
    \ operator*=(const Rational& other) {\n        UnsignedWide first_gcd = gcd(magnitude(Wide(_numerator)),\
    \ static_cast<UnsignedWide>(other._denominator));\n        UnsignedWide second_gcd\
    \ = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));\n\
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
    \ math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_RATIONAL_HPP\n#define M1UNE_MATH_RATIONAL_HPP 1\n\n#include\
    \ <cassert>\n#include <compare>\n#include <concepts>\n#include <iostream>\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace m1une {\nnamespace math {\n\n\
    template <std::signed_integral T = long long>\nstruct Rational {\n    static_assert(sizeof(T)\
    \ <= sizeof(long long));\n\n   private:\n    using Wide = __int128_t;\n    using\
    \ UnsignedWide = __uint128_t;\n\n    T _numerator;\n    T _denominator;\n\n  \
    \  static constexpr UnsignedWide magnitude(Wide value) {\n        if (value <\
    \ 0) {\n            return static_cast<UnsignedWide>(-(value + 1)) + 1;\n    \
    \    }\n        return static_cast<UnsignedWide>(value);\n    }\n\n    static\
    \ constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide second) {\n    \
    \    while (second != 0) {\n            UnsignedWide remainder = first % second;\n\
    \            first = second;\n            second = remainder;\n        }\n   \
    \     return first;\n    }\n\n    static constexpr T narrow(Wide value) {\n  \
    \      assert(Wide(std::numeric_limits<T>::min()) <= value);\n        assert(value\
    \ <= Wide(std::numeric_limits<T>::max()));\n        return static_cast<T>(value);\n\
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
    \ math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_RATIONAL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/rational.hpp
  requiredBy:
  - math/all.hpp
  - math/stern_brocot_tree.hpp
  timestamp: '2026-06-23 03:01:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/rational.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/yosupo_stern_brocot_tree.test.cpp
  - verify/math/stern_brocot_tree.test.cpp
documentation_of: math/rational.hpp
layout: document
title: Rational Number
---

## Overview

`Rational<T>` represents an exact fraction using a signed integral type.

Every value is normalized:

* numerator and denominator are coprime,
* the denominator is positive,
* zero is represented as `0/1`.

The default underlying type is `long long`.

## Construction

```cpp
Rational<T>();
Rational<T>(integer);
Rational<T>(numerator, denominator);
```

The denominator must be nonzero. Integer construction is implicit, so ordinary
integers can be mixed with rationals in arithmetic expressions.

`T` must be a signed integral type no wider than `long long`.

## Complexity Notation

* `M` is the maximum absolute value among the numerator, denominator, and
  widened intermediate values before normalization.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `numerator() const` | Returns the normalized numerator. | $O(1)$ |
| `denominator() const` | Returns the positive normalized denominator. | $O(1)$ |
| `is_integer() const` | Returns whether the denominator is one. | $O(1)$ |
| `sign() const` | Returns `-1`, `0`, or `1`. | $O(1)$ |
| `reciprocal() const` | Returns the reciprocal; requires a nonzero value. | $O(1)$ |
| `abs() const` | Returns the absolute value. | $O(1)$ |
| `trunc() const` | Rounds toward zero. | $O(1)$ |
| `floor() const` | Returns the mathematical floor. | $O(1)$ |
| `ceil() const` | Returns the mathematical ceiling. | $O(1)$ |
| `to_long_double() const` | Returns a floating-point approximation. | $O(1)$ |

Arithmetic operators `+`, `-`, `*`, and `/`, their compound forms, unary signs,
equality, and three-way comparison are supported.

All operations use `__int128_t` intermediates and reduce cross factors before
multiplication when possible. The final normalized numerator and denominator,
and every intermediate widened calculation, must be representable.
Construction and arithmetic normalize with gcd computations and take
$O(\log M)$ time. Comparisons take $O(1)$ widened arithmetic.

## Input and Output

Output uses `numerator/denominator`, omitting `/1` for integers.

Input accepts either an integer or a fraction with no spaces around the slash:

```text
5
-7/12
```

## Example

```cpp
#include "math/rational.hpp"

#include <iostream>

int main() {
    using Fraction = m1une::math::Rational<long long>;

    Fraction first(2, 3);
    Fraction second(5, 6);
    Fraction result = first + second;

    std::cout << result << "\n";        // 3/2
    std::cout << result.floor() << "\n"; // 1
}
```
