---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: optimization/alien_trick.hpp
    title: Alien Trick
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
  - icon: ':heavy_check_mark:'
    path: optimization/integer_lp.hpp
    title: Integer Linear Programming
  - icon: ':heavy_check_mark:'
    path: optimization/project_selection.hpp
    title: Project Selection
  - icon: ':heavy_check_mark:'
    path: optimization/simplex.hpp
    title: Simplex Algorithm
  - icon: ':heavy_check_mark:'
    path: optimization/slope_trick.hpp
    title: Slope Trick
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/optimization/slope_trick.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\n#line\
    \ 1 \"optimization/all.hpp\"\n\n\n\n#line 1 \"optimization/alien_trick.hpp\"\n\
    \n\n\n#line 5 \"optimization/alien_trick.hpp\"\n#include <concepts>\n#include\
    \ <numeric>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\n\
    namespace optimization {\n\nnamespace detail {\n\ntemplate <std::integral Penalty,\
    \ std::integral Count, class Oracle>\nPenalty alien_trick_penalty(Penalty lower,\
    \ Penalty upper, Count target_count, Oracle& oracle) {\n    assert(lower <= upper);\n\
    \    assert(oracle(lower).second >= target_count);\n    assert(oracle(upper).second\
    \ <= target_count);\n\n    while (lower < upper) {\n        Penalty middle = std::midpoint(lower,\
    \ upper);\n        if (middle == lower) ++middle;\n        if (oracle(middle).second\
    \ >= target_count) {\n            lower = middle;\n        } else {\n        \
    \    upper = middle - 1;\n        }\n    }\n    return lower;\n}\n\n}  // namespace\
    \ detail\n\n// Recovers the minimum value among solutions using exactly `target_count`\n\
    // items. The oracle minimizes value + penalty * count and breaks ties in favor\n\
    // of the larger count.\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nauto alien_trick_minimize(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower,\
    \ upper, target_count, oracle);\n    auto result = oracle(penalty);\n    using\
    \ Value = std::remove_cvref_t<decltype(result.first)>;\n    return result.first\
    \ - static_cast<Value>(penalty) * static_cast<Value>(target_count);\n}\n\n// Recovers\
    \ the maximum value among solutions using exactly `target_count`\n// items. The\
    \ oracle maximizes value - penalty * count and breaks ties in favor\n// of the\
    \ larger count.\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\n\
    auto alien_trick_maximize(Penalty lower, Penalty upper, Count target_count, Oracle\
    \ oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count,\
    \ oracle);\n    auto result = oracle(penalty);\n    using Value = std::remove_cvref_t<decltype(result.first)>;\n\
    \    return result.first + static_cast<Value>(penalty) * static_cast<Value>(target_count);\n\
    }\n\n}  // namespace optimization\n}  // namespace m1une\n\n\n#line 1 \"optimization/hungarian.hpp\"\
    \n\n\n\n#line 9 \"optimization/hungarian.hpp\"\n\nnamespace m1une {\nnamespace\
    \ optimization {\n\ntemplate <class T>\nstruct HungarianResult {\n    T cost;\n\
    \    std::vector<int> row_to_col;\n    std::vector<int> col_to_row;\n\n    int\
    \ matching_size() const {\n        int result = 0;\n        for (int col : row_to_col)\
    \ {\n            if (col != -1) result++;\n        }\n        return result;\n\
    \    }\n\n    std::vector<std::pair<int, int>> matching() const {\n        std::vector<std::pair<int,\
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
    \n\n\n\n#line 6 \"optimization/integer_lp.hpp\"\n#include <cmath>\n#line 10 \"\
    optimization/integer_lp.hpp\"\n\n#line 1 \"optimization/simplex.hpp\"\n\n\n\n\
    #line 9 \"optimization/simplex.hpp\"\n\nnamespace m1une {\nnamespace optimization\
    \ {\n\nenum class SimplexStatus {\n    Optimal,\n    Infeasible,\n    Unbounded,\n\
    };\n\ntemplate <class T>\nstruct SimplexResult {\n    SimplexStatus status;\n\
    \    T objective_value;\n    std::vector<T> variables;\n\n    bool is_optimal()\
    \ const { return status == SimplexStatus::Optimal; }\n    bool is_infeasible()\
    \ const { return status == SimplexStatus::Infeasible; }\n    bool is_unbounded()\
    \ const { return status == SimplexStatus::Unbounded; }\n};\n\nnamespace detail\
    \ {\n\ntemplate <class T>\nT simplex_abs(T x) {\n    return x < T() ? -x : x;\n\
    }\n\ntemplate <class T>\nstruct SimplexTableau {\n    int constraint_count;\n\
    \    int variable_count;\n    T eps;\n    std::vector<int> basis;\n    std::vector<int>\
    \ nonbasis;\n    std::vector<std::vector<T>> table;\n\n    SimplexTableau(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \  const std::vector<T>& c, T epsilon)\n        : constraint_count(int(b.size())),\n\
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
    }  // namespace m1une\n\n\n#line 1 \"optimization/project_selection.hpp\"\n\n\n\
    \n#line 9 \"optimization/project_selection.hpp\"\n\n#line 1 \"flow/max_flow.hpp\"\
    \n\n\n\n#line 7 \"flow/max_flow.hpp\"\n#include <queue>\n#line 10 \"flow/max_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap cap;\n\
    \        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n       \
    \ int to;\n        int rev;\n        Cap cap;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n   public:\n\
    \    MaxFlow() : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n\
    \        assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    int edge_count() const {\n        return int(_pos.size());\n   \
    \ }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0 <= from\
    \ && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0) <=\
    \ cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.emplace_back(from, from_id);\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    Edge get_edge(int i) const {\n        assert(0\
    \ <= i && i < int(_pos.size()));\n        auto [from, idx] = _pos[i];\n      \
    \  const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        return Edge{from, e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge>\
    \ edges() const {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n        auto [from, idx] = _pos[i];\n\
    \        auto& e = _g[from][idx];\n        auto& re = _g[e.to][e.rev];\n     \
    \   e.cap = new_cap - new_flow;\n        re.cap = new_flow;\n    }\n\n    Cap\
    \ max_flow(int s, int t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n\n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n\
    \        std::vector<int> level(_n), iter(_n);\n        auto bfs = [&]() -> bool\
    \ {\n            std::fill(level.begin(), level.end(), -1);\n            std::queue<int>\
    \ que;\n            level[s] = 0;\n            que.push(s);\n            while\
    \ (!que.empty()) {\n                int v = que.front();\n                que.pop();\n\
    \                for (const auto& e : _g[v]) {\n                    if (e.cap\
    \ == Cap(0) || level[e.to] != -1) continue;\n                    level[e.to] =\
    \ level[v] + 1;\n                    if (e.to == t) return true;\n           \
    \         que.push(e.to);\n                }\n            }\n            return\
    \ level[t] != -1;\n        };\n\n        auto dfs = [&](auto self, int v, Cap\
    \ up) -> Cap {\n            if (v == t) return up;\n            for (int& i =\
    \ iter[v]; i < int(_g[v].size()); i++) {\n                auto& e = _g[v][i];\n\
    \                if (e.cap == Cap(0) || level[v] >= level[e.to]) continue;\n \
    \               Cap d = self(self, e.to, std::min(up, e.cap));\n             \
    \   if (d == Cap(0)) continue;\n                e.cap -= d;\n                _g[e.to][e.rev].cap\
    \ += d;\n                return d;\n            }\n            return Cap(0);\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter.begin(), iter.end(), 0);\n            while (flow\
    \ < flow_limit) {\n                Cap f = dfs(dfs, s, flow_limit - flow);\n \
    \               if (f == Cap(0)) break;\n                flow += f;\n        \
    \    }\n        }\n        return flow;\n    }\n\n    std::vector<bool> min_cut(int\
    \ s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool> visited(_n,\
    \ false);\n        std::queue<int> que;\n        visited[s] = true;\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            for (const auto& e : _g[v]) {\n                if (e.cap\
    \ == Cap(0) || visited[e.to]) continue;\n                visited[e.to] = true;\n\
    \                que.push(e.to);\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 11 \"optimization/project_selection.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\ntemplate <class T>\nstruct\
    \ ProjectSelectionResult {\n    bool feasible;\n    T max_gain;\n    std::vector<bool>\
    \ selected;\n\n    bool is_feasible() const {\n        return feasible;\n    }\n\
    };\n\ntemplate <class T>\nclass ProjectSelection {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct Arc {\n        int from;\n        int\
    \ to;\n        T cap;\n    };\n\n    static constexpr int source = -1;\n    static\
    \ constexpr int sink = -2;\n\n    int _project_count;\n    int _vertex_count;\n\
    \    T _offset = T();\n    T _finite_cap_sum = T();\n    std::vector<Arc> _arcs;\n\
    \    std::vector<std::pair<int, int>> _hard_arcs;\n\n    void assert_project(int\
    \ project) const {\n        (void)project;\n        assert(0 <= project && project\
    \ < _project_count);\n    }\n\n    void assert_vertex(int vertex) const {\n  \
    \      (void)vertex;\n        assert(0 <= vertex && vertex < _vertex_count);\n\
    \    }\n\n    void add_offset(T value) {\n        if (value > T()) {\n       \
    \     assert(_offset <= std::numeric_limits<T>::max() - value);\n        } else\
    \ if (value < T()) {\n            assert(_offset >= std::numeric_limits<T>::lowest()\
    \ - value);\n        }\n        _offset += value;\n    }\n\n    T nonnegative_difference(T\
    \ large, T small) const {\n        assert(small <= large);\n        if (small\
    \ < T()) {\n            assert(large <= std::numeric_limits<T>::max() + small);\n\
    \        }\n        return large - small;\n    }\n\n    void add_arc(int from,\
    \ int to, T cap) {\n        assert(cap >= T());\n        if (from == to) return;\n\
    \        assert(cap <= std::numeric_limits<T>::max() - _finite_cap_sum);\n   \
    \     _finite_cap_sum += cap;\n        _arcs.push_back(Arc{from, to, cap});\n\
    \    }\n\n    void add_hard_arc(int from, int to) {\n        if (from == to) return;\n\
    \        _hard_arcs.emplace_back(from, to);\n    }\n\n    void add_vertex_gain(int\
    \ vertex, T gain_if_selected, T gain_if_unselected) {\n        assert_vertex(vertex);\n\
    \        if (gain_if_selected >= gain_if_unselected) {\n            add_offset(gain_if_selected);\n\
    \            add_arc(source, vertex,\n                    nonnegative_difference(gain_if_selected,\
    \ gain_if_unselected));\n        } else {\n            add_offset(gain_if_unselected);\n\
    \            add_arc(vertex, sink,\n                    nonnegative_difference(gain_if_unselected,\
    \ gain_if_selected));\n        }\n    }\n\n    int add_auxiliary_vertex() {\n\
    \        return _vertex_count++;\n    }\n\n   public:\n    ProjectSelection()\
    \ : ProjectSelection(0) {}\n\n    explicit ProjectSelection(int project_count)\n\
    \        : _project_count(project_count), _vertex_count(project_count) {\n   \
    \     assert(project_count >= 0);\n    }\n\n    int size() const {\n        return\
    \ _project_count;\n    }\n\n    void add_gain(int project, T gain_if_selected)\
    \ {\n        add_gain(project, gain_if_selected, T());\n    }\n\n    void add_gain(int\
    \ project, T gain_if_selected, T gain_if_unselected) {\n        assert_project(project);\n\
    \        add_vertex_gain(project, gain_if_selected, gain_if_unselected);\n   \
    \ }\n\n    void add_penalty(int selected_project, int unselected_project, T penalty)\
    \ {\n        assert_project(selected_project);\n        assert_project(unselected_project);\n\
    \        add_arc(selected_project, unselected_project, penalty);\n    }\n\n  \
    \  void add_penalty_if_different(int project_a, int project_b, T penalty) {\n\
    \        assert_project(project_a);\n        assert_project(project_b);\n    \
    \    add_arc(project_a, project_b, penalty);\n        add_arc(project_b, project_a,\
    \ penalty);\n    }\n\n    void add_gain_if_same(int project_a, int project_b,\
    \ T gain) {\n        assert(gain >= T());\n        add_offset(gain);\n       \
    \ add_penalty_if_different(project_a, project_b, gain);\n    }\n\n    void add_hard_implication(int\
    \ selected_project, int required_project) {\n        assert_project(selected_project);\n\
    \        assert_project(required_project);\n        add_hard_arc(selected_project,\
    \ required_project);\n    }\n\n    void force_selected(int project) {\n      \
    \  assert_project(project);\n        add_hard_arc(source, project);\n    }\n\n\
    \    void force_unselected(int project) {\n        assert_project(project);\n\
    \        add_hard_arc(project, sink);\n    }\n\n    void add_gain_if_all_selected(const\
    \ std::vector<int>& projects, T gain) {\n        assert(gain >= T());\n      \
    \  for (int project : projects) assert_project(project);\n        if (projects.empty())\
    \ {\n            add_offset(gain);\n            return;\n        }\n        if\
    \ (projects.size() == 1) {\n            add_vertex_gain(projects[0], gain, T());\n\
    \            return;\n        }\n        if (projects.size() == 2) {\n       \
    \     add_vertex_gain(projects[0], gain, T());\n            add_arc(projects[0],\
    \ projects[1], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, gain, T());\n\
    \        for (int project : projects) add_hard_arc(auxiliary, project);\n    }\n\
    \n    void add_gain_if_all_unselected(const std::vector<int>& projects, T gain)\
    \ {\n        assert(gain >= T());\n        for (int project : projects) assert_project(project);\n\
    \        if (projects.empty()) {\n            add_offset(gain);\n            return;\n\
    \        }\n        if (projects.size() == 1) {\n            add_vertex_gain(projects[0],\
    \ T(), gain);\n            return;\n        }\n        if (projects.size() ==\
    \ 2) {\n            add_vertex_gain(projects[0], T(), gain);\n            add_arc(projects[1],\
    \ projects[0], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, T(), gain);\n\
    \        for (int project : projects) add_hard_arc(project, auxiliary);\n    }\n\
    \n    ProjectSelectionResult<T> solve() const {\n        int s = _vertex_count;\n\
    \        int t = s + 1;\n        flow::MaxFlow<T> max_flow(_vertex_count + 2);\n\
    \n        auto vertex_id = [&](int vertex) {\n            if (vertex == source)\
    \ return s;\n            if (vertex == sink) return t;\n            return vertex;\n\
    \        };\n\n        for (const auto& arc : _arcs) {\n            max_flow.add_edge(vertex_id(arc.from),\
    \ vertex_id(arc.to), arc.cap);\n        }\n\n        T hard_cap = T();\n     \
    \   if (!_hard_arcs.empty()) {\n            assert(_finite_cap_sum < std::numeric_limits<T>::max());\n\
    \            hard_cap = _finite_cap_sum + T(1);\n            for (auto [from,\
    \ to] : _hard_arcs) {\n                max_flow.add_edge(vertex_id(from), vertex_id(to),\
    \ hard_cap);\n            }\n        }\n\n        T cut_cost =\n            _hard_arcs.empty()\
    \ ? max_flow.max_flow(s, t) : max_flow.max_flow(s, t, hard_cap);\n        ProjectSelectionResult<T>\
    \ result;\n        result.feasible = _hard_arcs.empty() || cut_cost < hard_cap;\n\
    \        result.max_gain = T();\n        result.selected.assign(_project_count,\
    \ false);\n        if (!result.feasible) return result;\n\n        assert(_offset\
    \ >= std::numeric_limits<T>::lowest() + cut_cost);\n        result.max_gain =\
    \ _offset - cut_cost;\n        auto source_side = max_flow.min_cut(s);\n     \
    \   for (int project = 0; project < _project_count; project++) {\n           \
    \ result.selected[project] = source_side[project];\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace optimization\n}  // namespace m1une\n\n\
    \n#line 1 \"optimization/slope_trick.hpp\"\n\n\n\n#line 5 \"optimization/slope_trick.hpp\"\
    \n#include <functional>\n#include <optional>\n#line 11 \"optimization/slope_trick.hpp\"\
    \n\nnamespace m1une {\nnamespace optimization {\n\ntemplate <class T>\nstruct\
    \ SlopeTrickArgmin {\n    std::optional<T> left;\n    std::optional<T> right;\n\
    };\n\ntemplate <class T>\nclass SlopeTrick {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    T _minimum = T();\n    T _left_offset = T();\n\
    \    T _right_offset = T();\n    std::priority_queue<T> _left;\n    std::priority_queue<T,\
    \ std::vector<T>, std::greater<T>> _right;\n\n    T left_top() const {\n     \
    \   return _left.top() + _left_offset;\n    }\n\n    T right_top() const {\n \
    \       return _right.top() + _right_offset;\n    }\n\n    void push_left(T value)\
    \ {\n        _left.push(value - _left_offset);\n    }\n\n    void push_right(T\
    \ value) {\n        _right.push(value - _right_offset);\n    }\n\n   public:\n\
    \    SlopeTrick() = default;\n\n    T minimum() const {\n        return _minimum;\n\
    \    }\n\n    int breakpoint_count() const {\n        return int(_left.size()\
    \ + _right.size());\n    }\n\n    SlopeTrickArgmin<T> argmin() const {\n     \
    \   SlopeTrickArgmin<T> result;\n        if (!_left.empty()) result.left = left_top();\n\
    \        if (!_right.empty()) result.right = right_top();\n        return result;\n\
    \    }\n\n    void add_constant(T value) {\n        _minimum += value;\n    }\n\
    \n    void add_x_minus_a(T a) {\n        if (!_left.empty() && left_top() > a)\
    \ {\n            T old = left_top();\n            _minimum += old - a;\n     \
    \       _left.pop();\n            push_left(a);\n            push_right(old);\n\
    \        } else {\n            push_right(a);\n        }\n    }\n\n    void add_a_minus_x(T\
    \ a) {\n        if (!_right.empty() && right_top() < a) {\n            T old =\
    \ right_top();\n            _minimum += a - old;\n            _right.pop();\n\
    \            push_right(a);\n            push_left(old);\n        } else {\n \
    \           push_left(a);\n        }\n    }\n\n    void add_abs(T a) {\n     \
    \   add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void clear_left()\
    \ {\n        _left = std::priority_queue<T>();\n    }\n\n    void clear_right()\
    \ {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n};\n\n}  // namespace optimization\n\
    }  // namespace m1une\n\n\n#line 10 \"optimization/all.hpp\"\n\n\n#line 10 \"\
    verify/optimization/slope_trick.test.cpp\"\n\nusing SlopeTrick = m1une::optimization::SlopeTrick<long\
    \ long>;\n\nconstexpr int coordinate_limit = 300;\nconstexpr long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n\nint index_of(int x) {\n    return x + coordinate_limit;\n\
    }\n\nvoid check_values(const SlopeTrick& slope, const std::vector<long long>&\
    \ value) {\n    long long expected_minimum = *std::min_element(value.begin(),\
    \ value.end());\n    assert(slope.minimum() == expected_minimum);\n    for (int\
    \ x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x) == value[index_of(x)]);\n\
    \    }\n\n    auto range = slope.argmin();\n    int first = -coordinate_limit;\n\
    \    while (first <= coordinate_limit && value[index_of(first)] != expected_minimum)\
    \ first++;\n    int last = coordinate_limit;\n    while (last >= -coordinate_limit\
    \ && value[index_of(last)] != expected_minimum) last--;\n    if (range.left.has_value())\
    \ assert(*range.left == first);\n    if (range.right.has_value()) assert(*range.right\
    \ == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n    assert(slope.minimum()\
    \ == 0);\n    assert(!slope.argmin().left.has_value());\n    assert(!slope.argmin().right.has_value());\n\
    \n    slope.add_abs(3);\n    slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n\
    \    slope.add_constant(5);\n    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3)\
    \ == 14);\n    auto range = slope.argmin();\n    assert(range.left == std::optional<long\
    \ long>(3));\n    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nint main() {\n    test_basic();\n\
    \    test_operations_against_explicit_function();\n    test_merge();\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#include \"../../optimization/all.hpp\"\n\nusing SlopeTrick = m1une::optimization::SlopeTrick<long\
    \ long>;\n\nconstexpr int coordinate_limit = 300;\nconstexpr long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n\nint index_of(int x) {\n    return x + coordinate_limit;\n\
    }\n\nvoid check_values(const SlopeTrick& slope, const std::vector<long long>&\
    \ value) {\n    long long expected_minimum = *std::min_element(value.begin(),\
    \ value.end());\n    assert(slope.minimum() == expected_minimum);\n    for (int\
    \ x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x) == value[index_of(x)]);\n\
    \    }\n\n    auto range = slope.argmin();\n    int first = -coordinate_limit;\n\
    \    while (first <= coordinate_limit && value[index_of(first)] != expected_minimum)\
    \ first++;\n    int last = coordinate_limit;\n    while (last >= -coordinate_limit\
    \ && value[index_of(last)] != expected_minimum) last--;\n    if (range.left.has_value())\
    \ assert(*range.left == first);\n    if (range.right.has_value()) assert(*range.right\
    \ == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n    assert(slope.minimum()\
    \ == 0);\n    assert(!slope.argmin().left.has_value());\n    assert(!slope.argmin().right.has_value());\n\
    \n    slope.add_abs(3);\n    slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n\
    \    slope.add_constant(5);\n    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3)\
    \ == 14);\n    auto range = slope.argmin();\n    assert(range.left == std::optional<long\
    \ long>(3));\n    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nint main() {\n    test_basic();\n\
    \    test_operations_against_explicit_function();\n    test_merge();\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - optimization/all.hpp
  - optimization/alien_trick.hpp
  - optimization/hungarian.hpp
  - optimization/integer_lp.hpp
  - optimization/simplex.hpp
  - optimization/project_selection.hpp
  - flow/max_flow.hpp
  - optimization/slope_trick.hpp
  isVerificationFile: true
  path: verify/optimization/slope_trick.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 01:26:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/slope_trick.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/slope_trick.test.cpp
- /verify/verify/optimization/slope_trick.test.cpp.html
title: verify/optimization/slope_trick.test.cpp
---
