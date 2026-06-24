#ifndef M1UNE_MATH_TETRATION_HPP
#define M1UNE_MATH_TETRATION_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "prime_factorization.hpp"

namespace m1une {
namespace math {

namespace tetration_detail {

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
uint64_t to_uint64(T value) {
    if constexpr (std::signed_integral<T>) {
        assert(value >= 0);
    }
    return static_cast<uint64_t>(value);
}

inline uint64_t multiply_mod(uint64_t first, uint64_t second, uint64_t mod) {
    return static_cast<uint64_t>(
        static_cast<__uint128_t>(first) * second % mod
    );
}

inline uint64_t pow_mod(uint64_t base, __uint128_t exponent, uint64_t mod) {
    assert(mod >= 1);
    if (mod == 1) return 0;
    base %= mod;
    uint64_t result = 1 % mod;
    while (exponent > 0) {
        if ((exponent & 1) != 0) result = multiply_mod(result, base, mod);
        base = multiply_mod(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

inline uint64_t pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {
    if (limit == 0) return 0;
    __uint128_t result = 1;
    for (uint64_t i = 0; i < exponent; i++) {
        result *= base;
        if (result >= limit) return limit;
    }
    return static_cast<uint64_t>(result);
}

inline uint64_t exponent_threshold(uint64_t base, uint64_t limit) {
    assert(base >= 2);
    if (limit <= 1) return 0;

    uint64_t exponent = 0;
    uint64_t value = 1;
    while (value < limit) {
        exponent++;
        if (value > limit / base) return exponent;
        value *= base;
    }
    return exponent;
}

inline uint64_t tetration_bounded_unsigned(uint64_t base, uint64_t height, uint64_t limit) {
    if (limit == 0) return 0;
    if (height == 0) return limit < 1 ? limit : 1;
    if (height == 1) return base < limit ? base : limit;

    if (base == 0) {
        const uint64_t value = (height & 1) == 0 ? 1 : 0;
        return value < limit ? value : limit;
    }
    if (base == 1) return limit < 1 ? limit : 1;

    const uint64_t threshold = exponent_threshold(base, limit);
    const uint64_t exponent = tetration_bounded_unsigned(base, height - 1, threshold);
    if (exponent >= threshold) return limit;
    return pow_bounded(base, exponent, limit);
}

inline uint64_t tetration_mod_unsigned(uint64_t base, uint64_t height, uint64_t mod) {
    assert(mod >= 1);
    if (mod == 1) return 0;
    if (height == 0) return 1 % mod;
    if (height == 1) return base % mod;
    if (base == 0) return (height & 1) == 0 ? 1 % mod : 0;
    if (base == 1) return 1 % mod;

    const uint64_t phi = euler_phi(mod);
    uint64_t reduced_exponent = tetration_mod_unsigned(base, height - 1, phi);
    __uint128_t exponent = reduced_exponent;
    if (tetration_bounded_unsigned(base, height - 1, phi) >= phi) {
        exponent += phi;
    }
    return pow_mod(base, exponent, mod);
}

inline uint64_t power_tower_bounded_unsigned(
    const std::vector<uint64_t>& bases,
    int index,
    uint64_t limit
) {
    if (limit == 0) return 0;
    if (index == int(bases.size())) return limit < 1 ? limit : 1;

    const uint64_t base = bases[index];
    if (index + 1 == int(bases.size())) return base < limit ? base : limit;

    if (base == 0) {
        const uint64_t exponent = power_tower_bounded_unsigned(bases, index + 1, 1);
        const uint64_t value = exponent == 0 ? 1 : 0;
        return value < limit ? value : limit;
    }
    if (base == 1) return limit < 1 ? limit : 1;

    const uint64_t threshold = exponent_threshold(base, limit);
    const uint64_t exponent = power_tower_bounded_unsigned(bases, index + 1, threshold);
    if (exponent >= threshold) return limit;
    return pow_bounded(base, exponent, limit);
}

inline uint64_t power_tower_mod_unsigned(
    const std::vector<uint64_t>& bases,
    int index,
    uint64_t mod
) {
    assert(mod >= 1);
    if (mod == 1) return 0;
    if (index == int(bases.size())) return 1 % mod;
    if (index + 1 == int(bases.size())) return bases[index] % mod;

    const uint64_t phi = euler_phi(mod);
    uint64_t reduced_exponent = power_tower_mod_unsigned(bases, index + 1, phi);
    __uint128_t exponent = reduced_exponent;
    if (power_tower_bounded_unsigned(bases, index + 1, phi) >= phi) {
        exponent += phi;
    }
    return pow_mod(bases[index], exponent, mod);
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
std::vector<uint64_t> normalize_bases(const std::vector<T>& bases) {
    std::vector<uint64_t> result;
    result.reserve(bases.size());
    for (T base : bases) result.push_back(to_uint64(base));
    return result;
}

}  // namespace tetration_detail

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
uint64_t tetration_mod(T base, uint64_t height, uint64_t mod) {
    assert(mod >= 1);
    return tetration_detail::tetration_mod_unsigned(
        tetration_detail::to_uint64(base),
        height,
        mod
    );
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
uint64_t tetration_bounded(T base, uint64_t height, uint64_t limit) {
    return tetration_detail::tetration_bounded_unsigned(
        tetration_detail::to_uint64(base),
        height,
        limit
    );
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
uint64_t power_tower_mod(const std::vector<T>& bases, uint64_t mod) {
    assert(mod >= 1);
    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);
    return tetration_detail::power_tower_mod_unsigned(normalized, 0, mod);
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
uint64_t power_tower_bounded(const std::vector<T>& bases, uint64_t limit) {
    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);
    return tetration_detail::power_tower_bounded_unsigned(normalized, 0, limit);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_TETRATION_HPP
