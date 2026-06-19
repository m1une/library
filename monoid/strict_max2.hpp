#ifndef M1UNE_MONOID_STRICT_MAX2_HPP
#define M1UNE_MONOID_STRICT_MAX2_HPP 1

#include <functional>
#include <limits>

#include "monoid/strict_min2.hpp"

namespace m1une {
namespace monoid {

// Monoid for finding the strictly 1st and 2nd maximum values in a range.
// Defined as a type alias of StrictMin2 using std::greater.
template <typename T, T Id = std::numeric_limits<T>::lowest()>
using StrictMax2 = StrictMin2<T, Id, std::greater<T>>;

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_STRICT_MAX2_HPP
