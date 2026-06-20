---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
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
  bundledCode: "#line 1 \"math/all.hpp\"\n\n\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T\
    \ n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n\
    \    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1\
    \ \"math/combinatorics.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\nstruct\
    \ Combinatorics {\n   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint>\
    \ _inverse_factorial;\n\n   public:\n    explicit Combinatorics(int maximum =\
    \ 0)\n        : _factorial(1, Mint(1)), _inverse_factorial(1, Mint(1)) {\n   \
    \     ensure(maximum);\n    }\n\n    int maximum() const {\n        return int(_factorial.size())\
    \ - 1;\n    }\n\n    void ensure(int maximum) {\n        assert(maximum >= 0);\n\
    \        assert(static_cast<uint64_t>(maximum) < Mint::mod());\n        if (maximum\
    \ <= this->maximum()) return;\n\n        const int old_maximum = this->maximum();\n\
    \        _factorial.resize(maximum + 1);\n        _inverse_factorial.resize(maximum\
    \ + 1);\n        for (int i = old_maximum + 1; i <= maximum; i++) {\n        \
    \    _factorial[i] = _factorial[i - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum]\
    \ = _factorial[maximum].inv();\n        for (int i = maximum; i > old_maximum;\
    \ i--) {\n            _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);\n\
    \        }\n    }\n\n    Mint factorial(int n) const {\n        assert(0 <= n\
    \ && n <= maximum());\n        return _factorial[n];\n    }\n\n    Mint inverse_factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _inverse_factorial[n];\n\
    \    }\n\n    Mint inverse(int n) const {\n        assert(1 <= n && n <= maximum());\n\
    \        return _factorial[n - 1] * _inverse_factorial[n];\n    }\n\n    Mint\
    \ binom(int n, int k) const {\n        if (k < 0 || k > n) return Mint(0);\n \
    \       assert(n <= maximum());\n        return _factorial[n] * _inverse_factorial[k]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint perm(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[n - k];\n    }\n\n    Mint\
    \ multiset(int types, int count) const {\n        if (types < 0 || count < 0)\
    \ return Mint(0);\n        if (types == 0) return Mint(count == 0);\n        const\
    \ long long total = static_cast<long long>(types) + count - 1;\n        assert(total\
    \ <= maximum());\n        return binom(static_cast<int>(total), count);\n    }\n\
    };\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt\
    \ {\n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t\
    \ mod() {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    constexpr ModInt(int\
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
    \ m1une\n\n\n#line 1 \"math/number_theory.hpp\"\n\n\n\n#line 6 \"math/number_theory.hpp\"\
    \n#include <limits>\n#line 9 \"math/number_theory.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace internal {\n\ninline long long safe_mod(long long\
    \ x, long long mod) {\n    x %= mod;\n    if (x < 0) x += mod;\n    return x;\n\
    }\n\ninline unsigned __int128 floor_sum_unsigned(\n    unsigned long long n,\n\
    \    unsigned long long mod,\n    unsigned long long a,\n    unsigned long long\
    \ b\n) {\n    unsigned __int128 answer = 0;\n    while (true) {\n        if (a\
    \ >= mod) {\n            answer += static_cast<unsigned __int128>(n) * (n - 1)\
    \ / 2 * (a / mod);\n            a %= mod;\n        }\n        if (b >= mod) {\n\
    \            answer += static_cast<unsigned __int128>(n) * (b / mod);\n      \
    \      b %= mod;\n        }\n\n        const unsigned __int128 y_max = static_cast<unsigned\
    \ __int128>(a) * n + b;\n        if (y_max < mod) break;\n        n = static_cast<unsigned\
    \ long long>(y_max / mod);\n        b = static_cast<unsigned long long>(y_max\
    \ % mod);\n        unsigned long long tmp = mod;\n        mod = a;\n        a\
    \ = tmp;\n    }\n    return answer;\n}\n\n}  // namespace internal\n\ninline long\
    \ long pow_mod(long long x, unsigned long long exponent, long long mod) {\n  \
    \  assert(mod >= 1);\n    if (mod == 1) return 0;\n\n    unsigned long long base\
    \ = static_cast<unsigned long long>(internal::safe_mod(x, mod));\n    unsigned\
    \ long long result = 1;\n    const unsigned long long unsigned_mod = static_cast<unsigned\
    \ long long>(mod);\n    while (exponent > 0) {\n        if (exponent & 1) {\n\
    \            result = static_cast<unsigned long long>(\n                static_cast<unsigned\
    \ __int128>(result) * base % unsigned_mod\n            );\n        }\n       \
    \ base = static_cast<unsigned long long>(\n            static_cast<unsigned __int128>(base)\
    \ * base % unsigned_mod\n        );\n        exponent >>= 1;\n    }\n    return\
    \ static_cast<long long>(result);\n}\n\n// Returns gcd(a, mod) and x such that\
    \ a * x is congruent to gcd(a, mod)\n// modulo mod. The returned x is in [0, mod\
    \ / gcd(a, mod)).\ninline std::pair<long long, long long> inv_gcd(long long a,\
    \ long long mod) {\n    assert(mod >= 1);\n    a = internal::safe_mod(a, mod);\n\
    \    if (a == 0) return {mod, 0};\n\n    long long s = mod;\n    long long t =\
    \ a;\n    long long m0 = 0;\n    long long m1 = 1;\n    while (t > 0) {\n    \
    \    const long long quotient = s / t;\n        s -= t * quotient;\n        m0\
    \ -= m1 * quotient;\n\n        long long tmp = s;\n        s = t;\n        t =\
    \ tmp;\n        tmp = m0;\n        m0 = m1;\n        m1 = tmp;\n    }\n    if\
    \ (m0 < 0) m0 += mod / s;\n    return {s, m0};\n}\n\ninline long long inv_mod(long\
    \ long x, long long mod) {\n    const auto result = inv_gcd(x, mod);\n    assert(result.first\
    \ == 1);\n    return result.second;\n}\n\n// Returns the smallest nonnegative\
    \ solution and the least common multiple of\n// the moduli. Returns {0, 0} when\
    \ the system is inconsistent.\ninline std::pair<long long, long long> crt(\n \
    \   const std::vector<long long>& remainders,\n    const std::vector<long long>&\
    \ moduli\n) {\n    assert(remainders.size() == moduli.size());\n\n    long long\
    \ r0 = 0;\n    long long m0 = 1;\n    for (int i = 0; i < int(remainders.size());\
    \ i++) {\n        assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
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
    \ answer =\n        (static_cast<__int128>(a) - normalized_a) / mod * n * (n -\
    \ 1) / 2;\n    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n\
    \    answer += internal::floor_sum_unsigned(\n        static_cast<unsigned long\
    \ long>(n),\n        static_cast<unsigned long long>(mod),\n        static_cast<unsigned\
    \ long long>(normalized_a),\n        static_cast<unsigned long long>(normalized_b)\n\
    \    );\n\n    assert(answer >= std::numeric_limits<long long>::min());\n    assert(answer\
    \ <= std::numeric_limits<long long>::max());\n    return static_cast<long long>(answer);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/prime_factorization.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"math/prime_factorization.hpp\"\n#include\
    \ <numeric>\n#line 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t\
    \ a, uint64_t b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned\
    \ __int128>(a) * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t\
    \ exponent, uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0)\
    \ {\n        if (exponent & 1) result = multiply_mod(result, base, mod);\n   \
    \     base = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n\
    \    return result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t\
    \ state = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime :\n    \
    \     {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL,\n   \
    \       31ULL, 37ULL}) {\n        if (value % prime == 0) return value == prime;\n\
    \    }\n\n    uint64_t odd_part = value - 1;\n    int power_of_two = 0;\n    while\
    \ ((odd_part & 1) == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n\
    \    }\n\n    for (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL,\
    \ 9780504ULL, 1795265022ULL}) {\n        if (base % value == 0) continue;\n  \
    \      uint64_t x = internal::power_mod(base % value, odd_part, value);\n    \
    \    if (x == 1 || x == value - 1) continue;\n\n        bool composite = true;\n\
    \        for (int i = 1; i < power_of_two; i++) {\n            x = internal::multiply_mod(x,\
    \ x, value);\n            if (x == value - 1) {\n                composite = false;\n\
    \                break;\n            }\n        }\n        if (composite) return\
    \ false;\n    }\n    return true;\n}\n\nnamespace internal {\n\ninline uint64_t\
    \ pollard_rho(uint64_t value) {\n    for (uint64_t prime :\n         {2ULL, 3ULL,\
    \ 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL,\n          31ULL, 37ULL})\
    \ {\n        if (value % prime == 0) return prime;\n    }\n\n    while (true)\
    \ {\n        const uint64_t constant = pollard_random() % (value - 1) + 1;\n \
    \       uint64_t y = pollard_random() % (value - 1) + 1;\n        uint64_t x =\
    \ 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd = 1;\n        uint64_t\
    \ segment_length = 1;\n\n        auto advance = [&](uint64_t current) {\n    \
    \        return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) +\n                 constant)\
    \ %\n                value\n            );\n        };\n\n        while (gcd ==\
    \ 1) {\n            x = y;\n            for (uint64_t i = 0; i < segment_length;\
    \ i++) y = advance(y);\n\n            for (uint64_t offset = 0; offset < segment_length\
    \ && gcd == 1;\n                 offset += 128) {\n                saved_y = y;\n\
    \                uint64_t product = 1;\n                const uint64_t block =\
    \ std::min<uint64_t>(128, segment_length - offset);\n                for (uint64_t\
    \ i = 0; i < block; i++) {\n                    y = advance(y);\n            \
    \        const uint64_t difference = x > y ? x - y : y - x;\n                \
    \    product = multiply_mod(product, difference, value);\n                }\n\
    \                gcd = std::gcd(product, value);\n            }\n            segment_length\
    \ <<= 1;\n        }\n\n        if (gcd == value) {\n            do {\n       \
    \         saved_y = advance(saved_y);\n                const uint64_t difference\
    \ = x > saved_y ? x - saved_y : saved_y - x;\n                gcd = std::gcd(difference,\
    \ value);\n            } while (gcd == 1);\n        }\n        if (gcd != value)\
    \ return gcd;\n    }\n}\n\ninline void factor_recursively(uint64_t value, std::vector<uint64_t>&\
    \ factors) {\n    if (value == 1) return;\n    if (is_prime(value)) {\n      \
    \  factors.push_back(value);\n        return;\n    }\n    const uint64_t divisor\
    \ = pollard_rho(value);\n    factor_recursively(divisor, factors);\n    factor_recursively(value\
    \ / divisor, factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t>\
    \ prime_factors(uint64_t value) {\n    assert(value >= 1);\n    std::vector<uint64_t>\
    \ result;\n    internal::factor_recursively(value, result);\n    std::sort(result.begin(),\
    \ result.end());\n    return result;\n}\n\ninline std::vector<std::pair<uint64_t,\
    \ int>> prime_factorize(uint64_t value) {\n    std::vector<uint64_t> factors =\
    \ prime_factors(value);\n    std::vector<std::pair<uint64_t, int>> result;\n \
    \   for (uint64_t prime : factors) {\n        if (result.empty() || result.back().first\
    \ != prime) {\n            result.emplace_back(prime, 1);\n        } else {\n\
    \            result.back().second++;\n        }\n    }\n    return result;\n}\n\
    \ninline std::vector<uint64_t> divisors(uint64_t value) {\n    std::vector<uint64_t>\
    \ result = {1};\n    for (const auto& factor : prime_factorize(value)) {\n   \
    \     const int current_size = int(result.size());\n        uint64_t power = 1;\n\
    \        for (int exponent = 1; exponent <= factor.second; exponent++) {\n   \
    \         power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"math/prime_sieve.hpp\"\n\n\n\n#line 8 \"math/prime_sieve.hpp\"\n\n\
    namespace m1une {\nnamespace math {\n\nstruct PrimeSieve {\n   private:\n    int\
    \ _limit;\n    std::vector<int> _min_prime_factor;\n    std::vector<int> _primes;\n\
    \n   public:\n    explicit PrimeSieve(int limit = 0) : _limit(0) {\n        assert(limit\
    \ >= 0);\n        _limit = limit;\n        _min_prime_factor.assign(limit + 1,\
    \ 0);\n        if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int value\
    \ = 2; value <= limit; value++) {\n            if (_min_prime_factor[value] ==\
    \ 0) {\n                _min_prime_factor[value] = value;\n                _primes.push_back(value);\n\
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
    \ % prime == 0\n                                ? result[reduced] * prime\n  \
    \                              : result[reduced] * (prime - 1);\n        }\n \
    \       return result;\n    }\n\n    std::vector<int> mobius_table() const {\n\
    \        std::vector<int> result(_limit + 1);\n        if (_limit >= 1) result[1]\
    \ = 1;\n        for (int value = 2; value <= _limit; value++) {\n            const\
    \ int prime = _min_prime_factor[value];\n            const int reduced = value\
    \ / prime;\n            result[value] = reduced % prime == 0 ? 0 : -result[reduced];\n\
    \        }\n        return result;\n    }\n};\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 10 \"math/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_MATH_ALL_HPP

    #define M1UNE_MATH_ALL_HPP 1


    #include "math/bit_ceil.hpp"

    #include "math/combinatorics.hpp"

    #include "math/modint.hpp"

    #include "math/number_theory.hpp"

    #include "math/prime_factorization.hpp"

    #include "math/prime_sieve.hpp"


    #endif  // M1UNE_MATH_ALL_HPP

    '
  dependsOn:
  - math/bit_ceil.hpp
  - math/combinatorics.hpp
  - math/modint.hpp
  - math/number_theory.hpp
  - math/prime_factorization.hpp
  - math/prime_sieve.hpp
  isVerificationFile: false
  path: math/all.hpp
  requiredBy: []
  timestamp: '2026-06-20 09:06:39+09:00'
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
* Use `combinatorics.hpp` for many factorial, combination, or permutation
  queries under a prime modulus.
* Use `prime_sieve.hpp` when all queried integers are at most a manageable
  limit, usually a few million or tens of millions.
* Use `prime_factorization.hpp` for isolated 64-bit integers that are too large
  for a sieve.
* Use `number_theory.hpp` for modular inverses, simultaneous remainder
  constraints, and sums involving floor division.

`math/all.hpp` is convenient during a contest when compile time and including a
few unused headers do not matter.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/bit_ceil.hpp` | Smallest power of two at least a given value. |
| `math/modint.hpp` | Static modular integer type. |
| `math/combinatorics.hpp` | Factorials, binomial coefficients, permutations, and multiset counts. |
| `math/number_theory.hpp` | Modular power and inverse, CRT, and floor sum. |
| `math/prime_sieve.hpp` | Linear sieve with smallest prime factors. |
| `math/prime_factorization.hpp` | Deterministic 64-bit primality test and Pollard-Rho factorization. |
