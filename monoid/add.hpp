#ifndef M1UNE_MONOID_ADD_HPP
#define M1UNE_MONOID_ADD_HPP 1

namespace m1une {
namespace monoid {

// Monoid for addition (Range Sum).
template <typename T>
struct Add {
    using value_type = T;

    // Returns the identity element for addition, which is 0.
    static constexpr T id() {
        return T(0);
    }

    // Returns the sum of a and b.
    static constexpr T op(const T& a, const T& b) {
        return a + b;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ADD_HPP
