#ifndef M1UNE_MONOID_LONGEST_SAME_HPP
#define M1UNE_MONOID_LONGEST_SAME_HPP 1

#include <algorithm>

namespace m1une {
namespace monoid {

template <typename T>
struct LongestSameNode {
    int len;
    int max_len;
    T l_val;
    int l_len;
    T r_val;
    int r_len;
};

// Monoid for finding the maximum length of a contiguous subarray
// where all elements have the same value.
template <typename T>
struct LongestSame {
    using value_type = LongestSameNode<T>;

    // The identity element represents an empty array.
    static constexpr value_type id() {
        return {0, 0, T(), 0, T(), 0};
    }

    // Merges two segments.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        value_type res;
        res.len = a.len + b.len;
        res.max_len = std::max(a.max_len, b.max_len);
        
        if (a.r_val == b.l_val) {
            res.max_len = std::max(res.max_len, a.r_len + b.l_len);
        }

        res.l_val = a.l_val;
        res.l_len = a.l_len;
        if (a.len == a.l_len && a.l_val == b.l_val) {
            res.l_len += b.l_len;
        }

        res.r_val = b.r_val;
        res.r_len = b.r_len;
        if (b.len == b.r_len && b.r_val == a.r_val) {
            res.r_len += a.r_len;
        }

        return res;
    }

    // Helper to securely create a leaf node from a single value.
    static constexpr value_type make(const T& val) {
        return {1, 1, val, 1, val, 1};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_LONGEST_SAME_HPP
