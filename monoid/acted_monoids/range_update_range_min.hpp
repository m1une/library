#ifndef M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP 1

#include "../acted_monoid.hpp"
#include "../monoids/min_monoid.hpp"
#include "../monoids/update_monoid.hpp"

namespace m1une {

template <typename T, T identity>
using range_update_range_max = acted_monoid<min_monoid<T>, update_monoid<T, identity>, [](T x, T a) {
    if (a == identity) return x;
    return a;
}>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_UPDATE_RANGE_MIN_HPP
