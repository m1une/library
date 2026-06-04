#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MIN_HPP
#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MIN_HPP 1

#include <algorithm>
#include <limits>
#include <optional>

namespace m1une {
namespace acted_monoid {

template <typename T, T Id = std::numeric_limits<T>::max()>
struct RangeUpdateRangeMin {
    using value_type = T;
    using operator_type = std::optional<T>;

    // Value Monoid (Min)
    static constexpr value_type id() { return Id; }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return std::min(a, b);
    }

    // Operator Monoid (Update)
    static constexpr operator_type op_id() { return std::nullopt; }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        // Prioritize the newer operation (f) over the older one (g)
        return f.has_value() ? f : g;
    }

    // Mapping
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value() || x == id()) return x;
        return f.value();
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif
