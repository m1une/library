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
  bundledCode: "#line 1 \"monoid/or.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise OR (Range OR).\ntemplate <typename T>\nstruct Or\
    \ {\n    using value_type = T;\n\n    // The identity element for bitwise OR is\
    \ 0 (all bits 0).\n    static constexpr T id() {\n        return T(0);\n    }\n\
    \n    // Returns the bitwise OR of a and b.\n    static constexpr T op(const T&\
    \ a, const T& b) {\n        return a | b;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_OR_HPP\n#define M1UNE_MONOID_OR_HPP 1\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for bitwise OR (Range OR).\ntemplate <typename\
    \ T>\nstruct Or {\n    using value_type = T;\n\n    // The identity element for\
    \ bitwise OR is 0 (all bits 0).\n    static constexpr T id() {\n        return\
    \ T(0);\n    }\n\n    // Returns the bitwise OR of a and b.\n    static constexpr\
    \ T op(const T& a, const T& b) {\n        return a | b;\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_OR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/or.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/or.hpp
layout: document
title: Bitwise OR Monoid
---

## Overview

A monoid representing the bitwise OR operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise OR ($a \ | \ b$)
* **Identity Element**: $0$ (All bits set to 0)
