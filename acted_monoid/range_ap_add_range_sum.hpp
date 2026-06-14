#ifndef M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP 1

#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeApAddRangeSumNode {
    T sum;
    long long size;
    T ord_sum;
};

template <typename T>
struct RangeApAddRangeSum {
    using value_type = RangeApAddRangeSumNode<T>;
    using operator_type = std::pair<T, T>;  // {a, b} for adding a * i + b

    // Value Monoid (Sum)
    static constexpr value_type id() {
        return {T(0), 0, T(0)};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size, a.ord_sum + b.ord_sum + T(a.size) * T(b.size)};
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() {
        return {T(0), T(0)};
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return {f.first + g.first, f.second + g.second};
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        return mapping(f, x, 0);
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x, long long ord) {
        return {x.sum + f.first * (x.ord_sum + T(ord) * T(x.size)) + f.second * T(x.size), x.size, x.ord_sum};
    }

    static constexpr operator_type op_shift(const operator_type& f, long long ord) {
        return {f.first, f.second + f.first * T(ord)};
    }

    static constexpr operator_type op_reverse(const operator_type& f, long long size) {
        return {-f.first, f.second + f.first * T(size - 1)};
    }

    static constexpr value_type make(const T& val) {
        return {val, 1, T(0)};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AP_ADD_RANGE_SUM_HPP
