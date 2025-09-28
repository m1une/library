#ifndef M1UNE_BIT_CEIL_HPP
#define M1UNE_BIT_CEIL_HPP 1

namespace m1une {
template <typename T>
constexpr T bit_ceil(T n) {
    if (n <= 1) return 1;
    T x = 1;
    while (x < n) x <<= 1;
    return x;
}
}  // namespace m1une

#endif  // M1UNE_BIT_CEIL_HPP
