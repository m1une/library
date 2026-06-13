#ifndef M1UNE_MONOID_XOR_HPP
#define M1UNE_MONOID_XOR_HPP 1

namespace m1une {
namespace monoid {

// Monoid for bitwise XOR (Range XOR).
template <typename T>
struct Xor {
    using value_type = T;

    // Returns the identity element for bitwise XOR, which is 0.
    static constexpr T id() {
        return T(0);
    }

    // Returns the bitwise XOR of a and b.
    static constexpr T op(const T& a, const T& b) {
        return a ^ b;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_XOR_HPP
