#ifndef M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP
#define M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP 1

#include <cassert>
#include <cstddef>
#include <vector>

namespace m1une {
namespace math {

namespace zeta_mobius_transform_detail {

inline bool is_power_of_two(std::size_t size) noexcept {
    return size != 0 && (size & (size - 1)) == 0;
}

inline std::vector<std::size_t> primes_up_to(std::size_t limit) {
    std::vector<std::size_t> primes;
    std::vector<bool> is_prime(limit + 1, true);
    if (!is_prime.empty()) is_prime[0] = false;
    if (limit >= 1) is_prime[1] = false;
    for (std::size_t value = 2; value <= limit; ++value) {
        if (!is_prime[value]) continue;
        primes.emplace_back(value);
        if (value > limit / value) continue;
        for (
            std::size_t multiple = value * value;
            multiple <= limit;
            multiple += value
        ) {
            is_prime[multiple] = false;
        }
    }
    return primes;
}

}  // namespace zeta_mobius_transform_detail

template <typename T>
void subset_zeta_transform(std::vector<T>& values) {
    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));
    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {
        for (
            std::size_t block = 0;
            block < values.size();
            block += bit << 1
        ) {
            for (std::size_t offset = 0; offset < bit; ++offset) {
                values[block + bit + offset] += values[block + offset];
            }
        }
    }
}

template <typename T>
void subset_mobius_transform(std::vector<T>& values) {
    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));
    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {
        for (
            std::size_t block = 0;
            block < values.size();
            block += bit << 1
        ) {
            for (std::size_t offset = 0; offset < bit; ++offset) {
                values[block + bit + offset] -= values[block + offset];
            }
        }
    }
}

template <typename T>
void superset_zeta_transform(std::vector<T>& values) {
    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));
    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {
        for (
            std::size_t block = 0;
            block < values.size();
            block += bit << 1
        ) {
            for (std::size_t offset = 0; offset < bit; ++offset) {
                values[block + offset] += values[block + bit + offset];
            }
        }
    }
}

template <typename T>
void superset_mobius_transform(std::vector<T>& values) {
    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));
    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {
        for (
            std::size_t block = 0;
            block < values.size();
            block += bit << 1
        ) {
            for (std::size_t offset = 0; offset < bit; ++offset) {
                values[block + offset] -= values[block + bit + offset];
            }
        }
    }
}

template <typename T>
void divisor_zeta_transform(std::vector<T>& values) {
    if (values.size() <= 2) return;
    const std::size_t limit = values.size() - 1;
    const std::vector<std::size_t> primes =
        zeta_mobius_transform_detail::primes_up_to(limit);
    for (std::size_t prime : primes) {
        for (std::size_t value = 1; value <= limit / prime; ++value) {
            values[value * prime] += values[value];
        }
    }
}

template <typename T>
void divisor_mobius_transform(std::vector<T>& values) {
    if (values.size() <= 2) return;
    const std::size_t limit = values.size() - 1;
    const std::vector<std::size_t> primes =
        zeta_mobius_transform_detail::primes_up_to(limit);
    for (std::size_t prime : primes) {
        for (
            std::size_t value = limit / prime;
            value >= 1;
            --value
        ) {
            values[value * prime] -= values[value];
        }
    }
}

template <typename T>
void multiple_zeta_transform(std::vector<T>& values) {
    if (values.size() <= 2) return;
    const std::size_t limit = values.size() - 1;
    const std::vector<std::size_t> primes =
        zeta_mobius_transform_detail::primes_up_to(limit);
    for (std::size_t prime : primes) {
        for (
            std::size_t value = limit / prime;
            value >= 1;
            --value
        ) {
            values[value] += values[value * prime];
        }
    }
}

template <typename T>
void multiple_mobius_transform(std::vector<T>& values) {
    if (values.size() <= 2) return;
    const std::size_t limit = values.size() - 1;
    const std::vector<std::size_t> primes =
        zeta_mobius_transform_detail::primes_up_to(limit);
    for (std::size_t prime : primes) {
        for (std::size_t value = 1; value <= limit / prime; ++value) {
            values[value] -= values[value * prime];
        }
    }
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP
