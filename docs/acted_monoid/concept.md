---
title: Acted Monoid Concept
documentation_of: ../../acted_monoid/concept.hpp
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
