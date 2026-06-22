---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/simplex.hpp
    title: Simplex Algorithm
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/project_selection.test.cpp
    title: verify/optimization/project_selection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/simplex.test.cpp
    title: verify/optimization/simplex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"optimization/integer_lp.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\n#line 1 \"optimization/simplex.hpp\"\n\n\n\n#line 7 \"optimization/simplex.hpp\"\
    \n#include <utility>\n#line 9 \"optimization/simplex.hpp\"\n\nnamespace m1une\
    \ {\nnamespace optimization {\n\nenum class SimplexStatus {\n    Optimal,\n  \
    \  Infeasible,\n    Unbounded,\n};\n\ntemplate <class T>\nstruct SimplexResult\
    \ {\n    SimplexStatus status;\n    T objective_value;\n    std::vector<T> variables;\n\
    \n    bool is_optimal() const { return status == SimplexStatus::Optimal; }\n \
    \   bool is_infeasible() const { return status == SimplexStatus::Infeasible; }\n\
    \    bool is_unbounded() const { return status == SimplexStatus::Unbounded; }\n\
    };\n\nnamespace detail {\n\ntemplate <class T>\nT simplex_abs(T x) {\n    return\
    \ x < T() ? -x : x;\n}\n\ntemplate <class T>\nstruct SimplexTableau {\n    int\
    \ constraint_count;\n    int variable_count;\n    T eps;\n    std::vector<int>\
    \ basis;\n    std::vector<int> nonbasis;\n    std::vector<std::vector<T>> table;\n\
    \n    SimplexTableau(const std::vector<std::vector<T>>& a, const std::vector<T>&\
    \ b,\n                   const std::vector<T>& c, T epsilon)\n        : constraint_count(int(b.size())),\n\
    \          variable_count(int(c.size())),\n          eps(epsilon),\n         \
    \ basis(constraint_count),\n          nonbasis(variable_count + 1),\n        \
    \  table(constraint_count + 2, std::vector<T>(variable_count + 2, T())) {\n  \
    \      for (int i = 0; i < constraint_count; i++) {\n            for (int j =\
    \ 0; j < variable_count; j++) table[i][j] = a[i][j];\n        }\n        for (int\
    \ i = 0; i < constraint_count; i++) {\n            basis[i] = variable_count +\
    \ i;\n            table[i][artificial_col()] = T(-1);\n            table[i][rhs_col()]\
    \ = b[i];\n        }\n        for (int j = 0; j < variable_count; j++) {\n   \
    \         nonbasis[j] = j;\n            table[objective_row()][j] = -c[j];\n \
    \       }\n        nonbasis[artificial_col()] = artificial_id();\n        table[auxiliary_row()][artificial_col()]\
    \ = T(1);\n    }\n\n    int objective_row() const { return constraint_count; }\n\
    \    int auxiliary_row() const { return constraint_count + 1; }\n    int artificial_col()\
    \ const { return variable_count; }\n    int rhs_col() const { return variable_count\
    \ + 1; }\n    int artificial_id() const { return -1; }\n\n    T normalize(T x)\
    \ const {\n        return simplex_abs(x) <= eps ? T() : x;\n    }\n\n    bool\
    \ less_with_tie(int row, int lhs, int rhs) const {\n        if (table[row][lhs]\
    \ < table[row][rhs] - eps) return true;\n        if (table[row][rhs] < table[row][lhs]\
    \ - eps) return false;\n        return nonbasis[lhs] < nonbasis[rhs];\n    }\n\
    \n    bool better_leaving_row(int lhs, int rhs, int entering_col) const {\n  \
    \      T lhs_ratio = table[lhs][rhs_col()] / table[lhs][entering_col];\n     \
    \   T rhs_ratio = table[rhs][rhs_col()] / table[rhs][entering_col];\n        if\
    \ (lhs_ratio < rhs_ratio - eps) return true;\n        if (rhs_ratio < lhs_ratio\
    \ - eps) return false;\n        return basis[lhs] < basis[rhs];\n    }\n\n   \
    \ void pivot(int leaving_row, int entering_col) {\n        T inverse = T(1) /\
    \ table[leaving_row][entering_col];\n        for (int i = 0; i < constraint_count\
    \ + 2; i++) {\n            if (i == leaving_row) continue;\n            for (int\
    \ j = 0; j < variable_count + 2; j++) {\n                if (j == entering_col)\
    \ continue;\n                table[i][j] -= table[leaving_row][j] * table[i][entering_col]\
    \ * inverse;\n            }\n        }\n        for (int j = 0; j < variable_count\
    \ + 2; j++) {\n            if (j != entering_col) table[leaving_row][j] *= inverse;\n\
    \        }\n        for (int i = 0; i < constraint_count + 2; i++) {\n       \
    \     if (i != leaving_row) table[i][entering_col] *= -inverse;\n        }\n \
    \       table[leaving_row][entering_col] = inverse;\n        std::swap(basis[leaving_row],\
    \ nonbasis[entering_col]);\n    }\n\n    bool run_simplex(int row) {\n       \
    \ while (true) {\n            int entering_col = -1;\n            for (int j =\
    \ 0; j <= variable_count; j++) {\n                if (nonbasis[j] == artificial_id())\
    \ continue;\n                if (entering_col == -1 || less_with_tie(row, j, entering_col))\
    \ entering_col = j;\n            }\n            if (entering_col == -1 || table[row][entering_col]\
    \ >= -eps) return true;\n\n            int leaving_row = -1;\n            for\
    \ (int i = 0; i < constraint_count; i++) {\n                if (table[i][entering_col]\
    \ <= eps) continue;\n                if (leaving_row == -1 || better_leaving_row(i,\
    \ leaving_row, entering_col)) {\n                    leaving_row = i;\n      \
    \          }\n            }\n            if (leaving_row == -1) return false;\n\
    \            pivot(leaving_row, entering_col);\n        }\n    }\n\n    bool make_feasible()\
    \ {\n        int leaving_row = 0;\n        for (int i = 1; i < constraint_count;\
    \ i++) {\n            if (table[i][rhs_col()] < table[leaving_row][rhs_col()])\
    \ leaving_row = i;\n        }\n        if (constraint_count == 0 || table[leaving_row][rhs_col()]\
    \ >= -eps) return true;\n\n        pivot(leaving_row, artificial_col());\n   \
    \     if (!run_simplex(auxiliary_row())) return false;\n        if (table[auxiliary_row()][rhs_col()]\
    \ < -eps) return false;\n\n        for (int i = 0; i < constraint_count; i++)\
    \ {\n            if (basis[i] != artificial_id()) continue;\n            int entering_col\
    \ = -1;\n            for (int j = 0; j <= variable_count; j++) {\n           \
    \     if (nonbasis[j] == artificial_id()) continue;\n                if (simplex_abs(table[i][j])\
    \ <= eps) continue;\n                if (entering_col == -1 || nonbasis[j] < nonbasis[entering_col])\
    \ entering_col = j;\n            }\n            if (entering_col != -1) pivot(i,\
    \ entering_col);\n        }\n        return true;\n    }\n\n    SimplexStatus\
    \ solve(std::vector<T>& variables, T& objective_value) {\n        if (!make_feasible())\
    \ return SimplexStatus::Infeasible;\n        if (!run_simplex(objective_row()))\
    \ return SimplexStatus::Unbounded;\n\n        variables.assign(variable_count,\
    \ T());\n        for (int i = 0; i < constraint_count; i++) {\n            if\
    \ (0 <= basis[i] && basis[i] < variable_count) {\n                variables[basis[i]]\
    \ = normalize(table[i][rhs_col()]);\n            }\n        }\n        objective_value\
    \ = normalize(table[objective_row()][rhs_col()]);\n        return SimplexStatus::Optimal;\n\
    \    }\n};\n\n}  // namespace detail\n\ntemplate <class T>\nSimplexResult<T> simplex_maximize(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \                 const std::vector<T>& c, T eps = T(1e-10)) {\n    static_assert(std::is_floating_point_v<T>,\
    \ \"simplex requires a floating-point type\");\n    assert(int(a.size()) == int(b.size()));\n\
    \    for (const auto& row : a) assert(int(row.size()) == int(c.size()));\n   \
    \ assert(eps > T());\n\n    SimplexResult<T> result;\n    result.status = SimplexStatus::Infeasible;\n\
    \    result.objective_value = std::numeric_limits<T>::quiet_NaN();\n    result.variables.assign(c.size(),\
    \ T());\n\n    detail::SimplexTableau<T> solver(a, b, c, eps);\n    result.status\
    \ = solver.solve(result.variables, result.objective_value);\n    if (result.status\
    \ == SimplexStatus::Infeasible) {\n        result.objective_value = std::numeric_limits<T>::quiet_NaN();\n\
    \    } else if (result.status == SimplexStatus::Unbounded) {\n        result.objective_value\
    \ = std::numeric_limits<T>::infinity();\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nSimplexResult<T> simplex_minimize(const std::vector<std::vector<T>>&\
    \ a, const std::vector<T>& b,\n                                  const std::vector<T>&\
    \ c, T eps = T(1e-10)) {\n    std::vector<T> negated = c;\n    for (T& x : negated)\
    \ x = -x;\n    auto result = simplex_maximize(a, b, negated, eps);\n    if (result.status\
    \ == SimplexStatus::Optimal) {\n        result.objective_value = -result.objective_value;\n\
    \    } else if (result.status == SimplexStatus::Unbounded) {\n        result.objective_value\
    \ = -std::numeric_limits<T>::infinity();\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nSimplexResult<T> simplex(const std::vector<std::vector<T>>& a, const\
    \ std::vector<T>& b,\n                         const std::vector<T>& c, T eps\
    \ = T(1e-10)) {\n    return simplex_maximize(a, b, c, eps);\n}\n\n}  // namespace\
    \ optimization\n}  // namespace m1une\n\n\n#line 12 \"optimization/integer_lp.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\nenum class IntegerLpStatus\
    \ {\n    Optimal,\n    Infeasible,\n    Unbounded,\n};\n\ntemplate <class T>\n\
    struct IntegerLpResult {\n    IntegerLpStatus status;\n    T objective_value;\n\
    \    std::vector<T> variables;\n\n    bool is_optimal() const { return status\
    \ == IntegerLpStatus::Optimal; }\n    bool is_infeasible() const { return status\
    \ == IntegerLpStatus::Infeasible; }\n    bool is_unbounded() const { return status\
    \ == IntegerLpStatus::Unbounded; }\n};\n\nnamespace detail {\n\ntemplate <class\
    \ T>\nstruct IntegerLpSolver {\n    using Real = long double;\n\n    struct Node\
    \ {\n        std::vector<std::vector<Real>> a;\n        std::vector<Real> b;\n\
    \    };\n\n    int variable_count;\n    bool maximize;\n    Real eps;\n    std::vector<T>\
    \ objective;\n    std::vector<Real> relaxation_objective;\n    Node initial_node;\n\
    \n    bool has_incumbent = false;\n    T best_value = T();\n    std::vector<T>\
    \ best_variables;\n\n    IntegerLpSolver(const std::vector<std::vector<T>>& a,\
    \ const std::vector<T>& b,\n                    const std::vector<T>& c, bool\
    \ is_maximize, Real epsilon)\n        : variable_count(int(c.size())),\n     \
    \     maximize(is_maximize),\n          eps(epsilon),\n          objective(c),\n\
    \          relaxation_objective(c.size(), Real()),\n          initial_node() {\n\
    \        initial_node.a.assign(a.size(), std::vector<Real>(variable_count, Real()));\n\
    \        initial_node.b.assign(b.size(), Real());\n        for (int i = 0; i <\
    \ int(a.size()); i++) {\n            for (int j = 0; j < variable_count; j++)\
    \ initial_node.a[i][j] = Real(a[i][j]);\n            initial_node.b[i] = Real(b[i]);\n\
    \        }\n        Real sign = maximize ? Real(1) : Real(-1);\n        for (int\
    \ j = 0; j < variable_count; j++) relaxation_objective[j] = sign * Real(c[j]);\n\
    \    }\n\n    Real abs_value(Real x) const {\n        return x < Real() ? -x :\
    \ x;\n    }\n\n    bool better_value(T lhs, T rhs) const {\n        return maximize\
    \ ? lhs > rhs : lhs < rhs;\n    }\n\n    bool can_prune_by_bound(Real relaxation_value)\
    \ const {\n        if (!has_incumbent) return false;\n        Real signed_best\
    \ = maximize ? Real(best_value) : -Real(best_value);\n        return relaxation_value\
    \ <= signed_best + eps;\n    }\n\n    T evaluate(const std::vector<T>& variables)\
    \ const {\n        T result = T();\n        for (int i = 0; i < variable_count;\
    \ i++) result += objective[i] * variables[i];\n        return result;\n    }\n\
    \n    bool round_solution(const std::vector<Real>& real_variables, std::vector<T>&\
    \ variables) const {\n        variables.assign(variable_count, T());\n       \
    \ for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            if (value < -eps) return false;\n            Real rounded = std::round(value);\n\
    \            if (abs_value(value - rounded) > eps) return false;\n           \
    \ variables[i] = static_cast<T>(rounded);\n        }\n        return true;\n \
    \   }\n\n    int find_fractional_variable(const std::vector<Real>& real_variables)\
    \ const {\n        int result = -1;\n        Real best_distance = eps;\n     \
    \   for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            Real rounded = std::round(value);\n            Real distance = abs_value(value\
    \ - rounded);\n            if (distance > best_distance) {\n                best_distance\
    \ = distance;\n                result = i;\n            }\n        }\n       \
    \ return result;\n    }\n\n    Node with_upper_bound(const Node& node, int variable,\
    \ T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(1);\n        result.b.push_back(Real(bound));\n\
    \        return result;\n    }\n\n    Node with_lower_bound(const Node& node,\
    \ int variable, T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(-1);\n        result.b.push_back(-Real(bound));\n\
    \        return result;\n    }\n\n    void push_branches(std::vector<Node>& stack,\
    \ const Node& node, int variable, Real value) const {\n        Real floor_value\
    \ = std::floor(value);\n        Real ceil_value = std::ceil(value);\n        T\
    \ upper_bound = static_cast<T>(floor_value);\n        T lower_bound = static_cast<T>(ceil_value);\n\
    \n        bool has_upper_branch = upper_bound >= T();\n        bool prefer_lower_branch\
    \ = relaxation_objective[variable] >= -eps;\n\n        if (prefer_lower_branch)\
    \ {\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n        } else {\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n        }\n    }\n\n    bool has_positive_direction(const\
    \ Node& node) const {\n        std::vector<std::vector<Real>> direction_a = node.a;\n\
    \        std::vector<Real> direction_b(node.b.size(), Real());\n\n        std::vector<Real>\
    \ objective_row(variable_count, Real());\n        for (int i = 0; i < variable_count;\
    \ i++) objective_row[i] = -relaxation_objective[i];\n        direction_a.push_back(objective_row);\n\
    \        direction_b.push_back(Real(-1));\n\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n        auto result = simplex_maximize(direction_a, direction_b, zero_objective,\
    \ eps);\n        return result.is_optimal();\n    }\n\n    bool find_integer_feasible(const\
    \ Node& start, std::vector<T>& feasible_variables) const {\n        std::vector<Node>\
    \ stack;\n        stack.push_back(start);\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n\n        while (!stack.empty()) {\n            Node node = stack.back();\n\
    \            stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, zero_objective, eps);\n            if (relaxation.is_infeasible()) continue;\n\
    \            if (relaxation.is_unbounded()) continue;\n\n            if (round_solution(relaxation.variables,\
    \ feasible_variables)) return true;\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n        return false;\n\
    \    }\n\n    void update_incumbent(const std::vector<T>& variables) {\n     \
    \   T value = evaluate(variables);\n        if (!has_incumbent || better_value(value,\
    \ best_value)) {\n            has_incumbent = true;\n            best_value =\
    \ value;\n            best_variables = variables;\n        }\n    }\n\n    IntegerLpResult<T>\
    \ make_infeasible_result() const {\n        IntegerLpResult<T> result;\n     \
    \   result.status = IntegerLpStatus::Infeasible;\n        result.objective_value\
    \ = T();\n        result.variables.assign(variable_count, T());\n        return\
    \ result;\n    }\n\n    IntegerLpResult<T> make_unbounded_result(const std::vector<T>&\
    \ variables) const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Unbounded;\n        result.objective_value =\n          \
    \  maximize ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest();\n\
    \        result.variables = variables;\n        return result;\n    }\n\n    IntegerLpResult<T>\
    \ make_optimal_result() const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Optimal;\n        result.objective_value = best_value;\n\
    \        result.variables = best_variables;\n        return result;\n    }\n\n\
    \    IntegerLpResult<T> solve() {\n        std::vector<Node> stack;\n        stack.push_back(initial_node);\n\
    \n        while (!stack.empty()) {\n            Node node = stack.back();\n  \
    \          stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, relaxation_objective, eps);\n            if (relaxation.is_infeasible())\
    \ continue;\n\n            if (relaxation.is_unbounded()) {\n                std::vector<T>\
    \ feasible_variables;\n                if (has_positive_direction(node) && find_integer_feasible(node,\
    \ feasible_variables)) {\n                    return make_unbounded_result(feasible_variables);\n\
    \                }\n                continue;\n            }\n\n            if\
    \ (can_prune_by_bound(relaxation.objective_value)) continue;\n\n            std::vector<T>\
    \ integer_variables;\n            if (round_solution(relaxation.variables, integer_variables))\
    \ {\n                update_incumbent(integer_variables);\n                continue;\n\
    \            }\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n\n        if (!has_incumbent)\
    \ return make_infeasible_result();\n        return make_optimal_result();\n  \
    \  }\n};\n\n}  // namespace detail\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_maximize(const\
    \ std::vector<std::vector<T>>& a,\n                                       const\
    \ std::vector<T>& b, const std::vector<T>& c,\n                              \
    \         long double eps = 1e-10L) {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>,\n                  \"integer_lp requires a signed integer\
    \ type\");\n    assert(int(a.size()) == int(b.size()));\n    for (const auto&\
    \ row : a) assert(int(row.size()) == int(c.size()));\n    assert(eps > 0);\n\n\
    \    detail::IntegerLpSolver<T> solver(a, b, c, true, eps);\n    return solver.solve();\n\
    }\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_minimize(const std::vector<std::vector<T>>&\
    \ a,\n                                       const std::vector<T>& b, const std::vector<T>&\
    \ c,\n                                       long double eps = 1e-10L) {\n   \
    \ static_assert(std::is_integral_v<T> && std::is_signed_v<T>,\n              \
    \    \"integer_lp requires a signed integer type\");\n    assert(int(a.size())\
    \ == int(b.size()));\n    for (const auto& row : a) assert(int(row.size()) ==\
    \ int(c.size()));\n    assert(eps > 0);\n\n    detail::IntegerLpSolver<T> solver(a,\
    \ b, c, false, eps);\n    return solver.solve();\n}\n\ntemplate <class T>\nIntegerLpResult<T>\
    \ integer_lp(const std::vector<std::vector<T>>& a, const std::vector<T>& b,\n\
    \                              const std::vector<T>& c, long double eps = 1e-10L)\
    \ {\n    return integer_lp_maximize(a, b, c, eps);\n}\n\n}  // namespace optimization\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_INTEGER_LP_HPP\n#define M1UNE_OPTIMIZATION_INTEGER_LP_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <limits>\n\
    #include <type_traits>\n#include <vector>\n\n#include \"simplex.hpp\"\n\nnamespace\
    \ m1une {\nnamespace optimization {\n\nenum class IntegerLpStatus {\n    Optimal,\n\
    \    Infeasible,\n    Unbounded,\n};\n\ntemplate <class T>\nstruct IntegerLpResult\
    \ {\n    IntegerLpStatus status;\n    T objective_value;\n    std::vector<T> variables;\n\
    \n    bool is_optimal() const { return status == IntegerLpStatus::Optimal; }\n\
    \    bool is_infeasible() const { return status == IntegerLpStatus::Infeasible;\
    \ }\n    bool is_unbounded() const { return status == IntegerLpStatus::Unbounded;\
    \ }\n};\n\nnamespace detail {\n\ntemplate <class T>\nstruct IntegerLpSolver {\n\
    \    using Real = long double;\n\n    struct Node {\n        std::vector<std::vector<Real>>\
    \ a;\n        std::vector<Real> b;\n    };\n\n    int variable_count;\n    bool\
    \ maximize;\n    Real eps;\n    std::vector<T> objective;\n    std::vector<Real>\
    \ relaxation_objective;\n    Node initial_node;\n\n    bool has_incumbent = false;\n\
    \    T best_value = T();\n    std::vector<T> best_variables;\n\n    IntegerLpSolver(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \   const std::vector<T>& c, bool is_maximize, Real epsilon)\n        : variable_count(int(c.size())),\n\
    \          maximize(is_maximize),\n          eps(epsilon),\n          objective(c),\n\
    \          relaxation_objective(c.size(), Real()),\n          initial_node() {\n\
    \        initial_node.a.assign(a.size(), std::vector<Real>(variable_count, Real()));\n\
    \        initial_node.b.assign(b.size(), Real());\n        for (int i = 0; i <\
    \ int(a.size()); i++) {\n            for (int j = 0; j < variable_count; j++)\
    \ initial_node.a[i][j] = Real(a[i][j]);\n            initial_node.b[i] = Real(b[i]);\n\
    \        }\n        Real sign = maximize ? Real(1) : Real(-1);\n        for (int\
    \ j = 0; j < variable_count; j++) relaxation_objective[j] = sign * Real(c[j]);\n\
    \    }\n\n    Real abs_value(Real x) const {\n        return x < Real() ? -x :\
    \ x;\n    }\n\n    bool better_value(T lhs, T rhs) const {\n        return maximize\
    \ ? lhs > rhs : lhs < rhs;\n    }\n\n    bool can_prune_by_bound(Real relaxation_value)\
    \ const {\n        if (!has_incumbent) return false;\n        Real signed_best\
    \ = maximize ? Real(best_value) : -Real(best_value);\n        return relaxation_value\
    \ <= signed_best + eps;\n    }\n\n    T evaluate(const std::vector<T>& variables)\
    \ const {\n        T result = T();\n        for (int i = 0; i < variable_count;\
    \ i++) result += objective[i] * variables[i];\n        return result;\n    }\n\
    \n    bool round_solution(const std::vector<Real>& real_variables, std::vector<T>&\
    \ variables) const {\n        variables.assign(variable_count, T());\n       \
    \ for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            if (value < -eps) return false;\n            Real rounded = std::round(value);\n\
    \            if (abs_value(value - rounded) > eps) return false;\n           \
    \ variables[i] = static_cast<T>(rounded);\n        }\n        return true;\n \
    \   }\n\n    int find_fractional_variable(const std::vector<Real>& real_variables)\
    \ const {\n        int result = -1;\n        Real best_distance = eps;\n     \
    \   for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            Real rounded = std::round(value);\n            Real distance = abs_value(value\
    \ - rounded);\n            if (distance > best_distance) {\n                best_distance\
    \ = distance;\n                result = i;\n            }\n        }\n       \
    \ return result;\n    }\n\n    Node with_upper_bound(const Node& node, int variable,\
    \ T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(1);\n        result.b.push_back(Real(bound));\n\
    \        return result;\n    }\n\n    Node with_lower_bound(const Node& node,\
    \ int variable, T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(-1);\n        result.b.push_back(-Real(bound));\n\
    \        return result;\n    }\n\n    void push_branches(std::vector<Node>& stack,\
    \ const Node& node, int variable, Real value) const {\n        Real floor_value\
    \ = std::floor(value);\n        Real ceil_value = std::ceil(value);\n        T\
    \ upper_bound = static_cast<T>(floor_value);\n        T lower_bound = static_cast<T>(ceil_value);\n\
    \n        bool has_upper_branch = upper_bound >= T();\n        bool prefer_lower_branch\
    \ = relaxation_objective[variable] >= -eps;\n\n        if (prefer_lower_branch)\
    \ {\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n        } else {\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n        }\n    }\n\n    bool has_positive_direction(const\
    \ Node& node) const {\n        std::vector<std::vector<Real>> direction_a = node.a;\n\
    \        std::vector<Real> direction_b(node.b.size(), Real());\n\n        std::vector<Real>\
    \ objective_row(variable_count, Real());\n        for (int i = 0; i < variable_count;\
    \ i++) objective_row[i] = -relaxation_objective[i];\n        direction_a.push_back(objective_row);\n\
    \        direction_b.push_back(Real(-1));\n\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n        auto result = simplex_maximize(direction_a, direction_b, zero_objective,\
    \ eps);\n        return result.is_optimal();\n    }\n\n    bool find_integer_feasible(const\
    \ Node& start, std::vector<T>& feasible_variables) const {\n        std::vector<Node>\
    \ stack;\n        stack.push_back(start);\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n\n        while (!stack.empty()) {\n            Node node = stack.back();\n\
    \            stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, zero_objective, eps);\n            if (relaxation.is_infeasible()) continue;\n\
    \            if (relaxation.is_unbounded()) continue;\n\n            if (round_solution(relaxation.variables,\
    \ feasible_variables)) return true;\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n        return false;\n\
    \    }\n\n    void update_incumbent(const std::vector<T>& variables) {\n     \
    \   T value = evaluate(variables);\n        if (!has_incumbent || better_value(value,\
    \ best_value)) {\n            has_incumbent = true;\n            best_value =\
    \ value;\n            best_variables = variables;\n        }\n    }\n\n    IntegerLpResult<T>\
    \ make_infeasible_result() const {\n        IntegerLpResult<T> result;\n     \
    \   result.status = IntegerLpStatus::Infeasible;\n        result.objective_value\
    \ = T();\n        result.variables.assign(variable_count, T());\n        return\
    \ result;\n    }\n\n    IntegerLpResult<T> make_unbounded_result(const std::vector<T>&\
    \ variables) const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Unbounded;\n        result.objective_value =\n          \
    \  maximize ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest();\n\
    \        result.variables = variables;\n        return result;\n    }\n\n    IntegerLpResult<T>\
    \ make_optimal_result() const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Optimal;\n        result.objective_value = best_value;\n\
    \        result.variables = best_variables;\n        return result;\n    }\n\n\
    \    IntegerLpResult<T> solve() {\n        std::vector<Node> stack;\n        stack.push_back(initial_node);\n\
    \n        while (!stack.empty()) {\n            Node node = stack.back();\n  \
    \          stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, relaxation_objective, eps);\n            if (relaxation.is_infeasible())\
    \ continue;\n\n            if (relaxation.is_unbounded()) {\n                std::vector<T>\
    \ feasible_variables;\n                if (has_positive_direction(node) && find_integer_feasible(node,\
    \ feasible_variables)) {\n                    return make_unbounded_result(feasible_variables);\n\
    \                }\n                continue;\n            }\n\n            if\
    \ (can_prune_by_bound(relaxation.objective_value)) continue;\n\n            std::vector<T>\
    \ integer_variables;\n            if (round_solution(relaxation.variables, integer_variables))\
    \ {\n                update_incumbent(integer_variables);\n                continue;\n\
    \            }\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n\n        if (!has_incumbent)\
    \ return make_infeasible_result();\n        return make_optimal_result();\n  \
    \  }\n};\n\n}  // namespace detail\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_maximize(const\
    \ std::vector<std::vector<T>>& a,\n                                       const\
    \ std::vector<T>& b, const std::vector<T>& c,\n                              \
    \         long double eps = 1e-10L) {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>,\n                  \"integer_lp requires a signed integer\
    \ type\");\n    assert(int(a.size()) == int(b.size()));\n    for (const auto&\
    \ row : a) assert(int(row.size()) == int(c.size()));\n    assert(eps > 0);\n\n\
    \    detail::IntegerLpSolver<T> solver(a, b, c, true, eps);\n    return solver.solve();\n\
    }\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_minimize(const std::vector<std::vector<T>>&\
    \ a,\n                                       const std::vector<T>& b, const std::vector<T>&\
    \ c,\n                                       long double eps = 1e-10L) {\n   \
    \ static_assert(std::is_integral_v<T> && std::is_signed_v<T>,\n              \
    \    \"integer_lp requires a signed integer type\");\n    assert(int(a.size())\
    \ == int(b.size()));\n    for (const auto& row : a) assert(int(row.size()) ==\
    \ int(c.size()));\n    assert(eps > 0);\n\n    detail::IntegerLpSolver<T> solver(a,\
    \ b, c, false, eps);\n    return solver.solve();\n}\n\ntemplate <class T>\nIntegerLpResult<T>\
    \ integer_lp(const std::vector<std::vector<T>>& a, const std::vector<T>& b,\n\
    \                              const std::vector<T>& c, long double eps = 1e-10L)\
    \ {\n    return integer_lp_maximize(a, b, c, eps);\n}\n\n}  // namespace optimization\n\
    }  // namespace m1une\n\n#endif  // M1UNE_OPTIMIZATION_INTEGER_LP_HPP\n"
  dependsOn:
  - optimization/simplex.hpp
  isVerificationFile: false
  path: optimization/integer_lp.hpp
  requiredBy:
  - optimization/all.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/simplex.test.cpp
documentation_of: optimization/integer_lp.hpp
layout: document
title: Integer Linear Programming
---

## Overview

`integer_lp_maximize(a, b, c)` solves an integer linear programming problem in
standard inequality form:

$$
\begin{array}{ll}
\text{maximize} & c^T x \\
\text{subject to} & A x \le b \\
& x \in \mathbb{Z}_{\ge 0}^W
\end{array}
$$

The implementation uses branch-and-bound over LP relaxations solved by
`simplex_maximize`. It is useful for small or naturally bounded instances.
Integer linear programming is NP-hard, so the number of explored nodes can be
exponential.

`integer_lp_minimize(a, b, c)` solves the corresponding minimization problem
with the same constraints. `integer_lp(a, b, c)` is an alias of
`integer_lp_maximize(a, b, c)`.

## Interface

The inputs are:

| Argument | Type | Meaning |
| --- | --- | --- |
| `a` | `std::vector<std::vector<T>>` | Constraint matrix `A`. |
| `b` | `std::vector<T>` | Right-hand side vector. Constraint `i` is `a[i] * x <= b[i]`. |
| `c` | `std::vector<T>` | Objective coefficients. |
| `eps` | `long double` | Optional tolerance used by LP relaxations. The default is `1e-10`. |

`a.size()` must equal `b.size()`, and every row of `a` must have
`c.size()` entries. `T` must be a signed integer type, such as `int` or
`long long`.

`IntegerLpStatus` has these values:

| Value | Meaning |
| --- | --- |
| `IntegerLpStatus::Optimal` | A finite integer optimum was found. |
| `IntegerLpStatus::Infeasible` | No integer vector satisfies all constraints. |
| `IntegerLpStatus::Unbounded` | The objective is unbounded in the requested direction. |

`IntegerLpResult<T>` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `status` | `IntegerLpStatus` | Solver status. |
| `objective_value` | `T` | Optimal objective value when `status` is `Optimal`. |
| `variables` | `std::vector<T>` | Optimal variable values when `status` is `Optimal`. |
| `is_optimal` | `bool is_optimal() const` | Returns whether the status is `Optimal`. |
| `is_infeasible` | `bool is_infeasible() const` | Returns whether the status is `Infeasible`. |
| `is_unbounded` | `bool is_unbounded() const` | Returns whether the status is `Unbounded`. |

When the result is `Unbounded`, `variables` contains an integer feasible point
found during the search, and `objective_value` is set to the numeric limit in
the unbounded direction. For `Infeasible`, `objective_value` and `variables`
are placeholders.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `integer_lp_maximize` | `template <class T> IntegerLpResult<T> integer_lp_maximize(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, long double eps = 1e-10L)` | Maximizes `c^T x` subject to `A x <= b` and nonnegative integer `x`. | Exponential in the worst case. |
| `integer_lp_minimize` | `template <class T> IntegerLpResult<T> integer_lp_minimize(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, long double eps = 1e-10L)` | Minimizes `c^T x` under the same constraints. | Exponential in the worst case. |
| `integer_lp` | `template <class T> IntegerLpResult<T> integer_lp(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, long double eps = 1e-10L)` | Alias of `integer_lp_maximize`. | Exponential in the worst case. |

## Example

```cpp
#include "optimization/integer_lp.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{2, 1});
    a.emplace_back(std::vector<long long>{1, 2});

    std::vector<long long> b = {4, 4};
    std::vector<long long> c = {3, 2};

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    if (result.is_optimal()) {
        std::cout << result.objective_value << "\n";  // 6
        std::cout << result.variables[0] << " " << result.variables[1] << "\n";
    }
}
```
