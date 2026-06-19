---
title: Longest Increasing Subsequence (LIS)
documentation_of: ../../sequence/lis.hpp
---

## Overview

Returns the zero-based indices of a longest increasing subsequence. The indices
can be used to recover the values or to align the result with parallel arrays.

The implementation uses a tails array and predecessor links. It uses
`std::lower_bound` for a strict subsequence and `std::upper_bound` for a
non-decreasing subsequence.

## Template Parameters

* `T`: Element type. Values must be comparable using `<`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> lis(const std::vector<T>& a, bool strict = true)` | Returns the indices of the LIS. If `strict` is `true`, finds a strictly increasing sequence. If `false`, allows adjacent elements in the sequence to be equal (non-decreasing). | $O(N \log N)$ time, $O(N)$ space |

## Example

```cpp
#include "sequence/lis.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    const std::vector<int> lis_indices = m1une::sequence::lis(a);

    std::cout << "LIS length: " << lis_indices.size() << "\n"; // Output: 4

    std::cout << "Indices: ";
    for (int idx : lis_indices) std::cout << idx << " ";
    std::cout << "\n";

    std::cout << "Values: ";
    for (int idx : lis_indices) std::cout << a[idx] << " ";
    std::cout << "\n";

    const std::vector<int> non_decreasing = m1une::sequence::lis(a, false);
    std::cout << "Non-decreasing length: " << non_decreasing.size() << "\n";

    return 0;
}
```
