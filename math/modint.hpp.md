---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_segtree.test.cpp
    title: verify/data_structure/lazy_segtree.test.cpp
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
  requiredBy: []
  timestamp: '2026-06-06 20:32:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/lazy_segtree.test.cpp
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

* `ModInt()`
  Initializes the value to `0`.
  * **Time complexity:** $\mathcal{O}(1)$

* `ModInt(int v)` / `ModInt(long long v)` / `ModInt(unsigned int v)`
  Initializes the structure with the given integer value. Negative values are properly converted to their positive modulo equivalents (e.g., `-1` becomes `Modulus - 1`).
  * **Time complexity:** $\mathcal{O}(1)$

## Methods

* `uint32_t val() const`
  Returns the internal stored value (`_v`), which is guaranteed to be in the range `[0, Modulus - 1]`.
  * **Time complexity:** $\mathcal{O}(1)$

* `ModInt pow(long long n) const`
  Computes the $n$-th power of the current value using binary exponentiation.
  * **Time complexity:** $\mathcal{O}(\log n)$

* `ModInt inv() const`
  Computes the modular multiplicative inverse using the Extended Euclidean Algorithm. Note: The modulus must be coprime to the current value for a valid inverse to exist.
  * **Time complexity:** $\mathcal{O}(\log(\text{Modulus}))$

* `static uint32_t mod()`
  Returns the `Modulus` parameter associated with this type.
  * **Time complexity:** $\mathcal{O}(1)$

* `static ModInt raw(uint32_t v)`
  Constructs a `ModInt` directly from an unsigned integer without applying the modulo operator. This is faster and should only be used if `v` is strictly less than `Modulus`.
  * **Time complexity:** $\mathcal{O}(1)$

## Operators

* **Arithmetic (`+`, `-`, `*`, `+=`, `-=`, `*=`):** Performs basic addition, subtraction, or multiplication with automatic modulo adjustments.
  * **Time complexity:** $\mathcal{O}(1)$
* **Division (`/`, `/=`):** Multiplies by the modular inverse of the right-hand side.
  * **Time complexity:** $\mathcal{O}(\log(\text{Modulus}))$
* **Increment/Decrement (`++`, `--`):** Safely wraps values around $0$ and $Modulus - 1$.
  * **Time complexity:** $\mathcal{O}(1)$
* **Comparison (`==`, `!=`):** Compares the internal values.
  * **Time complexity:** $\mathcal{O}(1)$
* **Stream I/O (`<<`, `>>`):** Inputs standard integers or outputs the internal value.
  * **Time complexity:** $\mathcal{O}(1)$

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
