---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/ordered_set/binary_trie_monoid.test.cpp
    title: verify/ds/ordered_set/binary_trie_monoid.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/mul.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for multiplication (Range Product).\ntemplate <typename T>\n\
    struct Mul {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for multiplication, which is 1.\n    static constexpr T id() {\n        return\
    \ T(1);\n    }\n\n    // Returns the product of a and b.\n    static constexpr\
    \ T op(const T& a, const T& b) {\n        return a * b;\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MUL_HPP\n#define M1UNE_MONOID_MUL_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for multiplication (Range Product).\n\
    template <typename T>\nstruct Mul {\n    using value_type = T;\n\n    // Returns\
    \ the identity element for multiplication, which is 1.\n    static constexpr T\
    \ id() {\n        return T(1);\n    }\n\n    // Returns the product of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a * b;\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MUL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/mul.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/ordered_set/binary_trie_monoid.test.cpp
documentation_of: monoid/mul.hpp
layout: document
title: Multiply Monoid
---

## Overview

A monoid representing the multiplication operation. Useful for Range Product queries. Commonly used alongside modular arithmetic types (`Modint`) to prevent overflow.

## Template Parameters

* `T`: The underlying numeric data type.

## Properties

* **Operation**: Multiplication ($a \times b$)
* **Identity Element**: $1$
