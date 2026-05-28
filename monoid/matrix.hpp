#ifndef M1UNE_MONOID_MATRIX_HPP
#define M1UNE_MONOID_MATRIX_HPP 1

#include <array>

namespace m1une {
namespace monoid {

// Monoid for fixed-size square matrix multiplication.
template <typename T, int N>
struct Matrix {
    using value_type = std::array<std::array<T, N>, N>;

    // The identity element is the identity matrix.
    static constexpr value_type id() {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            res[i][i] = T(1);
        }
        return res;
    }

    // Multiplies two matrices: a * b
    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res{};
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                for (int j = 0; j < N; ++j) {
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_MATRIX_HPP
