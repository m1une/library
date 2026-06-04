---
title: Affine Monoid
documentation_of: ../../monoid/affine.hpp
---

## Overview

A monoid for composing affine transformations, expressed as $f(x) = ax + b$. 
The underlying `value_type` is `std::pair<T, T>`, where `first` represents $a$ (the multiplier) and `second` represents $b$ (the addend).

This is particularly useful when you have a sequence of operations like "multiply by $X$, then add $Y$" and you want to find the composite function of a range.

## Initialization

You can create operations directly using pairs, or use the provided helper functions for clarity:

* **Add $C$:** `make_add(C)` -> `{1, C}`
* **Multiply by $C$:** `make_mul(C)` -> `{C, 0}`
* **Assign $C$:** `make_assign(C)` -> `{0, C}`

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/affine.hpp"
#include <iostream>

using AffineM = m1une::monoid::Affine<long long>;

int main() {
    // Operations:
    // 0: f(x) = 2x + 3
    // 1: f(x) = 1x + 5 (Add 5)
    // 2: f(x) = 3x + 0 (Multiply by 3)
    
    std::vector<AffineM::value_type> ops = {
        {2, 3}, 
        AffineM::make_add(5), 
        AffineM::make_mul(3)
    };

    m1une::data_structure::Segtree<AffineM> seg(ops);

    // Get the composite function for the range [0, 2)
    // f(x) = 1 * (2x + 3) + 5 = 2x + 8
    auto [a, b] = seg.prod(0, 2);
    std::cout << "f(x) = " << a << "x + " << b << "\n"; // Output: 2x + 8

    return 0;
}
```
