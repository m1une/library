---
title: Range Flip Range Sum
documentation_of: ../../acted_monoid/range_flip_range_sum.hpp
---

## Overview

An Acted Monoid designed specifically for binary arrays ($0$s and $1$s). It supports Range Bit Inversion (flipping $0 \leftrightarrow 1$) operations and Range Sum queries (which effectively counts the number of $1$s in the range).

### Important Usage Note

This is a highly optimized structure. When a range is flipped, the new sum (number of $1$s) becomes exactly `size - old_sum`. Therefore, the `value_type` tracks both the `sum` and the `size`.

The `operator_type` is a boolean, where `true` indicates that the range should be flipped, and `false` is the identity operation (no-op).

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_flip_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeFlipRangeSum<long long>;

int main() {
    std::vector<long long> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Sum of [0, 5) is 2 (two 1s)
    std::cout << "Initial 1s: " << seg.prod(0, 5).sum << "\n";

    // Flip bits in range [1, 4) -> Indices 1, 2, 3
    // Array becomes: {1, 1, 0, 1, 0}
    seg.apply(1, 4, true);

    // Sum of [0, 5) is now 3
    std::cout << "Updated 1s: " << seg.prod(0, 5).sum << "\n";

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
