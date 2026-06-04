---
title: Range Affine Range Sum
documentation_of: ../../acted_monoid/range_affine_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Affine Transformations ($f(x) = ax + b$) and Range Sum queries. It is commonly used with modular arithmetic (`Modint`) or standard scalar types.

### Important Usage Note

When applying an affine transformation $f(x) = ax + b$ to a range of elements, the new sum becomes $a \times \text{sum} + b \times \text{size}$. Therefore, the `value_type` must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAffineRangeSumNode<T>`, which holds both the `sum` and the `size`.

When initializing a Lazy Segment Tree, you must initialize the leaf nodes with `size = 1`. Always use the helper function `make(val)` for this purpose.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeSum<long long>;

int main() {
    int N = 3;
    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        // Initialize each leaf with the value and size = 1
        init_nodes[i] = AM::make(i + 1); // Array: {1, 2, 3}
    }

    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Apply f(x) = 2x + 3 to range [0, 2) 
    // Elements become: (2*1 + 3) = 5, and (2*2 + 3) = 7 -> Array: {5, 7, 3}
    seg.apply(0, 2, {2, 3});

    // Get the sum of range [0, 3) -> 5 + 7 + 3 = 15
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
