---
title: Mo's Algorithm
documentation_of: ../../../ds/range_query/mo.hpp
---

## Overview

`Mo` reorders static range queries so a maintained half-open interval changes
only a small number of positions between consecutive queries.

Use it when:

* every query is known before processing begins,
* the array does not change,
* one element can be inserted or erased from the maintained answer efficiently.

## Basic API

```cpp
m1une::ds::Mo mo(n);
int id = mo.add_query(left, right);
mo.run(add, remove, answer);
```

Queries use zero-based half-open intervals `[left, right)`.
`add_query` returns an insertion-order query ID. During `run`,
`answer(query_id)` is called when the maintained state represents exactly that
query's range.

For statistics whose update is the same on both sides, use:

```cpp
mo.run(add, remove, answer);
```

Both `add(index)` and `remove(index)` receive an array index.

## Directional Updates

Some statistics depend on which endpoint moves. Inversion counting is a common
example: adding an element to the left counts smaller existing elements, while
adding one to the right counts larger existing elements.

Use the full overload:

```cpp
mo.run(
    add_left,
    add_right,
    remove_left,
    remove_right,
    answer
);
```

Every callback receives the index being inserted or erased.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Mo(int n)` | Creates a query collection for an array of length `n`. | $O(1)$ |
| `add_query(l, r)` | Adds `[l, r)` and returns its query ID. | Amortized $O(1)$ |
| `query_count()` | Returns the number of queries. | $O(1)$ |
| `queries()` | Returns all queries in insertion order. | $O(1)$ |
| `order(block_size)` | Returns query IDs in processing order. | $O(Q\log Q)$ |
| `run(...)` | Processes all queries. | See below |
| `reserve(q)` | Reserves storage for `q` queries. | $O(Q)$ |
| `clear()` | Removes all queries while retaining array length. | $O(Q)$ |

`order` and `run` choose a block size automatically when `block_size <= 0`.
Passing a positive value allows problem-specific tuning. Right endpoints are
sorted in alternating directions between adjacent left blocks.

With $O(F)$ insertion and deletion callbacks, the usual complexity is
$O((N+Q)\sqrt{Q}\,F + Q\log Q)$ using the automatically selected block size.
The exact number of endpoint movements depends on the query distribution.

## Example

This computes the number of distinct values in every query:

```cpp
#include "ds/range_query/mo.hpp"

#include <vector>

int main() {
    std::vector<int> values = {1, 2, 1, 3};
    m1une::ds::Mo mo(int(values.size()));
    mo.add_query(0, 3);
    mo.add_query(1, 4);

    std::vector<int> frequency(4);
    std::vector<int> result(mo.query_count());
    int distinct = 0;

    mo.run(
        [&](int index) {
            if (frequency[values[index]]++ == 0) distinct++;
        },
        [&](int index) {
            if (--frequency[values[index]] == 0) distinct--;
        },
        [&](int query_id) {
            result[query_id] = distinct;
        }
    );
}
```
