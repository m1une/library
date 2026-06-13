#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP
#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP 1

#include <algorithm>
#include <limits>
#include <optional>
#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeApUpdateRangeMinMaxNode {
    T min_val;
    T max_val;
    long long left_idx;
    long long right_idx;
};

template <typename T, T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>
struct RangeApUpdateRangeMinMax {
    using value_type = RangeApUpdateRangeMinMaxNode<T>;
    using operator_type = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b

    // Value Monoid (Min & Max)
    static constexpr value_type id() {
        return {MinId, MaxId, std::numeric_limits<long long>::max(), std::numeric_limits<long long>::lowest()};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.min_val == MinId) return b;
        if (b.min_val == MinId) return a;
        return {std::min(a.min_val, b.min_val), std::max(a.max_val, b.max_val), std::min(a.left_idx, b.left_idx),
                std::max(a.right_idx, b.right_idx)};
    }

    // Operator Monoid (Update)
    static constexpr operator_type op_id() {
        return std::nullopt;
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        // Newer operation (f) completely overwrites the older one (g)
        return f.has_value() ? f : g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value() || x.min_val == MinId) return x;

        T a = f.value().first;
        T b = f.value().second;

        // Evaluate the linear function at the boundaries of the segment
        T val_left = a * static_cast<T>(x.left_idx) + b;
        T val_right = a * static_cast<T>(x.right_idx) + b;

        return {std::min(val_left, val_right), std::max(val_left, val_right), x.left_idx, x.right_idx};
    }

    // Helper for initializing a leaf node
    // Crucial: You MUST pass the 0-based index `idx` during initialization.
    static constexpr value_type make(const T& val, long long idx) {
        return {val, val, idx, idx};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP
