---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: data_structure/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/segtree/segtree.hpp
    title: Segment Tree
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/unit_test/lazy_segtree.test.cpp
    title: verify/unit_test/lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/unit_test/segtree.test.cpp
    title: verify/unit_test/segtree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_BIT_CEIL_HPP\n#define M1UNE_BIT_CEIL_HPP 1\n\nnamespace m1une\
    \ {\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return\
    \ 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_BIT_CEIL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/bit_ceil.hpp
  requiredBy:
  - data_structure/segtree/segtree.hpp
  - data_structure/segtree/lazy_segtree.hpp
  timestamp: '2025-09-28 19:24:13+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/unit_test/segtree.test.cpp
  - verify/unit_test/lazy_segtree.test.cpp
documentation_of: utilities/bit_ceil.hpp
layout: document
redirect_from:
- /library/utilities/bit_ceil.hpp
- /library/utilities/bit_ceil.hpp.html
title: utilities/bit_ceil.hpp
---
