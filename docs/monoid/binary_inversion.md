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
#include "data_structure/segtree.hpp"
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

    m1une::data_structure::Segtree<BinInv> seg(init_data);

    auto res = seg.prod(0, N);

    std::cout << "Zeros: " << res.zeros << "\n";
    std::cout << "Ones: " << res.ones << "\n";
    std::cout << "Inversions: " << res.inversions << "\n"; // Output: 5

    return 0;
}
```
