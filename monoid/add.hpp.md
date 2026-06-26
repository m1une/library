---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/all.hpp
    title: Dynamic Connectivity
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/online_dynamic_connectivity.hpp
    title: Online Dynamic Connectivity
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/dsu_monoid.test.cpp
    title: verify/ds/dsu/dsu_monoid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
    title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/potentialized_dsu.test.cpp
    title: verify/ds/dsu/potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/dynamic_monoid_array.test.cpp
    title: verify/ds/dynamic_array/dynamic_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
    title: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/link_cut_tree.test.cpp
    title: verify/ds/dynamic_tree/link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
    title: verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/ordered_set/binary_trie_monoid.test.cpp
    title: verify/ds/ordered_set/binary_trie_monoid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/disjoint_sparse_table.test.cpp
    title: verify/ds/range_query/disjoint_sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sqrt_tree.test.cpp
    title: verify/ds/range_query/sqrt_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/dynamic_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_segtree.test.cpp
    title: verify/ds/segtree/dynamic_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_segtree.test.cpp
    title: verify/ds/segtree/persistent_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/segtree.test.cpp
    title: verify/ds/segtree/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for addition,\
    \ which is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n\
    \    // Returns the sum of a and b.\n    static constexpr T op(const T& a, const\
    \ T& b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T&\
    \ x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_ADD_HPP\n#define M1UNE_MONOID_ADD_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate\
    \ <typename T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for addition, which is 0.\n    static constexpr T id() {\n\
    \        return T(0);\n    }\n\n    // Returns the sum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return a + b;\n    }\n\n \
    \   static constexpr T inv(const T& x) {\n        return -x;\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_ADD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/add.hpp
  requiredBy:
  - ds/dynamic_connectivity/online_dynamic_connectivity.hpp
  - ds/dynamic_connectivity/all.hpp
  timestamp: '2026-06-17 21:06:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_tree/link_cut_tree.test.cpp
  - verify/ds/dynamic_tree/path_link_cut_tree.test.cpp
  - verify/ds/dynamic_array/dynamic_monoid_array.test.cpp
  - verify/ds/ordered_set/binary_trie_monoid.test.cpp
  - verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  - verify/ds/range_query/sqrt_tree.test.cpp
  - verify/ds/range_query/disjoint_sparse_table.test.cpp
  - verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  - verify/ds/segtree/persistent_dual_segtree.test.cpp
  - verify/ds/segtree/dynamic_segtree.test.cpp
  - verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  - verify/ds/segtree/persistent_segtree.test.cpp
  - verify/ds/segtree/dynamic_dual_segtree.test.cpp
  - verify/ds/segtree/segtree.test.cpp
  - verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - verify/ds/dsu/dsu_monoid.test.cpp
  - verify/ds/dsu/potentialized_dsu.test.cpp
documentation_of: monoid/add.hpp
layout: document
title: Add Monoid
---

## Overview

A monoid representing the addition operation. It is commonly used with Segment Trees or Lazy Segment Trees for Range Sum Queries.

## Template Parameters

* `T`: The underlying numeric data type (e.g., `long long`, `int`, or `Modint`).

## Properties

* **Operation**: Addition ($a + b$)
* **Identity Element**: $0$

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
