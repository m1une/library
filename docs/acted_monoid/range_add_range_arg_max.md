---
title: Range Add Range ArgMax
documentation_of: ../../acted_monoid/range_add_range_arg_max.hpp
---

## Overview

An Acted Monoid to support Range Addition and queries for the Maximum Value *and its Index* (ArgMax). 

### Tie-breaking
If there are multiple maximum values in the queried range, the `op` function is designed to return the leftmost index (smallest index) by prioritizing the left child using `>=`.

## Example
When initializing the segment tree, ensure you pass the index explicitly using the `make()` helper function.

```cpp
using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
std::vector<AM::value_type> init_nodes(N);
for(int i = 0; i < N; ++i) {
    init_nodes[i] = AM::make(A[i], i);
}
m1une::data_structure::LazySegtree<AM> seg(init_nodes);
```
