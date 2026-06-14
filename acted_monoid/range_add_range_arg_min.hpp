#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP 1

#include <functional>
#include <limits>

#include "../monoid/arg_min.hpp"

namespace m1une {
namespace acted_monoid {

template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct RangeAddRangeArgMin {
    using BaseMonoid = m1une::monoid::ArgMin<T, Id, Compare>;
    using value_type = typename BaseMonoid::value_type;
    using operator_type = T;

    // Value Monoid (ArgMin)
    static constexpr value_type id() {
        return BaseMonoid::id();
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return BaseMonoid::op(a, b);
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() {
        return T(0);
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.size == 0) return x;
        return {x.value + f, x.size, x.ord};
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(const T& val) {
        return BaseMonoid::make(val);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MIN_HPP
