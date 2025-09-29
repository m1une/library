---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/acted_monoids/range_add_range_max.hpp
    title: monoid/acted_monoids/range_add_range_max.hpp
  - icon: ':warning:'
    path: monoid/acted_monoids/range_update_range_max.hpp
    title: monoid/acted_monoids/range_update_range_max.hpp
  - icon: ':warning:'
    path: monoid/prim_acted_monoids.hpp
    title: monoid/prim_acted_monoids.hpp
  - icon: ':warning:'
    path: monoid/prim_monoids.hpp
    title: monoid/prim_monoids.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/monoids/max_monoid.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#include <functional>\n\
    #include <type_traits>\n#include <concepts>\n\nnamespace m1une {\n\ntemplate <typename\
    \ T, auto operation, auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept monoid_concept = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 8 \"monoid/monoids/max_monoid.hpp\"\n\n\
    namespace m1une {\n\ntemplate <typename T>\nusing max_monoid =\n    monoid<T,\
    \ [](T a, T b) { return std::max(a, b); }, []() { return std::numeric_limits<T>::min();\
    \ }, true>;\n\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MAX_MONOID_HPP\n#define M1UNE_MAX_MONOID_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\n#include \"../monoid.hpp\"\n\nnamespace m1une\
    \ {\n\ntemplate <typename T>\nusing max_monoid =\n    monoid<T, [](T a, T b) {\
    \ return std::max(a, b); }, []() { return std::numeric_limits<T>::min(); }, true>;\n\
    \n}  // namespace m1une\n\n#endif  // M1UNE_MAX_MONOID_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  isVerificationFile: false
  path: monoid/monoids/max_monoid.hpp
  requiredBy:
  - monoid/acted_monoids/range_update_range_max.hpp
  - monoid/acted_monoids/range_add_range_max.hpp
  - monoid/prim_acted_monoids.hpp
  - monoid/prim_monoids.hpp
  timestamp: '2025-09-29 01:30:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/monoids/max_monoid.hpp
layout: document
redirect_from:
- /library/monoid/monoids/max_monoid.hpp
- /library/monoid/monoids/max_monoid.hpp.html
title: monoid/monoids/max_monoid.hpp
---
