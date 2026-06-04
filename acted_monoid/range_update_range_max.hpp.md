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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_max.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct RangeUpdateRangeMax {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Max)\n    static constexpr value_type\
    \ id() { return Id; }\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        return std::max(a, b);\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() { return std::nullopt;\
    \ }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        // Prioritize the newer operation (f) over the\
    \ older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f.has_value() || x == id()) return x;\n        return f.value();\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct RangeUpdateRangeMax {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Max)\n    static constexpr value_type\
    \ id() { return Id; }\n    static constexpr value_type op(const value_type& a,\
    \ const value_type& b) {\n        return std::max(a, b);\n    }\n\n    // Operator\
    \ Monoid (Update)\n    static constexpr operator_type op_id() { return std::nullopt;\
    \ }\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        // Prioritize the newer operation (f) over the\
    \ older one (g)\n        return f.has_value() ? f : g;\n    }\n\n    // Mapping\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f.has_value() || x == id()) return x;\n        return f.value();\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_max.hpp
  requiredBy: []
  timestamp: '2026-06-04 16:50:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_update_range_max.hpp
layout: document
redirect_from:
- /library/acted_monoid/range_update_range_max.hpp
- /library/acted_monoid/range_update_range_max.hpp.html
title: acted_monoid/range_update_range_max.hpp
---
