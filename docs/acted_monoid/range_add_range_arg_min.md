---
title: Range Add Range ArgMin
documentation_of: ../../acted_monoid/range_add_range_arg_min.hpp
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and its **relative order** in a range.

Adding a uniform constant to a range shifts all elements by the same amount, meaning the relative ordering remains unchanged.

By reusing `m1une::monoid::ArgMin`, this structure resolves ties by prioritizing the earlier order.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`. To build a **Range Add Range ArgMax**, simply pass `std::greater<T>`.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_arg_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeArgMin<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    m1une::ds::LazySegtree<AM> seg(A);

    // Initial min is 4 at order 1 (ties broken by earlier order)
    auto q1 = seg.prod(0, A.size());
    std::cout << "Min: " << q1.value << ", Order: " << q1.ord << "\n"; // Output: Min: 4, Order: 1

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4 at order 3
    auto q2 = seg.prod(0, A.size());
    std::cout << "Min: " << q2.value << ", Order: " << q2.ord << "\n"; // Output: Min: 4, Order: 3

    return 0;
}
```
