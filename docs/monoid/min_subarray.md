---
title: Min Subarray Monoid
documentation_of: ../../monoid/min_subarray.hpp
---

## Overview

A monoid for finding the minimum contiguous subarray sum within a range.
The underlying state is `m1une::monoid::SubarrayNode<T>`, which holds 4 values:
1. `sum`: The sum of the entire segment.
2. `pre`: The minimum prefix sum.
3. `suf`: The minimum suffix sum.
4. `opt`: The minimum subarray sum inside the segment.

## Initialization

To initialize a leaf node for a single value $x$, use the `make(val, allow_empty)` method.

* **If empty subarrays are NOT allowed (Standard):**
  Use `make(x)` or `make(x, false)`. At least 1 element must be chosen.
* **If empty subarrays ARE allowed (Min is bounded above by 0):**
  Use `make(x, true)`.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/min_subarray.hpp"
#include <iostream>
#include <vector>

using MinSubM = m1une::monoid::MinSubarray<long long>;

int main() {
    std::vector<long long> A = {2, -1, 3, -4, 1, -2, -1, 5, -4};
    int N = A.size();

    std::vector<MinSubM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Standard initialization (At least 1 element must be chosen)
        init_data[i] = MinSubM::make(A[i]);
    }

    m1une::ds::Segtree<MinSubM> seg(init_data);

    // Min subarray sum in the whole array is -7 (from "-4, 1, -2, -1")
    auto node = seg.prod(0, N);
    std::cout << "Min Subarray Sum: " << node.opt << "\n";

    return 0;
}
```
