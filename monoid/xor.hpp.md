---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/union_find/potentialized_dsu.test.cpp
    title: verify/ds/union_find/potentialized_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/xor.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate <typename T>\nstruct Xor\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for bitwise\
    \ XOR, which is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\
    \n    // Returns the bitwise XOR of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a ^ b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_XOR_HPP\n#define M1UNE_MONOID_XOR_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate\
    \ <typename T>\nstruct Xor {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for bitwise XOR, which is 0.\n    static constexpr T id() {\n\
    \        return T(0);\n    }\n\n    // Returns the bitwise XOR of a and b.\n \
    \   static constexpr T op(const T& a, const T& b) {\n        return a ^ b;\n \
    \   }\n\n    static constexpr T inv(const T& x) {\n        return x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_XOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/xor.hpp
  requiredBy: []
  timestamp: '2026-06-17 21:06:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/union_find/potentialized_dsu.test.cpp
documentation_of: monoid/xor.hpp
layout: document
title: Bitwise XOR Monoid
---

## Overview

A monoid representing the bitwise XOR operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise XOR ($a \ \text{\textasciicircum} \ b$)
* **Identity Element**: $0$
