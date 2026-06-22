---
title: Sqrt Tree
documentation_of: ../../../ds/range_query/sqrt_tree.hpp
---

## Overview

`SqrtTree<Monoid>` is a static range-product structure based on recursive
square-root decomposition. It supports any associative monoid, including
non-idempotent and non-commutative operations.

At each level, every block stores:

* prefix products,
* suffix products,
* products between complete child blocks.

A query uses the highest bit at which its two endpoints differ to select the
correct decomposition layer directly. It then combines at most three stored
products.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N\log\log N)$ time and memory |
| `prod(left, right)` | $O(1)$ |
| `all_prod()` | $O(1)$ |

Compared with `DisjointSparseTable`, Sqrt Tree retains constant-time queries
while reducing preprocessing and memory from $O(N\log N)$ to
$O(N\log\log N)$.

## Methods

| Method | Description |
| --- | --- |
| `SqrtTree(values)` | Builds the structure from an array. |
| `size()` | Returns the array length. |
| `empty()` | Returns whether the array is empty. |
| `prod(left, right)` | Returns the ordered monoid product over `[left, right)`. |
| `all_prod()` | Returns the product over the complete array. |

An empty range returns `Monoid::id()`.

As with the repository's sparse tables, construction from another element type
uses `Monoid::make(value)`, then `Monoid::make(value, index)`, then conversion
to the monoid value type, whichever is available.

## Example

```cpp
#include "ds/range_query/sqrt_tree.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {1, 2, 3, 4, 5};
    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);

    std::cout << tree.prod(1, 4) << "\n";  // 9
}
```
