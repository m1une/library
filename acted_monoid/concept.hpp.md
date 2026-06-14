---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/dual_segtree.hpp
    title: Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/dynamic_lazy_monoid_array.hpp
    title: Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_lazy_segtree.hpp
    title: Persistent Lazy Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dual_segtree.test.cpp
    title: verify/data_structure/dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array_range_ap.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_segtree.test.cpp
    title: verify/data_structure/lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/data_structure/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_lazy_segtree.test.cpp
    title: verify/data_structure/persistent_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\n\
    namespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_CONCEPT_HPP\n#define M1UNE_ACTED_MONOID_CONCEPT_HPP\
    \ 1\n\n#include <concepts>\n\nnamespace m1une {\nnamespace acted_monoid {\n\n\
    // Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type\
    \ b, typename AM::operator_type f,\n                                 typename\
    \ AM::operator_type g) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \  // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_CONCEPT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/concept.hpp
  requiredBy:
  - data_structure/lazy_segtree.hpp
  - data_structure/persistent_lazy_segtree.hpp
  - data_structure/dual_segtree.hpp
  - data_structure/persistent_dynamic_lazy_monoid_array.hpp
  - data_structure/dynamic_lazy_monoid_array.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - verify/data_structure/dual_segtree.test.cpp
  - verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/dynamic_lazy_monoid_array_range_ap.test.cpp
  - verify/data_structure/lazy_segtree.test.cpp
  - verify/data_structure/persistent_lazy_segtree.test.cpp
documentation_of: acted_monoid/concept.hpp
layout: document
title: Acted Monoid Concept
---

## Overview

`m1une::acted_monoid::IsActedMonoid` is the C++20 concept used by lazy
propagation data structures such as `LazySegtree`.

An acted monoid has three parts:

1. A value monoid, which combines segment values for queries.
2. An operator monoid, which combines lazy update operations.
3. A mapping function, which applies one operator to one value.

For example, in range-add range-sum:

* the value stores `(sum, size)`,
* the lazy operator stores the amount to add,
* `mapping(add, value)` increases the sum by `add * size`.

## Requirements

The concept requires the type to implement these members:

* `using value_type`
  The type stored for each segment.

* `using operator_type`
  The type stored for each lazy operation.

* `static constexpr value_type id()`
  Returns the identity element of the value monoid.

* `static constexpr value_type op(const value_type& a, const value_type& b)`
  Combines two segment values.

* `static constexpr operator_type op_id()`
  Returns the identity operation.

* `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)`
  Composes two operators. The order is `f(g(x))`: apply `g` first, then `f`.

* `static constexpr value_type mapping(const operator_type& f, const value_type& x)`
  Applies operator `f` to value `x`.

The concept checks the interface only. Associativity, identity laws, and the
interaction between `mapping` and `op` must be satisfied by the implementation.
