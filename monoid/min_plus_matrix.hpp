#ifndef M1UNE_MONOID_MIN_PLUS_MATRIX_HPP
#define M1UNE_MONOID_MIN_PLUS_MATRIX_HPP 1

#include <array>
#include <algorithm>
#include <limits>

namespace m1une {
namespace monoid {

// Monoid for fixed-size square matrix multiplication over the Min-Plus (Tropical) semiring.
// Useful for Dynamic DP (Minimization) and Shortest Path problems.
template <typename T, int N, T Inf = std::numeric_limits<T>::max() / 2>
struct MinPlusMatrix {
    using value_type = std::array<std::array<T, N>, N>;

    // The identity matrix for min-plus algebra.
    // Diagonal elements are 0 (identity for addition).
    // Off-diagonal elements are Inf (identity for min).
    static constexpr value_type id() {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = (i == j) ? T(0) : Inf;
            }
        }
        return res;
    }

    // Multiplies two min-plus matrices: c_{i, j} = min_k (a_{i, k} + b_{k, j})
    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = Inf;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                if (a[i][k] == Inf) continue;
                for (int j = 0; j < N; ++j) {
                    if (b[k][j] == Inf) continue;
                    res[i][j] = std::min(res[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return res;
    }

    // Helper to securely create a matrix initialized with Inf.
    static constexpr value_type make_inf() {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = Inf;
            }
        }
        return res;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MIN_PLUS_MATRIX_HPP
