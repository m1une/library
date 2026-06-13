#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP 1

#include <optional>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeUpdateRangeSumNode {
    T sum;
    long long size;
};

template <typename T>
struct RangeUpdateRangeSum {
    using value_type = RangeUpdateRangeSumNode<T>;
    using operator_type = std::optional<T>;

    static constexpr value_type id() {
        return {T(0), 0};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size};
    }

    static constexpr operator_type op_id() {
        return std::nullopt;
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f.has_value() ? f : g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value() || x.size == 0) return x;
        return {f.value() * static_cast<T>(x.size), x.size};
    }

    static constexpr value_type make(const T& val) {
        return {val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP
