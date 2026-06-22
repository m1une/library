---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/mo.test.cpp
    title: verify/ds/range_query/mo.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/mo.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Offline Mo's algorithm for half-open array ranges.\n\
    struct Mo {\n    struct Query {\n        int left;\n        int right;\n     \
    \   int id;\n    };\n\n   private:\n    int _n;\n    std::vector<Query> _queries;\n\
    \n   public:\n    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n) {\n      \
    \  assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int query_count() const {\n        return int(_queries.size());\n    }\n\
    \n    bool empty() const {\n        return _queries.empty();\n    }\n\n    const\
    \ std::vector<Query>& queries() const {\n        return _queries;\n    }\n\n \
    \   void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds [left, right) and returns its insertion-order\
    \ ID.\n    int add_query(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        int id = query_count();\n        _queries.push_back(Query{left,\
    \ right, id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order.\
    \ A non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_MO_HPP\n#define M1UNE_DS_RANGE_QUERY_MO_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <numeric>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Offline Mo's algorithm\
    \ for half-open array ranges.\nstruct Mo {\n    struct Query {\n        int left;\n\
    \        int right;\n        int id;\n    };\n\n   private:\n    int _n;\n   \
    \ std::vector<Query> _queries;\n\n   public:\n    Mo() : _n(0) {}\n\n    explicit\
    \ Mo(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int query_count() const {\n        return\
    \ int(_queries.size());\n    }\n\n    bool empty() const {\n        return _queries.empty();\n\
    \    }\n\n    const std::vector<Query>& queries() const {\n        return _queries;\n\
    \    }\n\n    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds [left, right) and returns its insertion-order\
    \ ID.\n    int add_query(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        int id = query_count();\n        _queries.push_back(Query{left,\
    \ right, id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order.\
    \ A non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_MO_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/mo.hpp
  requiredBy: []
  timestamp: '2026-06-23 02:21:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/mo.test.cpp
documentation_of: ds/range_query/mo.hpp
layout: document
title: Mo's Algorithm
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
