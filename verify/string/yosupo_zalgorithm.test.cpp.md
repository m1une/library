---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: Z Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"verify/string/yosupo_zalgorithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#line 1 \"string/z_algorithm.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ string {\n\n// Returns z[i] = LCP(sequence, sequence[i..]).\ntemplate <class\
    \ Sequence>\nstd::vector<int> z_algorithm(const Sequence& sequence) {\n    int\
    \ n = int(sequence.size());\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ z(n);\n    z[0] = n;\n    int left = 0;\n    int right = 0;\n    for (int i\
    \ = 1; i < n; i++) {\n        if (i < right) z[i] = std::min(right - i, z[i -\
    \ left]);\n        while (i + z[i] < n && sequence[z[i]] == sequence[i + z[i]])\
    \ {\n            z[i]++;\n        }\n        if (right < i + z[i]) {\n       \
    \     left = i;\n            right = i + z[i];\n        }\n    }\n    return z;\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/yosupo_zalgorithm.test.cpp\"\
    \n#include <iostream>\n#include <string>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n    std::string\
    \ S;\n    std::cin >> S;\n    std::vector<int> z = m1une::string::z_algorithm(S);\n\
    \    for (int i = 0; i < int(z.size()); ++i) {\n        std::cout << z[i] << (i\
    \ + 1 == int(z.size()) ? \"\" : \" \");\n    }\n    std::cout << \"\\n\";\n\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"../../string/z_algorithm.hpp\"\n#include <iostream>\n#include <string>\n\n\
    void fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n    std::string S;\n    std::cin >> S;\n  \
    \  std::vector<int> z = m1une::string::z_algorithm(S);\n    for (int i = 0; i\
    \ < int(z.size()); ++i) {\n        std::cout << z[i] << (i + 1 == int(z.size())\
    \ ? \"\" : \" \");\n    }\n    std::cout << \"\\n\";\n\n    return 0;\n}\n"
  dependsOn:
  - string/z_algorithm.hpp
  isVerificationFile: true
  path: verify/string/yosupo_zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/yosupo_zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/verify/string/yosupo_zalgorithm.test.cpp
- /verify/verify/string/yosupo_zalgorithm.test.cpp.html
title: verify/string/yosupo_zalgorithm.test.cpp
---
