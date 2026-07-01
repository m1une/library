#ifndef M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP
#define M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace string {

namespace levenshtein_distance_detail {

template <class RowSequence, class ColumnSequence>
int solve(const RowSequence& rows, const ColumnSequence& columns) {
    int row_count = int(rows.size());
    int column_count = int(columns.size());
    std::vector<int> distance(column_count + 1);
    for (int column = 0; column <= column_count; column++) distance[column] = column;

    for (int row = 1; row <= row_count; row++) {
        int diagonal = distance[0];
        distance[0] = row;
        for (int column = 1; column <= column_count; column++) {
            int above = distance[column];
            int substitution = diagonal + (rows[row - 1] == columns[column - 1] ? 0 : 1);
            distance[column] =
                std::min({above + 1, distance[column - 1] + 1, substitution});
            diagonal = above;
        }
    }
    return distance[column_count];
}

template <class RowSequence, class ColumnSequence>
int solve_bounded(const RowSequence& rows, const ColumnSequence& columns,
                  int max_distance) {
    int row_count = int(rows.size());
    int column_count = int(columns.size());
    assert(column_count <= row_count);
    if (row_count - column_count > max_distance) return max_distance + 1;
    if (max_distance >= row_count) return solve(rows, columns);

    int infinity = max_distance + 1;
    int previous_left = 0;
    int previous_right = std::min(column_count, max_distance);
    std::vector<int> previous(previous_right + 1);
    for (int column = 0; column <= previous_right; column++) previous[column] = column;
    std::vector<int> current;

    for (int row = 1; row <= row_count; row++) {
        int current_left = std::max(0, row - max_distance);
        int current_right = int(std::min<long long>(column_count,
                                                    static_cast<long long>(row) + max_distance));
        current.assign(current_right - current_left + 1, infinity);

        for (int column = current_left; column <= current_right; column++) {
            int best = infinity;
            if (previous_left <= column && column <= previous_right) {
                best = std::min(best, previous[column - previous_left] + 1);
            }
            if (current_left < column) {
                best = std::min(best, current[column - current_left - 1] + 1);
            }
            if (0 < column && previous_left <= column - 1 && column - 1 <= previous_right) {
                int substitution = previous[column - 1 - previous_left] +
                                   (rows[row - 1] == columns[column - 1] ? 0 : 1);
                best = std::min(best, substitution);
            }
            current[column - current_left] = std::min(best, infinity);
        }

        previous.swap(current);
        previous_left = current_left;
        previous_right = current_right;
    }
    return previous[column_count - previous_left];
}

}  // namespace levenshtein_distance_detail

// Returns the minimum number of insertions, deletions, and substitutions
// needed to transform first into second.
template <class Sequence1, class Sequence2>
int levenshtein_distance(const Sequence1& first, const Sequence2& second) {
    if (first.size() < second.size()) {
        return levenshtein_distance_detail::solve(second, first);
    }
    return levenshtein_distance_detail::solve(first, second);
}

// Returns the exact distance when it is at most max_distance, and
// max_distance + 1 otherwise.
template <class Sequence1, class Sequence2>
int levenshtein_distance(const Sequence1& first, const Sequence2& second,
                         int max_distance) {
    assert(0 <= max_distance);
    if (first.size() < second.size()) {
        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);
    }
    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_LEVENSHTEIN_DISTANCE_HPP
