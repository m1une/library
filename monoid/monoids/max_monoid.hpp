#ifndef M1UNE_MAX_MONOID_HPP
#define M1UNE_MAX_MONOID_HPP 1

#include <algorithm>
#include <limits>

#include "../monoid.hpp"

namespace m1une {

template <typename T>
using max_monoid =
    monoid<T, [](T a, T b) { return std::max(a, b); }, []() { return std::numeric_limits<T>::min(); }, true>;

}  // namespace m1une

#endif  // M1UNE_MAX_MONOID_HPP
