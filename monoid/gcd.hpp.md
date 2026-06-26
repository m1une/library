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
  bundledCode: "#line 1 \"monoid/gcd.hpp\"\n\n\n\n#include <numeric>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for Greatest Common Divisor (Range\
    \ GCD).\ntemplate <typename T>\nstruct Gcd {\n    using value_type = T;\n\n  \
    \  // The identity element for GCD is 0.\n    static constexpr T id() {\n    \
    \    return T(0);\n    }\n\n    // Returns the greatest common divisor of a and\
    \ b.\n    static constexpr T op(const T& a, const T& b) {\n        return std::gcd(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_GCD_HPP\n#define M1UNE_MONOID_GCD_HPP 1\n\n#include\
    \ <numeric>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for Greatest\
    \ Common Divisor (Range GCD).\ntemplate <typename T>\nstruct Gcd {\n    using\
    \ value_type = T;\n\n    // The identity element for GCD is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the greatest common\
    \ divisor of a and b.\n    static constexpr T op(const T& a, const T& b) {\n \
    \       return std::gcd(a, b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_GCD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/gcd.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/gcd.hpp
layout: document
title: GCD Monoid
---

## Overview

A monoid representing the Greatest Common Divisor (GCD) operation. This is an idempotent monoid, meaning it can be safely used with a Sparse Table for $O(1)$ Range GCD queries.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: `std::gcd(a, b)`
* **Identity Element**: $0$ (Since $\gcd(x, 0) = x$)

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
