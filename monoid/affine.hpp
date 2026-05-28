#ifndef M1UNE_MONOID_AFFINE_HPP
#define M1UNE_MONOID_AFFINE_HPP 1

#include <utility>

namespace m1une {
namespace monoid {

// Monoid for affine transformations f(x) = ax + b.
// Represented as a pair {a, b}.
template <typename T>
struct Affine {
    using value_type = std::pair<T, T>;

    // The identity transformation is f(x) = 1*x + 0.
    static constexpr value_type id() { 
        return {T(1), T(0)}; 
    }

    // Composes two affine transformations.
    // f(g(x)) where f = a, g = b.
    // a.first * (b.first * x + b.second) + a.second
    // = (a.first * b.first) * x + (a.first * b.second + a.second)
    static constexpr value_type op(const value_type& a, const value_type& b) { 
        return {a.first * b.first, a.first * b.second + a.second}; 
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_AFFINE_HPP
