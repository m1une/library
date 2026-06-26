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
  bundledCode: "#line 1 \"monoid/max.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Monoid for maximum (Range Maximum).\n\
    // The identity element defaults to the lowest possible value of type T, but can\
    \ be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct Max {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for maximum.\n    static constexpr T id() {\n        return Id;\n    }\n\n \
    \   // Returns the maximum of a and b.\n    static constexpr T op(const T& a,\
    \ const T& b) {\n        return std::max(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MAX_HPP\n#define M1UNE_MONOID_MAX_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for maximum (Range Maximum).\n// The identity element defaults to the\
    \ lowest possible value of type T, but can be overridden.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::lowest()>\nstruct Max {\n    using value_type\
    \ = T;\n\n    // Returns the identity element for maximum.\n    static constexpr\
    \ T id() {\n        return Id;\n    }\n\n    // Returns the maximum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return std::max(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_MONOID_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/max.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max.hpp
layout: document
title: Max Monoid
---

## Overview

A monoid representing the Maximum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Maximum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::lowest()`.

## Properties

* **Operation**: `std::max(a, b)`
* **Identity Element**: `Id`

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
