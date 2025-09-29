---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/acted_monoids/range_affine_range_minmax.hpp
    title: monoid/acted_monoids/range_affine_range_minmax.hpp
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/minmax_monoid.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n#include <utility>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n\
    #include <functional>\n#include <type_traits>\n#include <concepts>\n\nnamespace\
    \ m1une {\n\ntemplate <typename T, auto operation, auto identity, bool commutative>\n\
    struct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 9 \"monoid/monoids/minmax_monoid.hpp\"\n\
    \nnamespace m1une {\n\n// Monoid for storing both a minimum and maximum value.\n\
    // The operation combines two pairs by taking the component-wise min and max.\n\
    template <typename T>\nusing minmax_monoid =\n    monoid<std::pair<T, T>,\n  \
    \         [](std::pair<T, T> a, std::pair<T, T> b) {\n               return std::pair<T,\
    \ T>(std::min(a.first, b.first), std::max(a.second, b.second));\n           },\n\
    \           []() { return std::pair<T, T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest());\
    \ }, true>;\n\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MINMAX_MONOID_HPP\n#define M1UNE_MINMAX_MONOID_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <utility>\n\n#include \"../monoid.hpp\"\
    \n\nnamespace m1une {\n\n// Monoid for storing both a minimum and maximum value.\n\
    // The operation combines two pairs by taking the component-wise min and max.\n\
    template <typename T>\nusing minmax_monoid =\n    monoid<std::pair<T, T>,\n  \
    \         [](std::pair<T, T> a, std::pair<T, T> b) {\n               return std::pair<T,\
    \ T>(std::min(a.first, b.first), std::max(a.second, b.second));\n           },\n\
    \           []() { return std::pair<T, T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest());\
    \ }, true>;\n\n}  // namespace m1une\n\n#endif  // M1UNE_MINMAX_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/minmax_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_affine_range_minmax.hpp
  - monoid/prim_monoids.hpp
  timestamp: '2025-09-29 19:28:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/minmax_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/minmax_monoid.hpp
- /library/monoid/monoids/minmax_monoid.hpp.html
title: monoid/monoids/minmax_monoid.hpp
---
