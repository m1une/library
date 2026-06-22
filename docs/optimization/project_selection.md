---
title: Project Selection
documentation_of: ../../optimization/project_selection.hpp
---

## Overview

`ProjectSelection<T>` chooses a subset of binary projects that maximizes total
gain. Besides a gain or cost for each individual choice, it supports implication
penalties, hard implications, forced choices, and several common group rewards.

The problem is reduced to a minimum `s-t` cut and solved with Dinic's algorithm.
This is substantially faster and more predictable than a general integer
programming solver for objectives that fit the supported forms.

Project `i` is **selected** when `result.selected[i]` is true. Gains increase the
objective and penalties decrease it. A cost of `c` for selecting project `i`
can therefore be written as `add_gain(i, -c)`.

## Supported Objective Terms

All gains and penalties are additive.

| Call | Contribution to the objective |
| --- | --- |
| `add_gain(i, selected_gain)` | Adds `selected_gain` if `i` is selected. |
| `add_gain(i, selected_gain, unselected_gain)` | Adds the gain corresponding to the choice for `i`. |
| `add_penalty(i, j, penalty)` | Subtracts `penalty` exactly when `i` is selected and `j` is unselected. |
| `add_penalty_if_different(i, j, penalty)` | Subtracts `penalty` when exactly one of `i` and `j` is selected. |
| `add_gain_if_same(i, j, gain)` | Adds `gain` when `i` and `j` make the same choice. |
| `add_gain_if_all_selected(projects, gain)` | Adds `gain` when every listed project is selected. |
| `add_gain_if_all_unselected(projects, gain)` | Adds `gain` when every listed project is unselected. |

Every `penalty` argument must be non-negative. The `gain` passed to
`add_gain_if_same` and the two group methods must also be non-negative. The
group methods treat an empty list as vacuously satisfying the condition, so
their gain is always added.

`add_penalty(i, j, penalty)` is the low-level finite implication primitive. It
is useful for statements such as “choosing `i` without choosing `j` loses 20.”
It does not forbid that combination; use `add_hard_implication` when it must be
impossible.

Not every Boolean objective can be represented by one minimum cut. In
particular, a positive reward for “at least one is selected” or a penalty for
“both are selected” is not generally supported without reformulating the
problem. The methods above are exactly the forms provided by this interface.

## Reduction to Minimum Cut

The source side of the cut represents selected projects, and the sink side
represents unselected projects.

- A directed edge from `i` to `j` crosses the cut exactly when `i` is selected
  and `j` is unselected, so its capacity is the corresponding penalty.
- A unary gain is converted into a constant offset and one edge incident to
  the source or sink. Cutting that edge loses the difference between the two
  possible gains.
- Group rewards of three or more entries use one auxiliary vertex and hard
  implication edges. Smaller groups have a direct encoding.

Thus every cut has cost equal to a constant minus the modeled gain. A minimum
cut therefore gives a maximum-gain selection. If several selections have the
same maximum gain, `solve()` may return any one of them.

## Hard Constraints

| Call | Constraint |
| --- | --- |
| `add_hard_implication(i, j)` | If `i` is selected, `j` must also be selected. |
| `force_selected(i)` | Project `i` must be selected. |
| `force_unselected(i)` | Project `i` must be unselected. |

Hard constraints use a capacity larger than the sum of every finite capacity.
This value is computed only inside `solve()`, so constraints remain truly hard
even if more gains or penalties are added later.

Contradictory hard constraints make the result infeasible. Check
`result.is_feasible()` before reading `max_gain` or interpreting `selected`.

## Result

`ProjectSelectionResult<T>` contains:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether all hard constraints can be satisfied. |
| `max_gain` | `T` | Maximum total gain. It is meaningful only when feasible. |
| `selected` | `std::vector<bool>` | One optimal choice for the original projects. Auxiliary vertices are not included. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |

Calling `solve()` does not mutate the model, so it may be called repeatedly.

## Methods and Complexity

Let `N` be the number of original projects plus internally created auxiliary
vertices, and let `M` be the number of generated flow edges.

| Method | Complexity |
| --- | --- |
| Constructor, `size` | $O(1)$ |
| `add_gain`, `add_penalty`, `add_penalty_if_different`, `add_gain_if_same`, hard single-project methods | Amortized $O(1)$ |
| `add_gain_if_all_selected`, `add_gain_if_all_unselected` | $O(K)$ for a group of size `K` |
| `solve` | General-case $O(N^2 M)$ time and $O(N + M)$ memory |

A group-reward call creates one auxiliary vertex when its group has at least
three entries. `solve()` uses the repository's `MaxFlow<T>` implementation.

## Numeric Requirements

`T` must be a signed integral type; `long long` is recommended. Every
intermediate gain difference, the sum of finite capacities, the hard capacity,
and the final answer must fit in `T`. These range requirements are checked with
assertions where practical.

## Example

Suppose each selected project earns its listed gain, project `0` requires
project `1`, and completing projects `1` and `2` together earns a bonus.

```cpp
#include "optimization/project_selection.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::optimization::ProjectSelection<long long> solver(3);
    solver.add_gain(0, 10);
    solver.add_gain(1, -3);  // Selecting project 1 costs 3.
    solver.add_gain(2, 4);
    solver.add_hard_implication(0, 1);
    solver.add_gain_if_all_selected(std::vector<int>{1, 2}, 5);

    auto result = solver.solve();
    if (!result.is_feasible()) return 0;

    std::cout << result.max_gain << "\n";  // 16
    for (int i = 0; i < solver.size(); i++) {
        if (result.selected[i]) std::cout << i << "\n";
    }
}
```
