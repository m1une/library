#ifndef M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_MINMAX_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_MINMAX_HPP 1

#include "../acted_monoid.hpp"
#include "../monoids/affine_monoid.hpp"
#include "../monoids/minmax_monoid.hpp"

namespace m1une {

// Acted monoid for range affine transformations and range min/max queries.
template <typename T>
using range_affine_range_minmax_monoid =
    acted_monoid<minmax_monoid<T>, affine_monoid<T>,
                 [](typename affine_monoid<T>::value_type f, typename minmax_monoid<T>::value_type x) {
                     auto v1 = f.first * x.first + f.second;
                     auto v2 = f.first * x.second + f.second;
                     return std::pair<T, T>(std::min(v1, v2), std::max(v1, v2));
                 }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_AFFINE_RANGE_MINMAX_HPP
