#ifndef M1UNE_AFFINE_MONOID_HPP
#define M1UNE_AFFINE_MONOID_HPP 1

#include <utility>

#include "../monoid.hpp"

namespace m1une {
template <typename T>
// Affine transformation f(x) = ax + b is represented as (a, b)
// perform f first, then g
// op(f, g)(x) = g(f(x))
using affine_monoid = monoid<std::pair<T, T>,
                             [](std::pair<T, T> f, std::pair<T, T> g) {
                                 return std::pair<T, T>(f.first * g.first, f.second * g.first + g.second);
                             },
                             []() { return std::pair<T, T>(1, 0); }, false>;
}  // namespace m1une

#endif  // M1UNE_AFFINE_MONOID_HPP
