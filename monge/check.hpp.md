---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/check.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace monge {\n\ntemplate <class Value>\nbool is_monge(int\
    \ row_count, int column_count, Value value) {\n    assert(row_count >= 0);\n \
    \   assert(column_count >= 0);\n    for (int row = 0; row + 1 < row_count; row++)\
    \ {\n        for (int column = 0; column + 1 < column_count; column++) {\n   \
    \         if (value(row, column) + value(row + 1, column + 1) >\n            \
    \    value(row, column + 1) + value(row + 1, column)) {\n                return\
    \ false;\n            }\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ Value>\nbool is_anti_monge(int row_count, int column_count, Value value) {\n\
    \    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int row\
    \ = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column + 1\
    \ < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) <\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class T>\nbool is_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONGE_CHECK_HPP\n#define M1UNE_MONGE_CHECK_HPP 1\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace monge {\n\ntemplate\
    \ <class Value>\nbool is_monge(int row_count, int column_count, Value value) {\n\
    \    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int row\
    \ = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column + 1\
    \ < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) >\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
    \ int column_count, Value value) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    for (int row = 0; row + 1 < row_count; row++) {\n        for (int\
    \ column = 0; column + 1 < column_count; column++) {\n            if (value(row,\
    \ column) + value(row + 1, column + 1) <\n                value(row, column +\
    \ 1) + value(row + 1, column)) {\n                return false;\n            }\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_monge(row_count,\
    \ column_count,\n                    [&](int row, int column) -> const T& { return\
    \ matrix[row][column]; });\n}\n\ntemplate <class T>\nbool is_anti_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_anti_monge(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONGE_CHECK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/check.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/check.hpp
layout: document
title: Monge Checks
---

## Overview

This header checks the Monge or anti-Monge quadrangle inequality.

An `H` by `W` matrix `A` is Monge when

$$
A[i][j] + A[k][l] \le A[i][l] + A[k][j]
$$

for every `i < k` and `j < l`. It is enough to test adjacent rows and columns,
which gives an $O(HW)$ checker.

Anti-Monge reverses the inequality and is useful for row maxima.

## Interface

Implicit matrices:

```cpp
template <class Value>
bool is_monge(int row_count, int column_count, Value value);

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value);
```

Explicit rectangular matrices:

```cpp
template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix);

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix);
```

Empty matrices and matrices with fewer than two rows or columns satisfy both
properties vacuously.

The element type must support addition and comparison. Intermediate sums must
fit in the element type.

## Complexity

$O(HW)$ time and $O(1)$ additional memory.
