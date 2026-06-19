#ifndef M1UNE_MONOID_MAX_COUNT_HPP
#define M1UNE_MONOID_MAX_COUNT_HPP 1

#include <functional>
#include <limits>

#include "monoid/min_count.hpp"

namespace m1une {
namespace monoid {

// Monoid for finding the maximum value and its frequency in a range.
// Defined as a type alias of MinCount using std::greater.
template <typename T, T Id = std::numeric_limits<T>::lowest()>
using MaxCount = MinCount<T, Id, std::greater<T>>;

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MAX_COUNT_HPP
