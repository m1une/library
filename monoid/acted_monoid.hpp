#ifndef M1UNE_ACTED_MONOID_HPP
#define M1UNE_ACTED_MONOID_HPP 1

#include <functional>
#include <type_traits>

#include "monoid.hpp"

namespace m1une {

template <monoid_concept Data, monoid_concept Act, auto mapping>
struct acted_monoid {
    using data_monoid = Data;
    using act_monoid = Act;

    using data_type = typename Data::value_type;
    using act_type = typename Act::value_type;

    static_assert(std::is_convertible_v<decltype(mapping), std::function<data_type(act_type, data_type)>>,
                  "mapping must work as data_type(data_type, act_type)");

    static constexpr auto data_op = Data::op;
    static constexpr auto data_id = Data::id;
    static constexpr bool data_is_commutative = Data::is_commutative;
    static constexpr auto act_op = Act::op;
    static constexpr auto act_id = Act::id;
    static constexpr bool act_is_commutative = Act::is_commutative;
    static constexpr auto apply = mapping;
};

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_HPP
