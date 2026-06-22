---
title: Convex Hull Trick
documentation_of: ../../optimization/convex_hull_trick.hpp
---

## Overview

`ConvexHullTrick<T, Objective>` maintains linear functions

$$
f(x)=ax+b
$$

and answers minimum or maximum queries. Slopes must be inserted in
nondecreasing order, but query coordinates may arrive in any order.

The structure removes redundant lines as they are inserted and binary-searches
the remaining hull.

## Types

```cpp
enum class LineOptimization {
    Minimize,
    Maximize,
};
```

The convenient aliases are:

* `MinConvexHullTrick<T>`
* `MaxConvexHullTrick<T>`

`T` must be a signed integral type. Coefficients and query coordinates use `T`.
Evaluation and hull cross products use `line_wide_type<T>`, which is
`__int128_t`.

All intermediate products used to remove lines must fit the widened type.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `add_line(slope, intercept)` | Adds a line. Slopes must be nondecreasing. | Amortized $O(1)$ |
| `query(x)` | Returns the optimum at `x`; requires a nonempty hull. | $O(\log N)$ |
| `try_query(x)` | Returns the optimum, or `nullopt` when empty. | $O(\log N)$ |
| `lines()` | Returns the remaining hull lines. | $O(1)$ |
| `size()`, `empty()` | Return hull size and emptiness. | $O(1)$ |
| `reserve(capacity)` | Reserves line storage. | $O(N)$ |
| `clear()` | Removes every line. | $O(N)$ |

For equal slopes, only the better intercept is retained.

## Example

```cpp
#include "optimization/convex_hull_trick.hpp"

#include <iostream>

int main() {
    m1une::optimization::MinConvexHullTrick<long long> cht;
    cht.add_line(-2, 5);
    cht.add_line(0, 1);
    cht.add_line(3, -4);

    long long answer = static_cast<long long>(cht.query(2));
    std::cout << answer << "\n";
}
```
