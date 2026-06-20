---
title: Range XOR Range Sum
documentation_of: ../../acted_monoid/range_xor_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Bitwise XOR operations and Range Sum queries.

### Mathematical Mechanism

Because the XOR operation acts bit-by-bit, it does not distribute directly over addition ($C \oplus (A + B) \neq (C \oplus A) + (C \oplus B)$). To compute the new sum of a range after XORing by a value $f$, the segment tree node must independently track **how many times each bit is set** in its range.

If the $i$-th bit of $f$ is set, the new number of set bits at position $i$ within the segment becomes `size - old_bit_count`. The total sum is then re-evaluated based on the new bit counts.

## Template Parameters

* `T`: The underlying numerical type (e.g., `long long`).
* `BITS`: The maximum bit length to track. Defaults to `30` (sufficient for standard $10^9$ integers). If operating on `long long` values up to $10^{18}$, you should explicitly set this to `60`.

## Initialization

When initializing a Lazy Segment Tree, you must use the `make(val)` helper function so that the leaf nodes correctly initialize their internal bit count arrays and size.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_xor_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeXorRangeSum<long long, 30>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Get the sum of range [0, 4) -> 1 + 2 + 3 + 4 = 10
    std::cout << "Initial Sum: " << seg.prod(0, 4).sum << "\n";

    // XOR the range [0, 4) with 7
    // 1^7 = 6, 2^7 = 5, 3^7 = 4, 4^7 = 3
    // Array becomes: {6, 5, 4, 3, 5}
    seg.apply(0, 4, 7);

    // Get the new sum of range [0, 4) -> 6 + 5 + 4 + 3 = 18
    std::cout << "Updated Sum: " << seg.prod(0, 4).sum << "\n";

    return 0;
}
```
