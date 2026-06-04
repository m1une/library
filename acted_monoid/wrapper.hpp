#ifndef M1UNE_ACTED_MONOID_WRAPPER_HPP
#define M1UNE_ACTED_MONOID_WRAPPER_HPP 1

namespace m1une {
namespace acted_monoid {

// Wrapper struct to generate an Acted Monoid using Non-Type Template Parameters (NTTP).
// Useful for quickly defining acted monoids using custom functions or constexpr lambdas during contests.
template <
    typename T, 
    typename E, 
    auto Op, 
    auto Id, 
    auto OpComp, 
    auto OpId, 
    auto Mapping
>
struct Wrapper {
    using value_type = T;
    using operator_type = E;

    // Returns the identity element of the value monoid.
    static constexpr T id() {
        return Id();
    }

    // Returns the result of the value monoid binary operation.
    static constexpr T op(const T& a, const T& b) {
        return Op(a, b);
    }

    // Returns the identity element of the operator monoid.
    static constexpr E op_id() {
        return OpId();
    }

    // Composes two operations f and g (corresponds to f(g(x))).
    static constexpr E op_comp(const E& f, const E& g) {
        return OpComp(f, g);
    }

    // Applies the operator f onto the value x.
    static constexpr T mapping(const E& f, const T& x) {
        return Mapping(f, x);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_WRAPPER_HPP
