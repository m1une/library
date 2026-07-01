#ifndef M1UNE_MATH_BASE_N_HPP
#define M1UNE_MATH_BASE_N_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <optional>
#include <type_traits>
#include <vector>

namespace m1une {
namespace math {

// Returns the canonical most-significant-first base-n digits of a
// nonnegative integer. Zero is represented by one zero digit.
template <std::integral Integer>
requires(!std::same_as<std::remove_cv_t<Integer>, bool>)
std::vector<int> to_base_n(Integer value, int base) {
    assert(2 <= base);
    if (base < 2) return {};
    if constexpr (std::signed_integral<Integer>) {
        assert(0 <= value);
        if (value < 0) return {};
    }

    using Unsigned = std::make_unsigned_t<Integer>;
    Unsigned remaining = static_cast<Unsigned>(value);
    if (remaining == 0) return {0};

    std::vector<int> digits;
    const unsigned long long unsigned_base = static_cast<unsigned int>(base);
    while (remaining != 0) {
        digits.push_back(int(remaining % unsigned_base));
        remaining = Unsigned(remaining / unsigned_base);
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

// Converts most-significant-first base-n digits to an integer.
// Returns nullopt for an invalid digit or when the result does not fit.
template <std::integral Integer, class DigitSequence>
requires(!std::same_as<std::remove_cv_t<Integer>, bool>)
std::optional<Integer> checked_from_base_n(const DigitSequence& digits,
                                           int base) {
    assert(2 <= base);
    if (base < 2) return std::nullopt;

    using Unsigned = std::make_unsigned_t<Integer>;
    constexpr Unsigned integer_limit = [] {
        if constexpr (std::signed_integral<Integer>) {
            return Unsigned(std::numeric_limits<Integer>::max());
        } else {
            return std::numeric_limits<Integer>::max();
        }
    }();
    const unsigned __int128 limit = integer_limit;
    const unsigned __int128 unsigned_base = static_cast<unsigned int>(base);

    unsigned __int128 value = 0;
    for (const auto& digit_reference : digits) {
        using Digit = std::remove_cvref_t<decltype(digit_reference)>;
        static_assert(std::integral<Digit>);
        static_assert(!std::same_as<Digit, bool>);
        Digit digit = digit_reference;
        if constexpr (std::signed_integral<Digit>) {
            if (digit < 0) return std::nullopt;
        }
        using UnsignedDigit = std::make_unsigned_t<Digit>;
        UnsignedDigit unsigned_digit = static_cast<UnsignedDigit>(digit);
        unsigned __int128 converted_digit = unsigned_digit;
        if (converted_digit >= unsigned_base) {
            return std::nullopt;
        }

        if (converted_digit > limit ||
            value > (limit - converted_digit) / unsigned_base) {
            return std::nullopt;
        }
        value = value * unsigned_base + converted_digit;
    }
    return static_cast<Integer>(static_cast<Unsigned>(value));
}

// Converts most-significant-first base-n digits to an integer.
// Every digit must be valid and the result must fit in Integer.
template <std::integral Integer, class DigitSequence>
requires(!std::same_as<std::remove_cv_t<Integer>, bool>)
Integer from_base_n(const DigitSequence& digits, int base) {
    std::optional<Integer> result = checked_from_base_n<Integer>(digits, base);
    assert(result.has_value());
    return result.value_or(Integer(0));
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_BASE_N_HPP
