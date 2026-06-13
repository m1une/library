#ifndef M1UNE_MONOID_MAX_PLUS_MATRIX_HPP
#define M1UNE_MONOID_MAX_PLUS_MATRIX_HPP 1

#include <algorithm>
#include <array>
#include <limits>

namespace m1une {
namespace monoid {

// Monoid for fixed-size square matrix multiplication over the Max-Plus semiring.
// Useful for Dynamic DP (Maximization) and Longest Path problems.
template <typename T, int N, T MinInf = std::numeric_limits<T>::lowest() / 2>
struct MaxPlusMatrix {
    using value_type = std::array<std::array<T, N>, N>;

    // The identity matrix for max-plus algebra.
    // Diagonal elements are 0 (identity for addition).
    // Off-diagonal elements are MinInf (identity for max).
    static constexpr value_type id() {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = (i == j) ? T(0) : MinInf;
            }
        }
        return res;
    }

    // Multiplies two max-plus matrices: c_{i, j} = max_k (a_{i, k} + b_{k, j})
    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = MinInf;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                if (a[i][k] == MinInf) continue;
                for (int j = 0; j < N; ++j) {
                    if (b[k][j] == MinInf) continue;
                    res[i][j] = std::max(res[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return res;
    }

    // Helper to securely create a matrix initialized with MinInf.
    static constexpr value_type make_inf() {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = MinInf;
            }
        }
        return res;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MAX_PLUS_MATRIX_HPP
