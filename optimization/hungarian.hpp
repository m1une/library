#ifndef M1UNE_OPTIMIZATION_HUNGARIAN_HPP
#define M1UNE_OPTIMIZATION_HUNGARIAN_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace optimization {

template <class T>
struct HungarianResult {
    T cost;
    std::vector<int> row_to_col;
    std::vector<int> col_to_row;

    int matching_size() const {
        int result = 0;
        for (int col : row_to_col) {
            if (col != -1) result++;
        }
        return result;
    }

    std::vector<std::pair<int, int>> matching() const {
        std::vector<std::pair<int, int>> result;
        for (int row = 0; row < int(row_to_col.size()); row++) {
            if (row_to_col[row] != -1) result.push_back({row, row_to_col[row]});
        }
        return result;
    }
};

namespace detail {

template <class T>
T assignment_cost(const std::vector<std::vector<T>>& cost, const std::vector<int>& row_to_col) {
    T result = T();
    for (int row = 0; row < int(row_to_col.size()); row++) {
        if (row_to_col[row] != -1) result += cost[row][row_to_col[row]];
    }
    return result;
}

}  // namespace detail

template <class T>
HungarianResult<T> hungarian_min(const std::vector<std::vector<T>>& cost) {
    int row_count = int(cost.size());
    int col_count = row_count == 0 ? 0 : int(cost[0].size());
    for (const auto& row : cost) assert(int(row.size()) == col_count);

    HungarianResult<T> result;
    result.cost = T();
    result.row_to_col.assign(row_count, -1);
    result.col_to_row.assign(col_count, -1);
    if (row_count == 0 || col_count == 0) return result;

    bool transposed = row_count > col_count;
    int n = transposed ? col_count : row_count;
    int m = transposed ? row_count : col_count;
    T inf = std::numeric_limits<T>::max() / T(4);

    std::vector<T> u(n + 1, T()), v(m + 1, T()), minv(m + 1);
    std::vector<int> p(m + 1, 0), way(m + 1, 0);

    auto value = [&](int i, int j) -> T {
        return transposed ? cost[j][i] : cost[i][j];
    };

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        std::fill(minv.begin(), minv.end(), inf);
        std::vector<char> used(m + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0];
            int j1 = 0;
            T delta = inf;

            for (int j = 1; j <= m; j++) {
                if (used[j]) continue;
                T cur = value(i0 - 1, j - 1) - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (int j = 0; j <= m; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    for (int j = 1; j <= m; j++) {
        if (p[j] == 0) continue;
        int i = p[j] - 1;
        int matched = j - 1;
        if (transposed) {
            int row = matched;
            int col = i;
            result.row_to_col[row] = col;
            result.col_to_row[col] = row;
        } else {
            int row = i;
            int col = matched;
            result.row_to_col[row] = col;
            result.col_to_row[col] = row;
        }
    }
    result.cost = detail::assignment_cost(cost, result.row_to_col);
    return result;
}

template <class T>
HungarianResult<T> hungarian_max(const std::vector<std::vector<T>>& cost) {
    std::vector<std::vector<T>> negated = cost;
    for (auto& row : negated) {
        for (auto& x : row) x = -x;
    }
    auto result = hungarian_min(negated);
    result.cost = detail::assignment_cost(cost, result.row_to_col);
    return result;
}

template <class T>
HungarianResult<T> hungarian(const std::vector<std::vector<T>>& cost) {
    return hungarian_min(cost);
}

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_HUNGARIAN_HPP
