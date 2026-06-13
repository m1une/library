#ifndef M1UNE_MONOID_GCD_HPP
#define M1UNE_MONOID_GCD_HPP 1

#include <numeric>

namespace m1une {
namespace monoid {

// Monoid for Greatest Common Divisor (Range GCD).
template <typename T>
struct Gcd {
    using value_type = T;

    // The identity element for GCD is 0.
    static constexpr T id() {
        return T(0);
    }

    // Returns the greatest common divisor of a and b.
    static constexpr T op(const T& a, const T& b) {
        return std::gcd(a, b);
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_GCD_HPP
