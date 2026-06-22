---
title: Matrix Linear Algebra
documentation_of: ../../matrix/linear_algebra.hpp
---

## Overview

This header provides Gaussian-elimination algorithms for `Matrix<T>`:

* reduced row echelon form;
* rank;
* determinant;
* inverse;
* solving linear systems, including inconsistent and underdetermined systems.

These algorithms require `T` to behave like a field. Good choices are a
floating-point type or `ModInt` with a prime modulus. Plain integer types are
not suitable because division truncates.

## Zero Tests and Precision

For non-floating types, a value is zero exactly when it equals `T()`.
`default_epsilon<T>()` therefore returns `T()` for these types.

For `float`, `double`, and `long double`, values with absolute value at most
`eps` are treated as zero, and partial pivoting chooses the largest available
absolute value in each column. `default_epsilon<T>()` returns `1e-10`, which is
also the default argument. Pass an explicit tolerance when the scale or
accuracy requirements of the problem differ:

```cpp
auto rank = m1une::matrix::matrix_rank(matrix, 1e-12);
```

Floating-point answers remain approximate. For exact arithmetic modulo a
prime, use `ModInt`.

## Row Reduction and Rank

`reduced_row_echelon_form(matrix, eps)` returns `RowReduction<T>`.

| Member | Meaning |
| --- | --- |
| `matrix` | The reduced row echelon form. |
| `pivot_columns` | Pivot column indices from left to right. |
| `rank()` | The number of pivots. |

`matrix_rank(matrix, eps)` computes only the rank and avoids eliminating above
each pivot, making it faster than constructing the full reduced form.

For an `H x W` matrix, both operations take
$O(HW\min(H, W))$ time. The returned objects use $O(HW)$ memory because the
input is copied and preserved.

## Determinant and Inverse

| Function | Result | Complexity |
| --- | --- | --- |
| `determinant(matrix, eps)` | The determinant of a square matrix. The determinant of the `0 x 0` matrix is `1`. | $O(N^3)$ time, $O(N^2)$ memory |
| `inverse(matrix, eps)` | `std::optional<Matrix<T>>`; empty when the square matrix is singular. | $O(N^3)$ time, $O(N^2)$ memory |

## Linear Systems

`solve_linear_system(coefficients, constants, eps)` solves

$$
A x = b.
$$

The number of rows in `coefficients` must equal `constants.size()`. Rectangular
coefficient matrices are supported.

The returned `LinearSystemResult<T>` contains:

| Member / Method | Meaning |
| --- | --- |
| `consistent` | Whether at least one solution exists. |
| `particular_solution` | One solution when the system is consistent. Free variables are set to zero. |
| `nullspace_basis` | Basis vectors for all homogeneous solutions of `A x = 0`. |
| `pivot_columns` | Pivot variable indices. |
| `rank()` | Rank of `A`. |
| `nullity()` | Number of free variables when the system is consistent. |
| `has_unique_solution()` | Whether exactly one solution exists. |

When the system is consistent, every solution can be written as the particular
solution plus a linear combination of `nullspace_basis`.
When it is inconsistent, `particular_solution` and `nullspace_basis` are empty.

The complexity is $O(HW\min(H, W))$ time and $O(HW)$ memory.

## Example

```cpp
#include "math/modint.hpp"
#include "matrix/linear_algebra.hpp"

#include <iostream>
#include <vector>

int main() {
    using mint = m1une::math::modint998244353;
    m1une::matrix::Matrix<mint> coefficients(2, 2);
    coefficients[0][0] = 2;
    coefficients[0][1] = 1;
    coefficients[1][0] = 1;
    coefficients[1][1] = 3;

    std::vector<mint> constants = {5, 7};
    auto result =
        m1une::matrix::solve_linear_system(coefficients, constants);

    if (result.has_unique_solution()) {
        std::cout << result.particular_solution[0] << ' '
                  << result.particular_solution[1] << '\n';
    }
}
```
