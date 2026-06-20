#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../optimization/hungarian.hpp"

long long brute_min(const std::vector<std::vector<long long>>& cost) {
    int h = int(cost.size());
    int w = h == 0 ? 0 : int(cost[0].size());
    if (h == 0 || w == 0) return 0;

    long long best = std::numeric_limits<long long>::max() / 4;
    if (h <= w) {
        std::vector<int> perm(w);
        for (int i = 0; i < w; i++) perm[i] = i;
        do {
            long long sum = 0;
            for (int i = 0; i < h; i++) sum += cost[i][perm[i]];
            best = std::min(best, sum);
        } while (std::next_permutation(perm.begin(), perm.end()));
    } else {
        std::vector<int> perm(h);
        for (int i = 0; i < h; i++) perm[i] = i;
        do {
            long long sum = 0;
            for (int j = 0; j < w; j++) sum += cost[perm[j]][j];
            best = std::min(best, sum);
        } while (std::next_permutation(perm.begin(), perm.end()));
    }
    return best;
}

long long brute_max(const std::vector<std::vector<long long>>& cost) {
    std::vector<std::vector<long long>> negated = cost;
    for (auto& row : negated) {
        for (auto& x : row) x = -x;
    }
    return -brute_min(negated);
}

void check_result(const std::vector<std::vector<long long>>& cost,
                  const m1une::optimization::HungarianResult<long long>& result,
                  long long expected) {
    int h = int(cost.size());
    int w = h == 0 ? 0 : int(cost[0].size());
    assert(int(result.row_to_col.size()) == h);
    assert(int(result.col_to_row.size()) == w);
    assert(result.matching_size() == std::min(h, w));
    assert(result.cost == expected);

    std::vector<bool> used_cols(w, false);
    long long sum = 0;
    for (int i = 0; i < h; i++) {
        int j = result.row_to_col[i];
        if (j == -1) continue;
        assert(0 <= j && j < w);
        assert(!used_cols[j]);
        assert(result.col_to_row[j] == i);
        used_cols[j] = true;
        sum += cost[i][j];
    }
    for (int j = 0; j < w; j++) {
        int i = result.col_to_row[j];
        if (i == -1) continue;
        assert(0 <= i && i < h);
        assert(result.row_to_col[i] == j);
    }
    assert(sum == result.cost);

    auto pairs = result.matching();
    assert(int(pairs.size()) == result.matching_size());
    for (auto [row, col] : pairs) assert(result.row_to_col[row] == col);
}

void test_hungarian_min() {
    std::vector<std::vector<long long>> square = {
        {4, 1, 3},
        {2, 0, 5},
        {3, 2, 2},
    };
    auto sq = m1une::optimization::hungarian_min(square);
    check_result(square, sq, 5);

    std::vector<std::vector<long long>> wide = {
        {7, 4, 6, 8},
        {5, 9, 3, 1},
    };
    check_result(wide, m1une::optimization::hungarian(wide), brute_min(wide));

    std::vector<std::vector<long long>> tall = {
        {9, 4},
        {6, 7},
        {5, 8},
        {1, 3},
    };
    auto tall_result = m1une::optimization::hungarian_min(tall);
    check_result(tall, tall_result, brute_min(tall));
    assert(tall_result.col_to_row[0] != -1);
    assert(tall_result.col_to_row[1] != -1);

    std::vector<std::vector<long long>> negative = {
        {-4, 2, 0},
        {3, -5, 1},
    };
    check_result(negative, m1une::optimization::hungarian_min(negative), brute_min(negative));

    std::vector<std::vector<long long>> zero_cols(3);
    check_result(zero_cols, m1une::optimization::hungarian_min(zero_cols), 0);
}

void test_hungarian_max() {
    std::vector<std::vector<long long>> cost = {
        {1, 8, 2},
        {5, 3, 4},
        {6, 7, 0},
    };
    check_result(cost, m1une::optimization::hungarian_max(cost), brute_max(cost));
}

void test_against_bruteforce() {
    for (int h = 1; h <= 4; h++) {
        for (int w = 1; w <= 4; w++) {
            std::vector<std::vector<long long>> cost(h, std::vector<long long>(w));
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    cost[i][j] = ((i + 2) * (j + 3) * 5 + i * 7 - j * 11) % 17 - 8;
                }
            }
            check_result(cost, m1une::optimization::hungarian_min(cost), brute_min(cost));
            check_result(cost, m1une::optimization::hungarian_max(cost), brute_max(cost));
        }
    }
}

int main() {
    test_hungarian_min();
    test_hungarian_max();
    test_against_bruteforce();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
