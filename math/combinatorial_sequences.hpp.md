---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bell_number.test.cpp
    title: verify/math/bell_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bernoulli_number.test.cpp
    title: verify/math/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/partition_function.test.cpp
    title: verify/math/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stirling_number_of_the_second_kind.test.cpp
    title: verify/math/stirling_number_of_the_second_kind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/combinatorial_sequences.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\n#line 1 \"fps/formal_power_series.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"fps/formal_power_series.hpp\"\n#include\
    \ <optional>\n#include <utility>\n#line 10 \"fps/formal_power_series.hpp\"\n\n\
    #line 1 \"fps/convolution.hpp\"\n\n\n\n#line 5 \"fps/convolution.hpp\"\n#include\
    \ <array>\n#line 10 \"fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\n\n\
    \n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n#line 7 \"math/modint.hpp\"\
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
    \ {\n        int64_t a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n\
    \            int64_t t = a / b;\n            a -= t * b;\n            std::swap(a,\
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
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 12 \"fps/formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nstd::optional<Mint> modular_square_root(Mint value) {\n    const uint32_t\
    \ mod = Mint::mod();\n    if (value == Mint(0)) return Mint(0);\n    if (mod ==\
    \ 2) return value;\n    if (value.pow((mod - 1) / 2) != Mint(1)) return std::nullopt;\n\
    \    if (mod % 4 == 3) return value.pow((mod + 1) / 4);\n\n    uint32_t q = mod\
    \ - 1;\n    int s = 0;\n    while ((q & 1) == 0) {\n        q >>= 1;\n       \
    \ s++;\n    }\n\n    Mint z = 2;\n    while (z.pow((mod - 1) / 2) == Mint(1))\
    \ ++z;\n    Mint c = z.pow(q);\n    Mint x = value.pow((q + 1) / 2);\n    Mint\
    \ t = value.pow(q);\n    int m = s;\n    while (t != Mint(1)) {\n        int i\
    \ = 1;\n        Mint squared = t * t;\n        while (squared != Mint(1)) {\n\
    \            squared *= squared;\n            i++;\n        }\n        Mint b\
    \ = c.pow(uint64_t(1) << (m - i - 1));\n        x *= b;\n        c = b * b;\n\
    \        t *= c;\n        m = i;\n    }\n    return x;\n}\n\n}  // namespace internal\n\
    \ntemplate <class Mint>\nstruct FormalPowerSeries : std::vector<Mint> {\n    using\
    \ std::vector<Mint>::vector;\n    using Fps = FormalPowerSeries;\n\n    FormalPowerSeries()\
    \ = default;\n    FormalPowerSeries(const std::vector<Mint>& values) : std::vector<Mint>(values)\
    \ {}\n    FormalPowerSeries(std::vector<Mint>&& values) : std::vector<Mint>(std::move(values))\
    \ {}\n\n    Fps& shrink() {\n        while (!this->empty() && this->back() ==\
    \ Mint(0)) this->pop_back();\n        return *this;\n    }\n\n    Fps pre(int\
    \ degree) const {\n        assert(degree >= 0);\n        Fps result(this->begin(),\
    \ this->begin() + std::min<int>(degree, this->size()));\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    Fps reversed(int size = -1) const {\n  \
    \      Fps result = *this;\n        if (size >= 0) result.resize(size);\n    \
    \    std::reverse(result.begin(), result.end());\n        return result;\n   \
    \ }\n\n    Fps& operator+=(const Fps& rhs) {\n        if (this->size() < rhs.size())\
    \ this->resize(rhs.size());\n        for (int i = 0; i < int(rhs.size()); i++)\
    \ (*this)[i] += rhs[i];\n        return *this;\n    }\n\n    Fps& operator-=(const\
    \ Fps& rhs) {\n        if (this->size() < rhs.size()) this->resize(rhs.size());\n\
    \        for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];\n   \
    \     return *this;\n    }\n\n    Fps& operator*=(const Fps& rhs) {\n        std::vector<Mint>\
    \ lhs(this->begin(), this->end());\n        *this = convolution(lhs, rhs);\n \
    \       return *this;\n    }\n\n    Fps& operator*=(Mint rhs) {\n        for (Mint&\
    \ value : *this) value *= rhs;\n        return *this;\n    }\n\n    Fps& operator/=(Mint\
    \ rhs) {\n        return *this *= rhs.inv();\n    }\n\n    Fps& operator<<=(int\
    \ shift) {\n        assert(shift >= 0);\n        this->insert(this->begin(), shift,\
    \ Mint(0));\n        return *this;\n    }\n\n    Fps& operator>>=(int shift) {\n\
    \        assert(shift >= 0);\n        if (shift >= int(this->size())) {\n    \
    \        this->clear();\n        } else {\n            this->erase(this->begin(),\
    \ this->begin() + shift);\n        }\n        return *this;\n    }\n\n    Fps\
    \ operator+() const {\n        return *this;\n    }\n\n    Fps operator-() const\
    \ {\n        Fps result = *this;\n        for (Mint& value : result) value = Mint(0)\
    \ - value;\n        return result;\n    }\n\n    friend Fps operator+(Fps lhs,\
    \ const Fps& rhs) {\n        return lhs += rhs;\n    }\n\n    friend Fps operator-(Fps\
    \ lhs, const Fps& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Fps\
    \ operator*(Fps lhs, const Fps& rhs) {\n        return lhs *= rhs;\n    }\n\n\
    \    friend Fps operator*(Fps lhs, Mint rhs) {\n        return lhs *= rhs;\n \
    \   }\n\n    friend Fps operator*(Mint lhs, Fps rhs) {\n        return rhs *=\
    \ lhs;\n    }\n\n    friend Fps operator/(Fps lhs, Mint rhs) {\n        return\
    \ lhs /= rhs;\n    }\n\n    friend Fps operator<<(Fps lhs, int shift) {\n    \
    \    return lhs <<= shift;\n    }\n\n    friend Fps operator>>(Fps lhs, int shift)\
    \ {\n        return lhs >>= shift;\n    }\n\n    Fps derivative() const {\n  \
    \      if (this->empty()) return {};\n        Fps result(this->size() - 1);\n\
    \        for (int i = 1; i < int(this->size()); i++) result[i - 1] = (*this)[i]\
    \ * Mint(i);\n        return result;\n    }\n\n    Fps integral() const {\n  \
    \      Fps result(this->size() + 1);\n        if (this->empty()) return result;\n\
    \        assert(this->size() < Mint::mod());\n\n        std::vector<Mint> inverse(this->size()\
    \ + 1);\n        inverse[1] = 1;\n        for (int i = 2; i <= int(this->size());\
    \ i++) {\n            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) *\
    \ inverse[Mint::mod() % uint32_t(i)];\n        }\n        for (int i = 0; i <\
    \ int(this->size()); i++) result[i + 1] = (*this)[i] * inverse[i + 1];\n     \
    \   return result;\n    }\n\n    Mint evaluate(Mint x) const {\n        Mint result\
    \ = 0;\n        for (auto it = this->rbegin(); it != this->rend(); ++it) result\
    \ = result * x + *it;\n        return result;\n    }\n\n    Fps inv(int degree\
    \ = -1) const {\n        if (degree < 0) degree = int(this->size());\n       \
    \ assert(degree >= 0);\n        if (degree == 0) return {};\n        assert(!this->empty()\
    \ && (*this)[0] != Mint(0));\n\n        Fps result(1, (*this)[0].inv());\n   \
    \     for (int size = 1; size < degree; size <<= 1) {\n            const int next_size\
    \ = std::min(size << 1, degree);\n            Fps product = this->pre(next_size)\
    \ * result;\n            product.resize(next_size);\n            for (Mint& value\
    \ : product) value = Mint(0) - value;\n            product[0] += Mint(2);\n  \
    \          result = (result * product).pre(next_size);\n        }\n        return\
    \ result.pre(degree);\n    }\n\n    Fps log(int degree = -1) const {\n       \
    \ if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ == Mint(1));\n        return (derivative() * inv(degree)).pre(degree - 1).integral();\n\
    \    }\n\n    Fps exp(int degree = -1) const {\n        if (degree < 0) degree\
    \ = int(this->size());\n        assert(degree >= 0);\n        if (degree == 0)\
    \ return {};\n        assert(this->empty() || (*this)[0] == Mint(0));\n\n    \
    \    Fps result(1, Mint(1));\n        for (int size = 1; size < degree; size <<=\
    \ 1) {\n            const int next_size = std::min(size << 1, degree);\n     \
    \       Fps correction = this->pre(next_size) - result.log(next_size);\n     \
    \       correction[0] += Mint(1);\n            result = (result * correction).pre(next_size);\n\
    \        }\n        return result.pre(degree);\n    }\n\n    Fps pow(long long\
    \ exponent, int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(exponent >= 0 && degree >= 0);\n        if (degree == 0) return\
    \ {};\n        if (exponent == 0) {\n            Fps result(degree);\n       \
    \     result[0] = 1;\n            return result;\n        }\n\n        int first\
    \ = 0;\n        while (first < int(this->size()) && (*this)[first] == Mint(0))\
    \ first++;\n        if (first == int(this->size()) || first > (degree - 1) / exponent)\
    \ return Fps(degree);\n\n        const int shift = int(first * exponent);\n  \
    \      const Mint leading = (*this)[first];\n        Fps normalized = (*this >>\
    \ first) / leading;\n        Fps result = (normalized.log(degree - shift) * Mint(exponent)).exp(degree\
    \ - shift);\n        result *= leading.pow(exponent);\n        result <<= shift;\n\
    \        result.resize(degree);\n        return result;\n    }\n\n    std::optional<Fps>\
    \ sqrt(int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(degree >= 0);\n        if (degree == 0) return Fps();\n\n    \
    \    int first = 0;\n        while (first < int(this->size()) && (*this)[first]\
    \ == Mint(0)) first++;\n        if (first == int(this->size())) return Fps(degree);\n\
    \        if (first >= degree) return Fps(degree);\n        if (first & 1) return\
    \ std::nullopt;\n\n        const int shift = first / 2;\n        auto leading_root\
    \ = internal::modular_square_root((*this)[first]);\n        if (!leading_root.has_value())\
    \ return std::nullopt;\n\n        const int result_degree = degree - shift;\n\
    \        Fps normalized = (*this >> first) / (*this)[first];\n        Fps result\
    \ = (normalized.log(result_degree) / Mint(2)).exp(result_degree);\n        result\
    \ *= *leading_root;\n        result <<= shift;\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    std::pair<Fps, Fps> divmod(const Fps& divisor)\
    \ const {\n        Fps dividend = *this;\n        Fps normalized_divisor = divisor;\n\
    \        dividend.shrink();\n        normalized_divisor.shrink();\n        assert(!normalized_divisor.empty());\n\
    \n        if (dividend.size() < normalized_divisor.size()) return std::make_pair(Fps(),\
    \ dividend);\n        const int quotient_size = int(dividend.size() - normalized_divisor.size()\
    \ + 1);\n        Fps quotient =\n            (dividend.reversed().pre(quotient_size)\
    \ * normalized_divisor.reversed().inv(quotient_size))\n                .pre(quotient_size)\n\
    \                .reversed();\n        quotient.shrink();\n        Fps remainder\
    \ = dividend - normalized_divisor * quotient;\n        remainder.resize(normalized_divisor.size()\
    \ - 1);\n        remainder.shrink();\n        return std::make_pair(std::move(quotient),\
    \ std::move(remainder));\n    }\n\n    Fps& operator/=(const Fps& rhs) {\n   \
    \     *this = divmod(rhs).first;\n        return *this;\n    }\n\n    Fps& operator%=(const\
    \ Fps& rhs) {\n        *this = divmod(rhs).second;\n        return *this;\n  \
    \  }\n\n    friend Fps operator/(Fps lhs, const Fps& rhs) {\n        return lhs\
    \ /= rhs;\n    }\n\n    friend Fps operator%(Fps lhs, const Fps& rhs) {\n    \
    \    return lhs %= rhs;\n    }\n\n    Fps taylor_shift(Mint shift) const {\n \
    \       const int n = int(this->size());\n        if (n == 0) return {};\n   \
    \     assert(uint32_t(n) < Mint::mod());\n\n        std::vector<Mint> factorial(n,\
    \ Mint(1));\n        std::vector<Mint> inverse_factorial(n, Mint(1));\n      \
    \  for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * Mint(i);\n  \
    \      inverse_factorial[n - 1] = factorial[n - 1].inv();\n        for (int i\
    \ = n - 1; i > 0; i--) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);\n\
    \n        Fps left(n);\n        Fps right(n);\n        Mint power = 1;\n     \
    \   for (int i = 0; i < n; i++) {\n            left[n - 1 - i] = (*this)[i] *\
    \ factorial[i];\n            right[i] = power * inverse_factorial[i];\n      \
    \      power *= shift;\n        }\n        Fps product = left * right;\n     \
    \   Fps result(n);\n        for (int i = 0; i < n; i++) result[i] = product[n\
    \ - 1 - i] * inverse_factorial[i];\n        return result;\n    }\n};\n\n}  //\
    \ namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/combinatorics.hpp\"\
    \n\n\n\n#line 7 \"math/combinatorics.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <class Mint>\nstruct Combinatorics {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n   public:\n    explicit\
    \ Combinatorics(int maximum = 0) : _factorial(1, Mint(1)), _inverse_factorial(1,\
    \ Mint(1)) {\n        ensure(maximum);\n    }\n\n    int maximum() const {\n \
    \       return int(_factorial.size()) - 1;\n    }\n\n    void ensure(int maximum)\
    \ {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n        if (maximum <= this->maximum()) return;\n\n       \
    \ const int old_maximum = this->maximum();\n        _factorial.resize(maximum\
    \ + 1);\n        _inverse_factorial.resize(maximum + 1);\n        for (int i =\
    \ old_maximum + 1; i <= maximum; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum] = _factorial[maximum].inv();\n\
    \        for (int i = maximum; i > old_maximum; i--) {\n            _inverse_factorial[i\
    \ - 1] = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    Mint factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _factorial[n];\n\
    \    }\n\n    Mint inverse_factorial(int n) const {\n        assert(0 <= n &&\
    \ n <= maximum());\n        return _inverse_factorial[n];\n    }\n\n    Mint inverse(int\
    \ n) const {\n        assert(1 <= n && n <= maximum());\n        return _factorial[n\
    \ - 1] * _inverse_factorial[n];\n    }\n\n    Mint binom(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n -\
    \ k];\n    }\n\n    Mint perm(int n, int k) const {\n        if (k < 0 || k >\
    \ n) return Mint(0);\n        assert(n <= maximum());\n        return _factorial[n]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint multiset(int types, int count)\
    \ const {\n        if (types < 0 || count < 0) return Mint(0);\n        if (types\
    \ == 0) return Mint(count == 0);\n        const long long total = static_cast<long\
    \ long>(types) + count - 1;\n        assert(total <= maximum());\n        return\
    \ binom(static_cast<int>(total), count);\n    }\n\n    Mint catalan(int n) const\
    \ {\n        assert(n >= 0);\n        const long long doubled = 2LL * n;\n   \
    \     assert(doubled <= maximum());\n        return binom(int(doubled), n) - binom(int(doubled),\
    \ n + 1);\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/combinatorial_sequences.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <class Mint>\nstd::vector<Mint> catalan_numbers(int maximum) {\n\
    \    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());\n\
    \n    std::vector<Mint> inverse(maximum + 2);\n    inverse[1] = 1;\n    for (int\
    \ i = 2; i <= maximum + 1; i++) {\n        inverse[i] = Mint(0) - Mint(Mint::mod()\
    \ / uint32_t(i)) * inverse[Mint::mod() % uint32_t(i)];\n    }\n\n    std::vector<Mint>\
    \ result(maximum + 1);\n    result[0] = 1;\n    for (int n = 0; n < maximum; n++)\
    \ {\n        result[n + 1] = result[n] * Mint(2) * Mint(2LL * n + 1) * inverse[n\
    \ + 2];\n    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ bernoulli_numbers(int maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n    Combinatorics<Mint>\
    \ combinations(maximum + 1);\n    Fps denominator(maximum + 1);\n    for (int\
    \ i = 0; i <= maximum; i++) {\n        denominator[i] = combinations.inverse_factorial(i\
    \ + 1);\n    }\n\n    Fps generating_function = denominator.inv(maximum + 1);\n\
    \    std::vector<Mint> result(maximum + 1);\n    for (int i = 0; i <= maximum;\
    \ i++) {\n        result[i] = generating_function[i] * combinations.factorial(i);\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> bell_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n    Combinatorics<Mint>\
    \ combinations(maximum);\n    Fps exponent(maximum + 1);\n    for (int i = 1;\
    \ i <= maximum; i++) {\n        exponent[i] = combinations.inverse_factorial(i);\n\
    \    }\n\n    Fps generating_function = exponent.exp(maximum + 1);\n    std::vector<Mint>\
    \ result(maximum + 1);\n    for (int i = 0; i <= maximum; i++) {\n        result[i]\
    \ = generating_function[i] * combinations.factorial(i);\n    }\n    return result;\n\
    }\n\ntemplate <class Mint>\nstd::vector<Mint> stirling_numbers_second_kind(int\
    \ n) {\n    assert(n >= 0);\n    assert(static_cast<uint64_t>(n) < Mint::mod());\n\
    \n    Combinatorics<Mint> combinations(n);\n    std::vector<Mint> powers(n + 1);\n\
    \    std::vector<Mint> signs(n + 1);\n    for (int i = 0; i <= n; i++) {\n   \
    \     powers[i] = Mint(i).pow(n) * combinations.inverse_factorial(i);\n      \
    \  signs[i] = combinations.inverse_factorial(i);\n        if (i & 1) signs[i]\
    \ = Mint(0) - signs[i];\n    }\n\n    std::vector<Mint> result = fps::convolution(powers,\
    \ signs);\n    result.resize(n + 1);\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> partition_numbers(int maximum) {\n    assert(maximum\
    \ >= 0);\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n    Fps denominator(maximum\
    \ + 1);\n    denominator[0] = 1;\n    for (long long k = 1;; k++) {\n        const\
    \ long long first = k * (3 * k - 1) / 2;\n        const long long second = k *\
    \ (3 * k + 1) / 2;\n        if (first > maximum) break;\n\n        const Mint\
    \ sign = (k & 1) ? Mint(-1) : Mint(1);\n        denominator[int(first)] += sign;\n\
    \        if (second <= maximum) denominator[int(second)] += sign;\n    }\n   \
    \ return denominator.inv(maximum + 1);\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ derangement_numbers(int maximum) {\n    assert(maximum >= 0);\n\n    std::vector<Mint>\
    \ result(maximum + 1);\n    result[0] = 1;\n    if (maximum >= 1) result[1] =\
    \ 0;\n    for (int n = 2; n <= maximum; n++) {\n        result[n] = Mint(n - 1)\
    \ * (result[n - 1] + result[n - 2]);\n    }\n    return result;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP\n#define M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include \"\
    ../fps/formal_power_series.hpp\"\n#include \"combinatorics.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <class Mint>\nstd::vector<Mint> catalan_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n\n    std::vector<Mint> inverse(maximum + 2);\n    inverse[1]\
    \ = 1;\n    for (int i = 2; i <= maximum + 1; i++) {\n        inverse[i] = Mint(0)\
    \ - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod() % uint32_t(i)];\n  \
    \  }\n\n    std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    for\
    \ (int n = 0; n < maximum; n++) {\n        result[n + 1] = result[n] * Mint(2)\
    \ * Mint(2LL * n + 1) * inverse[n + 2];\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> bernoulli_numbers(int maximum) {\n    assert(maximum\
    \ >= 0);\n    assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());\n\n  \
    \  using Fps = fps::FormalPowerSeries<Mint>;\n    Combinatorics<Mint> combinations(maximum\
    \ + 1);\n    Fps denominator(maximum + 1);\n    for (int i = 0; i <= maximum;\
    \ i++) {\n        denominator[i] = combinations.inverse_factorial(i + 1);\n  \
    \  }\n\n    Fps generating_function = denominator.inv(maximum + 1);\n    std::vector<Mint>\
    \ result(maximum + 1);\n    for (int i = 0; i <= maximum; i++) {\n        result[i]\
    \ = generating_function[i] * combinations.factorial(i);\n    }\n    return result;\n\
    }\n\ntemplate <class Mint>\nstd::vector<Mint> bell_numbers(int maximum) {\n  \
    \  assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum) < Mint::mod());\n\
    \n    using Fps = fps::FormalPowerSeries<Mint>;\n    Combinatorics<Mint> combinations(maximum);\n\
    \    Fps exponent(maximum + 1);\n    for (int i = 1; i <= maximum; i++) {\n  \
    \      exponent[i] = combinations.inverse_factorial(i);\n    }\n\n    Fps generating_function\
    \ = exponent.exp(maximum + 1);\n    std::vector<Mint> result(maximum + 1);\n \
    \   for (int i = 0; i <= maximum; i++) {\n        result[i] = generating_function[i]\
    \ * combinations.factorial(i);\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> stirling_numbers_second_kind(int n) {\n    assert(n\
    \ >= 0);\n    assert(static_cast<uint64_t>(n) < Mint::mod());\n\n    Combinatorics<Mint>\
    \ combinations(n);\n    std::vector<Mint> powers(n + 1);\n    std::vector<Mint>\
    \ signs(n + 1);\n    for (int i = 0; i <= n; i++) {\n        powers[i] = Mint(i).pow(n)\
    \ * combinations.inverse_factorial(i);\n        signs[i] = combinations.inverse_factorial(i);\n\
    \        if (i & 1) signs[i] = Mint(0) - signs[i];\n    }\n\n    std::vector<Mint>\
    \ result = fps::convolution(powers, signs);\n    result.resize(n + 1);\n    return\
    \ result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> partition_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n\
    \    Fps denominator(maximum + 1);\n    denominator[0] = 1;\n    for (long long\
    \ k = 1;; k++) {\n        const long long first = k * (3 * k - 1) / 2;\n     \
    \   const long long second = k * (3 * k + 1) / 2;\n        if (first > maximum)\
    \ break;\n\n        const Mint sign = (k & 1) ? Mint(-1) : Mint(1);\n        denominator[int(first)]\
    \ += sign;\n        if (second <= maximum) denominator[int(second)] += sign;\n\
    \    }\n    return denominator.inv(maximum + 1);\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> derangement_numbers(int maximum) {\n    assert(maximum >= 0);\n\
    \n    std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    if (maximum\
    \ >= 1) result[1] = 0;\n    for (int n = 2; n <= maximum; n++) {\n        result[n]\
    \ = Mint(n - 1) * (result[n - 1] + result[n - 2]);\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_COMBINATORIAL_SEQUENCES_HPP\n"
  dependsOn:
  - fps/formal_power_series.hpp
  - fps/convolution.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  isVerificationFile: false
  path: math/combinatorial_sequences.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-21 17:44:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/bell_number.test.cpp
  - verify/math/partition_function.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/stirling_number_of_the_second_kind.test.cpp
  - verify/math/bernoulli_number.test.cpp
documentation_of: math/combinatorial_sequences.hpp
layout: document
title: Combinatorial Sequences
---

## Overview

This header generates several standard counting sequences:

* Catalan numbers;
* Bernoulli numbers;
* Bell numbers;
* Stirling numbers of the second kind;
* integer partition numbers;
* derangement numbers.

Every function returns a vector of modular values. Except for the Stirling
function, requesting `maximum` returns every value from index `0` through
`maximum`.

The Bernoulli, Bell, Stirling, and partition implementations use formal power
series and fast convolution. They are suitable for hundreds of thousands of
terms, rather than only the small sizes supported by quadratic dynamic
programming.

## Catalan Numbers

The `n`-th Catalan number is

$$
C_n = \frac{1}{n+1}\binom{2n}{n}.
$$

The first values are:

```text
n:   0  1  2  3   4   5
C_n: 1  1  2  5  14  42
```

Catalan numbers count many equivalent structures, including:

* balanced parenthesis strings containing `n` pairs;
* binary tree shapes with `n` internal vertices;
* ways to triangulate a convex polygon with `n + 2` vertices;
* monotone grid paths that never cross above the diagonal.

For example, the two balanced strings with two pairs are:

```text
()()
(())
```

`catalan_numbers<Mint>(maximum)` computes the sequence in $O(\text{maximum})$
time using

$$
C_{n+1}
= C_n \frac{2(2n+1)}{n+2}.
$$

If a `Combinatorics<Mint>` object already contains factorials through `2 * n`,
its `catalan(n)` method returns one Catalan number in $O(1)$ time.

## Bernoulli Numbers

Bernoulli numbers are rational numbers defined by the exponential generating
function

$$
\frac{x}{e^x-1}
= \sum_{n=0}^{\infty} B_n \frac{x^n}{n!}.
$$

This header uses the convention

$$
B_1 = -\frac{1}{2}.
$$

The first values are:

```text
B_0 = 1
B_1 = -1/2
B_2 = 1/6
B_3 = 0
B_4 = -1/30
B_5 = 0
B_6 = 1/42
```

Bernoulli numbers do not directly count a simple family of objects. Their most
common contest use is evaluating sums of powers. For example,

$$
1^p + 2^p + \cdots + n^p
= \frac{1}{p+1}
  \sum_{j=0}^{p}
  (-1)^j \binom{p+1}{j} B_j n^{p+1-j}.
$$

They also appear in finite differences, polynomial interpolation, and advanced
number theory.

The returned values are modular representations of the rational numbers.
For example, `B_1` is `-1 * inverse(2)` modulo `Mint::mod()`.

`bernoulli_numbers<Mint>(maximum)` computes all terms in
$O(\text{maximum} \log \text{maximum})$ time by inverting the series

$$
\frac{e^x-1}{x}
= \sum_{n=0}^{\infty}\frac{x^n}{(n+1)!}.
$$

## Stirling Numbers of the Second Kind

The Stirling number of the second kind $S(n,k)$ counts ways to divide a set of
`n` distinct elements into exactly `k` nonempty, unlabeled groups.

For the set containing `a`, `b`, and `c`:

* $S(3,1)=1$: all elements are in one group;
* $S(3,2)=3$: one element is alone and the other two are together;
* $S(3,3)=1$: every element is alone.

The row for `n = 5` is:

```text
k:       0  1   2   3   4  5
S(5,k):  0  1  15  25  10  1
```

`stirling_numbers_second_kind<Mint>(n)` returns this entire row. It uses the
convolution identity

$$
S(n,k)
= \sum_{i=0}^{k}
  \frac{(-1)^{k-i} i^n}{i!(k-i)!}
$$

and runs in $O(n \log n)$ time.

## Bell Numbers

The Bell number counts ways to divide a set of `n` distinct elements into any
number of nonempty, unlabeled groups.

The first values are:

```text
n:       0  1  2  3   4   5
Bell_n:  1  1  2  5  15  52
```

Bell numbers and Stirling numbers are related by

$$
\operatorname{Bell}_n = \sum_{k=0}^{n} S(n,k).
$$

Their exponential generating function is

$$
\exp(e^x-1)
= \sum_{n=0}^{\infty}
  \operatorname{Bell}_n \frac{x^n}{n!}.
$$

`bell_numbers<Mint>(maximum)` evaluates this series in
$O(\text{maximum} \log \text{maximum})$ time.

Bernoulli numbers and Bell numbers are both traditionally written as `B_n`,
but they are unrelated sequences. The API uses distinct function names to
avoid that ambiguity.

## Integer Partition Numbers

The partition number $p(n)$ counts ways to write `n` as a sum of positive
integers when order does not matter.

For example, $p(5)=7$:

```text
5
4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

This is different from a Bell number: integer partitions split an integer,
while Bell numbers split a set of distinct elements.

The generating function is

$$
\prod_{k=1}^{\infty}\frac{1}{1-x^k}
= \sum_{n=0}^{\infty}p(n)x^n.
$$

Euler's pentagonal number theorem gives a sparse denominator, which the
implementation inverts with formal power series. Therefore
`partition_numbers<Mint>(maximum)` runs in
$O(\text{maximum} \log \text{maximum})$ time.

## Derangements

A derangement is a permutation in which no element remains in its original
position.

For three elements, the two derangements are:

```text
2 3 1
3 1 2
```

The first values are:

```text
n:    0  1  2  3  4   5
D_n:  1  0  1  2  9  44
```

The sequence satisfies

$$
D_n = (n-1)(D_{n-1}+D_{n-2}).
$$

`derangement_numbers<Mint>(maximum)` uses this recurrence and runs in
$O(\text{maximum})$ time.

## API

```cpp
template <class Mint>
std::vector<Mint> catalan_numbers(int maximum);

template <class Mint>
std::vector<Mint> bernoulli_numbers(int maximum);

template <class Mint>
std::vector<Mint> bell_numbers(int maximum);

template <class Mint>
std::vector<Mint> stirling_numbers_second_kind(int n);

template <class Mint>
std::vector<Mint> partition_numbers(int maximum);

template <class Mint>
std::vector<Mint> derangement_numbers(int maximum);
```

The template argument `Mint` is the element type of the returned
`std::vector<Mint>`. The function argument is an `int` and must be
nonnegative. Except for Stirling numbers, a call with `maximum` returns a
vector of length `maximum + 1`. The Stirling function returns a vector of
length `n + 1`.

| Function | Returned values | Complexity |
| --- | --- | --- |
| `catalan_numbers<Mint>(maximum)` | `C_0` through `C_maximum` | $O(n)$ |
| `bernoulli_numbers<Mint>(maximum)` | `B_0` through `B_maximum` | $O(n \log n)$ |
| `bell_numbers<Mint>(maximum)` | Bell numbers `0` through `maximum` | $O(n \log n)$ |
| `stirling_numbers_second_kind<Mint>(n)` | `S(n, 0)` through `S(n, n)` | $O(n \log n)$ |
| `partition_numbers<Mint>(maximum)` | `p(0)` through `p(maximum)` | $O(n \log n)$ |
| `derangement_numbers<Mint>(maximum)` | `D_0` through `D_maximum` | $O(n)$ |

Every function uses $O(n)$ memory.

## Requirements

The fast formulas are intended for a static modular integer such as
`modint998244353`.

* The modulus should be prime for Catalan, Bernoulli, Bell, and Stirling
  numbers because the algorithms use modular inverses.
* `maximum + 1` must be smaller than the modulus for Catalan and Bernoulli
  numbers.
* `maximum` must be smaller than the modulus for Bell and Stirling numbers.
* The formal-power-series transform length must be supported by the convolution
  implementation. Modulus `998244353` is the standard fast choice.

These functions return residues modulo `Mint::mod()`, not arbitrary-precision
integers.

## Example

```cpp
#include "math/combinatorial_sequences.hpp"
#include "math/modint.hpp"

#include <iostream>

using Mint = m1une::math::modint998244353;

int main() {
    auto catalan = m1une::math::catalan_numbers<Mint>(10);
    auto bernoulli = m1une::math::bernoulli_numbers<Mint>(10);
    auto partitions = m1une::math::partition_numbers<Mint>(10);

    std::cout << catalan[5] << "\n";     // 42
    std::cout << bernoulli[1] * 2 << "\n";  // -1 modulo 998244353
    std::cout << partitions[5] << "\n";  // 7
}
```
