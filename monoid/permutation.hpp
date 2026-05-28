#ifndef M1UNE_MONOID_PERMUTATION_HPP
#define M1UNE_MONOID_PERMUTATION_HPP 1

#include <array>
#include <numeric>

namespace m1une {
namespace monoid {

// Monoid for Permutation Composition.
// Represents a permutation of fixed size N.
template <int N>
struct Permutation {
    using value_type = std::array<int, N>;

    // The identity element is the identity permutation (0, 1, 2, ..., N-1).
    static constexpr value_type id() {
        value_type res{};
        std::iota(res.begin(), res.end(), 0);
        return res;
    }

    // Composes two permutations (applies 'a' then 'b').
    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            res[i] = b[a[i]];
        }
        return res;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_PERMUTATION_HPP
