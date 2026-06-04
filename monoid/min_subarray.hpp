#ifndef M1UNE_MONOID_MIN_SUBARRAY_HPP
#define M1UNE_MONOID_MIN_SUBARRAY_HPP 1

#include <functional>
#include <limits>

namespace m1une {
namespace monoid {

// Node for managing the optimal subarray sum.
template <typename T>
struct SubarrayNode {
    T sum;
    T pre;
    T suf;
    T opt; // Holds the optimal value (e.g., min or max)
};

// Monoid for finding the minimum subarray sum in a range.
// Uses a comparison functor (Compare) to determine the optimal value.
// Can be reused for maximum subarray sum by changing the Compare functor.
template <typename T, T Id = std::numeric_limits<T>::max() / 2, typename Compare = std::less<T>>
struct MinSubarray {
    using value_type = SubarrayNode<T>;

    // The identity element contains values that do not affect the result.
    static constexpr value_type id() {
        return {T(0), Id, Id, Id};
    }

    // Merges two subarray nodes.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.opt == Id) return b;
        if (b.opt == Id) return a;

        // Lambda to select the optimal value according to the comparison functor.
        auto get_opt = [](const T& x, const T& y) {
            return Compare()(x, y) ? x : y;
        };

        return {
            a.sum + b.sum,
            get_opt(a.pre, a.sum + b.pre),
            get_opt(b.suf, a.suf + b.sum),
            get_opt(get_opt(a.opt, b.opt), a.suf + b.pre)
        };
    }

    // Helper to securely create a leaf node from a single value.
    // Set `allow_empty = true` if empty subarrays (sum = 0) are valid answers.
    static constexpr value_type make(const T& val, bool allow_empty = false) {
        if (allow_empty) {
            T opt_val = Compare()(val, T(0)) ? val : T(0);
            return {val, opt_val, opt_val, opt_val};
        }
        return {val, val, val, val};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MIN_SUBARRAY_HPP
