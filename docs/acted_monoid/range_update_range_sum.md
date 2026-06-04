---
title: Range Update Range Sum
documentation_of: ../../acted_monoid/range_update_range_sum.hpp
---

## Overview

An acted monoid that supports range update (overwrite) operations and range sum queries.

### Important Usage Note

Since the sum of a range updated to a single value $f$ becomes $f \times \text{size}$, the `value_type` must maintain the size of the segment. When initializing leaf nodes, use the provided helper function `make(val)` to correctly set the size to 1. The `operator_type` uses `std::optional<T>` to safely represent the state of "no operation".

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Update the range [1, 4) to 10
    seg.apply(1, 4, std::optional<long long>(10));

    // Get the sum of the range [0, 5)
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
