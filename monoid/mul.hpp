#ifndef M1UNE_MONOID_MUL_HPP
#define M1UNE_MONOID_MUL_HPP 1

namespace m1une {
namespace monoid {

// Monoid for multiplication (Range Product).
template <typename T>
struct Mul {
    using value_type = T;

    // Returns the identity element for multiplication, which is 1.
    static constexpr T id() {
        return T(1);
    }

    // Returns the product of a and b.
    static constexpr T op(const T& a, const T& b) {
        return a * b;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MUL_HPP
