---
title: Range Affine Range Min Max
documentation_of: ../../acted_monoid/range_affine_range_min_max.hpp
---

## Overview

An exceptionally versatile Acted Monoid that tracks both the **minimum** and **maximum** values of a contiguous subarray simultaneously while supporting Range Affine Transformations ($f(x) = ax + b$). 

This acted monoid perfectly handles **negative scale factors** ($a < 0$). When a negative value multiplies a range, the relative ordering inverts: the previous minimum becomes the basis for the new maximum, and the previous maximum becomes the basis for the new minimum. By maintaining both boundaries, the data structure accurately maps the state without losing validity.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`, `double`, or a custom floating type).
* `MinId`: The identity element for the minimum operation. Defaults to `std::numeric_limits<T>::max()`.
* `MaxId`: The identity element for the maximum operation. Defaults to `std::numeric_limits<T>::lowest()`.

## Data Structure

* `using value_type = RangeAffineRangeMinMaxNode<T>;`
  The compound state maintained in each segment tree node:
  * `min_val`: The minimum scalar within the range.
  * `max_val`: The maximum scalar within the range.
* `using operator_type = std::pair<T, T>;`
  A pair representing the linear coefficient and addend `{a, b}` for the function $f(x) = ax + b$.

## Element Creation

When building or updating individual elements, use the `make(val)` helper function to encapsulate the scalar into a node matching the value monoid specification.

### `static constexpr value_type make(const T& val)`
* **Parameters:**
  * `val`: The initial scalar value.
* **Returns:** A `RangeAffineRangeMinMaxNode` where both `min_val` and `max_val` are set to `val`.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_min_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeMinMax<long long>;

int main() {
    std::vector<long long> A = {2, 5, 3, 8, 4};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Query range [0, 3) -> Elements: {2, 5, 3} -> Min: 2, Max: 5
    auto q1 = seg.prod(0, 3);
    std::cout << "Min: " << q1.min_val << ", Max: " << q1.max_val << "\n"; // Output: Min: 2, Max: 5

    // Apply negative affine transformation f(x) = -2x + 3 to range [0, 3)
    // New values inside range become:
    // 2 -> -2(2) + 3 = -1
    // 5 -> -2(5) + 3 = -7
    // 3 -> -2(3) + 3 = -3
    // Range is now: {-1, -7, -3}
    seg.apply(0, 3, {-2, 3});

    // Query range [0, 3) again -> Min should be -7, Max should be -1
    auto q2 = seg.prod(0, 3);
    std::cout << "Updated Min: " << q2.min_val << ", Updated Max: " << q2.max_val << "\n"; // Output: Min: -7, Max: -1

    return 0;
}
```
