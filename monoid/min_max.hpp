#ifndef M1UNE_MONOID_MIN_MAX_HPP
#define M1UNE_MONOID_MIN_MAX_HPP 1

#include <algorithm>
#include <limits>
#include <utility>

namespace m1une {
namespace monoid {

// Monoid for finding both the minimum and maximum values in a range simultaneously.
template <typename T, T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>
struct MinMax {
    using value_type = std::pair<T, T>;

    // The identity element contains the bounds for min and max.
    static constexpr value_type id() {
        return {MinId, MaxId};
    }

    // Merges two elements, extracting the overall min and max.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {std::min(a.first, b.first), std::max(a.second, b.second)};
    }

    // Helper to securely create a leaf node from a single value.
    static constexpr value_type make(const T& val) {
        return {val, val};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MIN_MAX_HPP
