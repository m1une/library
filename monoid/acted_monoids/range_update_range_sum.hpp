#ifndef M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_SUM_HPP 1

#include "../acted_monoid.hpp"
#include "../monoid_addsz.hpp"
#include "../monoids/add_monoid.hpp"
#include "../monoids/update_monoid.hpp"

namespace m1une {

template <typename T, T identity>
using range_update_range_sum_monoid =
    acted_monoid<monoid_addsz<add_monoid<T>>, update_monoid<T, identity>,
                 [](T a, typename monoid_addsz<add_monoid<T>>::data_type x) {
                     if (a == identity) return x;
                     return typename monoid_addsz<add_monoid<T>>::data_type{a * x.size, x.size};
                 }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_SUM_HPP
