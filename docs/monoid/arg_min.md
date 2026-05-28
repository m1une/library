---
title: ArgMin Monoid
documentation_of: ../../monoid/arg_min.hpp
---

## Overview

A monoid for finding both the minimum value and its index in a range. If there are multiple minimum values, it returns the one with the smallest index.

For the maximum counterpart, see `monoid/arg_max.hpp`.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/arg_min.hpp"
#include <iostream>
#include <vector>

using ArgMinM = m1une::monoid::ArgMin<long long>;

int main() {
    std::vector<long long> A = {4, 2, 5, 2, 8};
    int N = A.size();

    std::vector<ArgMinM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = ArgMinM::make(A[i], i);
    }

    m1une::data_structure::Segtree<ArgMinM> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << "Min Value: " << res.first << "\n"; // Output: 2
    std::cout << "Index: " << res.second << "\n";    // Output: 1 (Index 1 is chosen over Index 3)

    return 0;
}
```
