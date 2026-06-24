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
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  - icon: ':heavy_check_mark:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Square Root and Power
  - icon: ':heavy_check_mark:'
    path: math/lucas.hpp
    title: Lucas's Theorem
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':heavy_check_mark:'
    path: math/prime_sieve.hpp
    title: Prime Sieve
  - icon: ':heavy_check_mark:'
    path: math/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  - icon: ':heavy_check_mark:'
    path: math/tetration.hpp
    title: Tetration
  - icon: ':heavy_check_mark:'
    path: math/two_square_sum.hpp
    title: Sum of Two Squares
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/all.hpp\"\n\n\n\n#line 1 \"math/bitwise_convolution.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#line 7 \"math/zeta_mobius_transform.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail\
    \ {\n\ninline bool is_power_of_two(std::size_t size) noexcept {\n    return size\
    \ != 0 && (size & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/bitwise_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace bitwise_convolution_detail {\n\ninline std::size_t common_size(\n\
    \    std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid walsh_hadamard_transform(\n    std::vector<T>& values,\n\
    \    bool inverse = false\n) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t length = 1; length < values.size(); length <<= 1) {\n  \
    \      for (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += length << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < length; ++offset) {\n                T first = values[block +\
    \ offset];\n                T second = values[block + offset + length];\n    \
    \            values[block + offset] = first + second;\n                values[block\
    \ + offset + length] = first - second;\n            }\n        }\n    }\n    if\
    \ (inverse) {\n        T size = T(static_cast<long long>(values.size()));\n  \
    \      for (T& value : values) value /= size;\n    }\n}\n\ntemplate <typename\
    \ T>\nstd::vector<T> bitwise_or_convolution(\n    std::vector<T> first,\n    std::vector<T>\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ size = bitwise_convolution_detail::common_size(\n        first.size(),\n   \
    \     second.size()\n    );\n    first.resize(size);\n    second.resize(size);\n\
    \    subset_zeta_transform(first);\n    subset_zeta_transform(second);\n    first\
    \ = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    subset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_and_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    superset_zeta_transform(first);\n    superset_zeta_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    superset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_xor_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    walsh_hadamard_transform(first);\n    walsh_hadamard_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    walsh_hadamard_transform(first, true);\n    return\
    \ first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"math/combinatorics.hpp\"\n\n\n\n#line 5 \"math/combinatorics.hpp\"\
    \n#include <cstdint>\n#line 7 \"math/combinatorics.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <class Mint>\nstruct Combinatorics {\n   private:\n\
    \    std::vector<Mint> _factorial;\n    std::vector<Mint> _inverse_factorial;\n\
    \n   public:\n    explicit Combinatorics(int maximum = 0) : _factorial(1, Mint(1)),\
    \ _inverse_factorial(1, Mint(1)) {\n        ensure(maximum);\n    }\n\n    int\
    \ maximum() const {\n        return int(_factorial.size()) - 1;\n    }\n\n   \
    \ void ensure(int maximum) {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
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
    \ 1 \"math/combinatorial_sequences.hpp\"\n\n\n\n#line 7 \"math/combinatorial_sequences.hpp\"\
    \n\n#line 1 \"fps/formal_power_series.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 7 \"fps/formal_power_series.hpp\"\n#include <optional>\n#line 10 \"fps/formal_power_series.hpp\"\
    \n\n#line 1 \"fps/convolution.hpp\"\n\n\n\n#line 5 \"fps/convolution.hpp\"\n#include\
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
    \ namespace fps\n}  // namespace m1une\n\n\n#line 10 \"math/combinatorial_sequences.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ catalan_numbers(int maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
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
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/integer_arithmetic.hpp\"\
    \n\n\n\n#line 5 \"math/integer_arithmetic.hpp\"\n#include <concepts>\n#include\
    \ <limits>\n#line 8 \"math/integer_arithmetic.hpp\"\n#include <type_traits>\n\n\
    namespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail {\n\
    \ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr std::optional<T> checked_multiply(T first, T second) {\n    constexpr\
    \ T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum = std::numeric_limits<T>::max();\n\
    \n    if constexpr (std::unsigned_integral<T>) {\n        if (second != 0 && maximum\
    \ / second < first) return std::nullopt;\n    } else {\n        if (0 < first)\
    \ {\n            if (0 < second) {\n                if (maximum / second < first)\
    \ return std::nullopt;\n            } else if (second < minimum / first) {\n \
    \               return std::nullopt;\n            }\n        } else if (first\
    \ < 0) {\n            if (0 < second) {\n                if (first < minimum /\
    \ second) return std::nullopt;\n            } else if (second < maximum / first)\
    \ {\n                return std::nullopt;\n            }\n        }\n    }\n \
    \   return T(first * second);\n}\n\n}  // namespace integer_arithmetic_detail\n\
    \n// Returns floor(sqrt(value)) exactly, without floating-point arithmetic.\n\
    template <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>) assert(0\
    \ <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n    T high\
    \ = value / 2 + 1;\n    while (low < high) {\n        T middle = low + (high -\
    \ low + 1) / 2;\n        if (middle <= value / middle) {\n            low = middle;\n\
    \        } else {\n            high = middle - 1;\n        }\n    }\n    return\
    \ low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
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
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"\
    math/lucas.hpp\"\n\n\n\n#line 7 \"math/lucas.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class Mint>\nstruct Lucas {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n    Mint small_binom(uint32_t\
    \ n, uint32_t k) const {\n        if (k > n) return Mint(0);\n        return _factorial[n]\
    \ * _inverse_factorial[k] * _inverse_factorial[n - k];\n    }\n\n   public:\n\
    \    Lucas() {\n        const uint32_t prime = Mint::mod();\n        assert(2\
    \ <= prime);\n        _factorial.resize(prime);\n        _inverse_factorial.resize(prime);\n\
    \        _factorial[0] = Mint(1);\n        for (uint32_t i = 1; i < prime; i++)\
    \ {\n            _factorial[i] = _factorial[i - 1] * Mint(i);\n        }\n   \
    \     _inverse_factorial[prime - 1] = _factorial[prime - 1].inv();\n        for\
    \ (uint32_t i = prime - 1; i > 0; i--) {\n            _inverse_factorial[i - 1]\
    \ = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    uint32_t prime()\
    \ const {\n        return Mint::mod();\n    }\n\n    Mint binom(uint64_t n, uint64_t\
    \ k) const {\n        if (k > n) return Mint(0);\n        const uint64_t modulus\
    \ = Mint::mod();\n        Mint result = Mint(1);\n        while (n > 0 || k >\
    \ 0) {\n            uint32_t n_digit = uint32_t(n % modulus);\n            uint32_t\
    \ k_digit = uint32_t(k % modulus);\n            if (k_digit > n_digit) return\
    \ Mint(0);\n            result *= small_binom(n_digit, k_digit);\n           \
    \ n /= modulus;\n            k /= modulus;\n        }\n        return result;\n\
    \    }\n\n    Mint operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\ntemplate <class Mint>\nusing LucasTheorem = Lucas<Mint>;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/number_theory.hpp\"\
    \n\n\n\n#line 9 \"math/number_theory.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nnamespace internal {\n\ninline long long safe_mod(long long x, long long\
    \ mod) {\n    x %= mod;\n    if (x < 0) x += mod;\n    return x;\n}\n\ninline\
    \ unsigned __int128 floor_sum_unsigned(unsigned long long n, unsigned long long\
    \ mod, unsigned long long a,\n                                            unsigned\
    \ long long b) {\n    unsigned __int128 answer = 0;\n    while (true) {\n    \
    \    if (a >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n        if (b\
    \ >= mod) {\n            answer += static_cast<unsigned __int128>(n) * (b / mod);\n\
    \            b %= mod;\n        }\n\n        const unsigned __int128 y_max = static_cast<unsigned\
    \ __int128>(a) * n + b;\n        if (y_max < mod) break;\n        n = static_cast<unsigned\
    \ long long>(y_max / mod);\n        b = static_cast<unsigned long long>(y_max\
    \ % mod);\n        unsigned long long tmp = mod;\n        mod = a;\n        a\
    \ = tmp;\n    }\n    return answer;\n}\n\n}  // namespace internal\n\ninline long\
    \ long pow_mod(long long x, unsigned long long exponent, long long mod) {\n  \
    \  assert(mod >= 1);\n    if (mod == 1) return 0;\n\n    unsigned long long base\
    \ = static_cast<unsigned long long>(internal::safe_mod(x, mod));\n    unsigned\
    \ long long result = 1;\n    const unsigned long long unsigned_mod = static_cast<unsigned\
    \ long long>(mod);\n    while (exponent > 0) {\n        if (exponent & 1) {\n\
    \            result = static_cast<unsigned long long>(static_cast<unsigned __int128>(result)\
    \ * base % unsigned_mod);\n        }\n        base = static_cast<unsigned long\
    \ long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);\n       \
    \ exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n}\n\n//\
    \ Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n// modulo\
    \ mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long long,\
    \ long long> inv_gcd(long long a, long long mod) {\n    assert(mod >= 1);\n  \
    \  a = internal::safe_mod(a, mod);\n    if (a == 0) return {mod, 0};\n\n    long\
    \ long s = mod;\n    long long t = a;\n    long long m0 = 0;\n    long long m1\
    \ = 1;\n    while (t > 0) {\n        const long long quotient = s / t;\n     \
    \   s -= t * quotient;\n        m0 -= m1 * quotient;\n\n        long long tmp\
    \ = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n\
    \        m1 = tmp;\n    }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n\
    }\n\ninline long long inv_mod(long long x, long long mod) {\n    const auto result\
    \ = inv_gcd(x, mod);\n    assert(result.first == 1);\n    return result.second;\n\
    }\n\n// Returns the smallest nonnegative solution and the least common multiple\
    \ of\n// the moduli. Returns {0, 0} when the system is inconsistent.\ninline std::pair<long\
    \ long, long long> crt(const std::vector<long long>& remainders,\n           \
    \                                const std::vector<long long>& moduli) {\n   \
    \ assert(remainders.size() == moduli.size());\n\n    long long r0 = 0;\n    long\
    \ long m0 = 1;\n    for (int i = 0; i < int(remainders.size()); i++) {\n     \
    \   assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
    \ moduli[i]);\n        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n \
    \           long long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n\
    \            tmp = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n\n        const auto inverse = inv_gcd(m0,\
    \ m1);\n        const long long gcd = inverse.first;\n        const long long\
    \ reduced_modulus = m1 / gcd;\n        const __int128 difference = static_cast<__int128>(r1)\
    \ - r0;\n        if (difference % gcd != 0) return {0, 0};\n\n        __int128\
    \ multiplier = difference / gcd % reduced_modulus;\n        multiplier = multiplier\
    \ * inverse.second % reduced_modulus;\n        if (multiplier < 0) multiplier\
    \ += reduced_modulus;\n\n        const __int128 new_modulus = static_cast<__int128>(m0)\
    \ * reduced_modulus;\n        assert(new_modulus <= std::numeric_limits<long long>::max());\n\
    \        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n\
    \        new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n#line 1 \"math/prime_factorization.hpp\"\n\n\n\n#line 7\
    \ \"math/prime_factorization.hpp\"\n#include <numeric>\n#line 10 \"math/prime_factorization.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t\
    \ multiply_mod(uint64_t a, uint64_t b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned\
    \ __int128>(a) * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t\
    \ exponent, uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0)\
    \ {\n        if (exponent & 1) result = multiply_mod(result, base, mod);\n   \
    \     base = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n\
    \    return result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t\
    \ state = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime : {2ULL,\
    \ 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n\
    \        if (value % prime == 0) return value == prime;\n    }\n\n    uint64_t\
    \ odd_part = value - 1;\n    int power_of_two = 0;\n    while ((odd_part & 1)\
    \ == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n    }\n\n    for\
    \ (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})\
    \ {\n        if (base % value == 0) continue;\n        uint64_t x = internal::power_mod(base\
    \ % value, odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\
    \n        bool composite = true;\n        for (int i = 1; i < power_of_two; i++)\
    \ {\n            x = internal::multiply_mod(x, x, value);\n            if (x ==\
    \ value - 1) {\n                composite = false;\n                break;\n \
    \           }\n        }\n        if (composite) return false;\n    }\n    return\
    \ true;\n}\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value)\
    \ {\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"math/primitive_root.hpp\"\n\n\n\n#line 9 \"math/primitive_root.hpp\"\
    \n\n#line 11 \"math/primitive_root.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ninline bool has_primitive_root(uint64_t mod) {\n    if (mod == 2 || mod\
    \ == 4) return true;\n    if (mod < 2) return false;\n\n    uint64_t odd_part\
    \ = mod;\n    if ((odd_part & 1) == 0) {\n        odd_part >>= 1;\n        if\
    \ ((odd_part & 1) == 0) return false;\n    }\n\n    return prime_factorize(odd_part).size()\
    \ == 1;\n}\n\n// Returns the smallest positive primitive root modulo mod.\n//\
    \ Returns 0 when no primitive root exists.\ninline uint64_t primitive_root(uint64_t\
    \ mod) {\n    assert(mod >= 2);\n    if (mod == 2) return 1;\n    if (!has_primitive_root(mod))\
    \ return 0;\n\n    const uint64_t phi = euler_phi(mod);\n    const std::vector<std::pair<uint64_t,\
    \ int>> factors = prime_factorize(phi);\n    for (uint64_t candidate = 2; candidate\
    \ < mod; candidate++) {\n        if (std::gcd(candidate, mod) != 1) continue;\n\
    \n        bool generator = true;\n        for (const auto& factor : factors) {\n\
    \            if (internal::power_mod(candidate, phi / factor.first, mod) == 1)\
    \ {\n                generator = false;\n                break;\n            }\n\
    \        }\n        if (generator) return candidate;\n    }\n    return 0;\n}\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/prime_sieve.hpp\"\
    \n\n\n\n#line 8 \"math/prime_sieve.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nstruct PrimeSieve {\n   private:\n    int _limit;\n    std::vector<int>\
    \ _min_prime_factor;\n    std::vector<int> _primes;\n\n   public:\n    explicit\
    \ PrimeSieve(int limit = 0) : _limit(0) {\n        assert(limit >= 0);\n     \
    \   _limit = limit;\n        _min_prime_factor.assign(limit + 1, 0);\n       \
    \ if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int value = 2; value\
    \ <= limit; value++) {\n            if (_min_prime_factor[value] == 0) {\n   \
    \             _min_prime_factor[value] = value;\n                _primes.push_back(value);\n\
    \            }\n            for (int prime : _primes) {\n                if (prime\
    \ > _min_prime_factor[value] || value > limit / prime) break;\n              \
    \  _min_prime_factor[value * prime] = prime;\n            }\n        }\n    }\n\
    \n    int limit() const {\n        return _limit;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    const std::vector<int>&\
    \ min_prime_factors() const {\n        return _min_prime_factor;\n    }\n\n  \
    \  bool is_prime(int value) const {\n        assert(0 <= value && value <= _limit);\n\
    \        return value >= 2 && _min_prime_factor[value] == value;\n    }\n\n  \
    \  int min_prime_factor(int value) const {\n        assert(2 <= value && value\
    \ <= _limit);\n        return _min_prime_factor[value];\n    }\n\n    std::vector<std::pair<int,\
    \ int>> factorize(int value) const {\n        assert(1 <= value && value <= _limit);\n\
    \        std::vector<std::pair<int, int>> result;\n        while (value > 1) {\n\
    \            const int prime = _min_prime_factor[value];\n            int exponent\
    \ = 0;\n            do {\n                value /= prime;\n                exponent++;\n\
    \            } while (value > 1 && _min_prime_factor[value] == prime);\n     \
    \       result.emplace_back(prime, exponent);\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> divisors(int value) const {\n        std::vector<int>\
    \ result = {1};\n        for (const auto& factor : factorize(value)) {\n     \
    \       const int current_size = int(result.size());\n            int power =\
    \ 1;\n            for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n                power *= factor.first;\n                for (int i = 0; i\
    \ < current_size; i++) {\n                    result.push_back(result[i] * power);\n\
    \                }\n            }\n        }\n        std::sort(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    int totient(int value)\
    \ const {\n        assert(1 <= value && value <= _limit);\n        int result\
    \ = value;\n        for (const auto& factor : factorize(value)) {\n          \
    \  result = result / factor.first * (factor.first - 1);\n        }\n        return\
    \ result;\n    }\n\n    int mobius(int value) const {\n        assert(1 <= value\
    \ && value <= _limit);\n        int result = 1;\n        for (const auto& factor\
    \ : factorize(value)) {\n            if (factor.second >= 2) return 0;\n     \
    \       result = -result;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ totient_table() const {\n        std::vector<int> result(_limit + 1);\n    \
    \    if (_limit >= 1) result[1] = 1;\n        for (int value = 2; value <= _limit;\
    \ value++) {\n            const int prime = _min_prime_factor[value];\n      \
    \      const int reduced = value / prime;\n            result[value] = reduced\
    \ % prime == 0 ? result[reduced] * prime : result[reduced] * (prime - 1);\n  \
    \      }\n        return result;\n    }\n\n    std::vector<int> mobius_table()\
    \ const {\n        std::vector<int> result(_limit + 1);\n        if (_limit >=\
    \ 1) result[1] = 1;\n        for (int value = 2; value <= _limit; value++) {\n\
    \            const int prime = _min_prime_factor[value];\n            const int\
    \ reduced = value / prime;\n            result[value] = reduced % prime == 0 ?\
    \ 0 : -result[reduced];\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/rational.hpp\"\n\n\
    \n\n#line 5 \"math/rational.hpp\"\n#include <compare>\n#line 10 \"math/rational.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral T =\
    \ long long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\
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
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/stern_brocot_tree.hpp\"\n\n\n\
    \n#line 10 \"math/stern_brocot_tree.hpp\"\n\n#line 12 \"math/stern_brocot_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nenum class SternBrocotDirection {\n\
    \    Left,\n    Right,\n};\n\nstruct SternBrocotRun {\n    SternBrocotDirection\
    \ direction;\n    uint64_t count;\n\n    friend bool operator==(const SternBrocotRun&,\
    \ const SternBrocotRun&) = default;\n};\n\nstruct SternBrocotPath {\n    std::vector<SternBrocotRun>\
    \ runs;\n\n    bool empty() const {\n        return runs.empty();\n    }\n\n \
    \   uint64_t depth() const {\n        uint64_t result = 0;\n        for (const\
    \ SternBrocotRun& run : runs) {\n            assert(run.count <= std::numeric_limits<uint64_t>::max()\
    \ - result);\n            result += run.count;\n        }\n        return result;\n\
    \    }\n\n    void push(SternBrocotDirection direction, uint64_t count = 1) {\n\
    \        if (count == 0) return;\n        if (!runs.empty() && runs.back().direction\
    \ == direction) {\n            assert(count <= std::numeric_limits<uint64_t>::max()\
    \ - runs.back().count);\n            runs.back().count += count;\n        } else\
    \ {\n            runs.push_back(SternBrocotRun{direction, count});\n        }\n\
    \    }\n\n    bool move_up(uint64_t count = 1) {\n        if (depth() < count)\
    \ return false;\n        while (count > 0) {\n            SternBrocotRun& run\
    \ = runs.back();\n            uint64_t removed = run.count < count ? run.count\
    \ : count;\n            run.count -= removed;\n            count -= removed;\n\
    \            if (run.count == 0) runs.pop_back();\n        }\n        return true;\n\
    \    }\n\n    SternBrocotPath ancestor(uint64_t count) const {\n        SternBrocotPath\
    \ result = *this;\n        [[maybe_unused]] bool valid = result.move_up(count);\n\
    \        assert(valid);\n        return result;\n    }\n\n    friend bool operator==(const\
    \ SternBrocotPath&, const SternBrocotPath&) = default;\n};\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct SternBrocotBounds {\n    std::pair<T, T> left;\n    std::pair<T,\
    \ T> right;\n};\n\ntemplate <std::signed_integral T>\nSternBrocotPath stern_brocot_path(T\
    \ numerator, T denominator) {\n    assert(0 < numerator);\n    assert(0 < denominator);\n\
    \    SternBrocotPath result;\n    while (numerator != denominator) {\n       \
    \ if (numerator < denominator) {\n            T count = (denominator - 1) / numerator;\n\
    \            result.push(SternBrocotDirection::Left, uint64_t(count));\n     \
    \       denominator -= count * numerator;\n        } else {\n            T count\
    \ = (numerator - 1) / denominator;\n            result.push(SternBrocotDirection::Right,\
    \ uint64_t(count));\n            numerator -= count * denominator;\n        }\n\
    \    }\n    assert(numerator == 1);\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T = long long>\nRational<T> stern_brocot_decode(const SternBrocotPath& path)\
    \ {\n    using Wide = __int128_t;\n    Wide left_numerator = 0;\n    Wide left_denominator\
    \ = 1;\n    Wide right_numerator = 1;\n    Wide right_denominator = 0;\n    Wide\
    \ numerator = 1;\n    Wide denominator = 1;\n    [[maybe_unused]] const Wide maximum\
    \ = std::numeric_limits<T>::max();\n    for (const SternBrocotRun& run : path.runs)\
    \ {\n        assert(run.count > 0);\n        assert(Wide(run.count) <= maximum);\n\
    \        Wide count = run.count;\n        if (run.direction == SternBrocotDirection::Left)\
    \ {\n            right_numerator = numerator + (count - 1) * left_numerator;\n\
    \            right_denominator = denominator + (count - 1) * left_denominator;\n\
    \            numerator += count * left_numerator;\n            denominator +=\
    \ count * left_denominator;\n        } else {\n            left_numerator = numerator\
    \ + (count - 1) * right_numerator;\n            left_denominator = denominator\
    \ + (count - 1) * right_denominator;\n            numerator += count * right_numerator;\n\
    \            denominator += count * right_denominator;\n        }\n        assert(numerator\
    \ <= maximum);\n        assert(denominator <= maximum);\n        assert(left_numerator\
    \ <= maximum);\n        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    return\
    \ Rational<T>(T(numerator), T(denominator));\n}\n\ntemplate <std::signed_integral\
    \ T>\nuint64_t stern_brocot_depth(T numerator, T denominator) {\n    return stern_brocot_path(numerator,\
    \ denominator).depth();\n}\n\ninline SternBrocotPath stern_brocot_lca_path(\n\
    \    const SternBrocotPath& first,\n    const SternBrocotPath& second\n) {\n \
    \   SternBrocotPath result;\n    int limit = int(first.runs.size() < second.runs.size()\
    \ ? first.runs.size() : second.runs.size());\n    for (int i = 0; i < limit; i++)\
    \ {\n        if (first.runs[i].direction != second.runs[i].direction) break;\n\
    \        uint64_t common =\n            first.runs[i].count < second.runs[i].count\n\
    \                ? first.runs[i].count\n                : second.runs[i].count;\n\
    \        result.push(first.runs[i].direction, common);\n        if (first.runs[i].count\
    \ != second.runs[i].count) break;\n    }\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T>\nRational<T> stern_brocot_lca(\n    T first_numerator,\n    T first_denominator,\n\
    \    T second_numerator,\n    T second_denominator\n) {\n    SternBrocotPath path\
    \ = stern_brocot_lca_path(\n        stern_brocot_path(first_numerator, first_denominator),\n\
    \        stern_brocot_path(second_numerator, second_denominator)\n    );\n   \
    \ return stern_brocot_decode<T>(path);\n}\n\ntemplate <std::signed_integral T>\n\
    Rational<T> stern_brocot_ancestor(T numerator, T denominator, uint64_t up) {\n\
    \    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n    [[maybe_unused]]\
    \ bool valid = path.move_up(up);\n    assert(valid);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_parent(T numerator,\
    \ T denominator) {\n    return stern_brocot_ancestor(numerator, denominator, 1);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_move(\n    T\
    \ numerator,\n    T denominator,\n    SternBrocotDirection direction,\n    uint64_t\
    \ count = 1\n) {\n    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n\
    \    path.push(direction, count);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T = long long>\nSternBrocotBounds<T> stern_brocot_bounds(const\
    \ SternBrocotPath& path) {\n    using Wide = __int128_t;\n    Wide left_numerator\
    \ = 0;\n    Wide left_denominator = 1;\n    Wide right_numerator = 1;\n    Wide\
    \ right_denominator = 0;\n    Wide numerator = 1;\n    Wide denominator = 1;\n\
    \    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();\n\n\
    \    for (const SternBrocotRun& run : path.runs) {\n        assert(run.count >\
    \ 0);\n        assert(Wide(run.count) <= maximum);\n        Wide count = run.count;\n\
    \        if (run.direction == SternBrocotDirection::Left) {\n            right_numerator\
    \ = numerator + (count - 1) * left_numerator;\n            right_denominator =\
    \ denominator + (count - 1) * left_denominator;\n            numerator += count\
    \ * left_numerator;\n            denominator += count * left_denominator;\n  \
    \      } else {\n            left_numerator = numerator + (count - 1) * right_numerator;\n\
    \            left_denominator = denominator + (count - 1) * right_denominator;\n\
    \            numerator += count * right_numerator;\n            denominator +=\
    \ count * right_denominator;\n        }\n        assert(numerator <= maximum);\n\
    \        assert(denominator <= maximum);\n        assert(left_numerator <= maximum);\n\
    \        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    SternBrocotBounds<T>\
    \ result;\n    result.left = {T(left_numerator), T(left_denominator)};\n    result.right\
    \ = {T(right_numerator), T(right_denominator)};\n    return result;\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/tetration.hpp\"\n\n\
    \n\n#line 9 \"math/tetration.hpp\"\n\n#line 11 \"math/tetration.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace tetration_detail {\n\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nuint64_t to_uint64(T\
    \ value) {\n    if constexpr (std::signed_integral<T>) {\n        assert(value\
    \ >= 0);\n    }\n    return static_cast<uint64_t>(value);\n}\n\ninline uint64_t\
    \ multiply_mod(uint64_t first, uint64_t second, uint64_t mod) {\n    return static_cast<uint64_t>(\n\
    \        static_cast<__uint128_t>(first) * second % mod\n    );\n}\n\ninline uint64_t\
    \ pow_mod(uint64_t base, __uint128_t exponent, uint64_t mod) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    base %= mod;\n    uint64_t result =\
    \ 1 % mod;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result\
    \ = multiply_mod(result, base, mod);\n        base = multiply_mod(base, base,\
    \ mod);\n        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t\
    \ pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {\n    if (limit\
    \ == 0) return 0;\n    __uint128_t result = 1;\n    for (uint64_t i = 0; i < exponent;\
    \ i++) {\n        result *= base;\n        if (result >= limit) return limit;\n\
    \    }\n    return static_cast<uint64_t>(result);\n}\n\ninline uint64_t exponent_threshold(uint64_t\
    \ base, uint64_t limit) {\n    assert(base >= 2);\n    if (limit <= 1) return\
    \ 0;\n\n    uint64_t exponent = 0;\n    uint64_t value = 1;\n    while (value\
    \ < limit) {\n        exponent++;\n        if (value > limit / base) return exponent;\n\
    \        value *= base;\n    }\n    return exponent;\n}\n\ninline uint64_t tetration_bounded_unsigned(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return limit < 1 ? limit : 1;\n    if (height == 1) return\
    \ base < limit ? base : limit;\n\n    if (base == 0) {\n        const uint64_t\
    \ value = (height & 1) == 0 ? 1 : 0;\n        return value < limit ? value : limit;\n\
    \    }\n    if (base == 1) return limit < 1 ? limit : 1;\n\n    const uint64_t\
    \ threshold = exponent_threshold(base, limit);\n    const uint64_t exponent =\
    \ tetration_bounded_unsigned(base, height - 1, threshold);\n    if (exponent >=\
    \ threshold) return limit;\n    return pow_bounded(base, exponent, limit);\n}\n\
    \ninline uint64_t tetration_mod_unsigned(uint64_t base, uint64_t height, uint64_t\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    if (height ==\
    \ 0) return 1 % mod;\n    if (height == 1) return base % mod;\n    if (base ==\
    \ 0) return (height & 1) == 0 ? 1 % mod : 0;\n    if (base == 1) return 1 % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = tetration_mod_unsigned(base,\
    \ height - 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (tetration_bounded_unsigned(base,\
    \ height - 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(base,\
    \ exponent, mod);\n}\n\ninline uint64_t power_tower_bounded_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t limit\n) {\n   \
    \ if (limit == 0) return 0;\n    if (index == int(bases.size())) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t base = bases[index];\n    if (index +\
    \ 1 == int(bases.size())) return base < limit ? base : limit;\n\n    if (base\
    \ == 0) {\n        const uint64_t exponent = power_tower_bounded_unsigned(bases,\
    \ index + 1, 1);\n        const uint64_t value = exponent == 0 ? 1 : 0;\n    \
    \    return value < limit ? value : limit;\n    }\n    if (base == 1) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t threshold = exponent_threshold(base,\
    \ limit);\n    const uint64_t exponent = power_tower_bounded_unsigned(bases, index\
    \ + 1, threshold);\n    if (exponent >= threshold) return limit;\n    return pow_bounded(base,\
    \ exponent, limit);\n}\n\ninline uint64_t power_tower_mod_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    if (index == int(bases.size())) return\
    \ 1 % mod;\n    if (index + 1 == int(bases.size())) return bases[index] % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = power_tower_mod_unsigned(bases,\
    \ index + 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (power_tower_bounded_unsigned(bases,\
    \ index + 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(bases[index],\
    \ exponent, mod);\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstd::vector<uint64_t> normalize_bases(const std::vector<T>& bases) {\n\
    \    std::vector<uint64_t> result;\n    result.reserve(bases.size());\n    for\
    \ (T base : bases) result.push_back(to_uint64(base));\n    return result;\n}\n\
    \n}  // namespace tetration_detail\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_mod(T base, uint64_t height, uint64_t mod) {\n  \
    \  assert(mod >= 1);\n    return tetration_detail::tetration_mod_unsigned(\n \
    \       tetration_detail::to_uint64(base),\n        height,\n        mod\n   \
    \ );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_bounded(T base, uint64_t height, uint64_t limit)\
    \ {\n    return tetration_detail::tetration_bounded_unsigned(\n        tetration_detail::to_uint64(base),\n\
    \        height,\n        limit\n    );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t power_tower_mod(const std::vector<T>& bases, uint64_t mod)\
    \ {\n    assert(mod >= 1);\n    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_mod_unsigned(normalized, 0, mod);\n\
    }\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    uint64_t power_tower_bounded(const std::vector<T>& bases, uint64_t limit) {\n\
    \    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_bounded_unsigned(normalized, 0, limit);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/two_square_sum.hpp\"\
    \n\n\n\n#line 9 \"math/two_square_sum.hpp\"\n\n#line 12 \"math/two_square_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace two_square_sum_detail {\n\
    \nstruct GaussianInteger {\n    __int128_t real;\n    __int128_t imaginary;\n\
    };\n\ninline GaussianInteger multiply(GaussianInteger first, GaussianInteger second)\
    \ {\n    return GaussianInteger{first.real * second.real - first.imaginary * second.imaginary,\n\
    \                           first.real * second.imaginary + first.imaginary *\
    \ second.real};\n}\n\ninline GaussianInteger power(GaussianInteger base, int exponent)\
    \ {\n    GaussianInteger result{1, 0};\n    while (exponent > 0) {\n        if\
    \ ((exponent & 1) != 0) result = multiply(result, base);\n        exponent >>=\
    \ 1;\n        if (exponent != 0) base = multiply(base, base);\n    }\n    return\
    \ result;\n}\n\ninline uint64_t absolute_value(__int128_t value) {\n    return\
    \ static_cast<uint64_t>(value < 0 ? -value : value);\n}\n\ninline uint64_t pow_uint64(uint64_t\
    \ base, int exponent) {\n    uint64_t result = 1;\n    while (exponent > 0) {\n\
    \        if ((exponent & 1) != 0) result *= base;\n        exponent >>= 1;\n \
    \       if (exponent != 0) base *= base;\n    }\n    return result;\n}\n\ninline\
    \ GaussianInteger prime_one_mod_four_representation(uint64_t prime) {\n    assert(prime\
    \ % 4 == 1);\n    uint64_t non_residue = 2;\n    while (internal::power_mod(non_residue,\
    \ (prime - 1) / 2, prime) != prime - 1) {\n        non_residue++;\n    }\n\n \
    \   uint64_t root = internal::power_mod(non_residue, (prime - 1) / 4, prime);\n\
    \    uint64_t previous = prime;\n    uint64_t current = root;\n    while (static_cast<__uint128_t>(current)\
    \ * current > prime) {\n        uint64_t next = previous % current;\n        previous\
    \ = current;\n        current = next;\n    }\n\n    const uint64_t real = current;\n\
    \    const uint64_t remaining = prime - real * real;\n    const uint64_t imaginary\
    \ = isqrt(remaining);\n    assert(imaginary * imaginary == remaining);\n    return\
    \ GaussianInteger{static_cast<__int128_t>(real), static_cast<__int128_t>(imaginary)};\n\
    }\n\ninline std::vector<GaussianInteger> prime_power_choices(GaussianInteger factor,\
    \ int exponent) {\n    GaussianInteger conjugate{factor.real, -factor.imaginary};\n\
    \n    std::vector<GaussianInteger> positive_powers(exponent + 1);\n    std::vector<GaussianInteger>\
    \ negative_powers(exponent + 1);\n    positive_powers[0] = GaussianInteger{1,\
    \ 0};\n    negative_powers[0] = GaussianInteger{1, 0};\n    for (int i = 0; i\
    \ < exponent; i++) {\n        positive_powers[i + 1] = multiply(positive_powers[i],\
    \ factor);\n        negative_powers[i + 1] = multiply(negative_powers[i], conjugate);\n\
    \    }\n\n    std::vector<GaussianInteger> result;\n    result.reserve(exponent\
    \ + 1);\n    for (int take_positive = 0; take_positive <= exponent; take_positive++)\
    \ {\n        result.push_back(multiply(positive_powers[take_positive], negative_powers[exponent\
    \ - take_positive]));\n    }\n    return result;\n}\n\ninline void add_nonnegative_pairs(std::vector<std::pair<uint64_t,\
    \ uint64_t>>& result, GaussianInteger value,\n                               \
    \   uint64_t scale) {\n    const uint64_t first = absolute_value(value.real) *\
    \ scale;\n    const uint64_t second = absolute_value(value.imaginary) * scale;\n\
    \    result.emplace_back(first, second);\n    result.emplace_back(second, first);\n\
    }\n\n}  // namespace two_square_sum_detail\n\ninline std::vector<std::pair<uint64_t,\
    \ uint64_t>> two_square_sum(uint64_t value) {\n    using two_square_sum_detail::GaussianInteger;\n\
    \n    if (value == 0) return std::vector<std::pair<uint64_t, uint64_t>>{std::pair<uint64_t,\
    \ uint64_t>(0, 0)};\n\n    uint64_t real_scale = 1;\n    std::vector<std::vector<GaussianInteger>>\
    \ choices_by_prime;\n    for (const auto& factor : prime_factorize(value)) {\n\
    \        const uint64_t prime = factor.first;\n        const int exponent = factor.second;\n\
    \n        if (prime % 4 == 3) {\n            if ((exponent & 1) != 0) return {};\n\
    \            real_scale *= two_square_sum_detail::pow_uint64(prime, exponent /\
    \ 2);\n            continue;\n        }\n\n        GaussianInteger gaussian_factor;\n\
    \        if (prime == 2) {\n            gaussian_factor = GaussianInteger{1, 1};\n\
    \        } else {\n            gaussian_factor = two_square_sum_detail::prime_one_mod_four_representation(prime);\n\
    \        }\n        choices_by_prime.push_back(two_square_sum_detail::prime_power_choices(gaussian_factor,\
    \ exponent));\n    }\n\n    std::vector<GaussianInteger> values;\n    values.push_back(GaussianInteger{1,\
    \ 0});\n    for (const std::vector<GaussianInteger>& choices : choices_by_prime)\
    \ {\n        std::vector<GaussianInteger> next;\n        next.reserve(values.size()\
    \ * choices.size());\n        for (GaussianInteger value_so_far : values) {\n\
    \            for (GaussianInteger choice : choices) {\n                next.push_back(two_square_sum_detail::multiply(value_so_far,\
    \ choice));\n            }\n        }\n        values.swap(next);\n    }\n\n \
    \   std::vector<std::pair<uint64_t, uint64_t>> result;\n    result.reserve(values.size()\
    \ * 2);\n    for (GaussianInteger gaussian : values) {\n        two_square_sum_detail::add_nonnegative_pairs(result,\
    \ gaussian, real_scale);\n    }\n\n    std::sort(result.begin(), result.end());\n\
    \    result.erase(std::unique(result.begin(), result.end()), result.end());\n\
    \    return result;\n}\n\ninline std::vector<std::pair<uint64_t, uint64_t>> represent_as_two_square_sum(uint64_t\
    \ value) {\n    return two_square_sum(value);\n}\n\ninline bool is_two_square_sum(uint64_t\
    \ value) {\n    if (value == 0) return true;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.first % 4 == 3 && (factor.second & 1) != 0) return false;\n\
    \    }\n    return true;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 20 \"math/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_MATH_ALL_HPP

    #define M1UNE_MATH_ALL_HPP 1


    #include "bitwise_convolution.hpp"

    #include "bit_ceil.hpp"

    #include "combinatorics.hpp"

    #include "combinatorial_sequences.hpp"

    #include "integer_arithmetic.hpp"

    #include "lucas.hpp"

    #include "modint.hpp"

    #include "number_theory.hpp"

    #include "prime_factorization.hpp"

    #include "primitive_root.hpp"

    #include "prime_sieve.hpp"

    #include "rational.hpp"

    #include "stern_brocot_tree.hpp"

    #include "tetration.hpp"

    #include "two_square_sum.hpp"

    #include "zeta_mobius_transform.hpp"


    #endif  // M1UNE_MATH_ALL_HPP

    '
  dependsOn:
  - math/bitwise_convolution.hpp
  - math/zeta_mobius_transform.hpp
  - math/bit_ceil.hpp
  - math/combinatorics.hpp
  - math/combinatorial_sequences.hpp
  - fps/formal_power_series.hpp
  - fps/convolution.hpp
  - math/modint.hpp
  - math/integer_arithmetic.hpp
  - math/lucas.hpp
  - math/modint.hpp
  - math/number_theory.hpp
  - math/prime_factorization.hpp
  - math/primitive_root.hpp
  - math/prime_sieve.hpp
  - math/rational.hpp
  - math/stern_brocot_tree.hpp
  - math/tetration.hpp
  - math/two_square_sum.hpp
  isVerificationFile: false
  path: math/all.hpp
  requiredBy: []
  timestamp: '2026-06-24 15:25:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
documentation_of: math/all.hpp
layout: document
title: Math All
---

## Overview

`math/all.hpp` includes every general math header in this directory.

## Choosing a Header

You usually do not need to include this entire bundle:

* Use `modint.hpp` for arithmetic modulo a fixed number such as `998244353`.
* Use `bitwise_convolution.hpp` for OR, AND, or XOR convolution over mask
  indices.
* Use `zeta_mobius_transform.hpp` for subset, superset, divisor, and multiple
  transforms.
* Use `combinatorics.hpp` for many factorial, combination, or permutation
  queries under a prime modulus.
* Use `lucas.hpp` for binomial coefficients with huge arguments modulo a small
  prime.
* Use `combinatorial_sequences.hpp` for Catalan, Bernoulli, Bell, Stirling,
  partition, or derangement numbers.
* Use `prime_sieve.hpp` when all queried integers are at most a manageable
  limit, usually a few million or tens of millions.
* Use `prime_factorization.hpp` for isolated 64-bit integers that are too large
  for a sieve.
* Use `primitive_root.hpp` to find a generator of the multiplicative group
  modulo an integer when one exists.
* Use `two_square_sum.hpp` to enumerate non-negative pairs `(a, b)` satisfying
  `n = a * a + b * b`.
* Use `number_theory.hpp` for modular inverses, simultaneous remainder
  constraints, and sums involving floor division.
* Use `integer_arithmetic.hpp` for exact integer square roots and powers.
* Use `tetration.hpp` for modular tetration and arbitrary power towers.
* Use `rational.hpp` for normalized exact fractions.
* Use `stern_brocot_tree.hpp` for positive rational tree paths, ancestors, and
  LCA operations.

`math/all.hpp` is convenient during a contest when compile time and including a
few unused headers do not matter.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/bitwise_convolution.hpp` | OR, AND, XOR convolutions and the Walsh-Hadamard transform. |
| `math/bit_ceil.hpp` | Smallest power of two at least a given value. |
| `math/integer_arithmetic.hpp` | Exact integer square roots and overflow-aware powers. |
| `math/lucas.hpp` | Lucas's theorem for huge binomial arguments modulo a small prime. |
| `math/modint.hpp` | Static modular integer type. |
| `math/combinatorics.hpp` | Factorials, binomial coefficients, permutations, and multiset counts. |
| `math/combinatorial_sequences.hpp` | Fast standard counting sequences and special numbers. |
| `math/number_theory.hpp` | Modular power and inverse, CRT, and floor sum. |
| `math/prime_sieve.hpp` | Linear sieve with smallest prime factors. |
| `math/prime_factorization.hpp` | Deterministic 64-bit primality test and Pollard-Rho factorization. |
| `math/primitive_root.hpp` | Smallest primitive root modulo an integer, when one exists. |
| `math/two_square_sum.hpp` | Enumerates representations as a sum of two non-negative squares. |
| `math/tetration.hpp` | Modular tetration, arbitrary power towers, and bounded tower comparison. |
| `math/rational.hpp` | Exact normalized rational arithmetic over signed integers. |
| `math/stern_brocot_tree.hpp` | Compressed Stern-Brocot paths and tree navigation. |
| `math/zeta_mobius_transform.hpp` | Subset, superset, divisor, and multiple zeta/Mobius transforms. |
