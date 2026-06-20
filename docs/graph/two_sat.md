---
title: Two-Satisfiability
documentation_of: ../../graph/two_sat.hpp
---

## Overview

`m1une::graph::TwoSat` solves boolean formulas whose clauses contain at most
two literals. It converts every clause to implications and checks strongly
connected components.

The implementation stores implications in a flat edge list and builds compact
CSR graphs when solving. Both SCC passes are iterative, so large formulas do
not depend on the process recursion limit.

## Literal Convention

The expression:

```cpp
add_clause(i, f, j, g)
```

adds the clause:

```text
(variable i == f) OR (variable j == g)
```

For example, `add_clause(0, true, 1, false)` means
$x_0 \lor \lnot x_1$.

## Construction

* `TwoSat()`: creates a formula with zero variables.
* `TwoSat(int n)`: creates a formula with variables `0` through `n - 1`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of variables. | $O(1)$ |
| `bool empty()` | Returns whether there are no variables. | $O(1)$ |
| `void reserve(size_t clauses)` | Reserves implication-edge storage for approximately `clauses` ordinary clauses. | $O(M)$ |
| `void add_clause(i, f, j, g)` | Adds `(x_i == f) OR (x_j == g)`. | Amortized $O(1)$ |
| `void add_implication(i, f, j, g)` | Adds `(x_i == f) => (x_j == g)`. | Amortized $O(1)$ |
| `void set_value(i, value)` | Forces `x_i` to equal `value`. | Amortized $O(1)$ |
| `void add_equal(i, j)` | Forces `x_i == x_j`. | Amortized $O(1)$ |
| `void add_not_equal(i, j)` | Forces `x_i != x_j`. | Amortized $O(1)$ |
| `bool satisfiable()` | Solves the current formula and returns whether an assignment exists. | $O(N + M)$ |
| `const vector<bool>& answer()` | Returns one satisfying assignment. Call only after a successful `satisfiable()`. | $O(1)$ |
| `bool value(int i)` | Returns the assigned value of variable `i`. | $O(1)$ |

Here $M$ is the number of implication edges, which is twice the number of
ordinary clauses. Calling `satisfiable()` again without adding constraints
returns the cached result in $O(1)$. Adding any constraint invalidates the
cached result.

`add_implication(a, f, b, g)` also adds its contrapositive, as required by its
equivalent 2-CNF clause.

## Example

```cpp
#include "graph/two_sat.hpp"

#include <iostream>

int main() {
    m1une::graph::TwoSat sat(3);

    sat.add_clause(0, true, 1, false); // x0 OR NOT x1
    sat.add_implication(1, true, 2, true);
    sat.set_value(0, true);

    if (!sat.satisfiable()) {
        std::cout << "impossible\n";
        return 0;
    }

    for (bool value : sat.answer()) {
        std::cout << value << "\n";
    }
}
```
