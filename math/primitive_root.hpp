#ifndef M1UNE_MATH_PRIMITIVE_ROOT_HPP
#define M1UNE_MATH_PRIMITIVE_ROOT_HPP 1

#include <cassert>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

#include "prime_factorization.hpp"

namespace m1une {
namespace math {

inline bool has_primitive_root(uint64_t mod) {
    if (mod == 2 || mod == 4) return true;
    if (mod < 2) return false;

    uint64_t odd_part = mod;
    if ((odd_part & 1) == 0) {
        odd_part >>= 1;
        if ((odd_part & 1) == 0) return false;
    }

    return prime_factorize(odd_part).size() == 1;
}

// Returns the smallest positive primitive root modulo mod.
// Returns 0 when no primitive root exists.
inline uint64_t primitive_root(uint64_t mod) {
    assert(mod >= 2);
    if (mod == 2) return 1;
    if (!has_primitive_root(mod)) return 0;

    const uint64_t phi = euler_phi(mod);
    const std::vector<std::pair<uint64_t, int>> factors = prime_factorize(phi);
    for (uint64_t candidate = 2; candidate < mod; candidate++) {
        if (std::gcd(candidate, mod) != 1) continue;

        bool generator = true;
        for (const auto& factor : factors) {
            if (internal::power_mod(candidate, phi / factor.first, mod) == 1) {
                generator = false;
                break;
            }
        }
        if (generator) return candidate;
    }
    return 0;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PRIMITIVE_ROOT_HPP
