#ifndef M1UNE_MONOID_POWER_HPP
#define M1UNE_MONOID_POWER_HPP 1

#include "concept.hpp"

namespace m1une {
namespace monoid {

// Computes a^n (a * a * ... * a, n times) for an element 'a' in Monoid 'M'.
// Uses binary exponentiation to achieve O(log n) time complexity.
// The template parameter 'M' is constrained by the 'IsMonoid' concept.
template <IsMonoid M>
constexpr typename M::value_type power(typename M::value_type a, long long n) {
    typename M::value_type res = M::id();
    while (n > 0) {
        if (n & 1) {
            res = M::op(res, a);
        }
        a = M::op(a, a);
        n >>= 1;
    }
    return res;
}

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_POWER_HPP
