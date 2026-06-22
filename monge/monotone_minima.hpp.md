---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  - icon: ':heavy_check_mark:'
    path: monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
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
  bundledCode: "#line 1 \"monge/monotone_minima.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\nnamespace m1une {\nnamespace monge\
    \ {\n\nnamespace monotone_minima_detail {\n\ntemplate <class Value, class Compare>\n\
    void solve(int row_left, int row_right, int column_left, int column_right,\n \
    \          const Value& value, const Compare& compare, std::vector<int>& answer)\
    \ {\n    if (row_left == row_right) return;\n    int row = (row_left + row_right)\
    \ / 2;\n    int best = column_left;\n    for (int column = column_left + 1; column\
    \ < column_right; column++) {\n        if (compare(value(row, column), value(row,\
    \ best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONGE_MONOTONE_MINIMA_HPP\n#define M1UNE_MONGE_MONOTONE_MINIMA_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace monge {\n\nnamespace monotone_minima_detail {\n\ntemplate\
    \ <class Value, class Compare>\nvoid solve(int row_left, int row_right, int column_left,\
    \ int column_right,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (row_left == row_right) return;\n    int row = (row_left +\
    \ row_right) / 2;\n    int best = column_left;\n    for (int column = column_left\
    \ + 1; column < column_right; column++) {\n        if (compare(value(row, column),\
    \ value(row, best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n#endif  // M1UNE_MONGE_MONOTONE_MINIMA_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/monotone_minima.hpp
  requiredBy:
  - monge/all.hpp
  - monge/divide_and_conquer_optimization.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/monotone_minima.hpp
layout: document
title: Monotone Minima
---

## Overview

The divide-and-conquer monotone-minima algorithm finds one optimum in every
row when the leftmost optimal columns are known to be nondecreasing.

Its precondition is weaker and sometimes easier to establish than total
monotonicity, although its asymptotic complexity is slightly worse than SMAWK.
It is commonly used for divide-and-conquer DP optimization.

## Interface

```cpp
template <class Value>
std::vector<int> monotone_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> monotone_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns one implicit matrix entry. The result stores the
optimal column for each row, choosing the leftmost optimum on ties.

Both functions also have convenience overloads accepting a rectangular
`std::vector<std::vector<T>>`.

`monotone_row_optima` is the generic overload accepting a strict comparator.

If there are no columns, every answer is `-1`.

## Requirements

The leftmost optimal columns under the chosen comparison must form a
nondecreasing sequence. The implementation does not verify this condition.

Unlike SMAWK, this function does not require every submatrix to preserve
monotonicity.

## Complexity

For an `H` by `W` implicit matrix, the algorithm uses
$O((H + W)\log H)$ callback evaluations in the general case and $O(H)$
additional memory including the result and recursion stack.

## Example

```cpp
#include "monge/monotone_minima.hpp"
#include <vector>

int main() {
    std::vector<long long> previous = {0, 3, 4, 8, 10};
    auto transition = [&](int row, int column) {
        long long distance = row - column;
        return previous[column] + distance * distance;
    };

    auto opt = m1une::monge::monotone_row_argmin(5, 5, transition);
}
```
