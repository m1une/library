---
title: Disjoint Sparse Table
documentation_of: ../../data_structure/disjoint_sparse_table.hpp
---

## Overview

A Disjoint Sparse Table that answers static range queries in $O(1)$ time after an $O(N \log N)$ preprocessing step. It operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept.

Unlike a normal Sparse Table, the monoid operation does not need to be idempotent. It can be used for operations like addition, multiplication, matrix multiplication, and other associative operations.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `DisjointSparseTable()` | Constructs an empty disjoint sparse table. | $O(1)$ |
| `DisjointSparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "data_structure/disjoint_sparse_table.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    m1une::data_structure::DisjointSparseTable<m1une::monoid::Add<long long>> dst(A);

    // Get sum of range [0, 3) -> 5 + 2 + 8 = 15
    std::cout << dst.prod(0, 3) << "\n";

    // Get sum of range [2, 5) -> 8 + 1 + 3 = 12
    std::cout << dst.prod(2, 5) << "\n";

    return 0;
}
```
