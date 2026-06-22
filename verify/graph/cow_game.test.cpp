#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../graph/all.hpp"

using CowGame = m1une::graph::CowGame<long long>;

void test_basic_constraints() {
    CowGame game(4);
    int first = game.add_upper_bound(0, 1, 5);
    game.add_lower_bound(0, 1, 2);
    game.add_bounds(1, 2, -1, 4);
    game.add_equality(2, 3, 3);

    assert(game.size() == 4);
    assert(game.constraint_count() == 6);
    assert(game.get_constraint(first).from == 0);
    assert(game.get_constraint(first).to == 1);
    assert(game.get_constraint(first).upper_bound == 5);

    auto solution = game.solve();
    assert(solution.is_feasible());
    assert(solution.value.size() == 4);
    for (const auto& constraint : game.constraints()) {
        assert(solution.value[constraint.to] - solution.value[constraint.from] <=
               constraint.upper_bound);
    }

    auto bounds = game.difference_bounds(0, 3);
    assert(bounds.is_feasible());
    assert(bounds.bounded_below());
    assert(bounds.bounded_above());
    assert(*bounds.lower_bound == 4);
    assert(*bounds.upper_bound == 12);

    auto all = game.tightest_upper_bounds(0);
    assert(all.is_feasible());
    assert(all.bounded(0));
    assert(all.bounded(3));
    assert(all.upper_bound[0] == 0);
    assert(all.upper_bound[3] == 12);
}

void test_infeasible() {
    CowGame game(2);
    game.add_lower_bound(0, 1, 5);
    assert(game.is_feasible());
    assert(game.solve().is_feasible());

    game.add_upper_bound(0, 1, 3);

    assert(!game.is_feasible());
    assert(!game.solve().is_feasible());
    assert(!game.tightest_upper_bounds(0).is_feasible());
    assert(!game.difference_bounds(0, 1).is_feasible());
}

void test_unbounded() {
    CowGame game(4);
    game.add_upper_bound(0, 1, 7);
    game.add_upper_bound(2, 3, 2);

    auto one_way = game.difference_bounds(0, 1);
    assert(one_way.is_feasible());
    assert(!one_way.bounded_below());
    assert(one_way.bounded_above());
    assert(*one_way.upper_bound == 7);

    auto disconnected = game.difference_bounds(0, 3);
    assert(disconnected.is_feasible());
    assert(!disconnected.bounded_below());
    assert(!disconnected.bounded_above());

    auto all = game.tightest_upper_bounds(0);
    assert(all.bounded(0));
    assert(all.bounded(1));
    assert(!all.bounded(2));
    assert(!all.bounded(3));
}

void test_alias_and_empty() {
    m1une::graph::DifferenceConstraints<long long> constraints(0);
    auto solution = constraints.solve();
    assert(solution.is_feasible());
    assert(solution.value.empty());
}

void test_against_warshall_floyd() {
    constexpr long long inf = std::numeric_limits<long long>::max() / 4;
    for (int n = 1; n <= 7; n++) {
        for (int test = 0; test < 80; test++) {
            CowGame game(n);
            std::vector<std::vector<long long>> dist(
                n, std::vector<long long>(n, inf));
            for (int i = 0; i < n; i++) dist[i][i] = 0;

            for (int from = 0; from < n; from++) {
                for (int to = 0; to < n; to++) {
                    if ((test * 5 + from * 7 + to * 11) % 6 != 0) continue;
                    long long upper_bound = (test * 3 + from * 5 + to * 2) % 13 - 6;
                    game.add_constraint(from, to, upper_bound);
                    dist[from][to] = std::min(dist[from][to], upper_bound);
                }
            }

            dist = m1une::graph::warshall_floyd(std::move(dist), inf);
            bool feasible = !m1une::graph::has_negative_cycle(dist);
            assert(game.is_feasible() == feasible);

            auto solution = game.solve();
            assert(solution.is_feasible() == feasible);
            if (!feasible) continue;
            for (const auto& constraint : game.constraints()) {
                assert(solution.value[constraint.to] - solution.value[constraint.from] <=
                       constraint.upper_bound);
            }

            for (int source = 0; source < n; source++) {
                auto upper = game.tightest_upper_bounds(source);
                assert(upper.is_feasible());
                for (int target = 0; target < n; target++) {
                    assert(upper.bounded(target) == (dist[source][target] != inf));
                    if (upper.bounded(target)) {
                        assert(upper.upper_bound[target] == dist[source][target]);
                    }

                    auto bounds = game.difference_bounds(source, target);
                    assert(bounds.is_feasible());
                    assert(bounds.bounded_above() == (dist[source][target] != inf));
                    assert(bounds.bounded_below() == (dist[target][source] != inf));
                    if (bounds.bounded_above()) {
                        assert(*bounds.upper_bound == dist[source][target]);
                    }
                    if (bounds.bounded_below()) {
                        assert(*bounds.lower_bound == -dist[target][source]);
                    }
                }
            }
        }
    }
}

int main() {
    test_basic_constraints();
    test_infeasible();
    test_unbounded();
    test_alias_and_empty();
    test_against_warshall_floyd();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
