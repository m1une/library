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
#include "ds/segtree/lazy_segtree.hpp"
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

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Apply f(x) = 2x + 3 to range [0, 2)
    // Elements become: (2*1 + 3) = 5, and (2*2 + 3) = 7 -> Array: {5, 7, 3}
    seg.apply(0, 2, {2, 3});

    // Get the sum of range [0, 3) -> 5 + 7 + 3 = 15
    std::cout << seg.prod(0, 3).sum << "\n";

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
