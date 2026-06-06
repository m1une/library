#ifndef M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP 1

namespace m1une {
namespace acted_monoid {

// Acted Monoid for Range Multiplication and Range Sum queries.
// Operates natively on scalars or Modint classes without needing to track segment size.
template <typename T>
struct RangeMulRangeSum {
    using value_type = T;
    using operator_type = T;

    // Value Monoid (Sum)
    static constexpr value_type id() { return T(0); }
    static constexpr value_type op(const value_type& a, const value_type& b) { 
        return a + b; 
    }

    // Operator Monoid (Multiply)
    static constexpr operator_type op_id() { return T(1); }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) { 
        return f * g; 
    }

    // Mapping: Distribution Property ( f * (a+b) = f*a + f*b )
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        return f * x;
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(const T& val) {
        return val;
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_MUL_RANGE_SUM_HPP
