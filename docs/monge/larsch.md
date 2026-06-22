---
title: LARSCH
documentation_of: ../../monge/larsch.hpp
---

## Overview

LARSCH finds row minima of an implicit lower-triangular totally monotone matrix
online. For row `i`, only columns `0` through `i` are candidates.

Unlike ordinary SMAWK, rows are produced in increasing order. Matrix entries in
later columns may therefore depend on answers already computed for earlier
rows. This supports dynamic programs such as

$$
dp[i] = \min_{0 \le j < i}\left(dp[j] + cost(j,i)\right)
$$

in linear time when the resulting triangular transition matrix is totally
monotone.

The algorithm is due to Larmore and Schieber:
[On-line dynamic programming with applications to the prediction of RNA
secondary structure](https://doi.org/10.1016/0196-6774(91)90016-R).

## Sequential Matrix Interface

```cpp
template <class T>
class Larsch;
```

Construct it with the number of rows and a callback:

```cpp
m1une::monge::Larsch<long long> optimizer(
    row_count,
    [&](int row, int column) {
        return matrix_value(row, column);
    });
```

Then call `next_argmin()` exactly once for each row, in order.

| Method | Meaning |
| --- | --- |
| `size()` | Total row count. |
| `processed_rows()` | Number of answers already returned. |
| `finished()` | Whether every row was processed. |
| `next_argmin()` | Returns the leftmost minimum column of the next row. |

When evaluating entry `(row, column)`, `column <= row`. More importantly,
entries using column `j + 1` are not accessed before row `j` has been answered.
This is the online guarantee that permits callbacks to depend on earlier DP
values.

## Monge DAG Shortest Paths

The convenience function

```cpp
template <class Cost>
auto larsch_shortest_path(int vertex_count, Cost cost);
```

solves the complete forward DAG recurrence:

$$
dist[0] = 0,\qquad
dist[i] = \min_{0 \le j < i}(dist[j] + cost(j,i)).
$$

It returns `LarschShortestPathResult<T>`:

| Member | Meaning |
| --- | --- |
| `distance[i]` | Minimum distance from vertex `0` to `i`. |
| `parent[i]` | Leftmost predecessor attaining that distance, or `-1` for vertex `0`. |

## Requirement

The lower-triangular matrix queried by the algorithm must be totally monotone
for minima. For the shortest-path helper, the matrix

$$
A(i,j) = dist[j] + cost(j,i+1),\qquad 0 \le j \le i
$$

must have that property. A Monge edge-cost function is the standard sufficient
condition.

The implementation does not verify total monotonicity.

## Complexity

Both interfaces use $O(N)$ callback evaluations, $O(N)$ time, and $O(N)$ memory,
assuming each callback evaluation takes $O(1)$.

## Example

```cpp
#include "monge/larsch.hpp"
#include <vector>

int main() {
    std::vector<long long> position = {0, 2, 5, 9, 14};
    auto result = m1une::monge::larsch_shortest_path(
        int(position.size()),
        [&](int from, int to) {
            long long distance = position[to] - position[from];
            return distance * distance + 3;
        });
}
```
