---
title: Interval Set
documentation_of: ../../../ds/interval_set/interval_set.hpp
---

## Overview

`m1une::ds::IntervalSet` manages a set of disjoint half-open intervals `[l, r)`.

It is useful for the standard technique of maintaining intervals with `std::set`.
When a new interval is inserted, all intersecting or adjacent intervals are merged automatically.
When an interval is erased, existing intervals may be shortened or split.

Internally, intervals are stored as pairs `(l, r)` in increasing order of `l`.

## Template Parameters

* `T`: The coordinate type of interval endpoints.
  It must be comparable with `<`, and should support copy construction.

## Interval Convention

All intervals are half-open.

* `[l, r)` contains `l`
* `[l, r)` does not contain `r`
* Empty intervals, where `l == r`, are ignored by `insert` and `erase`

Adjacent intervals are merged. For example, inserting `[1, 5)` and then `[5, 8)` results in one interval `[1, 8)`.

## Construction

* `IntervalSet()`: creates an empty interval set.
* `IntervalSet(std::initializer_list<std::pair<T, T>> init)`: creates an interval set from the given intervals, merging intersecting or adjacent intervals.
* `IntervalSet(Iterator first, Iterator last)`: creates an interval set from a range of pairs.

## Methods

Let $N$ be the number of stored disjoint intervals, and let $K$ be the number of intervals removed or merged by the operation.

| Method                                           | Description                                                                                       | Complexity         |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------------- | ------------------ |
| `int size() const`                               | Returns the number of stored disjoint intervals.                                                  | $O(1)$             |
| `bool empty() const`                             | Returns whether no interval is stored.                                                            | $O(1)$             |
| `void clear()`                                   | Removes every interval.                                                                           | $O(N)$             |
| `bool contains(T x) const`                       | Returns whether point `x` is covered by some interval.                                            | $O(\log N)$        |
| `bool contains(T l, T r) const`                  | Returns whether the whole interval `[l, r)` is covered by one stored interval.                    | $O(\log N)$        |
| `std::pair<T, T> get(T x) const`                 | Returns the stored interval containing `x`. Requires that `x` is covered.                         | $O(\log N)$        |
| `const std::pair<T, T>* get_if(T x) const`       | Returns a pointer to the stored interval containing `x`, or `nullptr` if no such interval exists. | $O(\log N)$        |
| `bool intersects(T l, T r) const`                | Returns whether `[l, r)` intersects at least one stored interval.                                 | $O(\log N)$        |
| `void insert(T l, T r)`                          | Adds `[l, r)`, merging all intersecting or adjacent intervals.                                    | $O((K + 1)\log N)$ |
| `void erase(T l, T r)`                           | Removes `[l, r)` from the covered set. Existing intervals may be shortened or split.              | $O((K + 1)\log N)$ |
| `T mex(T x) const`                               | Returns the minimum value `y >= x` not covered by the interval set.                               | $O(\log N)$        |
| `T min_not_covered(T x) const`                   | Alias of `mex(x)`.                                                                                | $O(\log N)$        |
| `std::vector<std::pair<T, T>> to_vector() const` | Returns all stored intervals in increasing order.                                                 | $O(N)$             |
| `begin() const`, `end() const`                   | Returns const iterators over the stored intervals.                                                | $O(1)$             |

## Example

```cpp
#include "ds/interval_set/interval_set.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    m1une::ds::IntervalSet<long long> st;

    st.insert(1, 5);   // [1, 5)
    st.insert(5, 8);   // merged into [1, 8)
    st.erase(3, 6);    // [1, 3), [6, 8)

    assert(st.contains(2));
    assert(!st.contains(3));

    assert(st.contains(1, 3));
    assert(!st.contains(1, 4));

    assert(st.intersects(4, 7));
    assert(!st.intersects(3, 6));

    assert(st.mex(1) == 3);
    assert(st.mex(4) == 4);
    assert(st.mex(6) == 8);

    auto v = st.to_vector();
    std::vector<std::pair<long long, long long>> expected;
    expected.emplace_back(1, 3);
    expected.emplace_back(6, 8);
    assert(v == expected);

    for (auto [l, r] : st) {
        std::cout << "[" << l << ", " << r << ")\n";
    }

    return 0;
}
```

## Notes

This data structure represents the covered set itself.

To manage free intervals in a universe `[0, N)`, first insert `[0, N)`, and then erase occupied intervals.
