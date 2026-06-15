---
title: Chmin Chmax
documentation_of: ../../utilities/chmin_chmax.hpp
---

## Overview

Small update helpers for dynamic programming and relaxation code. Each function updates the first argument only when the new value improves it, and returns whether the update happened.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `bool chmin(T& a, const U& b)` | Sets `a = b` if `b < a`. | $O(1)$ |
| `bool chmax(T& a, const U& b)` | Sets `a = b` if `a < b`. | $O(1)$ |

## Example

```cpp
#include "utilities/chmin_chmax.hpp"

int main() {
    int best = 100;
    bool updated = m1une::utilities::chmin(best, 42);
}
```
