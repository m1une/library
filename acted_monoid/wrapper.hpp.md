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
  bundledCode: "#line 1 \"acted_monoid/wrapper.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\n// Wrapper struct to generate an Acted Monoid using Non-Type\
    \ Template Parameters (NTTP).\n// Useful for quickly defining acted monoids using\
    \ custom functions or constexpr lambdas during contests.\ntemplate <\n    typename\
    \ T, \n    typename E, \n    auto Op, \n    auto Id, \n    auto OpComp, \n   \
    \ auto OpId, \n    auto Mapping\n>\nstruct Wrapper {\n    using value_type = T;\n\
    \    using operator_type = E;\n\n    // Returns the identity element of the value\
    \ monoid.\n    static constexpr T id() {\n        return Id();\n    }\n\n    //\
    \ Returns the result of the value monoid binary operation.\n    static constexpr\
    \ T op(const T& a, const T& b) {\n        return Op(a, b);\n    }\n\n    // Returns\
    \ the identity element of the operator monoid.\n    static constexpr E op_id()\
    \ {\n        return OpId();\n    }\n\n    // Composes two operations f and g (corresponds\
    \ to f(g(x))).\n    static constexpr E op_comp(const E& f, const E& g) {\n   \
    \     return OpComp(f, g);\n    }\n\n    // Applies the operator f onto the value\
    \ x.\n    static constexpr T mapping(const E& f, const T& x) {\n        return\
    \ Mapping(f, x);\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_WRAPPER_HPP\n#define M1UNE_ACTED_MONOID_WRAPPER_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Wrapper struct to generate\
    \ an Acted Monoid using Non-Type Template Parameters (NTTP).\n// Useful for quickly\
    \ defining acted monoids using custom functions or constexpr lambdas during contests.\n\
    template <\n    typename T, \n    typename E, \n    auto Op, \n    auto Id, \n\
    \    auto OpComp, \n    auto OpId, \n    auto Mapping\n>\nstruct Wrapper {\n \
    \   using value_type = T;\n    using operator_type = E;\n\n    // Returns the\
    \ identity element of the value monoid.\n    static constexpr T id() {\n     \
    \   return Id();\n    }\n\n    // Returns the result of the value monoid binary\
    \ operation.\n    static constexpr T op(const T& a, const T& b) {\n        return\
    \ Op(a, b);\n    }\n\n    // Returns the identity element of the operator monoid.\n\
    \    static constexpr E op_id() {\n        return OpId();\n    }\n\n    // Composes\
    \ two operations f and g (corresponds to f(g(x))).\n    static constexpr E op_comp(const\
    \ E& f, const E& g) {\n        return OpComp(f, g);\n    }\n\n    // Applies the\
    \ operator f onto the value x.\n    static constexpr T mapping(const E& f, const\
    \ T& x) {\n        return Mapping(f, x);\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_WRAPPER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/wrapper.hpp
  requiredBy: []
  timestamp: '2026-06-04 16:47:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/wrapper.hpp
layout: document
redirect_from:
- /library/acted_monoid/wrapper.hpp
- /library/acted_monoid/wrapper.hpp.html
title: acted_monoid/wrapper.hpp
---
