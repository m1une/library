---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sparse_table.test.cpp
    title: verify/ds/range_query/sparse_table.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/min.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Monoid for minimum (Range Minimum).\n\
    // The identity element defaults to the maximum possible value of type T, but\
    \ can be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct Min {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for minimum.\n    static constexpr T id() {\n        return Id;\n    }\n\n \
    \   // Returns the minimum of a and b.\n    static constexpr T op(const T& a,\
    \ const T& b) {\n        return std::min(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_HPP\n#define M1UNE_MONOID_MIN_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for minimum (Range Minimum).\n// The identity element defaults to the\
    \ maximum possible value of type T, but can be overridden.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max()>\nstruct Min {\n    using value_type\
    \ = T;\n\n    // Returns the identity element for minimum.\n    static constexpr\
    \ T id() {\n        return Id;\n    }\n\n    // Returns the minimum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return std::min(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_MONOID_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sparse_table.test.cpp
documentation_of: monoid/min.hpp
layout: document
title: Min Monoid
---

## Overview

A monoid representing the Minimum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Minimum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::max()`.

## Properties

* **Operation**: `std::min(a, b)`
* **Identity Element**: `Id`
