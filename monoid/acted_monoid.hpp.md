---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <functional>\n\
    #include <type_traits>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 6 \"monoid/monoid.hpp\"\
    \n#include <concepts>\n\nnamespace m1une {\n\ntemplate <typename T, auto operation,\
    \ auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept monoid_concept = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 8 \"monoid/acted_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <monoid_concept Data, monoid_concept Act, auto mapping>\n\
    struct acted_monoid {\n    using data_type = typename Data::value_type;\n    using\
    \ act_type = typename Act::value_type;\n\n    static_assert(std::is_convertible_v<decltype(mapping),\
    \ std::function<data_type(data_type, act_type)>>,\n                  \"mapping\
    \ must work as data_type(data_type, act_type)\");\n\n    static constexpr auto\
    \ data_op = Data::op;\n    static constexpr auto data_id = Data::id;\n    static\
    \ constexpr bool data_is_commutative = Data::is_commutative;\n    static constexpr\
    \ auto act_op = Act::op;\n    static constexpr auto act_id = Act::id;\n    static\
    \ constexpr bool act_is_commutative = Act::is_commutative;\n    static constexpr\
    \ auto apply = mapping;\n};\n\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_HPP\n#define M1UNE_ACTED_MONOID_HPP 1\n\n#include\
    \ <functional>\n#include <type_traits>\n\n#include \"monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <monoid_concept Data, monoid_concept Act, auto mapping>\n\
    struct acted_monoid {\n    using data_type = typename Data::value_type;\n    using\
    \ act_type = typename Act::value_type;\n\n    static_assert(std::is_convertible_v<decltype(mapping),\
    \ std::function<data_type(data_type, act_type)>>,\n                  \"mapping\
    \ must work as data_type(data_type, act_type)\");\n\n    static constexpr auto\
    \ data_op = Data::op;\n    static constexpr auto data_id = Data::id;\n    static\
    \ constexpr bool data_is_commutative = Data::is_commutative;\n    static constexpr\
    \ auto act_op = Act::op;\n    static constexpr auto act_id = Act::id;\n    static\
    \ constexpr bool act_is_commutative = Act::is_commutative;\n    static constexpr\
    \ auto apply = mapping;\n};\n\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/acted_monoid.hpp
  requiredBy: []
  timestamp: '2025-09-29 01:39:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/acted_monoid.hpp
layout: document
redirect_from:
- /library/monoid/acted_monoid.hpp
- /library/monoid/acted_monoid.hpp.html
title: monoid/acted_monoid.hpp
---
