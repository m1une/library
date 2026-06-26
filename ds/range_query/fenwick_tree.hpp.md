---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/fenwick_tree.test.cpp
    title: verify/ds/range_query/fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/mo.test.cpp
    title: verify/ds/range_query/mo.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\n\
    struct FenwickTree {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T>\
    \ _data;\n\n    static int max_power_leq(int n) {\n        int result = 1;\n \
    \       while (result <= n / 2) result <<= 1;\n        return result;\n    }\n\
    \n    T prefix_sum(int r) const {\n        T result{};\n        const T* data\
    \ = _data.data();\n        while (r > 0) {\n            result += data[r];\n \
    \           r -= r & -r;\n        }\n        return result;\n    }\n\n   public:\n\
    \    FenwickTree() : _n(0), _max_power(0) {}\n\n    explicit FenwickTree(int n)\n\
    \        : _n(n), _max_power(max_power_leq(n > 0 ? n : 1)), _data(n + 1, T{})\
    \ {}\n\n    explicit FenwickTree(const std::vector<T>& a)\n        : _n(int(a.size())),\n\
    \          _max_power(max_power_leq(_n > 0 ? _n : 1)),\n          _data(a.size()\
    \ + 1, T{}) {\n        for (int i = 1; i <= _n; ++i) {\n            _data[i] +=\
    \ a[i - 1];\n            const int p = i + (i & -i);\n            if (p <= _n)\
    \ {\n                _data[p] += _data[i];\n            }\n        }\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    // Adds `x` to the element at zero-based\
    \ index `p`.\n    void add(int p, const T& x) {\n        assert(0 <= p && p <\
    \ _n);\n        ++p;\n        T* data = _data.data();\n        while (p <= _n)\
    \ {\n            data[p] += x;\n            p += p & -p;\n        }\n    }\n\n\
    \    // Returns the sum of elements in the range [0, r).\n    T sum(int r) const\
    \ {\n        assert(0 <= r && r <= _n);\n        return prefix_sum(r);\n    }\n\
    \n    // Returns the sum of elements in the range [l, r).\n    T sum(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        return prefix_sum(r)\
    \ - prefix_sum(l);\n    }\n\n    // Returns the minimum index `r` such that the\
    \ sum of [0, r) >= w.\n    // Requires all elements in the tree to be non-negative.\n\
    \    int lower_bound(T w) const {\n        if (w <= 0) return 0;\n        int\
    \ x = 0;\n        const T* data = _data.data();\n        for (int k = _max_power;\
    \ k > 0; k >>= 1) {\n            if (x + k <= _n && data[x + k] < w) {\n     \
    \           w -= data[x + k];\n                x += k;\n            }\n      \
    \  }\n        return x + 1;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_FENWICK_TREE_HPP\n#define M1UNE_DS_FENWICK_TREE_HPP 1\n\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <typename T>\nstruct FenwickTree {\n   private:\n    int _n;\n    int\
    \ _max_power;\n    std::vector<T> _data;\n\n    static int max_power_leq(int n)\
    \ {\n        int result = 1;\n        while (result <= n / 2) result <<= 1;\n\
    \        return result;\n    }\n\n    T prefix_sum(int r) const {\n        T result{};\n\
    \        const T* data = _data.data();\n        while (r > 0) {\n            result\
    \ += data[r];\n            r -= r & -r;\n        }\n        return result;\n \
    \   }\n\n   public:\n    FenwickTree() : _n(0), _max_power(0) {}\n\n    explicit\
    \ FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n > 0 ? n : 1)),\
    \ _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>& a)\n\
    \        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0 ? _n\
    \ : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i <= _n;\
    \ ++i) {\n            _data[i] += a[i - 1];\n            const int p = i + (i\
    \ & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_FENWICK_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/fenwick_tree.hpp
  requiredBy: []
  timestamp: '2026-06-27 04:10:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/fenwick_tree.test.cpp
  - verify/ds/range_query/mo.test.cpp
documentation_of: ds/range_query/fenwick_tree.hpp
layout: document
title: Fenwick Tree (Binary Indexed Tree)
---

## Overview

A Fenwick tree, also called a binary indexed tree, supports point additions and
prefix-sum queries in logarithmic time.

Indices are zero-based and range queries use half-open intervals `[l, r)`.

## Template Parameters

* `T`: The underlying numeric type of the elements (e.g., `int`, `long long`, or a modular integer `modint`).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FenwickTree(int n)` | Initializes an array of size `n` with `0`s. | $O(N)$ |
| `FenwickTree(const std::vector<T>& a)` | Builds a tree from a given vector array `a`. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the tree is empty. | $O(1)$ |
| `void add(int p, const T& x)` | Adds `x` to the element at index `p`. | $O(\log N)$ |
| `T sum(int r) const` | Returns the sum of elements in the prefix `[0, r)`. | $O(\log N)$ |
| `T sum(int l, int r) const` | Returns the sum of elements in the interval `[l, r)`. | $O(\log N)$ |
| `int lower_bound(T w) const` | Returns the minimum `r` such that `sum(r) >= w`. Returns `0` when `w <= 0` and `size() + 1` when no such prefix exists. All values must be non-negative. | $O(\log N)$ |

## Example

```cpp
#include "ds/range_query/fenwick_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5};
    m1une::ds::FenwickTree<long long> tree(a);

    // Sum of [1, 4) which is elements at index 1, 2, 3 (2 + 3 + 4 = 9)
    std::cout << tree.sum(1, 4) << "\n"; // Output: 9

    // Add 10 to index 2
    tree.add(2, 10); // Array logically becomes: 1, 2, 13, 4, 5

    // Re-query the sum
    std::cout << tree.sum(1, 4) << "\n"; // Output: 19

    // Find the smallest prefix whose sum is >= 15
    // prefix [0, 3) = 1 + 2 + 13 = 16
    std::cout << tree.lower_bound(15) << "\n"; // Output: 3

    return 0;
}
```
