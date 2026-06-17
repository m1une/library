---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
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
  bundledCode: "#line 1 \"verify/optimization/hungarian.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\n#line\
    \ 1 \"optimization/hungarian.hpp\"\n\n\n\n#line 7 \"optimization/hungarian.hpp\"\
    \n#include <utility>\n#line 9 \"optimization/hungarian.hpp\"\n\nnamespace m1une\
    \ {\nnamespace optimization {\n\ntemplate <class T>\nstruct HungarianResult {\n\
    \    T cost;\n    std::vector<int> row_to_col;\n    std::vector<int> col_to_row;\n\
    \n    int matching_size() const {\n        int result = 0;\n        for (int col\
    \ : row_to_col) {\n            if (col != -1) result++;\n        }\n        return\
    \ result;\n    }\n\n    std::vector<std::pair<int, int>> matching() const {\n\
    \        std::vector<std::pair<int, int>> result;\n        for (int row = 0; row\
    \ < int(row_to_col.size()); row++) {\n            if (row_to_col[row] != -1) result.push_back({row,\
    \ row_to_col[row]});\n        }\n        return result;\n    }\n};\n\nnamespace\
    \ detail {\n\ntemplate <class T>\nT assignment_cost(const std::vector<std::vector<T>>&\
    \ cost, const std::vector<int>& row_to_col) {\n    T result = T();\n    for (int\
    \ row = 0; row < int(row_to_col.size()); row++) {\n        if (row_to_col[row]\
    \ != -1) result += cost[row][row_to_col[row]];\n    }\n    return result;\n}\n\
    \n}  // namespace detail\n\ntemplate <class T>\nHungarianResult<T> hungarian_min(const\
    \ std::vector<std::vector<T>>& cost) {\n    int row_count = int(cost.size());\n\
    \    int col_count = row_count == 0 ? 0 : int(cost[0].size());\n    for (const\
    \ auto& row : cost) assert(int(row.size()) == col_count);\n\n    HungarianResult<T>\
    \ result;\n    result.cost = T();\n    result.row_to_col.assign(row_count, -1);\n\
    \    result.col_to_row.assign(col_count, -1);\n    if (row_count == 0 || col_count\
    \ == 0) return result;\n\n    bool transposed = row_count > col_count;\n    int\
    \ n = transposed ? col_count : row_count;\n    int m = transposed ? row_count\
    \ : col_count;\n    T inf = std::numeric_limits<T>::max() / T(4);\n\n    std::vector<T>\
    \ u(n + 1, T()), v(m + 1, T()), minv(m + 1);\n    std::vector<int> p(m + 1, 0),\
    \ way(m + 1, 0);\n\n    auto value = [&](int i, int j) -> T {\n        return\
    \ transposed ? cost[j][i] : cost[i][j];\n    };\n\n    for (int i = 1; i <= n;\
    \ i++) {\n        p[0] = i;\n        int j0 = 0;\n        std::fill(minv.begin(),\
    \ minv.end(), inf);\n        std::vector<char> used(m + 1, false);\n\n       \
    \ do {\n            used[j0] = true;\n            int i0 = p[j0];\n          \
    \  int j1 = 0;\n            T delta = inf;\n\n            for (int j = 1; j <=\
    \ m; j++) {\n                if (used[j]) continue;\n                T cur = value(i0\
    \ - 1, j - 1) - u[i0] - v[j];\n                if (cur < minv[j]) {\n        \
    \            minv[j] = cur;\n                    way[j] = j0;\n              \
    \  }\n                if (minv[j] < delta) {\n                    delta = minv[j];\n\
    \                    j1 = j;\n                }\n            }\n\n           \
    \ for (int j = 0; j <= m; j++) {\n                if (used[j]) {\n           \
    \         u[p[j]] += delta;\n                    v[j] -= delta;\n            \
    \    } else {\n                    minv[j] -= delta;\n                }\n    \
    \        }\n            j0 = j1;\n        } while (p[j0] != 0);\n\n        do\
    \ {\n            int j1 = way[j0];\n            p[j0] = p[j1];\n            j0\
    \ = j1;\n        } while (j0 != 0);\n    }\n\n    for (int j = 1; j <= m; j++)\
    \ {\n        if (p[j] == 0) continue;\n        int i = p[j] - 1;\n        int\
    \ matched = j - 1;\n        if (transposed) {\n            int row = matched;\n\
    \            int col = i;\n            result.row_to_col[row] = col;\n       \
    \     result.col_to_row[col] = row;\n        } else {\n            int row = i;\n\
    \            int col = matched;\n            result.row_to_col[row] = col;\n \
    \           result.col_to_row[col] = row;\n        }\n    }\n    result.cost =\
    \ detail::assignment_cost(cost, result.row_to_col);\n    return result;\n}\n\n\
    template <class T>\nHungarianResult<T> hungarian_max(const std::vector<std::vector<T>>&\
    \ cost) {\n    std::vector<std::vector<T>> negated = cost;\n    for (auto& row\
    \ : negated) {\n        for (auto& x : row) x = -x;\n    }\n    auto result =\
    \ hungarian_min(negated);\n    result.cost = detail::assignment_cost(cost, result.row_to_col);\n\
    \    return result;\n}\n\ntemplate <class T>\nHungarianResult<T> hungarian(const\
    \ std::vector<std::vector<T>>& cost) {\n    return hungarian_min(cost);\n}\n\n\
    }  // namespace optimization\n}  // namespace m1une\n\n\n#line 10 \"verify/optimization/hungarian.test.cpp\"\
    \n\nlong long brute_min(const std::vector<std::vector<long long>>& cost) {\n \
    \   int h = int(cost.size());\n    int w = h == 0 ? 0 : int(cost[0].size());\n\
    \    if (h == 0 || w == 0) return 0;\n\n    long long best = std::numeric_limits<long\
    \ long>::max() / 4;\n    if (h <= w) {\n        std::vector<int> perm(w);\n  \
    \      for (int i = 0; i < w; i++) perm[i] = i;\n        do {\n            long\
    \ long sum = 0;\n            for (int i = 0; i < h; i++) sum += cost[i][perm[i]];\n\
    \            best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    } else {\n        std::vector<int> perm(h);\n        for\
    \ (int i = 0; i < h; i++) perm[i] = i;\n        do {\n            long long sum\
    \ = 0;\n            for (int j = 0; j < w; j++) sum += cost[perm[j]][j];\n   \
    \         best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    }\n    return best;\n}\n\nlong long brute_max(const std::vector<std::vector<long\
    \ long>>& cost) {\n    std::vector<std::vector<long long>> negated = cost;\n \
    \   for (auto& row : negated) {\n        for (auto& x : row) x = -x;\n    }\n\
    \    return -brute_min(negated);\n}\n\nvoid check_result(const std::vector<std::vector<long\
    \ long>>& cost,\n                  const m1une::optimization::HungarianResult<long\
    \ long>& result,\n                  long long expected) {\n    int h = int(cost.size());\n\
    \    int w = h == 0 ? 0 : int(cost[0].size());\n    assert(int(result.row_to_col.size())\
    \ == h);\n    assert(int(result.col_to_row.size()) == w);\n    assert(result.matching_size()\
    \ == std::min(h, w));\n    assert(result.cost == expected);\n\n    std::vector<bool>\
    \ used_cols(w, false);\n    long long sum = 0;\n    for (int i = 0; i < h; i++)\
    \ {\n        int j = result.row_to_col[i];\n        if (j == -1) continue;\n \
    \       assert(0 <= j && j < w);\n        assert(!used_cols[j]);\n        assert(result.col_to_row[j]\
    \ == i);\n        used_cols[j] = true;\n        sum += cost[i][j];\n    }\n  \
    \  for (int j = 0; j < w; j++) {\n        int i = result.col_to_row[j];\n    \
    \    if (i == -1) continue;\n        assert(0 <= i && i < h);\n        assert(result.row_to_col[i]\
    \ == j);\n    }\n    assert(sum == result.cost);\n\n    auto pairs = result.matching();\n\
    \    assert(int(pairs.size()) == result.matching_size());\n    for (auto [row,\
    \ col] : pairs) assert(result.row_to_col[row] == col);\n}\n\nvoid test_hungarian_min()\
    \ {\n    std::vector<std::vector<long long>> square = {\n        {4, 1, 3},\n\
    \        {2, 0, 5},\n        {3, 2, 2},\n    };\n    auto sq = m1une::optimization::hungarian_min(square);\n\
    \    check_result(square, sq, 5);\n\n    std::vector<std::vector<long long>> wide\
    \ = {\n        {7, 4, 6, 8},\n        {5, 9, 3, 1},\n    };\n    check_result(wide,\
    \ m1une::optimization::hungarian(wide), brute_min(wide));\n\n    std::vector<std::vector<long\
    \ long>> tall = {\n        {9, 4},\n        {6, 7},\n        {5, 8},\n       \
    \ {1, 3},\n    };\n    auto tall_result = m1une::optimization::hungarian_min(tall);\n\
    \    check_result(tall, tall_result, brute_min(tall));\n    assert(tall_result.col_to_row[0]\
    \ != -1);\n    assert(tall_result.col_to_row[1] != -1);\n\n    std::vector<std::vector<long\
    \ long>> negative = {\n        {-4, 2, 0},\n        {3, -5, 1},\n    };\n    check_result(negative,\
    \ m1une::optimization::hungarian_min(negative), brute_min(negative));\n\n    std::vector<std::vector<long\
    \ long>> zero_cols(3);\n    check_result(zero_cols, m1une::optimization::hungarian_min(zero_cols),\
    \ 0);\n}\n\nvoid test_hungarian_max() {\n    std::vector<std::vector<long long>>\
    \ cost = {\n        {1, 8, 2},\n        {5, 3, 4},\n        {6, 7, 0},\n    };\n\
    \    check_result(cost, m1une::optimization::hungarian_max(cost), brute_max(cost));\n\
    }\n\nvoid test_against_bruteforce() {\n    for (int h = 1; h <= 4; h++) {\n  \
    \      for (int w = 1; w <= 4; w++) {\n            std::vector<std::vector<long\
    \ long>> cost(h, std::vector<long long>(w));\n            for (int i = 0; i <\
    \ h; i++) {\n                for (int j = 0; j < w; j++) {\n                 \
    \   cost[i][j] = ((i + 2) * (j + 3) * 5 + i * 7 - j * 11) % 17 - 8;\n        \
    \        }\n            }\n            check_result(cost, m1une::optimization::hungarian_min(cost),\
    \ brute_min(cost));\n            check_result(cost, m1une::optimization::hungarian_max(cost),\
    \ brute_max(cost));\n        }\n    }\n}\n\nint main() {\n    test_hungarian_min();\n\
    \    test_hungarian_max();\n    test_against_bruteforce();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#include \"optimization/hungarian.hpp\"\n\nlong long brute_min(const std::vector<std::vector<long\
    \ long>>& cost) {\n    int h = int(cost.size());\n    int w = h == 0 ? 0 : int(cost[0].size());\n\
    \    if (h == 0 || w == 0) return 0;\n\n    long long best = std::numeric_limits<long\
    \ long>::max() / 4;\n    if (h <= w) {\n        std::vector<int> perm(w);\n  \
    \      for (int i = 0; i < w; i++) perm[i] = i;\n        do {\n            long\
    \ long sum = 0;\n            for (int i = 0; i < h; i++) sum += cost[i][perm[i]];\n\
    \            best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    } else {\n        std::vector<int> perm(h);\n        for\
    \ (int i = 0; i < h; i++) perm[i] = i;\n        do {\n            long long sum\
    \ = 0;\n            for (int j = 0; j < w; j++) sum += cost[perm[j]][j];\n   \
    \         best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    }\n    return best;\n}\n\nlong long brute_max(const std::vector<std::vector<long\
    \ long>>& cost) {\n    std::vector<std::vector<long long>> negated = cost;\n \
    \   for (auto& row : negated) {\n        for (auto& x : row) x = -x;\n    }\n\
    \    return -brute_min(negated);\n}\n\nvoid check_result(const std::vector<std::vector<long\
    \ long>>& cost,\n                  const m1une::optimization::HungarianResult<long\
    \ long>& result,\n                  long long expected) {\n    int h = int(cost.size());\n\
    \    int w = h == 0 ? 0 : int(cost[0].size());\n    assert(int(result.row_to_col.size())\
    \ == h);\n    assert(int(result.col_to_row.size()) == w);\n    assert(result.matching_size()\
    \ == std::min(h, w));\n    assert(result.cost == expected);\n\n    std::vector<bool>\
    \ used_cols(w, false);\n    long long sum = 0;\n    for (int i = 0; i < h; i++)\
    \ {\n        int j = result.row_to_col[i];\n        if (j == -1) continue;\n \
    \       assert(0 <= j && j < w);\n        assert(!used_cols[j]);\n        assert(result.col_to_row[j]\
    \ == i);\n        used_cols[j] = true;\n        sum += cost[i][j];\n    }\n  \
    \  for (int j = 0; j < w; j++) {\n        int i = result.col_to_row[j];\n    \
    \    if (i == -1) continue;\n        assert(0 <= i && i < h);\n        assert(result.row_to_col[i]\
    \ == j);\n    }\n    assert(sum == result.cost);\n\n    auto pairs = result.matching();\n\
    \    assert(int(pairs.size()) == result.matching_size());\n    for (auto [row,\
    \ col] : pairs) assert(result.row_to_col[row] == col);\n}\n\nvoid test_hungarian_min()\
    \ {\n    std::vector<std::vector<long long>> square = {\n        {4, 1, 3},\n\
    \        {2, 0, 5},\n        {3, 2, 2},\n    };\n    auto sq = m1une::optimization::hungarian_min(square);\n\
    \    check_result(square, sq, 5);\n\n    std::vector<std::vector<long long>> wide\
    \ = {\n        {7, 4, 6, 8},\n        {5, 9, 3, 1},\n    };\n    check_result(wide,\
    \ m1une::optimization::hungarian(wide), brute_min(wide));\n\n    std::vector<std::vector<long\
    \ long>> tall = {\n        {9, 4},\n        {6, 7},\n        {5, 8},\n       \
    \ {1, 3},\n    };\n    auto tall_result = m1une::optimization::hungarian_min(tall);\n\
    \    check_result(tall, tall_result, brute_min(tall));\n    assert(tall_result.col_to_row[0]\
    \ != -1);\n    assert(tall_result.col_to_row[1] != -1);\n\n    std::vector<std::vector<long\
    \ long>> negative = {\n        {-4, 2, 0},\n        {3, -5, 1},\n    };\n    check_result(negative,\
    \ m1une::optimization::hungarian_min(negative), brute_min(negative));\n\n    std::vector<std::vector<long\
    \ long>> zero_cols(3);\n    check_result(zero_cols, m1une::optimization::hungarian_min(zero_cols),\
    \ 0);\n}\n\nvoid test_hungarian_max() {\n    std::vector<std::vector<long long>>\
    \ cost = {\n        {1, 8, 2},\n        {5, 3, 4},\n        {6, 7, 0},\n    };\n\
    \    check_result(cost, m1une::optimization::hungarian_max(cost), brute_max(cost));\n\
    }\n\nvoid test_against_bruteforce() {\n    for (int h = 1; h <= 4; h++) {\n  \
    \      for (int w = 1; w <= 4; w++) {\n            std::vector<std::vector<long\
    \ long>> cost(h, std::vector<long long>(w));\n            for (int i = 0; i <\
    \ h; i++) {\n                for (int j = 0; j < w; j++) {\n                 \
    \   cost[i][j] = ((i + 2) * (j + 3) * 5 + i * 7 - j * 11) % 17 - 8;\n        \
    \        }\n            }\n            check_result(cost, m1une::optimization::hungarian_min(cost),\
    \ brute_min(cost));\n            check_result(cost, m1une::optimization::hungarian_max(cost),\
    \ brute_max(cost));\n        }\n    }\n}\n\nint main() {\n    test_hungarian_min();\n\
    \    test_hungarian_max();\n    test_against_bruteforce();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - optimization/hungarian.hpp
  isVerificationFile: true
  path: verify/optimization/hungarian.test.cpp
  requiredBy: []
  timestamp: '2026-06-17 10:25:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/hungarian.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/hungarian.test.cpp
- /verify/verify/optimization/hungarian.test.cpp.html
title: verify/optimization/hungarian.test.cpp
---
