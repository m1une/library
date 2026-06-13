#ifndef M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP
#define M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP 1

#include "../monoid/binary_inversion.hpp"

namespace m1une {
namespace acted_monoid {

template <typename T = long long>
struct RangeFlipRangeBinaryInversion {
    using value_type = m1une::monoid::BinaryInversionNode<T>;
    using operator_type = bool;

    static constexpr value_type id() {
        return {0, 0, 0};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.zeros + b.zeros, a.ones + b.ones, a.inversions + b.inversions + a.ones * b.zeros};
    }

    static constexpr operator_type op_id() {
        return false;
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f ^ g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f) return x;
        return {x.ones, x.zeros, x.zeros * x.ones - x.inversions};
    }

    static constexpr value_type make(int val) {
        if (val == 0) return {1, 0, 0};
        return {0, 1, 0};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP
