---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/shifted-array.hpp
    title: Shifted Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
  bundledCode: "#line 1 \"verify/utilities/shifted-array.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"utilities/shifted-array.hpp\"\
    \n\n\n\n#line 6 \"utilities/shifted-array.hpp\"\n\nnamespace m1une {\n// bool\
    \ is not allowed\n// if you want to use bool, use char instead\ntemplate <typename\
    \ T>\nstruct shifted_array {\n   private:\n    long long _offset;\n    long long\
    \ _step;\n    int _size;\n    std::vector<T> _data;\n\n   public:\n    // make\
    \ an array with indices from L to R (including both L and R)\n    // [L, R] (closed\
    \ interval)\n    shifted_array(long long L, long long R, T init_value = T(),\n\
    \                  long long step = 1)\n        : _offset(L),\n          _step(step),\n\
    \          _size((R - L) / step + 1),\n          _data(_size, init_value) {\n\
    \        if (step <= 0) {\n            throw std::invalid_argument(\"Step must\
    \ be positive\");\n        }\n        if (L > R) {\n            throw std::invalid_argument(\n\
    \                \"Left bound must be less than or equal to right bound\");\n\
    \        }\n    }\n    T &operator[](long long i) {\n        int index = (i -\
    \ _offset) / _step;\n        if (index < 0 || index >= _size) {\n            throw\
    \ std::out_of_range(\"Index out of range\");\n        }\n        return _data[index];\n\
    \    };\n    const T &operator[](long long i) const {\n        int index = (i\
    \ - _offset) / _step;\n        if (index < 0 || index >= _size) {\n          \
    \  throw std::out_of_range(\"Index out of range\");\n        }\n        return\
    \ _data[index];\n    };\n    long long index(long long i) const {\n        int\
    \ index = (i - _offset) / _step;\n        if (index < 0 || index >= _size) {\n\
    \            throw std::out_of_range(\"Index out of range\");\n        }\n   \
    \     return index;\n    }\n};\n\n}  // namespace m1une\n\n\n\n/**\n * @brief\
    \ Shifted Array\n */\n#line 7 \"verify/utilities/shifted-array.test.cpp\"\n\n\
    constexpr long long MAX = 100000;\n\nlong long solve(long long l, long long r)\
    \ {\n    vector<char> is_prime(MAX, 1);\n    is_prime[0] = is_prime[1] = 0;\n\
    \    m1une::shifted_array<vector<long long>> prime_factors(l, r);\n    for (long\
    \ long p = 2; p * p <= r; ++p) {\n        if (!is_prime[p]) continue;\n      \
    \  for (long long x = 2 * p; x < MAX; x += p) {\n            is_prime[x] = 0;\n\
    \        }\n        for (long long x = (l + p - 1) / p * p; x <= r; x += p) {\n\
    \            prime_factors[x].emplace_back(p);\n        }\n    }\n    long long\
    \ res = 0;\n    for (long long x = l; x <= r; ++x) {\n        long long factor_count\
    \ = 0;\n        long long y = x;\n        for (long long p : prime_factors[x])\
    \ {\n            while (y % p == 0) {\n                y /= p;\n             \
    \   ++factor_count;\n            }\n        }\n        if (y > 1) {\n        \
    \    ++factor_count;\n        }\n        if (is_prime[factor_count]) {\n     \
    \       ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n    long\
    \ long l, r;\n    cin >> l >> r;\n    cout << solve(l, r) << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../utilities/shifted-array.hpp\"\
    \n\nconstexpr long long MAX = 100000;\n\nlong long solve(long long l, long long\
    \ r) {\n    vector<char> is_prime(MAX, 1);\n    is_prime[0] = is_prime[1] = 0;\n\
    \    m1une::shifted_array<vector<long long>> prime_factors(l, r);\n    for (long\
    \ long p = 2; p * p <= r; ++p) {\n        if (!is_prime[p]) continue;\n      \
    \  for (long long x = 2 * p; x < MAX; x += p) {\n            is_prime[x] = 0;\n\
    \        }\n        for (long long x = (l + p - 1) / p * p; x <= r; x += p) {\n\
    \            prime_factors[x].emplace_back(p);\n        }\n    }\n    long long\
    \ res = 0;\n    for (long long x = l; x <= r; ++x) {\n        long long factor_count\
    \ = 0;\n        long long y = x;\n        for (long long p : prime_factors[x])\
    \ {\n            while (y % p == 0) {\n                y /= p;\n             \
    \   ++factor_count;\n            }\n        }\n        if (y > 1) {\n        \
    \    ++factor_count;\n        }\n        if (is_prime[factor_count]) {\n     \
    \       ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n    long\
    \ long l, r;\n    cin >> l >> r;\n    cout << solve(l, r) << endl;\n}\n"
  dependsOn:
  - utilities/shifted-array.hpp
  isVerificationFile: true
  path: verify/utilities/shifted-array.test.cpp
  requiredBy: []
  timestamp: '2025-09-25 18:51:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/shifted-array.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/shifted-array.test.cpp
- /verify/verify/utilities/shifted-array.test.cpp.html
title: verify/utilities/shifted-array.test.cpp
---
