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
  bundledCode: "#line 1 \"monoid/and.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise AND (Range AND).\n// ~T(0) sets all bits to 1, acting\
    \ as the identity for bitwise AND.\ntemplate <typename T>\nstruct And {\n    using\
    \ value_type = T;\n\n    // The identity element for bitwise AND is all bits set\
    \ to 1.\n    static constexpr T id() { return ~T(0); }\n\n    // Returns the bitwise\
    \ AND of a and b.\n    static constexpr T op(const T& a, const T& b) { return\
    \ a & b; }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_AND_HPP\n#define M1UNE_MONOID_AND_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for bitwise AND (Range AND).\n// ~T(0)\
    \ sets all bits to 1, acting as the identity for bitwise AND.\ntemplate <typename\
    \ T>\nstruct And {\n    using value_type = T;\n\n    // The identity element for\
    \ bitwise AND is all bits set to 1.\n    static constexpr T id() { return ~T(0);\
    \ }\n\n    // Returns the bitwise AND of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) { return a & b; }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_AND_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/and.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:48:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/and.hpp
layout: document
title: Bitwise AND Monoid
---

## Overview

A monoid representing the bitwise AND operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise AND ($a \ \& \ b$)
* **Identity Element**: `~T(0)` (All bits set to 1)

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
