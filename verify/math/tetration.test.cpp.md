---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':question:'
    path: math/tetration.hpp
    title: Tetration
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
  bundledCode: "#line 1 \"verify/math/tetration.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/tetration.hpp\"\n\n\n\n#include <cassert>\n#include <concepts>\n\
    #include <cstdint>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"math/prime_factorization.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"math/prime_factorization.hpp\"\n#include\
    \ <numeric>\n#include <utility>\n#line 10 \"math/prime_factorization.hpp\"\n\n\
    namespace m1une {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t\
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
    \n#line 11 \"math/tetration.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ tetration_detail {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t to_uint64(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ {\n        assert(value >= 0);\n    }\n    return static_cast<uint64_t>(value);\n\
    }\n\ninline uint64_t multiply_mod(uint64_t first, uint64_t second, uint64_t mod)\
    \ {\n    return static_cast<uint64_t>(\n        static_cast<__uint128_t>(first)\
    \ * second % mod\n    );\n}\n\ninline uint64_t pow_mod(uint64_t base, __uint128_t\
    \ exponent, uint64_t mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n\
    \    base %= mod;\n    uint64_t result = 1 % mod;\n    while (exponent > 0) {\n\
    \        if ((exponent & 1) != 0) result = multiply_mod(result, base, mod);\n\
    \        base = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n\
    \    return result;\n}\n\ninline uint64_t pow_bounded(uint64_t base, uint64_t\
    \ exponent, uint64_t limit) {\n    if (limit == 0) return 0;\n    __uint128_t\
    \ result = 1;\n    for (uint64_t i = 0; i < exponent; i++) {\n        result *=\
    \ base;\n        if (result >= limit) return limit;\n    }\n    return static_cast<uint64_t>(result);\n\
    }\n\ninline uint64_t exponent_threshold(uint64_t base, uint64_t limit) {\n   \
    \ assert(base >= 2);\n    if (limit <= 1) return 0;\n\n    uint64_t exponent =\
    \ 0;\n    uint64_t value = 1;\n    while (value < limit) {\n        exponent++;\n\
    \        if (value > limit / base) return exponent;\n        value *= base;\n\
    \    }\n    return exponent;\n}\n\ninline uint64_t tetration_bounded_unsigned(uint64_t\
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
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 4 \"verify/math/tetration.test.cpp\"\
    \n\n#line 7 \"verify/math/tetration.test.cpp\"\n#include <iostream>\n#line 9 \"\
    verify/math/tetration.test.cpp\"\n\nnamespace {\n\nuint64_t minimum(uint64_t first,\
    \ uint64_t second) {\n    return first < second ? first : second;\n}\n\nuint64_t\
    \ brute_pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {\n    if\
    \ (limit == 0) return 0;\n    if (exponent == 0) return 1 < limit ? 1 : limit;\n\
    \    if (base == 0) return 0;\n\n    __uint128_t result = 1;\n    for (uint64_t\
    \ i = 0; i < exponent; i++) {\n        result *= base;\n        if (result >=\
    \ limit) return limit;\n    }\n    return uint64_t(result);\n}\n\nuint64_t brute_tetration_bounded(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return minimum(1, limit);\n    if (height == 1) return minimum(base,\
    \ limit);\n\n    uint64_t exponent = brute_tetration_bounded(base, height - 1,\
    \ limit);\n    return brute_pow_bounded(base, exponent, limit);\n}\n\nuint64_t\
    \ brute_tower_bounded(\n    const std::vector<uint64_t>& bases,\n    int index,\n\
    \    uint64_t limit\n) {\n    if (limit == 0) return 0;\n    if (index == int(bases.size()))\
    \ return minimum(1, limit);\n    if (index + 1 == int(bases.size())) return minimum(bases[index],\
    \ limit);\n\n    uint64_t exponent = brute_tower_bounded(bases, index + 1, limit);\n\
    \    return brute_pow_bounded(bases[index], exponent, limit);\n}\n\nvoid test_fixed_cases()\
    \ {\n    assert(m1une::math::tetration_mod(2ULL, 0, 1000) == 1);\n    assert(m1une::math::tetration_mod(2ULL,\
    \ 1, 1000) == 2);\n    assert(m1une::math::tetration_mod(2ULL, 4, 1000) == 536);\n\
    \    assert(m1une::math::tetration_mod(3ULL, 3, 100) == 87);\n    assert(m1une::math::tetration_mod(0ULL,\
    \ 0, 1000) == 1);\n    assert(m1une::math::tetration_mod(0ULL, 1, 1000) == 0);\n\
    \    assert(m1une::math::tetration_mod(0ULL, 2, 1000) == 1);\n    assert(m1une::math::tetration_mod(0ULL,\
    \ 3, 1000) == 0);\n    assert(m1une::math::tetration_mod(7ULL, 100, 1) == 0);\n\
    \    assert(m1une::math::tetration_bounded(2ULL, 5, 1000000) == 1000000);\n\n\
    \    std::vector<unsigned long long> empty;\n    assert(m1une::math::power_tower_mod(empty,\
    \ 37) == 1);\n    assert(m1une::math::power_tower_bounded(empty, 10) == 1);\n\n\
    \    std::vector<unsigned long long> zero_zero;\n    zero_zero.push_back(0);\n\
    \    zero_zero.push_back(0);\n    assert(m1une::math::power_tower_mod(zero_zero,\
    \ 1000) == 1);\n\n    std::vector<unsigned long long> two_zero;\n    two_zero.push_back(2);\n\
    \    two_zero.push_back(0);\n    assert(m1une::math::power_tower_mod(two_zero,\
    \ 1000) == 1);\n\n    std::vector<unsigned long long> two_three_four;\n    two_three_four.push_back(2);\n\
    \    two_three_four.push_back(3);\n    two_three_four.push_back(4);\n    assert(m1une::math::power_tower_mod(two_three_four,\
    \ 1000) == 352);\n}\n\nvoid test_tetration_against_bruteforce() {\n    const uint64_t\
    \ cap = 1000000;\n    for (uint64_t base = 0; base <= 8; base++) {\n        for\
    \ (uint64_t height = 0; height <= 7; height++) {\n            for (uint64_t limit\
    \ = 0; limit <= 1000; limit++) {\n                uint64_t expected = brute_tetration_bounded(base,\
    \ height, limit);\n                uint64_t actual = m1une::math::tetration_bounded(base,\
    \ height, limit);\n                assert(actual == expected);\n            }\n\
    \            uint64_t exact = brute_tetration_bounded(base, height, cap);\n  \
    \          if (exact == cap) continue;\n            for (uint64_t mod = 1; mod\
    \ <= 257; mod++) {\n                assert(m1une::math::tetration_mod(base, height,\
    \ mod) == exact % mod);\n            }\n        }\n    }\n}\n\nvoid enumerate_towers(\n\
    \    int length,\n    int position,\n    std::vector<uint64_t>& bases\n) {\n \
    \   if (position == length) {\n        const uint64_t cap = 1000000;\n       \
    \ for (uint64_t limit = 0; limit <= 300; limit++) {\n            uint64_t expected\
    \ = brute_tower_bounded(bases, 0, limit);\n            uint64_t actual = m1une::math::power_tower_bounded(bases,\
    \ limit);\n            assert(actual == expected);\n        }\n\n        uint64_t\
    \ exact = brute_tower_bounded(bases, 0, cap);\n        if (exact == cap) return;\n\
    \        for (uint64_t mod = 1; mod <= 127; mod++) {\n            assert(m1une::math::power_tower_mod(bases,\
    \ mod) == exact % mod);\n        }\n        return;\n    }\n\n    for (uint64_t\
    \ base = 0; base <= 4; base++) {\n        bases[position] = base;\n        enumerate_towers(length,\
    \ position + 1, bases);\n    }\n}\n\nvoid test_power_tower_against_bruteforce()\
    \ {\n    for (int length = 0; length <= 5; length++) {\n        std::vector<uint64_t>\
    \ bases(length);\n        enumerate_towers(length, 0, bases);\n    }\n}\n\n} \
    \ // namespace\n\nint main() {\n    test_fixed_cases();\n    test_tetration_against_bruteforce();\n\
    \    test_power_tower_against_bruteforce();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/tetration.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <iostream>\n#include <vector>\n\nnamespace {\n\nuint64_t minimum(uint64_t first,\
    \ uint64_t second) {\n    return first < second ? first : second;\n}\n\nuint64_t\
    \ brute_pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {\n    if\
    \ (limit == 0) return 0;\n    if (exponent == 0) return 1 < limit ? 1 : limit;\n\
    \    if (base == 0) return 0;\n\n    __uint128_t result = 1;\n    for (uint64_t\
    \ i = 0; i < exponent; i++) {\n        result *= base;\n        if (result >=\
    \ limit) return limit;\n    }\n    return uint64_t(result);\n}\n\nuint64_t brute_tetration_bounded(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return minimum(1, limit);\n    if (height == 1) return minimum(base,\
    \ limit);\n\n    uint64_t exponent = brute_tetration_bounded(base, height - 1,\
    \ limit);\n    return brute_pow_bounded(base, exponent, limit);\n}\n\nuint64_t\
    \ brute_tower_bounded(\n    const std::vector<uint64_t>& bases,\n    int index,\n\
    \    uint64_t limit\n) {\n    if (limit == 0) return 0;\n    if (index == int(bases.size()))\
    \ return minimum(1, limit);\n    if (index + 1 == int(bases.size())) return minimum(bases[index],\
    \ limit);\n\n    uint64_t exponent = brute_tower_bounded(bases, index + 1, limit);\n\
    \    return brute_pow_bounded(bases[index], exponent, limit);\n}\n\nvoid test_fixed_cases()\
    \ {\n    assert(m1une::math::tetration_mod(2ULL, 0, 1000) == 1);\n    assert(m1une::math::tetration_mod(2ULL,\
    \ 1, 1000) == 2);\n    assert(m1une::math::tetration_mod(2ULL, 4, 1000) == 536);\n\
    \    assert(m1une::math::tetration_mod(3ULL, 3, 100) == 87);\n    assert(m1une::math::tetration_mod(0ULL,\
    \ 0, 1000) == 1);\n    assert(m1une::math::tetration_mod(0ULL, 1, 1000) == 0);\n\
    \    assert(m1une::math::tetration_mod(0ULL, 2, 1000) == 1);\n    assert(m1une::math::tetration_mod(0ULL,\
    \ 3, 1000) == 0);\n    assert(m1une::math::tetration_mod(7ULL, 100, 1) == 0);\n\
    \    assert(m1une::math::tetration_bounded(2ULL, 5, 1000000) == 1000000);\n\n\
    \    std::vector<unsigned long long> empty;\n    assert(m1une::math::power_tower_mod(empty,\
    \ 37) == 1);\n    assert(m1une::math::power_tower_bounded(empty, 10) == 1);\n\n\
    \    std::vector<unsigned long long> zero_zero;\n    zero_zero.push_back(0);\n\
    \    zero_zero.push_back(0);\n    assert(m1une::math::power_tower_mod(zero_zero,\
    \ 1000) == 1);\n\n    std::vector<unsigned long long> two_zero;\n    two_zero.push_back(2);\n\
    \    two_zero.push_back(0);\n    assert(m1une::math::power_tower_mod(two_zero,\
    \ 1000) == 1);\n\n    std::vector<unsigned long long> two_three_four;\n    two_three_four.push_back(2);\n\
    \    two_three_four.push_back(3);\n    two_three_four.push_back(4);\n    assert(m1une::math::power_tower_mod(two_three_four,\
    \ 1000) == 352);\n}\n\nvoid test_tetration_against_bruteforce() {\n    const uint64_t\
    \ cap = 1000000;\n    for (uint64_t base = 0; base <= 8; base++) {\n        for\
    \ (uint64_t height = 0; height <= 7; height++) {\n            for (uint64_t limit\
    \ = 0; limit <= 1000; limit++) {\n                uint64_t expected = brute_tetration_bounded(base,\
    \ height, limit);\n                uint64_t actual = m1une::math::tetration_bounded(base,\
    \ height, limit);\n                assert(actual == expected);\n            }\n\
    \            uint64_t exact = brute_tetration_bounded(base, height, cap);\n  \
    \          if (exact == cap) continue;\n            for (uint64_t mod = 1; mod\
    \ <= 257; mod++) {\n                assert(m1une::math::tetration_mod(base, height,\
    \ mod) == exact % mod);\n            }\n        }\n    }\n}\n\nvoid enumerate_towers(\n\
    \    int length,\n    int position,\n    std::vector<uint64_t>& bases\n) {\n \
    \   if (position == length) {\n        const uint64_t cap = 1000000;\n       \
    \ for (uint64_t limit = 0; limit <= 300; limit++) {\n            uint64_t expected\
    \ = brute_tower_bounded(bases, 0, limit);\n            uint64_t actual = m1une::math::power_tower_bounded(bases,\
    \ limit);\n            assert(actual == expected);\n        }\n\n        uint64_t\
    \ exact = brute_tower_bounded(bases, 0, cap);\n        if (exact == cap) return;\n\
    \        for (uint64_t mod = 1; mod <= 127; mod++) {\n            assert(m1une::math::power_tower_mod(bases,\
    \ mod) == exact % mod);\n        }\n        return;\n    }\n\n    for (uint64_t\
    \ base = 0; base <= 4; base++) {\n        bases[position] = base;\n        enumerate_towers(length,\
    \ position + 1, bases);\n    }\n}\n\nvoid test_power_tower_against_bruteforce()\
    \ {\n    for (int length = 0; length <= 5; length++) {\n        std::vector<uint64_t>\
    \ bases(length);\n        enumerate_towers(length, 0, bases);\n    }\n}\n\n} \
    \ // namespace\n\nint main() {\n    test_fixed_cases();\n    test_tetration_against_bruteforce();\n\
    \    test_power_tower_against_bruteforce();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/tetration.hpp
  - math/prime_factorization.hpp
  isVerificationFile: true
  path: verify/math/tetration.test.cpp
  requiredBy: []
  timestamp: '2026-06-24 14:35:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/tetration.test.cpp
layout: document
redirect_from:
- /verify/verify/math/tetration.test.cpp
- /verify/verify/math/tetration.test.cpp.html
title: verify/math/tetration.test.cpp
---
