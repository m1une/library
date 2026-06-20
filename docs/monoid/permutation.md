---
title: Permutation Monoid
documentation_of: ../../monoid/permutation.hpp
---

## Overview

A monoid for representing and composing fixed-size permutations. The underlying `value_type` is `std::array<int, N>`.

When two permutations $A$ and $B$ are merged (i.e., `op(A, B)`), it corresponds to applying permutation $A$ first, followed by permutation $B$. That is, the resulting permutation $C$ satisfies $C[i] = B[A[i]]$.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/permutation.hpp"
#include <iostream>
#include <vector>

using Perm3 = m1une::monoid::Permutation<3>;

int main() {
    std::vector<Perm3::value_type> init_data = {
        {1, 2, 0}, // Swaps elements cyclically
        {0, 2, 1}  // Swaps index 1 and 2
    };

    m1une::ds::Segtree<Perm3> seg(init_data);

    // Get the composed permutation for the range [0, 2)
    auto res = seg.prod(0, 2);

    std::cout << "0 maps to: " << res[0] << "\n";
    std::cout << "1 maps to: " << res[1] << "\n";
    std::cout << "2 maps to: " << res[2] << "\n";

    return 0;
}
```
