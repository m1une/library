---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: monoid/rolling_hash.hpp
    title: Rolling Hash Monoid
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/aoj_alds1_14_b.test.cpp
    title: verify/string/aoj_alds1_14_b.test.cpp
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/rolling_hash.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <string>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
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
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_ROLLING_HASH_HPP\n#define M1UNE_STRING_ROLLING_HASH_HPP\
    \ 1\n\n#include <algorithm>\n#include <string>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\n// Standard Rolling Hash for static\
    \ strings.\n// Precomputes hashes to answer substring queries in O(1).\n// Provides\
    \ advanced operations like LCP, lexicographical comparison, and string repetition\
    \ in O(log N).\ntemplate <long long Base = 10007, long long Mod = (1LL << 61)\
    \ - 1>\nstruct RollingHash {\n    std::string s;\n    std::vector<long long> hash;\n\
    \    std::vector<long long> power;\n\n    RollingHash() = default;\n\n    // Constructs\
    \ the rolling hash table for the given string.\n    explicit RollingHash(const\
    \ std::string& str) : s(str) {\n        int n = s.size();\n        hash.assign(n\
    \ + 1, 0);\n        power.assign(n + 1, 1);\n        for (int i = 0; i < n; ++i)\
    \ {\n            // Use __int128_t to prevent overflow during multiplication\n\
    \            hash[i + 1] = (static_cast<__int128_t>(hash[i]) * Base + s[i]) %\
    \ Mod;\n            power[i + 1] = (static_cast<__int128_t>(power[i]) * Base)\
    \ % Mod;\n        }\n    }\n\n    // Returns the hash of the substring S[l..r)\
    \ in O(1).\n    long long get(int l, int r) const {\n        long long res = hash[r]\
    \ - (static_cast<__int128_t>(hash[l]) * power[r - l]) % Mod;\n        if (res\
    \ < 0) res += Mod;\n        return res;\n    }\n\n    // Returns the hash of the\
    \ concatenated substrings S[l1..r1) and S[l2..r2).\n    long long concat(int l1,\
    \ int r1, int l2, int r2) const {\n        long long h1 = get(l1, r1);\n     \
    \   long long h2 = get(l2, r2);\n        return combine(h1, h2, power[r2 - l2]);\n\
    \    }\n\n    // Calculates the Longest Common Prefix (LCP) length of S[l1..r1)\
    \ and S[l2..r2) in O(log N).\n    int lcp(int l1, int r1, int l2, int r2) const\
    \ {\n        int len = std::min(r1 - l1, r2 - l2);\n        int low = 0, high\
    \ = len + 1;\n        while (high - low > 1) {\n            int mid = low + (high\
    \ - low) / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 + mid)) {\n   \
    \             low = mid;\n            } else {\n                high = mid;\n\
    \            }\n        }\n        return low;\n    }\n\n    // Lexicographically\
    \ compares S[l1..r1) and S[l2..r2) in O(log N).\n    // Returns -1 if S[l1..r1)\
    \ < S[l2..r2), 0 if equal, and 1 if S[l1..r1) > S[l2..r2).\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int l = lcp(l1, r1, l2, r2);\n\
    \        bool end1 = (l1 + l == r1);\n        bool end2 = (l2 + l == r2);\n  \
    \      if (end1 && end2) return 0;\n        if (end1) return -1;\n        if (end2)\
    \ return 1;\n        return s[l1 + l] < s[l2 + l] ? -1 : 1;\n    }\n\n    // Returns\
    \ the hash of the substring S[l..r) repeated 'k' times.\n    long long repeat(int\
    \ l, int r, long long k) const {\n        long long h = get(l, r);\n        long\
    \ long p = power[r - l];\n        return repeat_hash(h, p, k);\n    }\n\n    //\
    \ --- Static Helpers for dynamic processing and Monoid integration ---\n\n   \
    \ // Computes the hash of a single string in O(N) time and O(1) space.\n    static\
    \ long long compute_hash(const std::string& str) {\n        long long h = 0;\n\
    \        for (char c : str) {\n            h = (static_cast<__int128_t>(h) * Base\
    \ + c) % Mod;\n        }\n        return h;\n    }\n\n    // Combines two hashes.\
    \ Equivalent to concatenating string 'b' to the right of string 'a'.\n    static\
    \ constexpr long long combine(long long h1, long long h2, long long base_power2)\
    \ {\n        return (static_cast<__int128_t>(h1) * base_power2 + h2) % Mod;\n\
    \    }\n\n    // Returns the hash of a string (with hash 'h' and base_power 'p')\
    \ repeated 'k' times.\n    static constexpr long long repeat_hash(long long h,\
    \ long long p, long long k) {\n        long long res_h = 0;\n        long long\
    \ res_p = 1;\n        long long cur_h = h;\n        long long cur_p = p;\n   \
    \     while (k > 0) {\n            if (k & 1) {\n                res_h = combine(res_h,\
    \ cur_h, cur_p);\n                res_p = (static_cast<__int128_t>(res_p) * cur_p)\
    \ % Mod;\n            }\n            cur_h = combine(cur_h, cur_h, cur_p);\n \
    \           cur_p = (static_cast<__int128_t>(cur_p) * cur_p) % Mod;\n        \
    \    k >>= 1;\n        }\n        return res_h;\n    }\n\n    // Creates the state\
    \ pair {hash_value, base_power} for a single character.\n    static constexpr\
    \ std::pair<long long, long long> make_single(long long c) {\n        return {c\
    \ % Mod, Base % Mod};\n    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\
    \n#endif  // M1UNE_STRING_ROLLING_HASH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash.hpp
  requiredBy:
  - monoid/rolling_hash.hpp
  - string/all.hpp
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/aoj_alds1_14_b.test.cpp
documentation_of: string/rolling_hash.hpp
layout: document
title: Static Rolling Hash
---

## Overview

A robust data structure that precomputes the hash values of a string's prefixes to answer substring hash queries in $O(1)$ time. It uses `__int128_t` internally to safely prevent integer overflow.

In addition to standard substring hashes, this class supports advanced operations such as finding the Longest Common Prefix (LCP), lexicographical comparison, and string repetition in $O(\log N)$ time. It also provides static helpers for calculating hashes dynamically and powering the `monoid::RollingHash`.

## Template Parameters

* `Base`: The hash base. Default is `10007`.
* `Mod`: The modulo for the hash. Default is `(1LL << 61) - 1` (a Mersenne prime for extreme collision resistance).

## Instance Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `RollingHash(const std::string& s)` | Builds prefix hashes and base powers for `s`, and keeps a copy for character comparisons. | $O(N)$ time and space |
| `long long get(int l, int r) const` | Returns the hash of substring `[l, r)`. | $O(1)$ |
| `long long concat(int l1, int r1, int l2, int r2) const` | Returns the hash of `[l1, r1)` followed by `[l2, r2)`. | $O(1)$ |
| `int lcp(int l1, int r1, int l2, int r2) const` | Returns the longest common prefix length of two substrings. | $O(\log(\min(r1 - l1, r2 - l2)))$ |
| `int compare(int l1, int r1, int l2, int r2) const` | Lexicographically compares two substrings. Returns `-1`, `0`, or `1`. | $O(\log N)$ |
| `long long repeat(int l, int r, long long k) const` | Returns the hash of substring `[l, r)` repeated `k` times. | $O(\log k)$ |

## Static Helper Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `static long long compute_hash(const std::string& str)` | Computes the hash of `str` without building prefix arrays. | $O(N)$ time, $O(1)$ auxiliary space |
| `static constexpr long long combine(long long h1, long long h2, long long base_power2)` | Returns the hash of a left string with hash `h1` followed by a right string with hash `h2`. `base_power2` is $Base^{\text{right length}} \bmod Mod$. | $O(1)$ |
| `static constexpr long long repeat_hash(long long h, long long p, long long k)` | Returns the hash of a string with hash `h` repeated `k` times. `p` is $Base^{\text{string length}} \bmod Mod$. | $O(\log k)$ |

## Example

```cpp
#include "string/rolling_hash.hpp"
#include <iostream>
#include <string>

using RH = m1une::string::RollingHash<10007, 998244353>;

int main() {
    std::string S = "abracadabra";
    RH rh(S);

    // Basic substring hash
    std::cout << (rh.get(0, 3) == rh.get(7, 10)) << "\n"; // Output: 1 (True, "abr" == "abr")

    // LCP of S[0..4] ("abrac") and S[7..11] ("abra")
    std::cout << rh.lcp(0, 5, 7, 11) << "\n"; // Output: 4

    // Lexicographical compare ("abrac" > "abra")
    std::cout << rh.compare(0, 5, 7, 11) << "\n"; // Output: 1

    // Substring repetition (Hash of "abr" repeated 100 times)
    long long repeated = rh.repeat(0, 3, 100);

    // Static compute hash (O(1) space)
    long long pattern = RH::compute_hash("cad");
    std::cout << repeated << " " << pattern << "\n";

    return 0;
}
```
