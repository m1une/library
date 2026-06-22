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
  bundledCode: "#line 1 \"monge/smawk.hpp\"\n\n\n\n#include <cassert>\n#include <functional>\n\
    #include <numeric>\n#include <vector>\n\nnamespace m1une {\nnamespace monge {\n\
    \nnamespace smawk_detail {\n\ntemplate <class Value, class Compare>\nvoid solve(const\
    \ std::vector<int>& rows, const std::vector<int>& columns,\n           const Value&\
    \ value, const Compare& compare, std::vector<int>& answer) {\n    if (rows.empty())\
    \ return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
    \    for (int column : columns) {\n        while (!reduced.empty()) {\n      \
    \      int row = rows[int(reduced.size()) - 1];\n            if (!compare(value(row,\
    \ column), value(row, reduced.back()))) break;\n            reduced.pop_back();\n\
    \        }\n        if (reduced.size() < rows.size()) reduced.push_back(column);\n\
    \    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size() / 2);\n\
    \    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, value, compare, answer);\n\n    int left = 0;\n\
    \    int right = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n   \
    \     if (i + 1 < int(rows.size())) {\n            while (reduced[right] != answer[rows[i\
    \ + 1]]) right++;\n        } else {\n            right = int(reduced.size()) -\
    \ 1;\n        }\n\n        int best = left;\n        for (int j = left + 1; j\
    \ <= right; j++) {\n            if (compare(value(rows[i], reduced[j]), value(rows[i],\
    \ reduced[best]))) {\n                best = j;\n            }\n        }\n  \
    \      answer[rows[i]] = reduced[best];\n        left = right;\n    }\n}\n\n}\
    \  // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    std::vector<int> answer(row_count,\
    \ -1);\n    if (row_count == 0 || column_count == 0) return answer;\n\n    std::vector<int>\
    \ rows(row_count), columns(column_count);\n    std::iota(rows.begin(), rows.end(),\
    \ 0);\n    std::iota(columns.begin(), columns.end(), 0);\n    smawk_detail::solve(rows,\
    \ columns, value, compare, answer);\n    return answer;\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> smawk_row_argmin(int row_count, int column_count, Value\
    \ value) {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return smawk_row_argmin(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ smawk_row_argmax(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return smawk_row_argmax(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\n}  // namespace\
    \ monge\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONGE_SMAWK_HPP\n#define M1UNE_MONGE_SMAWK_HPP 1\n\n#include\
    \ <cassert>\n#include <functional>\n#include <numeric>\n#include <vector>\n\n\
    namespace m1une {\nnamespace monge {\n\nnamespace smawk_detail {\n\ntemplate <class\
    \ Value, class Compare>\nvoid solve(const std::vector<int>& rows, const std::vector<int>&\
    \ columns,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (rows.empty()) return;\n\n    std::vector<int> reduced;\n\
    \    reduced.reserve(columns.size());\n    for (int column : columns) {\n    \
    \    while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!compare(value(row, column), value(row, reduced.back())))\
    \ break;\n            reduced.pop_back();\n        }\n        if (reduced.size()\
    \ < rows.size()) reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n\
    \    odd_rows.reserve(rows.size() / 2);\n    for (int i = 1; i < int(rows.size());\
    \ i += 2) odd_rows.push_back(rows[i]);\n    solve(odd_rows, reduced, value, compare,\
    \ answer);\n\n    int left = 0;\n    int right = 0;\n    for (int i = 0; i < int(rows.size());\
    \ i += 2) {\n        if (i + 1 < int(rows.size())) {\n            while (reduced[right]\
    \ != answer[rows[i + 1]]) right++;\n        } else {\n            right = int(reduced.size())\
    \ - 1;\n        }\n\n        int best = left;\n        for (int j = left + 1;\
    \ j <= right; j++) {\n            if (compare(value(rows[i], reduced[j]), value(rows[i],\
    \ reduced[best]))) {\n                best = j;\n            }\n        }\n  \
    \      answer[rows[i]] = reduced[best];\n        left = right;\n    }\n}\n\n}\
    \  // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    std::vector<int> answer(row_count,\
    \ -1);\n    if (row_count == 0 || column_count == 0) return answer;\n\n    std::vector<int>\
    \ rows(row_count), columns(column_count);\n    std::iota(rows.begin(), rows.end(),\
    \ 0);\n    std::iota(columns.begin(), columns.end(), 0);\n    smawk_detail::solve(rows,\
    \ columns, value, compare, answer);\n    return answer;\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> smawk_row_argmin(int row_count, int column_count, Value\
    \ value) {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return smawk_row_argmin(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ smawk_row_argmax(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return smawk_row_argmax(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\n}  // namespace\
    \ monge\n}  // namespace m1une\n\n#endif  // M1UNE_MONGE_SMAWK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/smawk.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/smawk.hpp
layout: document
title: SMAWK
---

## Overview

SMAWK finds an optimum in every row of an implicit totally monotone matrix.
The matrix is supplied as a callback, so the full rectangular matrix never
needs to be stored or evaluated.

The algorithm was introduced by Aggarwal, Klawe, Moran, Shor, and Wilber in
[Geometric applications of a matrix-searching algorithm](https://doi.org/10.1007/BF01840359).

For minima, total monotonicity means that the leftmost minimizing columns stay
nondecreasing after selecting any subset of rows and columns. Every Monge
matrix is totally monotone, so SMAWK is the standard linear-time row-minimum
primitive for Monge optimization.

All names are in `m1une::monge`.

## Interface

```cpp
template <class Value>
std::vector<int> smawk_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> smawk_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns the matrix entry at that position. The result
contains the selected column for every row. Ties choose the leftmost optimum.

Explicit rectangular matrices have convenience overloads:

```cpp
template <class T>
std::vector<int> smawk_row_argmin(
    const std::vector<std::vector<T>>& matrix
);

template <class T>
std::vector<int> smawk_row_argmax(
    const std::vector<std::vector<T>>& matrix
);
```

The generic form accepts a strict comparator:

```cpp
template <class Value, class Compare = std::less<>>
std::vector<int> smawk_row_optima(
    int row_count,
    int column_count,
    Value value,
    Compare compare = Compare()
);
```

`compare(a, b)` must return whether `a` is strictly better than `b`.

If there are no columns, every answer is `-1`. If there are no rows, the result
is empty.

## Requirements

For `smawk_row_argmin`, the implicit matrix must be totally monotone for
leftmost minima. For `smawk_row_argmax`, it must be totally monotone under the
reversed comparison. The implementation does not verify this precondition.

The callback may return values by value or by reference. Values only need to
support the selected comparison.

## Complexity

SMAWK uses $O(H + W)$ callback evaluations and $O(H + W)$ additional memory for
an `H` by `W` matrix. This assumes each callback evaluation and comparison take
$O(1)$ time.

## Example

```cpp
#include "monge/smawk.hpp"
#include <iostream>

int main() {
    int rows = 5;
    int columns = 8;
    auto value = [](int row, int column) {
        long long difference = row * 2LL - column;
        return difference * difference;
    };

    auto argmin = m1une::monge::smawk_row_argmin(rows, columns, value);
    for (int column : argmin) std::cout << column << "\n";
}
```
