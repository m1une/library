---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: data_structure/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/segtree.hpp
    title: Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/segtree.test.cpp
    title: verify/data_structure/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n\
    \ <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\
    \n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_BIT_CEIL_HPP\n#define M1UNE_BIT_CEIL_HPP 1\n\nnamespace m1une\
    \ {\nnamespace utilities {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n)\
    \ {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n   \
    \ return x;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_BIT_CEIL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/bit_ceil.hpp
  requiredBy:
  - data_structure/segtree.hpp
  - data_structure/lazy_segtree.hpp
  timestamp: '2026-05-29 01:41:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/segtree.test.cpp
documentation_of: utilities/bit_ceil.hpp
layout: document
title: Bit Ceil
---

## Overview

A utility function that calculates the smallest power of two that is greater than or equal to a given number `n`.

This is frequently used internally to determine the optimal underlying array size for complete binary tree structures (like Segment Trees) so that their length is perfectly aligned to a power of 2.

## Parameters

* `T n`: The target integer.

## Returns

The smallest power of 2 $\ge n$. If $n \le 1$, it returns $1$.
