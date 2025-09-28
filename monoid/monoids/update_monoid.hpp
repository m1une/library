#ifndef M1UNE_MONOIDS_UPDATE_MONOID_HPP
#define M1UNE_MONOIDS_UPDATE_MONOID_HPP 1

#include "../monoid.hpp"

namespace m1une {

template <typename T, T identity>
using update_monoid = monoid<T,
                             [](T a, T b) {
                                 if (b == identity) return a;
                                 return b;
                             },
                             []() { return identity; }, false>;

}  // namespace m1une

#endif  // M1UNE_MONOIDS_UPDATE_MONOID_HPP
