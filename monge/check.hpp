#ifndef M1UNE_MONGE_CHECK_HPP
#define M1UNE_MONGE_CHECK_HPP 1

#include <cassert>
#include <vector>

namespace m1une {
namespace monge {

template <class Value>
bool is_monge(int row_count, int column_count, Value value) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    for (int row = 0; row + 1 < row_count; row++) {
        for (int column = 0; column + 1 < column_count; column++) {
            if (value(row, column) + value(row + 1, column + 1) >
                value(row, column + 1) + value(row + 1, column)) {
                return false;
            }
        }
    }
    return true;
}

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    for (int row = 0; row + 1 < row_count; row++) {
        for (int column = 0; column + 1 < column_count; column++) {
            if (value(row, column) + value(row + 1, column + 1) <
                value(row, column + 1) + value(row + 1, column)) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return is_monge(row_count, column_count,
                    [&](int row, int column) -> const T& { return matrix[row][column]; });
}

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return is_anti_monge(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_CHECK_HPP
