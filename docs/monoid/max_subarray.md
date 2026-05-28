---
title: Max Subarray Monoid
documentation_of: ../../monoid/max_subarray.hpp
---

## Overview

A monoid for finding the maximum contiguous subarray sum within a range.
The underlying state is `m1une::monoid::SubarrayNode<T>`, which holds 4 values:
1. `sum`: The sum of the entire segment.
2. `pre`: The maximum prefix sum.
3. `suf`: The maximum suffix sum.
4. `opt`: The maximum subarray sum inside the segment.

## Initialization

To initialize a leaf node for a single value $x$, you must set all four properties based on whether empty subarrays (sum = 0) are allowed.

* **If empty subarrays are NOT allowed (Standard):**
  Use `{x, x, x, x}`.
* **If empty subarrays ARE allowed (Max is bounded below by 0):**
  Use `{x, max(0, x), max(0, x), max(0, x)}`.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/max_subarray.hpp"
#include <iostream>
#include <vector>

using MaxSubM = m1une::monoid::MaxSubarray<long long>;

int main() {
    std::vector<long long> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int N = A.size();

    std::vector<MaxSubM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        long long x = A[i];
        // Standard initialization (At least 1 element must be chosen)
        init_data[i] = {x, x, x, x};
    }

    m1une::data_structure::Segtree<MaxSubM> seg(init_data);

    // Max subarray sum in the whole array is 6 (from "4, -1, 2, 1")
    auto node = seg.prod(0, N);
    std::cout << "Max Subarray Sum: " << node.opt << "\n"; 

    return 0;
}
```
