---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':x:'
    path: data_structure/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_max.hpp
    title: monoid/acted_monoids/range_add_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_min.hpp
    title: monoid/acted_monoids/range_add_range_min.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_sum.hpp
    title: monoid/acted_monoids/range_add_range_sum.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_affine_range_minmax.hpp
    title: monoid/acted_monoids/range_affine_range_minmax.hpp
  - icon: ':x:'
    path: monoid/acted_monoids/range_affine_range_sum.hpp
    title: monoid/acted_monoids/range_affine_range_sum.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_max.hpp
    title: monoid/acted_monoids/range_update_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_min.hpp
    title: monoid/acted_monoids/range_update_range_min.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_sum.hpp
    title: monoid/acted_monoids/range_update_range_sum.hpp
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/unit_test/lazy_segtree.test.cpp
    title: verify/unit_test/lazy_segtree.test.cpp
  - icon: ':x:'
    path: verify/unit_test/lazy_segtree.test.cpp
    title: verify/unit_test/lazy_segtree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <concepts>\n#include\
    \ <functional>\n#include <type_traits>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n\
    #line 7 \"monoid/monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename T, auto\
    \ operation, auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(operation), T, T>, \"operation must work as T(T, T)\");\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(identity)>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires(typename T::value_type v) {\n\
    \    typename T::value_type;\n    { T::op(v, v) } -> std::same_as<typename T::value_type>;\n\
    \    { T::id() } -> std::same_as<typename T::value_type>;\n    { T::is_commutative\
    \ } -> std::convertible_to<bool>;\n};\n\n}  // namespace m1une\n\n\n#line 9 \"\
    monoid/acted_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <Monoid Data, Monoid\
    \ Act, auto mapping>\nstruct acted_monoid {\n    using data_monoid = Data;\n \
    \   using act_monoid = Act;\n\n    using data_type = typename Data::value_type;\n\
    \    using act_type = typename Act::value_type;\n\n    static_assert(std::is_invocable_r_v<data_type,\
    \ decltype(mapping), act_type, data_type>,\n                  \"mapping must work\
    \ as data_type(act_type, data_type)\");\n\n    static constexpr auto data_op =\
    \ Data::op;\n    static constexpr auto data_id = Data::id;\n    static constexpr\
    \ bool data_is_commutative = Data::is_commutative;\n    static constexpr auto\
    \ act_op = Act::op;\n    static constexpr auto act_id = Act::id;\n    static constexpr\
    \ bool act_is_commutative = Act::is_commutative;\n    static constexpr auto apply\
    \ = mapping;\n};\n\ntemplate <typename T>\nconcept ActedMonoid = requires(typename\
    \ T::data_type d, typename T::act_type a) {\n    typename T::data_monoid;\n  \
    \  typename T::act_monoid;\n    typename T::data_type;\n    typename T::act_type;\n\
    \    requires Monoid<typename T::data_monoid>;\n    requires Monoid<typename T::act_monoid>;\n\
    \    { T::apply(a, d) } -> std::same_as<typename T::data_type>;\n};\n\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_HPP\n#define M1UNE_ACTED_MONOID_HPP 1\n\n#include\
    \ <concepts>\n#include <functional>\n#include <type_traits>\n\n#include \"monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <Monoid Data, Monoid Act, auto mapping>\nstruct\
    \ acted_monoid {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\
    \n    using data_type = typename Data::value_type;\n    using act_type = typename\
    \ Act::value_type;\n\n    static_assert(std::is_invocable_r_v<data_type, decltype(mapping),\
    \ act_type, data_type>,\n                  \"mapping must work as data_type(act_type,\
    \ data_type)\");\n\n    static constexpr auto data_op = Data::op;\n    static\
    \ constexpr auto data_id = Data::id;\n    static constexpr bool data_is_commutative\
    \ = Data::is_commutative;\n    static constexpr auto act_op = Act::op;\n    static\
    \ constexpr auto act_id = Act::id;\n    static constexpr bool act_is_commutative\
    \ = Act::is_commutative;\n    static constexpr auto apply = mapping;\n};\n\ntemplate\
    \ <typename T>\nconcept ActedMonoid = requires(typename T::data_type d, typename\
    \ T::act_type a) {\n    typename T::data_monoid;\n    typename T::act_monoid;\n\
    \    typename T::data_type;\n    typename T::act_type;\n    requires Monoid<typename\
    \ T::data_monoid>;\n    requires Monoid<typename T::act_monoid>;\n    { T::apply(a,\
    \ d) } -> std::same_as<typename T::data_type>;\n};\n\n}  // namespace m1une\n\n\
    #endif  // M1UNE_ACTED_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/acted_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_update_range_max.hpp
  - monoid/acted_monoids/range_add_range_sum.hpp
  - monoid/acted_monoids/range_affine_range_sum.hpp
  - monoid/acted_monoids/range_update_range_min.hpp
  - monoid/acted_monoids/range_update_range_sum.hpp
  - monoid/acted_monoids/range_add_range_min.hpp
  - monoid/acted_monoids/range_add_range_max.hpp
  - monoid/acted_monoids/range_affine_range_minmax.hpp
  - monoid/prim_acted_monoids.hpp
  - monoid/prim_acted_monoids.hpp
  - data_structure/segtree/lazy_segtree.hpp
  timestamp: '2025-10-01 15:41:05+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/unit_test/lazy_segtree.test.cpp
  - verify/unit_test/lazy_segtree.test.cpp
documentation_of: monoid/acted_monoid.hpp
layout: document
title: Acted Monoid
---

## Overview

This file provides a generic struct to define an **Acted Monoid**, which is an algebraic structure used in data structures like the Lazy Segment Tree. It combines two monoids: a "data" monoid and an "action" monoid, along with a function that defines how actions affect the data.

## Properties

An acted monoid consists of:
1.  A monoid for data, $(D, \cdot, e_D)$.
2.  A monoid for actions, $(A, *, e_A)$.
3.  A mapping function `apply(f, x)` where $f \in A$ and $x \in D$, which returns a new element in $D$.

This structure is essential for data structures that need to support range updates and range queries.

## Template Parameters

* `Monoid Data`
    The monoid that defines the data elements and their binary operation.

* `Monoid Act`
    The monoid that defines the actions (or "lazy updates") and their composition.

* `auto mapping`
    A lambda or function pointer representing the mapping from an action and a data element to a new data element. It must take an `act_type` and a `data_type` and return a `data_type`.

## Action Composition

The binary operation of the action monoid, `act_op`, defines how two actions are combined. The order is important. In this library's lazy segment tree, if an existing action `f` is stored and a new action `g` is applied, they are combined as `act_op(f, g)`.

This composed action `act_op(f, g)` must be equivalent to applying the original action `f` first, and then applying the new action `g` to the result.

`apply(act_op(f, g), x) = apply(g, apply(f, x))`

For function composition, this means that `act_op(f, g)` corresponds to `g ∘ f`.

## Mapping Function Properties

For the lazy segment tree and other data structures to work correctly, the `mapping` function (let's call it $F$) must satisfy certain properties. Let $(D, \cdot, e_D)$ be the data monoid and $(A, *, e_A)$ be the action monoid.

1.  **Identity**: For any data element $x \in D$, applying the identity action $e_A$ must not change the data element.
    $F(e_A, x) = x$

2.  **Distributivity/Homomorphism**: For any action $f \in A$ and any data elements $x, y \in D$, applying the action to the combination of two data elements must be the same as combining the results of applying the action to each element individually.
    $F(f, x \cdot y) = F(f, x) \cdot F(f, y)$

3.  **Compatibility with Composition**: For any actions $f, g \in A$ and any data element $x \in D$, applying the composed action must be equivalent to applying the actions sequentially (as defined in the **Action Composition** section).
    $F(f * g, x) = F(g, F(f, x))$

## Members

* `using data_monoid = Data;`
    An alias for the data monoid.

* `using act_monoid = Act;`
    An alias for the action monoid.

* `using data_type = typename Data::value_type;`
    An alias for the data element type.

* `using act_type = typename Act::value_type;`
    An alias for the action element type.

* `static constexpr auto data_op = Data::op;`
    The binary operation for the data monoid.

* `static constexpr auto data_id = Data::id;`
    The identity element for the data monoid.

* `static constexpr auto act_op = Act::op;`
    The binary operation for the action monoid.

* `static constexpr auto act_id = Act::id;`
    The identity element for the action monoid.

* `static constexpr auto apply = mapping;`
    The function that applies an action to a data element.

## Usage Example

The library provides several pre-defined acted monoids. Here is how `range_add_range_min_monoid` is defined using this base struct:

```cpp
template <typename T>
using range_add_range_min_monoid = acted_monoid<min_monoid<T>, add_monoid<T>, [](T a, T x) { return a + x; }>;
```

This defines an acted monoid for range addition and range minimum queries. The data monoid is `min_monoid`, the action monoid is `add_monoid`, and the mapping function simply adds the action value to the data value.
