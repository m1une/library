#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP
#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP 1

#include <optional>

#include "../monoid/longest_true.hpp"

namespace m1une {
namespace acted_monoid {

struct RangeUpdateRangeLongestTrue {
    using BaseMonoid = m1une::monoid::LongestTrue;
    using value_type = typename BaseMonoid::value_type;
    using operator_type = std::optional<bool>;

    // Value Monoid
    static constexpr value_type id() {
        return BaseMonoid::id();
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return BaseMonoid::op(a, b);
    }

    // Operator Monoid (Update/Overwrite)
    static constexpr operator_type op_id() {
        return std::nullopt;
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f.has_value() ? f : g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value()) return x;
        bool v = f.value();

        // If updating to 'true', the entire length satisfies the condition.
        // If updating to 'false', zero elements satisfy the condition.
        return {x.len, v ? x.len : 0, v ? x.len : 0, v ? x.len : 0};
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(bool val) {
        return BaseMonoid::make(val);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_LONGEST_TRUE_HPP
