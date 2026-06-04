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
  bundledCode: "#line 1 \"acted_monoid/range_xor_range_xor.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeXorRangeXorNode\
    \ {\n    T val;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeXorRangeXor\
    \ {\n    using value_type = RangeXorRangeXorNode<T>;\n    using operator_type\
    \ = T;\n\n    static constexpr value_type id() { return {T(0), 0}; }\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.val ^ b.val, a.size + b.size};\n    }\n\n    static constexpr operator_type\
    \ op_id() { return T(0); }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return f ^ g;\n    }\n\n    static constexpr\
    \ value_type mapping(const operator_type& f, const value_type& x) {\n        if\
    \ (x.size % 2 == 1) {\n            return {x.val ^ f, x.size};\n        }\n  \
    \      return x;\n    }\n\n    static constexpr value_type make(const T& val)\
    \ {\n        return {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP\n#define M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeXorRangeXorNode {\n    T val;\n    long long size;\n};\n\ntemplate\
    \ <typename T>\nstruct RangeXorRangeXor {\n    using value_type = RangeXorRangeXorNode<T>;\n\
    \    using operator_type = T;\n\n    static constexpr value_type id() { return\
    \ {T(0), 0}; }\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        return {a.val ^ b.val, a.size + b.size};\n    }\n\n\
    \    static constexpr operator_type op_id() { return T(0); }\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f ^ g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (x.size % 2 == 1) {\n            return\
    \ {x.val ^ f, x.size};\n        }\n        return x;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_xor_range_xor.hpp
  requiredBy: []
  timestamp: '2026-06-04 17:32:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/range_xor_range_xor.hpp
layout: document
title: Range Xor Range Xor
---

## Overview

An acted monoid that supports range bitwise XOR operations and range XOR sum queries.

### Important Usage Note

When a value $f$ is XORed to all elements in a segment, the total XOR sum of the segment changes by $f$ only if the segment's length is odd. Therefore, `value_type` holds the size of the segment. Use the `make(val)` helper function to initialize leaf nodes.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_xor_range_xor.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeXorRangeXor<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();
    
    std::vector<AM::value_type> init_nodes(N);
    for(int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }
    
    m1une::data_structure::LazySegtree<AM> seg(init_nodes);

    seg.apply(1, 4, 7);

    std::cout << seg.prod(1, 4).val << "\n";

    return 0;
}
```
