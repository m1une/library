#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../monge/all.hpp"

void test_divide_and_conquer_dp() {
    for (int states = 0; states <= 60; states++) {
        for (int candidates = 0; candidates <= 60; candidates++) {
            auto value = [&](int state, int candidate) {
                long long difference = state * 3LL - candidate * 2LL;
                return difference * difference + candidate * 5LL;
            };
            auto result = m1une::monge::divide_and_conquer_dp(states, candidates, value);
            assert(int(result.value.size()) == states);
            assert(int(result.argmin.size()) == states);
            for (int state = 0; state < states; state++) {
                if (candidates == 0) {
                    assert(result.argmin[state] == -1);
                    continue;
                }
                int best = 0;
                for (int candidate = 1; candidate < candidates; candidate++) {
                    if (value(state, candidate) < value(state, best)) best = candidate;
                }
                assert(result.argmin[state] == best);
                assert(result.value[state] == value(state, best));
            }
        }
    }

    std::vector<long long> previous = {7, 1, 9, 3, 6};
    auto result = m1une::monge::divide_and_conquer_transition(
        previous, 8, [](int candidate, int state) {
            long long difference = state - candidate;
            return difference * difference;
        });
    for (int state = 0; state < 8; state++) {
        long long expected = std::numeric_limits<long long>::max();
        for (int candidate = 0; candidate < int(previous.size()); candidate++) {
            long long difference = state - candidate;
            expected = std::min(expected, previous[candidate] + difference * difference);
        }
        assert(result.value[state] == expected);
    }
}

void test_knuth_optimization() {
    for (int n = 0; n <= 45; n++) {
        for (int test = 0; test < 20; test++) {
            std::vector<long long> weight(n);
            for (int i = 0; i < n; i++) weight[i] = (test * 7 + i * 11 + n) % 13;
            std::vector<long long> prefix(n + 1);
            for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + weight[i];
            auto interval_cost = [&](int left, int right) {
                return prefix[right] - prefix[left];
            };

            auto result = m1une::monge::knuth_optimization(n, interval_cost);
            std::vector<std::vector<long long>> expected(
                n + 1, std::vector<long long>(n + 1));
            for (int length = 2; length <= n; length++) {
                for (int left = 0; left + length <= n; left++) {
                    int right = left + length;
                    expected[left][right] = std::numeric_limits<long long>::max();
                    for (int split = left + 1; split < right; split++) {
                        expected[left][right] =
                            std::min(expected[left][right],
                                     expected[left][split] + expected[split][right] +
                                         interval_cost(left, right));
                    }
                }
            }
            assert(result.value == expected);
            assert(result.optimum() == expected[0][n]);

            for (int length = 2; length <= n; length++) {
                for (int left = 0; left + length <= n; left++) {
                    int right = left + length;
                    int split = result.split[left][right];
                    assert(result.split[left][right - 1] <= split);
                    assert(split <= result.split[left + 1][right]);
                    assert(result.value[left][right] ==
                           result.value[left][split] + result.value[split][right] +
                               interval_cost(left, right));
                }
            }
        }
    }
}

void test_larsch_triangular_matrix() {
    for (int n = 0; n <= 100; n++) {
        int evaluations = 0;
        auto raw_value = [&](int row, int column) {
            long long difference = row * 2LL - column * 3LL;
            return difference * difference + column * 4LL;
        };
        auto value = [&](int row, int column) {
            evaluations++;
            return raw_value(row, column);
        };
        m1une::monge::Larsch<long long> larsch(n, value);
        assert(larsch.size() == n);
        for (int row = 0; row < n; row++) {
            int expected = 0;
            for (int column = 1; column <= row; column++) {
                if (raw_value(row, column) < raw_value(row, expected)) expected = column;
            }
            assert(larsch.next_argmin() == expected);
            assert(larsch.processed_rows() == row + 1);
        }
        assert(larsch.finished());
        if (n != 0) assert(evaluations <= 50 * n);
    }

    m1une::monge::Larsch<int> ties(80, [](int, int) { return 0; });
    for (int row = 0; row < 80; row++) assert(ties.next_argmin() == 0);
}

void test_larsch_shortest_path() {
    for (int n = 0; n <= 150; n++) {
        for (int test = 0; test < 12; test++) {
            std::vector<long long> position(n);
            for (int i = 1; i < n; i++) {
                position[i] = position[i - 1] + 1 + (test * 5 + i * 7) % 6;
            }
            int evaluations = 0;
            auto raw_cost = [&](int from, int to) {
                long long distance = position[to] - position[from];
                return distance * distance + 3;
            };
            auto cost = [&](int from, int to) {
                evaluations++;
                return raw_cost(from, to);
            };

            auto result = m1une::monge::larsch_shortest_path(n, cost);
            int larsch_evaluations = evaluations;
            std::vector<long long> expected(n);
            std::vector<int> parent(n, -1);
            for (int to = 1; to < n; to++) {
                expected[to] = expected[0] + raw_cost(0, to);
                parent[to] = 0;
                for (int from = 1; from < to; from++) {
                    long long candidate = expected[from] + raw_cost(from, to);
                    if (candidate < expected[to]) {
                        expected[to] = candidate;
                        parent[to] = from;
                    }
                }
            }
            assert(result.distance == expected);
            assert(result.parent == parent);
            if (n >= 2) assert(larsch_evaluations <= 80 * n);
        }
    }
}

int main() {
    test_divide_and_conquer_dp();
    test_knuth_optimization();
    test_larsch_triangular_matrix();
    test_larsch_shortest_path();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
