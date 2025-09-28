---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: monoid/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/affine_right_monoid.hpp\"\n\n\n\n#include\
    \ <utility>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <type_traits>\n\nnamespace m1une {\ntemplate <typename T, auto operation, auto\
    \ identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n}\
    \  // namespace m1une\n\n\n#line 7 \"monoid/monoids/affine_right_monoid.hpp\"\n\
    \nnamespace m1une {\n// right associative version of affine_monoid\n// Affine\
    \ transformation f(x) = ax + b is represented as (a, b)\n// perform g first, then\
    \ f\n// op(f, g)(x) = f(g(x))\ntemplate <typename T>\nusing affine_right_monoid\
    \ = monoid<std::pair<T, T>,\n                                   [](std::pair<T,\
    \ T> f, std::pair<T, T> g) {\n                                       return std::pair<T,\
    \ T>(f.first * g.first, f.first * g.second + f.second);\n                    \
    \               },\n                                   []() { return std::pair<T,\
    \ T>(1, 0); }, false>;\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_AFFINE_RIGHT_MONOID_HPP\n#define M1UNE_AFFINE_RIGHT_MONOID_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../monoid.hpp\"\n\nnamespace m1une {\n\
    // right associative version of affine_monoid\n// Affine transformation f(x) =\
    \ ax + b is represented as (a, b)\n// perform g first, then f\n// op(f, g)(x)\
    \ = f(g(x))\ntemplate <typename T>\nusing affine_right_monoid = monoid<std::pair<T,\
    \ T>,\n                                   [](std::pair<T, T> f, std::pair<T, T>\
    \ g) {\n                                       return std::pair<T, T>(f.first\
    \ * g.first, f.first * g.second + f.second);\n                               \
    \    },\n                                   []() { return std::pair<T, T>(1, 0);\
    \ }, false>;\n}  // namespace m1une\n\n#endif  // M1UNE_AFFINE_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/affine_right_monoid.hpp
  requiredBy: []
  timestamp: '2025-09-28 21:32:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/affine_right_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/affine_right_monoid.hpp
- /library/monoid/monoids/affine_right_monoid.hpp.html
title: monoid/monoids/affine_right_monoid.hpp
---
