---
title: Divide-and-Conquer DP Optimization
documentation_of: ../../monge/divide_and_conquer_optimization.hpp
---

## Overview

Divide-and-conquer DP optimization computes

$$
dp[i] = \min_j A(i,j)
$$

when the leftmost minimizing index is nondecreasing with `i`. It evaluates only
a narrowed candidate interval for each recursive subproblem.

This header is the DP-facing wrapper around `monotone_row_argmin`: it returns
both optimum values and their candidate indices.

## Generic Interface

```cpp
template <class Value>
auto divide_and_conquer_dp(
    int state_count,
    int candidate_count,
    Value value
);
```

`value(state, candidate)` returns one transition value. The return type is
`DivideAndConquerDpResult<T>`:

| Member | Meaning |
| --- | --- |
| `value[i]` | Minimum value for state `i`. |
| `argmin[i]` | Leftmost minimizing candidate for state `i`. |

If there are no candidates, every `argmin` is `-1`; the corresponding values
are placeholders.

## Previous-Layer Helper

For the common recurrence

$$
dp_{\mathrm{next}}[i]
= \min_j \left(dp_{\mathrm{previous}}[j] + cost(j,i)\right),
$$

use:

```cpp
template <class T, class Cost>
auto divide_and_conquer_transition(
    const std::vector<T>& previous,
    int state_count,
    Cost cost
);
```

Candidates that are invalid for a state can be represented by a sufficiently
large value, provided arithmetic does not overflow and the remaining leftmost
argmins are still nondecreasing.

## Requirement

The leftmost minimizing candidate indices must be nondecreasing over states.
The implementation does not verify this condition.

Monge transition matrices satisfy the requirement, but the condition also
holds for some matrices that are not Monge.

## Complexity

For `H` states and `W` candidates, the algorithm uses
$O((H+W)\log H)$ transition evaluations and $O(H)$ additional memory.

## Example

```cpp
#include "monge/divide_and_conquer_optimization.hpp"
#include <vector>

int main() {
    std::vector<long long> previous = {0, 4, 7, 9};

    auto result = m1une::monge::divide_and_conquer_transition(
        previous, 6, [](int candidate, int state) {
            long long difference = state - candidate;
            return difference * difference;
        });
}
```
