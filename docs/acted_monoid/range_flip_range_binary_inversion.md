---
title: Range Flip Range Binary Inversion
documentation_of: ../../acted_monoid/range_flip_range_binary_inversion.hpp
---

## Overview

An Acted Monoid designed for binary arrays (01-strings) to support range bit-flipping operations (inverting $0 \leftrightarrow 1$) and range binary inversion queries (the number of pairs $(i, j)$ such that $i < j$ and $A[i] = 1, A[j] = 0$).

This acted monoid leverages the structure of `m1une::monoid::BinaryInversionNode`. When a range is flipped, the counts of zeros and ones are swapped. Concurrently, the new number of inversions is computed as the total number of possible pairs minus the old number of inversions:
$$\text{new\_inversions} = (\text{zeros} \times \text{ones}) - \text{old\_inversions}$$

## Template Parameters

* `T`: The underlying scalar integer type used to store counts and inversion numbers (e.g., `long long`).

## Data Structure

* `using value_type = m1une::monoid::BinaryInversionNode<T>;`
  The state tracked in each segment tree node:
  * `zeros`: The number of `0`s in the segment.
  * `ones`: The number of `1`s in the segment.
  * `inversions`: The number of pairs where `1` appears before `0`.
* `using operator_type = bool;`
  A boolean flag representing whether the segment needs to be flipped (`true`) or not (`false`).

## Element Creation

When initializing the lazy segment tree, you must transform the raw binary values (`0` or `1`) into valid monoid nodes.
**Always use the `make(val)` helper method** to securely build the leaf nodes.

### `static constexpr value_type make(int val)`

* **Parameters:**
  * `val`: The binary element value (`0` or `1`).
* **Returns:** A `BinaryInversionNode` properly initialized for a single element.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_flip_range_binary_inversion.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeFlipRangeBinaryInversion<long long>;

int main() {
    // Initial binary array: [1, 0, 1, 0, 0]
    std::vector<int> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // 1. Query entire array inversion count
    // Initial inversions: 5 (index pairs: (0,1), (0,3), (0,4), (2,3), (2,4))
    std::cout << "Initial Inversions: " << seg.all_prod().inversions << "\n"; // Output: 5

    // 2. Range Flip: Invert bits in range [1, 4) -> indices 1, 2, 3
    // A becomes: [1, 1, 0, 1, 0]
    seg.apply(1, 4, true);

    // 3. Query after inversion
    // New inversions: 5 (index pairs: (0,2), (0,4), (1,2), (1,4), (3,4))
    auto res = seg.prod(0, N);
    std::cout << "Zeros: " << res.zeros << ", Ones: " << res.ones << "\n"; // Output: Zeros: 2, Ones: 3
    std::cout << "Updated Inversions: " << res.inversions << "\n";         // Output: 5

    return 0;
}
```
