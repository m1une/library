---
title: Prefix Function and KMP
documentation_of: ../../string/prefix_function.hpp
---

## Overview

The prefix function stores, for every prefix ending at position `i`, the length
of its longest proper prefix that is also a suffix. It is the preprocessing
step for Knuth-Morris-Pratt pattern matching and is also useful for borders and
periods.

Both functions are generic over indexable sequences with comparable elements.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> prefix_function(const Sequence& sequence)` | Returns the prefix-function array. | $O(N)$ |
| `vector<int> kmp_search(const Text& text, const Pattern& pattern)` | Returns every occurrence's starting index, including overlapping matches. | $O(N + M)$ |

An empty pattern occurs at every position from `0` through `text.size()`.

## Example

```cpp
#include "string/prefix_function.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "ababa";
    std::string pattern = "aba";

    for (int position : m1une::string::kmp_search(text, pattern)) {
        std::cout << position << "\n"; // 0, then 2
    }
}
```
