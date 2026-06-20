---
title: Z Algorithm
documentation_of: ../../string/z_algorithm.hpp
---

## Overview

`z_algorithm(sequence)` returns the longest common prefix length between the
whole sequence and every suffix. It is useful for exact pattern matching,
periodicity, borders, and comparing a fixed prefix against all positions.

The function is generic over indexable sequences such as `std::string` and
`std::vector<int>`.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> z_algorithm(const Sequence& sequence)` | Returns `z[i] = LCP(sequence, sequence[i..])`. For a non-empty sequence, `z[0]` equals its length. | $O(N)$ |

An empty sequence returns an empty vector.

## Example

```cpp
#include "string/z_algorithm.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "ababa";
    auto z = m1une::string::z_algorithm(text);

    for (int length : z) std::cout << length << " ";
    std::cout << "\n"; // 5 0 3 0 1
}
```
