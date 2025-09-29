---
title: Acted Monoid
documentation_of: ../../monoid/acted_monoid.hpp
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
