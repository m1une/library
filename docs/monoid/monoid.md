---
title: Monoid
documentation_of: ../../monoid/monoid.hpp
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
