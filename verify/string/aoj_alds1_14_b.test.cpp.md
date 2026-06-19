---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"verify/string/aoj_alds1_14_b.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\n\n\
    #line 1 \"string/rolling_hash.hpp\"\n\n\n\n#include <algorithm>\n#include <string>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \n// Standard Rolling Hash for static strings.\n// Precomputes hashes to answer\
    \ substring queries in O(1).\n// Provides advanced operations like LCP, lexicographical\
    \ comparison, and string repetition in O(log N).\ntemplate <long long Base = 10007,\
    \ long long Mod = (1LL << 61) - 1>\nstruct RollingHash {\n    std::string s;\n\
    \    std::vector<long long> hash;\n    std::vector<long long> power;\n\n    RollingHash()\
    \ = default;\n\n    // Constructs the rolling hash table for the given string.\n\
    \    explicit RollingHash(const std::string& str) : s(str) {\n        int n =\
    \ s.size();\n        hash.assign(n + 1, 0);\n        power.assign(n + 1, 1);\n\
    \        for (int i = 0; i < n; ++i) {\n            // Use __int128_t to prevent\
    \ overflow during multiplication\n            hash[i + 1] = (static_cast<__int128_t>(hash[i])\
    \ * Base + s[i]) % Mod;\n            power[i + 1] = (static_cast<__int128_t>(power[i])\
    \ * Base) % Mod;\n        }\n    }\n\n    // Returns the hash of the substring\
    \ S[l..r) in O(1).\n    long long get(int l, int r) const {\n        long long\
    \ res = hash[r] - (static_cast<__int128_t>(hash[l]) * power[r - l]) % Mod;\n \
    \       if (res < 0) res += Mod;\n        return res;\n    }\n\n    // Returns\
    \ the hash of the concatenated substrings S[l1..r1) and S[l2..r2).\n    long long\
    \ concat(int l1, int r1, int l2, int r2) const {\n        long long h1 = get(l1,\
    \ r1);\n        long long h2 = get(l2, r2);\n        return combine(h1, h2, power[r2\
    \ - l2]);\n    }\n\n    // Calculates the Longest Common Prefix (LCP) length of\
    \ S[l1..r1) and S[l2..r2) in O(log N).\n    int lcp(int l1, int r1, int l2, int\
    \ r2) const {\n        int len = std::min(r1 - l1, r2 - l2);\n        int low\
    \ = 0, high = len + 1;\n        while (high - low > 1) {\n            int mid\
    \ = low + (high - low) / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 +\
    \ mid)) {\n                low = mid;\n            } else {\n                high\
    \ = mid;\n            }\n        }\n        return low;\n    }\n\n    // Lexicographically\
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
    \n\n#line 4 \"verify/string/aoj_alds1_14_b.test.cpp\"\n#include <iostream>\n#line\
    \ 6 \"verify/string/aoj_alds1_14_b.test.cpp\"\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nusing RH = m1une::string::RollingHash<10007,\
    \ 2305843009213693951LL>;\n\nint main() {\n    fast_io();\n    std::string T,\
    \ P;\n    std::cin >> T >> P;\n\n    if (T.size() < P.size()) return 0;\n\n  \
    \  RH rh(T);\n\n    long long p_hash = RH::compute_hash(P);\n\n    int n = T.size(),\
    \ m = P.size();\n    for (int i = 0; i <= n - m; ++i) {\n        if (rh.get(i,\
    \ i + m) == p_hash) {\n            std::cout << i << \"\\n\";\n        }\n   \
    \ }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#include \"../../string/rolling_hash.hpp\"\n#include <iostream>\n#include\
    \ <string>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n \
    \   std::cin.tie(nullptr);\n}\n\nusing RH = m1une::string::RollingHash<10007,\
    \ 2305843009213693951LL>;\n\nint main() {\n    fast_io();\n    std::string T,\
    \ P;\n    std::cin >> T >> P;\n\n    if (T.size() < P.size()) return 0;\n\n  \
    \  RH rh(T);\n\n    long long p_hash = RH::compute_hash(P);\n\n    int n = T.size(),\
    \ m = P.size();\n    for (int i = 0; i <= n - m; ++i) {\n        if (rh.get(i,\
    \ i + m) == p_hash) {\n            std::cout << i << \"\\n\";\n        }\n   \
    \ }\n\n    return 0;\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  isVerificationFile: true
  path: verify/string/aoj_alds1_14_b.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/aoj_alds1_14_b.test.cpp
layout: document
redirect_from:
- /verify/verify/string/aoj_alds1_14_b.test.cpp
- /verify/verify/string/aoj_alds1_14_b.test.cpp.html
title: verify/string/aoj_alds1_14_b.test.cpp
---
