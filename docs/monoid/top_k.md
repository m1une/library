---
title: Top K Monoid
documentation_of: ../../monoid/top_k.hpp
---

## Overview

A monoid that maintains the Top $K$ (largest) elements in a range. The underlying `value_type` is `std::vector<T>`. Merging two nodes takes $O(K)$ time, so $K$ should be relatively small (e.g., $K \le 10$).

## Initialization

Since the state is a `std::vector<T>`, you can use the `make(val)` helper to automatically wrap a single array element into a vector of size 1.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/top_k.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 3 elements
using Top3M = m1une::monoid::TopK<long long, 3>;

int main() {
    std::vector<long long> A = {10, 50, 20, 40, 30};
    int N = A.size();

    std::vector<Top3M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top3M::make(A[i]);
    }

    m1une::ds::Segtree<Top3M> seg(init_data);

    // Get the top 3 elements in the range [0, 4) -> {50, 40, 20}
    std::vector<long long> top3 = seg.prod(0, 4);

    for (long long x : top3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
