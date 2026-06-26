---
title: Max Monoid
documentation_of: ../../monoid/max.hpp
---

## Overview

A monoid representing the Maximum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Maximum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::lowest()`.

## Properties

* **Operation**: `std::max(a, b)`
* **Identity Element**: `Id`

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
