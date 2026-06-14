---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
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
    path: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/lazy_segtree.test.cpp
    title: verify/data_structure/lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
    title: verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
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
  - data_structure/persistent_dynamic_lazy_monoid_array.hpp
  - data_structure/dynamic_lazy_monoid_array.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/persistent_dynamic_lazy_monoid_array.test.cpp
  - verify/data_structure/lazy_segtree.test.cpp
  - verify/data_structure/persistent_lazy_segtree.test.cpp
documentation_of: acted_monoid/concept.hpp
layout: document
title: Acted Monoid Concept
---

## Overview

An Acted Monoid (also known as a Monoid Action) is a mathematical structure used in data structures like Lazy Segment Trees. It defines how a set of operations (operators) interacts with a set of elements (values). It consists of three parts:
1. A **Value Monoid**: The monoid over the values of the array.
2. An **Operator Monoid**: The monoid over the lazy operations applied to the array.
3. A **Mapping Function**: A function that defines how an operator from the operator monoid is applied to a value from the value monoid.

## Requirements

The `m1une::acted_monoid::IsActedMonoid` concept requires the type to implement the following members:

- `using value_type`: The type of the value elements.
- `using operator_type`: The type of the operator elements.
- `static constexpr value_type id()`: Returns the identity element of the value monoid.
- `static constexpr value_type op(const value_type& a, const value_type& b)`: Returns the result of the binary operation of the value monoid.
- `static constexpr operator_type op_id()`: Returns the identity element (no-op) of the operator monoid.
- `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)`: Returns the composition of two operators $f$ and $g$. The semantics must be $f(g(x))$, meaning $g$ is applied first, then $f$.
- `static constexpr value_type mapping(const operator_type& f, const value_type& x)`: Returns the result of applying the operator $f$ to the value $x$.
