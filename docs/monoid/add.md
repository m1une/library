---
title: Add Monoid
documentation_of: ../../monoid/add.hpp
---

## Overview

A monoid representing the addition operation. It is commonly used with Segment Trees or Lazy Segment Trees for Range Sum Queries.

## Template Parameters

* `T`: The underlying numeric data type (e.g., `long long`, `int`, or `Modint`).

## Properties

* **Operation**: Addition ($a + b$)
* **Identity Element**: $0$

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
