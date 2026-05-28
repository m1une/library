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
  bundledCode: "#line 1 \"math/affine.hpp\"\n\n\n\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <typename T>\nT affine(std::pair<T, T>\
    \ f, T x) {\n    return f.first * x + f.second;\n}\n\n}  // namespace math\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_AFFINE_HPP\n#define M1UNE_AFFINE_HPP 1\n\n#include <utility>\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nT affine(std::pair<T,\
    \ T> f, T x) {\n    return f.first * x + f.second;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n#endif  // M1UNE_AFFINE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/affine.hpp
  requiredBy: []
  timestamp: '2026-05-29 01:41:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/affine.hpp
layout: document
redirect_from:
- /library/math/affine.hpp
- /library/math/affine.hpp.html
title: math/affine.hpp
---
