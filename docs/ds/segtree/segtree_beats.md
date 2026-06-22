---
title: Segment Tree Beats!
documentation_of: ../../../ds/segtree/segtree_beats.hpp
---

## Overview

`SegtreeBeats<T>` maintains a numeric array under the operations:

* replace each value by `min(value, upper)`,
* replace each value by `max(value, lower)`,
* add a constant,
* query range sum, minimum, or maximum.

It stores the largest and second-largest values and their multiplicities, and
the symmetric information for minima. A `chmin` update can stop at a node when
only its current maximum changes; `chmax` behaves symmetrically.

`T` must be a signed integral type. All values, additions, and sums must remain
representable by `T`. The extreme values of `T` are reserved internally as
sentinels for absent second minima and maxima.

## Methods

All ranges are zero-based and half-open.

| Method | Description |
| --- | --- |
| `SegtreeBeats(n)` | Creates `n` zeroes. |
| `SegtreeBeats(values)` | Builds from an array in $O(N)$. |
| `chmin(l, r, x)`, `range_chmin(l, r, x)` | Applies `a[i] = min(a[i], x)`. |
| `chmax(l, r, x)`, `range_chmax(l, r, x)` | Applies `a[i] = max(a[i], x)`. |
| `add(l, r, x)`, `range_add(l, r, x)` | Adds `x` to every value. |
| `sum(l, r)`, `range_sum(l, r)` | Returns the range sum. |
| `min(l, r)`, `range_min(l, r)` | Returns the range minimum. |
| `max(l, r)`, `range_max(l, r)` | Returns the range maximum. |
| `all_sum()`, `all_min()`, `all_max()` | Return whole-array aggregates. |
| `get(i)`, `operator[](i)` | Return one element. |
| `set(i, x)` | Assigns one element. |
| `to_vector()` | Materializes the array in $O(N\log N)$. |
| `size()`, `empty()` | Return the array size and emptiness. |

`sum(l, l)` returns zero. Minimum and maximum queries require a nonempty range.

## Complexity

Range sum/min/max queries and range additions take $O(\log N)$.

The standard Segment Tree Beats amortization applies to `chmin` and `chmax`:
over typical operation sequences, updates take amortized $O(\log N)$, with the
potential argument based on how often a node's distinct extrema can change.

## Example

```cpp
#include "ds/segtree/segtree_beats.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::ds::SegtreeBeats<long long> seg(
        std::vector<long long>{5, 1, 7, 3}
    );

    seg.chmin(0, 4, 4);  // 4, 1, 4, 3
    seg.chmax(1, 3, 2);  // 4, 2, 4, 3
    seg.add(0, 2, 10);   // 14, 12, 4, 3

    std::cout << seg.sum(0, 4) << "\n"; // 33
}
```
