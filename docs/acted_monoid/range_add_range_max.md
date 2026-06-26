---
title: Range Add Range Max
documentation_of: ../../acted_monoid/range_add_range_max.hpp
---

## Overview

An Acted Monoid representing Range Addition operations and Range Maximum queries.

It uses `std::numeric_limits<T>::lowest()` as the default identity element for the Value Monoid to correctly handle negative maximum values.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMax<long long>;

int main() {
    std::vector<long long> A = {1, 5, 2, 8, 3};
    m1une::ds::LazySegtree<AM> seg(A);

    // Get the maximum value in [1, 4) -> max(5, 2, 8) = 8
    std::cout << seg.prod(1, 4) << "\n";

    // Add 10 to range [1, 3) -> {1, 15, 12, 8, 3}
    seg.apply(1, 3, 10);

    // Get the maximum value in [1, 4) -> max(15, 12, 8) = 15
    std::cout << seg.prod(1, 4) << "\n";

    return 0;
}
```

## Interface and Complexity

This is a stateless acted-monoid tag. Lazy data structures use its public
`value_type`, `operator_type`, `id()`, `op(a, b)`, `op_id()`, `op_comp(f, g)`,
and `mapping(f, x)` members. Helpers such as `make(...)`, shifted mappings, or
reversal-aware mappings are described above when the header provides them.

The static operations are $O(1)$ for the scalar metadata stored by these range
acted monoids, aside from the cost of the underlying arithmetic type.
