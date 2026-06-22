---
title: Sliding Window Aggregation
documentation_of: ../../../ds/range_query/sliding_window_aggregation.hpp
---

## Overview

`SlidingWindowAggregation<Monoid>` maintains a queue and the monoid product of
all its elements. It is commonly called SWAG.

Elements are stored in two aggregate stacks. Each element moves from the back
stack to the front stack at most once, giving amortized constant-time queue
operations.

`Swag<Monoid>` is a shorter alias.

## Ordering

The product follows queue order:

$$
a_0 \mathbin{\mathrm{op}} a_1 \mathbin{\mathrm{op}} \cdots
\mathbin{\mathrm{op}} a_{n-1}.
$$

The monoid does not need to be commutative. This matters for affine-function
composition, matrices, and string concatenation.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `push(value)`, `push_back(value)` | Appends an element. | Amortized $O(1)$ |
| `pop()`, `pop_front()` | Removes the oldest element. | Amortized $O(1)$ |
| `front()` | Returns the oldest element. | Amortized $O(1)$ |
| `back()` | Returns the newest element. | $O(1)$ |
| `prod()`, `all_prod()` | Returns the ordered product, or the identity when empty. | $O(1)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether the queue is empty. | $O(1)$ |
| `clear()` | Removes every element. | $O(N)$ |
| `reserve(capacity)` | Reserves both internal stacks. | $O(N)$ |

`pop`, `pop_front`, `front`, and `back` require a nonempty queue.

## Example

This finds the minimum in every window of length three:

```cpp
#include "ds/range_query/sliding_window_aggregation.hpp"
#include "monoid/min.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {4, 2, 5, 1, 3};
    m1une::ds::Swag<m1une::monoid::Min<int>> window;

    for (int index = 0; index < int(values.size()); index++) {
        window.push(values[index]);
        if (window.size() > 3) window.pop();
        if (window.size() == 3) std::cout << window.prod() << "\n";
    }
}
```
