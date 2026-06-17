---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/fenwick_tree.hpp\"\n\n\n\n#include <vector>\n\
    #include <cassert>\n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate\
    \ <typename T>\nstruct FenwickTree {\n   private:\n    int _n;\n    std::vector<T>\
    \ data;\n\n   public:\n    FenwickTree() : _n(0) {}\n    \n    explicit FenwickTree(int\
    \ n) : _n(n), data(n + 1, 0) {}\n    \n    explicit FenwickTree(const std::vector<T>&\
    \ a) : _n(a.size()), data(a.size() + 1, 0) {\n        // Initialize in O(N) time\n\
    \        for (int i = 1; i <= _n; i++) {\n            data[i] += a[i - 1];\n \
    \           int p = i + (i & -i);\n            if (p <= _n) {\n              \
    \  data[p] += data[i];\n            }\n        }\n    }\n\n    // Adds 'x' to\
    \ the element at index 'p' (0-indexed)\n    void add(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p++;\n        while (p <= _n) {\n            data[p]\
    \ += x;\n            p += p & -p;\n        }\n    }\n\n    // Returns the sum\
    \ of elements in the range [0, r)\n    T sum(int r) const {\n        assert(0\
    \ <= r && r <= _n);\n        T s = 0;\n        while (r > 0) {\n            s\
    \ += data[r];\n            r -= r & -r;\n        }\n        return s;\n    }\n\
    \n    // Returns the sum of elements in the range [l, r)\n    T sum(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        return sum(r)\
    \ - sum(l);\n    }\n\n    // Returns the minimum index `r` such that the sum of\
    \ [0, r) >= w.\n    // Requires all elements in the tree to be non-negative.\n\
    \    int lower_bound(T w) const {\n        if (w <= 0) return 0;\n        int\
    \ x = 0;\n        int k = 1;\n        while (k <= _n) k <<= 1;\n        for (k\
    \ >>= 1; k > 0; k >>= 1) {\n            if (x + k <= _n && data[x + k] < w) {\n\
    \                w -= data[x + k];\n                x += k;\n            }\n \
    \       }\n        return x + 1;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP\n#define M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP\
    \ 1\n\n#include <vector>\n#include <cassert>\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\ntemplate <typename T>\nstruct FenwickTree {\n   private:\n    int _n;\n\
    \    std::vector<T> data;\n\n   public:\n    FenwickTree() : _n(0) {}\n    \n\
    \    explicit FenwickTree(int n) : _n(n), data(n + 1, 0) {}\n    \n    explicit\
    \ FenwickTree(const std::vector<T>& a) : _n(a.size()), data(a.size() + 1, 0) {\n\
    \        // Initialize in O(N) time\n        for (int i = 1; i <= _n; i++) {\n\
    \            data[i] += a[i - 1];\n            int p = i + (i & -i);\n       \
    \     if (p <= _n) {\n                data[p] += data[i];\n            }\n   \
    \     }\n    }\n\n    // Adds 'x' to the element at index 'p' (0-indexed)\n  \
    \  void add(int p, T x) {\n        assert(0 <= p && p < _n);\n        p++;\n \
    \       while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r)\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        T s = 0;\n\
    \        while (r > 0) {\n            s += data[r];\n            r -= r & -r;\n\
    \        }\n        return s;\n    }\n\n    // Returns the sum of elements in\
    \ the range [l, r)\n    T sum(int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        return sum(r) - sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        int k = 1;\n     \
    \   while (k <= _n) k <<= 1;\n        for (k >>= 1; k > 0; k >>= 1) {\n      \
    \      if (x + k <= _n && data[x + k] < w) {\n                w -= data[x + k];\n\
    \                x += k;\n            }\n        }\n        return x + 1;\n  \
    \  }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_DATA_STRUCTURE_FENWICK_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/fenwick_tree.hpp
  requiredBy: []
  timestamp: '2026-06-18 04:06:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/fenwick_tree.hpp
layout: document
title: Fenwick Tree (Binary Indexed Tree)
---

## Overview

A Fenwick Tree (Binary Indexed Tree) is a data structure that can efficiently update elements and calculate prefix sums in an array. It takes significantly less code and less memory overhead than a full Segment Tree.

All indices provided to the API are `0`-indexed, adhering to standard C++ conventions, and the range query covers the half-open interval `[l, r)`.

## Template Parameters

* `T`: The underlying numeric type of the elements (e.g., `int`, `long long`, or a modular integer `modint`).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FenwickTree(int n)` | Initializes an array of size `n` with `0`s. | $O(N)$ |
| `FenwickTree(const std::vector<T>& a)` | Builds a tree from a given vector array `a`. | $O(N)$ |
| `void add(int p, T x)` | Adds `x` to the element at `0`-indexed position `p`. | $O(\log N)$ |
| `T sum(int r) const` | Returns the sum of elements in the prefix `[0, r)`. | $O(\log N)$ |
| `T sum(int l, int r) const` | Returns the sum of elements in the interval `[l, r)`. | $O(\log N)$ |
| `int lower_bound(T w) const` | Binary searches the tree in parallel. Returns the minimum length `r` such that `sum(r) >= w`. **Requires all values to be non-negative.** | $O(\log N)$ |

## Example

```cpp
#include "data_structure/fenwick_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5};
    m1une::data_structure::FenwickTree<long long> fenw(a);

    // Sum of [1, 4) which is elements at index 1, 2, 3 (2 + 3 + 4 = 9)
    std::cout << fenw.sum(1, 4) << "\n"; // Output: 9

    // Add 10 to index 2
    fenw.add(2, 10); // Array logically becomes: 1, 2, 13, 4, 5

    // Re-query the sum
    std::cout << fenw.sum(1, 4) << "\n"; // Output: 19

    // Find the smallest prefix whose sum is >= 15
    // prefix [0, 3) = 1 + 2 + 13 = 16
    std::cout << fenw.lower_bound(15) << "\n"; // Output: 3

    return 0;
}
```
