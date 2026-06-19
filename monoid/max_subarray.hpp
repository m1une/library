#ifndef M1UNE_MONOID_MAX_SUBARRAY_HPP
#define M1UNE_MONOID_MAX_SUBARRAY_HPP 1

#include <functional>
#include <limits>

#include "monoid/min_subarray.hpp"

namespace m1une {
namespace monoid {

// Monoid for finding the maximum subarray sum in a range.
// Defined as a type alias of MinSubarray using std::greater.
template <typename T, T Id = std::numeric_limits<T>::lowest() / 2>
using MaxSubarray = MinSubarray<T, Id, std::greater<T>>;

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MAX_SUBARRAY_HPP
