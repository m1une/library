#ifndef M1UNE_OPTIMIZATION_SIMPLEX_HPP
#define M1UNE_OPTIMIZATION_SIMPLEX_HPP 1

#include <cassert>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace optimization {

enum class SimplexStatus {
    Optimal,
    Infeasible,
    Unbounded,
};

template <class T>
struct SimplexResult {
    SimplexStatus status;
    T objective_value;
    std::vector<T> variables;

    bool is_optimal() const { return status == SimplexStatus::Optimal; }
    bool is_infeasible() const { return status == SimplexStatus::Infeasible; }
    bool is_unbounded() const { return status == SimplexStatus::Unbounded; }
};

namespace detail {

template <class T>
T simplex_abs(T x) {
    return x < T() ? -x : x;
}

template <class T>
struct SimplexTableau {
    int constraint_count;
    int variable_count;
    T eps;
    std::vector<int> basis;
    std::vector<int> nonbasis;
    std::vector<std::vector<T>> table;

    SimplexTableau(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                   const std::vector<T>& c, T epsilon)
        : constraint_count(int(b.size())),
          variable_count(int(c.size())),
          eps(epsilon),
          basis(constraint_count),
          nonbasis(variable_count + 1),
          table(constraint_count + 2, std::vector<T>(variable_count + 2, T())) {
        for (int i = 0; i < constraint_count; i++) {
            for (int j = 0; j < variable_count; j++) table[i][j] = a[i][j];
        }
        for (int i = 0; i < constraint_count; i++) {
            basis[i] = variable_count + i;
            table[i][artificial_col()] = T(-1);
            table[i][rhs_col()] = b[i];
        }
        for (int j = 0; j < variable_count; j++) {
            nonbasis[j] = j;
            table[objective_row()][j] = -c[j];
        }
        nonbasis[artificial_col()] = artificial_id();
        table[auxiliary_row()][artificial_col()] = T(1);
    }

    int objective_row() const { return constraint_count; }
    int auxiliary_row() const { return constraint_count + 1; }
    int artificial_col() const { return variable_count; }
    int rhs_col() const { return variable_count + 1; }
    int artificial_id() const { return -1; }

    T normalize(T x) const {
        return simplex_abs(x) <= eps ? T() : x;
    }

    bool less_with_tie(int row, int lhs, int rhs) const {
        if (table[row][lhs] < table[row][rhs] - eps) return true;
        if (table[row][rhs] < table[row][lhs] - eps) return false;
        return nonbasis[lhs] < nonbasis[rhs];
    }

    bool better_leaving_row(int lhs, int rhs, int entering_col) const {
        T lhs_ratio = table[lhs][rhs_col()] / table[lhs][entering_col];
        T rhs_ratio = table[rhs][rhs_col()] / table[rhs][entering_col];
        if (lhs_ratio < rhs_ratio - eps) return true;
        if (rhs_ratio < lhs_ratio - eps) return false;
        return basis[lhs] < basis[rhs];
    }

    void pivot(int leaving_row, int entering_col) {
        T inverse = T(1) / table[leaving_row][entering_col];
        for (int i = 0; i < constraint_count + 2; i++) {
            if (i == leaving_row) continue;
            for (int j = 0; j < variable_count + 2; j++) {
                if (j == entering_col) continue;
                table[i][j] -= table[leaving_row][j] * table[i][entering_col] * inverse;
            }
        }
        for (int j = 0; j < variable_count + 2; j++) {
            if (j != entering_col) table[leaving_row][j] *= inverse;
        }
        for (int i = 0; i < constraint_count + 2; i++) {
            if (i != leaving_row) table[i][entering_col] *= -inverse;
        }
        table[leaving_row][entering_col] = inverse;
        std::swap(basis[leaving_row], nonbasis[entering_col]);
    }

    bool run_simplex(int row) {
        while (true) {
            int entering_col = -1;
            for (int j = 0; j <= variable_count; j++) {
                if (nonbasis[j] == artificial_id()) continue;
                if (entering_col == -1 || less_with_tie(row, j, entering_col)) entering_col = j;
            }
            if (entering_col == -1 || table[row][entering_col] >= -eps) return true;

            int leaving_row = -1;
            for (int i = 0; i < constraint_count; i++) {
                if (table[i][entering_col] <= eps) continue;
                if (leaving_row == -1 || better_leaving_row(i, leaving_row, entering_col)) {
                    leaving_row = i;
                }
            }
            if (leaving_row == -1) return false;
            pivot(leaving_row, entering_col);
        }
    }

    bool make_feasible() {
        int leaving_row = 0;
        for (int i = 1; i < constraint_count; i++) {
            if (table[i][rhs_col()] < table[leaving_row][rhs_col()]) leaving_row = i;
        }
        if (constraint_count == 0 || table[leaving_row][rhs_col()] >= -eps) return true;

        pivot(leaving_row, artificial_col());
        if (!run_simplex(auxiliary_row())) return false;
        if (table[auxiliary_row()][rhs_col()] < -eps) return false;

        for (int i = 0; i < constraint_count; i++) {
            if (basis[i] != artificial_id()) continue;
            int entering_col = -1;
            for (int j = 0; j <= variable_count; j++) {
                if (nonbasis[j] == artificial_id()) continue;
                if (simplex_abs(table[i][j]) <= eps) continue;
                if (entering_col == -1 || nonbasis[j] < nonbasis[entering_col]) entering_col = j;
            }
            if (entering_col != -1) pivot(i, entering_col);
        }
        return true;
    }

    SimplexStatus solve(std::vector<T>& variables, T& objective_value) {
        if (!make_feasible()) return SimplexStatus::Infeasible;
        if (!run_simplex(objective_row())) return SimplexStatus::Unbounded;

        variables.assign(variable_count, T());
        for (int i = 0; i < constraint_count; i++) {
            if (0 <= basis[i] && basis[i] < variable_count) {
                variables[basis[i]] = normalize(table[i][rhs_col()]);
            }
        }
        objective_value = normalize(table[objective_row()][rhs_col()]);
        return SimplexStatus::Optimal;
    }
};

}  // namespace detail

template <class T>
SimplexResult<T> simplex_maximize(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                                  const std::vector<T>& c, T eps = T(1e-10)) {
    static_assert(std::is_floating_point_v<T>, "simplex requires a floating-point type");
    assert(int(a.size()) == int(b.size()));
    for (const auto& row : a) assert(int(row.size()) == int(c.size()));
    assert(eps > T());

    SimplexResult<T> result;
    result.status = SimplexStatus::Infeasible;
    result.objective_value = std::numeric_limits<T>::quiet_NaN();
    result.variables.assign(c.size(), T());

    detail::SimplexTableau<T> solver(a, b, c, eps);
    result.status = solver.solve(result.variables, result.objective_value);
    if (result.status == SimplexStatus::Infeasible) {
        result.objective_value = std::numeric_limits<T>::quiet_NaN();
    } else if (result.status == SimplexStatus::Unbounded) {
        result.objective_value = std::numeric_limits<T>::infinity();
    }
    return result;
}

template <class T>
SimplexResult<T> simplex_minimize(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                                  const std::vector<T>& c, T eps = T(1e-10)) {
    std::vector<T> negated = c;
    for (T& x : negated) x = -x;
    auto result = simplex_maximize(a, b, negated, eps);
    if (result.status == SimplexStatus::Optimal) {
        result.objective_value = -result.objective_value;
    } else if (result.status == SimplexStatus::Unbounded) {
        result.objective_value = -std::numeric_limits<T>::infinity();
    }
    return result;
}

template <class T>
SimplexResult<T> simplex(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                         const std::vector<T>& c, T eps = T(1e-10)) {
    return simplex_maximize(a, b, c, eps);
}

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_SIMPLEX_HPP
