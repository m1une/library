---
title: Range Affine Range Sum of Squares
documentation_of: ../../acted_monoid/range_affine_range_sum_of_squares.hpp
---

## Overview

An Acted Monoid representing Range Affine Transformations ($f(x) = ax + b$) and Range Sum of Squares queries. This is an incredibly powerful structure for calculating expected values, variances, or quadratic constraints over dynamic arrays in $O(\log N)$ time.

### Mathematical Mechanism

When an affine transformation $f(x) = ax + b$ is applied to a range, the new sum of squares is expanded algebraically:
$$\sum (ax_i + b)^2 = a^2 \left(\sum x_i^2\right) + 2ab \left(\sum x_i\right) + b^2 \cdot \text{size}$$

To support this $O(1)$ mapping operation, the node state (`value_type`) tracks three properties of the segment: the sum of squares (`sum_sq`), the standard sum (`sum`), and the `size`.

## Template Parameters

* `T`: The underlying numerical type. This is often used with a modular arithmetic struct (e.g., `Modint`) to prevent overflow, but standard `long long` works if numbers are small.

## Operator Details

The `operator_type` is an `std::pair<T, T>` representing `{a, b}` in $f(x) = ax + b$.
This allows you to perform multiple types of range operations seamlessly:
* **Range Add $C$:** Use `{1, C}`
* **Range Multiply $C$:** Use `{C, 0}`
* **Range Assign/Overwrite $C$:** Use `{0, C}` (the $a=0$ coefficient completely zeroes out the old sum, effectively replacing the entire segment).

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_affine_range_sum_of_squares.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAffineRangeSumOfSquares<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Initial sum of squares for [0, 3): 1^2 + 2^2 + 3^2 = 14
    std::cout << "Initial Sum_Sq: " << seg.prod(0, 3).sum_sq << "\n"; // Output: 14

    // Apply affine function: f(x) = 2x + 1 to range [0, 2)
    // 1 -> 2(1)+1 = 3
    // 2 -> 2(2)+1 = 5
    // Array becomes: {3, 5, 3}
    seg.apply(0, 2, {2, 1});

    // New sum of squares for [0, 3): 3^2 + 5^2 + 3^2 = 9 + 25 + 9 = 43
    std::cout << "Updated Sum_Sq: " << seg.prod(0, 3).sum_sq << "\n"; // Output: 43

    return 0;
}
```
