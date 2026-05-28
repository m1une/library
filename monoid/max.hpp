#ifndef M1UNE_MONOID_MAX_HPP
#define M1UNE_MONOID_MAX_HPP 1

#include <algorithm>
#include <limits>

namespace m1une {
namespace monoid {

// Monoid for maximum (Range Maximum).
// The identity element defaults to the lowest possible value of type T, but can be overridden.
template <typename T, T Id = std::numeric_limits<T>::lowest()>
struct Max {
    using value_type = T;

    // Returns the identity element for maximum.
    static constexpr T id() { return Id; }

    // Returns the maximum of a and b.
    static constexpr T op(const T& a, const T& b) { return std::max(a, b); }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MAX_HPP
