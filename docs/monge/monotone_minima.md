---
title: Monotone Minima
documentation_of: ../../monge/monotone_minima.hpp
---

## Overview

The divide-and-conquer monotone-minima algorithm finds one optimum in every
row when the leftmost optimal columns are known to be nondecreasing.

Its precondition is weaker and sometimes easier to establish than total
monotonicity, although its asymptotic complexity is slightly worse than SMAWK.
It is commonly used for divide-and-conquer DP optimization.

## Interface

```cpp
template <class Value>
std::vector<int> monotone_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> monotone_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns one implicit matrix entry. The result stores the
optimal column for each row, choosing the leftmost optimum on ties.

Both functions also have convenience overloads accepting a rectangular
`std::vector<std::vector<T>>`.

`monotone_row_optima` is the generic overload accepting a strict comparator.

If there are no columns, every answer is `-1`.

## Requirements

The leftmost optimal columns under the chosen comparison must form a
nondecreasing sequence. The implementation does not verify this condition.

Unlike SMAWK, this function does not require every submatrix to preserve
monotonicity.

## Complexity

For an `H` by `W` implicit matrix, the algorithm uses
$O((H + W)\log H)$ callback evaluations in the general case and $O(H)$
additional memory including the result and recursion stack.

## Example

```cpp
#include "monge/monotone_minima.hpp"
#include <vector>

int main() {
    std::vector<long long> previous = {0, 3, 4, 8, 10};
    auto transition = [&](int row, int column) {
        long long distance = row - column;
        return previous[column] + distance * distance;
    };

    auto opt = m1une::monge::monotone_row_argmin(5, 5, transition);
}
```
