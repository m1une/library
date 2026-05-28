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
  bundledCode: "#line 1 \"monoid/permutation.hpp\"\n\n\n\n#include <array>\n#include\
    \ <numeric>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for Permutation\
    \ Composition.\n// Represents a permutation of fixed size N.\ntemplate <int N>\n\
    struct Permutation {\n    using value_type = std::array<int, N>;\n\n    // The\
    \ identity element is the identity permutation (0, 1, 2, ..., N-1).\n    static\
    \ constexpr value_type id() {\n        value_type res{};\n        std::iota(res.begin(),\
    \ res.end(), 0);\n        return res;\n    }\n\n    // Composes two permutations\
    \ (applies 'a' then 'b').\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        value_type res{};\n        for (int i = 0;\
    \ i < N; ++i) {\n            res[i] = b[a[i]];\n        }\n        return res;\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_PERMUTATION_HPP\n#define M1UNE_MONOID_PERMUTATION_HPP\
    \ 1\n\n#include <array>\n#include <numeric>\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for Permutation Composition.\n// Represents a permutation of\
    \ fixed size N.\ntemplate <int N>\nstruct Permutation {\n    using value_type\
    \ = std::array<int, N>;\n\n    // The identity element is the identity permutation\
    \ (0, 1, 2, ..., N-1).\n    static constexpr value_type id() {\n        value_type\
    \ res{};\n        std::iota(res.begin(), res.end(), 0);\n        return res;\n\
    \    }\n\n    // Composes two permutations (applies 'a' then 'b').\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  value_type res{};\n        for (int i = 0; i < N; ++i) {\n            res[i]\
    \ = b[a[i]];\n        }\n        return res;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_PERMUTATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/permutation.hpp
  requiredBy: []
  timestamp: '2026-05-28 18:13:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/permutation.hpp
layout: document
redirect_from:
- /library/monoid/permutation.hpp
- /library/monoid/permutation.hpp.html
title: monoid/permutation.hpp
---
