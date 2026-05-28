#ifndef M1UNE_MONOID_ARG_MAX_HPP
#define M1UNE_MONOID_ARG_MAX_HPP 1

#include "arg_min.hpp"
#include <limits>
#include <functional>

namespace m1une {
namespace monoid {

// Monoid for finding the maximum value and its corresponding index.
// Defined as a type alias of ArgMin using std::greater.
template <typename T, T Id = std::numeric_limits<T>::lowest()>
using ArgMax = ArgMin<T, Id, std::greater<T>>;

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ARG_MAX_HPP
