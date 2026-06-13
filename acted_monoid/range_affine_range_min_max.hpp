#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP
#define M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP 1

#include <algorithm>
#include <limits>
#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeAffineRangeMinMaxNode {
    T min_val;
    T max_val;
};

template <typename T, T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>
struct RangeAffineRangeMinMax {
    using value_type = RangeAffineRangeMinMaxNode<T>;
    using operator_type = std::pair<T, T>;

    static constexpr value_type id() {
        return {MinId, MaxId};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {std::min(a.min_val, b.min_val), std::max(a.max_val, b.max_val)};
    }

    static constexpr operator_type op_id() {
        return {T(1), T(0)};
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return {f.first * g.first, f.first * g.second + f.second};
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.min_val == MinId) return x;

        T v1 = f.first * x.min_val + f.second;
        T v2 = f.first * x.max_val + f.second;

        if (f.first < 0) {
            return {v2, v1};
        }
        return {v1, v2};
    }

    static constexpr value_type make(const T& val) {
        return {val, val};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_MIN_MAX_HPP
