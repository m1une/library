---
title: Range Update Range Max
documentation_of: ../../acted_monoid/range_update_range_max.hpp
---

## Overview

An Acted Monoid representing Range Update (overwrite) operations and Range Maximum queries.

### Important Usage Note

Similar to `RangeUpdateRangeMin`, this implementation uses `std::optional<T>` as the `operator_type` to safely represent the state of "no operation" (the identity element of the operator monoid).

- A valid update operation with value $v$ is represented as `std::optional<T>(v)`.
- The identity operator (no operation) is represented as `std::nullopt`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMax<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 100 -> {10, 100, 100, 100, 50}
    seg.apply(1, 4, std::optional<long long>(100));

    // Get max of [0, 2) -> max(10, 100) = 100
    std::cout << seg.prod(0, 2) << "\n";

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
