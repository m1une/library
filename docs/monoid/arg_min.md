---
title: ArgMin Monoid
documentation_of: ../../monoid/arg_min.hpp
---

## Overview

A monoid for finding both the minimum value and its relative order in a range. If there are multiple minimum values, it returns the earliest one.

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
    m1une::data_structure::Segtree<ArgMinM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Min Value: " << res.value << "\n"; // Output: 2
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
