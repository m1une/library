#ifndef M1UNE_MONOID_AND_HPP
#define M1UNE_MONOID_AND_HPP 1

namespace m1une {
namespace monoid {

// Monoid for bitwise AND (Range AND).
// ~T(0) sets all bits to 1, acting as the identity for bitwise AND.
template <typename T>
struct And {
    using value_type = T;

    // The identity element for bitwise AND is all bits set to 1.
    static constexpr T id() { return ~T(0); }

    // Returns the bitwise AND of a and b.
    static constexpr T op(const T& a, const T& b) { return a & b; }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_AND_HPP
