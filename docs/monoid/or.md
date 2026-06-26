---
title: Bitwise OR Monoid
documentation_of: ../../monoid/or.hpp
---

## Overview

A monoid representing the bitwise OR operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise OR ($a \ | \ b$)
* **Identity Element**: $0$ (All bits set to 0)

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
