---
title: Range AP Update Range Min Max
documentation_of: ../../acted_monoid/range_ap_update_range_min_max.hpp
---

## Overview

An acted monoid that overwrites a range with an arithmetic progression and
queries the minimum and maximum values in a range.

The operator replaces existing elements with a linear function $f(i) = a \cdot i + b$, where $i$ is the 0-based order inside the updated range.

### Mathematical Mechanism

Unlike AP Addition (which cannot support Min/Max queries because the sum of an arbitrary curve and a line is unpredictable), AP **Update** completely overwrites the segment data with a perfectly straight line.

Because a linear function is monotonic, the minimum and maximum values over any continuous range occur at the boundary endpoints. Therefore, by storing the segment `size`, the new Min/Max can be computed in $O(1)$ time by evaluating the local endpoints.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `MinId`: The identity element for the minimum operation. Defaults to `std::numeric_limits<T>::max()`.
* `MaxId`: The identity element for the maximum operation. Defaults to `std::numeric_limits<T>::lowest()`.

## Data Structure

* `using value_type = RangeApUpdateRangeMinMaxNode<T>;`
  The state maintained in each segment tree node:
  * `min_val`: The minimum scalar within the range.
  * `max_val`: The maximum scalar within the range.
  * `size`: The number of elements in the range.
* `using operator_type = std::optional<std::pair<T, T>>;`
  An optional pair representing the linear coefficient and addend `{a, b}` for the overwrite function $f(i) = a \cdot i + b$.

## Element Creation

Leaf nodes are initialized with `make(val)` or by constructing a data structure directly from raw values.

### `static constexpr value_type make(const T& val)`

* **Parameters:**
  * `val`: The initial scalar value of the element.
* **Returns:** A fully initialized single-element node.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_update_range_min_max.hpp"
#include <iostream>
#include <vector>
#include <optional>
#include <utility>

using AM = m1une::acted_monoid::RangeApUpdateRangeMinMax<long long>;

int main() {
    std::vector<long long> A = {10, 5, 20, 15, 30};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite the range [1, 5) with f(i) = -3 * i + 100, where i is local to [1, 5)
    // Array conceptually becomes: {10, 100, 97, 94, 91}
    seg.apply(1, 5, std::optional<std::pair<long long, long long>>({-3, 100}));

    // Query Min/Max of range [2, 5) -> Elements: {97, 94, 91}
    auto q = seg.prod(2, 5);
    std::cout << "Min: " << q.min_val << "\n"; // Output: 91
    std::cout << "Max: " << q.max_val << "\n"; // Output: 97

    return 0;
}
```
