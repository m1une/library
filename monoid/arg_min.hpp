#ifndef M1UNE_MONOID_ARG_MIN_HPP
#define M1UNE_MONOID_ARG_MIN_HPP 1

#include <functional>
#include <limits>

namespace m1une {
namespace monoid {

template <typename T>
struct ArgMinNode {
    T value;
    long long size;
    long long ord;
};

// Monoid for finding the optimal value (minimum by default) and its relative order.
// Ties are broken by choosing the earlier element.
template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct ArgMin {
    using value_type = ArgMinNode<T>;

    static constexpr value_type id() {
        return {Id, 0, -1};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        long long size = a.size + b.size;
        if (Compare()(a.value, b.value)) return {a.value, size, a.ord};
        if (Compare()(b.value, a.value)) return {b.value, size, b.ord + a.size};
        return {a.value, size, a.ord};
    }

    static constexpr value_type make(const T& val) {
        return {val, 1, 0};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ARG_MIN_HPP
