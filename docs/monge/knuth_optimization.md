---
title: Knuth Optimization
documentation_of: ../../monge/knuth_optimization.hpp
---

## Overview

Knuth optimization accelerates interval dynamic programming of the form

$$
dp[l][r]
= w(l,r) + \min_{l < k < r}\left(dp[l][k] + dp[k][r]\right).
$$

All intervals are half-open. Singleton and empty intervals have value zero.
The implementation returns every interval value and its optimal split.

The optimization originates in Knuth's
[Optimum binary search trees](https://doi.org/10.1007/BF00288690).

## Interface

```cpp
template <class IntervalCost>
auto knuth_optimization(
    int element_count,
    IntervalCost interval_cost
);
```

`interval_cost(left, right)` returns `w(left, right)` for `[left, right)`.

The result is `KnuthOptimizationResult<T>`:

| Member / Method | Meaning |
| --- | --- |
| `value[l][r]` | Optimal value for `[l, r)`. |
| `split[l][r]` | Leftmost optimal split `k`. |
| `optimum()` | Returns `value[0][element_count]`. |

For intervals of length at least two, the split is strictly inside the
interval.

## Requirement

The recurrence must satisfy Knuth's monotonicity:

$$
opt[l][r-1] \le opt[l][r] \le opt[l+1][r].
$$

A standard sufficient condition is that `w` obeys the quadrangle inequality
and interval monotonicity. For `a <= b <= c <= d`:

$$
w(a,c) + w(b,d) \le w(a,d) + w(b,c)
$$

and

$$
w(b,c) \le w(a,d).
$$

Nonnegative interval sums are a common example. The implementation assumes the
condition and does not verify it.

## Complexity

$O(N^2)$ time and $O(N^2)$ memory, improving the unrestricted cubic recurrence.

## Example

```cpp
#include "monge/knuth_optimization.hpp"
#include <vector>

int main() {
    std::vector<long long> weight = {2, 5, 1, 4};
    std::vector<long long> prefix(weight.size() + 1);
    for (int i = 0; i < int(weight.size()); i++) {
        prefix[i + 1] = prefix[i] + weight[i];
    }

    auto result = m1une::monge::knuth_optimization(
        int(weight.size()),
        [&](int left, int right) {
            return prefix[right] - prefix[left];
        });
}
```
