---
title: Monge Checks
documentation_of: ../../monge/check.hpp
---

## Overview

This header checks the Monge or anti-Monge quadrangle inequality.

An `H` by `W` matrix `A` is Monge when

$$
A[i][j] + A[k][l] \le A[i][l] + A[k][j]
$$

for every `i < k` and `j < l`. It is enough to test adjacent rows and columns,
which gives an $O(HW)$ checker.

Anti-Monge reverses the inequality and is useful for row maxima.

## Interface

Implicit matrices:

```cpp
template <class Value>
bool is_monge(int row_count, int column_count, Value value);

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value);
```

Explicit rectangular matrices:

```cpp
template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix);

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix);
```

Empty matrices and matrices with fewer than two rows or columns satisfy both
properties vacuously.

The element type must support addition and comparison. Intermediate sums must
fit in the element type.

## Complexity

$O(HW)$ time and $O(1)$ additional memory.
