---
title: Simplex Algorithm
documentation_of: ../../optimization/simplex.hpp
---

## Overview

`simplex_maximize(a, b, c)` solves a linear programming problem in standard
inequality form:

$$
\begin{array}{ll}
\text{maximize} & c^T x \\
\text{subject to} & A x \le b \\
& x \ge 0
\end{array}
$$

The implementation uses two-phase simplex, so constraints with negative
right-hand sides are allowed and infeasible problems are detected.

`simplex_minimize(a, b, c)` solves the corresponding minimization problem with
the same constraints by maximizing the negated objective. `simplex(a, b, c)` is
an alias of `simplex_maximize(a, b, c)`.

## Interface

The inputs are:

| Argument | Type | Meaning |
| --- | --- | --- |
| `a` | `std::vector<std::vector<T>>` | Constraint matrix `A`. |
| `b` | `std::vector<T>` | Right-hand side vector. Constraint `i` is `a[i] * x <= b[i]`. |
| `c` | `std::vector<T>` | Objective coefficients. |
| `eps` | `T` | Optional tolerance. The default is `1e-10`. |

`a.size()` must equal `b.size()`, and every row of `a` must have
`c.size()` entries. `T` must be a floating-point type, such as `double` or
`long double`.

`SimplexStatus` has these values:

| Value | Meaning |
| --- | --- |
| `SimplexStatus::Optimal` | A finite optimum was found. |
| `SimplexStatus::Infeasible` | No vector satisfies all constraints. |
| `SimplexStatus::Unbounded` | The objective is unbounded in the requested direction. |

`SimplexResult<T>` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `status` | `SimplexStatus` | Solver status. |
| `objective_value` | `T` | Optimal objective value when `status` is `Optimal`. |
| `variables` | `std::vector<T>` | Optimal variable values when `status` is `Optimal`. |
| `is_optimal` | `bool is_optimal() const` | Returns whether the status is `Optimal`. |
| `is_infeasible` | `bool is_infeasible() const` | Returns whether the status is `Infeasible`. |
| `is_unbounded` | `bool is_unbounded() const` | Returns whether the status is `Unbounded`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `simplex_maximize` | `template <class T> SimplexResult<T> simplex_maximize(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, T eps = T(1e-10))` | Maximizes `c^T x` subject to `A x <= b` and `x >= 0`. | $O(P \cdot H \cdot W)$ where `P` is the number of pivots, `H = b.size()`, and `W = c.size()`. Simplex has exponential worst-case behavior. |
| `simplex_minimize` | `template <class T> SimplexResult<T> simplex_minimize(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, T eps = T(1e-10))` | Minimizes `c^T x` under the same constraints. | Same as above. |
| `simplex` | `template <class T> SimplexResult<T> simplex(const std::vector<std::vector<T>>& a, const std::vector<T>& b, const std::vector<T>& c, T eps = T(1e-10))` | Alias of `simplex_maximize`. | Same as above. |

## Example

```cpp
#include "optimization/simplex.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<long double>> a = {
        {1, 1},
        {1, 0},
        {0, 1},
    };
    std::vector<long double> b = {4, 2, 3};
    std::vector<long double> c = {3, 2};

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    if (result.is_optimal()) {
        std::cout << result.objective_value << "\n";  // 10
        std::cout << result.variables[0] << " " << result.variables[1] << "\n";
    }
}
```
