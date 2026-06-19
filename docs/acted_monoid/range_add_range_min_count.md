---
title: Range Add Range Min Count
documentation_of: ../../acted_monoid/range_add_range_min_count.hpp
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and **its frequency (count)** in a range.

Adding a uniform constant to a range shifts all elements by the same amount. Because relative differences remain unchanged, the count of the minimum element stays exactly the same, allowing the mapping operation to be performed in $O(1)$ time.

By reusing `m1une::monoid::MinCount`, this structure can easily be converted to **Range Add Range Max Count** by passing `std::greater<T>` as the comparison functor.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min_count.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMinCount<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Initial min is 4, appearing 2 times
    auto q1 = seg.prod(0, N);
    std::cout << "Min: " << q1.first << ", Count: " << q1.second << "\n"; // Output: Min: 4, Count: 2

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4, appearing 1 time
    auto q2 = seg.prod(0, N);
    std::cout << "Min: " << q2.first << ", Count: " << q2.second << "\n"; // Output: Min: 4, Count: 1

    return 0;
}
```
