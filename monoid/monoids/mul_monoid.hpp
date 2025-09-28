#ifndef M1UNE_MUL_MONOID_HPP
#define M1UNE_MUL_MONOID_HPP 1

#include "../monoid.hpp"

namespace m1une {

template <typename T>
using mul_monoid = monoid<T, [](T a, T b) { return a * b; }, []() { return T(1); }, true>;

}  // namespace m1une

#endif  // M1UNE_MUL_MONOID_HPP
