---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dual_segtree.hpp
    title: Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':warning:'
    path: ds/segtree/segtree_2d.hpp
    title: Segtree 2D
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dual_segtree.test.cpp
    title: verify/ds/segtree/dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/lazy_segtree.test.cpp
    title: verify/ds/segtree/lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/segtree.test.cpp
    title: verify/ds/segtree/segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1)\
    \ return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n} \
    \ // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_BIT_CEIL_HPP\n#define M1UNE_BIT_CEIL_HPP 1\n\nnamespace m1une\
    \ {\nnamespace math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n\
    \    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return\
    \ x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_BIT_CEIL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/bit_ceil.hpp
  requiredBy:
  - ds/segtree/segtree.hpp
  - ds/segtree/lazy_segtree.hpp
  - ds/segtree/segtree_2d.hpp
  - ds/segtree/dual_segtree.hpp
  - math/all.hpp
  timestamp: '2026-06-15 01:47:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dual_segtree.test.cpp
  - verify/ds/segtree/lazy_segtree.test.cpp
  - verify/ds/segtree/segtree.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/bit_ceil.hpp
layout: document
title: Bit Ceil
---

## Overview

A math utility function that calculates the smallest power of two that is greater than or equal to a given number `n`.

This is frequently used internally to determine the optimal underlying array size for complete binary tree structures (like Segment Trees) so that their length is perfectly aligned to a power of 2.

## API

```cpp
template <typename T>
constexpr T bit_ceil(T n);
```

`T` is both the argument and return type. It must be an integer-like type that
supports comparison, left shift, and construction from `1`.

The function returns the smallest power of two greater than or equal to `n`.
If `n <= 1`, it returns `T(1)`. The result must be representable by `T`.

## Complexity

The running time is $O(\log n)$ and the additional memory usage is $O(1)$.

## Example

```cpp
#include "math/bit_ceil.hpp"

#include <iostream>

int main() {
    std::cout << m1une::math::bit_ceil(13) << "\n"; // 16
}
```
