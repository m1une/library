---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/knuth_optimization.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace monge {\n\ntemplate <class T>\nstruct KnuthOptimizationResult {\n\
    \    std::vector<std::vector<T>> value;\n    std::vector<std::vector<int>> split;\n\
    \n    T optimum() const {\n        return value[0].back();\n    }\n};\n\ntemplate\
    \ <class IntervalCost>\nauto knuth_optimization(int element_count, IntervalCost\
    \ interval_cost)\n    -> KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP\n#define M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nstruct\
    \ KnuthOptimizationResult {\n    std::vector<std::vector<T>> value;\n    std::vector<std::vector<int>>\
    \ split;\n\n    T optimum() const {\n        return value[0].back();\n    }\n\
    };\n\ntemplate <class IntervalCost>\nauto knuth_optimization(int element_count,\
    \ IntervalCost interval_cost)\n    -> KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n#endif  // M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/knuth_optimization.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/knuth_optimization.hpp
layout: document
title: Knuth Optimization
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
