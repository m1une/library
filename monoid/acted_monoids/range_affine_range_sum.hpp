#ifndef M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_SUM_HPP 1

#include "../acted_monoid.hpp"
#include "../monoid_addsz.hpp"
#include "../monoids/add_monoid.hpp"
#include "../monoids/affine_monoid.hpp"

namespace m1une {

template <typename T>
using range_affine_range_sum_monoid =
    acted_monoid<monoid_addsz<add_monoid<T>>, affine_monoid<T>,
                 [](typename affine_monoid<T>::value_type f, typename monoid_addsz<add_monoid<T>>::value_type x) {
                     // f = (a, b) is the affine transformation
                     // x = {value, size} is the data (sum and size of the range)
                     // Applying f to each element xi and summing up:
                     // sum(a*xi + b) = a * sum(xi) + b * size
                     return typename monoid_addsz<add_monoid<T>>::value_type{f.first * x.value + f.second * x.size,
                                                                             x.size};
                 }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_SUM_HPP
