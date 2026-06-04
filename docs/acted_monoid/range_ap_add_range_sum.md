---
title: Range AP Add Range Sum
documentation_of: ../../acted_monoid/range_ap_add_range_sum.hpp
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries. 

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the original global 0-based index of the array element.

### Important Usage Note

Because standard lazy segment trees do not pass array bounds downwards during propagation, the node state (`value_type`) must store the sum of the indices (`idx_sum`) it covers, along with the standard `size`. 

When initializing the leaf nodes, you **must provide the index** of the element to the `make(val, idx)` helper.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        // Pass both the initial value AND the current index 'i'
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Add f(i) = 2 * i + 5 to the range [1, 4)
    // index 1: 2(1) + 5 = 7
    // index 2: 2(2) + 5 = 9
    // index 3: 2(3) + 5 = 11
    // Array becomes: {0, 7, 9, 11, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 7 + 9 + 11 + 0 = 27
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
