#ifndef M1UNE_MONGE_SMAWK_HPP
#define M1UNE_MONGE_SMAWK_HPP 1

#include <cassert>
#include <functional>
#include <numeric>
#include <vector>

namespace m1une {
namespace monge {

namespace smawk_detail {

template <class Value, class Compare>
void solve(const std::vector<int>& rows, const std::vector<int>& columns,
           const Value& value, const Compare& compare, std::vector<int>& answer) {
    if (rows.empty()) return;

    std::vector<int> reduced;
    reduced.reserve(columns.size());
    for (int column : columns) {
        while (!reduced.empty()) {
            int row = rows[int(reduced.size()) - 1];
            if (!compare(value(row, column), value(row, reduced.back()))) break;
            reduced.pop_back();
        }
        if (reduced.size() < rows.size()) reduced.push_back(column);
    }

    std::vector<int> odd_rows;
    odd_rows.reserve(rows.size() / 2);
    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);
    solve(odd_rows, reduced, value, compare, answer);

    int left = 0;
    int right = 0;
    for (int i = 0; i < int(rows.size()); i += 2) {
        if (i + 1 < int(rows.size())) {
            while (reduced[right] != answer[rows[i + 1]]) right++;
        } else {
            right = int(reduced.size()) - 1;
        }

        int best = left;
        for (int j = left + 1; j <= right; j++) {
            if (compare(value(rows[i], reduced[j]), value(rows[i], reduced[best]))) {
                best = j;
            }
        }
        answer[rows[i]] = reduced[best];
        left = right;
    }
}

}  // namespace smawk_detail

template <class Value, class Compare = std::less<>>
std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,
                                  Compare compare = Compare()) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    std::vector<int> answer(row_count, -1);
    if (row_count == 0 || column_count == 0) return answer;

    std::vector<int> rows(row_count), columns(column_count);
    std::iota(rows.begin(), rows.end(), 0);
    std::iota(columns.begin(), columns.end(), 0);
    smawk_detail::solve(rows, columns, value, compare, answer);
    return answer;
}

template <class Value>
std::vector<int> smawk_row_argmin(int row_count, int column_count, Value value) {
    return smawk_row_optima(row_count, column_count, value, std::less<>());
}

template <class Value>
std::vector<int> smawk_row_argmax(int row_count, int column_count, Value value) {
    return smawk_row_optima(row_count, column_count, value, std::greater<>());
}

template <class T>
std::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return smawk_row_argmin(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

template <class T>
std::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return smawk_row_argmax(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_SMAWK_HPP
