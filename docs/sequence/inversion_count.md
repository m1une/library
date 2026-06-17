---
title: Inversion Count
documentation_of: ../../sequence/inversion_count.hpp
---

## Overview

Calculates the number of inversions in a given sequence. An inversion is a pair of indices `(i, j)` such that `i < j` and `a[i] > a[j]`. It represents how far away the array is from being completely sorted.

The algorithm uses a modified Merge Sort, which is highly efficient and operates seamlessly on any comparable data type (e.g., `int`, `long long`, `double`, `std::string`) without requiring coordinate compression.

*Note: The function returns a `long long` because the maximum number of inversions in an array of size $N$ is $N(N-1)/2$, which will easily overflow a standard 32-bit `int` for $N \ge 10^5$.*

## Template Parameters

* `T`: The underlying data type of the sequence elements. Must be comparable using `<=`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `long long inversion_count(std::vector<T> a)` | Returns the total number of inversions. The argument is taken by value. Use `std::move(a)` if you no longer need the original array to avoid an $O(N)$ copy. | $O(N \log N)$ time, $O(N)$ space |

## Example

```cpp
#include "sequence/inversion_count.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {2, 4, 1, 3, 5};
    
    // Calculate inversions
    long long invs = m1une::sequence::inversion_count(a);
    
    // The inversions are:
    // (2, 1) -> indices 0 and 2
    // (4, 1) -> indices 1 and 2
    // (4, 3) -> indices 1 and 3
    std::cout << "Inversions: " << invs << "\n"; // Output: 3
    
    // To avoid copying the array if you don't need it afterward:
    // long long fast_invs = m1une::sequence::inversion_count(std::move(a));

    return 0;
}
```
