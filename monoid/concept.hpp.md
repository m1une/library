---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/disjoint_sparse_table.hpp
    title: Disjoint Sparse Table
  - icon: ':heavy_check_mark:'
    path: data_structure/dynamic_monoid_array.hpp
    title: Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: data_structure/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/sparse_table.hpp
    title: Sparse Table
  - icon: ':warning:'
    path: monoid/power.hpp
    title: Monoid Power
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/disjoint_sparse_table.test.cpp
    title: verify/data_structure/disjoint_sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_monoid_array.test.cpp
    title: verify/data_structure/dynamic_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/segtree.test.cpp
    title: verify/data_structure/segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/sparse_table.test.cpp
    title: verify/data_structure/sparse_table.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_CONCEPT_HPP\n#define M1UNE_MONOID_CONCEPT_HPP 1\n\n\
    #include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to\
    \ check if a type satisfies the requirements of a Monoid.\n// A Monoid must have\
    \ a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MONOID_CONCEPT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/concept.hpp
  requiredBy:
  - data_structure/segtree.hpp
  - data_structure/dynamic_monoid_array.hpp
  - data_structure/disjoint_sparse_table.hpp
  - data_structure/sparse_table.hpp
  - monoid/power.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_monoid_array.test.cpp
  - verify/data_structure/sparse_table.test.cpp
  - verify/data_structure/segtree.test.cpp
  - verify/data_structure/disjoint_sparse_table.test.cpp
documentation_of: monoid/concept.hpp
layout: document
title: Monoid Concept
---

## Overview

Provides a C++20 `concept` to constrain template arguments for Monoids. This ensures that the given type satisfies the mathematical requirements of a monoid, enabling safer and more readable template instantiations (e.g., in Segment Trees).

## Concept Requirements

To satisfy `m1une::monoid::IsMonoid`, a struct `M` must implement the following:

* `using value_type = T;`
  An alias for the underlying type of the monoid.
  
* `static constexpr T id();`
  A static function returning the identity element of the monoid.
  
* `static constexpr T op(const T& a, const T& b);`
  A static function representing the associative binary operation.

## Example

```cpp
#include "monoid/concept.hpp"
#include <algorithm>

struct MinMonoid {
    using value_type = int;
    static constexpr int id() { return 1e9; }
    static constexpr int op(const int& a, const int& b) { return std::min(a, b); }
};

// This assertion will pass at compile time
static_assert(m1une::monoid::IsMonoid<MinMonoid>);
```
