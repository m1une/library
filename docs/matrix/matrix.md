---
title: Dense Matrix
documentation_of: ../../matrix/matrix.hpp
---

## Overview

`Matrix<T>` is a dynamically sized dense matrix for competitive programming.
Its entries are stored contiguously in row-major order. Matrix multiplication
uses the loop order `row`, `middle`, `column`, so both the output row and the
selected row of the right-hand matrix are traversed sequentially.

The class supports rectangular matrices, arithmetic, transposition,
matrix-vector products, and binary exponentiation of square matrices.

Use `Matrix<m1une::math::modint998244353>` when answers are taken modulo a
prime. Integer matrices are also supported, but ordinary integer overflow is
not detected.

## Construction and Access

| Interface | Description | Complexity |
| --- | --- | --- |
| `Matrix()` | Constructs a matrix with shape `0 x 0`. | $O(1)$ |
| `Matrix(rows, cols, value)` | Constructs a matrix filled with `value`. The default value is `T()`. | $O(rows \cdot cols)$ |
| `Matrix(rows, cols, values)` | Constructs from a flat row-major `std::vector<T>`. Its size must be `rows * cols`. | $O(1)$ when moved |
| `Matrix(values)` | Constructs from a rectangular `std::vector<std::vector<T>>`. | $O(rows \cdot cols)$ |
| `rows()`, `cols()` | Returns the dimensions. | $O(1)$ |
| `empty()` | Returns whether at least one dimension is zero. | $O(1)$ |
| `matrix[row][col]`, `matrix(row, col)` | Accesses one entry. | $O(1)$ |
| `data()` | Returns the flat row-major storage. | $O(1)$ |

Dimensions and indices are checked with `assert`.

## Operations

| Interface | Description | Complexity |
| --- | --- | --- |
| `Matrix<T>::identity(n)` | Returns the `n x n` identity matrix. | $O(n^2)$ |
| `transposed()` | Returns the transpose. | $O(rows \cdot cols)$ |
| `swap_rows(i, j)` | Exchanges two rows. | $O(cols)$ |
| `+`, `-`, `+=`, `-=` | Entrywise matrix addition or subtraction. Shapes must match. | $O(rows \cdot cols)$ |
| `matrix * scalar`, `scalar * matrix`, `matrix / scalar` | Applies a scalar operation to every entry. | $O(rows \cdot cols)$ |
| `lhs * rhs`, `lhs *= rhs` | Matrix multiplication. `lhs.cols()` must equal `rhs.rows()`. The shape of `lhs` can change after `*=`. | $O(lhs.rows() \cdot lhs.cols() \cdot rhs.cols())$ |
| `matrix * vector` | Multiplies a column vector. | $O(rows \cdot cols)$ |
| `vector * matrix` | Multiplies a row vector. | $O(rows \cdot cols)$ |
| `==`, `!=` | Compares shapes and every entry. | $O(rows \cdot cols)$ |
| `pow(exponent)` | Raises a square matrix to a nonnegative integer power. | $O(n^3 \log exponent)$ |

The arithmetic type `T` must provide the operations used by the selected
method. In particular, multiplication needs `T()`, `+`, `*`, and equality with
zero. Division is only needed by `/` and by the linear algebra header.

## Example: Fibonacci Numbers

```cpp
#include "math/modint.hpp"
#include "matrix/matrix.hpp"

#include <cstdint>
#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    m1une::matrix::Matrix<mint> transition(2, 2);
    transition[0][0] = 1;
    transition[0][1] = 1;
    transition[1][0] = 1;

    std::uint64_t n;
    std::cin >> n;
    auto powered = transition.pow(n);
    std::cout << powered[0][1] << '\n';
}
```

For `n = 0`, this prints `0`; otherwise it prints the `n`-th Fibonacci number
modulo `998244353`.
