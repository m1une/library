---
title: Range Add Range ArgMax
documentation_of: ../../acted_monoid/range_add_range_arg_max.hpp
---

## Overview

An acted monoid for range addition and range maximum queries with the position
of the selected maximum.

### Tie-breaking

If there are multiple maximum values in the queried range, the `op` function returns the earliest order.

## Example

```cpp
using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
m1une::ds::LazySegtree<AM> seg(A);
auto q = seg.prod(0, A.size());
std::cout << q.max_val << " " << q.ord << "\n";
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
