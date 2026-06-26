---
title: Range Add Range Sum
documentation_of: ../../acted_monoid/range_add_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Addition operations and Range Sum queries.

### Important Usage Note

When adding a value $f$ to a range of sum $x$, the total sum increases by $f \times (\text{length of the range})$. Therefore, the `value_type` cannot just be an integer; it must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAddRangeSumNode<T>`, which holds both the `sum` and the `size`.

When initializing a data structure (like a Lazy Segment Tree) with this acted monoid, you must initialize the leaf nodes with `size = 1`. You can use the helper function `make(val)` for this purpose.

## Example

```cpp
// Assuming `lazy_segtree` is implemented
std::vector<m1une::acted_monoid::RangeAddRangeSumNode<long long>> init_nodes(N);
for (int i = 0; i < N; ++i) {
    // Initialize each leaf with the value and size = 1
    init_nodes[i] = m1une::acted_monoid::RangeAddRangeSum<long long>::make(A[i]);
}

lazy_segtree<RangeAddRangeSum<long long>> seg(init_nodes);
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
