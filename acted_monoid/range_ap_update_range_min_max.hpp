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
    long long size;
};

template <typename T, T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>
struct RangeApUpdateRangeMinMax {
    using value_type = RangeApUpdateRangeMinMaxNode<T>;
    using operator_type = std::optional<std::pair<T, T>>;  // {a, b} for setting to a * i + b

    // Value Monoid (Min & Max)
    static constexpr value_type id() {
        return {MinId, MaxId, 0};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        return {std::min(a.min_val, b.min_val), std::max(a.max_val, b.max_val), a.size + b.size};
    }

    // Operator Monoid (Update)
    static constexpr operator_type op_id() {
        return std::nullopt;
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        // Newer operation (f) completely overwrites the older one (g)
        return f.has_value() ? f : g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        return mapping(f, x, 0);
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x, long long ord) {
        if (!f.has_value() || x.min_val == MinId) return x;

        T a = f.value().first;
        T b = f.value().second;
        T val_left = a * static_cast<T>(ord) + b;
        T val_right = a * static_cast<T>(ord + x.size - 1) + b;

        return {std::min(val_left, val_right), std::max(val_left, val_right), x.size};
    }

    static constexpr operator_type op_shift(const operator_type& f, long long ord) {
        if (!f.has_value()) return f;
        return std::pair<T, T>{f.value().first, f.value().second + f.value().first * T(ord)};
    }

    static constexpr operator_type op_reverse(const operator_type& f, long long size) {
        if (!f.has_value()) return f;
        return std::pair<T, T>{-f.value().first, f.value().second + f.value().first * T(size - 1)};
    }

    static constexpr value_type make(const T& val) {
        return {val, val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_MIN_MAX_HPP
