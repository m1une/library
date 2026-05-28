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
  bundledCode: "#line 1 \"monoid/rolling_hash.hpp\"\n\n\n\n#include <utility>\n\n\
    namespace m1une {\nnamespace monoid {\n\n// Monoid for Dynamic Rolling Hash (String\
    \ Concatenation).\n// Represented as a pair {hash_value, base_power}.\n// 'Base'\
    \ is the hash base, 'Mod' is the modulo.\n//\n// [Important Usage Note for Contests]\n\
    // To initialize a Segment Tree with a string S, the leaf node for a single\n\
    // character S[i] MUST be initialized as: {S[i], Base % Mod}.\n// \n// Example\
    \ (if Base = 10007):\n//   std::vector<RH::value_type> init_data(N);\n//   for\
    \ (int i = 0; i < N; ++i) {\n//       init_data[i] = {S[i], 10007}; // {char_code,\
    \ Base^1 % Mod}\n//   }\n//   Segtree<RH> seg(init_data);\ntemplate <long long\
    \ Base, long long Mod>\nstruct RollingHash {\n    using value_type = std::pair<long\
    \ long, long long>;\n\n    // The identity element represents an empty string.\n\
    \    // Hash is 0, and Base^0 % Mod is 1.\n    static constexpr value_type id()\
    \ {\n        return {0LL, 1LL};\n    }\n\n    // Combines two hashes (concatenates\
    \ string 'b' to the right of string 'a').\n    // new_hash = (a.hash * b.base_power\
    \ + b.hash) % Mod\n    // new_base_power = (a.base_power * b.base_power) % Mod\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        return {\n            (a.first * b.second + b.first) % Mod,\n   \
    \         (a.second * b.second) % Mod\n        };\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_ROLLING_HASH_HPP\n#define M1UNE_MONOID_ROLLING_HASH_HPP\
    \ 1\n\n#include <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid\
    \ for Dynamic Rolling Hash (String Concatenation).\n// Represented as a pair {hash_value,\
    \ base_power}.\n// 'Base' is the hash base, 'Mod' is the modulo.\n//\n// [Important\
    \ Usage Note for Contests]\n// To initialize a Segment Tree with a string S, the\
    \ leaf node for a single\n// character S[i] MUST be initialized as: {S[i], Base\
    \ % Mod}.\n// \n// Example (if Base = 10007):\n//   std::vector<RH::value_type>\
    \ init_data(N);\n//   for (int i = 0; i < N; ++i) {\n//       init_data[i] = {S[i],\
    \ 10007}; // {char_code, Base^1 % Mod}\n//   }\n//   Segtree<RH> seg(init_data);\n\
    template <long long Base, long long Mod>\nstruct RollingHash {\n    using value_type\
    \ = std::pair<long long, long long>;\n\n    // The identity element represents\
    \ an empty string.\n    // Hash is 0, and Base^0 % Mod is 1.\n    static constexpr\
    \ value_type id() {\n        return {0LL, 1LL};\n    }\n\n    // Combines two\
    \ hashes (concatenates string 'b' to the right of string 'a').\n    // new_hash\
    \ = (a.hash * b.base_power + b.hash) % Mod\n    // new_base_power = (a.base_power\
    \ * b.base_power) % Mod\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {\n            (a.first * b.second\
    \ + b.first) % Mod,\n            (a.second * b.second) % Mod\n        };\n   \
    \ }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_ROLLING_HASH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/rolling_hash.hpp
  requiredBy: []
  timestamp: '2026-05-28 18:13:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/rolling_hash.hpp
layout: document
title: Rolling Hash Monoid
---

## Overview

A monoid for maintaining a dynamic rolling hash of a string on a Segment Tree. This allows you to update characters in $O(\log N)$ and query the hash of any substring in $O(\log N)$.

## Important Usage Note (Initialization)

When initializing the Segment Tree, you must convert each character of the string into the `value_type` pair: `{hash_value, base_power}`. 
For a single character, the string length is 1, so the `base_power` must be exactly `Base % Mod`.

### Example

```cpp
#include "monoid/rolling_hash.hpp"
#include <string>
#include <vector>

// Define the monoid with Base = 10007, Mod = 998244353
using RH = m1une::monoid::RollingHash<10007, 998244353>;

int main() {
    std::string S = "abracadabra";
    int N = S.length();

    // 1. Initialize leaf nodes
    std::vector<RH::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // S[i] acts as the hash value for a single character.
        // 10007 is Base^1 % Mod.
        init_data[i] = {S[i], 10007}; 
    }

    // 2. Build the Segment Tree (assuming m1une::Segtree is available)
    // m1une::Segtree<RH> seg(init_data);

    // 3. Point Update: Change S[1] ('b') to 'x'
    // seg.set(1, {'x', 10007});

    return 0;
}
```
