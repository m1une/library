#ifndef M1UNE_MATH_PRIME_FACTORIZATION_HPP
#define M1UNE_MATH_PRIME_FACTORIZATION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

namespace m1une {
namespace math {

namespace internal {

inline uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t mod) {
    return static_cast<uint64_t>(static_cast<unsigned __int128>(a) * b % mod);
}

inline uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = multiply_mod(result, base, mod);
        base = multiply_mod(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

inline uint64_t pollard_random() {
    static uint64_t state = 0x123456789abcdef0ULL;
    state += 0x9e3779b97f4a7c15ULL;
    uint64_t value = state;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

}  // namespace internal

inline bool is_prime(uint64_t value) {
    if (value < 2) return false;
    for (uint64_t prime :
         {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL,
          31ULL, 37ULL}) {
        if (value % prime == 0) return value == prime;
    }

    uint64_t odd_part = value - 1;
    int power_of_two = 0;
    while ((odd_part & 1) == 0) {
        odd_part >>= 1;
        power_of_two++;
    }

    for (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (base % value == 0) continue;
        uint64_t x = internal::power_mod(base % value, odd_part, value);
        if (x == 1 || x == value - 1) continue;

        bool composite = true;
        for (int i = 1; i < power_of_two; i++) {
            x = internal::multiply_mod(x, x, value);
            if (x == value - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

namespace internal {

inline uint64_t pollard_rho(uint64_t value) {
    for (uint64_t prime :
         {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL,
          31ULL, 37ULL}) {
        if (value % prime == 0) return prime;
    }

    while (true) {
        const uint64_t constant = pollard_random() % (value - 1) + 1;
        uint64_t y = pollard_random() % (value - 1) + 1;
        uint64_t x = 0;
        uint64_t saved_y = 0;
        uint64_t gcd = 1;
        uint64_t segment_length = 1;

        auto advance = [&](uint64_t current) {
            return static_cast<uint64_t>(
                (static_cast<unsigned __int128>(multiply_mod(current, current, value)) +
                 constant) %
                value
            );
        };

        while (gcd == 1) {
            x = y;
            for (uint64_t i = 0; i < segment_length; i++) y = advance(y);

            for (uint64_t offset = 0; offset < segment_length && gcd == 1;
                 offset += 128) {
                saved_y = y;
                uint64_t product = 1;
                const uint64_t block = std::min<uint64_t>(128, segment_length - offset);
                for (uint64_t i = 0; i < block; i++) {
                    y = advance(y);
                    const uint64_t difference = x > y ? x - y : y - x;
                    product = multiply_mod(product, difference, value);
                }
                gcd = std::gcd(product, value);
            }
            segment_length <<= 1;
        }

        if (gcd == value) {
            do {
                saved_y = advance(saved_y);
                const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;
                gcd = std::gcd(difference, value);
            } while (gcd == 1);
        }
        if (gcd != value) return gcd;
    }
}

inline void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {
    if (value == 1) return;
    if (is_prime(value)) {
        factors.push_back(value);
        return;
    }
    const uint64_t divisor = pollard_rho(value);
    factor_recursively(divisor, factors);
    factor_recursively(value / divisor, factors);
}

}  // namespace internal

inline std::vector<uint64_t> prime_factors(uint64_t value) {
    assert(value >= 1);
    std::vector<uint64_t> result;
    internal::factor_recursively(value, result);
    std::sort(result.begin(), result.end());
    return result;
}

inline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value) {
    std::vector<uint64_t> factors = prime_factors(value);
    std::vector<std::pair<uint64_t, int>> result;
    for (uint64_t prime : factors) {
        if (result.empty() || result.back().first != prime) {
            result.emplace_back(prime, 1);
        } else {
            result.back().second++;
        }
    }
    return result;
}

inline std::vector<uint64_t> divisors(uint64_t value) {
    std::vector<uint64_t> result = {1};
    for (const auto& factor : prime_factorize(value)) {
        const int current_size = int(result.size());
        uint64_t power = 1;
        for (int exponent = 1; exponent <= factor.second; exponent++) {
            power *= factor.first;
            for (int i = 0; i < current_size; i++) {
                result.push_back(result[i] * power);
            }
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

inline uint64_t euler_phi(uint64_t value) {
    assert(value >= 1);
    uint64_t result = value;
    for (const auto& factor : prime_factorize(value)) {
        result = result / factor.first * (factor.first - 1);
    }
    return result;
}

inline int mobius(uint64_t value) {
    assert(value >= 1);
    int result = 1;
    for (const auto& factor : prime_factorize(value)) {
        if (factor.second >= 2) return 0;
        result = -result;
    }
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PRIME_FACTORIZATION_HPP
