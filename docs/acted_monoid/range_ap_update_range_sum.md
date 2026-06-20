---
title: Range AP Update Range Sum
documentation_of: ../../acted_monoid/range_ap_update_range_sum.hpp
---

## Overview

An Acted Monoid that supports overwriting a range with an arithmetic progression, alongside range sum queries.

The operator replaces existing elements with $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Important Usage Note

Similar to `RangeApAddRangeSum`, the node state (`value_type`) tracks `size` and the sum of relative orders (`ord_sum`), enabling $O(1)$ block updates.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`. The `operator_type` relies on `std::optional` to safely designate the "no operation" state.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite the range [0, 3) with f(i) = 3 * i + 1, where i is local to [0, 3)
    // Array becomes: {1, 4, 7, 40, 50}
    seg.apply(0, 3, std::optional<std::pair<long long, long long>>({3, 1}));

    // Query sum of range [0, 3) -> 1 + 4 + 7 = 12
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
