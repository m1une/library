#ifndef M1UNE_MATH_RATIONAL_HPP
#define M1UNE_MATH_RATIONAL_HPP 1

#include <cassert>
#include <compare>
#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>

namespace m1une {
namespace math {

template <std::signed_integral T = long long>
struct Rational {
    static_assert(sizeof(T) <= sizeof(long long));

   private:
    using Wide = __int128_t;
    using UnsignedWide = __uint128_t;

    T _numerator;
    T _denominator;

    static constexpr UnsignedWide magnitude(Wide value) {
        if (value < 0) {
            return static_cast<UnsignedWide>(-(value + 1)) + 1;
        }
        return static_cast<UnsignedWide>(value);
    }

    static constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide second) {
        while (second != 0) {
            UnsignedWide remainder = first % second;
            first = second;
            second = remainder;
        }
        return first;
    }

    static constexpr T narrow(Wide value) {
        assert(Wide(std::numeric_limits<T>::min()) <= value);
        assert(value <= Wide(std::numeric_limits<T>::max()));
        return static_cast<T>(value);
    }

    constexpr void assign_normalized(Wide numerator, Wide denominator) {
        assert(denominator != 0);
        if (numerator == 0) {
            _numerator = 0;
            _denominator = 1;
            return;
        }

        UnsignedWide divisor = gcd(magnitude(numerator), magnitude(denominator));
        numerator /= static_cast<Wide>(divisor);
        denominator /= static_cast<Wide>(divisor);
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        _numerator = narrow(numerator);
        _denominator = narrow(denominator);
    }

    static constexpr Rational from_wide(Wide numerator, Wide denominator) {
        Rational result;
        result.assign_normalized(numerator, denominator);
        return result;
    }

   public:
    constexpr Rational() : _numerator(0), _denominator(1) {}

    constexpr Rational(T integer) : _numerator(integer), _denominator(1) {}

    constexpr Rational(T numerator, T denominator) {
        assign_normalized(Wide(numerator), Wide(denominator));
    }

    constexpr T numerator() const {
        return _numerator;
    }

    constexpr T denominator() const {
        return _denominator;
    }

    constexpr bool is_integer() const {
        return _denominator == 1;
    }

    constexpr int sign() const {
        return (_numerator > 0) - (_numerator < 0);
    }

    constexpr Rational reciprocal() const {
        assert(_numerator != 0);
        return from_wide(Wide(_denominator), Wide(_numerator));
    }

    constexpr Rational abs() const {
        return _numerator < 0 ? -*this : *this;
    }

    constexpr long double to_long_double() const {
        return static_cast<long double>(_numerator) / static_cast<long double>(_denominator);
    }

    explicit constexpr operator long double() const {
        return to_long_double();
    }

    constexpr T trunc() const {
        return _numerator / _denominator;
    }

    constexpr T floor() const {
        T quotient = _numerator / _denominator;
        if (_numerator < 0 && _numerator % _denominator != 0) --quotient;
        return quotient;
    }

    constexpr T ceil() const {
        T quotient = _numerator / _denominator;
        if (0 < _numerator && _numerator % _denominator != 0) ++quotient;
        return quotient;
    }

    constexpr Rational operator+() const {
        return *this;
    }

    constexpr Rational operator-() const {
        return from_wide(-Wide(_numerator), Wide(_denominator));
    }

    constexpr Rational& operator+=(const Rational& other) {
        UnsignedWide common =
            gcd(static_cast<UnsignedWide>(_denominator), static_cast<UnsignedWide>(other._denominator));
        Wide left_scale = Wide(other._denominator) / static_cast<Wide>(common);
        Wide right_scale = Wide(_denominator) / static_cast<Wide>(common);
        assign_normalized(Wide(_numerator) * left_scale + Wide(other._numerator) * right_scale,
                          Wide(_denominator) * left_scale);
        return *this;
    }

    constexpr Rational& operator-=(const Rational& other) {
        return *this += -other;
    }

    constexpr Rational& operator*=(const Rational& other) {
        UnsignedWide first_gcd = gcd(magnitude(Wide(_numerator)), static_cast<UnsignedWide>(other._denominator));
        UnsignedWide second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));
        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *
                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),
                          (Wide(_denominator) / static_cast<Wide>(second_gcd)) *
                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));
        return *this;
    }

    constexpr Rational& operator/=(const Rational& other) {
        return *this *= other.reciprocal();
    }

    friend constexpr Rational operator+(Rational left, const Rational& right) {
        return left += right;
    }

    friend constexpr Rational operator-(Rational left, const Rational& right) {
        return left -= right;
    }

    friend constexpr Rational operator*(Rational left, const Rational& right) {
        return left *= right;
    }

    friend constexpr Rational operator/(Rational left, const Rational& right) {
        return left /= right;
    }

    friend constexpr bool operator==(const Rational& left, const Rational& right) {
        return left._numerator == right._numerator && left._denominator == right._denominator;
    }

    friend constexpr std::strong_ordering operator<=>(const Rational& left, const Rational& right) {
        Wide first = Wide(left._numerator) * Wide(right._denominator);
        Wide second = Wide(right._numerator) * Wide(left._denominator);
        if (first < second) return std::strong_ordering::less;
        if (second < first) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend std::ostream& operator<<(std::ostream& output, const Rational& value) {
        output << value._numerator;
        if (value._denominator != 1) {
            output << '/' << value._denominator;
        }
        return output;
    }

    friend std::istream& operator>>(std::istream& input, Rational& value) {
        T numerator;
        if (!(input >> numerator)) return input;
        T denominator = 1;
        if (input.peek() == '/') {
            input.get();
            if (!(input >> denominator)) return input;
        }
        value = Rational(numerator, denominator);
        return input;
    }
};

template <std::signed_integral T>
constexpr Rational<T> abs(const Rational<T>& value) {
    return value.abs();
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_RATIONAL_HPP
