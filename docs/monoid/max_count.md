---
title: MaxCount Monoid
documentation_of: ../../monoid/max_count.hpp
---

## Overview

A monoid for finding both the **maximum value** and **the frequency (count) of that maximum value** in a range. The underlying `value_type` is `std::pair<T, int>`, where `first` is the value and `second` is the count.

This is the maximum counterpart to `monoid/min_count.hpp`.

## Initialization

When initializing a segment tree from an array of elements, use the `make(val)` method to construct a leaf node with a default count of 1.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/max_count.hpp"
#include <iostream>
#include <vector>

using MaxCountM = m1une::monoid::MaxCount<long long>;

int main() {
    std::vector<long long> A = {3, 9, 4, 9, 5, 9, 1};
    int N = A.size();

    std::vector<MaxCountM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MaxCountM::make(A[i]);
    }

    m1une::ds::Segtree<MaxCountM> seg(init_data);

    // Query the range [0, 6) -> Elements: {3, 9, 4, 9, 5, 9}
    // Maximum is 9, it appears 3 times.
    auto [max_val, count] = seg.prod(0, 6);
    std::cout << "Max: " << max_val << ", Count: " << count << "\n"; // Output: Max: 9, Count: 3

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
