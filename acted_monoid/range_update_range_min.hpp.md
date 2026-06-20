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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_min.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct RangeUpdateRangeMin {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Min)\n    static constexpr value_type\
    \ id() {\n        return Id;\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return std::min(a, b);\n    }\n\
    \n    // Operator Monoid (Update)\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        // Prioritize the newer\
    \ operation (f) over the older one (g)\n        return f.has_value() ? f : g;\n\
    \    }\n\n    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x == id()) return x;\n\
    \        return f.value();\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MIN_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MIN_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n#include <optional>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct RangeUpdateRangeMin {\n    using value_type = T;\n    using operator_type\
    \ = std::optional<T>;\n\n    // Value Monoid (Min)\n    static constexpr value_type\
    \ id() {\n        return Id;\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return std::min(a, b);\n    }\n\
    \n    // Operator Monoid (Update)\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        // Prioritize the newer\
    \ operation (f) over the older one (g)\n        return f.has_value() ? f : g;\n\
    \    }\n\n    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x == id()) return x;\n\
    \        return f.value();\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_min.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_update_range_min.hpp
layout: document
title: Range Update Range Min
---

## Overview

An Acted Monoid representing Range Update (overwrite/assignment) operations and Range Minimum queries.

### Important Usage Note

This implementation uses `std::optional<T>` as the `operator_type` to safely represent the state of "no operation" (the identity element of the operator monoid).

- A valid update operation with value $v$ is represented as `std::optional<T>(v)`.
- The identity operator (no operation) is represented as `std::nullopt`.

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Example

```cpp
#include "ds/segment_tree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 5 -> {10, 5, 5, 5, 50}
    seg.apply(1, 4, std::optional<long long>(5));

    // Get the minimum in range [0, 5) -> min(10, 5, 5, 5, 50) = 5
    std::cout << seg.prod(0, 5) << "\n";

    return 0;
}
```
