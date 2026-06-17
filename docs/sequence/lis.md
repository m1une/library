---
title: Longest Increasing Subsequence (LIS)
documentation_of: ../../sequence/lis.hpp
---

## Overview

Calculates the Longest Increasing Subsequence (LIS) of a given array. Instead of returning just the maximum length or the raw values, this function optimally computes and returns a `std::vector<int>` containing the **0-based indices** of the elements that form the sequence. 

This enables you to easily reconstruct the sequence, query the original elements, or correlate them with parallel arrays.

The implementation tracks the DP array and back-pointers, utilizing `std::lower_bound` (or `std::upper_bound`) to run efficiently in $O(N \log N)$ time.

## Template Parameters

* `T`: The underlying data type of the elements in the array. Must be comparable using `<`.

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
    
    // Find strictly increasing subsequence
    std::vector<int> lis_indices = m1une::sequence::lis(a);
    
    std::cout << "LIS Length: " << lis_indices.size() << "\n"; // Output: 4
    
    std::cout << "Indices: ";
    for (int idx : lis_indices) std::cout << idx << " ";
    // Output might be: 1 2 4 5  (corresponding to indices of 1, 4, 5, 9)
    std::cout << "\n";
    
    std::cout << "Values: ";
    for (int idx : lis_indices) std::cout << a[idx] << " ";
    // Output: 1 4 5 9
    std::cout << "\n";

    // Find non-decreasing subsequence (allows duplicates)
    std::vector<int> nds_indices = m1une::sequence::lis(a, false);
    
    std::cout << "Non-Decreasing Length: " << nds_indices.size() << "\n"; // Output: 5
    // A valid non-decreasing sequence values: 1 1 2 3 5
    
    return 0;
}
```
