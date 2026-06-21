---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: Manacher Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"verify/string/manacher.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n\n#line 1 \"string/manacher.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace string {\n\nstruct ManacherResult\
    \ {\n    // odd[i] is the radius including center i.\n    // The palindrome is\
    \ [i - odd[i] + 1, i + odd[i]).\n    std::vector<int> odd;\n\n    // even[i] is\
    \ the radius centered between i - 1 and i.\n    // The palindrome is [i - even[i],\
    \ i + even[i]).\n    std::vector<int> even;\n\n    int size() const {\n      \
    \  return int(odd.size());\n    }\n\n    bool empty() const {\n        return\
    \ odd.empty();\n    }\n\n    bool is_palindrome(int left, int right) const {\n\
    \        int n = size();\n        assert(0 <= left && left <= right && right <=\
    \ n);\n        int length = right - left;\n        if (length == 0) return true;\n\
    \        if (length & 1) {\n            int center = (left + right) / 2;\n   \
    \         return length / 2 + 1 <= odd[center];\n        }\n        int center\
    \ = (left + right) / 2;\n        return length / 2 <= even[center];\n    }\n\n\
    \    int longest_length() const {\n        int result = 0;\n        for (int radius\
    \ : odd) result = std::max(result, 2 * radius - 1);\n        for (int radius :\
    \ even) result = std::max(result, 2 * radius);\n        return result;\n    }\n\
    };\n\ntemplate <class Sequence>\nManacherResult manacher(const Sequence& sequence)\
    \ {\n    int n = int(sequence.size());\n    ManacherResult result;\n    result.odd.assign(n,\
    \ 0);\n    result.even.assign(n, 0);\n\n    int left = 0;\n    int right = -1;\n\
    \    for (int i = 0; i < n; i++) {\n        int radius = i > right ? 1 : std::min(result.odd[left\
    \ + right - i], right - i + 1);\n        while (\n            0 <= i - radius\
    \ &&\n            i + radius < n &&\n            sequence[i - radius] == sequence[i\
    \ + radius]\n        ) {\n            radius++;\n        }\n        result.odd[i]\
    \ = radius;\n        if (right < i + radius - 1) {\n            left = i - radius\
    \ + 1;\n            right = i + radius - 1;\n        }\n    }\n\n    left = 0;\n\
    \    right = -1;\n    for (int i = 0; i < n; i++) {\n        int radius = i >\
    \ right ? 0 : std::min(result.even[left + right - i + 1], right - i + 1);\n  \
    \      while (\n            0 <= i - radius - 1 &&\n            i + radius < n\
    \ &&\n            sequence[i - radius - 1] == sequence[i + radius]\n        )\
    \ {\n            radius++;\n        }\n        result.even[i] = radius;\n    \
    \    if (right < i + radius - 1) {\n            left = i - radius;\n         \
    \   right = i + radius - 1;\n        }\n    }\n    return result;\n}\n\n}  //\
    \ namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/manacher.test.cpp\"\
    \n\n#include <iostream>\n#include <string>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::string text;\n    std::cin >> text;\n\
    \    m1une::string::ManacherResult result = m1une::string::manacher(text);\n\n\
    \    for (int center = 0; center < 2 * int(text.size()) - 1; center++) {\n   \
    \     if (center != 0) std::cout << ' ';\n        if (center & 1) {\n        \
    \    std::cout << 2 * result.even[(center + 1) / 2];\n        } else {\n     \
    \       std::cout << 2 * result.odd[center / 2] - 1;\n        }\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n\n#include \"../../string/manacher.hpp\"\n\n#include <iostream>\n#include <string>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    m1une::string::ManacherResult\
    \ result = m1une::string::manacher(text);\n\n    for (int center = 0; center <\
    \ 2 * int(text.size()) - 1; center++) {\n        if (center != 0) std::cout <<\
    \ ' ';\n        if (center & 1) {\n            std::cout << 2 * result.even[(center\
    \ + 1) / 2];\n        } else {\n            std::cout << 2 * result.odd[center\
    \ / 2] - 1;\n        }\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - string/manacher.hpp
  isVerificationFile: true
  path: verify/string/manacher.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/manacher.test.cpp
layout: document
redirect_from:
- /verify/verify/string/manacher.test.cpp
- /verify/verify/string/manacher.test.cpp.html
title: verify/string/manacher.test.cpp
---
