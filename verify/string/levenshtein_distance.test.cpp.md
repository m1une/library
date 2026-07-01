---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/levenshtein_distance.hpp
    title: Levenshtein Distance
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E
  bundledCode: "#line 1 \"verify/string/levenshtein_distance.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E\"\n\n#line 1 \"string/levenshtein_distance.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace string {\n\nnamespace levenshtein_distance_detail {\n\ntemplate\
    \ <class RowSequence, class ColumnSequence>\nint solve(const RowSequence& rows,\
    \ const ColumnSequence& columns) {\n    int row_count = int(rows.size());\n  \
    \  int column_count = int(columns.size());\n    std::vector<int> distance(column_count\
    \ + 1);\n    for (int column = 0; column <= column_count; column++) distance[column]\
    \ = column;\n\n    for (int row = 1; row <= row_count; row++) {\n        int diagonal\
    \ = distance[0];\n        distance[0] = row;\n        for (int column = 1; column\
    \ <= column_count; column++) {\n            int above = distance[column];\n  \
    \          int substitution = diagonal + (rows[row - 1] == columns[column - 1]\
    \ ? 0 : 1);\n            distance[column] =\n                std::min({above +\
    \ 1, distance[column - 1] + 1, substitution});\n            diagonal = above;\n\
    \        }\n    }\n    return distance[column_count];\n}\n\ntemplate <class RowSequence,\
    \ class ColumnSequence>\nint solve_bounded(const RowSequence& rows, const ColumnSequence&\
    \ columns,\n                  int max_distance) {\n    int row_count = int(rows.size());\n\
    \    int column_count = int(columns.size());\n    assert(column_count <= row_count);\n\
    \    if (row_count - column_count > max_distance) return max_distance + 1;\n \
    \   if (max_distance >= row_count) return solve(rows, columns);\n\n    int infinity\
    \ = max_distance + 1;\n    int previous_left = 0;\n    int previous_right = std::min(column_count,\
    \ max_distance);\n    std::vector<int> previous(previous_right + 1);\n    for\
    \ (int column = 0; column <= previous_right; column++) previous[column] = column;\n\
    \    std::vector<int> current;\n\n    for (int row = 1; row <= row_count; row++)\
    \ {\n        int current_left = std::max(0, row - max_distance);\n        int\
    \ current_right = int(std::min<long long>(column_count,\n                    \
    \                                static_cast<long long>(row) + max_distance));\n\
    \        current.assign(current_right - current_left + 1, infinity);\n\n     \
    \   for (int column = current_left; column <= current_right; column++) {\n   \
    \         int best = infinity;\n            if (previous_left <= column && column\
    \ <= previous_right) {\n                best = std::min(best, previous[column\
    \ - previous_left] + 1);\n            }\n            if (current_left < column)\
    \ {\n                best = std::min(best, current[column - current_left - 1]\
    \ + 1);\n            }\n            if (0 < column && previous_left <= column\
    \ - 1 && column - 1 <= previous_right) {\n                int substitution = previous[column\
    \ - 1 - previous_left] +\n                                   (rows[row - 1] ==\
    \ columns[column - 1] ? 0 : 1);\n                best = std::min(best, substitution);\n\
    \            }\n            current[column - current_left] = std::min(best, infinity);\n\
    \        }\n\n        previous.swap(current);\n        previous_left = current_left;\n\
    \        previous_right = current_right;\n    }\n    return previous[column_count\
    \ - previous_left];\n}\n\n}  // namespace levenshtein_distance_detail\n\n// Returns\
    \ the minimum number of insertions, deletions, and substitutions\n// needed to\
    \ transform first into second.\ntemplate <class Sequence1, class Sequence2>\n\
    int levenshtein_distance(const Sequence1& first, const Sequence2& second) {\n\
    \    if (first.size() < second.size()) {\n        return levenshtein_distance_detail::solve(second,\
    \ first);\n    }\n    return levenshtein_distance_detail::solve(first, second);\n\
    }\n\n// Returns the exact distance when it is at most max_distance, and\n// max_distance\
    \ + 1 otherwise.\ntemplate <class Sequence1, class Sequence2>\nint levenshtein_distance(const\
    \ Sequence1& first, const Sequence2& second,\n                         int max_distance)\
    \ {\n    assert(0 <= max_distance);\n    if (first.size() < second.size()) {\n\
    \        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);\n\
    \    }\n    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/levenshtein_distance.test.cpp\"\
    \n\n#line 7 \"verify/string/levenshtein_distance.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <string>\n#line 11 \"verify/string/levenshtein_distance.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class Sequence1, class Sequence2>\nint naive_distance(const\
    \ Sequence1& first, const Sequence2& second) {\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    std::vector<std::vector<int>> dp(n + 1,\
    \ std::vector<int>(m + 1));\n    for (int i = 0; i <= n; i++) dp[i][0] = i;\n\
    \    for (int j = 0; j <= m; j++) dp[0][j] = j;\n    for (int i = 1; i <= n; i++)\
    \ {\n        for (int j = 1; j <= m; j++) {\n            int substitution = dp[i\
    \ - 1][j - 1] + (first[i - 1] == second[j - 1] ? 0 : 1);\n            dp[i][j]\
    \ = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, substitution});\n        }\n\
    \    }\n    return dp[n][m];\n}\n\nvoid test_edge_cases() {\n    using m1une::string::levenshtein_distance;\n\
    \    assert(levenshtein_distance(std::string(), std::string()) == 0);\n    assert(levenshtein_distance(std::string(),\
    \ std::string(\"abc\")) == 3);\n    assert(levenshtein_distance(std::string(\"\
    abc\"), std::string()) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\")) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\"), 3) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\"), 2) == 3);\n    assert(levenshtein_distance(std::string(\"\
    flaw\"), std::string(\"lawn\")) == 2);\n    assert(levenshtein_distance(std::string(\"\
    same\"), std::string(\"same\"), 0) == 0);\n    assert(levenshtein_distance(std::string(\"\
    a\"), std::string(\"bbbb\"), 1) == 2);\n\n    std::vector<int> first = {1, 2,\
    \ 3};\n    std::vector<int> second = {1, 3, 4};\n    assert(levenshtein_distance(first,\
    \ second) == 2);\n\n    std::string long_first(100000, 'a');\n    std::string\
    \ long_second = long_first;\n    long_second.back() = 'b';\n    assert(levenshtein_distance(long_first,\
    \ long_second, 1) == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 123456789;\n    auto random = [&]() {\n        state ^= state << 7;\n    \
    \    state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 2000; trial++) {\n        int n = int(random() % 16);\n       \
    \ int m = int(random() % 16);\n        std::string first(n, 'a');\n        std::string\
    \ second(m, 'a');\n        for (char& value : first) value = char('a' + random()\
    \ % 4);\n        for (char& value : second) value = char('a' + random() % 4);\n\
    \n        [[maybe_unused]] int expected = naive_distance(first, second);\n   \
    \     assert(m1une::string::levenshtein_distance(first, second) == expected);\n\
    \        assert(m1une::string::levenshtein_distance(second, first) == expected);\n\
    \        for (int max_distance = 0; max_distance <= 8; max_distance++) {\n   \
    \         [[maybe_unused]] int bounded_expected = std::min(expected, max_distance\
    \ + 1);\n            assert(m1une::string::levenshtein_distance(first, second,\
    \ max_distance) ==\n                   bounded_expected);\n            assert(m1une::string::levenshtein_distance(second,\
    \ first, max_distance) ==\n                   bounded_expected);\n        }\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\
    \n    std::string first, second;\n    std::cin >> first >> second;\n    std::cout\
    \ << m1une::string::levenshtein_distance(first, second) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E\"\n\n\
    #include \"../../string/levenshtein_distance.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <string>\n#include\
    \ <vector>\n\nnamespace {\n\ntemplate <class Sequence1, class Sequence2>\nint\
    \ naive_distance(const Sequence1& first, const Sequence2& second) {\n    int n\
    \ = int(first.size());\n    int m = int(second.size());\n    std::vector<std::vector<int>>\
    \ dp(n + 1, std::vector<int>(m + 1));\n    for (int i = 0; i <= n; i++) dp[i][0]\
    \ = i;\n    for (int j = 0; j <= m; j++) dp[0][j] = j;\n    for (int i = 1; i\
    \ <= n; i++) {\n        for (int j = 1; j <= m; j++) {\n            int substitution\
    \ = dp[i - 1][j - 1] + (first[i - 1] == second[j - 1] ? 0 : 1);\n            dp[i][j]\
    \ = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, substitution});\n        }\n\
    \    }\n    return dp[n][m];\n}\n\nvoid test_edge_cases() {\n    using m1une::string::levenshtein_distance;\n\
    \    assert(levenshtein_distance(std::string(), std::string()) == 0);\n    assert(levenshtein_distance(std::string(),\
    \ std::string(\"abc\")) == 3);\n    assert(levenshtein_distance(std::string(\"\
    abc\"), std::string()) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\")) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\"), 3) == 3);\n    assert(levenshtein_distance(std::string(\"\
    kitten\"), std::string(\"sitting\"), 2) == 3);\n    assert(levenshtein_distance(std::string(\"\
    flaw\"), std::string(\"lawn\")) == 2);\n    assert(levenshtein_distance(std::string(\"\
    same\"), std::string(\"same\"), 0) == 0);\n    assert(levenshtein_distance(std::string(\"\
    a\"), std::string(\"bbbb\"), 1) == 2);\n\n    std::vector<int> first = {1, 2,\
    \ 3};\n    std::vector<int> second = {1, 3, 4};\n    assert(levenshtein_distance(first,\
    \ second) == 2);\n\n    std::string long_first(100000, 'a');\n    std::string\
    \ long_second = long_first;\n    long_second.back() = 'b';\n    assert(levenshtein_distance(long_first,\
    \ long_second, 1) == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 123456789;\n    auto random = [&]() {\n        state ^= state << 7;\n    \
    \    state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 2000; trial++) {\n        int n = int(random() % 16);\n       \
    \ int m = int(random() % 16);\n        std::string first(n, 'a');\n        std::string\
    \ second(m, 'a');\n        for (char& value : first) value = char('a' + random()\
    \ % 4);\n        for (char& value : second) value = char('a' + random() % 4);\n\
    \n        [[maybe_unused]] int expected = naive_distance(first, second);\n   \
    \     assert(m1une::string::levenshtein_distance(first, second) == expected);\n\
    \        assert(m1une::string::levenshtein_distance(second, first) == expected);\n\
    \        for (int max_distance = 0; max_distance <= 8; max_distance++) {\n   \
    \         [[maybe_unused]] int bounded_expected = std::min(expected, max_distance\
    \ + 1);\n            assert(m1une::string::levenshtein_distance(first, second,\
    \ max_distance) ==\n                   bounded_expected);\n            assert(m1une::string::levenshtein_distance(second,\
    \ first, max_distance) ==\n                   bounded_expected);\n        }\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\
    \n    std::string first, second;\n    std::cin >> first >> second;\n    std::cout\
    \ << m1une::string::levenshtein_distance(first, second) << '\\n';\n}\n"
  dependsOn:
  - string/levenshtein_distance.hpp
  isVerificationFile: true
  path: verify/string/levenshtein_distance.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 21:56:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/levenshtein_distance.test.cpp
layout: document
redirect_from:
- /verify/verify/string/levenshtein_distance.test.cpp
- /verify/verify/string/levenshtein_distance.test.cpp.html
title: verify/string/levenshtein_distance.test.cpp
---
