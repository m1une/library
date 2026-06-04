---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/min_count.hpp
    title: monoid/min_count.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/max_count.hpp\"\n\n\n\n#line 1 \"monoid/min_count.hpp\"\
    \n\n\n\n#include <utility>\n#include <limits>\n#include <functional>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the optimal value and its\
    \ frequency in a range.\n// Uses a comparison functor (Compare) to determine the\
    \ optimal value (default is less, i.e., minimum).\ntemplate <typename T, T Id\
    \ = std::numeric_limits<T>::max(), typename Compare = std::less<T>>\nstruct MinCount\
    \ {\n    using value_type = std::pair<T, int>;\n\n    // The identity element\
    \ has the specified Id value and a count of 0.\n    static constexpr value_type\
    \ id() {\n        return {Id, 0};\n    }\n\n    // Combines two elements, updating\
    \ the optimal value and summing the counts if they are equal.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (Compare()(a.first,\
    \ b.first)) return a;\n        if (Compare()(b.first, a.first)) return b;\n  \
    \      return {a.first, a.second + b.second};\n    }\n\n    // Helper to securely\
    \ create a leaf node from a single value.\n    static constexpr value_type make(const\
    \ T& val, int count = 1) {\n        return {val, count};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n#line 7 \"monoid/max_count.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the maximum value and its\
    \ frequency in a range.\n// Defined as a type alias of MinCount using std::greater.\n\
    template <typename T, T Id = std::numeric_limits<T>::lowest()>\nusing MaxCount\
    \ = MinCount<T, Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_MAX_COUNT_HPP

    #define M1UNE_MONOID_MAX_COUNT_HPP 1


    #include "min_count.hpp"

    #include <limits>

    #include <functional>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum value and its frequency in a range.

    // Defined as a type alias of MinCount using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using MaxCount = MinCount<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_MAX_COUNT_HPP

    '
  dependsOn:
  - monoid/min_count.hpp
  isVerificationFile: false
  path: monoid/max_count.hpp
  requiredBy: []
  timestamp: '2026-06-04 16:59:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max_count.hpp
layout: document
redirect_from:
- /library/monoid/max_count.hpp
- /library/monoid/max_count.hpp.html
title: monoid/max_count.hpp
---
