---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/min_subarray.hpp
    title: monoid/min_subarray.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/max_subarray.hpp\"\n\n\n\n#line 1 \"monoid/min_subarray.hpp\"\
    \n\n\n\n#include <functional>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Node for managing the optimal subarray sum.\ntemplate <typename\
    \ T>\nstruct SubarrayNode {\n    T sum;\n    T pre;\n    T suf;\n    T opt; //\
    \ Holds the optimal value (e.g., min or max)\n};\n\n// Monoid for finding the\
    \ minimum subarray sum in a range.\n// Uses a comparison functor (Compare) to\
    \ determine the optimal value.\n// Can be reused for maximum subarray sum by changing\
    \ the Compare functor.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()\
    \ / 2, typename Compare = std::less<T>>\nstruct MinSubarray {\n    using value_type\
    \ = SubarrayNode<T>;\n\n    // The identity element contains values that do not\
    \ affect the result.\n    static constexpr value_type id() {\n        return {T(0),\
    \ Id, Id, Id};\n    }\n\n    // Merges two subarray nodes.\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.opt\
    \ == Id) return b;\n        if (b.opt == Id) return a;\n\n        // Lambda to\
    \ select the optimal value according to the comparison functor.\n        auto\
    \ get_opt = [](const T& x, const T& y) {\n            return Compare()(x, y) ?\
    \ x : y;\n        };\n\n        return {\n            a.sum + b.sum,\n       \
    \     get_opt(a.pre, a.sum + b.pre),\n            get_opt(b.suf, a.suf + b.sum),\n\
    \            get_opt(get_opt(a.opt, b.opt), a.suf + b.pre)\n        };\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 7 \"monoid/max_subarray.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for finding the maximum\
    \ subarray sum in a range.\n// Defined as a type alias of MinSubarray using std::greater.\n\
    template <typename T, T Id = std::numeric_limits<T>::lowest() / 2>\nusing MaxSubarray\
    \ = MinSubarray<T, Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: '#ifndef M1UNE_MONOID_MAX_SUBARRAY_HPP

    #define M1UNE_MONOID_MAX_SUBARRAY_HPP 1


    #include "min_subarray.hpp"

    #include <functional>

    #include <limits>


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum subarray sum in a range.

    // Defined as a type alias of MinSubarray using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest() / 2>

    using MaxSubarray = MinSubarray<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_MAX_SUBARRAY_HPP

    '
  dependsOn:
  - monoid/min_subarray.hpp
  isVerificationFile: false
  path: monoid/max_subarray.hpp
  requiredBy: []
  timestamp: '2026-05-28 17:59:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/max_subarray.hpp
layout: document
redirect_from:
- /library/monoid/max_subarray.hpp
- /library/monoid/max_subarray.hpp.html
title: monoid/max_subarray.hpp
---
