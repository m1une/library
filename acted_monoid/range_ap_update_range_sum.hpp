#ifndef M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP 1

#include <optional>
#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeApUpdateRangeSumNode {
    T sum;
    long long size;
    T idx_sum;
};

template <typename T>
struct RangeApUpdateRangeSum {
    using value_type = RangeApUpdateRangeSumNode<T>;
    using operator_type = std::optional<std::pair<T, T>>; // {a, b} for setting to a * i + b

    // Value Monoid (Sum)
    static constexpr value_type id() { return {T(0), 0, T(0)}; }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size, a.idx_sum + b.idx_sum};
    }

    // Operator Monoid (Update)
    static constexpr operator_type op_id() { return std::nullopt; }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        // Prioritize the newer operation (f) over the older one (g)
        return f.has_value() ? f : g;
    }

    // Mapping: sum = a * idx_sum + b * size
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value() || x.size == 0) return x;
        return {
            f.value().first * x.idx_sum + f.value().second * T(x.size),
            x.size,
            x.idx_sum
        };
    }

    // Helper for initializing a leaf node
    // Crucial: You MUST pass the 0-based index `idx` during initialization.
    static constexpr value_type make(const T& val, long long idx) {
        return {val, 1, T(idx)};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AP_UPDATE_RANGE_SUM_HPP
