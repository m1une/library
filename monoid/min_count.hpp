#ifndef M1UNE_MONOID_MIN_COUNT_HPP
#define M1UNE_MONOID_MIN_COUNT_HPP 1

#include <utility>
#include <limits>
#include <functional>

namespace m1une {
namespace monoid {

// Monoid for finding the optimal value and its frequency in a range.
// Uses a comparison functor (Compare) to determine the optimal value (default is less, i.e., minimum).
template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct MinCount {
    using value_type = std::pair<T, int>;

    // The identity element has the specified Id value and a count of 0.
    static constexpr value_type id() {
        return {Id, 0};
    }

    // Combines two elements, updating the optimal value and summing the counts if they are equal.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (Compare()(a.first, b.first)) return a;
        if (Compare()(b.first, a.first)) return b;
        return {a.first, a.second + b.second};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MIN_COUNT_HPP
