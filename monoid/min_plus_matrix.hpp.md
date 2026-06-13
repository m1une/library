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
  bundledCode: "#line 1 \"monoid/min_plus_matrix.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\
    \n// Monoid for fixed-size square matrix multiplication over the Min-Plus (Tropical)\
    \ semiring.\n// Useful for Dynamic DP (Minimization) and Shortest Path problems.\n\
    template <typename T, int N, T Inf = std::numeric_limits<T>::max() / 2>\nstruct\
    \ MinPlusMatrix {\n    using value_type = std::array<std::array<T, N>, N>;\n\n\
    \    // The identity matrix for min-plus algebra.\n    // Diagonal elements are\
    \ 0 (identity for addition).\n    // Off-diagonal elements are Inf (identity for\
    \ min).\n    static constexpr value_type id() {\n        value_type res{};\n \
    \       for (int i = 0; i < N; ++i) {\n            for (int j = 0; j < N; ++j)\
    \ {\n                res[i][j] = (i == j) ? T(0) : Inf;\n            }\n     \
    \   }\n        return res;\n    }\n\n    // Multiplies two min-plus matrices:\
    \ c_{i, j} = min_k (a_{i, k} + b_{k, j})\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        value_type res{};\n        for\
    \ (int i = 0; i < N; ++i) {\n            for (int j = 0; j < N; ++j) {\n     \
    \           res[i][j] = Inf;\n            }\n        }\n        for (int i = 0;\
    \ i < N; ++i) {\n            for (int k = 0; k < N; ++k) {\n                if\
    \ (a[i][k] == Inf) continue;\n                for (int j = 0; j < N; ++j) {\n\
    \                    if (b[k][j] == Inf) continue;\n                    res[i][j]\
    \ = std::min(res[i][j], a[i][k] + b[k][j]);\n                }\n            }\n\
    \        }\n        return res;\n    }\n\n    // Helper to securely create a matrix\
    \ initialized with Inf.\n    static constexpr value_type make_inf() {\n      \
    \  value_type res{};\n        for (int i = 0; i < N; ++i) {\n            for (int\
    \ j = 0; j < N; ++j) {\n                res[i][j] = Inf;\n            }\n    \
    \    }\n        return res;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_PLUS_MATRIX_HPP\n#define M1UNE_MONOID_MIN_PLUS_MATRIX_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <limits>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for fixed-size square matrix multiplication\
    \ over the Min-Plus (Tropical) semiring.\n// Useful for Dynamic DP (Minimization)\
    \ and Shortest Path problems.\ntemplate <typename T, int N, T Inf = std::numeric_limits<T>::max()\
    \ / 2>\nstruct MinPlusMatrix {\n    using value_type = std::array<std::array<T,\
    \ N>, N>;\n\n    // The identity matrix for min-plus algebra.\n    // Diagonal\
    \ elements are 0 (identity for addition).\n    // Off-diagonal elements are Inf\
    \ (identity for min).\n    static constexpr value_type id() {\n        value_type\
    \ res{};\n        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j\
    \ < N; ++j) {\n                res[i][j] = (i == j) ? T(0) : Inf;\n          \
    \  }\n        }\n        return res;\n    }\n\n    // Multiplies two min-plus\
    \ matrices: c_{i, j} = min_k (a_{i, k} + b_{k, j})\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res{};\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j < N; ++j)\
    \ {\n                res[i][j] = Inf;\n            }\n        }\n        for (int\
    \ i = 0; i < N; ++i) {\n            for (int k = 0; k < N; ++k) {\n          \
    \      if (a[i][k] == Inf) continue;\n                for (int j = 0; j < N; ++j)\
    \ {\n                    if (b[k][j] == Inf) continue;\n                    res[i][j]\
    \ = std::min(res[i][j], a[i][k] + b[k][j]);\n                }\n            }\n\
    \        }\n        return res;\n    }\n\n    // Helper to securely create a matrix\
    \ initialized with Inf.\n    static constexpr value_type make_inf() {\n      \
    \  value_type res{};\n        for (int i = 0; i < N; ++i) {\n            for (int\
    \ j = 0; j < N; ++j) {\n                res[i][j] = Inf;\n            }\n    \
    \    }\n        return res;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_MIN_PLUS_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min_plus_matrix.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/min_plus_matrix.hpp
layout: document
title: Min-Plus Matrix Monoid
---

## Overview

A monoid for range matrix multiplication over the Min-Plus (Tropical) semiring. 
In this algebra, the standard addition operation is replaced by `std::min`, and the standard multiplication operation is replaced by regular addition `+`.

This is highly effective for solving **Dynamic DP** problems (where state transitions involve taking the minimum of sums) or finding shortest paths over dynamic edge weights on a Segment Tree.

Merging two matrices takes $O(N^3)$ time, so $N$ should be kept small.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/min_plus_matrix.hpp"
#include <iostream>
#include <vector>

// 2x2 Min-Plus Matrix with long long
using MinMat = m1une::monoid::MinPlusMatrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<MinMat::value_type> init_data(N);
    
    // Initialize state transitions
    for (int i = 0; i < N; ++i) {
        auto mat = MinMat::make_inf();
        mat[0][0] = 5; // Transition cost from state 0 to 0
        mat[0][1] = 2; // Transition cost from state 1 to 0
        mat[1][0] = 3; // Transition cost from state 0 to 1
        mat[1][1] = 0; // Transition cost from state 1 to 1
        init_data[i] = mat;
    }

    m1une::data_structure::Segtree<MinMat> seg(init_data);

    // Get the transition matrix for the range [0, 3)
    auto res = seg.prod(0, N);
    
    // Output the shortest path cost from initial state j to final state i
    std::cout << "Cost 0 -> 0: " << res[0][0] << "\n";
    std::cout << "Cost 1 -> 0: " << res[0][1] << "\n";

    return 0;
}
```
