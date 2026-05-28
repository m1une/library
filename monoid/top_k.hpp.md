---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/bottom_k.hpp
    title: monoid/bottom_k.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/top_k.hpp\"\n\n\n\n#include <vector>\n#include <algorithm>\n\
    #include <functional>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for\
    \ finding the top/bottom K elements in a range.\n// The elements must be stored\
    \ in the order defined by the Compare functor.\n// Default Compare is std::greater<T>\
    \ (i.e., descending order for Top K).\ntemplate <typename T, int K, typename Compare\
    \ = std::greater<T>>\nstruct TopK {\n    using value_type = std::vector<T>;\n\n\
    \    // The identity element is an empty vector.\n    static constexpr value_type\
    \ id() { \n        return std::vector<T>(); \n    }\n\n    // Merges two sorted\
    \ vectors and keeps only the first K elements.\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res;\n  \
    \      res.reserve(std::min(K, (int)(a.size() + b.size())));\n        \n     \
    \   int i = 0, j = 0;\n        while (res.size() < (std::size_t)K && (i < (int)a.size()\
    \ || j < (int)b.size())) {\n            if (i == (int)a.size()) {\n          \
    \      res.push_back(b[j++]);\n            } else if (j == (int)b.size()) {\n\
    \                res.push_back(a[i++]);\n            } else if (Compare()(a[i],\
    \ b[j])) { \n                res.push_back(a[i++]);\n            } else {\n  \
    \              res.push_back(b[j++]);\n            }\n        }\n        return\
    \ res;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_TOP_K_HPP\n#define M1UNE_MONOID_TOP_K_HPP 1\n\n#include\
    \ <vector>\n#include <algorithm>\n#include <functional>\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for finding the top/bottom K elements in a range.\n\
    // The elements must be stored in the order defined by the Compare functor.\n\
    // Default Compare is std::greater<T> (i.e., descending order for Top K).\ntemplate\
    \ <typename T, int K, typename Compare = std::greater<T>>\nstruct TopK {\n   \
    \ using value_type = std::vector<T>;\n\n    // The identity element is an empty\
    \ vector.\n    static constexpr value_type id() { \n        return std::vector<T>();\
    \ \n    }\n\n    // Merges two sorted vectors and keeps only the first K elements.\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        value_type res;\n        res.reserve(std::min(K, (int)(a.size() +\
    \ b.size())));\n        \n        int i = 0, j = 0;\n        while (res.size()\
    \ < (std::size_t)K && (i < (int)a.size() || j < (int)b.size())) {\n          \
    \  if (i == (int)a.size()) {\n                res.push_back(b[j++]);\n       \
    \     } else if (j == (int)b.size()) {\n                res.push_back(a[i++]);\n\
    \            } else if (Compare()(a[i], b[j])) { \n                res.push_back(a[i++]);\n\
    \            } else {\n                res.push_back(b[j++]);\n            }\n\
    \        }\n        return res;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MONOID_TOP_K_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/top_k.hpp
  requiredBy:
  - monoid/bottom_k.hpp
  timestamp: '2026-05-28 17:48:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/top_k.hpp
layout: document
redirect_from:
- /library/monoid/top_k.hpp
- /library/monoid/top_k.hpp.html
title: monoid/top_k.hpp
---
