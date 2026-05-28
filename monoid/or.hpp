#ifndef M1UNE_MONOID_OR_HPP
#define M1UNE_MONOID_OR_HPP 1

namespace m1une {
namespace monoid {

// Monoid for bitwise OR (Range OR).
template <typename T>
struct Or {
    using value_type = T;

    // The identity element for bitwise OR is 0 (all bits 0).
    static constexpr T id() { return T(0); }

    // Returns the bitwise OR of a and b.
    static constexpr T op(const T& a, const T& b) { return a | b; }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_OR_HPP
