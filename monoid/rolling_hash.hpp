#ifndef M1UNE_MONOID_ROLLING_HASH_HPP
#define M1UNE_MONOID_ROLLING_HASH_HPP 1

#include <utility>

namespace m1une {
namespace monoid {

// Monoid for Dynamic Rolling Hash (String Concatenation).
// Represented as a pair {hash_value, base_power}.
// 'Base' is the hash base, 'Mod' is the modulo.
//
// [Important Usage Note for Contests]
// To initialize a Segment Tree with a string S, the leaf node for a single
// character S[i] MUST be initialized as: {S[i], Base % Mod}.
// 
// Example (if Base = 10007):
//   std::vector<RH::value_type> init_data(N);
//   for (int i = 0; i < N; ++i) {
//       init_data[i] = {S[i], 10007}; // {char_code, Base^1 % Mod}
//   }
//   Segtree<RH> seg(init_data);
template <long long Base, long long Mod>
struct RollingHash {
    using value_type = std::pair<long long, long long>;

    // The identity element represents an empty string.
    // Hash is 0, and Base^0 % Mod is 1.
    static constexpr value_type id() {
        return {0LL, 1LL};
    }

    // Combines two hashes (concatenates string 'b' to the right of string 'a').
    // new_hash = (a.hash * b.base_power + b.hash) % Mod
    // new_base_power = (a.base_power * b.base_power) % Mod
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {
            (a.first * b.second + b.first) % Mod,
            (a.second * b.second) % Mod
        };
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ROLLING_HASH_HPP
