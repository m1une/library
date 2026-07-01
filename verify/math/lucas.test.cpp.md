---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/lucas.hpp
    title: Lucas's Theorem
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
  bundledCode: "#line 1 \"verify/math/lucas.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/lucas.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\n\
    struct Lucas {\n   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint>\
    \ _inverse_factorial;\n\n    Mint small_binom(uint32_t n, uint32_t k) const {\n\
    \        if (k > n) return Mint(0);\n        return _factorial[n] * _inverse_factorial[k]\
    \ * _inverse_factorial[n - k];\n    }\n\n   public:\n    Lucas() {\n        const\
    \ uint32_t prime = Mint::mod();\n        assert(2 <= prime);\n        _factorial.resize(prime);\n\
    \        _inverse_factorial.resize(prime);\n        _factorial[0] = Mint(1);\n\
    \        for (uint32_t i = 1; i < prime; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[prime - 1] = _factorial[prime\
    \ - 1].inv();\n        for (uint32_t i = prime - 1; i > 0; i--) {\n          \
    \  _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);\n        }\n \
    \   }\n\n    uint32_t prime() const {\n        return Mint::mod();\n    }\n\n\
    \    Mint binom(uint64_t n, uint64_t k) const {\n        if (k > n) return Mint(0);\n\
    \        const uint64_t modulus = Mint::mod();\n        Mint result = Mint(1);\n\
    \        while (n > 0 || k > 0) {\n            uint32_t n_digit = uint32_t(n %\
    \ modulus);\n            uint32_t k_digit = uint32_t(k % modulus);\n         \
    \   if (k_digit > n_digit) return Mint(0);\n            result *= small_binom(n_digit,\
    \ k_digit);\n            n /= modulus;\n            k /= modulus;\n        }\n\
    \        return result;\n    }\n\n    Mint operator()(uint64_t n, uint64_t k)\
    \ const {\n        return binom(n, k);\n    }\n};\n\ntemplate <class Mint>\nusing\
    \ LucasTheorem = Lucas<Mint>;\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
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
    \ m1une\n\n\n#line 5 \"verify/math/lucas.test.cpp\"\n\n#line 10 \"verify/math/lucas.test.cpp\"\
    \n\nnamespace {\n\ntemplate <uint32_t Prime>\nvoid test_prime() {\n    using Mint\
    \ = m1une::math::ModInt<Prime>;\n    m1une::math::Lucas<Mint> lucas;\n    assert(lucas.prime()\
    \ == Prime);\n\n    const int maximum = 500;\n    std::vector<Mint> previous(maximum\
    \ + 2);\n    previous[0] = Mint(1);\n    for (int n = 0; n <= maximum; n++) {\n\
    \        for (int k = 0; k <= n; k++) {\n            assert(lucas.binom(n, k)\
    \ == previous[k]);\n            assert(lucas(n, k) == previous[k]);\n        }\n\
    \        assert(lucas.binom(n, uint64_t(n) + 1) == Mint(0));\n\n        std::vector<Mint>\
    \ next(maximum + 2);\n        next[0] = Mint(1);\n        for (int k = 1; k <=\
    \ n + 1; k++) {\n            next[k] = previous[k - 1] + previous[k];\n      \
    \  }\n        previous.swap(next);\n    }\n}\n\nvoid test_large_arguments() {\n\
    \    using Mint2 = m1une::math::ModInt<2>;\n    m1une::math::Lucas<Mint2> binary;\n\
    \    uint64_t n = 0xF0F0F0F0F0F0F0F0ULL;\n    uint64_t subset = 0x1010101010101010ULL;\n\
    \    uint64_t not_subset = subset | 1ULL;\n    assert(binary(n, subset) == Mint2(1));\n\
    \    assert(binary(n, not_subset) == Mint2(0));\n\n    using Mint5 = m1une::math::ModInt<5>;\n\
    \    m1une::math::LucasTheorem<Mint5> base_five;\n    const uint64_t power = 7450580596923828125ULL;\n\
    \    assert(base_five.binom(power, 0) == Mint5(1));\n    assert(base_five.binom(power,\
    \ power) == Mint5(1));\n    assert(base_five.binom(power, 1) == Mint5(0));\n \
    \   assert(base_five.binom(power + 3, 2) == Mint5(3));\n}\n\n}  // namespace\n\
    \nint main() {\n    test_prime<2>();\n    test_prime<3>();\n    test_prime<5>();\n\
    \    test_prime<7>();\n    test_prime<11>();\n    test_prime<13>();\n    test_large_arguments();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/lucas.hpp\"\n#include \"../../math/modint.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nnamespace {\n\n\
    template <uint32_t Prime>\nvoid test_prime() {\n    using Mint = m1une::math::ModInt<Prime>;\n\
    \    m1une::math::Lucas<Mint> lucas;\n    assert(lucas.prime() == Prime);\n\n\
    \    const int maximum = 500;\n    std::vector<Mint> previous(maximum + 2);\n\
    \    previous[0] = Mint(1);\n    for (int n = 0; n <= maximum; n++) {\n      \
    \  for (int k = 0; k <= n; k++) {\n            assert(lucas.binom(n, k) == previous[k]);\n\
    \            assert(lucas(n, k) == previous[k]);\n        }\n        assert(lucas.binom(n,\
    \ uint64_t(n) + 1) == Mint(0));\n\n        std::vector<Mint> next(maximum + 2);\n\
    \        next[0] = Mint(1);\n        for (int k = 1; k <= n + 1; k++) {\n    \
    \        next[k] = previous[k - 1] + previous[k];\n        }\n        previous.swap(next);\n\
    \    }\n}\n\nvoid test_large_arguments() {\n    using Mint2 = m1une::math::ModInt<2>;\n\
    \    m1une::math::Lucas<Mint2> binary;\n    uint64_t n = 0xF0F0F0F0F0F0F0F0ULL;\n\
    \    uint64_t subset = 0x1010101010101010ULL;\n    uint64_t not_subset = subset\
    \ | 1ULL;\n    assert(binary(n, subset) == Mint2(1));\n    assert(binary(n, not_subset)\
    \ == Mint2(0));\n\n    using Mint5 = m1une::math::ModInt<5>;\n    m1une::math::LucasTheorem<Mint5>\
    \ base_five;\n    const uint64_t power = 7450580596923828125ULL;\n    assert(base_five.binom(power,\
    \ 0) == Mint5(1));\n    assert(base_five.binom(power, power) == Mint5(1));\n \
    \   assert(base_five.binom(power, 1) == Mint5(0));\n    assert(base_five.binom(power\
    \ + 3, 2) == Mint5(3));\n}\n\n}  // namespace\n\nint main() {\n    test_prime<2>();\n\
    \    test_prime<3>();\n    test_prime<5>();\n    test_prime<7>();\n    test_prime<11>();\n\
    \    test_prime<13>();\n    test_large_arguments();\n\n    long long a, b;\n \
    \   std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/lucas.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/lucas.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/lucas.test.cpp
layout: document
redirect_from:
- /verify/verify/math/lucas.test.cpp
- /verify/verify/math/lucas.test.cpp.html
title: verify/math/lucas.test.cpp
---
