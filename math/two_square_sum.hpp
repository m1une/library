#ifndef M1UNE_MATH_TWO_SQUARE_SUM_HPP
#define M1UNE_MATH_TWO_SQUARE_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "integer_arithmetic.hpp"
#include "prime_factorization.hpp"

namespace m1une {
namespace math {

namespace two_square_sum_detail {

struct GaussianInteger {
    __int128_t real;
    __int128_t imaginary;
};

inline GaussianInteger multiply(GaussianInteger first, GaussianInteger second) {
    return GaussianInteger{first.real * second.real - first.imaginary * second.imaginary,
                           first.real * second.imaginary + first.imaginary * second.real};
}

inline GaussianInteger power(GaussianInteger base, int exponent) {
    GaussianInteger result{1, 0};
    while (exponent > 0) {
        if ((exponent & 1) != 0) result = multiply(result, base);
        exponent >>= 1;
        if (exponent != 0) base = multiply(base, base);
    }
    return result;
}

inline uint64_t absolute_value(__int128_t value) {
    return static_cast<uint64_t>(value < 0 ? -value : value);
}

inline uint64_t pow_uint64(uint64_t base, int exponent) {
    uint64_t result = 1;
    while (exponent > 0) {
        if ((exponent & 1) != 0) result *= base;
        exponent >>= 1;
        if (exponent != 0) base *= base;
    }
    return result;
}

inline GaussianInteger prime_one_mod_four_representation(uint64_t prime) {
    assert(prime % 4 == 1);
    uint64_t non_residue = 2;
    while (internal::power_mod(non_residue, (prime - 1) / 2, prime) != prime - 1) {
        non_residue++;
    }

    uint64_t root = internal::power_mod(non_residue, (prime - 1) / 4, prime);
    uint64_t previous = prime;
    uint64_t current = root;
    while (static_cast<__uint128_t>(current) * current > prime) {
        uint64_t next = previous % current;
        previous = current;
        current = next;
    }

    const uint64_t real = current;
    const uint64_t remaining = prime - real * real;
    const uint64_t imaginary = isqrt(remaining);
    assert(imaginary * imaginary == remaining);
    return GaussianInteger{static_cast<__int128_t>(real), static_cast<__int128_t>(imaginary)};
}

inline std::vector<GaussianInteger> prime_power_choices(GaussianInteger factor, int exponent) {
    GaussianInteger conjugate{factor.real, -factor.imaginary};

    std::vector<GaussianInteger> positive_powers(exponent + 1);
    std::vector<GaussianInteger> negative_powers(exponent + 1);
    positive_powers[0] = GaussianInteger{1, 0};
    negative_powers[0] = GaussianInteger{1, 0};
    for (int i = 0; i < exponent; i++) {
        positive_powers[i + 1] = multiply(positive_powers[i], factor);
        negative_powers[i + 1] = multiply(negative_powers[i], conjugate);
    }

    std::vector<GaussianInteger> result;
    result.reserve(exponent + 1);
    for (int take_positive = 0; take_positive <= exponent; take_positive++) {
        result.push_back(multiply(positive_powers[take_positive], negative_powers[exponent - take_positive]));
    }
    return result;
}

inline void add_nonnegative_pairs(std::vector<std::pair<uint64_t, uint64_t>>& result, GaussianInteger value,
                                  uint64_t scale) {
    const uint64_t first = absolute_value(value.real) * scale;
    const uint64_t second = absolute_value(value.imaginary) * scale;
    result.emplace_back(first, second);
    result.emplace_back(second, first);
}

}  // namespace two_square_sum_detail

inline std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value) {
    using two_square_sum_detail::GaussianInteger;

    if (value == 0) return std::vector<std::pair<uint64_t, uint64_t>>{std::pair<uint64_t, uint64_t>(0, 0)};

    uint64_t real_scale = 1;
    std::vector<std::vector<GaussianInteger>> choices_by_prime;
    for (const auto& factor : prime_factorize(value)) {
        const uint64_t prime = factor.first;
        const int exponent = factor.second;

        if (prime % 4 == 3) {
            if ((exponent & 1) != 0) return {};
            real_scale *= two_square_sum_detail::pow_uint64(prime, exponent / 2);
            continue;
        }

        GaussianInteger gaussian_factor;
        if (prime == 2) {
            gaussian_factor = GaussianInteger{1, 1};
        } else {
            gaussian_factor = two_square_sum_detail::prime_one_mod_four_representation(prime);
        }
        choices_by_prime.push_back(two_square_sum_detail::prime_power_choices(gaussian_factor, exponent));
    }

    std::vector<GaussianInteger> values;
    values.push_back(GaussianInteger{1, 0});
    for (const std::vector<GaussianInteger>& choices : choices_by_prime) {
        std::vector<GaussianInteger> next;
        next.reserve(values.size() * choices.size());
        for (GaussianInteger value_so_far : values) {
            for (GaussianInteger choice : choices) {
                next.push_back(two_square_sum_detail::multiply(value_so_far, choice));
            }
        }
        values.swap(next);
    }

    std::vector<std::pair<uint64_t, uint64_t>> result;
    result.reserve(values.size() * 2);
    for (GaussianInteger gaussian : values) {
        two_square_sum_detail::add_nonnegative_pairs(result, gaussian, real_scale);
    }

    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

inline std::vector<std::pair<uint64_t, uint64_t>> represent_as_two_square_sum(uint64_t value) {
    return two_square_sum(value);
}

inline bool is_two_square_sum(uint64_t value) {
    if (value == 0) return true;
    for (const auto& factor : prime_factorize(value)) {
        if (factor.first % 4 == 3 && (factor.second & 1) != 0) return false;
    }
    return true;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_TWO_SQUARE_SUM_HPP
