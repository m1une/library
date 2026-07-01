---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: matrix/all.hpp
    title: Matrix Bundle
  - icon: ':x:'
    path: matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/matrix/inverse_matrix.test.cpp
    title: verify/matrix/inverse_matrix.test.cpp
  - icon: ':x:'
    path: verify/matrix/matrix.test.cpp
    title: verify/matrix/matrix.test.cpp
  - icon: ':x:'
    path: verify/matrix/matrix_product.test.cpp
    title: verify/matrix/matrix_product.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matrix/matrix.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace matrix {\n\ntemplate <class T>\nclass Matrix {\n   private:\n\
    \    int _rows;\n    int _cols;\n    std::vector<T> _data;\n\n    static std::size_t\
    \ storage_size(int rows, int cols) {\n        assert(rows >= 0);\n        assert(cols\
    \ >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n\
    \    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int\
    \ rows, int cols, const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
    \ cols), value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n\
    \        : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        assert(_data.size() == std::size_t(rows)\
    \ * std::size_t(cols));\n    }\n\n    explicit Matrix(const std::vector<std::vector<T>>&\
    \ values)\n        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),\n\
    \          _data(storage_size(_rows, _cols)) {\n        for (int row = 0; row\
    \ < _rows; row++) {\n            assert(int(values[std::size_t(row)].size()) ==\
    \ _cols);\n            for (int col = 0; col < _cols; col++) {\n             \
    \   (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n        \
    \    }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n  \
    \  }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_MATRIX_HPP\n#define M1UNE_MATRIX_MATRIX_HPP 1\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nclass\
    \ Matrix {\n   private:\n    int _rows;\n    int _cols;\n    std::vector<T> _data;\n\
    \n    static std::size_t storage_size(int rows, int cols) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n\
    \    }\n\n   public:\n    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0)\
    \ {}\n\n    Matrix(int rows, int cols, const T& value = T())\n        : _rows(rows),\
    \ _cols(cols), _data(storage_size(rows, cols), value) {}\n\n    Matrix(int rows,\
    \ int cols, std::vector<T> values)\n        : _rows(rows), _cols(cols), _data(std::move(values))\
    \ {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        assert(_data.size()\
    \ == std::size_t(rows) * std::size_t(cols));\n    }\n\n    explicit Matrix(const\
    \ std::vector<std::vector<T>>& values)\n        : _rows(int(values.size())), _cols(values.empty()\
    \ ? 0 : int(values[0].size())),\n          _data(storage_size(_rows, _cols)) {\n\
    \        for (int row = 0; row < _rows; row++) {\n            assert(int(values[std::size_t(row)].size())\
    \ == _cols);\n            for (int col = 0; col < _cols; col++) {\n          \
    \      (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n     \
    \       }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n\
    \    }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n#endif  // M1UNE_MATRIX_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matrix/matrix.hpp
  requiredBy:
  - matrix/all.hpp
  - matrix/linear_algebra.hpp
  timestamp: '2026-06-22 14:42:39+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/matrix/inverse_matrix.test.cpp
  - verify/matrix/matrix.test.cpp
  - verify/matrix/matrix_product.test.cpp
documentation_of: matrix/matrix.hpp
layout: document
title: Dense Matrix
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
