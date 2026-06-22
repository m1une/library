#ifndef M1UNE_MATH_INTEGER_ARITHMETIC_HPP
#define M1UNE_MATH_INTEGER_ARITHMETIC_HPP 1

#include <cassert>
#include <concepts>
#include <limits>
#include <optional>
#include <type_traits>

namespace m1une {
namespace math {

namespace integer_arithmetic_detail {

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr std::optional<T> checked_multiply(T first, T second) {
    constexpr T minimum = std::numeric_limits<T>::min();
    constexpr T maximum = std::numeric_limits<T>::max();

    if constexpr (std::unsigned_integral<T>) {
        if (second != 0 && maximum / second < first) return std::nullopt;
    } else {
        if (0 < first) {
            if (0 < second) {
                if (maximum / second < first) return std::nullopt;
            } else if (second < minimum / first) {
                return std::nullopt;
            }
        } else if (first < 0) {
            if (0 < second) {
                if (first < minimum / second) return std::nullopt;
            } else if (second < maximum / first) {
                return std::nullopt;
            }
        }
    }
    return T(first * second);
}

}  // namespace integer_arithmetic_detail

// Returns floor(sqrt(value)) exactly, without floating-point arithmetic.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T isqrt(T value) {
    if constexpr (std::signed_integral<T>) assert(0 <= value);
    if (value <= 1) return value;

    T low = 1;
    T high = value / 2 + 1;
    while (low < high) {
        T middle = low + (high - low + 1) / 2;
        if (middle <= value / middle) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T floor_sqrt(T value) {
    return isqrt(value);
}

// Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T ceil_sqrt(T value) {
    T result = isqrt(value);
    if (result == 0) return 0;
    if (result != 0 && value / result == result && value % result == 0) {
        return result;
    }
    return result + 1;
}

// Returns base^exponent, or nullopt when the result does not fit in T.
template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr std::optional<T> checked_ipow(T base, Exponent exponent) {
    T result = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            auto product =
                integer_arithmetic_detail::checked_multiply(result, base);
            if (!product.has_value()) return std::nullopt;
            result = *product;
        }
        exponent >>= 1;
        if (exponent != 0) {
            auto square =
                integer_arithmetic_detail::checked_multiply(base, base);
            if (!square.has_value()) return std::nullopt;
            base = *square;
        }
    }
    return result;
}

template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr std::optional<T> checked_integer_pow(T base, Exponent exponent) {
    return checked_ipow(base, exponent);
}

// Returns base^exponent. The result must be representable by T.
template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr T ipow(T base, Exponent exponent) {
    std::optional<T> result = checked_ipow(base, exponent);
    assert(result.has_value());
    return result.value_or(T());
}

template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr T integer_pow(T base, Exponent exponent) {
    return ipow(base, exponent);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_INTEGER_ARITHMETIC_HPP
