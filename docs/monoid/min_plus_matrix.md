---
title: Min-Plus Matrix Monoid
documentation_of: ../../monoid/min_plus_matrix.hpp
---

## Overview

A monoid for range matrix multiplication over the Min-Plus (Tropical) semiring. 
In this algebra, the standard addition operation is replaced by `std::min`, and the standard multiplication operation is replaced by regular addition `+`.

This is highly effective for solving **Dynamic DP** problems (where state transitions involve taking the minimum of sums) or finding shortest paths over dynamic edge weights on a Segment Tree.

Merging two matrices takes $O(N^3)$ time, so $N$ should be kept small.

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/min_plus_matrix.hpp"
#include <iostream>
#include <vector>

// 2x2 Min-Plus Matrix with long long
using MinMat = m1une::monoid::MinPlusMatrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<MinMat::value_type> init_data(N);
    
    // Initialize state transitions
    for (int i = 0; i < N; ++i) {
        auto mat = MinMat::make_inf();
        mat[0][0] = 5; // Transition cost from state 0 to 0
        mat[0][1] = 2; // Transition cost from state 1 to 0
        mat[1][0] = 3; // Transition cost from state 0 to 1
        mat[1][1] = 0; // Transition cost from state 1 to 1
        init_data[i] = mat;
    }

    m1une::data_structure::Segtree<MinMat> seg(init_data);

    // Get the transition matrix for the range [0, 3)
    auto res = seg.prod(0, N);
    
    // Output the shortest path cost from initial state j to final state i
    std::cout << "Cost 0 -> 0: " << res[0][0] << "\n";
    std::cout << "Cost 1 -> 0: " << res[0][1] << "\n";

    return 0;
}
```
