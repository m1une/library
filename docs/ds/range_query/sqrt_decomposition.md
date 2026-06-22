---
title: Square-Root Decomposition
documentation_of: ../../../ds/range_query/sqrt_decomposition.hpp
---

## Overview

`SqrtDecomposition<Monoid>` divides a mutable array into blocks of approximately
$\sqrt N$ elements. Each block stores its ordered monoid product.

It supports point assignments and range products without the complexity of a
segment tree. Any associative monoid is supported, including
non-commutative operations.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N)$ |
| `set(index, value)` | $O(\sqrt N)$ |
| `prod(left, right)` | $O(\sqrt N)$ |
| `all_prod()` | $O(\sqrt N)$ |
| `get(index)` | $O(1)$ |

Ranges are zero-based and half-open.

## Methods

| Method | Description |
| --- | --- |
| `SqrtDecomposition(n)` | Creates `n` identity elements. |
| `SqrtDecomposition(values)` | Builds from an array. |
| `size()`, `empty()` | Return the array size and whether it is empty. |
| `set(index, value)` | Assigns an element and rebuilds its block. |
| `get(index)`, `operator[](index)` | Return an element. |
| `prod(left, right)` | Returns the ordered product over `[left, right)`. |
| `all_prod()` | Returns the product over the complete array. |

Construction from another element type uses `Monoid::make(value)`, then
`Monoid::make(value, index)`, then conversion to the monoid value type,
whichever is available.

## Block Access

For custom square-root-decomposition algorithms, the structure exposes:

* `block_size()` and `block_count()`
* `block_of(index)`
* `block_range(block)`
* `values()`
* `block_products()`

These views are read-only so the cached products cannot silently become stale.
Use `set` to modify an element.

## Example

```cpp
#include "ds/range_query/sqrt_decomposition.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {1, 2, 3, 4, 5};
    m1une::ds::SqrtDecomposition<m1une::monoid::Add<long long>> blocks(values);

    std::cout << blocks.prod(1, 4) << "\n";  // 9
    blocks.set(2, 10);
    std::cout << blocks.prod(1, 4) << "\n";  // 16
}
```
