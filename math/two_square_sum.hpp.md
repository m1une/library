---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Square Root and Power
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/two_square_sum.test.cpp
    title: verify/math/two_square_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/two_square_sum.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"math/integer_arithmetic.hpp\"\n\n\n\n#line 5 \"math/integer_arithmetic.hpp\"\
    \n#include <concepts>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail {\n\
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
    math/prime_factorization.hpp\"\n\n\n\n#line 7 \"math/prime_factorization.hpp\"\
    \n#include <numeric>\n#line 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une\
    \ {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t\
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
    \n#line 12 \"math/two_square_sum.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace two_square_sum_detail {\n\nstruct GaussianInteger {\n    __int128_t\
    \ real;\n    __int128_t imaginary;\n};\n\ninline GaussianInteger multiply(GaussianInteger\
    \ first, GaussianInteger second) {\n    return GaussianInteger{first.real * second.real\
    \ - first.imaginary * second.imaginary,\n                           first.real\
    \ * second.imaginary + first.imaginary * second.real};\n}\n\ninline GaussianInteger\
    \ power(GaussianInteger base, int exponent) {\n    GaussianInteger result{1, 0};\n\
    \    while (exponent > 0) {\n        if ((exponent & 1) != 0) result = multiply(result,\
    \ base);\n        exponent >>= 1;\n        if (exponent != 0) base = multiply(base,\
    \ base);\n    }\n    return result;\n}\n\ninline uint64_t absolute_value(__int128_t\
    \ value) {\n    return static_cast<uint64_t>(value < 0 ? -value : value);\n}\n\
    \ninline uint64_t pow_uint64(uint64_t base, int exponent) {\n    uint64_t result\
    \ = 1;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result *=\
    \ base;\n        exponent >>= 1;\n        if (exponent != 0) base *= base;\n \
    \   }\n    return result;\n}\n\ninline GaussianInteger prime_one_mod_four_representation(uint64_t\
    \ prime) {\n    assert(prime % 4 == 1);\n    uint64_t non_residue = 2;\n    while\
    \ (internal::power_mod(non_residue, (prime - 1) / 2, prime) != prime - 1) {\n\
    \        non_residue++;\n    }\n\n    uint64_t root = internal::power_mod(non_residue,\
    \ (prime - 1) / 4, prime);\n    uint64_t previous = prime;\n    uint64_t current\
    \ = root;\n    while (static_cast<__uint128_t>(current) * current > prime) {\n\
    \        uint64_t next = previous % current;\n        previous = current;\n  \
    \      current = next;\n    }\n\n    const uint64_t real = current;\n    const\
    \ uint64_t remaining = prime - real * real;\n    const uint64_t imaginary = isqrt(remaining);\n\
    \    assert(imaginary * imaginary == remaining);\n    return GaussianInteger{static_cast<__int128_t>(real),\
    \ static_cast<__int128_t>(imaginary)};\n}\n\ninline std::vector<GaussianInteger>\
    \ prime_power_choices(GaussianInteger factor, int exponent) {\n    GaussianInteger\
    \ conjugate{factor.real, -factor.imaginary};\n\n    std::vector<GaussianInteger>\
    \ positive_powers(exponent + 1);\n    std::vector<GaussianInteger> negative_powers(exponent\
    \ + 1);\n    positive_powers[0] = GaussianInteger{1, 0};\n    negative_powers[0]\
    \ = GaussianInteger{1, 0};\n    for (int i = 0; i < exponent; i++) {\n       \
    \ positive_powers[i + 1] = multiply(positive_powers[i], factor);\n        negative_powers[i\
    \ + 1] = multiply(negative_powers[i], conjugate);\n    }\n\n    std::vector<GaussianInteger>\
    \ result;\n    result.reserve(exponent + 1);\n    for (int take_positive = 0;\
    \ take_positive <= exponent; take_positive++) {\n        result.push_back(multiply(positive_powers[take_positive],\
    \ negative_powers[exponent - take_positive]));\n    }\n    return result;\n}\n\
    \ninline void add_nonnegative_pairs(std::vector<std::pair<uint64_t, uint64_t>>&\
    \ result, GaussianInteger value,\n                                  uint64_t scale)\
    \ {\n    const uint64_t first = absolute_value(value.real) * scale;\n    const\
    \ uint64_t second = absolute_value(value.imaginary) * scale;\n    result.emplace_back(first,\
    \ second);\n    result.emplace_back(second, first);\n}\n\n}  // namespace two_square_sum_detail\n\
    \ninline std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value)\
    \ {\n    using two_square_sum_detail::GaussianInteger;\n\n    if (value == 0)\
    \ return std::vector<std::pair<uint64_t, uint64_t>>{std::pair<uint64_t, uint64_t>(0,\
    \ 0)};\n\n    uint64_t real_scale = 1;\n    std::vector<std::vector<GaussianInteger>>\
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
    \n"
  code: "#ifndef M1UNE_MATH_TWO_SQUARE_SUM_HPP\n#define M1UNE_MATH_TWO_SQUARE_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"integer_arithmetic.hpp\"\n#include\
    \ \"prime_factorization.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ two_square_sum_detail {\n\nstruct GaussianInteger {\n    __int128_t real;\n\
    \    __int128_t imaginary;\n};\n\ninline GaussianInteger multiply(GaussianInteger\
    \ first, GaussianInteger second) {\n    return GaussianInteger{first.real * second.real\
    \ - first.imaginary * second.imaginary,\n                           first.real\
    \ * second.imaginary + first.imaginary * second.real};\n}\n\ninline GaussianInteger\
    \ power(GaussianInteger base, int exponent) {\n    GaussianInteger result{1, 0};\n\
    \    while (exponent > 0) {\n        if ((exponent & 1) != 0) result = multiply(result,\
    \ base);\n        exponent >>= 1;\n        if (exponent != 0) base = multiply(base,\
    \ base);\n    }\n    return result;\n}\n\ninline uint64_t absolute_value(__int128_t\
    \ value) {\n    return static_cast<uint64_t>(value < 0 ? -value : value);\n}\n\
    \ninline uint64_t pow_uint64(uint64_t base, int exponent) {\n    uint64_t result\
    \ = 1;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result *=\
    \ base;\n        exponent >>= 1;\n        if (exponent != 0) base *= base;\n \
    \   }\n    return result;\n}\n\ninline GaussianInteger prime_one_mod_four_representation(uint64_t\
    \ prime) {\n    assert(prime % 4 == 1);\n    uint64_t non_residue = 2;\n    while\
    \ (internal::power_mod(non_residue, (prime - 1) / 2, prime) != prime - 1) {\n\
    \        non_residue++;\n    }\n\n    uint64_t root = internal::power_mod(non_residue,\
    \ (prime - 1) / 4, prime);\n    uint64_t previous = prime;\n    uint64_t current\
    \ = root;\n    while (static_cast<__uint128_t>(current) * current > prime) {\n\
    \        uint64_t next = previous % current;\n        previous = current;\n  \
    \      current = next;\n    }\n\n    const uint64_t real = current;\n    const\
    \ uint64_t remaining = prime - real * real;\n    const uint64_t imaginary = isqrt(remaining);\n\
    \    assert(imaginary * imaginary == remaining);\n    return GaussianInteger{static_cast<__int128_t>(real),\
    \ static_cast<__int128_t>(imaginary)};\n}\n\ninline std::vector<GaussianInteger>\
    \ prime_power_choices(GaussianInteger factor, int exponent) {\n    GaussianInteger\
    \ conjugate{factor.real, -factor.imaginary};\n\n    std::vector<GaussianInteger>\
    \ positive_powers(exponent + 1);\n    std::vector<GaussianInteger> negative_powers(exponent\
    \ + 1);\n    positive_powers[0] = GaussianInteger{1, 0};\n    negative_powers[0]\
    \ = GaussianInteger{1, 0};\n    for (int i = 0; i < exponent; i++) {\n       \
    \ positive_powers[i + 1] = multiply(positive_powers[i], factor);\n        negative_powers[i\
    \ + 1] = multiply(negative_powers[i], conjugate);\n    }\n\n    std::vector<GaussianInteger>\
    \ result;\n    result.reserve(exponent + 1);\n    for (int take_positive = 0;\
    \ take_positive <= exponent; take_positive++) {\n        result.push_back(multiply(positive_powers[take_positive],\
    \ negative_powers[exponent - take_positive]));\n    }\n    return result;\n}\n\
    \ninline void add_nonnegative_pairs(std::vector<std::pair<uint64_t, uint64_t>>&\
    \ result, GaussianInteger value,\n                                  uint64_t scale)\
    \ {\n    const uint64_t first = absolute_value(value.real) * scale;\n    const\
    \ uint64_t second = absolute_value(value.imaginary) * scale;\n    result.emplace_back(first,\
    \ second);\n    result.emplace_back(second, first);\n}\n\n}  // namespace two_square_sum_detail\n\
    \ninline std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value)\
    \ {\n    using two_square_sum_detail::GaussianInteger;\n\n    if (value == 0)\
    \ return std::vector<std::pair<uint64_t, uint64_t>>{std::pair<uint64_t, uint64_t>(0,\
    \ 0)};\n\n    uint64_t real_scale = 1;\n    std::vector<std::vector<GaussianInteger>>\
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
    #endif  // M1UNE_MATH_TWO_SQUARE_SUM_HPP\n"
  dependsOn:
  - math/integer_arithmetic.hpp
  - math/prime_factorization.hpp
  isVerificationFile: false
  path: math/two_square_sum.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-24 15:07:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/two_square_sum.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/two_square_sum.hpp
layout: document
title: Sum of Two Squares
---

## Overview

Find representations of an integer as a sum of two non-negative squares.

```cpp
#include "math/two_square_sum.hpp"
```

All names are in `m1une::math`.

For example, `25` has four ordered non-negative representations:

```text
0^2 + 5^2
3^2 + 4^2
4^2 + 3^2
5^2 + 0^2
```

so `two_square_sum(25)` returns the pairs `(0, 5)`, `(3, 4)`, `(4, 3)`, and
`(5, 0)`.

## API

```cpp
std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value);

std::vector<std::pair<uint64_t, uint64_t>>
represent_as_two_square_sum(uint64_t value);

bool is_two_square_sum(uint64_t value);
```

| Function | Description |
| --- | --- |
| `two_square_sum(value)` | Returns all ordered non-negative pairs `(a, b)` such that `value = a * a + b * b`. |
| `represent_as_two_square_sum(value)` | Alias of `two_square_sum(value)`. |
| `is_two_square_sum(value)` | Returns whether at least one representation exists. |

The returned vector is sorted in lexicographic order and contains no duplicate
pairs. Both `(a, b)` and `(b, a)` are included when they are different.

`two_square_sum(0)` returns one pair: `(0, 0)`.

## Criterion

By Fermat's theorem on sums of two squares, an integer has a representation as
$a^2 + b^2$ exactly when every prime congruent to `3` modulo `4` appears with an
even exponent in its prime factorization.

This is the condition tested by `is_two_square_sum`.

For construction, each prime congruent to `1` modulo `4` is first represented as
a Gaussian integer norm, and all choices of conjugate factors are combined.
Prime powers congruent to `3` modulo `4` only contribute to a real scale factor
because their exponents must be even.

## Complexity

The function first factors `value` with Pollard-Rho from
`prime_factorization.hpp`. After factorization, the construction is linear in
the number of generated Gaussian-factor choices and the number of returned
pairs.

For a prime factorization

$$
value = 2^e \prod p_i^{\alpha_i} \prod q_j^{2\beta_j},
$$

where every `p_i` is `1` modulo `4` and every `q_j` is `3` modulo `4`, the
number of Gaussian-factor choices is

$$
(e + 1) \prod_i (\alpha_i + 1).
$$

The returned vector contains at most twice this many pairs before duplicate
removal.

## Example

```cpp
#include "math/two_square_sum.hpp"

#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    uint64_t value = 65;
    std::vector<std::pair<uint64_t, uint64_t>> pairs =
        m1une::math::two_square_sum(value);

    for (const auto& pair : pairs) {
        std::cout << pair.first << " " << pair.second << "\n";
    }
}
```
