#ifndef M1UNE_AFFINE_RIGHT_MONOID_HPP
#define M1UNE_AFFINE_RIGHT_MONOID_HPP 1

#include <utility>

#include "../monoid.hpp"

namespace m1une {

// right associative version of affine_monoid
// Affine transformation f(x) = ax + b is represented as (a, b)
// perform g first, then f
// op(f, g)(x) = f(g(x))
template <typename T>
using affine_right_monoid = monoid<std::pair<T, T>,
                                   [](std::pair<T, T> f, std::pair<T, T> g) {
                                       return std::pair<T, T>(f.first * g.first, f.first * g.second + f.second);
                                   },
                                   []() { return std::pair<T, T>(1, 0); }, false>;

}  // namespace m1une

#endif  // M1UNE_AFFINE_MONOID_HPP
