---
title: Range Update Range Min
documentation_of: ../../acted_monoid/range_update_range_min.hpp
---

## Overview

An Acted Monoid representing Range Update (overwrite/assignment) operations and Range Minimum queries.

### Important Usage Note

This implementation uses `std::optional<T>` as the `operator_type` to safely represent the state of "no operation" (the identity element of the operator monoid).

- A valid update operation with value $v$ is represented as `std::optional<T>(v)`.
- The identity operator (no operation) is represented as `std::nullopt`.

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 5 -> {10, 5, 5, 5, 50}
    seg.apply(1, 4, std::optional<long long>(5));

    // Get the minimum in range [0, 5) -> min(10, 5, 5, 5, 50) = 5
    std::cout << seg.prod(0, 5) << "\n";

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
