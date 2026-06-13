#ifndef M1UNE_MONOID_CONCEPT_HPP
#define M1UNE_MONOID_CONCEPT_HPP 1

#include <concepts>

namespace m1une {
namespace monoid {

// Concept to check if a type satisfies the requirements of a Monoid.
// A Monoid must have a `value_type`, an identity element `id()`, and an associative binary operation `op()`.
template <typename M>
concept IsMonoid = requires(typename M::value_type a, typename M::value_type b) {
    // 1. Must define `value_type`
    typename M::value_type;

    // 2. Must have a static method `id()` returning `value_type`
    { M::id() } -> std::same_as<typename M::value_type>;

    // 3. Must have a static method `op(a, b)` returning `value_type`
    { M::op(a, b) } -> std::same_as<typename M::value_type>;
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_CONCEPT_HPP
