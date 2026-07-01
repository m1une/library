---
title: Matroid All
documentation_of: ../../matroid/all.hpp
---

## Overview

`matroid/all.hpp` includes the standard matroid independence oracles and the
unweighted matroid-intersection algorithm.

Every oracle accepts a `const std::vector<int>&` subset and can be passed
directly to `m1une::matroid::matroid_intersection`.

Oracle subsets must contain distinct valid ground-set indices. The intersection
algorithm always satisfies this precondition.

## Included Headers

| Header | Contents |
| --- | --- |
| `matroid/uniform_matroid.hpp` | Uniform matroid $U_{r,n}$. |
| `matroid/partition_matroid.hpp` | Per-group capacity constraints. |
| `matroid/graphic_matroid.hpp` | Forest independence on graph edges. |
| `matroid/linear_matroid.hpp` | General field and 64-bit binary linear matroids. |
| `matroid/matroid_intersection.hpp` | Maximum-cardinality common independent set. |
| `matroid/weighted_matroid_intersection.hpp` | Minimum- or maximum-weight common independent set among those of maximum cardinality. |

## Example

```cpp
#include "matroid/all.hpp"
#include <vector>

int main() {
    m1une::matroid::UniformMatroid at_most_three(6, 3);
    m1une::matroid::PartitionMatroid one_per_group(
        std::vector<int>{0, 0, 1, 1, 2, 2});

    auto result = m1une::matroid::matroid_intersection(
        6, at_most_three, one_per_group);
}
```
