---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: data_structure/lazy_segtree.hpp
    title: Lazy Segment Tree
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\n\
    namespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(\n\
    \    typename AM::value_type a, typename AM::value_type b,\n    typename AM::operator_type\
    \ f, typename AM::operator_type g\n) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \ // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_CONCEPT_HPP\n#define M1UNE_ACTED_MONOID_CONCEPT_HPP\
    \ 1\n\n#include <concepts>\n\nnamespace m1une {\nnamespace acted_monoid {\n\n\
    // Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(\n    typename AM::value_type a, typename\
    \ AM::value_type b,\n    typename AM::operator_type f, typename AM::operator_type\
    \ g\n) {\n    // 1. Value Monoid\n    typename AM::value_type;\n    { AM::id()\
    \ } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename\
    \ AM::value_type>;\n\n    // 2. Operator Monoid\n    typename AM::operator_type;\n\
    \    { AM::op_id() } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f,\
    \ g) } -> std::same_as<typename AM::operator_type>; // Composition order: f(g(x))\n\
    \n    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ACTED_MONOID_CONCEPT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/concept.hpp
  requiredBy:
  - data_structure/lazy_segtree.hpp
  timestamp: '2026-06-04 16:47:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/concept.hpp
layout: document
redirect_from:
- /library/acted_monoid/concept.hpp
- /library/acted_monoid/concept.hpp.html
title: acted_monoid/concept.hpp
---
