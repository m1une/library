---
title: GCD Monoid
documentation_of: ../../monoid/gcd.hpp
---

## Overview

A monoid representing the Greatest Common Divisor (GCD) operation. This is an idempotent monoid, meaning it can be safely used with a Sparse Table for $O(1)$ Range GCD queries.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: `std::gcd(a, b)`
* **Identity Element**: $0$ (Since $\gcd(x, 0) = x$)

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
