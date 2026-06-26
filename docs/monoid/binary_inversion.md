---
title: Binary Inversion Monoid
documentation_of: ../../monoid/binary_inversion.hpp
---

## Overview

A monoid for counting the number of `0`s, `1`s, and inversions (the number of pairs where `1` appears before `0`) in a binary array.

## Initialization

Use the `make(val)` helper to initialize leaf nodes, passing either `0` or `1`.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/binary_inversion.hpp"
#include <iostream>
#include <vector>

using BinInv = m1une::monoid::BinaryInversion<long long>;

int main() {
    // Array: [1, 0, 1, 0, 0]
    std::vector<int> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<BinInv::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = BinInv::make(A[i]);
    }

    m1une::ds::Segtree<BinInv> seg(init_data);

    auto res = seg.prod(0, N);

    std::cout << "Zeros: " << res.zeros << "\n";
    std::cout << "Ones: " << res.ones << "\n";
    std::cout << "Inversions: " << res.inversions << "\n"; // Output: 5

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
