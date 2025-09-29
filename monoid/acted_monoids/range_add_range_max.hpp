#ifndef M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP
#define M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP 1

#include "../acted_monoid.hpp"
#include "../monoids/add_monoid.hpp"
#include "../monoids/max_monoid.hpp"

namespace m1une {

template <typename T>
using range_add_range_max_monoid = acted_monoid<max_monoid<T>, add_monoid<T>, [](T a, T x) { return a + x; }>;

}  // namespace m1une

#endif  // M1UNE_ACTED_MONOIDS_RANGE_ADD_RANGE_MAX_HPP
