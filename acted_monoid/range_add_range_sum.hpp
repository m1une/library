#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP 1

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeAddRangeSumNode {
    T sum;
    long long size;
};

template <typename T>
struct RangeAddRangeSum {
    using value_type = RangeAddRangeSumNode<T>;
    using operator_type = T;

    // Value Monoid (Sum)
    static constexpr value_type id() { return {T(0), 0}; }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size};
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() { return 0; }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    // Mapping (sum + f * size)
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        return {x.sum + f * x.size, x.size};
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(const T& val) {
        return {val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP
