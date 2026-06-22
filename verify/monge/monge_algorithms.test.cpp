#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

#include "../../monge/all.hpp"

template <class Value, class Compare>
std::vector<int> brute_row_optima(int rows, int columns, Value value, Compare compare) {
    std::vector<int> result(rows, -1);
    if (columns == 0) return result;
    for (int row = 0; row < rows; row++) {
        result[row] = 0;
        for (int column = 1; column < columns; column++) {
            if (compare(value(row, column), value(row, result[row]))) {
                result[row] = column;
            }
        }
    }
    return result;
}

void test_smawk_monge() {
    for (int rows = 0; rows <= 40; rows++) {
        for (int columns = 0; columns <= 40; columns++) {
            auto value = [&](int row, int column) {
                long long difference = row * 3LL - column * 2LL;
                return difference * difference + row * 7LL + column * 5LL;
            };
            auto expected = brute_row_optima(rows, columns, value, std::less<>());
            assert(m1une::monge::smawk_row_argmin(rows, columns, value) == expected);
        }
    }
}

void test_smawk_totally_monotone_and_ties() {
    for (int rows = 1; rows <= 50; rows++) {
        for (int columns = 1; columns <= 50; columns++) {
            std::vector<int> threshold(rows);
            for (int row = 0; row < rows; row++) {
                threshold[row] = std::min(columns - 1, (row * 7 + rows) / 5);
            }
            auto value = [&](int row, int column) {
                int difference = column - threshold[row];
                return difference * difference;
            };
            auto result = m1une::monge::smawk_row_argmin(rows, columns, value);
            assert(result == threshold);
        }
    }

    auto constant = [](int, int) { return 0; };
    auto result = m1une::monge::smawk_row_argmin(20, 30, constant);
    assert(result == std::vector<int>(20, 0));
}

void test_smawk_max() {
    auto value = [](int row, int column) {
        long long difference = row - column;
        return -difference * difference;
    };
    auto expected = brute_row_optima(30, 25, value, std::greater<>());
    assert(m1une::monge::smawk_row_argmax(30, 25, value) == expected);
}

void test_smawk_matrix_overload_and_evaluations() {
    std::vector<std::vector<long long>> matrix(17, std::vector<long long>(23));
    for (int row = 0; row < 17; row++) {
        for (int column = 0; column < 23; column++) {
            long long difference = row * 2LL - column;
            matrix[row][column] = difference * difference;
        }
    }
    auto expected = brute_row_optima(
        17, 23, [&](int row, int column) { return matrix[row][column]; }, std::less<>());
    assert(m1une::monge::smawk_row_argmin(matrix) == expected);

    for (auto sizes : std::vector<std::pair<int, int>>{
             std::pair<int, int>{10, 1000},
             std::pair<int, int>{1000, 10},
             std::pair<int, int>{700, 900},
         }) {
        int evaluations = 0;
        auto value = [&](int row, int column) {
            evaluations++;
            long long difference = row * 3LL - column * 2LL;
            return difference * difference;
        };
        auto result = m1une::monge::smawk_row_argmin(sizes.first, sizes.second, value);
        assert(int(result.size()) == sizes.first);
        assert(evaluations <= 20 * (sizes.first + sizes.second));
    }
}

void test_monotone_minima() {
    for (int rows = 1; rows <= 40; rows++) {
        for (int columns = 1; columns <= 40; columns++) {
            std::vector<int> optimum(rows);
            for (int row = 0; row < rows; row++) {
                optimum[row] = std::min(columns - 1, row * columns / rows);
            }
            auto value = [&](int row, int column) {
                if (column == optimum[row]) return 0;
                return 1000 + (row * 97 + column * 53) % 101;
            };
            auto result = m1une::monge::monotone_row_argmin(rows, columns, value);
            assert(result == optimum);
        }
    }

    auto empty = m1une::monge::monotone_row_argmin(5, 0, [](int, int) { return 0; });
    assert(empty == std::vector<int>(5, -1));

    std::vector<std::vector<int>> matrix;
    matrix.emplace_back(std::vector<int>{0, 5, 7});
    matrix.emplace_back(std::vector<int>{4, 0, 8});
    matrix.emplace_back(std::vector<int>{9, 3, 0});
    assert(m1une::monge::monotone_row_argmin(matrix) == std::vector<int>({0, 1, 2}));
}

void test_monge_checks() {
    std::vector<std::vector<long long>> matrix(8, std::vector<long long>(11));
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 11; column++) {
            long long difference = row - column;
            matrix[row][column] = difference * difference;
        }
    }
    assert(m1une::monge::is_monge(matrix));
    assert(!m1une::monge::is_anti_monge(matrix));

    for (auto& row : matrix) {
        for (auto& value : row) value = -value;
    }
    assert(!m1une::monge::is_monge(matrix));
    assert(m1une::monge::is_anti_monge(matrix));

    std::vector<std::vector<int>> empty;
    assert(m1une::monge::is_monge(empty));
    assert(m1une::monge::is_anti_monge(empty));
}

template <class T, class Compare>
std::vector<T> brute_convolution(const std::vector<T>& first, const std::vector<T>& second,
                                 Compare compare) {
    if (first.empty() || second.empty()) return {};
    std::vector<T> result(first.size() + second.size() - 1);
    for (int index = 0; index < int(result.size()); index++) {
        int left = std::max(0, index - int(second.size()) + 1);
        int right = std::min(int(first.size()), index + 1);
        result[index] = first[left] + second[index - left];
        for (int i = left + 1; i < right; i++) {
            T value = first[i] + second[index - i];
            if (compare(value, result[index])) result[index] = value;
        }
    }
    return result;
}

void test_structured_convolutions() {
    for (int first_size = 0; first_size <= 35; first_size++) {
        for (int second_size = 0; second_size <= 35; second_size++) {
            for (int test = 0; test < 8; test++) {
                std::vector<long long> arbitrary(first_size);
                for (int i = 0; i < first_size; i++) {
                    arbitrary[i] = (test * 17 + i * 31 + first_size * 7) % 61 - 30;
                }

                std::vector<long long> convex(second_size);
                long long difference = -10 + test;
                for (int i = 1; i < second_size; i++) {
                    difference += (test * 3 + i * 5) % 4;
                    convex[i] = convex[i - 1] + difference;
                }
                assert(m1une::monge::is_convex_sequence(convex));
                auto expected_min = brute_convolution(arbitrary, convex, std::less<>());
                assert(m1une::monge::min_plus_convolution_convex(arbitrary, convex) ==
                       expected_min);

                std::vector<long long> concave = convex;
                for (auto& value : concave) value = -value;
                assert(m1une::monge::is_concave_sequence(concave));
                auto expected_max = brute_convolution(arbitrary, concave, std::greater<>());
                assert(m1une::monge::max_plus_convolution_concave(arbitrary, concave) ==
                       expected_max);
            }
        }
    }

    assert(!m1une::monge::is_convex_sequence(std::vector<int>{0, 2, 1}));
    assert(!m1une::monge::is_concave_sequence(std::vector<int>{0, -2, -1}));
}

int main() {
    test_smawk_monge();
    test_smawk_totally_monotone_and_ties();
    test_smawk_max();
    test_smawk_matrix_overload_and_evaluations();
    test_monotone_minima();
    test_monge_checks();
    test_structured_convolutions();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
