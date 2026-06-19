---
title: Range Update Range Max Subarray
documentation_of: ../../acted_monoid/range_update_range_max_subarray.hpp
---

## Overview

An Acted Monoid for answering Maximum Contiguous Subarray Sum queries subject to Range Assignment (Set/Update) operations.

It maintains the total sum, prefix max, suffix max, and maximum subarray sum for each segment tree node. This represents a classic competitive programming pattern (e.g., CSES "Hotel Queries" variations or AtCoder Library practice).

### Usage Notes

* `operator_type` uses `std::optional<T>`, where `std::nullopt` represents no operation.
* By default, it allows picking an empty subarray (the minimum possible answer is `0`).

## Example

```cpp
using AM = m1une::acted_monoid::RangeUpdateRangeMaxSubarray<long long>;
// seg.prod(l, r).max_sub will give the maximum subarray sum in range [l, r)
// seg.apply(l, r, 5) will set all elements in [l, r) to 5.
```
