---
title: Longest Same Monoid
documentation_of: ../../monoid/longest_same.hpp
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements have the same value.

## Initialization

When initializing a segment tree from an array of elements, you should use the `make` helper method to correctly build the leaf nodes.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/longest_same.hpp"
#include <iostream>
#include <vector>

using LSM = m1une::monoid::LongestSame<long long>;

int main() {
    std::vector<long long> A = {2, 2, 5, 5, 5, 2, 2};
    int N = A.size();

    std::vector<LSM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = LSM::make(A[i]);
    }

    m1une::ds::Segtree<LSM> seg(init_data);

    // Get the maximum length of consecutive identical elements in range [0, 7)
    auto res = seg.prod(0, N);
    std::cout << "Max Length: " << res.max_len << "\n"; // Output: 3 (because of "5, 5, 5")

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
