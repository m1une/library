---
title: Hungarian Algorithm
documentation_of: ../../optimization/hungarian.hpp
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
| `hungarian_min` | `template <class T> HungarianResult<T> hungarian_min(const std::vector<std::vector<T>>& cost)` | Returns a minimum-cost assignment. | $O(\min(H,W)^2 \max(H,W))$ |
| `hungarian_max` | `template <class T> HungarianResult<T> hungarian_max(const std::vector<std::vector<T>>& cost)` | Returns a maximum-cost assignment. | $O(\min(H,W)^2 \max(H,W))$ |
| `hungarian` | `template <class T> HungarianResult<T> hungarian(const std::vector<std::vector<T>>& cost)` | Alias of `hungarian_min`. | $O(\min(H,W)^2 \max(H,W))$ |

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
