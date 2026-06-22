#ifndef M1UNE_MONGE_MONOTONE_MINIMA_HPP
#define M1UNE_MONGE_MONOTONE_MINIMA_HPP 1

#include <cassert>
#include <functional>
#include <vector>

namespace m1une {
namespace monge {

namespace monotone_minima_detail {

template <class Value, class Compare>
void solve(int row_left, int row_right, int column_left, int column_right,
           const Value& value, const Compare& compare, std::vector<int>& answer) {
    if (row_left == row_right) return;
    int row = (row_left + row_right) / 2;
    int best = column_left;
    for (int column = column_left + 1; column < column_right; column++) {
        if (compare(value(row, column), value(row, best))) best = column;
    }
    answer[row] = best;
    solve(row_left, row, column_left, best + 1, value, compare, answer);
    solve(row + 1, row_right, best, column_right, value, compare, answer);
}

}  // namespace monotone_minima_detail

template <class Value, class Compare = std::less<>>
std::vector<int> monotone_row_optima(int row_count, int column_count, Value value,
                                     Compare compare = Compare()) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    std::vector<int> answer(row_count, -1);
    if (row_count == 0 || column_count == 0) return answer;
    monotone_minima_detail::solve(0, row_count, 0, column_count, value, compare, answer);
    return answer;
}

template <class Value>
std::vector<int> monotone_row_argmin(int row_count, int column_count, Value value) {
    return monotone_row_optima(row_count, column_count, value, std::less<>());
}

template <class Value>
std::vector<int> monotone_row_argmax(int row_count, int column_count, Value value) {
    return monotone_row_optima(row_count, column_count, value, std::greater<>());
}

template <class T>
std::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return monotone_row_argmin(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

template <class T>
std::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return monotone_row_argmax(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_MONOTONE_MINIMA_HPP
