---
title: Long Long Convolution
documentation_of: ../../fps/convolution_ll.hpp
---

## Overview

`convolution_ll` computes an exact polynomial convolution whose inputs and
outputs use signed `long long` coefficients.

It performs convolution modulo three NTT-friendly primes and reconstructs each
signed coefficient with the Chinese remainder theorem. Unlike FFT followed by
rounding, the result has no floating-point error.

## Function

```cpp
std::vector<long long> convolution_ll(
    const std::vector<long long>& first,
    const std::vector<long long>& second);
```

The coefficient at index `k` is

$$
\sum_{i+j=k} \text{first}[i]\,\text{second}[j].
$$

If either input is empty, the result is empty. Otherwise, the result has
`first.size() + second.size() - 1` coefficients.

Every exact result coefficient must fit in signed `long long`. Individual
products and intermediate mathematical sums may exceed 64 bits. The required
NTT length must not exceed $2^{24}$.

| Function | Complexity |
| --- | --- |
| `convolution_ll(first, second)` | $O(L\log L)$ time and $O(L)$ memory. |

Here $L$ is the output length rounded up to a power of two. Small inputs use
the modular convolution implementation's quadratic cutoff.

## Example

```cpp
#include "fps/convolution_ll.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> first = {1, -2, 3};
    std::vector<long long> second = {4, 5};
    auto result = m1une::fps::convolution_ll(first, second);

    for (long long value : result) std::cout << value << " ";
    std::cout << "\n"; // 4 -3 2 15
}
```
