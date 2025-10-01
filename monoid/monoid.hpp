#ifndef M1UNE_MONOID_HPP
#define M1UNE_MONOID_HPP 1

#include <concepts>
#include <functional>
#include <type_traits>

namespace m1une {

template <typename T, auto operation, auto identity, bool commutative>
struct monoid {
    static_assert(std::is_invocable_r_v<T, decltype(operation), T, T>, "operation must work as T(T, T)");
    static_assert(std::is_invocable_r_v<T, decltype(identity)>, "identity must work as T()");

    using value_type = T;
    static constexpr auto op = operation;
    static constexpr auto id = identity;
    static constexpr bool is_commutative = commutative;
};

template <typename T>
concept Monoid = requires(typename T::value_type v) {
    typename T::value_type;
    { T::op(v, v) } -> std::same_as<typename T::value_type>;
    { T::id() } -> std::same_as<typename T::value_type>;
    { T::is_commutative } -> std::convertible_to<bool>;
};

}  // namespace m1une

#endif  // M1UNE_MONOID_HPP
