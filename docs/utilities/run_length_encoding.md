---
title: Run Length Encoding
documentation_of: ../../utilities/run_length_encoding.hpp
---

## Overview

Compresses consecutive equal values into `(value, count)` pairs. It works with containers such as `std::vector` and `std::string`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `run_length_encoding(container)` | Returns `vector<pair<T, long long>>` for consecutive runs. | $O(N)$ |

## Example

```cpp
#include "utilities/run_length_encoding.hpp"
#include <string>

int main() {
    std::string s = "aaabbc";
    auto runs = m1une::utilities::run_length_encoding(s);
    // ('a', 3), ('b', 2), ('c', 1)
}
```
