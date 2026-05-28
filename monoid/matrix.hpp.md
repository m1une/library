---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/matrix.hpp\"\n\n\n\n#include <array>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for fixed-size square matrix multiplication.\n\
    template <typename T, int N>\nstruct Matrix {\n    using value_type = std::array<std::array<T,\
    \ N>, N>;\n\n    // The identity element is the identity matrix.\n    static constexpr\
    \ value_type id() {\n        value_type res{};\n        for (int i = 0; i < N;\
    \ ++i) {\n            res[i][i] = T(1);\n        }\n        return res;\n    }\n\
    \n    // Multiplies two matrices: a * b\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        value_type res{};\n        for\
    \ (int i = 0; i < N; ++i) {\n            for (int k = 0; k < N; ++k) {\n     \
    \           for (int j = 0; j < N; ++j) {\n                    res[i][j] += a[i][k]\
    \ * b[k][j];\n                }\n            }\n        }\n        return res;\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MATRIX_HPP\n#define M1UNE_MONOID_MATRIX_HPP 1\n\n#include\
    \ <array>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for fixed-size\
    \ square matrix multiplication.\ntemplate <typename T, int N>\nstruct Matrix {\n\
    \    using value_type = std::array<std::array<T, N>, N>;\n\n    // The identity\
    \ element is the identity matrix.\n    static constexpr value_type id() {\n  \
    \      value_type res{};\n        for (int i = 0; i < N; ++i) {\n            res[i][i]\
    \ = T(1);\n        }\n        return res;\n    }\n\n    // Multiplies two matrices:\
    \ a * b\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        value_type res{};\n        for (int i = 0; i < N; ++i) {\n   \
    \         for (int k = 0; k < N; ++k) {\n                for (int j = 0; j < N;\
    \ ++j) {\n                    res[i][j] += a[i][k] * b[k][j];\n              \
    \  }\n            }\n        }\n        return res;\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/matrix.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:15:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/matrix.hpp
layout: document
title: Matrix Monoid
---

## Overview

A monoid for range matrix multiplication. The underlying `value_type` is an `N x N` `std::array`. This is extremely useful for Dynamic DP, where state transitions can be represented as matrix multiplications over a segment tree.

Merging two matrices takes $O(N^3)$ time, so $N$ should be small (typically $N \le 4$).

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/matrix.hpp"
#include <iostream>
#include <vector>

// 2x2 Matrix with long long
using Mat = m1une::monoid::Matrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<Mat::value_type> init_data(N);
    
    // Initialize matrices (e.g., Fibonacci transition matrices)
    for (int i = 0; i < N; ++i) {
        init_data[i] = {{{1, 1}, {1, 0}}};
    }

    m1une::data_structure::Segtree<Mat> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << res[0][0] << " " << res[0][1] << "\n";
    std::cout << res[1][0] << " " << res[1][1] << "\n";

    return 0;
}
```
