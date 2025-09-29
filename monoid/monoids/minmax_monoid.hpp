#ifndef M1UNE_MINMAX_MONOID_HPP
#define M1UNE_MINMAX_MONOID_HPP 1

#include <algorithm>
#include <limits>
#include <utility>

#include "../monoid.hpp"

namespace m1une {

// Monoid for storing both a minimum and maximum value.
// The operation combines two pairs by taking the component-wise min and max.
template <typename T>
using minmax_monoid =
    monoid<std::pair<T, T>,
           [](std::pair<T, T> a, std::pair<T, T> b) {
               return std::pair<T, T>(std::min(a.first, b.first), std::max(a.second, b.second));
           },
           []() { return std::pair<T, T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest()); }, true>;

}  // namespace m1une

#endif  // M1UNE_MINMAX_MONOID_HPP
