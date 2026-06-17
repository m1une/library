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
  bundledCode: "#line 1 \"monoid/top_k_count.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <functional>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Monoid for finding the top K distinct elements and their frequencies\
    \ in a range.\n// The default Compare is std::greater<T> (descending order for\
    \ Top K).\ntemplate <typename T, int K, typename Compare = std::greater<T>>\n\
    struct TopKCount {\n    using value_type = std::vector<std::pair<T, int>>;\n\n\
    \    static constexpr value_type id() {\n        return value_type();\n    }\n\
    \n    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        value_type res;\n        res.reserve(std::min(K, (int)(a.size() +\
    \ b.size())));\n\n        int i = 0, j = 0;\n        while (res.size() < (std::size_t)K\
    \ && (i < (int)a.size() || j < (int)b.size())) {\n            if (i == (int)a.size())\
    \ {\n                res.push_back(b[j++]);\n            } else if (j == (int)b.size())\
    \ {\n                res.push_back(a[i++]);\n            } else if (a[i].first\
    \ == b[j].first) {\n                // If the values are identical, merge their\
    \ counts\n                res.push_back({a[i].first, a[i].second + b[j].second});\n\
    \                i++;\n                j++;\n            } else if (Compare()(a[i].first,\
    \ b[j].first)) {\n                res.push_back(a[i++]);\n            } else {\n\
    \                res.push_back(b[j++]);\n            }\n        }\n        return\
    \ res;\n    }\n\n    // Helper to securely create a leaf node from a single value.\n\
    \    static constexpr value_type make(const T& val, int count = 1) {\n       \
    \ return value_type{std::pair<T, int>{val, count}};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_TOP_K_COUNT_HPP\n#define M1UNE_MONOID_TOP_K_COUNT_HPP\
    \ 1\n\n#include <algorithm>\n#include <functional>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for finding the\
    \ top K distinct elements and their frequencies in a range.\n// The default Compare\
    \ is std::greater<T> (descending order for Top K).\ntemplate <typename T, int\
    \ K, typename Compare = std::greater<T>>\nstruct TopKCount {\n    using value_type\
    \ = std::vector<std::pair<T, int>>;\n\n    static constexpr value_type id() {\n\
    \        return value_type();\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        value_type res;\n        res.reserve(std::min(K,\
    \ (int)(a.size() + b.size())));\n\n        int i = 0, j = 0;\n        while (res.size()\
    \ < (std::size_t)K && (i < (int)a.size() || j < (int)b.size())) {\n          \
    \  if (i == (int)a.size()) {\n                res.push_back(b[j++]);\n       \
    \     } else if (j == (int)b.size()) {\n                res.push_back(a[i++]);\n\
    \            } else if (a[i].first == b[j].first) {\n                // If the\
    \ values are identical, merge their counts\n                res.push_back({a[i].first,\
    \ a[i].second + b[j].second});\n                i++;\n                j++;\n \
    \           } else if (Compare()(a[i].first, b[j].first)) {\n                res.push_back(a[i++]);\n\
    \            } else {\n                res.push_back(b[j++]);\n            }\n\
    \        }\n        return res;\n    }\n\n    // Helper to securely create a leaf\
    \ node from a single value.\n    static constexpr value_type make(const T& val,\
    \ int count = 1) {\n        return value_type{std::pair<T, int>{val, count}};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_TOP_K_COUNT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/top_k_count.hpp
  requiredBy: []
  timestamp: '2026-06-17 14:06:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/top_k_count.hpp
layout: document
title: Top K Count Monoid
---

## Overview

A monoid that maintains the Top $K$ (largest) distinct elements and their frequencies (counts) in a range. The underlying `value_type` is `std::vector<std::pair<T, int>>`. Merging two nodes takes $O(K)$ time.

## Initialization

Use the `make(val)` method to construct a leaf node containing a single value with a count of 1.

### Example

```cpp
#include "data_structure/segtree.hpp"
#include "monoid/top_k_count.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 2 distinct elements and their counts
using Top2CM = m1une::monoid::TopKCount<long long, 2>;

int main() {
    std::vector<long long> A = {10, 50, 50, 40, 50};
    int N = A.size();

    std::vector<Top2CM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top2CM::make(A[i]);
    }

    m1une::data_structure::Segtree<Top2CM> seg(init_data);

    // Get the top 2 elements in the range [0, 5) -> { (50, 3), (40, 1) }
    auto top2 = seg.prod(0, 5);
    
    for (auto p : top2) {
        std::cout << "Value: " << p.first << " Count: " << p.second << "\n";
    }

    return 0;
}
```
