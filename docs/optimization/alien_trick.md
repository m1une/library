---
title: Alien Trick
documentation_of: ../../optimization/alien_trick.hpp
---

## Overview

The Alien Trick, also called Lagrangian relaxation or WQS binary search,
converts an optimization problem with an exact-count constraint into a sequence
of unconstrained penalized problems.

This header provides:

* `alien_trick_minimize(lower, upper, target_count, oracle)`
* `alien_trick_maximize(lower, upper, target_count, oracle)`

Both functions return the optimum among solutions whose count is exactly
`target_count`.

## Oracle Contract

For minimization, `oracle(penalty)` must return a pair
`{penalized_value, count}` minimizing

$$
\mathrm{original\ value} + \mathrm{penalty} \cdot \mathrm{count}.
$$

For maximization, it must return a pair maximizing

$$
\mathrm{original\ value} - \mathrm{penalty} \cdot \mathrm{count}.
$$

If several solutions have the same penalized value, the oracle must choose the
one with the larger count. Consequently, the returned count is non-increasing
as the penalty increases.

The exact-count optimum must be discrete convex for minimization or discrete
concave for maximization. Without this condition, the relaxed problem can skip
the requested count and the Alien Trick cannot recover its optimum.

## Penalty Bounds

`lower` and `upper` are inclusive integral penalty bounds. They must satisfy:

* `lower <= upper`
* `oracle(lower).second >= target_count`
* `oracle(upper).second <= target_count`

All values, penalties, products, and intermediate oracle calculations must fit
their respective types.

## Complexity

If one oracle call takes $O(D)$ time, the helper takes
$O(D \log(\mathrm{upper}-\mathrm{lower}+1))$ time and $O(1)$ additional space,
excluding the oracle.

## Example

```cpp
#include "optimization/alien_trick.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<long long> exact = {25, 12, 5, 2, 3, 8};

    auto oracle = [&exact](long long penalty) {
        std::pair<long long, int> best;
        best.first = exact[0];
        best.second = 0;
        for (int count = 1; count < int(exact.size()); count++) {
            long long value = exact[count] + penalty * count;
            if (value < best.first || (value == best.first && best.second < count)) {
                best.first = value;
                best.second = count;
            }
        }
        return best;
    };

    std::cout << m1une::optimization::alien_trick_minimize(
        -100LL,
        100LL,
        3,
        oracle
    ) << "\n";
}
```
