---
title: SMAWK
documentation_of: ../../monge/smawk.hpp
---

## Overview

SMAWK finds an optimum in every row of an implicit totally monotone matrix.
The matrix is supplied as a callback, so the full rectangular matrix never
needs to be stored or evaluated.

The algorithm was introduced by Aggarwal, Klawe, Moran, Shor, and Wilber in
[Geometric applications of a matrix-searching algorithm](https://doi.org/10.1007/BF01840359).

For minima, total monotonicity means that the leftmost minimizing columns stay
nondecreasing after selecting any subset of rows and columns. Every Monge
matrix is totally monotone, so SMAWK is the standard linear-time row-minimum
primitive for Monge optimization.

All names are in `m1une::monge`.

## Interface

```cpp
template <class Value>
std::vector<int> smawk_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> smawk_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns the matrix entry at that position. The result
contains the selected column for every row. Ties choose the leftmost optimum.

Explicit rectangular matrices have convenience overloads:

```cpp
template <class T>
std::vector<int> smawk_row_argmin(
    const std::vector<std::vector<T>>& matrix
);

template <class T>
std::vector<int> smawk_row_argmax(
    const std::vector<std::vector<T>>& matrix
);
```

The generic form accepts a strict comparator:

```cpp
template <class Value, class Compare = std::less<>>
std::vector<int> smawk_row_optima(
    int row_count,
    int column_count,
    Value value,
    Compare compare = Compare()
);
```

`compare(a, b)` must return whether `a` is strictly better than `b`.

If there are no columns, every answer is `-1`. If there are no rows, the result
is empty.

## Requirements

For `smawk_row_argmin`, the implicit matrix must be totally monotone for
leftmost minima. For `smawk_row_argmax`, it must be totally monotone under the
reversed comparison. The implementation does not verify this precondition.

The callback may return values by value or by reference. Values only need to
support the selected comparison.

## Complexity

SMAWK uses $O(H + W)$ callback evaluations and $O(H + W)$ additional memory for
an `H` by `W` matrix. This assumes each callback evaluation and comparison take
$O(1)$ time.

## Example

```cpp
#include "monge/smawk.hpp"
#include <iostream>

int main() {
    int rows = 5;
    int columns = 8;
    auto value = [](int row, int column) {
        long long difference = row * 2LL - column;
        return difference * difference;
    };

    auto argmin = m1une::monge::smawk_row_argmin(rows, columns, value);
    for (int column : argmin) std::cout << column << "\n";
}
```
