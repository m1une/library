---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':x:'
    path: verify/string/suffix_array.test.cpp
    title: verify/string/suffix_array.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_array.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <string>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace string {\nnamespace detail {\n\
    \ntemplate <class Sequence>\nstd::vector<int> suffix_array_impl(const Sequence&\
    \ sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return {};\n\
    \n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_SUFFIX_ARRAY_HPP\n#define M1UNE_STRING_SUFFIX_ARRAY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <string>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ string {\nnamespace detail {\n\ntemplate <class Sequence>\nstd::vector<int>\
    \ suffix_array_impl(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    if (n == 0) return {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n#endif  // M1UNE_STRING_SUFFIX_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-21 02:43:08+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/suffix_array.test.cpp
documentation_of: string/suffix_array.hpp
layout: document
title: Suffix Array and LCP Array
---

## Overview

A suffix array lists every suffix starting position in lexicographic order.
Together with the LCP array, it is useful for substring counting, repeated
substrings, lexicographic queries, and offline pattern matching.

The implementation uses counting-sorted doubling and runs in
$O(N \log N)$. `lcp_array` uses Kasai's algorithm and runs in $O(N)$.

`suffix_array` supports `std::string` and other indexable sequences whose
elements are sortable. String bytes are compared as unsigned characters.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> suffix_array(const Sequence& sequence)` | Returns suffix starting positions in lexicographic order. | $O(N \log N)$ |
| `vector<int> lcp_array(const Sequence& sequence, const vector<int>& sa)` | Returns LCP lengths of adjacent suffixes. The result has length `max(N - 1, 0)`. | $O(N)$ |

For `lcp = lcp_array(s, sa)`, `lcp[i]` is the longest common prefix length of
suffixes `s[sa[i]..]` and `s[sa[i + 1]..]`.

## Example

```cpp
#include "string/suffix_array.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    auto suffixes = m1une::string::suffix_array(text);
    auto lcp = m1une::string::lcp_array(text, suffixes);

    for (int position : suffixes) std::cout << position << " ";
    std::cout << "\n"; // 5 3 1 0 4 2
}
```
