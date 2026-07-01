---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
  bundledCode: "#line 1 \"verify/math/modint.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <random>\n#include <type_traits>\n\n#line 1 \"math/modint.hpp\"\n\n\n\
    \n#line 7 \"math/modint.hpp\"\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0\
    \ < Modulus, \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\
    \n   public:\n    static constexpr uint32_t mod() {\n        return Modulus;\n\
    \    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt\
    \ x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept\
    \ : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
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
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/math/modint.test.cpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nstatic_assert(std::is_constructible_v<mint, signed char>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned char>);\nstatic_assert(std::is_constructible_v<mint, short>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned short>);\nstatic_assert(std::is_constructible_v<mint, int>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned int>);\nstatic_assert(std::is_constructible_v<mint, long>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned long>);\nstatic_assert(std::is_constructible_v<mint, long long>);\n\
    static_assert(std::is_constructible_v<mint, unsigned long long>);\n\nconstexpr\
    \ bool test_constexpr_construction() {\n    constexpr std::uint64_t mod = mint::mod();\n\
    \    constexpr long long signed_value = std::numeric_limits<long long>::min();\n\
    \    constexpr unsigned long long unsigned_value =\n        std::numeric_limits<unsigned\
    \ long long>::max();\n\n    mint from_signed = signed_value;\n    mint from_unsigned\
    \ = unsigned_value;\n    std::int64_t signed_remainder = signed_value % std::int64_t(mod);\n\
    \    if (signed_remainder < 0) signed_remainder += mod;\n    return from_signed.val()\
    \ == std::uint64_t(signed_remainder) &&\n           from_unsigned.val() == unsigned_value\
    \ % mod;\n}\n\nstatic_assert(test_constexpr_construction());\n\nvoid test_integral_construction()\
    \ {\n    assert(mint(-1).val() == mint::mod() - 1);\n    assert(mint(std::numeric_limits<unsigned\
    \ long long>::max()).val() ==\n           std::numeric_limits<unsigned long long>::max()\
    \ % mint::mod());\n\n    std::mt19937 random(123456789);\n    mint from_random\
    \ = random();\n    assert(from_random.val() < mint::mod());\n    from_random =\
    \ random() % 100;\n    assert(from_random.val() < 100);\n}\n\nint main() {\n \
    \   test_integral_construction();\n\n    long long a, b;\n    std::cin >> a >>\
    \ b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n#include <random>\n\
    #include <type_traits>\n\n#include \"../../math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nstatic_assert(std::is_constructible_v<mint, signed char>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned char>);\nstatic_assert(std::is_constructible_v<mint, short>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned short>);\nstatic_assert(std::is_constructible_v<mint, int>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned int>);\nstatic_assert(std::is_constructible_v<mint, long>);\nstatic_assert(std::is_constructible_v<mint,\
    \ unsigned long>);\nstatic_assert(std::is_constructible_v<mint, long long>);\n\
    static_assert(std::is_constructible_v<mint, unsigned long long>);\n\nconstexpr\
    \ bool test_constexpr_construction() {\n    constexpr std::uint64_t mod = mint::mod();\n\
    \    constexpr long long signed_value = std::numeric_limits<long long>::min();\n\
    \    constexpr unsigned long long unsigned_value =\n        std::numeric_limits<unsigned\
    \ long long>::max();\n\n    mint from_signed = signed_value;\n    mint from_unsigned\
    \ = unsigned_value;\n    std::int64_t signed_remainder = signed_value % std::int64_t(mod);\n\
    \    if (signed_remainder < 0) signed_remainder += mod;\n    return from_signed.val()\
    \ == std::uint64_t(signed_remainder) &&\n           from_unsigned.val() == unsigned_value\
    \ % mod;\n}\n\nstatic_assert(test_constexpr_construction());\n\nvoid test_integral_construction()\
    \ {\n    assert(mint(-1).val() == mint::mod() - 1);\n    assert(mint(std::numeric_limits<unsigned\
    \ long long>::max()).val() ==\n           std::numeric_limits<unsigned long long>::max()\
    \ % mint::mod());\n\n    std::mt19937 random(123456789);\n    mint from_random\
    \ = random();\n    assert(from_random.val() < mint::mod());\n    from_random =\
    \ random() % 100;\n    assert(from_random.val() < 100);\n}\n\nint main() {\n \
    \   test_integral_construction();\n\n    long long a, b;\n    std::cin >> a >>\
    \ b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/modint.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/modint.test.cpp
layout: document
redirect_from:
- /verify/verify/math/modint.test.cpp
- /verify/verify/math/modint.test.cpp.html
title: verify/math/modint.test.cpp
---
