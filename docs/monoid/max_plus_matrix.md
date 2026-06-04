---
title: Max-Plus Matrix Monoid
documentation_of: ../../monoid/max_plus_matrix.hpp
---

## Overview

A monoid for range matrix multiplication over the Max-Plus semiring. 
In this algebra, the standard addition operation is replaced by `std::max`, and the standard multiplication operation is replaced by regular addition `+`.

This is highly effective for solving **Dynamic DP** problems (where state transitions involve taking the maximum of sums) or finding longest paths over dynamic edge weights on a Segment Tree.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/max_plus_matrix.hpp"
#include <iostream>
#include <vector>

using MaxMat = m1une::monoid::MaxPlusMatrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<MaxMat::value_type> init_data(N);
    
    for (int i = 0; i < N; ++i) {
        auto mat = MaxMat::make_inf();
        mat[0][0] = 5; 
        mat[0][1] = 2; 
        mat[1][0] = 3; 
        mat[1][1] = 0; 
        init_data[i] = mat;
    }

    m1une::data_structure::Segtree<MaxMat> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << "Max Cost 0 -> 0: " << res[0][0] << "\n";
    return 0;
}
```
