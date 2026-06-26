---
title: Range OR Range Sum
documentation_of: ../../acted_monoid/range_or_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Bitwise OR operations and Range Sum queries.

### Mathematical Mechanism

Because Bitwise OR does not distribute directly over addition, the node must track how many times each individual bit is set within its range. When a Range OR is applied with a value $f$, any bit set to `1` in $f$ forces that specific bit to become `1` for *every* element in the segment. Its bit count immediately becomes equal to `size`.

## Template Parameters

* `T`: The underlying numerical type.
* `BITS`: Max bit length (default 30). Set to 60 for `long long` bounds.

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
