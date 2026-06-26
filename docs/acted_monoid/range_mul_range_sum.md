---
title: Range Multiply Range Sum
documentation_of: ../../acted_monoid/range_mul_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Multiplication operations and Range Sum queries.

Unlike Range Addition or Range Affine transformations, Range Multiplication distributes perfectly over addition: $C \times (A + B) = C \cdot A + C \cdot B$. Because of this mathematical property, the `value_type` does **not** need to store the `size` of the segment, making this monoid lighter in memory and faster to compute than the full `RangeAffineRangeSum`.

## Template Parameters

* `T`: The underlying numerical type. It is strongly recommended to use a modular arithmetic struct (e.g., `Modint`) to prevent overflow, as repeated multiplications grow exponentially.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_mul_range_sum.hpp"
#include <iostream>
#include <vector>

// Assuming a modular arithmetic type or standard long long for small bounds
using AM = m1une::acted_monoid::RangeMulRangeSum<long long>;

int main() {
    std::vector<long long> A = {2, 3, 4, 1};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        // Initializes leaf node
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Sum of range [0, 3) -> 2 + 3 + 4 = 9
    std::cout << "Initial Sum: " << seg.prod(0, 3) << "\n";

    // Multiply range [0, 2) by 5
    // Array becomes: {10, 15, 4, 1}
    seg.apply(0, 2, 5);

    // Sum of range [0, 3) -> 10 + 15 + 4 = 29
    std::cout << "Updated Sum: " << seg.prod(0, 3) << "\n";

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
