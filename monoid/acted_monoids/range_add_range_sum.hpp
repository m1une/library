#ifndef M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_SUM_HPP 1

#include "../acted_monoid.hpp"
#include "../monoid_addsz.hpp"
#include "../monoids/add_monoid.hpp"

namespace m1une {

template <typename T>
using range_add_range_sum_monoid =
    acted_monoid<monoid_addsz<add_monoid<T>>, add_monoid<T>,
                 [](T a, typename monoid_addsz<add_monoid<T>>::data_type x) {
                     return typename monoid_addsz<add_monoid<T>>::data_type{x.value + a * x.size, x.size};
                 }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_SUM_HPP
