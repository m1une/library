---
title: MinCount Monoid
documentation_of: ../../monoid/min_count.hpp
---

## Overview

A monoid for finding both the **minimum value** and **the frequency (count) of that minimum value** in a range. The underlying `value_type` is `std::pair<T, int>`, where `first` is the value and `second` is the count.

## Initialization

When initializing a segment tree from an array of elements, use the `make(val)` method to construct a leaf node with a default count of 1.

### Example

```cpp
#include "ds/segment_tree/segtree.hpp"
#include "monoid/min_count.hpp"
#include <iostream>
#include <vector>

using MinCountM = m1une::monoid::MinCount<long long>;

int main() {
    std::vector<long long> A = {3, 1, 4, 1, 5, 1, 9};
    int N = A.size();

    std::vector<MinCountM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinCountM::make(A[i]);
    }

    m1une::ds::Segtree<MinCountM> seg(init_data);

    // Query the range [0, 5) -> Elements: {3, 1, 4, 1, 5}
    // Minimum is 1, it appears 2 times.
    auto [min_val, count] = seg.prod(0, 5);
    std::cout << "Min: " << min_val << ", Count: " << count << "\n"; // Output: Min: 1, Count: 2

    return 0;
}
```
