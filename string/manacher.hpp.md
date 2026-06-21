---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/manacher.test.cpp
    title: verify/string/manacher.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/manacher.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\nstruct\
    \ ManacherResult {\n    // odd[i] is the radius including center i.\n    // The\
    \ palindrome is [i - odd[i] + 1, i + odd[i]).\n    std::vector<int> odd;\n\n \
    \   // even[i] is the radius centered between i - 1 and i.\n    // The palindrome\
    \ is [i - even[i], i + even[i]).\n    std::vector<int> even;\n\n    int size()\
    \ const {\n        return int(odd.size());\n    }\n\n    bool empty() const {\n\
    \        return odd.empty();\n    }\n\n    bool is_palindrome(int left, int right)\
    \ const {\n        int n = size();\n        assert(0 <= left && left <= right\
    \ && right <= n);\n        int length = right - left;\n        if (length == 0)\
    \ return true;\n        if (length & 1) {\n            int center = (left + right)\
    \ / 2;\n            return length / 2 + 1 <= odd[center];\n        }\n       \
    \ int center = (left + right) / 2;\n        return length / 2 <= even[center];\n\
    \    }\n\n    int longest_length() const {\n        int result = 0;\n        for\
    \ (int radius : odd) result = std::max(result, 2 * radius - 1);\n        for (int\
    \ radius : even) result = std::max(result, 2 * radius);\n        return result;\n\
    \    }\n};\n\ntemplate <class Sequence>\nManacherResult manacher(const Sequence&\
    \ sequence) {\n    int n = int(sequence.size());\n    ManacherResult result;\n\
    \    result.odd.assign(n, 0);\n    result.even.assign(n, 0);\n\n    int left =\
    \ 0;\n    int right = -1;\n    for (int i = 0; i < n; i++) {\n        int radius\
    \ = i > right ? 1 : std::min(result.odd[left + right - i], right - i + 1);\n \
    \       while (\n            0 <= i - radius &&\n            i + radius < n &&\n\
    \            sequence[i - radius] == sequence[i + radius]\n        ) {\n     \
    \       radius++;\n        }\n        result.odd[i] = radius;\n        if (right\
    \ < i + radius - 1) {\n            left = i - radius + 1;\n            right =\
    \ i + radius - 1;\n        }\n    }\n\n    left = 0;\n    right = -1;\n    for\
    \ (int i = 0; i < n; i++) {\n        int radius = i > right ? 0 : std::min(result.even[left\
    \ + right - i + 1], right - i + 1);\n        while (\n            0 <= i - radius\
    \ - 1 &&\n            i + radius < n &&\n            sequence[i - radius - 1]\
    \ == sequence[i + radius]\n        ) {\n            radius++;\n        }\n   \
    \     result.even[i] = radius;\n        if (right < i + radius - 1) {\n      \
    \      left = i - radius;\n            right = i + radius - 1;\n        }\n  \
    \  }\n    return result;\n}\n\n}  // namespace string\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_STRING_MANACHER_HPP\n#define M1UNE_STRING_MANACHER_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace string {\n\nstruct ManacherResult {\n    // odd[i] is the radius\
    \ including center i.\n    // The palindrome is [i - odd[i] + 1, i + odd[i]).\n\
    \    std::vector<int> odd;\n\n    // even[i] is the radius centered between i\
    \ - 1 and i.\n    // The palindrome is [i - even[i], i + even[i]).\n    std::vector<int>\
    \ even;\n\n    int size() const {\n        return int(odd.size());\n    }\n\n\
    \    bool empty() const {\n        return odd.empty();\n    }\n\n    bool is_palindrome(int\
    \ left, int right) const {\n        int n = size();\n        assert(0 <= left\
    \ && left <= right && right <= n);\n        int length = right - left;\n     \
    \   if (length == 0) return true;\n        if (length & 1) {\n            int\
    \ center = (left + right) / 2;\n            return length / 2 + 1 <= odd[center];\n\
    \        }\n        int center = (left + right) / 2;\n        return length /\
    \ 2 <= even[center];\n    }\n\n    int longest_length() const {\n        int result\
    \ = 0;\n        for (int radius : odd) result = std::max(result, 2 * radius -\
    \ 1);\n        for (int radius : even) result = std::max(result, 2 * radius);\n\
    \        return result;\n    }\n};\n\ntemplate <class Sequence>\nManacherResult\
    \ manacher(const Sequence& sequence) {\n    int n = int(sequence.size());\n  \
    \  ManacherResult result;\n    result.odd.assign(n, 0);\n    result.even.assign(n,\
    \ 0);\n\n    int left = 0;\n    int right = -1;\n    for (int i = 0; i < n; i++)\
    \ {\n        int radius = i > right ? 1 : std::min(result.odd[left + right - i],\
    \ right - i + 1);\n        while (\n            0 <= i - radius &&\n         \
    \   i + radius < n &&\n            sequence[i - radius] == sequence[i + radius]\n\
    \        ) {\n            radius++;\n        }\n        result.odd[i] = radius;\n\
    \        if (right < i + radius - 1) {\n            left = i - radius + 1;\n \
    \           right = i + radius - 1;\n        }\n    }\n\n    left = 0;\n    right\
    \ = -1;\n    for (int i = 0; i < n; i++) {\n        int radius = i > right ? 0\
    \ : std::min(result.even[left + right - i + 1], right - i + 1);\n        while\
    \ (\n            0 <= i - radius - 1 &&\n            i + radius < n &&\n     \
    \       sequence[i - radius - 1] == sequence[i + radius]\n        ) {\n      \
    \      radius++;\n        }\n        result.even[i] = radius;\n        if (right\
    \ < i + radius - 1) {\n            left = i - radius;\n            right = i +\
    \ radius - 1;\n        }\n    }\n    return result;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n#endif  // M1UNE_STRING_MANACHER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-21 02:43:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/manacher.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/manacher.hpp
layout: document
title: Manacher Algorithm
---

## Overview

`manacher(sequence)` finds every maximal odd- and even-length palindrome in
linear time. The result also answers whether any substring is a palindrome in
$O(1)$.

The function is generic over indexable sequences with comparable elements.

## Result

`ManacherResult` contains:

| Member / Method | Meaning | Complexity |
| --- | --- | --- |
| `odd[i]` | Radius including center `i`; palindrome `[i - odd[i] + 1, i + odd[i])`. | Access $O(1)$ |
| `even[i]` | Radius centered between `i - 1` and `i`; palindrome `[i - even[i], i + even[i])`. | Access $O(1)$ |
| `size()` | Returns the original sequence length. | $O(1)$ |
| `empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `is_palindrome(l, r)` | Returns whether `[l, r)` is a palindrome. | $O(1)$ |
| `longest_length()` | Returns the longest palindromic substring length. | $O(N)$ |

Construction takes $O(N)$ time and space.

## Example

```cpp
#include "string/manacher.hpp"

#include <iostream>
#include <string>

int main() {
    auto palindromes = m1une::string::manacher(std::string("abacaba"));

    std::cout << palindromes.longest_length() << "\n";      // 7
    std::cout << palindromes.is_palindrome(1, 6) << "\n";   // 1
    std::cout << palindromes.is_palindrome(0, 4) << "\n";   // 0
}
```
