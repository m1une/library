#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../optimization/all.hpp"

using ProjectSelection = m1une::optimization::ProjectSelection<long long>;

void test_basic() {
    ProjectSelection solver(4);
    solver.add_gain(0, 8);
    solver.add_gain(1, 5);
    solver.add_gain(2, -4);
    solver.add_gain(3, 3, 1);
    solver.add_penalty(0, 1, 10);
    solver.add_penalty_if_different(1, 2, 2);
    solver.add_gain_if_same(0, 3, 4);
    solver.add_gain_if_all_selected(std::vector<int>{0, 1, 2}, 7);
    solver.add_gain_if_all_unselected(std::vector<int>{1, 2}, 6);

    auto result = solver.solve();
    assert(result.is_feasible());

    long long expected = std::numeric_limits<long long>::lowest();
    for (int mask = 0; mask < (1 << 4); mask++) {
        auto selected = [&](int project) {
            return ((mask >> project) & 1) != 0;
        };

        long long gain = 0;
        gain += selected(0) ? 8 : 0;
        gain += selected(1) ? 5 : 0;
        gain += selected(2) ? -4 : 0;
        gain += selected(3) ? 3 : 1;
        if (selected(0) && !selected(1)) gain -= 10;
        if (selected(1) != selected(2)) gain -= 2;
        if (selected(0) == selected(3)) gain += 4;
        if (selected(0) && selected(1) && selected(2)) gain += 7;
        if (!selected(1) && !selected(2)) gain += 6;
        if (gain > expected) {
            expected = gain;
        }
    }

    assert(result.max_gain == expected);
    long long returned_mask = 0;
    for (int project = 0; project < 4; project++) {
        if (result.selected[project]) returned_mask |= 1LL << project;
    }

    auto selected = [&](int project) {
        return ((returned_mask >> project) & 1) != 0;
    };
    long long returned_gain = 0;
    returned_gain += selected(0) ? 8 : 0;
    returned_gain += selected(1) ? 5 : 0;
    returned_gain += selected(2) ? -4 : 0;
    returned_gain += selected(3) ? 3 : 1;
    if (selected(0) && !selected(1)) returned_gain -= 10;
    if (selected(1) != selected(2)) returned_gain -= 2;
    if (selected(0) == selected(3)) returned_gain += 4;
    if (selected(0) && selected(1) && selected(2)) returned_gain += 7;
    if (!selected(1) && !selected(2)) returned_gain += 6;
    assert(returned_gain == expected);
}

void test_hard_constraints() {
    ProjectSelection solver(4);
    solver.add_gain(0, 10);
    solver.add_gain(1, -2);
    solver.add_gain(2, 7);
    solver.add_gain(3, 3);
    solver.add_hard_implication(0, 1);
    solver.add_hard_implication(1, 2);
    solver.force_selected(0);
    solver.force_unselected(3);

    auto result = solver.solve();
    assert(result.is_feasible());
    assert(result.max_gain == 15);
    assert(result.selected[0]);
    assert(result.selected[1]);
    assert(result.selected[2]);
    assert(!result.selected[3]);

    ProjectSelection impossible(1);
    impossible.force_selected(0);
    impossible.force_unselected(0);
    assert(!impossible.solve().is_feasible());
}

void test_empty_groups_and_repeated_solve() {
    ProjectSelection solver(0);
    solver.add_gain_if_all_selected({}, 3);
    solver.add_gain_if_all_unselected({}, 4);
    assert(solver.size() == 0);

    auto first = solver.solve();
    auto second = solver.solve();
    assert(first.is_feasible() && second.is_feasible());
    assert(first.max_gain == 7 && second.max_gain == 7);
    assert(first.selected.empty() && second.selected.empty());
}

void test_unary_against_bruteforce() {
    for (int n = 1; n <= 8; n++) {
        ProjectSelection solver(n);
        std::vector<long long> selected_gain(n);
        std::vector<long long> unselected_gain(n);
        for (int i = 0; i < n; i++) {
            selected_gain[i] = (i * 7 + n * 3) % 13 - 6;
            unselected_gain[i] = (i * 5 + n * 2) % 11 - 5;
            solver.add_gain(i, selected_gain[i], unselected_gain[i]);
        }

        auto result = solver.solve();
        long long expected = std::numeric_limits<long long>::lowest();
        for (int mask = 0; mask < (1 << n); mask++) {
            long long gain = 0;
            for (int i = 0; i < n; i++) {
                gain += ((mask >> i) & 1) ? selected_gain[i] : unselected_gain[i];
            }
            if (gain > expected) expected = gain;
        }
        assert(result.is_feasible());
        assert(result.max_gain == expected);
    }
}

void test_mixed_models_against_bruteforce() {
    for (int n = 1; n <= 7; n++) {
        for (int test = 0; test < 24; test++) {
            ProjectSelection solver(n);
            std::vector<long long> selected_gain(n);
            std::vector<long long> unselected_gain(n);
            for (int i = 0; i < n; i++) {
                selected_gain[i] = (test * 7 + i * 5 + n) % 15 - 7;
                unselected_gain[i] = (test * 3 + i * 11 + n * 2) % 13 - 6;
                solver.add_gain(i, selected_gain[i], unselected_gain[i]);
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if ((test + i * 3 + j * 5) % 7 != 0) continue;
                    long long penalty = (test + i + j) % 6;
                    solver.add_penalty(i, j, penalty);
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if ((test + i + j) % 5 == 0) {
                        solver.add_penalty_if_different(i, j, (test + i * 2 + j) % 5);
                    }
                    if ((test + i * 2 + j * 3) % 8 == 0) {
                        solver.add_gain_if_same(i, j, (test + i + j * 2) % 6);
                    }
                }
            }

            std::vector<int> all_selected;
            std::vector<int> all_unselected;
            for (int i = 0; i < n; i++) {
                if ((test + i) % 3 != 0) all_selected.push_back(i);
                if ((test + i * 2) % 4 != 0) all_unselected.push_back(i);
            }
            long long all_selected_gain = test % 7;
            long long all_unselected_gain = (test * 2 + n) % 8;
            solver.add_gain_if_all_selected(all_selected, all_selected_gain);
            solver.add_gain_if_all_unselected(all_unselected, all_unselected_gain);

            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                if ((test + i * 4) % 11 == 0) solver.add_hard_implication(i, j);
            }
            if (test % 9 == 0) solver.force_selected(test % n);
            if (test % 10 == 0) solver.force_unselected((test * 3 + 1) % n);

            bool found = false;
            long long expected = std::numeric_limits<long long>::lowest();
            for (int mask = 0; mask < (1 << n); mask++) {
                auto selected = [&](int project) {
                    return ((mask >> project) & 1) != 0;
                };

                bool feasible = true;
                for (int i = 0; i < n; i++) {
                    int j = (i + 1) % n;
                    if ((test + i * 4) % 11 == 0 && selected(i) && !selected(j)) {
                        feasible = false;
                    }
                }
                if (test % 9 == 0 && !selected(test % n)) feasible = false;
                if (test % 10 == 0 && selected((test * 3 + 1) % n)) feasible = false;
                if (!feasible) continue;

                long long gain = 0;
                for (int i = 0; i < n; i++) {
                    gain += selected(i) ? selected_gain[i] : unselected_gain[i];
                }
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if ((test + i * 3 + j * 5) % 7 == 0 && selected(i) && !selected(j)) {
                            gain -= (test + i + j) % 6;
                        }
                    }
                }
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if ((test + i + j) % 5 == 0 && selected(i) != selected(j)) {
                            gain -= (test + i * 2 + j) % 5;
                        }
                        if ((test + i * 2 + j * 3) % 8 == 0 && selected(i) == selected(j)) {
                            gain += (test + i + j * 2) % 6;
                        }
                    }
                }

                bool every_selected = true;
                for (int project : all_selected) every_selected &= selected(project);
                if (every_selected) gain += all_selected_gain;
                bool every_unselected = true;
                for (int project : all_unselected) every_unselected &= !selected(project);
                if (every_unselected) gain += all_unselected_gain;

                found = true;
                if (gain > expected) expected = gain;
            }

            auto result = solver.solve();
            assert(result.is_feasible() == found);
            if (found) assert(result.max_gain == expected);
        }
    }
}

int main() {
    test_basic();
    test_hard_constraints();
    test_empty_groups_and_repeated_solve();
    test_unary_against_bruteforce();
    test_mixed_models_against_bruteforce();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
