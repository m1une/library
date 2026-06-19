---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sequence/inversion_count.hpp
    title: Inversion Count
  - icon: ':heavy_check_mark:'
    path: sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/sequence/sequence_algorithms.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n\n#line 1 \"sequence/inversion_count.hpp\"\n\n\
    \n\n#line 5 \"sequence/inversion_count.hpp\"\n\nnamespace m1une {\nnamespace sequence\
    \ {\n\n// Returns the number of pairs (i, j) with i < j and a[i] > a[j].\n// The\
    \ vector is taken by value because merge sort rearranges it.\ntemplate <typename\
    \ T>\nlong long inversion_count(std::vector<T> a) {\n    const int n = int(a.size());\n\
    \    std::vector<T> temp = a;\n\n    auto merge_sort = [&](auto& self, int l,\
    \ int r) -> long long {\n        if (r - l <= 1) return 0;\n\n        const int\
    \ m = l + (r - l) / 2;\n        long long inv = self(self, l, m) + self(self,\
    \ m, r);\n\n        int i = l;\n        int j = m;\n        int k = l;\n     \
    \   while (i < m && j < r) {\n            if (!(a[j] < a[i])) {\n            \
    \    temp[k++] = a[i++];\n            } else {\n                temp[k++] = a[j++];\n\
    \                inv += m - i;\n            }\n        }\n\n        while (i <\
    \ m) temp[k++] = a[i++];\n        while (j < r) temp[k++] = a[j++];\n\n      \
    \  for (int p = l; p < r; ++p) {\n            a[p] = temp[p];\n        }\n\n \
    \       return inv;\n    };\n\n    return merge_sort(merge_sort, 0, n);\n}\n\n\
    }  // namespace sequence\n}  // namespace m1une\n\n\n#line 1 \"sequence/lis.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <iterator>\n#line 7 \"sequence/lis.hpp\"\
    \n\nnamespace m1une {\nnamespace sequence {\n\n// Returns the zero-based indices\
    \ of a longest increasing subsequence.\n// If `strict` is false, equal adjacent\
    \ values are also allowed.\ntemplate <typename T>\nstd::vector<int> lis(const\
    \ std::vector<T>& a, bool strict = true) {\n    const int n = int(a.size());\n\
    \    std::vector<T> tails;\n    std::vector<int> tail_positions;\n    std::vector<int>\
    \ predecessor(n, -1);\n    tails.reserve(n);\n    tail_positions.reserve(n);\n\
    \n    for (int i = 0; i < n; ++i) {\n        auto it = strict ? std::lower_bound(tails.begin(),\
    \ tails.end(), a[i])\n                         : std::upper_bound(tails.begin(),\
    \ tails.end(), a[i]);\n        const int length = int(std::distance(tails.begin(),\
    \ it));\n\n        if (it == tails.end()) {\n            tails.push_back(a[i]);\n\
    \            tail_positions.push_back(i);\n        } else {\n            *it =\
    \ a[i];\n            tail_positions[length] = i;\n        }\n\n        if (length\
    \ > 0) {\n            predecessor[i] = tail_positions[length - 1];\n        }\n\
    \    }\n\n    if (tail_positions.empty()) return {};\n\n    std::vector<int> result;\n\
    \    result.reserve(tail_positions.size());\n    int current = tail_positions.back();\n\
    \    while (current != -1) {\n        result.push_back(current);\n        current\
    \ = predecessor[current];\n    }\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\n}  // namespace sequence\n}  // namespace m1une\n\n\n\
    #line 9 \"verify/sequence/sequence_algorithms.test.cpp\"\n\nstruct LessOnly {\n\
    \    int value;\n\n    explicit LessOnly(int value) : value(value) {}\n\n    friend\
    \ bool operator<(const LessOnly& lhs, const LessOnly& rhs) {\n        return lhs.value\
    \ < rhs.value;\n    }\n};\n\ntemplate <typename T>\nvoid assert_subsequence(\n\
    \    const std::vector<T>& values,\n    const std::vector<int>& indices,\n   \
    \ bool strict\n) {\n    for (int i = 0; i < int(indices.size()); ++i) {\n    \
    \    assert(0 <= indices[i] && indices[i] < int(values.size()));\n        if (i\
    \ == 0) continue;\n        assert(indices[i - 1] < indices[i]);\n        if (strict)\
    \ {\n            assert(values[indices[i - 1]] < values[indices[i]]);\n      \
    \  } else {\n            assert(!(values[indices[i]] < values[indices[i - 1]]));\n\
    \        }\n    }\n}\n\nvoid test_lis() {\n    const std::vector<int> values =\
    \ {3, 1, 2, 2, 4};\n\n    const auto strict = m1une::sequence::lis(values);\n\
    \    assert(strict.size() == 3);\n    assert_subsequence(values, strict, true);\n\
    \n    const auto non_decreasing = m1une::sequence::lis(values, false);\n    assert(non_decreasing.size()\
    \ == 4);\n    assert_subsequence(values, non_decreasing, false);\n\n    assert(m1une::sequence::lis(std::vector<int>()).empty());\n\
    }\n\nvoid test_inversion_count() {\n    assert(m1une::sequence::inversion_count(std::vector<int>{2,\
    \ 4, 1, 3, 5}) == 3);\n    assert(m1une::sequence::inversion_count(std::vector<int>{1,\
    \ 1, 1}) == 0);\n    assert(m1une::sequence::inversion_count(std::vector<int>{3,\
    \ 2, 1}) == 3);\n\n    std::vector<LessOnly> values = {LessOnly(2), LessOnly(1),\
    \ LessOnly(1)};\n    assert(m1une::sequence::inversion_count(values) == 2);\n\
    }\n\nint main() {\n    test_lis();\n    test_inversion_count();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#include \"sequence/inversion_count.hpp\"\
    \n#include \"sequence/lis.hpp\"\n\nstruct LessOnly {\n    int value;\n\n    explicit\
    \ LessOnly(int value) : value(value) {}\n\n    friend bool operator<(const LessOnly&\
    \ lhs, const LessOnly& rhs) {\n        return lhs.value < rhs.value;\n    }\n\
    };\n\ntemplate <typename T>\nvoid assert_subsequence(\n    const std::vector<T>&\
    \ values,\n    const std::vector<int>& indices,\n    bool strict\n) {\n    for\
    \ (int i = 0; i < int(indices.size()); ++i) {\n        assert(0 <= indices[i]\
    \ && indices[i] < int(values.size()));\n        if (i == 0) continue;\n      \
    \  assert(indices[i - 1] < indices[i]);\n        if (strict) {\n            assert(values[indices[i\
    \ - 1]] < values[indices[i]]);\n        } else {\n            assert(!(values[indices[i]]\
    \ < values[indices[i - 1]]));\n        }\n    }\n}\n\nvoid test_lis() {\n    const\
    \ std::vector<int> values = {3, 1, 2, 2, 4};\n\n    const auto strict = m1une::sequence::lis(values);\n\
    \    assert(strict.size() == 3);\n    assert_subsequence(values, strict, true);\n\
    \n    const auto non_decreasing = m1une::sequence::lis(values, false);\n    assert(non_decreasing.size()\
    \ == 4);\n    assert_subsequence(values, non_decreasing, false);\n\n    assert(m1une::sequence::lis(std::vector<int>()).empty());\n\
    }\n\nvoid test_inversion_count() {\n    assert(m1une::sequence::inversion_count(std::vector<int>{2,\
    \ 4, 1, 3, 5}) == 3);\n    assert(m1une::sequence::inversion_count(std::vector<int>{1,\
    \ 1, 1}) == 0);\n    assert(m1une::sequence::inversion_count(std::vector<int>{3,\
    \ 2, 1}) == 3);\n\n    std::vector<LessOnly> values = {LessOnly(2), LessOnly(1),\
    \ LessOnly(1)};\n    assert(m1une::sequence::inversion_count(values) == 2);\n\
    }\n\nint main() {\n    test_lis();\n    test_inversion_count();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - sequence/inversion_count.hpp
  - sequence/lis.hpp
  isVerificationFile: true
  path: verify/sequence/sequence_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/sequence/sequence_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/sequence/sequence_algorithms.test.cpp
- /verify/verify/sequence/sequence_algorithms.test.cpp.html
title: verify/sequence/sequence_algorithms.test.cpp
---
