---
title: Top K Count Monoid
documentation_of: ../../monoid/top_k_count.hpp
---

## Overview

A monoid that maintains the Top $K$ (largest) distinct elements and their frequencies (counts) in a range. The underlying `value_type` is `std::vector<std::pair<T, int>>`. Merging two nodes takes $O(K)$ time.

## Initialization

Use the `make(val)` method to construct a leaf node containing a single value with a count of 1.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/top_k_count.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 2 distinct elements and their counts
using Top2CM = m1une::monoid::TopKCount<long long, 2>;

int main() {
    std::vector<long long> A = {10, 50, 50, 40, 50};
    int N = A.size();

    std::vector<Top2CM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top2CM::make(A[i]);
    }

    m1une::data_structure::Segtree<Top2CM> seg(init_data);

    // Get the top 2 elements in the range [0, 5) -> { (50, 3), (40, 1) }
    auto top2 = seg.prod(0, 5);

    for (auto p : top2) {
        std::cout << "Value: " << p.first << " Count: " << p.second << "\n";
    }

    return 0;
}
```
