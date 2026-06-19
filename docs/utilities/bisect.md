---
title: Bisect
documentation_of: ../../utilities/bisect.hpp
---

## Overview

Binary search helpers for monotone predicates. The integer functions use explicit `ok` and `ng` sentinels, so they work for both increasing and decreasing search directions.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `long long first_true(long long ng, long long ok, F pred)` | Given `pred(ng) == false` and `pred(ok) == true`, returns the boundary `ok`. | $O(\log |ok - ng|)$ |
| `long long last_true(long long ok, long long ng, F pred)` | Given `pred(ok) == true` and `pred(ng) == false`, returns the boundary `ok`. | $O(\log |ok - ng|)$ |
| `double real_first_true(double ng, double ok, F pred, int iterations = 80)` | Floating-point version of `first_true` with a fixed iteration count. | $O(\text{iterations})$ |

## Example

```cpp
#include "utilities/bisect.hpp"
#include <iostream>

int main() {
    long long n = 100;
    long long x = m1une::utilities::first_true(0, n + 1, [&](long long v) {
        return v * v >= n;
    });
    std::cout << x << "\n";
}
```
