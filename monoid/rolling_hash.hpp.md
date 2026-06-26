---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/rolling_hash.hpp\"\n\n\n\n#include <utility>\n\n\
    #line 1 \"string/rolling_hash.hpp\"\n\n\n\n#include <algorithm>\n#include <string>\n\
    #line 7 \"string/rolling_hash.hpp\"\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\n// Standard Rolling Hash for static strings.\n// Precomputes\
    \ hashes to answer substring queries in O(1).\n// Provides advanced operations\
    \ like LCP, lexicographical comparison, and string repetition in O(log N).\ntemplate\
    \ <long long Base = 10007, long long Mod = (1LL << 61) - 1>\nstruct RollingHash\
    \ {\n    std::string s;\n    std::vector<long long> hash;\n    std::vector<long\
    \ long> power;\n\n    RollingHash() = default;\n\n    // Constructs the rolling\
    \ hash table for the given string.\n    explicit RollingHash(const std::string&\
    \ str) : s(str) {\n        int n = s.size();\n        hash.assign(n + 1, 0);\n\
    \        power.assign(n + 1, 1);\n        for (int i = 0; i < n; ++i) {\n    \
    \        // Use __int128_t to prevent overflow during multiplication\n       \
    \     hash[i + 1] = (static_cast<__int128_t>(hash[i]) * Base + s[i]) % Mod;\n\
    \            power[i + 1] = (static_cast<__int128_t>(power[i]) * Base) % Mod;\n\
    \        }\n    }\n\n    // Returns the hash of the substring S[l..r) in O(1).\n\
    \    long long get(int l, int r) const {\n        long long res = hash[r] - (static_cast<__int128_t>(hash[l])\
    \ * power[r - l]) % Mod;\n        if (res < 0) res += Mod;\n        return res;\n\
    \    }\n\n    // Returns the hash of the concatenated substrings S[l1..r1) and\
    \ S[l2..r2).\n    long long concat(int l1, int r1, int l2, int r2) const {\n \
    \       long long h1 = get(l1, r1);\n        long long h2 = get(l2, r2);\n   \
    \     return combine(h1, h2, power[r2 - l2]);\n    }\n\n    // Calculates the\
    \ Longest Common Prefix (LCP) length of S[l1..r1) and S[l2..r2) in O(log N).\n\
    \    int lcp(int l1, int r1, int l2, int r2) const {\n        int len = std::min(r1\
    \ - l1, r2 - l2);\n        int low = 0, high = len + 1;\n        while (high -\
    \ low > 1) {\n            int mid = low + (high - low) / 2;\n            if (get(l1,\
    \ l1 + mid) == get(l2, l2 + mid)) {\n                low = mid;\n            }\
    \ else {\n                high = mid;\n            }\n        }\n        return\
    \ low;\n    }\n\n    // Lexicographically compares S[l1..r1) and S[l2..r2) in\
    \ O(log N).\n    // Returns -1 if S[l1..r1) < S[l2..r2), 0 if equal, and 1 if\
    \ S[l1..r1) > S[l2..r2).\n    int compare(int l1, int r1, int l2, int r2) const\
    \ {\n        int l = lcp(l1, r1, l2, r2);\n        bool end1 = (l1 + l == r1);\n\
    \        bool end2 = (l2 + l == r2);\n        if (end1 && end2) return 0;\n  \
    \      if (end1) return -1;\n        if (end2) return 1;\n        return s[l1\
    \ + l] < s[l2 + l] ? -1 : 1;\n    }\n\n    // Returns the hash of the substring\
    \ S[l..r) repeated 'k' times.\n    long long repeat(int l, int r, long long k)\
    \ const {\n        long long h = get(l, r);\n        long long p = power[r - l];\n\
    \        return repeat_hash(h, p, k);\n    }\n\n    // --- Static Helpers for\
    \ dynamic processing and Monoid integration ---\n\n    // Computes the hash of\
    \ a single string in O(N) time and O(1) space.\n    static long long compute_hash(const\
    \ std::string& str) {\n        long long h = 0;\n        for (char c : str) {\n\
    \            h = (static_cast<__int128_t>(h) * Base + c) % Mod;\n        }\n \
    \       return h;\n    }\n\n    // Combines two hashes. Equivalent to concatenating\
    \ string 'b' to the right of string 'a'.\n    static constexpr long long combine(long\
    \ long h1, long long h2, long long base_power2) {\n        return (static_cast<__int128_t>(h1)\
    \ * base_power2 + h2) % Mod;\n    }\n\n    // Returns the hash of a string (with\
    \ hash 'h' and base_power 'p') repeated 'k' times.\n    static constexpr long\
    \ long repeat_hash(long long h, long long p, long long k) {\n        long long\
    \ res_h = 0;\n        long long res_p = 1;\n        long long cur_h = h;\n   \
    \     long long cur_p = p;\n        while (k > 0) {\n            if (k & 1) {\n\
    \                res_h = combine(res_h, cur_h, cur_p);\n                res_p\
    \ = (static_cast<__int128_t>(res_p) * cur_p) % Mod;\n            }\n         \
    \   cur_h = combine(cur_h, cur_h, cur_p);\n            cur_p = (static_cast<__int128_t>(cur_p)\
    \ * cur_p) % Mod;\n            k >>= 1;\n        }\n        return res_h;\n  \
    \  }\n\n    // Creates the state pair {hash_value, base_power} for a single character.\n\
    \    static constexpr std::pair<long long, long long> make_single(long long c)\
    \ {\n        return {c % Mod, Base % Mod};\n    }\n};\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 7 \"monoid/rolling_hash.hpp\"\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for Dynamic Rolling Hash (String Concatenation).\n\
    // Acts as a clean wrapper around the mathematical logic defined in string::RollingHash.\n\
    //\n// [Important Usage Note for Contests]\n// To initialize a leaf node for a\
    \ single character S[i], use the `make` method:\n//\n// Example:\n//   std::vector<RH::value_type>\
    \ init_data(N);\n//   for (int i = 0; i < N; ++i) {\n//       init_data[i] = RH::make(S[i]);\n\
    //   }\n//   Segtree<RH> seg(init_data);\ntemplate <long long Base = 10007, long\
    \ long Mod = (1LL << 61) - 1>\nstruct RollingHash {\n    using StringRH = m1une::string::RollingHash<Base,\
    \ Mod>;\n    using value_type = std::pair<long long, long long>;\n\n    // The\
    \ identity element represents an empty string.\n    static constexpr value_type\
    \ id() {\n        return {0LL, 1LL};\n    }\n\n    // Combines two hashes by delegating\
    \ to string::RollingHash.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {StringRH::combine(a.first, b.first,\
    \ b.second), (static_cast<__int128_t>(a.second) * b.second) % Mod};\n    }\n\n\
    \    // Helper to securely create a monoid element from a single character (or\
    \ integer).\n    // Delegates to string::RollingHash to hide the base/mod mechanics.\n\
    \    static constexpr value_type make(long long c) {\n        return StringRH::make_single(c);\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_ROLLING_HASH_HPP\n#define M1UNE_MONOID_ROLLING_HASH_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../string/rolling_hash.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for Dynamic Rolling Hash (String Concatenation).\n\
    // Acts as a clean wrapper around the mathematical logic defined in string::RollingHash.\n\
    //\n// [Important Usage Note for Contests]\n// To initialize a leaf node for a\
    \ single character S[i], use the `make` method:\n//\n// Example:\n//   std::vector<RH::value_type>\
    \ init_data(N);\n//   for (int i = 0; i < N; ++i) {\n//       init_data[i] = RH::make(S[i]);\n\
    //   }\n//   Segtree<RH> seg(init_data);\ntemplate <long long Base = 10007, long\
    \ long Mod = (1LL << 61) - 1>\nstruct RollingHash {\n    using StringRH = m1une::string::RollingHash<Base,\
    \ Mod>;\n    using value_type = std::pair<long long, long long>;\n\n    // The\
    \ identity element represents an empty string.\n    static constexpr value_type\
    \ id() {\n        return {0LL, 1LL};\n    }\n\n    // Combines two hashes by delegating\
    \ to string::RollingHash.\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {StringRH::combine(a.first, b.first,\
    \ b.second), (static_cast<__int128_t>(a.second) * b.second) % Mod};\n    }\n\n\
    \    // Helper to securely create a monoid element from a single character (or\
    \ integer).\n    // Delegates to string::RollingHash to hide the base/mod mechanics.\n\
    \    static constexpr value_type make(long long c) {\n        return StringRH::make_single(c);\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_ROLLING_HASH_HPP\n"
  dependsOn:
  - string/rolling_hash.hpp
  isVerificationFile: false
  path: monoid/rolling_hash.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/rolling_hash.hpp
layout: document
title: Rolling Hash Monoid
---

## Overview

A monoid for maintaining a dynamic rolling hash of a string on a Segment Tree. This allows you to update characters in $O(\log N)$ and query the hash of any substring in $O(\log N)$.

By default, it uses $Base = 10007$ and $Mod = 2^{61}-1$ (a Mersenne prime), which provides extreme collision resistance and avoids the need to specify them manually.

## Data Structure

* `using value_type = std::pair<long long, long long>;`
  The state maintained in each node of the Segment Tree.
  * `first`: The hash value of the string segment.
  * `second`: The base power, calculated as $Base^{\text{length of the segment}} \pmod{Mod}$.

## Initialization & Element Creation

When initializing the Segment Tree or updating a single point, you must convert a single character into the `value_type` pair.
**Always use the `make(c)` helper method** to automatically generate the correct element.

### `static constexpr value_type make(long long c)`

Generates a valid monoid element for a single character.

* **Parameters:** `c` is the character code (or integer) for one element.
* **Returns:** A `value_type` pair initialized as `{c % Mod, Base % Mod}`.

### Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/rolling_hash.hpp"
#include <iostream>
#include <string>
#include <vector>

// Use the default Base and Mod by providing empty angle brackets <>
using RHMonoid = m1une::monoid::RollingHash<>;

int main() {
    std::string S = "abracadabra";
    int N = S.length();

    // 1. Initialize leaf nodes securely using `make`
    std::vector<RHMonoid::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Pass the character S[i] to `make`
        init_data[i] = RHMonoid::make(S[i]);
    }

    // 2. Build the Segment Tree
    m1une::ds::Segtree<RHMonoid> seg(init_data);

    // 3. Point Update: Change S[1] ('b') to 'x' using `make`
    seg.set(1, RHMonoid::make('x'));

    // 4. Query Range: Get the hash of S[0..4] (indices [0, 5))
    // The returned value is a pair. Extract `.first` to get the actual hash.
    long long hash_val = seg.prod(0, 5).first;
    std::cout << hash_val << "\n";

    return 0;
}
```

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
