---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  - verify/data_structure/lazy_segtree.test.cpp
documentation_of: math/modint.hpp
layout: document
redirect_from:
- /library/math/modint.hpp
- /library/math/modint.hpp.html
title: math/modint.hpp
---
