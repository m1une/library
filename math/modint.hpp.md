---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/all.hpp
    title: fps/all.hpp
  - icon: ':heavy_check_mark:'
    path: fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dual_segtree.test.cpp
    title: verify/data_structure/dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_segtree.test.cpp
    title: verify/data_structure/lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/rake_compress_link_cut_tree.test.cpp
    title: verify/data_structure/rake_compress_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
    title: verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/convolution_mod.test.cpp
    title: verify/fps/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/exp_of_formal_power_series.test.cpp
    title: verify/fps/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/fps_algorithms.test.cpp
    title: verify/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/inv_of_formal_power_series.test.cpp
    title: verify/fps/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: verify/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/multipoint_evaluation.test.cpp
    title: verify/fps/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/polynomial_interpolation.test.cpp
    title: verify/fps/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/polynomial_taylor_shift.test.cpp
    title: verify/fps/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/fps/pow_of_formal_power_series.test.cpp
    title: verify/fps/pow_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/modint.hpp\"\n\n\n\n#include <cstdint>\n#include <iostream>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t\
    \ Modulus>\nstruct ModInt {\n   private:\n    uint32_t _v;\n\n   public:\n   \
    \ static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static\
    \ constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v\
    \ = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\
    \n    constexpr ModInt(int v) noexcept {\n        long long x = (long long)(v\
    \ % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n        _v = static_cast<uint32_t>(x);\n\
    \    }\n\n    constexpr ModInt(long long v) noexcept {\n        long long x =\
    \ (long long)(v % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n \
    \       _v = static_cast<uint32_t>(x);\n    }\n\n    constexpr ModInt(unsigned\
    \ int v) noexcept {\n        _v = static_cast<uint32_t>(v % Modulus);\n    }\n\
    \n    constexpr uint32_t val() const noexcept {\n        return _v;\n    }\n\n\
    \    constexpr ModInt& operator++() noexcept {\n        _v++;\n        if (_v\
    \ == Modulus) _v = 0;\n        return *this;\n    }\n\n    constexpr ModInt& operator--()\
    \ noexcept {\n        if (_v == 0) _v = Modulus;\n        _v--;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt operator++(int) noexcept {\n        ModInt\
    \ res = *this;\n        ++*this;\n        return res;\n    }\n\n    constexpr\
    \ ModInt operator--(int) noexcept {\n        ModInt res = *this;\n        --*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt& operator+=(const ModInt&\
    \ rhs) noexcept {\n        _v += rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator-=(const ModInt&\
    \ rhs) noexcept {\n        _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt&\
    \ rhs) noexcept {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v\
    \ = static_cast<uint32_t>(z % Modulus);\n        return *this;\n    }\n\n    constexpr\
    \ ModInt& operator/=(const ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n\
    \    }\n\n    constexpr ModInt operator+(const ModInt& rhs) const noexcept {\n\
    \        return ModInt(*this) += rhs;\n    }\n    constexpr ModInt operator-(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) -= rhs;\n    }\n\
    \    constexpr ModInt operator*(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) *= rhs;\n    }\n    constexpr ModInt operator/(const ModInt& rhs)\
    \ const noexcept {\n        return ModInt(*this) /= rhs;\n    }\n\n    constexpr\
    \ bool operator==(const ModInt& rhs) const noexcept {\n        return _v == rhs._v;\n\
    \    }\n    constexpr bool operator!=(const ModInt& rhs) const noexcept {\n  \
    \      return _v != rhs._v;\n    }\n\n    constexpr ModInt pow(long long n) const\
    \ noexcept {\n        ModInt res = raw(1), x = *this;\n        while (n > 0) {\n\
    \            if (n & 1) res *= x;\n            x *= x;\n            n >>= 1;\n\
    \        }\n        return res;\n    }\n\n    constexpr ModInt inv() const noexcept\
    \ {\n        int32_t a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n\
    \            int32_t t = a / b;\n            a -= t * b;\n            std::swap(a,\
    \ b);\n            u -= t * v;\n            std::swap(u, v);\n        }\n    \
    \    if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_MODINT_HPP\n#define M1UNE_MATH_MODINT_HPP 1\n\n#include\
    \ <cstdint>\n#include <iostream>\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n   private:\n    uint32_t\
    \ _v;\n\n   public:\n    static constexpr uint32_t mod() {\n        return Modulus;\n\
    \    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt\
    \ x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept\
    \ : _v(0) {}\n\n    constexpr ModInt(int v) noexcept {\n        long long x =\
    \ (long long)(v % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n \
    \       _v = static_cast<uint32_t>(x);\n    }\n\n    constexpr ModInt(long long\
    \ v) noexcept {\n        long long x = (long long)(v % (long long)(Modulus));\n\
    \        if (x < 0) x += Modulus;\n        _v = static_cast<uint32_t>(x);\n  \
    \  }\n\n    constexpr ModInt(unsigned int v) noexcept {\n        _v = static_cast<uint32_t>(v\
    \ % Modulus);\n    }\n\n    constexpr uint32_t val() const noexcept {\n      \
    \  return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept {\n      \
    \  _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n    }\n\n\
    \    constexpr ModInt& operator--() noexcept {\n        if (_v == 0) _v = Modulus;\n\
    \        _v--;\n        return *this;\n    }\n\n    constexpr ModInt operator++(int)\
    \ noexcept {\n        ModInt res = *this;\n        ++*this;\n        return res;\n\
    \    }\n\n    constexpr ModInt operator--(int) noexcept {\n        ModInt res\
    \ = *this;\n        --*this;\n        return res;\n    }\n\n    constexpr ModInt&\
    \ operator+=(const ModInt& rhs) noexcept {\n        _v += rhs._v;\n        if\
    \ (_v >= Modulus) _v -= Modulus;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt& operator-=(const ModInt& rhs) noexcept {\n        _v -= rhs._v;\n  \
    \      if (_v >= Modulus) _v += Modulus;\n        return *this;\n    }\n\n   \
    \ constexpr ModInt& operator*=(const ModInt& rhs) noexcept {\n        uint64_t\
    \ z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z % Modulus);\n\
    \        return *this;\n    }\n\n    constexpr ModInt& operator/=(const ModInt&\
    \ rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int32_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int32_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATH_MODINT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modint.hpp
  requiredBy:
  - fps/formal_power_series.hpp
  - fps/all.hpp
  - fps/multipoint_evaluation.hpp
  - fps/linear_recurrence.hpp
  - fps/convolution.hpp
  timestamp: '2026-06-06 20:32:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/dual_segtree.test.cpp
  - verify/data_structure/rake_compress_link_cut_tree.test.cpp
  - verify/data_structure/lazy_segtree.test.cpp
  - verify/data_structure/yosupo_point_set_tree_path_composite_sum.test.cpp
  - verify/fps/inv_of_formal_power_series.test.cpp
  - verify/fps/pow_of_formal_power_series.test.cpp
  - verify/fps/polynomial_interpolation.test.cpp
  - verify/fps/exp_of_formal_power_series.test.cpp
  - verify/fps/multipoint_evaluation.test.cpp
  - verify/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - verify/fps/convolution_mod.test.cpp
  - verify/fps/polynomial_taylor_shift.test.cpp
  - verify/fps/fps_algorithms.test.cpp
documentation_of: math/modint.hpp
layout: document
title: ModInt
---

## Overview

A struct for automatic modular arithmetic. It wraps standard integer types to safely and automatically apply modulo operations during addition, subtraction, multiplication, and division. This is highly useful in competitive programming to prevent integer overflow and simplify code syntax.

## Template Parameters

* `Modulus`: A `uint32_t` representing the modulo value (e.g., `998244353` or `1000000007`).

## Type Aliases

For convenience, the library provides the following common type aliases:
* `using modint998244353 = ModInt<998244353>;`
* `using modint1000000007 = ModInt<1000000007>;`

## Constructors

| Constructor | Description | Complexity |
| --- | --- | --- |
| `ModInt()` | Initializes the value to `0`. | $\mathcal{O}(1)$ |
| `ModInt(int v)`, `ModInt(long long v)`, `ModInt(unsigned int v)` | Initializes from an integer. Negative values are converted to their positive modulo equivalents. | $\mathcal{O}(1)$ |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `uint32_t val() const` | Returns the stored value in `[0, Modulus - 1]`. | $\mathcal{O}(1)$ |
| `ModInt pow(long long n) const` | Computes the `n`-th power by binary exponentiation. | $\mathcal{O}(\log n)$ |
| `ModInt inv() const` | Computes the modular inverse by the extended Euclidean algorithm. The value and modulus must be coprime. | $\mathcal{O}(\log(\text{Modulus}))$ |
| `static uint32_t mod()` | Returns the modulus associated with this type. | $\mathcal{O}(1)$ |
| `static ModInt raw(uint32_t v)` | Constructs directly from `v` without applying `% Modulus`. Use only when `v < Modulus`. | $\mathcal{O}(1)$ |

## Operators

| Operators | Description | Complexity |
| --- | --- | --- |
| `+`, `-`, `*`, `+=`, `-=`, `*=` | Performs addition, subtraction, or multiplication with automatic modulo adjustment. | $\mathcal{O}(1)$ |
| `/`, `/=` | Multiplies by the modular inverse of the right-hand side. | $\mathcal{O}(\log(\text{Modulus}))$ |
| `++`, `--` | Increments or decrements while wrapping around `0` and `Modulus - 1`. | $\mathcal{O}(1)$ |
| `==`, `!=` | Compares stored values. | $\mathcal{O}(1)$ |
| `<<`, `>>` | Outputs the stored value or inputs a standard integer. | $\mathcal{O}(1)$ |

## Example

```cpp
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;

int main() {
    mint a = 1000000000;
    mint b = 1000000000;

    // Automatic modulo arithmetic
    mint c = a * b; // Will not overflow and handles modulo automatically
    std::cout << "a * b = " << c << "\n";

    // Power
    mint d = a.pow(100);
    std::cout << "a^100 = " << d << "\n";

    // Modular inverse & Division
    mint e = mint(5).inv();
    mint f = a / 5; // Equivalently uses a * mint(5).inv()
    std::cout << "Inverse of 5 = " << e << "\n";
    std::cout << "a / 5 = " << f << "\n";

    return 0;
}
```
