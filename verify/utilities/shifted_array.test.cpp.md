---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/shifted_array.hpp
    title: Shifted Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
  bundledCode: "#line 1 \"verify/utilities/shifted_array.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"utilities/shifted_array.hpp\"\
    \n\n\n\n#line 6 \"utilities/shifted_array.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\n// `bool` is not supported; use `char` for boolean-like arrays.\n\
    template <typename T>\nstruct ShiftedArray {\n   private:\n    long long _offset;\n\
    \    long long _step;\n    long long _size;\n    std::vector<T> _data;\n\n   \
    \ static long long checked_size(long long L, long long R, long long step) {\n\
    \        if (step <= 0) {\n            throw std::invalid_argument(\"Step must\
    \ be positive\");\n        }\n        if (L > R) {\n            throw std::invalid_argument(\"\
    Left bound must be less than or equal to right bound\");\n        }\n        return\
    \ (R - L) / step + 1;\n    }\n\n    long long to_index(long long i) const {\n\
    \        if (i < _offset) {\n            throw std::out_of_range(\"Index out of\
    \ range\");\n        }\n        long long diff = i - _offset;\n        if (diff\
    \ % _step != 0) {\n            throw std::out_of_range(\"Index is not aligned\
    \ to the step\");\n        }\n        long long index = diff / _step;\n      \
    \  if (index >= _size) {\n            throw std::out_of_range(\"Index out of range\"\
    );\n        }\n        return index;\n    }\n\n   public:\n    // Creates an array\
    \ on the closed interval [L, R] using the given step.\n    ShiftedArray(long long\
    \ L, long long R, T init_value = T(), long long step = 1)\n        : _offset(L),\
    \ _step(step), _size(checked_size(L, R, step)), _data(_size, init_value) {}\n\n\
    \    T& operator[](long long i) {\n        return _data[to_index(i)];\n    }\n\
    \n    const T& operator[](long long i) const {\n        return _data[to_index(i)];\n\
    \    }\n\n    long long index(long long i) const {\n        return to_index(i);\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 7 \"\
    verify/utilities/shifted_array.test.cpp\"\n\nconstexpr long long MAX = 100000;\n\
    \nvoid test_shifted_array_edges() {\n    m1une::utilities::ShiftedArray<int> stepped(-2,\
    \ 4, 0, 2);\n    stepped[-2] = 1;\n    stepped[0] = 2;\n    stepped[4] = 3;\n\
    \    assert(stepped.index(2) == 2);\n    assert(stepped[-2] == 1);\n    assert(stepped[0]\
    \ == 2);\n    assert(stepped[4] == 3);\n\n    bool rejected = false;\n    try\
    \ {\n        (void)stepped[1];\n    } catch (const out_of_range&) {\n        rejected\
    \ = true;\n    }\n    assert(rejected);\n\n    rejected = false;\n    try {\n\
    \        m1une::utilities::ShiftedArray<int> invalid_step(0, 10, 0, 0);\n    }\
    \ catch (const invalid_argument&) {\n        rejected = true;\n    }\n    assert(rejected);\n\
    }\n\nlong long solve(long long l, long long r) {\n    vector<char> is_prime(MAX,\
    \ 1);\n    is_prime[0] = is_prime[1] = 0;\n    m1une::utilities::ShiftedArray<vector<long\
    \ long>> prime_factors(l, r);\n    for (long long p = 2; p * p <= r; ++p) {\n\
    \        if (!is_prime[p]) continue;\n        for (long long x = 2 * p; x < MAX;\
    \ x += p) {\n            is_prime[x] = 0;\n        }\n        for (long long x\
    \ = (l + p - 1) / p * p; x <= r; x += p) {\n            prime_factors[x].emplace_back(p);\n\
    \        }\n    }\n    long long res = 0;\n    for (long long x = l; x <= r; ++x)\
    \ {\n        long long factor_count = 0;\n        long long y = x;\n        for\
    \ (long long p : prime_factors[x]) {\n            while (y % p == 0) {\n     \
    \           y /= p;\n                ++factor_count;\n            }\n        }\n\
    \        if (y > 1) {\n            ++factor_count;\n        }\n        if (is_prime[factor_count])\
    \ {\n            ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n\
    \    test_shifted_array_edges();\n\n    long long l, r;\n    cin >> l >> r;\n\
    \    cout << solve(l, r) << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../utilities/shifted_array.hpp\"\
    \n\nconstexpr long long MAX = 100000;\n\nvoid test_shifted_array_edges() {\n \
    \   m1une::utilities::ShiftedArray<int> stepped(-2, 4, 0, 2);\n    stepped[-2]\
    \ = 1;\n    stepped[0] = 2;\n    stepped[4] = 3;\n    assert(stepped.index(2)\
    \ == 2);\n    assert(stepped[-2] == 1);\n    assert(stepped[0] == 2);\n    assert(stepped[4]\
    \ == 3);\n\n    bool rejected = false;\n    try {\n        (void)stepped[1];\n\
    \    } catch (const out_of_range&) {\n        rejected = true;\n    }\n    assert(rejected);\n\
    \n    rejected = false;\n    try {\n        m1une::utilities::ShiftedArray<int>\
    \ invalid_step(0, 10, 0, 0);\n    } catch (const invalid_argument&) {\n      \
    \  rejected = true;\n    }\n    assert(rejected);\n}\n\nlong long solve(long long\
    \ l, long long r) {\n    vector<char> is_prime(MAX, 1);\n    is_prime[0] = is_prime[1]\
    \ = 0;\n    m1une::utilities::ShiftedArray<vector<long long>> prime_factors(l,\
    \ r);\n    for (long long p = 2; p * p <= r; ++p) {\n        if (!is_prime[p])\
    \ continue;\n        for (long long x = 2 * p; x < MAX; x += p) {\n          \
    \  is_prime[x] = 0;\n        }\n        for (long long x = (l + p - 1) / p * p;\
    \ x <= r; x += p) {\n            prime_factors[x].emplace_back(p);\n        }\n\
    \    }\n    long long res = 0;\n    for (long long x = l; x <= r; ++x) {\n   \
    \     long long factor_count = 0;\n        long long y = x;\n        for (long\
    \ long p : prime_factors[x]) {\n            while (y % p == 0) {\n           \
    \     y /= p;\n                ++factor_count;\n            }\n        }\n   \
    \     if (y > 1) {\n            ++factor_count;\n        }\n        if (is_prime[factor_count])\
    \ {\n            ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n\
    \    test_shifted_array_edges();\n\n    long long l, r;\n    cin >> l >> r;\n\
    \    cout << solve(l, r) << endl;\n}\n"
  dependsOn:
  - utilities/shifted_array.hpp
  isVerificationFile: true
  path: verify/utilities/shifted_array.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/utilities/shifted_array.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/shifted_array.test.cpp
- /verify/verify/utilities/shifted_array.test.cpp.html
title: verify/utilities/shifted_array.test.cpp
---
