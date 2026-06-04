---
title: Range Add Range ArgMin
documentation_of: ../../acted_monoid/range_add_range_arg_min.hpp
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and its **corresponding index** in a range.

Adding a uniform constant to a range shifts all elements by the same amount, meaning the relative ordering remains unchanged. Thus, the index of the minimum (or maximum) element is perfectly preserved after range additions. This is highly useful in sweepline algorithms or resource allocation problems where you need to identify *where* the minimum value is located.

By reusing `m1une::monoid::ArgMin`, this structure resolves ties by prioritizing the smaller index.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`. To build a **Range Add Range ArgMax**, simply pass `std::greater<T>`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_arg_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeArgMin<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i], i);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Initial min is 4 at index 1 (ties broken by smaller index)
    auto q1 = seg.prod(0, N);
    std::cout << "Min: " << q1.first << ", Index: " << q1.second << "\n"; // Output: Min: 4, Index: 1

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4 at index 3
    auto q2 = seg.prod(0, N);
    std::cout << "Min: " << q2.first << ", Index: " << q2.second << "\n"; // Output: Min: 4, Index: 3

    return 0;
}
```
