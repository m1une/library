#ifndef M1UNE_ACTED_MONOID_CONCEPT_HPP
#define M1UNE_ACTED_MONOID_CONCEPT_HPP 1

#include <concepts>

namespace m1une {
namespace acted_monoid {

// Concept defining the requirements for an Acted Monoid.
template <typename AM>
concept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type b, typename AM::operator_type f,
                                 typename AM::operator_type g) {
    // 1. Value Monoid
    typename AM::value_type;
    { AM::id() } -> std::same_as<typename AM::value_type>;
    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;

    // 2. Operator Monoid
    typename AM::operator_type;
    { AM::op_id() } -> std::same_as<typename AM::operator_type>;
    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))

    // 3. Mapping: Operator x Value -> Value
    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_CONCEPT_HPP
