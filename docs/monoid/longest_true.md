---
title: Longest True Monoid
documentation_of: ../../monoid/longest_true.hpp
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements satisfy a specific condition (e.g., all elements are `true` or equal to a target value).

## Initialization

Convert your target elements into booleans and use the `make` method to initialize the leaf nodes.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/longest_true.hpp"
#include <iostream>
#include <vector>

using LTM = m1une::monoid::LongestTrue;

int main() {
    std::vector<long long> A = {1, 3, 3, 4, 3, 3, 3, 1};
    int N = A.size();
    long long target = 3;

    std::vector<LTM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Only set to true if the element matches the target
        init_data[i] = LTM::make(A[i] == target);
    }

    m1une::ds::Segtree<LTM> seg(init_data);

    auto res = seg.prod(0, N);
    std::cout << "Max Length of " << target << "s: " << res.max_len << "\n"; // Output: 3

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
