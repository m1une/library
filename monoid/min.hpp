#ifndef M1UNE_MONOID_MIN_HPP
#define M1UNE_MONOID_MIN_HPP 1

#include <algorithm>
#include <limits>

namespace m1une {
namespace monoid {

// Monoid for minimum (Range Minimum).
// The identity element defaults to the maximum possible value of type T, but can be overridden.
template <typename T, T Id = std::numeric_limits<T>::max()>
struct Min {
    using value_type = T;

    // Returns the identity element for minimum.
    static constexpr T id() { return Id; }

    // Returns the minimum of a and b.
    static constexpr T op(const T& a, const T& b) { return std::min(a, b); }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MIN_HPP
