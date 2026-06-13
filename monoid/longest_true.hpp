#ifndef M1UNE_MONOID_LONGEST_TRUE_HPP
#define M1UNE_MONOID_LONGEST_TRUE_HPP 1

#include <algorithm>

namespace m1une {
namespace monoid {

struct LongestTrueNode {
    int len;
    int max_len;
    int l_len;
    int r_len;
};

// Monoid for finding the maximum length of a contiguous subarray
// where all elements satisfy a certain condition (i.e., are "true").
struct LongestTrue {
    using value_type = LongestTrueNode;

    // The identity element represents an empty array.
    static constexpr value_type id() {
        return {0, 0, 0, 0};
    }

    // Merges two segments.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        value_type res;
        res.len = a.len + b.len;
        res.max_len = std::max({a.max_len, b.max_len, a.r_len + b.l_len});

        res.l_len = a.l_len;
        if (a.len == a.l_len) res.l_len += b.l_len;

        res.r_len = b.r_len;
        if (b.len == b.r_len) res.r_len += a.r_len;

        return res;
    }

    // Helper to securely create a leaf node from a boolean condition.
    static constexpr value_type make(bool val) {
        return {1, val ? 1 : 0, val ? 1 : 0, val ? 1 : 0};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_LONGEST_TRUE_HPP
