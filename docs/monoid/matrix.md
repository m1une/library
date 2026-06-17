---
title: Matrix Monoid
documentation_of: ../../monoid/matrix.hpp
---

## Overview

A monoid for range matrix multiplication. The underlying `value_type` is an `N x N` `std::array`. This is extremely useful for Dynamic DP, where state transitions can be represented as matrix multiplications over a segment tree.

Merging two matrices takes $O(N^3)$ time, so $N$ should be small (typically $N \le 4$).

## Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/matrix.hpp"
#include <iostream>
#include <vector>

// 2x2 Matrix with long long
using Mat = m1une::monoid::Matrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<Mat::value_type> init_data(N);
    
    // Initialize matrices (e.g., Fibonacci transition matrices)
    for (int i = 0; i < N; ++i) {
        init_data[i][0] = {1, 1};
        init_data[i][1] = {1, 0};
    }

    m1une::data_structure::Segtree<Mat> seg(init_data);

    auto res = seg.prod(0, N);
    
    std::cout << res[0][0] << " " << res[0][1] << "\n";
    std::cout << res[1][0] << " " << res[1][1] << "\n";

    return 0;
}
```
