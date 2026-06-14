---
title: Sparse Table
documentation_of: ../../data_structure/sparse_table.hpp
---

## Overview

A Sparse Table that answers static range queries in $O(1)$ time after an $O(N \log N)$ preprocessing step. It operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept.

**[IMPORTANT]** For $O(1)$ range queries to work correctly, the monoid operation MUST be **idempotent**. This means that `Monoid::op(x, x) == x` must hold for all valid values of `x` (e.g., Min, Max, GCD, Bitwise AND/OR). It cannot be used for operations like addition or multiplication.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`. It must be an idempotent monoid.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SparseTable()` | Constructs an empty sparse table. | $O(1)$ |
| `SparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "data_structure/sparse_table.hpp"
#include "monoid/min.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    // Initialize Sparse Table with Min Monoid
    m1une::data_structure::SparseTable<m1une::monoid::Min<long long>> st(A);

    // Get minimum of range [0, 3) -> min(5, 2, 8) = 2
    std::cout << st.prod(0, 3) << "\n";

    // Get minimum of range [2, 5) -> min(8, 1, 3) = 1
    std::cout << st.prod(2, 5) << "\n";

    return 0;
}
```
