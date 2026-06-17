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
  bundledCode: "#line 1 \"sequence/inversion_count.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace m1une {\nnamespace sequence {\n\n// Calculates the number of inversions\
    \ in the array.\n// Takes the vector by value because the merge sort process mutates\
    \ it.\n// If you don't need the original array, you can pass it with std::move().\n\
    template <typename T>\nlong long inversion_count(std::vector<T> a) {\n    int\
    \ n = a.size();\n    std::vector<T> temp(n);\n\n    // Recursive lambda for merge\
    \ sort\n    auto merge_sort = [&](auto& self, int l, int r) -> long long {\n \
    \       if (r - l <= 1) return 0;\n        \n        int m = l + (r - l) / 2;\n\
    \        long long inv = self(self, l, m) + self(self, m, r);\n        \n    \
    \    int i = l, j = m, k = l;\n        while (i < m && j < r) {\n            if\
    \ (a[i] <= a[j]) {\n                temp[k++] = a[i++];\n            } else {\n\
    \                temp[k++] = a[j++];\n                // All remaining elements\
    \ in the left half are strictly greater than a[j]\n                inv += m -\
    \ i;\n            }\n        }\n        \n        while (i < m) temp[k++] = a[i++];\n\
    \        while (j < r) temp[k++] = a[j++];\n        \n        for (int p = l;\
    \ p < r; ++p) {\n            a[p] = temp[p];\n        }\n        \n        return\
    \ inv;\n    };\n\n    return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace\
    \ sequence\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEQUENCE_INVERSION_COUNT_HPP\n#define M1UNE_SEQUENCE_INVERSION_COUNT_HPP\
    \ 1\n\n#include <vector>\n\nnamespace m1une {\nnamespace sequence {\n\n// Calculates\
    \ the number of inversions in the array.\n// Takes the vector by value because\
    \ the merge sort process mutates it.\n// If you don't need the original array,\
    \ you can pass it with std::move().\ntemplate <typename T>\nlong long inversion_count(std::vector<T>\
    \ a) {\n    int n = a.size();\n    std::vector<T> temp(n);\n\n    // Recursive\
    \ lambda for merge sort\n    auto merge_sort = [&](auto& self, int l, int r) ->\
    \ long long {\n        if (r - l <= 1) return 0;\n        \n        int m = l\
    \ + (r - l) / 2;\n        long long inv = self(self, l, m) + self(self, m, r);\n\
    \        \n        int i = l, j = m, k = l;\n        while (i < m && j < r) {\n\
    \            if (a[i] <= a[j]) {\n                temp[k++] = a[i++];\n      \
    \      } else {\n                temp[k++] = a[j++];\n                // All remaining\
    \ elements in the left half are strictly greater than a[j]\n                inv\
    \ += m - i;\n            }\n        }\n        \n        while (i < m) temp[k++]\
    \ = a[i++];\n        while (j < r) temp[k++] = a[j++];\n        \n        for\
    \ (int p = l; p < r; ++p) {\n            a[p] = temp[p];\n        }\n        \n\
    \        return inv;\n    };\n\n    return merge_sort(merge_sort, 0, n);\n}\n\n\
    }  // namespace sequence\n}  // namespace m1une\n\n#endif  // M1UNE_SEQUENCE_INVERSION_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: sequence/inversion_count.hpp
  requiredBy: []
  timestamp: '2026-06-18 04:21:29+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: sequence/inversion_count.hpp
layout: document
title: Inversion Count
---

## Overview

Calculates the number of inversions in a given sequence. An inversion is a pair of indices `(i, j)` such that `i < j` and `a[i] > a[j]`. It represents how far away the array is from being completely sorted.

The algorithm uses a modified Merge Sort, which is highly efficient and operates seamlessly on any comparable data type (e.g., `int`, `long long`, `double`, `std::string`) without requiring coordinate compression.

*Note: The function returns a `long long` because the maximum number of inversions in an array of size $N$ is $N(N-1)/2$, which will easily overflow a standard 32-bit `int` for $N \ge 10^5$.*

## Template Parameters

* `T`: The underlying data type of the sequence elements. Must be comparable using `<=`.

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
    
    // Calculate inversions
    long long invs = m1une::sequence::inversion_count(a);
    
    // The inversions are:
    // (2, 1) -> indices 0 and 2
    // (4, 1) -> indices 1 and 2
    // (4, 3) -> indices 1 and 3
    std::cout << "Inversions: " << invs << "\n"; // Output: 3
    
    // To avoid copying the array if you don't need it afterward:
    // long long fast_invs = m1une::sequence::inversion_count(std::move(a));

    return 0;
}
```
