---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':warning:'
    path: monoid/monoids/add_monoid.hpp
    title: monoid/monoids/add_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/monoids/affine_monoid.hpp
    title: monoid/monoids/affine_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/and_monoid.hpp
    title: monoid/monoids/and_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/max_monoid.hpp
    title: monoid/monoids/max_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/min_monoid.hpp
    title: monoid/monoids/min_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/mul_monoid.hpp
    title: monoid/monoids/mul_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/or_monoid.hpp
    title: monoid/monoids/or_monoid.hpp
  - icon: ':warning:'
    path: monoid/monoids/xor_monoid.hpp
    title: monoid/monoids/xor_monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/prim_monoids.hpp\"\n\n\n\n#line 1 \"monoid/monoid.hpp\"\
    \n\n\n\n#include <functional>\n#include <type_traits>\n\nnamespace m1une {\n\n\
    template <typename T, auto operation, auto identity, bool commutative>\nstruct\
    \ monoid {\n    static_assert(std::is_convertible_v<decltype(operation), std::function<T(T,\
    \ T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/monoids/add_monoid.hpp\"\n\n\n\n#line\
    \ 5 \"monoid/monoids/add_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename\
    \ T>\nusing add_monoid = monoid<T, [](T a, T b) { return a + b; }, []() { return\
    \ T(0); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/mul_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoids/mul_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing mul_monoid = monoid<T, [](T a, T b) { return a * b; }, []()\
    \ { return T(1); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/min_monoid.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <limits>\n\n#line 8 \"monoid/monoids/min_monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing min_monoid =\n    monoid<T,\
    \ [](T a, T b) { return std::min(a, b); }, []() { return std::numeric_limits<T>::max();\
    \ }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/max_monoid.hpp\"\
    \n\n\n\n#line 6 \"monoid/monoids/max_monoid.hpp\"\n\n#line 8 \"monoid/monoids/max_monoid.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename T>\nusing max_monoid =\n    monoid<T,\
    \ [](T a, T b) { return std::max(a, b); }, []() { return std::numeric_limits<T>::min();\
    \ }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/and_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoids/and_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing and_monoid = monoid<T, [](T a, T b) { return a & b; }, []()\
    \ { return ~T(0); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/or_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoids/or_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing or_monoid = monoid<T, [](T a, T b) { return a | b; }, []()\
    \ { return T(0); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/xor_monoid.hpp\"\
    \n\n\n\n#line 5 \"monoid/monoids/xor_monoid.hpp\"\n\nnamespace m1une {\n\ntemplate\
    \ <typename T>\nusing xor_monoid = monoid<T, [](T a, T b) { return a ^ b; }, []()\
    \ { return T(0); }, true>;\n\n}  // namespace m1une\n\n\n#line 1 \"monoid/monoids/affine_monoid.hpp\"\
    \n\n\n\n#include <utility>\n\n#line 7 \"monoid/monoids/affine_monoid.hpp\"\n\n\
    namespace m1une {\n\n// Affine transformation f(x) = ax + b is represented as\
    \ (a, b)\n// perform f first, then g\n// op(f, g)(x) = g(f(x))\ntemplate <typename\
    \ T>\nusing affine_monoid = monoid<std::pair<T, T>,\n                        \
    \     [](std::pair<T, T> f, std::pair<T, T> g) {\n                           \
    \      return std::pair<T, T>(f.first * g.first, f.second * g.first + g.second);\n\
    \                             },\n                             []() { return std::pair<T,\
    \ T>(1, 0); }, false>;\n\n}  // namespace m1une\n\n\n#line 13 \"monoid/monoids/prim_monoids.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_PRIM_MONOIDS_HPP

    #define M1UNE_PRIM_MONOIDS_HPP 1


    #include "../monoid.hpp"

    #include "add_monoid.hpp"

    #include "mul_monoid.hpp"

    #include "min_monoid.hpp"

    #include "max_monoid.hpp"

    #include "and_monoid.hpp"

    #include "or_monoid.hpp"

    #include "xor_monoid.hpp"

    #include "affine_monoid.hpp"


    #endif  // M1UNE_PRIM_MONOIDS_HPP

    '
  dependsOn:
  - monoid/monoid.hpp
  - monoid/monoids/add_monoid.hpp
  - monoid/monoids/mul_monoid.hpp
  - monoid/monoids/min_monoid.hpp
  - monoid/monoids/max_monoid.hpp
  - monoid/monoids/and_monoid.hpp
  - monoid/monoids/or_monoid.hpp
  - monoid/monoids/xor_monoid.hpp
  - monoid/monoids/affine_monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/prim_monoids.hpp
  requiredBy: []
  timestamp: '2025-09-29 00:58:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/prim_monoids.hpp
layout: document
redirect_from:
- /library/monoid/monoids/prim_monoids.hpp
- /library/monoid/monoids/prim_monoids.hpp.html
title: monoid/monoids/prim_monoids.hpp
---
