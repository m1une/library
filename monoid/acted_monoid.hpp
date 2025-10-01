#ifndef M1UNE_ACTED_MONOID_HPP
#define M1UNE_ACTED_MONOID_HPP 1

#include <concepts>
#include <functional>
#include <type_traits>

#include "monoid.hpp"

namespace m1une {

template <Monoid Data, Monoid Act, auto mapping>
struct acted_monoid {
    using data_monoid = Data;
    using act_monoid = Act;

    using data_type = typename Data::value_type;
    using act_type = typename Act::value_type;

    static_assert(std::is_invocable_r_v<data_type, decltype(mapping), act_type, data_type>,
                  "mapping must work as data_type(act_type, data_type)");

    static constexpr auto data_op = Data::op;
    static constexpr auto data_id = Data::id;
    static constexpr bool data_is_commutative = Data::is_commutative;
    static constexpr auto act_op = Act::op;
    static constexpr auto act_id = Act::id;
    static constexpr bool act_is_commutative = Act::is_commutative;
    static constexpr auto apply = mapping;
};

template <typename T>
concept ActedMonoid = requires(typename T::data_type d, typename T::act_type a) {
    typename T::data_monoid;
    typename T::act_monoid;
    typename T::data_type;
    typename T::act_type;
    requires Monoid<typename T::data_monoid>;
    requires Monoid<typename T::act_monoid>;
    { T::apply(a, d) } -> std::same_as<typename T::data_type>;
};

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_HPP
