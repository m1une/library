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
  bundledCode: "#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n};\n\n\
    // Designed to accept Modint or similar types as T\ntemplate <typename T>\nstruct\
    \ RangeAffineRangeSum {\n    using value_type = RangeAffineRangeSumNode<T>;\n\
    \    using operator_type = std::pair<T, T>; // {a, b} for ax + b\n\n    // Value\
    \ Monoid\n    static constexpr value_type id() { return {T(0), 0}; }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.sum + b.sum, a.size + b.size};\n    }\n\n    // Operator Monoid (Affine\
    \ Composition)\n    // f(x) = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x\
    \ + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr operator_type op_id()\
    \ { return {T(1), T(0)}; }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first * g.first, f.first * g.second\
    \ + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum\
    \ x_i + b * size\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return {f.first * x.sum + f.second * T(x.size),\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\
    \ 1\n\n#include <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n\
    };\n\n// Designed to accept Modint or similar types as T\ntemplate <typename T>\n\
    struct RangeAffineRangeSum {\n    using value_type = RangeAffineRangeSumNode<T>;\n\
    \    using operator_type = std::pair<T, T>; // {a, b} for ax + b\n\n    // Value\
    \ Monoid\n    static constexpr value_type id() { return {T(0), 0}; }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.sum + b.sum, a.size + b.size};\n    }\n\n    // Operator Monoid (Affine\
    \ Composition)\n    // f(x) = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x\
    \ + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr operator_type op_id()\
    \ { return {T(1), T(0)}; }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first * g.first, f.first * g.second\
    \ + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum\
    \ x_i + b * size\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return {f.first * x.sum + f.second * T(x.size),\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_AFFINE_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_affine_range_sum.hpp
  requiredBy: []
  timestamp: '2026-06-04 17:06:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_affine_range_sum.hpp
layout: document
redirect_from:
- /library/acted_monoid/range_affine_range_sum.hpp
- /library/acted_monoid/range_affine_range_sum.hpp.html
title: acted_monoid/range_affine_range_sum.hpp
---
