#ifndef M1UNE_MIN_MONOID_HPP
#define M1UNE_MIN_MONOID_HPP 1

#include <algorithm>
#include <limits>

#include "../monoid.hpp"

namespace m1une {
template <typename T>
using min_monoid =
    monoid<T, [](T a, T b) { return std::min(a, b); }, []() { return std::numeric_limits<T>::max(); }, true>;
}  // namespace m1une

#endif  // M1UNE_MIN_MONOID_HPP
