---
title: Cow Game (Difference Constraints)
documentation_of: ../../graph/cow_game.hpp
---

## Overview

`CowGame<T>` solves a system of difference constraints. Each variable is a
number `x[i]`, and the primitive constraint is

$$
x[\mathrm{to}] - x[\mathrm{from}] \le \mathrm{upper\_bound}.
$$

This family is sometimes called a “cow game” in competitive-programming
slang, after several classic cow-placement problems with distance constraints.
`DifferenceConstraints<T>` is provided as a descriptive alias of
`CowGame<T>`.

The solver can:

- determine whether all constraints are simultaneously feasible;
- return one feasible assignment;
- find the tightest upper bounds relative to one variable;
- find the tightest lower and upper bounds on one difference;
- report when either side of a difference is unbounded.

Internally, every constraint becomes a directed edge and the implementation
uses Bellman-Ford relaxation. A negative cycle means that the system is
infeasible.

## Adding Constraints

All variable indices are zero-based.

| Method | Added condition |
| --- | --- |
| `add_upper_bound(from, to, upper)` | `x[to] - x[from] <= upper` |
| `add_constraint(from, to, upper)` | Alias of `add_upper_bound` |
| `add_lower_bound(from, to, lower)` | `lower <= x[to] - x[from]` |
| `add_bounds(from, to, lower, upper)` | `lower <= x[to] - x[from] <= upper` |
| `add_equality(from, to, difference)` | `x[to] - x[from] == difference` |

`add_upper_bound` and `add_constraint` return the id of the generated
constraint. A lower bound is represented by reversing the edge and negating
the bound. Bounds and equalities therefore generate two primitive constraints.

## Feasible Assignment

`solve()` returns `CowGameSolution<T>`:

| Member / Method | Meaning |
| --- | --- |
| `feasible` | Whether the whole system is feasible. |
| `value` | One assignment satisfying every constraint when feasible. |
| `is_feasible()` | Returns `feasible`. |

The system contains only differences, so adding the same constant to every
value preserves feasibility. The assignment returned by `solve()` is one
convenient representative, not a uniquely normalized solution.

`is_feasible()` checks feasibility without returning the assignment.
The feasibility result is cached until another constraint is added, which
avoids repeating the global negative-cycle check across bound queries.

## Tight Difference Bounds

`tightest_upper_bounds(source)` returns `CowGameUpperBounds<T>`. When the
system is feasible, `upper_bound[v]` is the smallest implied upper bound on
`x[v] - x[source]`. It equals the shortest-path distance from `source` to `v`.

If no directed constraint path exists, the difference is unbounded above:
`bounded(v)` is false and `upper_bound[v]` equals the result's `inf` sentinel.

`difference_bounds(from, to)` returns `CowGameDifferenceBounds<T>`:

| Member / Method | Meaning |
| --- | --- |
| `feasible` | Whether the whole system is feasible. |
| `lower_bound` | Tightest lower bound on `x[to] - x[from]`, or empty if unbounded below. |
| `upper_bound` | Tightest upper bound on `x[to] - x[from]`, or empty if unbounded above. |
| `bounded_below()` | Whether `lower_bound` exists. |
| `bounded_above()` | Whether `upper_bound` exists. |

Check feasibility before interpreting bounds. In an infeasible system, neither
bound is meaningful.

## Constraint Inspection

`CowGameConstraint<T>` stores `from`, `to`, and `upper_bound`.

| Method | Meaning |
| --- | --- |
| `size()` | Number of variables. |
| `constraint_count()` | Number of primitive upper-bound constraints. |
| `get_constraint(id)` | Returns one primitive constraint. |
| `constraints()` | Returns all primitive constraints. |

## Complexity

Let `N` be the number of variables and `M` the number of primitive constraints.

| Operation | Time | Memory |
| --- | --- | --- |
| Add or inspect one constraint | Amortized $O(1)$ | $O(1)$ additional |
| First `solve` or `is_feasible` after adding a constraint | $O(NM)$ | $O(N + M)$ |
| Later `solve`, `is_feasible` before another addition | $O(N)$ for `solve`, $O(1)$ for `is_feasible` | $O(N)$ returned by `solve` |
| `tightest_upper_bounds` | $O(NM)$ | $O(N + M)$ |
| `difference_bounds` | $O(NM)$ | $O(N + M)$ |

All relaxations stop early when an entire pass makes no update.

## Numeric Requirements

`T` must be a signed arithmetic type. `long long` is recommended. Negated
lower bounds, finite path sums, and answers must fit in `T`. For bound queries,
finite path sums must also stay strictly inside the sentinel range based on
`numeric_limits<T>::max() / 4`.

## Example

```cpp
#include "graph/cow_game.hpp"
#include <iostream>

int main() {
    m1une::graph::CowGame<long long> game(3);

    // 2 <= x[1] - x[0] <= 5
    game.add_bounds(0, 1, 2, 5);

    // x[2] - x[1] == 4
    game.add_equality(1, 2, 4);

    auto bounds = game.difference_bounds(0, 2);
    if (!bounds.is_feasible()) {
        std::cout << "infeasible\n";
        return 0;
    }

    std::cout << *bounds.lower_bound << " " << *bounds.upper_bound << "\n";
    // 6 9
}
```
