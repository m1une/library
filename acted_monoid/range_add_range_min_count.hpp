#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP 1

#include "../monoid/min_count.hpp"
#include <limits>
#include <functional>

namespace m1une {
namespace acted_monoid {

template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct RangeAddRangeMinCount {
    using BaseMonoid = m1une::monoid::MinCount<T, Id, Compare>;
    using value_type = typename BaseMonoid::value_type; // std::pair<T, int>
    using operator_type = T;

    // Value Monoid (Min Count)
    static constexpr value_type id() { return BaseMonoid::id(); }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return BaseMonoid::op(a, b);
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() { return T(0); }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.second == 0) return x; // Do not apply to the identity element
        return {x.first + f, x.second};
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(const T& val, int count = 1) {
        return BaseMonoid::make(val, count);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_COUNT_HPP
