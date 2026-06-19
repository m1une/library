---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/convolution.hpp
    title: Convolution
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
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"verify/fps/convolution_mod.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include <iostream>\n#include\
    \ <vector>\n\n#line 1 \"fps/convolution.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <utility>\n#line 10\
    \ \"fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 7 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr\
    \ uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr ModInt\
    \ raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n        return\
    \ x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    constexpr ModInt(int\
    \ v) noexcept {\n        long long x = (long long)(v % (long long)(Modulus));\n\
    \        if (x < 0) x += Modulus;\n        _v = static_cast<uint32_t>(x);\n  \
    \  }\n\n    constexpr ModInt(long long v) noexcept {\n        long long x = (long\
    \ long)(v % (long long)(Modulus));\n        if (x < 0) x += Modulus;\n       \
    \ _v = static_cast<uint32_t>(x);\n    }\n\n    constexpr ModInt(unsigned int v)\
    \ noexcept {\n        _v = static_cast<uint32_t>(v % Modulus);\n    }\n\n    constexpr\
    \ uint32_t val() const noexcept {\n        return _v;\n    }\n\n    constexpr\
    \ ModInt& operator++() noexcept {\n        _v++;\n        if (_v == Modulus) _v\
    \ = 0;\n        return *this;\n    }\n\n    constexpr ModInt& operator--() noexcept\
    \ {\n        if (_v == 0) _v = Modulus;\n        _v--;\n        return *this;\n\
    \    }\n\n    constexpr ModInt operator++(int) noexcept {\n        ModInt res\
    \ = *this;\n        ++*this;\n        return res;\n    }\n\n    constexpr ModInt\
    \ operator--(int) noexcept {\n        ModInt res = *this;\n        --*this;\n\
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
    \ m1une\n\n\n#line 12 \"fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\nnamespace internal {\n\nconstexpr uint32_t primitive_root_constexpr(uint32_t\
    \ mod) {\n    if (mod == 2) return 1;\n    if (mod == 167772161) return 3;\n \
    \   if (mod == 469762049) return 3;\n    if (mod == 754974721) return 11;\n  \
    \  if (mod == 998244353) return 3;\n    if (mod == 1224736769) return 3;\n\n \
    \   uint32_t divisors[32] = {};\n    int count = 0;\n    uint32_t x = mod - 1;\n\
    \    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {\n        if (x % p != 0)\
    \ continue;\n        divisors[count++] = p;\n        while (x % p == 0) x /= p;\n\
    \    }\n    if (x > 1) divisors[count++] = x;\n\n    for (uint32_t g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < count; i++) {\n    \
    \        uint64_t value = 1;\n            uint64_t base = g;\n            uint32_t\
    \ exponent = (mod - 1) / divisors[i];\n            while (exponent > 0) {\n  \
    \              if (exponent & 1) value = value * base % mod;\n               \
    \ base = base * base % mod;\n                exponent >>= 1;\n            }\n\
    \            if (value == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\nconstexpr int\
    \ two_adic_order(uint32_t x) {\n    int result = 0;\n    while ((x & 1) == 0)\
    \ {\n        x >>= 1;\n        result++;\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstruct NttRoots {\n    static constexpr int max_base = two_adic_order(Mint::mod()\
    \ - 1);\n    std::array<Mint, max_base + 1> root;\n    std::array<Mint, max_base\
    \ + 1> inverse_root;\n\n    NttRoots() {\n        constexpr uint32_t primitive_root\
    \ = primitive_root_constexpr(Mint::mod());\n        for (int level = 1; level\
    \ <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>& ntt_roots()\
    \ {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\ntemplate\
    \ <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse) {\n    const int\
    \ n = int(a.size());\n    assert(n > 0 && (n & (n - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(n) == 0);\n\n    for (int i = 1, j = 0; i < n; i++) {\n    \
    \    int bit = n >> 1;\n        while (j & bit) {\n            j ^= bit;\n   \
    \         bit >>= 1;\n        }\n        j ^= bit;\n        if (i < j) std::swap(a[i],\
    \ a[j]);\n    }\n\n    const auto& roots = ntt_roots<Mint>();\n    int level =\
    \ 1;\n    for (int len = 2; len <= n; len <<= 1, level++) {\n        const Mint\
    \ step = inverse ? roots.inverse_root[level] : roots.root[level];\n        const\
    \ int half = len >> 1;\n        for (int offset = 0; offset < n; offset += len)\
    \ {\n            Mint w = 1;\n            for (int j = 0; j < half; j++) {\n \
    \               Mint even = a[offset + j];\n                Mint odd = a[offset\
    \ + j + half] * w;\n                a[offset + j] = even + odd;\n            \
    \    a[offset + j + half] = even - odd;\n                w *= step;\n        \
    \    }\n        }\n    }\n\n    if (inverse) {\n        const Mint inverse_n =\
    \ Mint(n).inv();\n        for (Mint& value : a) value *= inverse_n;\n    }\n}\n\
    \n}  // namespace internal\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_naive(const\
    \ std::vector<Mint>& a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty())\
    \ return {};\n    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size()\
    \ < b.size()) {\n        for (int i = 0; i < int(a.size()); i++) {\n         \
    \   for (int j = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n  \
    \      }\n    } else {\n        for (int j = 0; j < int(b.size()); j++) {\n  \
    \          for (int i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>& b) {\n\
    \    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n \
    \   while (n < result_size) n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n)\
    \ == 0);\n\n    std::vector<Mint> fa(a.begin(), a.end());\n    std::vector<Mint>\
    \ fb(b.begin(), b.end());\n    fa.resize(n);\n    fb.resize(n);\n    internal::ntt(fa,\
    \ false);\n    internal::ntt(fb, false);\n    for (int i = 0; i < n; i++) fa[i]\
    \ *= fb[i];\n    internal::ntt(fa, true);\n    fa.resize(result_size);\n    return\
    \ fa;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> convolution(const std::vector<Mint>&\
    \ a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    if (std::min(a.size(), b.size()) <= 32) return convolution_naive(a, b);\n\
    \n    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n\
    \    while (n < result_size) n <<= 1;\n    if ((Mint::mod() - 1) % uint32_t(n)\
    \ == 0) return convolution_ntt(a, b);\n\n    using Mint1 = math::ModInt<167772161>;\n\
    \    using Mint2 = math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n\
    \    assert(n <= (1 << 24));\n\n    const unsigned __int128 coefficient_bound\
    \ =\n        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod()\
    \ - 1) *\n        (Mint::mod() - 1);\n    const unsigned __int128 crt_modulus\
    \ =\n        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod() * Mint3::mod();\n\
    \    assert(coefficient_bound < crt_modulus);\n\n    auto converted_convolution\
    \ = [&]<class OtherMint>() {\n        std::vector<OtherMint> converted_a(a.size());\n\
    \        std::vector<OtherMint> converted_b(b.size());\n        for (int i = 0;\
    \ i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());\n        for\
    \ (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());\n\
    \        return convolution_ntt(converted_a, converted_b);\n    };\n    std::vector<Mint1>\
    \ c1 = converted_convolution.template operator()<Mint1>();\n    std::vector<Mint2>\
    \ c2 = converted_convolution.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ c3 = converted_convolution.template operator()<Mint3>();\n    static const uint64_t\
    \ inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n    static const uint64_t\
    \ mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static const uint64_t mod1_mod2_mod3\
    \ =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();\n    static\
    \ const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
    \n    const uint64_t target_mod = Mint::mod();\n    const uint64_t mod1_target\
    \ = Mint1::mod() % target_mod;\n    const uint64_t mod1_mod2_target = mod1_target\
    \ * (Mint2::mod() % target_mod) % target_mod;\n    std::vector<Mint> result(result_size);\n\
    \    for (int i = 0; i < result_size; i++) {\n        const uint64_t r1 = c1[i].val();\n\
    \        const uint64_t r2 = c2[i].val();\n        const uint64_t r3 = c3[i].val();\n\
    \        const uint64_t first =\n            (r2 + Mint2::mod() - r1 % Mint2::mod())\
    \ % Mint2::mod() * inverse_mod1_mod2 %\n            Mint2::mod();\n        const\
    \ uint64_t combined_mod3 =\n            (r1 % Mint3::mod() + mod1_mod3 * (first\
    \ % Mint3::mod())) % Mint3::mod();\n        const uint64_t second =\n        \
    \    (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3\
    \ %\n            Mint3::mod();\n\n        uint64_t value = r1 % target_mod;\n\
    \        value = (value + mod1_target * (first % target_mod)) % target_mod;\n\
    \        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;\n\
    \        result[i] = Mint::raw(uint32_t(value));\n    }\n    return result;\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 8 \"verify/fps/convolution_mod.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<mint>\
    \ a(n), b(m);\n    for (mint& value : a) std::cin >> value;\n    for (mint& value\
    \ : b) std::cin >> value;\n    std::vector<mint> result = m1une::fps::convolution(a,\
    \ b);\n    for (int i = 0; i < int(result.size()); i++) {\n        if (i) std::cout\
    \ << ' ';\n        std::cout << result[i];\n    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#include \"fps/convolution.hpp\"\n#include\
    \ \"math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n, m;\n    std::cin >> n >> m;\n    std::vector<mint> a(n), b(m);\n    for\
    \ (mint& value : a) std::cin >> value;\n    for (mint& value : b) std::cin >>\
    \ value;\n    std::vector<mint> result = m1une::fps::convolution(a, b);\n    for\
    \ (int i = 0; i < int(result.size()); i++) {\n        if (i) std::cout << ' ';\n\
    \        std::cout << result[i];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - fps/convolution.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/fps/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 07:30:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/fps/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/verify/fps/convolution_mod.test.cpp
- /verify/verify/fps/convolution_mod.test.cpp.html
title: verify/fps/convolution_mod.test.cpp
---
