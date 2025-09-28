#ifndef M1UNE_AND_MONOID_HPP
#define M1UNE_AND_MONOID_HPP 1

#include "../monoid.hpp"

namespace m1une {

template <typename T>
using and_monoid = monoid<T, [](T a, T b) { return a & b; }, []() { return ~T(0); }, true>;

}  // namespace m1une

#endif  // M1UNE_AND_MONOID_HPP
