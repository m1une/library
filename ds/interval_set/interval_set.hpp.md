---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/interval_set/interval_set.test.cpp
    title: verify/ds/interval_set/interval_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/interval_set/interval_set.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <initializer_list>\n#include <iterator>\n#include\
    \ <memory>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct IntervalSet {\n    using\
    \ value_type = T;\n    using interval_type = std::pair<T, T>;\n\nprivate:\n  \
    \  std::set<interval_type> intervals;\n\n    typename std::set<interval_type>::iterator\
    \ first_intersecting_or_touching(T l) {\n        auto it = intervals.lower_bound(interval_type(l,\
    \ l));\n        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator first_intersecting_or_touching(T\
    \ l) const {\n        auto it = intervals.lower_bound(interval_type(l, l));\n\
    \        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator find_interval(T\
    \ x) const {\n        auto it = intervals.lower_bound(interval_type(x, x));\n\
    \        if (it != intervals.end() && it->first == x) return it;\n        if (it\
    \ == intervals.begin()) return intervals.end();\n        --it;\n        if (it->first\
    \ <= x && x < it->second) return it;\n        return intervals.end();\n    }\n\
    \npublic:\n    IntervalSet() = default;\n\n    IntervalSet(std::initializer_list<interval_type>\
    \ init) {\n        for (auto [l, r] : init) insert(l, r);\n    }\n\n    template\
    \ <class Iterator>\n    IntervalSet(Iterator first, Iterator last) {\n       \
    \ while (first != last) {\n            insert(first->first, first->second);\n\
    \            ++first;\n        }\n    }\n\n    int size() const { return int(intervals.size());\
    \ }\n\n    bool empty() const { return intervals.empty(); }\n\n    void clear()\
    \ { intervals.clear(); }\n\n    bool contains(T x) const { return find_interval(x)\
    \ != intervals.end(); }\n\n    bool contains(T l, T r) const {\n        assert(l\
    \ <= r);\n        if (l == r) return true;\n        auto it = find_interval(l);\n\
    \        return it != intervals.end() && r <= it->second;\n    }\n\n    interval_type\
    \ get(T x) const {\n        auto it = find_interval(x);\n        assert(it !=\
    \ intervals.end());\n        return *it;\n    }\n\n    const interval_type* get_if(T\
    \ x) const {\n        auto it = find_interval(x);\n        return it == intervals.end()\
    \ ? nullptr : std::addressof(*it);\n    }\n\n    bool intersects(T l, T r) const\
    \ {\n        assert(l <= r);\n        if (l == r) return false;\n\n        auto\
    \ it = intervals.lower_bound(interval_type(l, l));\n\n        if (it != intervals.begin())\
    \ {\n            auto prev = std::prev(it);\n            if (l < prev->second)\
    \ return true;\n        }\n\n        return it != intervals.end() && it->first\
    \ < r;\n    }\n\n    void insert(T l, T r) {\n        assert(l <= r);\n      \
    \  if (l == r) return;\n\n        auto it = first_intersecting_or_touching(l);\n\
    \n        while (it != intervals.end() && it->first <= r) {\n            l = std::min(l,\
    \ it->first);\n            r = std::max(r, it->second);\n            it = intervals.erase(it);\n\
    \        }\n\n        intervals.emplace(l, r);\n    }\n\n    void erase(T l, T\
    \ r) {\n        assert(l <= r);\n        if (l == r) return;\n\n        auto it\
    \ = first_intersecting_or_touching(l);\n\n        while (it != intervals.end()\
    \ && it->first < r) {\n            const T a = it->first;\n            const T\
    \ b = it->second;\n\n            if (b <= l) {\n                ++it;\n      \
    \          continue;\n            }\n\n            it = intervals.erase(it);\n\
    \n            if (a < l) intervals.emplace(a, l);\n            if (r < b) {\n\
    \                intervals.emplace(r, b);\n                break;\n          \
    \  }\n        }\n    }\n\n    T mex(T x) const {\n        auto it = find_interval(x);\n\
    \        return it == intervals.end() ? x : it->second;\n    }\n\n    T min_not_covered(T\
    \ x) const { return mex(x); }\n\n    std::vector<interval_type> to_vector() const\
    \ {\n        return std::vector<interval_type>(intervals.begin(), intervals.end());\n\
    \    }\n\n    auto begin() const { return intervals.begin(); }\n\n    auto end()\
    \ const { return intervals.end(); }\n};\n\n} // namespace ds\n} // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_INTERVAL_SET_HPP\n#define M1UNE_INTERVAL_SET_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <initializer_list>\n#include <iterator>\n\
    #include <memory>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct IntervalSet {\n    using\
    \ value_type = T;\n    using interval_type = std::pair<T, T>;\n\nprivate:\n  \
    \  std::set<interval_type> intervals;\n\n    typename std::set<interval_type>::iterator\
    \ first_intersecting_or_touching(T l) {\n        auto it = intervals.lower_bound(interval_type(l,\
    \ l));\n        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator first_intersecting_or_touching(T\
    \ l) const {\n        auto it = intervals.lower_bound(interval_type(l, l));\n\
    \        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator find_interval(T\
    \ x) const {\n        auto it = intervals.lower_bound(interval_type(x, x));\n\
    \        if (it != intervals.end() && it->first == x) return it;\n        if (it\
    \ == intervals.begin()) return intervals.end();\n        --it;\n        if (it->first\
    \ <= x && x < it->second) return it;\n        return intervals.end();\n    }\n\
    \npublic:\n    IntervalSet() = default;\n\n    IntervalSet(std::initializer_list<interval_type>\
    \ init) {\n        for (auto [l, r] : init) insert(l, r);\n    }\n\n    template\
    \ <class Iterator>\n    IntervalSet(Iterator first, Iterator last) {\n       \
    \ while (first != last) {\n            insert(first->first, first->second);\n\
    \            ++first;\n        }\n    }\n\n    int size() const { return int(intervals.size());\
    \ }\n\n    bool empty() const { return intervals.empty(); }\n\n    void clear()\
    \ { intervals.clear(); }\n\n    bool contains(T x) const { return find_interval(x)\
    \ != intervals.end(); }\n\n    bool contains(T l, T r) const {\n        assert(l\
    \ <= r);\n        if (l == r) return true;\n        auto it = find_interval(l);\n\
    \        return it != intervals.end() && r <= it->second;\n    }\n\n    interval_type\
    \ get(T x) const {\n        auto it = find_interval(x);\n        assert(it !=\
    \ intervals.end());\n        return *it;\n    }\n\n    const interval_type* get_if(T\
    \ x) const {\n        auto it = find_interval(x);\n        return it == intervals.end()\
    \ ? nullptr : std::addressof(*it);\n    }\n\n    bool intersects(T l, T r) const\
    \ {\n        assert(l <= r);\n        if (l == r) return false;\n\n        auto\
    \ it = intervals.lower_bound(interval_type(l, l));\n\n        if (it != intervals.begin())\
    \ {\n            auto prev = std::prev(it);\n            if (l < prev->second)\
    \ return true;\n        }\n\n        return it != intervals.end() && it->first\
    \ < r;\n    }\n\n    void insert(T l, T r) {\n        assert(l <= r);\n      \
    \  if (l == r) return;\n\n        auto it = first_intersecting_or_touching(l);\n\
    \n        while (it != intervals.end() && it->first <= r) {\n            l = std::min(l,\
    \ it->first);\n            r = std::max(r, it->second);\n            it = intervals.erase(it);\n\
    \        }\n\n        intervals.emplace(l, r);\n    }\n\n    void erase(T l, T\
    \ r) {\n        assert(l <= r);\n        if (l == r) return;\n\n        auto it\
    \ = first_intersecting_or_touching(l);\n\n        while (it != intervals.end()\
    \ && it->first < r) {\n            const T a = it->first;\n            const T\
    \ b = it->second;\n\n            if (b <= l) {\n                ++it;\n      \
    \          continue;\n            }\n\n            it = intervals.erase(it);\n\
    \n            if (a < l) intervals.emplace(a, l);\n            if (r < b) {\n\
    \                intervals.emplace(r, b);\n                break;\n          \
    \  }\n        }\n    }\n\n    T mex(T x) const {\n        auto it = find_interval(x);\n\
    \        return it == intervals.end() ? x : it->second;\n    }\n\n    T min_not_covered(T\
    \ x) const { return mex(x); }\n\n    std::vector<interval_type> to_vector() const\
    \ {\n        return std::vector<interval_type>(intervals.begin(), intervals.end());\n\
    \    }\n\n    auto begin() const { return intervals.begin(); }\n\n    auto end()\
    \ const { return intervals.end(); }\n};\n\n} // namespace ds\n} // namespace m1une\n\
    \n#endif // M1UNE_INTERVAL_SET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/interval_set/interval_set.hpp
  requiredBy: []
  timestamp: '2026-06-21 13:10:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/interval_set/interval_set.test.cpp
documentation_of: ds/interval_set/interval_set.hpp
layout: document
title: Interval Set
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
