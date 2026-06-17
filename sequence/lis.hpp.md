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
  bundledCode: "#line 1 \"sequence/lis.hpp\"\n\n\n\n#include <vector>\n#include <algorithm>\n\
    \nnamespace m1une {\nnamespace sequence {\n\n// Returns the 0-indexed positions\
    \ (indices) of the longest increasing subsequence.\n// If 'strict' is true, it\
    \ finds a strictly increasing subsequence (a[i] < a[j]).\n// If 'strict' is false,\
    \ it finds a non-decreasing subsequence (a[i] <= a[j]).\ntemplate <typename T>\n\
    std::vector<int> lis(const std::vector<T>& a, bool strict = true) {\n    int n\
    \ = a.size();\n    std::vector<T> dp;\n    std::vector<int> pos;\n    std::vector<int>\
    \ prev(n, -1);\n\n    for (int i = 0; i < n; ++i) {\n        auto it = strict\
    \ ? std::lower_bound(dp.begin(), dp.end(), a[i])\n                         : std::upper_bound(dp.begin(),\
    \ dp.end(), a[i]);\n        int d = std::distance(dp.begin(), it);\n        \n\
    \        if (it == dp.end()) {\n            dp.push_back(a[i]);\n            pos.push_back(i);\n\
    \        } else {\n            *it = a[i];\n            pos[d] = i;\n        }\n\
    \        \n        if (d > 0) {\n            prev[i] = pos[d - 1];\n        }\n\
    \    }\n\n    if (pos.empty()) return {};\n\n    // Reconstruct the indices of\
    \ the sequence\n    std::vector<int> res;\n    int curr = pos.back();\n    while\
    \ (curr != -1) {\n        res.push_back(curr);\n        curr = prev[curr];\n \
    \   }\n    std::reverse(res.begin(), res.end());\n    \n    return res;\n}\n\n\
    }  // namespace sequence\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEQUENCE_LIS_HPP\n#define M1UNE_SEQUENCE_LIS_HPP 1\n\n#include\
    \ <vector>\n#include <algorithm>\n\nnamespace m1une {\nnamespace sequence {\n\n\
    // Returns the 0-indexed positions (indices) of the longest increasing subsequence.\n\
    // If 'strict' is true, it finds a strictly increasing subsequence (a[i] < a[j]).\n\
    // If 'strict' is false, it finds a non-decreasing subsequence (a[i] <= a[j]).\n\
    template <typename T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict\
    \ = true) {\n    int n = a.size();\n    std::vector<T> dp;\n    std::vector<int>\
    \ pos;\n    std::vector<int> prev(n, -1);\n\n    for (int i = 0; i < n; ++i) {\n\
    \        auto it = strict ? std::lower_bound(dp.begin(), dp.end(), a[i])\n   \
    \                      : std::upper_bound(dp.begin(), dp.end(), a[i]);\n     \
    \   int d = std::distance(dp.begin(), it);\n        \n        if (it == dp.end())\
    \ {\n            dp.push_back(a[i]);\n            pos.push_back(i);\n        }\
    \ else {\n            *it = a[i];\n            pos[d] = i;\n        }\n      \
    \  \n        if (d > 0) {\n            prev[i] = pos[d - 1];\n        }\n    }\n\
    \n    if (pos.empty()) return {};\n\n    // Reconstruct the indices of the sequence\n\
    \    std::vector<int> res;\n    int curr = pos.back();\n    while (curr != -1)\
    \ {\n        res.push_back(curr);\n        curr = prev[curr];\n    }\n    std::reverse(res.begin(),\
    \ res.end());\n    \n    return res;\n}\n\n}  // namespace sequence\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_SEQUENCE_LIS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: sequence/lis.hpp
  requiredBy: []
  timestamp: '2026-06-18 04:11:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: sequence/lis.hpp
layout: document
title: Longest Increasing Subsequence (LIS)
---

## Overview

Calculates the Longest Increasing Subsequence (LIS) of a given array. Instead of returning just the maximum length or the raw values, this function optimally computes and returns a `std::vector<int>` containing the **0-based indices** of the elements that form the sequence. 

This enables you to easily reconstruct the sequence, query the original elements, or correlate them with parallel arrays.

The implementation tracks the DP array and back-pointers, utilizing `std::lower_bound` (or `std::upper_bound`) to run efficiently in $O(N \log N)$ time.

## Template Parameters

* `T`: The underlying data type of the elements in the array. Must be comparable using `<`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> lis(const std::vector<T>& a, bool strict = true)` | Returns the indices of the LIS. If `strict` is `true`, finds a strictly increasing sequence. If `false`, allows adjacent elements in the sequence to be equal (non-decreasing). | $O(N \log N)$ time, $O(N)$ space |

## Example

```cpp
#include "sequence/lis.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    // Find strictly increasing subsequence
    std::vector<int> lis_indices = m1une::sequence::lis(a);
    
    std::cout << "LIS Length: " << lis_indices.size() << "\n"; // Output: 4
    
    std::cout << "Indices: ";
    for (int idx : lis_indices) std::cout << idx << " ";
    // Output might be: 1 2 4 5  (corresponding to indices of 1, 4, 5, 9)
    std::cout << "\n";
    
    std::cout << "Values: ";
    for (int idx : lis_indices) std::cout << a[idx] << " ";
    // Output: 1 4 5 9
    std::cout << "\n";

    // Find non-decreasing subsequence (allows duplicates)
    std::vector<int> nds_indices = m1une::sequence::lis(a, false);
    
    std::cout << "Non-Decreasing Length: " << nds_indices.size() << "\n"; // Output: 5
    // A valid non-decreasing sequence values: 1 1 2 3 5
    
    return 0;
}
```
