#ifndef M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP 1

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeFlipRangeSumNode {
    T sum;
    long long size;
};

// Acted Monoid for binary arrays (0s and 1s).
// Supports range bit inversion (flip) and range sum queries.
template <typename T = long long>
struct RangeFlipRangeSum {
    using value_type = RangeFlipRangeSumNode<T>;
    using operator_type = bool;  // 'true' means flip the bits in the range

    static constexpr value_type id() {
        return {T(0), 0};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size};
    }

    static constexpr operator_type op_id() {
        return false;
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f ^ g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f || x.size == 0) return x;
        // If flipped, the new number of 1s is exactly (Total Elements - Old number of 1s)
        return {static_cast<T>(x.size) - x.sum, x.size};
    }

    // Initialize with a 0 or 1
    static constexpr value_type make(const T& val) {
        return {val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP
