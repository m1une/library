---
title: Y Combinator
documentation_of: ../../utilities/y_combinator.hpp
---

## Overview

Helper for writing recursive lambdas without declaring a separate function object.

## Functions

| Function | Description |
| --- | --- |
| `y_combinator(lambda)` | Wraps a lambda so it can call itself through its first argument. |

## Example

```cpp
#include "utilities/y_combinator.hpp"

int main() {
    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long {
        if (n == 0) return 1;
        return n * self(n - 1);
    });

    long long x = fact(10);
}
```
