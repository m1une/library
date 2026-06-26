---
title: Update Monoid
documentation_of: ../../monoid/update.hpp
---

## Overview

A monoid for range updates/assignments. It uses `std::optional<T>` to safely represent whether an assignment operation exists or not (the identity element is `std::nullopt`).

When two operations are composed, the newer operation (on the left, when applied) completely overwrites the older operation (on the right), unless the newer operation is empty.

## Template Parameters

* `T`: The underlying data type being assigned.

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
