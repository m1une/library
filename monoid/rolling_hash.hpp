#ifndef M1UNE_MONOID_ROLLING_HASH_HPP
#define M1UNE_MONOID_ROLLING_HASH_HPP 1

#include <utility>
#include "../string/rolling_hash.hpp"

namespace m1une {
namespace monoid {

// Monoid for Dynamic Rolling Hash (String Concatenation).
// Acts as a clean wrapper around the mathematical logic defined in string::RollingHash.
//
// [Important Usage Note for Contests]
// To initialize a leaf node for a single character S[i], use the `make` method:
// 
// Example:
//   std::vector<RH::value_type> init_data(N);
//   for (int i = 0; i < N; ++i) {
//       init_data[i] = RH::make(S[i]); 
//   }
//   Segtree<RH> seg(init_data);
template <long long Base, long long Mod>
struct RollingHash {
    using StringRH = m1une::string::RollingHash<Base, Mod>;
    using value_type = std::pair<long long, long long>;

    // The identity element represents an empty string.
    static constexpr value_type id() {
        return {0LL, 1LL};
    }

    // Combines two hashes by delegating to string::RollingHash.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {
            StringRH::combine(a.first, b.first, b.second),
            (static_cast<__int128_t>(a.second) * b.second) % Mod
        };
    }

    // Helper to securely create a monoid element from a single character (or integer).
    // Delegates to string::RollingHash to hide the base/mod mechanics.
    static constexpr value_type make(long long c) {
        return StringRH::make_single(c);
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_ROLLING_HASH_HPP
