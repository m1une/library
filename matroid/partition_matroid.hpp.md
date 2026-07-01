---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroid_intersection.test.cpp
    title: verify/matroid/matroid_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/weighted_matroid_intersection.test.cpp
    title: verify/matroid/weighted_matroid_intersection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/partition_matroid.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace matroid {\n\nclass PartitionMatroid {\n   private:\n    std::vector<int>\
    \ _group;\n    std::vector<int> _capacity;\n\n    void validate() const {\n#ifndef\
    \ NDEBUG\n        for (int capacity : _capacity) assert(0 <= capacity);\n    \
    \    for (int group : _group) assert(0 <= group && group < int(_capacity.size()));\n\
    #endif\n    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit\
    \ PartitionMatroid(std::vector<int> group) : _group(std::move(group)) {\n    \
    \    int group_count = 0;\n        for (int value : _group) {\n            assert(0\
    \ <= value);\n            group_count = std::max(group_count, value + 1);\n  \
    \      }\n        _capacity.assign(group_count, 1);\n    }\n\n    PartitionMatroid(std::vector<int>\
    \ group, std::vector<int> capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATROID_PARTITION_MATROID_HPP\n#define M1UNE_MATROID_PARTITION_MATROID_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace matroid {\n\nclass PartitionMatroid\
    \ {\n   private:\n    std::vector<int> _group;\n    std::vector<int> _capacity;\n\
    \n    void validate() const {\n#ifndef NDEBUG\n        for (int capacity : _capacity)\
    \ assert(0 <= capacity);\n        for (int group : _group) assert(0 <= group &&\
    \ group < int(_capacity.size()));\n#endif\n    }\n\n   public:\n    PartitionMatroid()\
    \ = default;\n\n    explicit PartitionMatroid(std::vector<int> group) : _group(std::move(group))\
    \ {\n        int group_count = 0;\n        for (int value : _group) {\n      \
    \      assert(0 <= value);\n            group_count = std::max(group_count, value\
    \ + 1);\n        }\n        _capacity.assign(group_count, 1);\n    }\n\n    PartitionMatroid(std::vector<int>\
    \ group, std::vector<int> capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n#endif  // M1UNE_MATROID_PARTITION_MATROID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/partition_matroid.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/matroids.test.cpp
  - verify/matroid/matroid_intersection.test.cpp
  - verify/matroid/weighted_matroid_intersection.test.cpp
documentation_of: matroid/partition_matroid.hpp
layout: document
title: Partition Matroid
---

## Overview

`PartitionMatroid` assigns every ground element to one group and limits how
many elements may be selected from each group.

The one-argument constructor gives every group capacity one. The two-argument
constructor accepts individual capacities.

Oracle inputs must contain distinct valid ground-set indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `PartitionMatroid(std::vector<int> group)` | Creates capacity-one groups. Group ids must be non-negative and dense enough to allocate through the maximum id. | $O(N+G)$ |
| `PartitionMatroid(std::vector<int> group, std::vector<int> capacity)` | Uses `capacity[g]` for group `g`. | $O(N+G)$ |
| `int size() const` | Returns the ground-set size. | $O(1)$ |
| `int group_count() const` | Returns the number of groups. | $O(1)$ |
| `const std::vector<int>& groups() const` | Returns the group of every element. | $O(1)$ |
| `const std::vector<int>& capacities() const` | Returns the capacities. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Checks all group capacities. | $O(G+|S|)$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(G+|S|)$ |

## Example

```cpp
#include "matroid/partition_matroid.hpp"
#include <vector>

std::vector<int> group = {0, 0, 1, 1, 1};
std::vector<int> capacity = {1, 2};
m1une::matroid::PartitionMatroid matroid(group, capacity);

bool ok = matroid(std::vector<int>{0, 2, 4}); // true
```
