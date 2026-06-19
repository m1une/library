---
title: Inversion Count
documentation_of: ../../sequence/inversion_count.hpp
---

## Overview

Calculates the number of inversions in a sequence. An inversion is a pair of
indices `(i, j)` such that `i < j` and `a[i] > a[j]`.

The implementation uses merge sort and does not require coordinate compression.

The return type is `long long` because a sequence of size $N$ can have
$N(N-1)/2$ inversions.

## Template Parameters

* `T`: Element type. Values must be comparable using `<`.

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

    const long long inversions = m1une::sequence::inversion_count(a);

    // The inversions are:
    // (2, 1) -> indices 0 and 2
    // (4, 1) -> indices 1 and 2
    // (4, 3) -> indices 1 and 3
    std::cout << "Inversions: " << inversions << "\n"; // Output: 3

    // To avoid copying the array if you don't need it afterward:
    // long long fast_invs = m1une::sequence::inversion_count(std::move(a));

    return 0;
}
```
