#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP
#define M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP 1

#include <utility>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeAffineRangeSumOfSquaresNode {
    T sum_sq;
    T sum;
    long long size;
};

// Designed to work with standard scalars or Modint types
template <typename T>
struct RangeAffineRangeSumOfSquares {
    using value_type = RangeAffineRangeSumOfSquaresNode<T>;
    using operator_type = std::pair<T, T>; // {a, b} for f(x) = a*x + b

    // Value Monoid (Sum of Squares, Sum, Size)
    static constexpr value_type id() { return {T(0), T(0), 0}; }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.sum_sq + b.sum_sq, a.sum + b.sum, a.size + b.size};
    }

    // Operator Monoid (Affine Composition)
    // f(x) = a1*x + b1, g(x) = a2*x + b2
    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)
    static constexpr operator_type op_id() { return {T(1), T(0)}; }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return {f.first * g.first, f.first * g.second + f.second};
    }

    // Mapping
    // \sum (a*x_i + b)^2 = a^2 \sum x_i^2 + 2ab \sum x_i + b^2 * size
    // \sum (a*x_i + b)   = a \sum x_i + b * size
    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.size == 0) return x;
        T a = f.first;
        T b = f.second;
        T sz = static_cast<T>(x.size);
        
        return {
            a * a * x.sum_sq + T(2) * a * b * x.sum + b * b * sz,
            a * x.sum + b * sz,
            x.size
        };
    }

    // Helper for initializing a leaf node
    static constexpr value_type make(const T& val) {
        return {val * val, val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_OF_SQUARES_HPP
