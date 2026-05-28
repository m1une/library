#ifndef M1UNE_MONOID_WRAPPER_HPP
#define M1UNE_MONOID_WRAPPER_HPP 1

namespace m1une {
namespace monoid {

// Wrapper struct to generate a Monoid using Non-Type Template Parameters (NTTP).
// Useful for quickly defining monoids using custom functions or constexpr lambdas during contests.
template <typename T, auto Op, auto Id>
struct Wrapper {
    using value_type = T;

    // Returns the identity element by invoking the provided `Id` function.
    static constexpr T id() {
        return Id();
    }

    // Returns the result of the binary operation by invoking the provided `Op` function.
    static constexpr T op(const T& a, const T& b) {
        return Op(a, b);
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_WRAPPER_HPP
