---
title: Range Update Range Longest True
documentation_of: ../../acted_monoid/range_update_range_longest_true.hpp
---

## Overview

An Acted Monoid designed to solve "Hotel Queries" or contiguous memory allocation problems. It supports range overwrite operations (setting a block to all `true` or all `false`) and queries the **maximum contiguous length** of `true` values in a range.

Because updating an entire segment to `true` simply makes the contiguous length equal to the segment's total length (and updating to `false` makes it `0`), the mapping operation executes in $O(1)$ time by leveraging the `m1une::monoid::LongestTrueNode`.

## Data Structure

* `using value_type = m1une::monoid::LongestTrueNode;`
  The state maintained in each segment tree node:
  * `len`: Total length of the segment.
  * `max_len`: The longest contiguous block of `true`.
  * `l_len`: The length of the contiguous `true` block starting from the left edge.
  * `r_len`: The length of the contiguous `true` block starting from the right edge.
* `using operator_type = std::optional<bool>;`
  An optional boolean representing the overwrite operation. `std::nullopt` represents the identity operation.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_longest_true.hpp"
#include <iostream>
#include <vector>
#include <optional>

using AM = m1une::acted_monoid::RangeUpdateRangeLongestTrue;

int main() {
    // 1 implies the seat is empty (true), 0 implies occupied (false)
    std::vector<bool> A = {true, false, true, true, false, true};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    // Initial longest block of empty seats is 2 (indices 2 to 3)
    std::cout << "Max empty block: " << seg.all_prod().max_len << "\n"; // Output: 2

    // Free up seats in range [4, 6) -> {true, false, true, true, true, true}
    seg.apply(4, 6, std::optional<bool>(true));

    // The new longest contiguous block of empty seats is now 4 (indices 2 to 5)
    std::cout << "Max empty block: " << seg.all_prod().max_len << "\n"; // Output: 4

    return 0;
}
```
