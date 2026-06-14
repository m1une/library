---
title: ArgMax Monoid
documentation_of: ../../monoid/arg_max.hpp
---

## Overview

A monoid for finding both the maximum value and its relative order in a range. If there are multiple maximum values, it returns the earliest one.

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
    m1une::data_structure::Segtree<ArgMaxM> seg(A);

    auto res = seg.prod(0, A.size());
    
    std::cout << "Max Value: " << res.value << "\n"; // Output: 8
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
