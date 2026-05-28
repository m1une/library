#ifndef M1UNE_MONOID_BRACKET_HPP
#define M1UNE_MONOID_BRACKET_HPP 1

#include <algorithm>

namespace m1une {
namespace monoid {

struct BracketNode {
    int matched;
    int unmatched_right; // Count of unmatched ')'
    int unmatched_left;  // Count of unmatched '('
};

// Monoid for matching parentheses (Bracket Sequences).
struct Bracket {
    using value_type = BracketNode;

    // The identity element is an empty sequence.
    static constexpr value_type id() {
        return {0, 0, 0};
    }

    // Merges two bracket sequences.
    // The unmatched '(' from the left perfectly matches the unmatched ')' from the right.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        int match = std::min(a.unmatched_left, b.unmatched_right);
        return {
            a.matched + b.matched + match,
            a.unmatched_right + b.unmatched_right - match,
            a.unmatched_left + b.unmatched_left - match
        };
    }

    // Helper to securely create a leaf node from a single character.
    static constexpr value_type make(char c) {
        if (c == '(') return {0, 0, 1};
        if (c == ')') return {0, 1, 0};
        return {0, 0, 0};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_BRACKET_HPP
