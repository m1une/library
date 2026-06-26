---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/partially_persistent_dsu.test.cpp
    title: verify/ds/dsu/partially_persistent_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/partially_persistent_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\nstruct PartiallyPersistentDsu {\n   private:\n\
    \    static constexpr int never = std::numeric_limits<int>::max();\n\n    int\
    \ _n;\n    int _time;\n    std::vector<int> parent;\n    std::vector<int> parent_time;\n\
    \    std::vector<std::vector<std::pair<int, int>>> size_history;\n\n    static\
    \ int check_size(int n) {\n        assert(0 <= n);\n        return n;\n    }\n\
    \n    void check_time(int t) const {\n        assert(0 <= t && t <= _time);\n\
    \    }\n\n   public:\n    PartiallyPersistentDsu() : PartiallyPersistentDsu(0)\
    \ {}\n\n    explicit PartiallyPersistentDsu(int n)\n        : _n(check_size(n)),\
    \ _time(0), parent(_n, -1), parent_time(_n, never), size_history(_n) {\n     \
    \   for (int i = 0; i < _n; i++) size_history[i].emplace_back(0, 1);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    int time() const {\n        return _time;\n\
    \    }\n\n    int leader(int t, int a) const {\n        check_time(t);\n     \
    \   assert(0 <= a && a < _n);\n        while (parent_time[a] <= t) a = parent[a];\n\
    \        return a;\n    }\n\n    int leader(int a) const {\n        return leader(_time,\
    \ a);\n    }\n\n    bool same(int t, int a, int b) const {\n        check_time(t);\n\
    \        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n      \
    \  return leader(t, a) == leader(t, b);\n    }\n\n    bool same(int a, int b)\
    \ const {\n        return same(_time, a, b);\n    }\n\n    int group_size(int\
    \ t, int a) const {\n        int r = leader(t, a);\n        const auto& h = size_history[r];\n\
    \        auto it = std::upper_bound(h.begin(), h.end(), std::pair<int, int>(t,\
    \ never));\n        --it;\n        return it->second;\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent[leader(a)];\n    }\n\n    int size(int t,\
    \ int a) const {\n        return group_size(t, a);\n    }\n\n    int size(int\
    \ a) const {\n        return group_size(a);\n    }\n\n    bool merge(int a, int\
    \ b) {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n\
    \        ++_time;\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return false;\n        if (-parent[x] < -parent[y]) {\n            std::swap(x,\
    \ y);\n        }\n        parent[x] += parent[y];\n        parent[y] = x;\n  \
    \      parent_time[y] = _time;\n        size_history[x].emplace_back(_time, -parent[x]);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups(int t)\
    \ const {\n        check_time(t);\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(t,\
    \ i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        return groups(_time);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PARTIALLY_PERSISTENT_DSU_HPP\n#define M1UNE_PARTIALLY_PERSISTENT_DSU_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\nstruct PartiallyPersistentDsu\
    \ {\n   private:\n    static constexpr int never = std::numeric_limits<int>::max();\n\
    \n    int _n;\n    int _time;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_time;\n    std::vector<std::vector<std::pair<int, int>>> size_history;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n    void check_time(int t) const {\n        assert(0 <= t && t\
    \ <= _time);\n    }\n\n   public:\n    PartiallyPersistentDsu() : PartiallyPersistentDsu(0)\
    \ {}\n\n    explicit PartiallyPersistentDsu(int n)\n        : _n(check_size(n)),\
    \ _time(0), parent(_n, -1), parent_time(_n, never), size_history(_n) {\n     \
    \   for (int i = 0; i < _n; i++) size_history[i].emplace_back(0, 1);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    int time() const {\n        return _time;\n\
    \    }\n\n    int leader(int t, int a) const {\n        check_time(t);\n     \
    \   assert(0 <= a && a < _n);\n        while (parent_time[a] <= t) a = parent[a];\n\
    \        return a;\n    }\n\n    int leader(int a) const {\n        return leader(_time,\
    \ a);\n    }\n\n    bool same(int t, int a, int b) const {\n        check_time(t);\n\
    \        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n      \
    \  return leader(t, a) == leader(t, b);\n    }\n\n    bool same(int a, int b)\
    \ const {\n        return same(_time, a, b);\n    }\n\n    int group_size(int\
    \ t, int a) const {\n        int r = leader(t, a);\n        const auto& h = size_history[r];\n\
    \        auto it = std::upper_bound(h.begin(), h.end(), std::pair<int, int>(t,\
    \ never));\n        --it;\n        return it->second;\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent[leader(a)];\n    }\n\n    int size(int t,\
    \ int a) const {\n        return group_size(t, a);\n    }\n\n    int size(int\
    \ a) const {\n        return group_size(a);\n    }\n\n    bool merge(int a, int\
    \ b) {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n\
    \        ++_time;\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return false;\n        if (-parent[x] < -parent[y]) {\n            std::swap(x,\
    \ y);\n        }\n        parent[x] += parent[y];\n        parent[y] = x;\n  \
    \      parent_time[y] = _time;\n        size_history[x].emplace_back(_time, -parent[x]);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups(int t)\
    \ const {\n        check_time(t);\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(t,\
    \ i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        return groups(_time);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_PARTIALLY_PERSISTENT_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/partially_persistent_dsu.hpp
  requiredBy: []
  timestamp: '2026-06-27 02:52:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/partially_persistent_dsu.test.cpp
documentation_of: ds/dsu/partially_persistent_dsu.hpp
layout: document
title: Partially Persistent DSU
---

## Overview

`PartiallyPersistentDsu` is a Union-Find data structure that supports queries
against old times after merges are applied. The update history is linear:
`merge(a, b)` creates the next time, and queries can be asked at any time from
`0` through the current time.

Time `0` is the initial state. Each call to `merge`, including a no-op merge
inside one component, increases the time by one.

It uses union by size without path compression, because old parent paths must
remain queryable.

## Complexity Notation

* `N` is the number of elements.
* `Q` is the number of merge calls already made.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PartiallyPersistentDsu()` | Creates an empty DSU at time `0`. | $O(1)$ |
| `explicit PartiallyPersistentDsu(int n)` | Creates `n` singleton sets at time `0`. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `int time() const` | Returns the current time. | $O(1)$ |
| `bool merge(int a, int b)` | Advances time by one and merges the current sets containing `a` and `b`. Returns whether two different sets were merged. | $O(\log N)$ |
| `bool same(int t, int a, int b) const` | Returns whether `a` and `b` were in the same set at time `t`. | $O(\log N)$ |
| `bool same(int a, int b) const` | Equivalent to `same(time(), a, b)`. | $O(\log N)$ |
| `int leader(int t, int a) const` | Returns the representative of the set containing `a` at time `t`. | $O(\log N)$ |
| `int leader(int a) const` | Equivalent to `leader(time(), a)`. | $O(\log N)$ |
| `int group_size(int t, int a) const`, `int size(int t, int a) const` | Returns the size of the set containing `a` at time `t`. | $O(\log N + \log Q)$ |
| `int group_size(int a) const`, `int size(int a) const` | Equivalent to querying at the current time. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups(int t) const` | Returns all sets at time `t` as vectors of element indices. | $O(N \log N)$ |
| `std::vector<std::vector<int>> groups() const` | Equivalent to `groups(time())`. | $O(N \log N)$ |

## Example

```cpp
#include "ds/dsu/partially_persistent_dsu.hpp"

#include <iostream>

int main() {
    m1une::ds::PartiallyPersistentDsu dsu(4);

    dsu.merge(0, 1); // time 1
    dsu.merge(2, 3); // time 2
    dsu.merge(1, 2); // time 3

    std::cout << dsu.same(1, 0, 2) << "\n"; // 0
    std::cout << dsu.same(3, 0, 2) << "\n"; // 1
    std::cout << dsu.size(2, 0) << "\n";    // 2
    std::cout << dsu.size(3, 0) << "\n";    // 4
}
```
