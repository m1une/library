---
title: Range Add Range ArgMax
documentation_of: ../../acted_monoid/range_add_range_arg_max.hpp
---

## Overview

An acted monoid for range addition and range maximum queries with the position
of the selected maximum.

### Tie-breaking

If there are multiple maximum values in the queried range, the `op` function returns the earliest order.

## Example

```cpp
using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
m1une::data_structure::LazySegtree<AM> seg(A);
auto q = seg.prod(0, A.size());
std::cout << q.max_val << " " << q.ord << "\n";
```
