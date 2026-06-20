#ifndef M1UNE_OPTIMIZATION_INTEGER_LP_HPP
#define M1UNE_OPTIMIZATION_INTEGER_LP_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <type_traits>
#include <vector>

#include "simplex.hpp"

namespace m1une {
namespace optimization {

enum class IntegerLpStatus {
    Optimal,
    Infeasible,
    Unbounded,
};

template <class T>
struct IntegerLpResult {
    IntegerLpStatus status;
    T objective_value;
    std::vector<T> variables;

    bool is_optimal() const { return status == IntegerLpStatus::Optimal; }
    bool is_infeasible() const { return status == IntegerLpStatus::Infeasible; }
    bool is_unbounded() const { return status == IntegerLpStatus::Unbounded; }
};

namespace detail {

template <class T>
struct IntegerLpSolver {
    using Real = long double;

    struct Node {
        std::vector<std::vector<Real>> a;
        std::vector<Real> b;
    };

    int variable_count;
    bool maximize;
    Real eps;
    std::vector<T> objective;
    std::vector<Real> relaxation_objective;
    Node initial_node;

    bool has_incumbent = false;
    T best_value = T();
    std::vector<T> best_variables;

    IntegerLpSolver(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                    const std::vector<T>& c, bool is_maximize, Real epsilon)
        : variable_count(int(c.size())),
          maximize(is_maximize),
          eps(epsilon),
          objective(c),
          relaxation_objective(c.size(), Real()),
          initial_node() {
        initial_node.a.assign(a.size(), std::vector<Real>(variable_count, Real()));
        initial_node.b.assign(b.size(), Real());
        for (int i = 0; i < int(a.size()); i++) {
            for (int j = 0; j < variable_count; j++) initial_node.a[i][j] = Real(a[i][j]);
            initial_node.b[i] = Real(b[i]);
        }
        Real sign = maximize ? Real(1) : Real(-1);
        for (int j = 0; j < variable_count; j++) relaxation_objective[j] = sign * Real(c[j]);
    }

    Real abs_value(Real x) const {
        return x < Real() ? -x : x;
    }

    bool better_value(T lhs, T rhs) const {
        return maximize ? lhs > rhs : lhs < rhs;
    }

    bool can_prune_by_bound(Real relaxation_value) const {
        if (!has_incumbent) return false;
        Real signed_best = maximize ? Real(best_value) : -Real(best_value);
        return relaxation_value <= signed_best + eps;
    }

    T evaluate(const std::vector<T>& variables) const {
        T result = T();
        for (int i = 0; i < variable_count; i++) result += objective[i] * variables[i];
        return result;
    }

    bool round_solution(const std::vector<Real>& real_variables, std::vector<T>& variables) const {
        variables.assign(variable_count, T());
        for (int i = 0; i < variable_count; i++) {
            Real value = real_variables[i];
            if (value < -eps) return false;
            Real rounded = std::round(value);
            if (abs_value(value - rounded) > eps) return false;
            variables[i] = static_cast<T>(rounded);
        }
        return true;
    }

    int find_fractional_variable(const std::vector<Real>& real_variables) const {
        int result = -1;
        Real best_distance = eps;
        for (int i = 0; i < variable_count; i++) {
            Real value = real_variables[i];
            Real rounded = std::round(value);
            Real distance = abs_value(value - rounded);
            if (distance > best_distance) {
                best_distance = distance;
                result = i;
            }
        }
        return result;
    }

    Node with_upper_bound(const Node& node, int variable, T bound) const {
        Node result = node;
        result.a.emplace_back(variable_count, Real());
        result.a.back()[variable] = Real(1);
        result.b.push_back(Real(bound));
        return result;
    }

    Node with_lower_bound(const Node& node, int variable, T bound) const {
        Node result = node;
        result.a.emplace_back(variable_count, Real());
        result.a.back()[variable] = Real(-1);
        result.b.push_back(-Real(bound));
        return result;
    }

    void push_branches(std::vector<Node>& stack, const Node& node, int variable, Real value) const {
        Real floor_value = std::floor(value);
        Real ceil_value = std::ceil(value);
        T upper_bound = static_cast<T>(floor_value);
        T lower_bound = static_cast<T>(ceil_value);

        bool has_upper_branch = upper_bound >= T();
        bool prefer_lower_branch = relaxation_objective[variable] >= -eps;

        if (prefer_lower_branch) {
            if (has_upper_branch) stack.push_back(with_upper_bound(node, variable, upper_bound));
            stack.push_back(with_lower_bound(node, variable, lower_bound));
        } else {
            stack.push_back(with_lower_bound(node, variable, lower_bound));
            if (has_upper_branch) stack.push_back(with_upper_bound(node, variable, upper_bound));
        }
    }

    bool has_positive_direction(const Node& node) const {
        std::vector<std::vector<Real>> direction_a = node.a;
        std::vector<Real> direction_b(node.b.size(), Real());

        std::vector<Real> objective_row(variable_count, Real());
        for (int i = 0; i < variable_count; i++) objective_row[i] = -relaxation_objective[i];
        direction_a.push_back(objective_row);
        direction_b.push_back(Real(-1));

        std::vector<Real> zero_objective(variable_count, Real());
        auto result = simplex_maximize(direction_a, direction_b, zero_objective, eps);
        return result.is_optimal();
    }

    bool find_integer_feasible(const Node& start, std::vector<T>& feasible_variables) const {
        std::vector<Node> stack;
        stack.push_back(start);
        std::vector<Real> zero_objective(variable_count, Real());

        while (!stack.empty()) {
            Node node = stack.back();
            stack.pop_back();

            auto relaxation = simplex_maximize(node.a, node.b, zero_objective, eps);
            if (relaxation.is_infeasible()) continue;
            if (relaxation.is_unbounded()) continue;

            if (round_solution(relaxation.variables, feasible_variables)) return true;

            int variable = find_fractional_variable(relaxation.variables);
            if (variable == -1) continue;
            push_branches(stack, node, variable, relaxation.variables[variable]);
        }
        return false;
    }

    void update_incumbent(const std::vector<T>& variables) {
        T value = evaluate(variables);
        if (!has_incumbent || better_value(value, best_value)) {
            has_incumbent = true;
            best_value = value;
            best_variables = variables;
        }
    }

    IntegerLpResult<T> make_infeasible_result() const {
        IntegerLpResult<T> result;
        result.status = IntegerLpStatus::Infeasible;
        result.objective_value = T();
        result.variables.assign(variable_count, T());
        return result;
    }

    IntegerLpResult<T> make_unbounded_result(const std::vector<T>& variables) const {
        IntegerLpResult<T> result;
        result.status = IntegerLpStatus::Unbounded;
        result.objective_value =
            maximize ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest();
        result.variables = variables;
        return result;
    }

    IntegerLpResult<T> make_optimal_result() const {
        IntegerLpResult<T> result;
        result.status = IntegerLpStatus::Optimal;
        result.objective_value = best_value;
        result.variables = best_variables;
        return result;
    }

    IntegerLpResult<T> solve() {
        std::vector<Node> stack;
        stack.push_back(initial_node);

        while (!stack.empty()) {
            Node node = stack.back();
            stack.pop_back();

            auto relaxation = simplex_maximize(node.a, node.b, relaxation_objective, eps);
            if (relaxation.is_infeasible()) continue;

            if (relaxation.is_unbounded()) {
                std::vector<T> feasible_variables;
                if (has_positive_direction(node) && find_integer_feasible(node, feasible_variables)) {
                    return make_unbounded_result(feasible_variables);
                }
                continue;
            }

            if (can_prune_by_bound(relaxation.objective_value)) continue;

            std::vector<T> integer_variables;
            if (round_solution(relaxation.variables, integer_variables)) {
                update_incumbent(integer_variables);
                continue;
            }

            int variable = find_fractional_variable(relaxation.variables);
            if (variable == -1) continue;
            push_branches(stack, node, variable, relaxation.variables[variable]);
        }

        if (!has_incumbent) return make_infeasible_result();
        return make_optimal_result();
    }
};

}  // namespace detail

template <class T>
IntegerLpResult<T> integer_lp_maximize(const std::vector<std::vector<T>>& a,
                                       const std::vector<T>& b, const std::vector<T>& c,
                                       long double eps = 1e-10L) {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>,
                  "integer_lp requires a signed integer type");
    assert(int(a.size()) == int(b.size()));
    for (const auto& row : a) assert(int(row.size()) == int(c.size()));
    assert(eps > 0);

    detail::IntegerLpSolver<T> solver(a, b, c, true, eps);
    return solver.solve();
}

template <class T>
IntegerLpResult<T> integer_lp_minimize(const std::vector<std::vector<T>>& a,
                                       const std::vector<T>& b, const std::vector<T>& c,
                                       long double eps = 1e-10L) {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>,
                  "integer_lp requires a signed integer type");
    assert(int(a.size()) == int(b.size()));
    for (const auto& row : a) assert(int(row.size()) == int(c.size()));
    assert(eps > 0);

    detail::IntegerLpSolver<T> solver(a, b, c, false, eps);
    return solver.solve();
}

template <class T>
IntegerLpResult<T> integer_lp(const std::vector<std::vector<T>>& a, const std::vector<T>& b,
                              const std::vector<T>& c, long double eps = 1e-10L) {
    return integer_lp_maximize(a, b, c, eps);
}

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_INTEGER_LP_HPP
