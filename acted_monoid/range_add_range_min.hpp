#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP 1

#include <algorithm>
#include <limits>

namespace m1une {
namespace acted_monoid {

template <typename T, T Id = std::numeric_limits<T>::max()>
struct RangeAddRangeMin {
    using value_type = T;
    using operator_type = T;

    // Value Monoid (Min)
    static constexpr value_type id() {
        return Id;
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return std::min(a, b);
    }

    // Operator Monoid (Add)
    static constexpr operator_type op_id() {
        return 0;
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x == id()) return x;  // Do not apply the operator to the identity element
        return x + f;
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP
