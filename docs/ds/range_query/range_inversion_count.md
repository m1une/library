---
title: Static Range Inversion Count
documentation_of: ../../../ds/range_query/range_inversion_count.hpp
---

## Overview

`RangeInversionCount<T>` preprocesses a static array and answers inversion
counts for arbitrary subarrays.

For a query `[left, right)`, it returns the number of pairs `(i, j)` satisfying

$$
\mathrm{left}\le i<j<\mathrm{right}
\quad\text{and}\quad
a_i>a_j.
$$

Equal values are not inversions.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N\sqrt N)$ time and memory |
| `query(left, right)` | $O(\sqrt N)$ |

The values only need equality and `<` comparisons. They are compressed during
construction.

## How It Works

The array is divided into blocks of approximately $\sqrt N$ elements.
Preprocessing stores:

* inversion counts from every block boundary to every right endpoint,
* cumulative value-rank counts at block boundaries,
* inversion counts for all ranges contained in one block,
* sorted prefixes and suffixes of each block.

A query begins with the answer from the first complete block boundary. The
remaining left fringe contributes its internal inversions, inversions against
complete blocks through rank-count tables, and inversions against the final
partial block through a linear merge of two sorted boundary pieces.

## Methods

| Method | Description |
| --- | --- |
| `RangeInversionCount(values)` | Builds the static structure. |
| `query(left, right)` | Returns inversions in `[left, right)`. |
| `inversion_count(left, right)` | Alias of `query`. |
| `size()`, `empty()` | Return the array size and whether it is empty. |
| `block_size()` | Returns the selected decomposition block size. |

## Example

```cpp
#include "ds/range_query/range_inversion_count.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {3, 1, 4, 1, 5};
    m1une::ds::RangeInversionCount<int> inversions(values);

    std::cout << inversions.query(0, 5) << "\n"; // 3
    std::cout << inversions.query(1, 4) << "\n"; // 1
}
```
