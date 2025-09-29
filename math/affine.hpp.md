---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/unit_test/segtree.test.cpp
    title: verify/unit_test/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/affine.hpp\"\n\n\n\n#include <utility>\n\nnamespace\
    \ m1une {\ntemplate <typename T>\nT affine(std::pair<T, T> f, T x) {\n    return\
    \ f.first * x + f.second;\n}\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_AFFINE_HPP\n#define M1UNE_AFFINE_HPP 1\n\n#include <utility>\n\
    \nnamespace m1une {\ntemplate <typename T>\nT affine(std::pair<T, T> f, T x) {\n\
    \    return f.first * x + f.second;\n}\n}  // namespace m1une\n\n#endif  // M1UNE_AFFINE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/affine.hpp
  requiredBy: []
  timestamp: '2025-09-28 21:36:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/unit_test/segtree.test.cpp
documentation_of: math/affine.hpp
layout: document
redirect_from:
- /library/math/affine.hpp
- /library/math/affine.hpp.html
title: math/affine.hpp
---
