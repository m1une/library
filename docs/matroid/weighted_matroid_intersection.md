---
title: Weighted Matroid Intersection
documentation_of: ../../matroid/weighted_matroid_intersection.hpp
---

## Overview

Weighted matroid intersection finds a maximum-cardinality subset that is
independent in two matroids, then optimizes its total element weight.

This header provides both objectives:

- `weighted_matroid_intersection_max` maximizes total weight;
- `weighted_matroid_intersection_min` minimizes total weight.

`weighted_matroid_intersection` is an alias for the maximizing version.

The `_each` variants report the optimal solution for every feasible
cardinality without retaining all selected sets. If the maximum
common-independent-set size is $R$, the callback runs for
$k=0,1,\ldots,R$.

Cardinality is always the primary objective. Consequently, a negative-weight
element may still be selected when it is needed to reach maximum cardinality.
This differs from asking for the maximum-weight common independent set over all
cardinalities, where the empty set could win.

## Oracle Interface

The ground set is `{0, 1, ..., ground_size - 1}`. Both matroids are supplied as
independence oracles:

```cpp
bool oracle(const std::vector<int>& subset);
```

The standard matroids in this directory provide this interface directly. A
custom oracle must ignore element order and consistently describe a fixed
matroid. The received vector contains distinct valid indices and is only valid
during the call.

## Result

```cpp
template <class Weight>
struct WeightedMatroidIntersectionResult {
    Weight total_weight;
    std::vector<int> elements;

    int size() const;
    bool empty() const;
};
```

`elements` is the optimal maximum-cardinality set in increasing order, and
`total_weight` is its weight. Ordinary min/max calls retain only this final
solution.

| Result operation | Description | Complexity |
| --- | --- | --- |
| `result.size()`, `result.empty()` | Queries the final solution. | $O(1)$ |

## Functions

```cpp
template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_max(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2);

template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_min(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2);

template <class Weight, class IndependenceOracle1,
          class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_max_each(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2,
    OnSolution on_solution);

template <class Weight, class IndependenceOracle1,
          class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_min_each(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2,
    OnSolution on_solution);
```

The callback signature is:

```cpp
void on_solution(
    int cardinality,
    const Weight& total_weight,
    const std::vector<int>& elements);
```

It receives the optimum containing exactly `cardinality` elements. The
`elements` reference is valid only during the callback. Store a copy only when
the actual set is needed later; storing just `total_weight` for every
cardinality uses $O(R)$ memory.

The `weight` vector must contain exactly `ground_size` values. `Weight` should
be a signed, exactly ordered additive type supporting `0`, addition,
subtraction, and `<`; `long long` is the usual choice. Intermediate path costs
and the final total must fit in `Weight`.

| Function | Objective after maximizing cardinality | Complexity |
| --- | --- | --- |
| `weighted_matroid_intersection_max` | Maximum total weight. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_min` | Minimum total weight. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection` | Alias for the maximum version. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_max_each` | Maximum weight for every cardinality through a callback. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_min_each` | Minimum weight for every cardinality through a callback. | $O(NR^2(C_1+C_2+\log N))$ |

Here $N$ is the ground-set size, $R$ is the maximum common-independent-set
size, and $C_i$ is the cost of oracle `i`. Additional memory is $O(NR)$ for the
exchange graph. The ordinary functions and streaming variants do not retain
the intermediate sets.

## Algorithm

Starting with the empty set, the algorithm maintains a minimum- or
maximum-weight common independent set of the current cardinality. It builds the
matroid exchange graph and finds a best augmenting path with Dijkstra's
algorithm.

Potentials keep every reduced edge length nonnegative, even though the original
exchange-edge lengths may be negative. After an augmentation, the potentials
of the toggled elements are adjusted for their new inside/outside roles. This
lets the next iteration use Dijkstra again although its exchange graph has
changed.

After Dijkstra updates the potentials, a breadth-first search in the graph of
zero reduced-length edges chooses the fewest-edge path among all best-weight
augmenting paths. This tie rule is required by the weighted augmentation
theorem. Each successful augmentation increases the cardinality by one.

## Example

```cpp
#include "matroid/partition_matroid.hpp"
#include "matroid/weighted_matroid_intersection.hpp"
#include <iostream>
#include <vector>

int main() {
    // Choose edges of a bipartite matching: one per left and right endpoint.
    std::vector<int> left = {0, 0, 1};
    std::vector<int> right = {0, 1, 0};
    std::vector<long long> weight = {100, 60, 70};

    m1une::matroid::PartitionMatroid by_left(left);
    m1une::matroid::PartitionMatroid by_right(right);
    std::vector<long long> best_weight;
    auto result = m1une::matroid::weighted_matroid_intersection_max_each(
        3, weight, by_left, by_right,
        [&](int cardinality, const long long& total,
            const std::vector<int>&) {
            // Callbacks arrive in cardinality order, starting with zero.
            best_weight.push_back(total);
        });

    // Elements 1 and 2 form the only size-two solution, with weight 130.
    std::cout << result.size() << " " << result.total_weight << "\n";

    // Best weights for cardinalities zero, one, and two: 0, 100, 130.
    for (long long value : best_weight) std::cout << value << " ";
    std::cout << "\n";
}
```
