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
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMax<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::data_structure::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 100 -> {10, 100, 100, 100, 50}
    seg.apply(1, 4, std::optional<long long>(100));

    // Get max of [0, 2) -> max(10, 100) = 100
    std::cout << seg.prod(0, 2) << "\n";

    return 0;
}
```
