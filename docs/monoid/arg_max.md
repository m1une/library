---
title: ArgMax Monoid
documentation_of: ../../monoid/arg_max.hpp
---

## Overview

A monoid for finding both the maximum value and its relative order in a range. If there are multiple maximum values, it returns the earliest one.

This is defined as a type alias of `ArgMin` using `std::greater`. For the minimum counterpart, see `monoid/arg_min.hpp`.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/arg_max.hpp"
#include <iostream>
#include <vector>

using ArgMaxM = m1une::monoid::ArgMax<long long>;

int main() {
    std::vector<long long> A = {4, 8, 5, 8, 2};
    m1une::ds::Segtree<ArgMaxM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Max Value: " << res.value << "\n"; // Output: 8
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
