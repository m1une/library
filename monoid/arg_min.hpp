#ifndef M1UNE_MONOID_ARG_MIN_HPP
#define M1UNE_MONOID_ARG_MIN_HPP 1

#include <functional>
#include <limits>
#include <utility>

namespace m1une {
namespace monoid {

// Monoid for finding the optimal value (minimum by default) and its corresponding index.
// Ties are broken by choosing the smaller index.
template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct ArgMin {
    using value_type = std::pair<T, int>;

    // The identity element uses the Id value and an invalid index.
    static constexpr value_type id() {
        return {Id, -1};
    }

    // Merges two elements based on the Compare functor.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (Compare()(a.first, b.first)) return a;
        if (Compare()(b.first, a.first)) return b;
        return (a.second < b.second) ? a : b;
    }

    // Helper to create a leaf node.
    static constexpr value_type make(const T& val, int index) {
        return {val, index};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ARG_MIN_HPP
