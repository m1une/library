---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monge/check.hpp
    title: Monge Checks
  - icon: ':heavy_check_mark:'
    path: monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
  - icon: ':heavy_check_mark:'
    path: monge/knuth_optimization.hpp
    title: Knuth Optimization
  - icon: ':heavy_check_mark:'
    path: monge/larsch.hpp
    title: LARSCH
  - icon: ':heavy_check_mark:'
    path: monge/min_plus_convolution.hpp
    title: Structured Min-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: monge/monotone_minima.hpp
    title: Monotone Minima
  - icon: ':heavy_check_mark:'
    path: monge/smawk.hpp
    title: SMAWK
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/all.hpp\"\n\n\n\n#line 1 \"monge/check.hpp\"\n\n\n\
    \n#include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace monge\
    \ {\n\ntemplate <class Value>\nbool is_monge(int row_count, int column_count,\
    \ Value value) {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n\
    \    for (int row = 0; row + 1 < row_count; row++) {\n        for (int column\
    \ = 0; column + 1 < column_count; column++) {\n            if (value(row, column)\
    \ + value(row + 1, column + 1) >\n                value(row, column + 1) + value(row\
    \ + 1, column)) {\n                return false;\n            }\n        }\n \
    \   }\n    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
    \ int column_count, Value value) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    for (int row = 0; row + 1 < row_count; row++) {\n        for (int\
    \ column = 0; column + 1 < column_count; column++) {\n            if (value(row,\
    \ column) + value(row + 1, column + 1) <\n                value(row, column +\
    \ 1) + value(row + 1, column)) {\n                return false;\n            }\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_monge(row_count,\
    \ column_count,\n                    [&](int row, int column) -> const T& { return\
    \ matrix[row][column]; });\n}\n\ntemplate <class T>\nbool is_anti_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_anti_monge(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monge/divide_and_conquer_optimization.hpp\"\n\n\n\n#include\
    \ <type_traits>\n#include <utility>\n#line 7 \"monge/divide_and_conquer_optimization.hpp\"\
    \n\n#line 1 \"monge/monotone_minima.hpp\"\n\n\n\n#line 5 \"monge/monotone_minima.hpp\"\
    \n#include <functional>\n#line 7 \"monge/monotone_minima.hpp\"\n\nnamespace m1une\
    \ {\nnamespace monge {\n\nnamespace monotone_minima_detail {\n\ntemplate <class\
    \ Value, class Compare>\nvoid solve(int row_left, int row_right, int column_left,\
    \ int column_right,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (row_left == row_right) return;\n    int row = (row_left +\
    \ row_right) / 2;\n    int best = column_left;\n    for (int column = column_left\
    \ + 1; column < column_right; column++) {\n        if (compare(value(row, column),\
    \ value(row, best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 9 \"monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\ntemplate <class\
    \ Value>\nauto divide_and_conquer_dp(int state_count, int candidate_count, Value\
    \ value)\n    -> DivideAndConquerDpResult<\n        std::decay_t<std::invoke_result_t<Value,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;\n\
    \    DivideAndConquerDpResult<T> result;\n    result.argmin = monotone_row_argmin(state_count,\
    \ candidate_count, value);\n    result.value.resize(state_count);\n    for (int\
    \ state = 0; state < state_count; state++) {\n        if (result.argmin[state]\
    \ != -1) {\n            result.value[state] = value(state, result.argmin[state]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class T, class Cost>\nauto\
    \ divide_and_conquer_transition(const std::vector<T>& previous, int state_count,\n\
    \                                   Cost cost)\n    -> DivideAndConquerDpResult<\n\
    \        std::decay_t<decltype(std::declval<T>() + cost(0, 0))>> {\n    using\
    \ Result = std::decay_t<decltype(std::declval<T>() + cost(0, 0))>;\n    return\
    \ divide_and_conquer_dp(\n        state_count, int(previous.size()),\n       \
    \ [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monge/knuth_optimization.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 8 \"monge/knuth_optimization.hpp\"\n\nnamespace m1une {\nnamespace monge\
    \ {\n\ntemplate <class T>\nstruct KnuthOptimizationResult {\n    std::vector<std::vector<T>>\
    \ value;\n    std::vector<std::vector<int>> split;\n\n    T optimum() const {\n\
    \        return value[0].back();\n    }\n};\n\ntemplate <class IntervalCost>\n\
    auto knuth_optimization(int element_count, IntervalCost interval_cost)\n    ->\
    \ KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 1 \"monge/larsch.hpp\"\
    \n\n\n\n#line 6 \"monge/larsch.hpp\"\n#include <memory>\n#line 10 \"monge/larsch.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nclass Larsch {\n\
    \    struct ReduceColumn;\n\n    struct ReduceRow {\n        int size;\n     \
    \   std::function<T(int, int)> value;\n        int current_row = 0;\n        int\
    \ boundary = 0;\n        std::unique_ptr<ReduceColumn> recursive;\n\n        explicit\
    \ ReduceRow(int size_) : size(size_) {\n            if (size / 2 != 0) recursive\
    \ = std::make_unique<ReduceColumn>(size / 2);\n        }\n\n        void set_value(std::function<T(int,\
    \ int)> value_) {\n            value = std::move(value_);\n            if (recursive)\
    \ {\n                recursive->set_value(\n                    [&](int row, int\
    \ column) { return value(row * 2 + 1, column); });\n            }\n        }\n\
    \n        int next_argmin() {\n            int row = current_row++;\n        \
    \    if (row % 2 == 0) {\n                int previous = boundary;\n         \
    \       int next = row + 1 == size ? size - 1 : recursive->next_argmin();\n  \
    \              boundary = next;\n                int best = previous;\n      \
    \          for (int column = previous + 1; column <= next; column++) {\n     \
    \               if (value(row, column) < value(row, best)) best = column;\n  \
    \              }\n                return best;\n            }\n            return\
    \ value(row, boundary) <= value(row, row) ? boundary : row;\n        }\n    };\n\
    \n    struct ReduceColumn {\n        int size;\n        std::function<T(int, int)>\
    \ value;\n        int current_row = 0;\n        std::vector<int> columns;\n  \
    \      ReduceRow recursive;\n\n        explicit ReduceColumn(int size_) : size(size_),\
    \ recursive(size_) {}\n\n        void set_value(std::function<T(int, int)> value_)\
    \ {\n            value = std::move(value_);\n            recursive.set_value(\n\
    \                [&](int row, int column) { return value(row, columns[column]);\
    \ });\n        }\n\n        int next_argmin() {\n            int row = current_row++;\n\
    \            int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row\
    \ * 2;\n            for (int column = first; column <= last; column++) {\n   \
    \             while (int(columns.size()) != row &&\n                       value(int(columns.size())\
    \ - 1, columns.back()) >\n                           value(int(columns.size())\
    \ - 1, column)) {\n                    columns.pop_back();\n                }\n\
    \                if (int(columns.size()) != size) columns.push_back(column);\n\
    \            }\n            return columns[recursive.next_argmin()];\n       \
    \ }\n    };\n\n    int _size;\n    int _processed = 0;\n    std::unique_ptr<ReduceRow>\
    \ _base;\n\n   public:\n    template <class Value>\n    explicit Larsch(int size,\
    \ Value value)\n        : _size(size), _base(std::make_unique<ReduceRow>(size))\
    \ {\n        assert(size >= 0);\n        _base->set_value(std::function<T(int,\
    \ int)>(std::move(value)));\n    }\n\n    int size() const {\n        return _size;\n\
    \    }\n\n    int processed_rows() const {\n        return _processed;\n    }\n\
    \n    bool finished() const {\n        return _processed == _size;\n    }\n\n\
    \    int next_argmin() {\n        assert(!finished());\n        _processed++;\n\
    \        return _base->next_argmin();\n    }\n};\n\ntemplate <class T>\nstruct\
    \ LarschShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\ntemplate <class Cost>\nauto larsch_shortest_path(int vertex_count,\
    \ Cost cost)\n    -> LarschShortestPathResult<\n        std::decay_t<std::invoke_result_t<Cost,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;\n\
    \    assert(vertex_count >= 0);\n\n    LarschShortestPathResult<T> result;\n \
    \   result.distance.assign(vertex_count, T());\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count <= 1) return result;\n\n    Larsch<T> optimizer(vertex_count\
    \ - 1, [&](int row, int column) {\n        return result.distance[column] + cost(column,\
    \ row + 1);\n    });\n    for (int vertex = 1; vertex < vertex_count; vertex++)\
    \ {\n        int parent = optimizer.next_argmin();\n        result.parent[vertex]\
    \ = parent;\n        result.distance[vertex] = result.distance[parent] + cost(parent,\
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monge/min_plus_convolution.hpp\"\n\n\n\n#line 6 \"monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\nnamespace convolution_detail {\n\n\
    template <class T, class Compare>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare) {\n    if\
    \ (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size =\
    \ int(arbitrary.size());\n    int second_size = int(structured.size());\n    int\
    \ result_size = first_size + second_size - 1;\n    std::vector<T> result(result_size);\n\
    \n    auto solve = [&](auto self, int result_left, int result_right, int candidate_left,\n\
    \                     int candidate_right) -> void {\n        if (result_left\
    \ == result_right) return;\n        int index = (result_left + result_right) /\
    \ 2;\n        int left = candidate_left > index - second_size + 1 ? candidate_left\n\
    \                                                            : index - second_size\
    \ + 1;\n        int right = candidate_right < index + 1 ? candidate_right : index\
    \ + 1;\n\n        int best = left;\n        T best_value = arbitrary[best] + structured[index\
    \ - best];\n        for (int candidate = left + 1; candidate < right; candidate++)\
    \ {\n            T current = arbitrary[candidate] + structured[index - candidate];\n\
    \            if (compare(current, best_value)) {\n                best = candidate;\n\
    \                best_value = current;\n            }\n        }\n        result[index]\
    \ = best_value;\n        self(self, result_left, index, candidate_left, best +\
    \ 1);\n        self(self, index + 1, result_right, best, candidate_right);\n \
    \   };\n\n    solve(solve, 0, result_size, 0, first_size);\n    return result;\n\
    }\n\n}  // namespace convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence) {\n    for\
    \ (int i = 1; i + 1 < int(sequence.size()); i++) {\n        if (sequence[i] -\
    \ sequence[i - 1] < sequence[i + 1] - sequence[i]) {\n            return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const\
    \ std::vector<T>& arbitrary,\n                                           const\
    \ std::vector<T>& convex) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ convex, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n\n#line 1 \"monge/smawk.hpp\"\n\n\n\n#line 6 \"monge/smawk.hpp\"\n#include <numeric>\n\
    #line 8 \"monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace monge {\n\nnamespace\
    \ smawk_detail {\n\ntemplate <class Value, class Compare>\nvoid solve(const std::vector<int>&\
    \ rows, const std::vector<int>& columns,\n           const Value& value, const\
    \ Compare& compare, std::vector<int>& answer) {\n    if (rows.empty()) return;\n\
    \n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n    for\
    \ (int column : columns) {\n        while (!reduced.empty()) {\n            int\
    \ row = rows[int(reduced.size()) - 1];\n            if (!compare(value(row, column),\
    \ value(row, reduced.back()))) break;\n            reduced.pop_back();\n     \
    \   }\n        if (reduced.size() < rows.size()) reduced.push_back(column);\n\
    \    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size() / 2);\n\
    \    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, value, compare, answer);\n\n    int left = 0;\n\
    \    int right = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n   \
    \     if (i + 1 < int(rows.size())) {\n            while (reduced[right] != answer[rows[i\
    \ + 1]]) right++;\n        } else {\n            right = int(reduced.size()) -\
    \ 1;\n        }\n\n        int best = left;\n        for (int j = left + 1; j\
    \ <= right; j++) {\n            if (compare(value(rows[i], reduced[j]), value(rows[i],\
    \ reduced[best]))) {\n                best = j;\n            }\n        }\n  \
    \      answer[rows[i]] = reduced[best];\n        left = right;\n    }\n}\n\n}\
    \  // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    std::vector<int> answer(row_count,\
    \ -1);\n    if (row_count == 0 || column_count == 0) return answer;\n\n    std::vector<int>\
    \ rows(row_count), columns(column_count);\n    std::iota(rows.begin(), rows.end(),\
    \ 0);\n    std::iota(columns.begin(), columns.end(), 0);\n    smawk_detail::solve(rows,\
    \ columns, value, compare, answer);\n    return answer;\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> smawk_row_argmin(int row_count, int column_count, Value\
    \ value) {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return smawk_row_argmin(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ smawk_row_argmax(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return smawk_row_argmax(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\n}  // namespace\
    \ monge\n}  // namespace m1une\n\n\n#line 11 \"monge/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_MONGE_ALL_HPP

    #define M1UNE_MONGE_ALL_HPP 1


    #include "check.hpp"

    #include "divide_and_conquer_optimization.hpp"

    #include "knuth_optimization.hpp"

    #include "larsch.hpp"

    #include "min_plus_convolution.hpp"

    #include "monotone_minima.hpp"

    #include "smawk.hpp"


    #endif  // M1UNE_MONGE_ALL_HPP

    '
  dependsOn:
  - monge/check.hpp
  - monge/divide_and_conquer_optimization.hpp
  - monge/monotone_minima.hpp
  - monge/knuth_optimization.hpp
  - monge/larsch.hpp
  - monge/min_plus_convolution.hpp
  - monge/smawk.hpp
  isVerificationFile: false
  path: monge/all.hpp
  requiredBy: []
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/all.hpp
layout: document
title: Monge All
---

## Overview

`monge/all.hpp` includes the repository's Monge and monotone-matrix algorithms.

## Included Headers

| Header | Contents |
| --- | --- |
| `monge/smawk.hpp` | Linear-time row optima for implicit totally monotone matrices. |
| `monge/monotone_minima.hpp` | Divide-and-conquer row optima under monotone argmins. |
| `monge/divide_and_conquer_optimization.hpp` | DP-facing divide-and-conquer optimization returning values and choices. |
| `monge/knuth_optimization.hpp` | Quadratic Knuth optimization for interval DP. |
| `monge/larsch.hpp` | Linear-time online minima and shortest paths for triangular totally monotone matrices. |
| `monge/check.hpp` | Monge and anti-Monge quadrangle-inequality checks. |
| `monge/min_plus_convolution.hpp` | Fast min-plus convolution with a convex sequence and max-plus convolution with a concave sequence. |
