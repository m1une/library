#ifndef M1UNE_MATRIX_LINEAR_ALGEBRA_HPP
#define M1UNE_MATRIX_LINEAR_ALGEBRA_HPP 1

#include <optional>
#include <type_traits>
#include <vector>

#include "matrix.hpp"

namespace m1une {
namespace matrix {

template <class T>
constexpr T default_epsilon() {
    if constexpr (std::is_floating_point_v<T>) {
        return T(1e-10);
    } else {
        return T();
    }
}

namespace detail {

template <class T>
T matrix_abs(T value) {
    return value < T() ? T() - value : value;
}

template <class T>
bool is_zero(const T& value, const T& eps) {
    if constexpr (std::is_floating_point_v<T>) {
        return matrix_abs(value) <= eps;
    } else {
        (void)eps;
        return value == T();
    }
}

template <class T>
int choose_pivot(const Matrix<T>& matrix, int first_row, int col, const T& eps) {
    int pivot = -1;
    if constexpr (std::is_floating_point_v<T>) {
        for (int row = first_row; row < matrix.rows(); row++) {
            if (is_zero(matrix[row][col], eps)) continue;
            if (pivot == -1 || matrix_abs(matrix[pivot][col]) < matrix_abs(matrix[row][col])) {
                pivot = row;
            }
        }
    } else {
        for (int row = first_row; row < matrix.rows(); row++) {
            if (!is_zero(matrix[row][col], eps)) {
                pivot = row;
                break;
            }
        }
    }
    return pivot;
}

template <class T>
std::vector<int> row_reduce(Matrix<T>& matrix, int pivot_col_limit, const T& eps,
                            bool reduced) {
    std::vector<int> pivot_columns;
    int pivot_row = 0;
    for (int col = 0; col < pivot_col_limit && pivot_row < matrix.rows(); col++) {
        int pivot = choose_pivot(matrix, pivot_row, col, eps);
        if (pivot == -1) continue;
        matrix.swap_rows(pivot_row, pivot);

        const T pivot_value = matrix[pivot_row][col];
        if (reduced) {
            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j] /= pivot_value;
        }

        const int first_row = reduced ? 0 : pivot_row + 1;
        for (int row = first_row; row < matrix.rows(); row++) {
            if (row == pivot_row || is_zero(matrix[row][col], eps)) continue;
            T factor = matrix[row][col];
            if (!reduced) factor /= pivot_value;
            matrix[row][col] = T();
            for (int j = col + 1; j < matrix.cols(); j++) {
                matrix[row][j] -= factor * matrix[pivot_row][j];
            }
        }

        pivot_columns.push_back(col);
        pivot_row++;
    }

    if constexpr (std::is_floating_point_v<T>) {
        for (T& value : matrix.data()) {
            if (is_zero(value, eps)) value = T();
        }
    }
    return pivot_columns;
}

}  // namespace detail

template <class T>
struct RowReduction {
    Matrix<T> matrix;
    std::vector<int> pivot_columns;

    int rank() const {
        return int(pivot_columns.size());
    }
};

template <class T>
RowReduction<T> reduced_row_echelon_form(Matrix<T> matrix,
                                         T eps = default_epsilon<T>()) {
    RowReduction<T> result;
    result.pivot_columns = detail::row_reduce(matrix, matrix.cols(), eps, true);
    result.matrix = std::move(matrix);
    return result;
}

template <class T>
int matrix_rank(Matrix<T> matrix, T eps = default_epsilon<T>()) {
    return int(detail::row_reduce(matrix, matrix.cols(), eps, false).size());
}

template <class T>
T determinant(Matrix<T> matrix, T eps = default_epsilon<T>()) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    T result = T(1);
    bool negate = false;

    for (int col = 0; col < size; col++) {
        int pivot = detail::choose_pivot(matrix, col, col, eps);
        if (pivot == -1) return T();
        if (pivot != col) {
            matrix.swap_rows(pivot, col);
            negate = !negate;
        }

        const T pivot_value = matrix[col][col];
        result *= pivot_value;
        for (int row = col + 1; row < size; row++) {
            if (detail::is_zero(matrix[row][col], eps)) continue;
            const T factor = matrix[row][col] / pivot_value;
            matrix[row][col] = T();
            for (int j = col + 1; j < size; j++) {
                matrix[row][j] -= factor * matrix[col][j];
            }
        }
    }
    return negate ? T() - result : result;
}

template <class T>
std::optional<Matrix<T>> inverse(const Matrix<T>& matrix,
                                 T eps = default_epsilon<T>()) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    Matrix<T> augmented(size, size * 2);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            augmented[row][col] = matrix[row][col];
        }
        augmented[row][size + row] = T(1);
    }

    const std::vector<int> pivots = detail::row_reduce(augmented, size, eps, true);
    if (int(pivots.size()) != size) return std::nullopt;

    Matrix<T> result(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] = augmented[row][size + col];
        }
    }
    return result;
}

template <class T>
struct LinearSystemResult {
    bool consistent = false;
    std::vector<T> particular_solution;
    std::vector<std::vector<T>> nullspace_basis;
    std::vector<int> pivot_columns;

    int rank() const {
        return int(pivot_columns.size());
    }

    int nullity() const {
        return consistent ? int(nullspace_basis.size()) : 0;
    }

    bool has_unique_solution() const {
        return consistent && nullspace_basis.empty();
    }
};

template <class T>
LinearSystemResult<T> solve_linear_system(const Matrix<T>& coefficients,
                                          const std::vector<T>& constants,
                                          T eps = default_epsilon<T>()) {
    assert(coefficients.rows() == int(constants.size()));
    const int equation_count = coefficients.rows();
    const int variable_count = coefficients.cols();
    Matrix<T> augmented(equation_count, variable_count + 1);
    for (int row = 0; row < equation_count; row++) {
        for (int col = 0; col < variable_count; col++) {
            augmented[row][col] = coefficients[row][col];
        }
        augmented[row][variable_count] = constants[std::size_t(row)];
    }

    LinearSystemResult<T> result;
    result.pivot_columns =
        detail::row_reduce(augmented, variable_count, eps, true);

    for (int row = result.rank(); row < equation_count; row++) {
        bool zero_left = true;
        for (int col = 0; col < variable_count; col++) {
            if (!detail::is_zero(augmented[row][col], eps)) {
                zero_left = false;
                break;
            }
        }
        if (zero_left && !detail::is_zero(augmented[row][variable_count], eps)) {
            return result;
        }
    }

    result.consistent = true;
    result.particular_solution.assign(std::size_t(variable_count), T());
    std::vector<bool> is_pivot(std::size_t(variable_count), false);
    for (int row = 0; row < result.rank(); row++) {
        const int col = result.pivot_columns[std::size_t(row)];
        is_pivot[std::size_t(col)] = true;
        result.particular_solution[std::size_t(col)] = augmented[row][variable_count];
    }

    for (int free_col = 0; free_col < variable_count; free_col++) {
        if (is_pivot[std::size_t(free_col)]) continue;
        std::vector<T> direction(static_cast<std::size_t>(variable_count));
        direction[std::size_t(free_col)] = T(1);
        for (int row = 0; row < result.rank(); row++) {
            const int pivot_col = result.pivot_columns[std::size_t(row)];
            direction[std::size_t(pivot_col)] = T() - augmented[row][free_col];
        }
        result.nullspace_basis.push_back(std::move(direction));
    }
    return result;
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_LINEAR_ALGEBRA_HPP
