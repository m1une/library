---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/sequence/sequence_algorithms.test.cpp
    title: verify/sequence/sequence_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"sequence/inversion_count.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace m1une {\nnamespace sequence {\n\n// Returns the number of pairs (i,\
    \ j) with i < j and a[i] > a[j].\n// The vector is taken by value because merge\
    \ sort rearranges it.\ntemplate <typename T>\nlong long inversion_count(std::vector<T>\
    \ a) {\n    const int n = int(a.size());\n    std::vector<T> temp = a;\n\n   \
    \ auto merge_sort = [&](auto& self, int l, int r) -> long long {\n        if (r\
    \ - l <= 1) return 0;\n\n        const int m = l + (r - l) / 2;\n        long\
    \ long inv = self(self, l, m) + self(self, m, r);\n\n        int i = l;\n    \
    \    int j = m;\n        int k = l;\n        while (i < m && j < r) {\n      \
    \      if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n          \
    \  } else {\n                temp[k++] = a[j++];\n                inv += m - i;\n\
    \            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n     \
    \   while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p) {\n\
    \            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n   \
    \ return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace sequence\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_SEQUENCE_INVERSION_COUNT_HPP\n#define M1UNE_SEQUENCE_INVERSION_COUNT_HPP\
    \ 1\n\n#include <vector>\n\nnamespace m1une {\nnamespace sequence {\n\n// Returns\
    \ the number of pairs (i, j) with i < j and a[i] > a[j].\n// The vector is taken\
    \ by value because merge sort rearranges it.\ntemplate <typename T>\nlong long\
    \ inversion_count(std::vector<T> a) {\n    const int n = int(a.size());\n    std::vector<T>\
    \ temp = a;\n\n    auto merge_sort = [&](auto& self, int l, int r) -> long long\
    \ {\n        if (r - l <= 1) return 0;\n\n        const int m = l + (r - l) /\
    \ 2;\n        long long inv = self(self, l, m) + self(self, m, r);\n\n       \
    \ int i = l;\n        int j = m;\n        int k = l;\n        while (i < m &&\
    \ j < r) {\n            if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n\
    \            } else {\n                temp[k++] = a[j++];\n                inv\
    \ += m - i;\n            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n\
    \        while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p)\
    \ {\n            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n\
    \    return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace sequence\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_SEQUENCE_INVERSION_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: sequence/inversion_count.hpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/sequence/sequence_algorithms.test.cpp
documentation_of: sequence/inversion_count.hpp
layout: document
title: Inversion Count
---

## Overview

Calculates the number of inversions in a sequence. An inversion is a pair of
indices `(i, j)` such that `i < j` and `a[i] > a[j]`.

The implementation uses merge sort and does not require coordinate compression.

The return type is `long long` because a sequence of size $N$ can have
$N(N-1)/2$ inversions.

## Template Parameters

* `T`: Element type. Values must be comparable using `<`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `long long inversion_count(std::vector<T> a)` | Returns the total number of inversions. The argument is taken by value. Use `std::move(a)` if you no longer need the original array to avoid an $O(N)$ copy. | $O(N \log N)$ time, $O(N)$ space |

## Example

```cpp
#include "sequence/inversion_count.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {2, 4, 1, 3, 5};

    const long long inversions = m1une::sequence::inversion_count(a);

    // The inversions are:
    // (2, 1) -> indices 0 and 2
    // (4, 1) -> indices 1 and 2
    // (4, 3) -> indices 1 and 3
    std::cout << "Inversions: " << inversions << "\n"; // Output: 3

    // To avoid copying the array if you don't need it afterward:
    // long long fast_invs = m1une::sequence::inversion_count(std::move(a));

    return 0;
}
```
