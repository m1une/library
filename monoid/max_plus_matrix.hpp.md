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
  bundledCode: "#line 1 \"monoid/max_plus_matrix.hpp\"\n\n\n\n#include <array>\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for fixed-size square matrix multiplication over the Max-Plus semiring.\n\
    // Useful for Dynamic DP (Maximization) and Longest Path problems.\ntemplate <typename\
    \ T, int N, T MinInf = std::numeric_limits<T>::lowest() / 2>\nstruct MaxPlusMatrix\
    \ {\n    using value_type = std::array<std::array<T, N>, N>;\n\n    // The identity\
    \ matrix for max-plus algebra.\n    // Diagonal elements are 0 (identity for addition).\n\
    \    // Off-diagonal elements are MinInf (identity for max).\n    static constexpr\
    \ value_type id() {\n        value_type res{};\n        for (int i = 0; i < N;\
    \ ++i) {\n            for (int j = 0; j < N; ++j) {\n                res[i][j]\
    \ = (i == j) ? T(0) : MinInf;\n            }\n        }\n        return res;\n\
    \    }\n\n    // Multiplies two max-plus matrices: c_{i, j} = max_k (a_{i, k}\
    \ + b_{k, j})\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        value_type res{};\n        for (int i = 0; i < N; ++i) {\n   \
    \         for (int j = 0; j < N; ++j) {\n                res[i][j] = MinInf;\n\
    \            }\n        }\n        for (int i = 0; i < N; ++i) {\n           \
    \ for (int k = 0; k < N; ++k) {\n                if (a[i][k] == MinInf) continue;\n\
    \                for (int j = 0; j < N; ++j) {\n                    if (b[k][j]\
    \ == MinInf) continue;\n                    res[i][j] = std::max(res[i][j], a[i][k]\
    \ + b[k][j]);\n                }\n            }\n        }\n        return res;\n\
    \    }\n\n    // Helper to securely create a matrix initialized with MinInf.\n\
    \    static constexpr value_type make_inf() {\n        value_type res{};\n   \
    \     for (int i = 0; i < N; ++i) {\n            for (int j = 0; j < N; ++j) {\n\
    \                res[i][j] = MinInf;\n            }\n        }\n        return\
    \ res;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MAX_PLUS_MATRIX_HPP\n#define M1UNE_MONOID_MAX_PLUS_MATRIX_HPP\
    \ 1\n\n#include <array>\n#include <algorithm>\n#include <limits>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for fixed-size square matrix multiplication\
    \ over the Max-Plus semiring.\n// Useful for Dynamic DP (Maximization) and Longest\
    \ Path problems.\ntemplate <typename T, int N, T MinInf = std::numeric_limits<T>::lowest()\
    \ / 2>\nstruct MaxPlusMatrix {\n    using value_type = std::array<std::array<T,\
    \ N>, N>;\n\n    // The identity matrix for max-plus algebra.\n    // Diagonal\
    \ elements are 0 (identity for addition).\n    // Off-diagonal elements are MinInf\
    \ (identity for max).\n    static constexpr value_type id() {\n        value_type\
    \ res{};\n        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j\
    \ < N; ++j) {\n                res[i][j] = (i == j) ? T(0) : MinInf;\n       \
    \     }\n        }\n        return res;\n    }\n\n    // Multiplies two max-plus\
    \ matrices: c_{i, j} = max_k (a_{i, k} + b_{k, j})\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res{};\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j < N; ++j)\
    \ {\n                res[i][j] = MinInf;\n            }\n        }\n        for\
    \ (int i = 0; i < N; ++i) {\n            for (int k = 0; k < N; ++k) {\n     \
    \           if (a[i][k] == MinInf) continue;\n                for (int j = 0;\
    \ j < N; ++j) {\n                    if (b[k][j] == MinInf) continue;\n      \
    \              res[i][j] = std::max(res[i][j], a[i][k] + b[k][j]);\n         \
    \       }\n            }\n        }\n        return res;\n    }\n\n    // Helper\
    \ to securely create a matrix initialized with MinInf.\n    static constexpr value_type\
    \ make_inf() {\n        value_type res{};\n        for (int i = 0; i < N; ++i)\
    \ {\n            for (int j = 0; j < N; ++j) {\n                res[i][j] = MinInf;\n\
    \            }\n        }\n        return res;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_MAX_PLUS_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/max_plus_matrix.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:25:27+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max_plus_matrix.hpp
layout: document
redirect_from:
- /library/monoid/max_plus_matrix.hpp
- /library/monoid/max_plus_matrix.hpp.html
title: monoid/max_plus_matrix.hpp
---
