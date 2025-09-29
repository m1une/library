#ifndef M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MIN_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MIN_HPP 1

#include "../acted_monoid.hpp"
#include "../monoids/add_monoid.hpp"
#include "../monoids/min_monoid.hpp"

namespace m1une {

template <typename T>
using range_add_range_min_monoid = acted_monoid<min_monoid<T>, add_monoid<T>, [](T a, T x) { return a + x; }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MIN_HPP
