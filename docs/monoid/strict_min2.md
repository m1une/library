---
title: Strict Min 2 Monoid
documentation_of: ../../monoid/strict_min2.hpp
---

## Overview

A monoid that maintains the strictly smallest (`opt1`) and strictly second-smallest (`opt2`) values in a contiguous subarray. If all elements in the range are the same, `opt2` will remain the identity element.

For the maximum counterpart, see `monoid/strict_max2.hpp`.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/strict_min2.hpp"
#include <iostream>
#include <vector>

using StrictMin2M = m1une::monoid::StrictMin2<long long>;

int main() {
    std::vector<long long> A = {3, 3, 5, 8, 3, 6};
    int N = A.size();

    std::vector<StrictMin2M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = StrictMin2M::make(A[i]);
    }

    m1une::data_structure::Segtree<StrictMin2M> seg(init_data);

    auto res = seg.prod(0, 4); // Range: [3, 3, 5, 8]
    
    std::cout << "1st Min: " << res.opt1 << "\n"; // Output: 3
    std::cout << "2nd Min: " << res.opt2 << "\n"; // Output: 5

    return 0;
}
```
