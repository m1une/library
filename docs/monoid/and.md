---
title: Bitwise AND Monoid
documentation_of: ../../monoid/and.hpp
---

## Overview

A monoid representing the bitwise AND operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise AND ($a \ \& \ b$)
* **Identity Element**: `~T(0)` (All bits set to 1)

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
