#ifndef M1UNE_AFFINE_HPP
#define M1UNE_AFFINE_HPP 1

#include <utility>

namespace m1une {
template <typename T>
T affine(std::pair<T, T> f, T x) {
    return f.first * x + f.second;
}
}  // namespace m1une

#endif  // M1UNE_AFFINE_HPP
