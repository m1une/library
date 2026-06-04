---
title: Range AP Update Range Sum
documentation_of: ../../acted_monoid/range_ap_update_range_sum.hpp
---

## Overview

An Acted Monoid that supports overwriting a range with an arithmetic progression, alongside range sum queries.

The operator replaces existing elements with $f(i) = a \cdot i + b$, where $i$ is the original global 0-based index of the array element.

### Important Usage Note

Similar to `RangeApAddRangeSum`, the node state (`value_type`) tracks the sum of the indices (`idx_sum`) it covers, enabling $O(1)$ block updates. 

When initializing the leaf nodes, you **must provide the index** of the element to the `make(val, idx)` helper. The `operator_type` relies on `std::optional` to safely designate the "no operation" state.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Overwrite the range [0, 3) with f(i) = 3 * i + 1
    // index 0: 3(0) + 1 = 1
    // index 1: 3(1) + 1 = 4
    // index 2: 3(2) + 1 = 7
    // Array becomes: {1, 4, 7, 40, 50}
    seg.apply(0, 3, std::optional<std::pair<long long, long long>>({3, 1}));

    // Query sum of range [0, 3) -> 1 + 4 + 7 = 12
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
