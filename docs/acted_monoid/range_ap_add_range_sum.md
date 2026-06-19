---
title: Range AP Add Range Sum
documentation_of: ../../acted_monoid/range_ap_add_range_sum.hpp
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries.

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Important Usage Note

The node state (`value_type`) stores `size` and the sum of relative orders (`ord_sum`) it covers. This makes it usable in dynamic arrays where global indices change after insertions, deletions, and reversals.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    m1une::data_structure::LazySegtree<AM> seg(A);

    // Add f(i) = 2 * i + 5 to the range [1, 4), where i is local to [1, 4)
    // Array becomes: {0, 5, 7, 9, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 5 + 7 + 9 + 0 = 21
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
