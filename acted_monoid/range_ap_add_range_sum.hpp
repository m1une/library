#ifndef M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP 1

#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeApAddRangeSumNode {
    T sum;
    long long size;
    T idx_sum;
};

template <typename T>
struct RangeApAddRangeSum {
    using value_type = RangeApAddRangeSumNode<T>;
    using operator_type = std::pair<T, T>; // {a, b} for adding a * i + b

    // Value Monoid (Sum)
    static constexpr value_type id() { return {T(0), 0, T(0)}; }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size, a.idx_sum + b.idx_sum};
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() { return {T(0), T(0)}; }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return {f.first + g.first, f.second + g.second};
    }

    // Mapping: sum += a * idx_sum + b * size
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        return {
            x.sum + f.first * x.idx_sum + f.second * T(x.size),
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

#endif  // M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP
