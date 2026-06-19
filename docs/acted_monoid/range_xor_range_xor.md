---
title: Range Xor Range Xor
documentation_of: ../../acted_monoid/range_xor_range_xor.hpp
---

## Overview

An acted monoid that supports range bitwise XOR operations and range XOR sum queries.

### Important Usage Note

When a value $f$ is XORed to all elements in a segment, the total XOR sum of the segment changes by $f$ only if the segment's length is odd. Therefore, `value_type` holds the size of the segment. Use the `make(val)` helper function to initialize leaf nodes.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_xor_range_xor.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeXorRangeXor<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    seg.apply(1, 4, 7);

    std::cout << seg.prod(1, 4).val << "\n";

    return 0;
}
```
