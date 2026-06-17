---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
    }  // namespace optimization\n}  // namespace m1une\n\n\n#line 5 \"optimization/all.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_OPTIMIZATION_ALL_HPP

    #define M1UNE_OPTIMIZATION_ALL_HPP 1


    #include "optimization/hungarian.hpp"


    #endif  // M1UNE_OPTIMIZATION_ALL_HPP

    '
  dependsOn:
  - optimization/hungarian.hpp
  isVerificationFile: false
  path: optimization/all.hpp
  requiredBy: []
  timestamp: '2026-06-17 10:25:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
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
