---
title: Range AP Add Range Sum
documentation_of: ../../acted_monoid/range_ap_add_range_sum.hpp
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries.

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Important Usage Note

The node state (`value_type`) stores `size` and the sum of relative orders (`ord_sum`) it covers. This makes it usable in dynamic arrays where global indices change after insertions, deletions, and reversals.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add f(i) = 2 * i + 5 to the range [1, 4), where i is local to [1, 4)
    // Array becomes: {0, 5, 7, 9, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 5 + 7 + 9 + 0 = 21
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
