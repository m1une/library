---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/hungarian.test.cpp
    title: verify/optimization/hungarian.test.cpp
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
  bundledCode: "#line 1 \"optimization/hungarian.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace optimization {\n\ntemplate <class T>\nstruct HungarianResult\
    \ {\n    T cost;\n    std::vector<int> row_to_col;\n    std::vector<int> col_to_row;\n\
    \n    int matching_size() const {\n        int result = 0;\n        for (int col\
    \ : row_to_col) {\n            if (col != -1) result++;\n        }\n        return\
    \ result;\n    }\n\n    std::vector<std::pair<int, int>> matching() const {\n\
    \        std::vector<std::pair<int, int>> result;\n        for (int row = 0; row\
    \ < int(row_to_col.size()); row++) {\n            if (row_to_col[row] != -1) result.push_back({row,\
    \ row_to_col[row]});\n        }\n        return result;\n    }\n};\n\nnamespace\
    \ detail {\n\ntemplate <class T>\nT assignment_cost(const std::vector<std::vector<T>>&\
    \ cost, const std::vector<int>& row_to_col) {\n    T result = T();\n    for (int\
    \ row = 0; row < int(row_to_col.size()); row++) {\n        if (row_to_col[row]\
    \ != -1) result += cost[row][row_to_col[row]];\n    }\n    return result;\n}\n\
    \n}  // namespace detail\n\ntemplate <class T>\nHungarianResult<T> hungarian_min(const\
    \ std::vector<std::vector<T>>& cost) {\n    int row_count = int(cost.size());\n\
    \    int col_count = row_count == 0 ? 0 : int(cost[0].size());\n    for (const\
    \ auto& row : cost) assert(int(row.size()) == col_count);\n\n    HungarianResult<T>\
    \ result;\n    result.cost = T();\n    result.row_to_col.assign(row_count, -1);\n\
    \    result.col_to_row.assign(col_count, -1);\n    if (row_count == 0 || col_count\
    \ == 0) return result;\n\n    bool transposed = row_count > col_count;\n    int\
    \ n = transposed ? col_count : row_count;\n    int m = transposed ? row_count\
    \ : col_count;\n    T inf = std::numeric_limits<T>::max() / T(4);\n\n    std::vector<T>\
    \ u(n + 1, T()), v(m + 1, T()), minv(m + 1);\n    std::vector<int> p(m + 1, 0),\
    \ way(m + 1, 0);\n\n    auto value = [&](int i, int j) -> T {\n        return\
    \ transposed ? cost[j][i] : cost[i][j];\n    };\n\n    for (int i = 1; i <= n;\
    \ i++) {\n        p[0] = i;\n        int j0 = 0;\n        std::fill(minv.begin(),\
    \ minv.end(), inf);\n        std::vector<char> used(m + 1, false);\n\n       \
    \ do {\n            used[j0] = true;\n            int i0 = p[j0];\n          \
    \  int j1 = 0;\n            T delta = inf;\n\n            for (int j = 1; j <=\
    \ m; j++) {\n                if (used[j]) continue;\n                T cur = value(i0\
    \ - 1, j - 1) - u[i0] - v[j];\n                if (cur < minv[j]) {\n        \
    \            minv[j] = cur;\n                    way[j] = j0;\n              \
    \  }\n                if (minv[j] < delta) {\n                    delta = minv[j];\n\
    \                    j1 = j;\n                }\n            }\n\n           \
    \ for (int j = 0; j <= m; j++) {\n                if (used[j]) {\n           \
    \         u[p[j]] += delta;\n                    v[j] -= delta;\n            \
    \    } else {\n                    minv[j] -= delta;\n                }\n    \
    \        }\n            j0 = j1;\n        } while (p[j0] != 0);\n\n        do\
    \ {\n            int j1 = way[j0];\n            p[j0] = p[j1];\n            j0\
    \ = j1;\n        } while (j0 != 0);\n    }\n\n    for (int j = 1; j <= m; j++)\
    \ {\n        if (p[j] == 0) continue;\n        int i = p[j] - 1;\n        int\
    \ matched = j - 1;\n        if (transposed) {\n            int row = matched;\n\
    \            int col = i;\n            result.row_to_col[row] = col;\n       \
    \     result.col_to_row[col] = row;\n        } else {\n            int row = i;\n\
    \            int col = matched;\n            result.row_to_col[row] = col;\n \
    \           result.col_to_row[col] = row;\n        }\n    }\n    result.cost =\
    \ detail::assignment_cost(cost, result.row_to_col);\n    return result;\n}\n\n\
    template <class T>\nHungarianResult<T> hungarian_max(const std::vector<std::vector<T>>&\
    \ cost) {\n    std::vector<std::vector<T>> negated = cost;\n    for (auto& row\
    \ : negated) {\n        for (auto& x : row) x = -x;\n    }\n    auto result =\
    \ hungarian_min(negated);\n    result.cost = detail::assignment_cost(cost, result.row_to_col);\n\
    \    return result;\n}\n\ntemplate <class T>\nHungarianResult<T> hungarian(const\
    \ std::vector<std::vector<T>>& cost) {\n    return hungarian_min(cost);\n}\n\n\
    }  // namespace optimization\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_HUNGARIAN_HPP\n#define M1UNE_OPTIMIZATION_HUNGARIAN_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace optimization {\n\ntemplate <class\
    \ T>\nstruct HungarianResult {\n    T cost;\n    std::vector<int> row_to_col;\n\
    \    std::vector<int> col_to_row;\n\n    int matching_size() const {\n       \
    \ int result = 0;\n        for (int col : row_to_col) {\n            if (col !=\
    \ -1) result++;\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> matching() const {\n        std::vector<std::pair<int, int>> result;\n\
    \        for (int row = 0; row < int(row_to_col.size()); row++) {\n          \
    \  if (row_to_col[row] != -1) result.push_back({row, row_to_col[row]});\n    \
    \    }\n        return result;\n    }\n};\n\nnamespace detail {\n\ntemplate <class\
    \ T>\nT assignment_cost(const std::vector<std::vector<T>>& cost, const std::vector<int>&\
    \ row_to_col) {\n    T result = T();\n    for (int row = 0; row < int(row_to_col.size());\
    \ row++) {\n        if (row_to_col[row] != -1) result += cost[row][row_to_col[row]];\n\
    \    }\n    return result;\n}\n\n}  // namespace detail\n\ntemplate <class T>\n\
    HungarianResult<T> hungarian_min(const std::vector<std::vector<T>>& cost) {\n\
    \    int row_count = int(cost.size());\n    int col_count = row_count == 0 ? 0\
    \ : int(cost[0].size());\n    for (const auto& row : cost) assert(int(row.size())\
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
    }  // namespace optimization\n}  // namespace m1une\n\n#endif  // M1UNE_OPTIMIZATION_HUNGARIAN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: optimization/hungarian.hpp
  requiredBy:
  - optimization/all.hpp
  timestamp: '2026-06-17 10:25:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/simplex.test.cpp
  - verify/optimization/hungarian.test.cpp
documentation_of: optimization/hungarian.hpp
layout: document
title: Hungarian Algorithm
---

## Overview

`hungarian_min(cost)` solves the assignment problem for a rectangular cost
matrix. It chooses distinct columns for rows, or distinct rows for columns,
minimizing the total selected cost.

If the matrix has `H` rows and `W` columns, the algorithm creates
`min(H, W)` pairs and completely matches the smaller side. When `H <= W`,
every row is assigned to one column. When `H > W`, every column is assigned to
one row and the remaining rows are left unassigned.

`hungarian_max(cost)` solves the corresponding maximization problem by
negating costs internally. `hungarian(cost)` is an alias of
`hungarian_min(cost)`.

## Interface

The input is a rectangular `std::vector<std::vector<T>>`. All rows must have
the same length. `T` should be a signed numeric type with enough range for
subtraction and summation, such as `long long` or `long double`.

`HungarianResult<T>` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `cost` | `T` | Total cost of the returned assignment. |
| `row_to_col` | `std::vector<int>` | `row_to_col[i]` is the column assigned to row `i`, or `-1` if row `i` is unassigned. |
| `col_to_row` | `std::vector<int>` | `col_to_row[j]` is the row assigned to column `j`, or `-1` if column `j` is unassigned. |
| `matching_size` | `int matching_size() const` | Returns the number of assigned pairs. |
| `matching` | `std::vector<std::pair<int, int>> matching() const` | Returns `(row, column)` pairs. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `hungarian_min` | `template <class T> HungarianResult<T> hungarian_min(const std::vector<std::vector<T>>& cost)` | Returns a minimum-cost assignment. | $O(\min(H, W)^2 \max(H, W))$ |
| `hungarian_max` | `template <class T> HungarianResult<T> hungarian_max(const std::vector<std::vector<T>>& cost)` | Returns a maximum-cost assignment. | $O(\min(H, W)^2 \max(H, W))$ |
| `hungarian` | `template <class T> HungarianResult<T> hungarian(const std::vector<std::vector<T>>& cost)` | Alias of `hungarian_min`. | $O(\min(H, W)^2 \max(H, W))$ |

## Example

```cpp
#include "optimization/hungarian.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {4, 1, 3},
        {2, 0, 5},
        {3, 2, 2},
    };

    auto result = m1une::optimization::hungarian_min(cost);
    std::cout << result.cost << "\n";  // 5
    for (auto [row, col] : result.matching()) {
        std::cout << row << " " << col << "\n";
    }
}
```
