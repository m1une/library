---
title: MinMax Monoid
documentation_of: ../../monoid/min_max.hpp
---

## Overview

A monoid for retrieving both the minimum and maximum values of a contiguous subarray in a single query. The underlying `value_type` is `std::pair<T, T>`, where `first` is the minimum value and `second` is the maximum value.

## Initialization

Use the `make(val)` method to construct a leaf node from a single scalar value.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/min_max.hpp"
#include <iostream>
#include <vector>

using MinMaxM = m1une::monoid::MinMax<long long>;

int main() {
    std::vector<long long> A = {8, 2, 5, 3, 9, 1};
    int N = A.size();

    std::vector<MinMaxM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinMaxM::make(A[i]);
    }

    m1une::ds::Segtree<MinMaxM> seg(init_data);

    // Query the range [1, 4) -> {2, 5, 3}
    auto [min_val, max_val] = seg.prod(1, 4);

    std::cout << "Min: " << min_val << ", Max: " << max_val << "\n"; // Output: Min: 2, Max: 5

    return 0;
}
```
