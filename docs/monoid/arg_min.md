---
title: ArgMin Monoid
documentation_of: ../../monoid/arg_min.hpp
---

## Overview

A monoid for finding both the minimum value and its relative order in a range. If there are multiple minimum values, it returns the earliest one.

For the maximum counterpart, see `monoid/arg_max.hpp`.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/arg_min.hpp"
#include <iostream>
#include <vector>

using ArgMinM = m1une::monoid::ArgMin<long long>;

int main() {
    std::vector<long long> A = {4, 2, 5, 2, 8};
    m1une::ds::Segtree<ArgMinM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Min Value: " << res.value << "\n"; // Output: 2
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

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
