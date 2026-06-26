---
title: Slope Trick
documentation_of: ../../optimization/slope_trick.hpp
---

## Overview

`SlopeTrick<T>` maintains a convex piecewise-linear function whose slopes
change by integer units. It supports adding hinge and absolute-value functions,
translations, sliding-window minima, evaluation, and function addition.

The structure stores the breakpoints in two heaps. Most updates take logarithmic
time without explicitly constructing the function over its whole domain.

Typical applications include scheduling, sequence adjustment, median costs,
and dynamic programs with convex piecewise-linear states.

## Complexity Notation

* `N` is the number of breakpoints stored in the current object.
* `M` is the number of breakpoints stored in another object passed to `merge`.

## Represented Function

A new object represents `f(x) = 0` for every `x`.

The template parameter must be a signed arithmetic type. `long long` is
recommended for integer problems. All values, breakpoint translations, and
intermediate sums must fit in `T`.

## Adding Functions

| Method | Effect |
| --- | --- |
| `add_constant(c)` | Adds the constant `c`. |
| `add_x_minus_a(a)` | Adds `max(x - a, 0)`. |
| `add_a_minus_x(a)` | Adds `max(a - x, 0)`. |
| `add_abs(a)` | Adds `abs(x - a)`. |

Each hinge insertion takes amortized $O(\log N)$ time, where `N` is the current
number of stored breakpoints. `add_abs` inserts two hinges.

## Minimum and Argmin

| Method | Meaning |
| --- | --- |
| `minimum()` | Minimum function value. |
| `argmin()` | Closed interval on which the minimum is attained. |
| `breakpoint_count()` | Number of stored unit-slope breakpoints. |

`argmin()` returns `SlopeTrickArgmin<T>` with optional `left` and `right`
endpoints. An empty left endpoint means the interval is unbounded below; an
empty right endpoint means it is unbounded above.

For the initial constant function, both endpoints are empty.

## Translation and Sliding Minimum

`shift(delta)` replaces the function by

$$
g(x) = f(x-\mathrm{delta}).
$$

`shift(left_delta, right_delta)` requires
`left_delta <= right_delta` and computes

$$
g(x) = \min_{x-b \le y \le x-a} f(y).
$$

This operation shifts the left and right breakpoint heaps independently and
takes $O(1)$ time.

The one-sided variants are:

| Method | Effect |
| --- | --- |
| `prefix_minimum()` / `clear_right()` | Replaces `f(x)` by `min` over `y <= x` of `f(y)`. |
| `suffix_minimum()` / `clear_left()` | Replaces `f(x)` by `min` over `y >= x` of `f(y)`. |

Clearing one side takes linear time in the number of discarded breakpoints.

## Evaluation and Merge

`evaluate(x)` returns `f(x)` in $O(N)$ time without changing the structure.
This is intended mainly for final answers and debugging; slope trick is useful
because updates and minimum queries avoid evaluating arbitrary points.

`merge(other)` adds the function represented by `other` to this function.
`other` is passed by value, so passing an rvalue avoids an extra copy. The
operation takes $O((N+M)\log(N+M))$ time in the worst case.

## Example

```cpp
#include "optimization/slope_trick.hpp"
#include <iostream>

int main() {
    m1une::optimization::SlopeTrick<long long> slope;
    slope.add_abs(3);
    slope.add_x_minus_a(0);
    slope.shift(-1, 2);

    std::cout << slope.minimum() << "\n";
    auto range = slope.argmin();
    if (range.left) std::cout << *range.left << "\n";
}
```
