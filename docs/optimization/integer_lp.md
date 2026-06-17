---
title: Integer Linear Programming
documentation_of: ../../optimization/integer_lp.hpp
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
