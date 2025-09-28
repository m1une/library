---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/monoids/add_monoid.hpp
    title: monoid/monoids/add_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/monoids/affine_monoid.hpp
    title: monoid/monoids/affine_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/affine_right_monoid.hpp
    title: monoid/monoids/affine_right_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/and_monoid.hpp
    title: monoid/monoids/and_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/max_monoid.hpp
    title: monoid/monoids/max_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/min_monoid.hpp
    title: monoid/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/mul_monoid.hpp
    title: monoid/monoids/mul_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/or_monoid.hpp
    title: monoid/monoids/or_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/xor_monoid.hpp
    title: monoid/monoids/xor_monoid.hpp
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/segtree/segtree.test.cpp
    title: verify/data_structure/segtree/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <type_traits>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_HPP\n#define M1UNE_MONOID_HPP 1\n\n#include <functional>\n\
    #include <type_traits>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/monoid.hpp
  requiredBy:
  - monoid/prim_monoids.hpp
  - monoid/prim_monoids.hpp
  - monoid/monoids/affine_right_monoid.hpp
  - monoid/monoids/min_monoid.hpp
  - monoid/monoids/and_monoid.hpp
  - monoid/monoids/max_monoid.hpp
  - monoid/monoids/mul_monoid.hpp
  - monoid/monoids/xor_monoid.hpp
  - monoid/monoids/or_monoid.hpp
  - monoid/monoids/affine_monoid.hpp
  - monoid/monoids/add_monoid.hpp
  timestamp: '2025-09-29 00:58:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/segtree/segtree.test.cpp
documentation_of: monoid/monoid.hpp
layout: document
title: Monoid
---

## Overview

This file provides a generic struct to define a **Monoid**, which is a fundamental algebraic structure used in various data structures.

## Properties

A monoid is a set of elements $S$ equipped with a single binary operation $(\cdot)$ that satisfies the following two properties:

1.  **Associativity**: For any three elements $a, b, c \in S$, the equation $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ holds.
2.  **Identity Element**: There exists an identity element $e \in S$ such that for any element $a \in S$, the equation $e \cdot a = a \cdot e = a$ holds.

This `monoid` struct serves as a template for creating specific monoids (like for addition, multiplication, etc.) that can be passed as template parameters to data structures like the Segment Tree.

## Template Parameters

* `typename T`
    The type of the elements in the monoid's set (e.g., `int`, `long long`, `std::pair<mint, mint>`).

* `auto operation`
    A lambda or function pointer representing the binary operation $(\cdot)$ of the monoid. It must take two arguments of type `T` and return a `T`.

* `auto identity`
    A lambda or function pointer that returns the identity element $e$ of the monoid.

* `bool commutative`
    A boolean flag indicating whether the binary operation is commutative (i.e., if $a \cdot b = b \cdot a$). This is an optional optimization hint for some data structures.

## Members

* `using value_type = T;`
    An alias for the element type `T`.

* `static constexpr auto op = operation;`
    The binary operation function.

* `static constexpr auto id = identity;`
    The identity element function.

* `static constexpr bool is_commutative = commutative;`
    The commutativity flag.

## Usage Example

The library provides several pre-defined monoids. Here is how `add_monoid` is defined using this base struct:

```cpp
template <typename T>
using add_monoid = monoid<T, [](T a, T b) { return a + b; }, []() { return T(0); }, true>;
```

This defines a monoid for addition on any type `T`, where the operation is `+`, the identity is `0`, and the operation is commutative.
