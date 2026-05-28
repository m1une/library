---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/arg_min.hpp
    title: ArgMin Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/arg_max.hpp\"\n\n\n\n#line 1 \"monoid/arg_min.hpp\"\
    \n\n\n\n#include <limits>\n#include <utility>\n#include <functional>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the optimal value (minimum\
    \ by default) and its corresponding index.\n// Ties are broken by choosing the\
    \ smaller index.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct ArgMin {\n    using value_type = std::pair<T,\
    \ int>;\n\n    // The identity element uses the Id value and an invalid index.\n\
    \    static constexpr value_type id() {\n        return {Id, -1};\n    }\n\n \
    \   // Merges two elements based on the Compare functor.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (Compare()(a.first,\
    \ b.first)) return a;\n        if (Compare()(b.first, a.first)) return b;\n  \
    \      return (a.second < b.second) ? a : b;\n    }\n\n    // Helper to create\
    \ a leaf node.\n    static constexpr value_type make(const T& val, int index)\
    \ {\n        return {val, index};\n    }\n};\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 7 \"monoid/arg_max.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Monoid for finding the maximum value and its corresponding index.\n\
    // Defined as a type alias of ArgMin using std::greater.\ntemplate <typename T,\
    \ T Id = std::numeric_limits<T>::lowest()>\nusing ArgMax = ArgMin<T, Id, std::greater<T>>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_ARG_MAX_HPP

    #define M1UNE_MONOID_ARG_MAX_HPP 1


    #include "arg_min.hpp"

    #include <limits>

    #include <functional>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum value and its corresponding index.

    // Defined as a type alias of ArgMin using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using ArgMax = ArgMin<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_ARG_MAX_HPP

    '
  dependsOn:
  - monoid/arg_min.hpp
  isVerificationFile: false
  path: monoid/arg_max.hpp
  requiredBy: []
  timestamp: '2026-05-29 03:23:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/arg_max.hpp
layout: document
redirect_from:
- /library/monoid/arg_max.hpp
- /library/monoid/arg_max.hpp.html
title: monoid/arg_max.hpp
---
