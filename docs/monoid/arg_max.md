---
title: ArgMax Monoid
documentation_of: ../../monoid/arg_max.hpp
---

## Overview

A monoid for finding both the maximum value and its index in a range. If there are multiple maximum values, it returns the one with the smallest index.

This is defined as a type alias of `ArgMin` using `std::greater`. For the minimum counterpart, see `monoid/arg_min.hpp`.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/arg_max.hpp"
#include <iostream>
#include <vector>

using ArgMaxM = m1une::monoid::ArgMax<long long>;

int main() {
    std::vector<long long> A = {4, 8, 5, 8, 2};
    int N = A.size();

    std::vector<ArgMaxM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = ArgMaxM::make(A[i], i);
    }

    m1une::data_structure::Segtree<ArgMaxM> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << "Max Value: " << res.first << "\n"; // Output: 8
    std::cout << "Index: " << res.second << "\n";    // Output: 1 (Index 1 is chosen over Index 3)

    return 0;
}
```
