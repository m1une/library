---
title: Strict Max 2 Monoid
documentation_of: ../../monoid/strict_max2.hpp
---

## Overview

A monoid that maintains the strictly largest (`opt1`) and strictly second-largest (`opt2`) values in a contiguous subarray. If all elements in the range are the same, `opt2` will remain the identity element.

This is the maximum counterpart to `monoid/strict_min2.hpp`.

## Example

```cpp
#include "ds/segment_tree/segtree.hpp"
#include "monoid/strict_max2.hpp"
#include <iostream>
#include <vector>

using StrictMax2M = m1une::monoid::StrictMax2<long long>;

int main() {
    std::vector<long long> A = {8, 8, 5, 3, 8, 6};
    int N = A.size();

    std::vector<StrictMax2M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = StrictMax2M::make(A[i]);
    }

    m1une::ds::Segtree<StrictMax2M> seg(init_data);

    auto res = seg.prod(2, 6); // Range: [5, 3, 8, 6]

    std::cout << "1st Max: " << res.opt1 << "\n"; // Output: 8
    std::cout << "2nd Max: " << res.opt2 << "\n"; // Output: 6

    return 0;
}
```
