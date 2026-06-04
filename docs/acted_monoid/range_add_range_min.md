---
title: Range Add Range Min
documentation_of: ../../acted_monoid/range_add_range_min.hpp
---

## Overview

An Acted Monoid representing Range Addition operations and Range Minimum queries. It safely handles the identity element to prevent wrapping or incorrect modifications on uninitialized values.

## Template Parameters

* `T`: The underlying scalar data type (e.g., `long long`, `int`).
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::data_structure::LazySegtree<AM> seg(A);

    // Add -15 to all elements in range [1, 4) -> {10, 5, 15, 25, 50}
    seg.apply(1, 4, -15);

    // Get the minimum in range [0, 3) -> min(10, 5, 15) = 5
    std::cout << seg.prod(0, 3) << "\n"; 

    return 0;
}
```
