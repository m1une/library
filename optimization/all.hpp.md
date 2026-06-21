---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
  - icon: ':heavy_check_mark:'
    path: optimization/integer_lp.hpp
    title: Integer Linear Programming
  - icon: ':heavy_check_mark:'
    path: optimization/simplex.hpp
    title: Simplex Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/simplex.test.cpp
    title: verify/optimization/simplex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"optimization/all.hpp\"\n\n\n\n#line 1 \"optimization/hungarian.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace optimization {\n\
    \ntemplate <class T>\nstruct HungarianResult {\n    T cost;\n    std::vector<int>\
    \ row_to_col;\n    std::vector<int> col_to_row;\n\n    int matching_size() const\
    \ {\n        int result = 0;\n        for (int col : row_to_col) {\n         \
    \   if (col != -1) result++;\n        }\n        return result;\n    }\n\n   \
    \ std::vector<std::pair<int, int>> matching() const {\n        std::vector<std::pair<int,\
    \ int>> result;\n        for (int row = 0; row < int(row_to_col.size()); row++)\
    \ {\n            if (row_to_col[row] != -1) result.push_back({row, row_to_col[row]});\n\
    \        }\n        return result;\n    }\n};\n\nnamespace detail {\n\ntemplate\
    \ <class T>\nT assignment_cost(const std::vector<std::vector<T>>& cost, const\
    \ std::vector<int>& row_to_col) {\n    T result = T();\n    for (int row = 0;\
    \ row < int(row_to_col.size()); row++) {\n        if (row_to_col[row] != -1) result\
    \ += cost[row][row_to_col[row]];\n    }\n    return result;\n}\n\n}  // namespace\
    \ detail\n\ntemplate <class T>\nHungarianResult<T> hungarian_min(const std::vector<std::vector<T>>&\
    \ cost) {\n    int row_count = int(cost.size());\n    int col_count = row_count\
    \ == 0 ? 0 : int(cost[0].size());\n    for (const auto& row : cost) assert(int(row.size())\
    \ == col_count);\n\n    HungarianResult<T> result;\n    result.cost = T();\n \
    \   result.row_to_col.assign(row_count, -1);\n    result.col_to_row.assign(col_count,\
    \ -1);\n    if (row_count == 0 || col_count == 0) return result;\n\n    bool transposed\
    \ = row_count > col_count;\n    int n = transposed ? col_count : row_count;\n\
    \    int m = transposed ? row_count : col_count;\n    T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n\n    std::vector<T> u(n + 1, T()), v(m + 1, T()), minv(m + 1);\n \
    \   std::vector<int> p(m + 1, 0), way(m + 1, 0);\n\n    auto value = [&](int i,\
    \ int j) -> T {\n        return transposed ? cost[j][i] : cost[i][j];\n    };\n\
    \n    for (int i = 1; i <= n; i++) {\n        p[0] = i;\n        int j0 = 0;\n\
    \        std::fill(minv.begin(), minv.end(), inf);\n        std::vector<char>\
    \ used(m + 1, false);\n\n        do {\n            used[j0] = true;\n        \
    \    int i0 = p[j0];\n            int j1 = 0;\n            T delta = inf;\n\n\
    \            for (int j = 1; j <= m; j++) {\n                if (used[j]) continue;\n\
    \                T cur = value(i0 - 1, j - 1) - u[i0] - v[j];\n              \
    \  if (cur < minv[j]) {\n                    minv[j] = cur;\n                \
    \    way[j] = j0;\n                }\n                if (minv[j] < delta) {\n\
    \                    delta = minv[j];\n                    j1 = j;\n         \
    \       }\n            }\n\n            for (int j = 0; j <= m; j++) {\n     \
    \           if (used[j]) {\n                    u[p[j]] += delta;\n          \
    \          v[j] -= delta;\n                } else {\n                    minv[j]\
    \ -= delta;\n                }\n            }\n            j0 = j1;\n        }\
    \ while (p[j0] != 0);\n\n        do {\n            int j1 = way[j0];\n       \
    \     p[j0] = p[j1];\n            j0 = j1;\n        } while (j0 != 0);\n    }\n\
    \n    for (int j = 1; j <= m; j++) {\n        if (p[j] == 0) continue;\n     \
    \   int i = p[j] - 1;\n        int matched = j - 1;\n        if (transposed) {\n\
    \            int row = matched;\n            int col = i;\n            result.row_to_col[row]\
    \ = col;\n            result.col_to_row[col] = row;\n        } else {\n      \
    \      int row = i;\n            int col = matched;\n            result.row_to_col[row]\
    \ = col;\n            result.col_to_row[col] = row;\n        }\n    }\n    result.cost\
    \ = detail::assignment_cost(cost, result.row_to_col);\n    return result;\n}\n\
    \ntemplate <class T>\nHungarianResult<T> hungarian_max(const std::vector<std::vector<T>>&\
    \ cost) {\n    std::vector<std::vector<T>> negated = cost;\n    for (auto& row\
    \ : negated) {\n        for (auto& x : row) x = -x;\n    }\n    auto result =\
    \ hungarian_min(negated);\n    result.cost = detail::assignment_cost(cost, result.row_to_col);\n\
    \    return result;\n}\n\ntemplate <class T>\nHungarianResult<T> hungarian(const\
    \ std::vector<std::vector<T>>& cost) {\n    return hungarian_min(cost);\n}\n\n\
    }  // namespace optimization\n}  // namespace m1une\n\n\n#line 1 \"optimization/integer_lp.hpp\"\
    \n\n\n\n#line 6 \"optimization/integer_lp.hpp\"\n#include <cmath>\n#line 8 \"\
    optimization/integer_lp.hpp\"\n#include <type_traits>\n#line 10 \"optimization/integer_lp.hpp\"\
    \n\n#line 1 \"optimization/simplex.hpp\"\n\n\n\n#line 9 \"optimization/simplex.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\nenum class SimplexStatus {\n\
    \    Optimal,\n    Infeasible,\n    Unbounded,\n};\n\ntemplate <class T>\nstruct\
    \ SimplexResult {\n    SimplexStatus status;\n    T objective_value;\n    std::vector<T>\
    \ variables;\n\n    bool is_optimal() const { return status == SimplexStatus::Optimal;\
    \ }\n    bool is_infeasible() const { return status == SimplexStatus::Infeasible;\
    \ }\n    bool is_unbounded() const { return status == SimplexStatus::Unbounded;\
    \ }\n};\n\nnamespace detail {\n\ntemplate <class T>\nT simplex_abs(T x) {\n  \
    \  return x < T() ? -x : x;\n}\n\ntemplate <class T>\nstruct SimplexTableau {\n\
    \    int constraint_count;\n    int variable_count;\n    T eps;\n    std::vector<int>\
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
    }  // namespace m1une\n\n\n#line 7 \"optimization/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_OPTIMIZATION_ALL_HPP

    #define M1UNE_OPTIMIZATION_ALL_HPP 1


    #include "hungarian.hpp"

    #include "integer_lp.hpp"

    #include "simplex.hpp"


    #endif  // M1UNE_OPTIMIZATION_ALL_HPP

    '
  dependsOn:
  - optimization/hungarian.hpp
  - optimization/integer_lp.hpp
  - optimization/simplex.hpp
  isVerificationFile: false
  path: optimization/all.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/simplex.test.cpp
documentation_of: optimization/all.hpp
layout: document
title: Optimization All
---

## Overview

`optimization/all.hpp` includes optimization algorithms whose public interface
is not naturally a graph, data structure, or algebraic object.

## Included Headers

| Header | Contents |
| --- | --- |
| `optimization/hungarian.hpp` | Hungarian algorithm for minimum-cost and maximum-cost rectangular assignment. |
| `optimization/integer_lp.hpp` | Branch-and-bound solver for integer linear programming in standard inequality form. |
| `optimization/simplex.hpp` | Two-phase simplex algorithm for linear programming in standard inequality form. |
