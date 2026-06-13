#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP
#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP 1

#include <algorithm>
#include <optional>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeUpdateRangeMaxSubarrayNode {
    T sum, pref, suff, max_sub;
    long long size;
};

// Acted Monoid for Range Assignment (Update) and Max Contiguous Subarray Sum.
// Note: This implementation assumes empty subarrays are allowed (max sum is at least 0).
template <typename T>
struct RangeUpdateRangeMaxSubarray {
    using value_type = RangeUpdateRangeMaxSubarrayNode<T>;
    using operator_type = std::optional<T>;

    static constexpr value_type id() {
        return {T(0), T(0), T(0), T(0), 0};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        value_type res;
        res.sum = a.sum + b.sum;
        res.pref = std::max(a.pref, a.sum + b.pref);
        res.suff = std::max(b.suff, b.sum + a.suff);
        res.max_sub = std::max({a.max_sub, b.max_sub, a.suff + b.pref});
        res.size = a.size + b.size;
        return res;
    }

    static constexpr operator_type op_id() {
        return std::nullopt;
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f ? f : g;  // left-biased because new updates override old ones
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f || x.size == 0) return x;
        value_type res;
        res.sum = (*f) * x.size;
        T max_val = std::max(T(0), res.sum);
        // If empty subarrays are NOT allowed, change to: T max_val = (*f) > 0 ? res.sum : (*f);
        res.pref = res.suff = res.max_sub = max_val;
        res.size = x.size;
        return res;
    }

    static constexpr value_type make(const T& val) {
        T max_val = std::max(T(0), val);
        return {val, max_val, max_val, max_val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP
