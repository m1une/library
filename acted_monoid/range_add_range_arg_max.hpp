#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP 1

#include <limits>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeAddRangeArgMaxNode {
    T max_val;
    long long index;
};

// Acted Monoid for Range Addition and Range Maximum Value & Index queries.
template <typename T>
struct RangeAddRangeArgMax {
    using value_type = RangeAddRangeArgMaxNode<T>;
    using operator_type = T;

    static constexpr value_type id() {
        return {std::numeric_limits<T>::lowest(), -1};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        // >= gives priority to the earlier (leftmost) index in case of a tie
        if (a.max_val >= b.max_val) return a;
        return b;
    }

    static constexpr operator_type op_id() {
        return T(0);
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.index == -1) return x;
        return {x.max_val + f, x.index};
    }

    // Helper for initialization, requires passing the index explicitly
    static constexpr value_type make(const T& val, long long index) {
        return {val, index};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP
