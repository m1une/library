#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "optimization/all.hpp"

long long evaluate(const std::vector<long long>& c, const std::vector<long long>& x) {
    long long result = 0;
    for (int i = 0; i < int(c.size()); i++) result += c[i] * x[i];
    return result;
}

bool feasible(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
              const std::vector<long long>& x) {
    for (long long value : x) {
        if (value < 0) return false;
    }
    for (int i = 0; i < int(a.size()); i++) {
        long long lhs = 0;
        for (int j = 0; j < int(x.size()); j++) lhs += a[i][j] * x[j];
        if (lhs > b[i]) return false;
    }
    return true;
}

void brute_dfs(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
               const std::vector<long long>& c, const std::vector<long long>& limits, int index,
               std::vector<long long>& current, bool maximize, bool& found, long long& best) {
    if (index == int(c.size())) {
        if (!feasible(a, b, current)) return;
        long long value = evaluate(c, current);
        if (!found || (maximize ? value > best : value < best)) {
            found = true;
            best = value;
        }
        return;
    }
    for (long long value = 0; value <= limits[index]; value++) {
        current[index] = value;
        brute_dfs(a, b, c, limits, index + 1, current, maximize, found, best);
    }
}

long long brute_solve(const std::vector<std::vector<long long>>& a,
                      const std::vector<long long>& b, const std::vector<long long>& c,
                      const std::vector<long long>& limits, bool maximize) {
    bool found = false;
    long long best = 0;
    std::vector<long long> current(c.size(), 0);
    brute_dfs(a, b, c, limits, 0, current, maximize, found, best);
    assert(found);
    return best;
}

void check_optimal(const std::vector<std::vector<long long>>& a,
                   const std::vector<long long>& b, const std::vector<long long>& c,
                   const m1une::optimization::IntegerLpResult<long long>& result,
                   long long expected) {
    assert(result.is_optimal());
    assert(feasible(a, b, result.variables));
    assert(result.objective_value == expected);
    assert(evaluate(c, result.variables) == expected);
}

void test_basic_maximize() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{2, 1});
    a.emplace_back(std::vector<long long>{1, 2});
    std::vector<long long> b = {4, 4};
    std::vector<long long> c = {3, 2};

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    check_optimal(a, b, c, result, 6);

    auto alias_result = m1une::optimization::integer_lp(a, b, c);
    check_optimal(a, b, c, alias_result, 6);
}

void test_minimize() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{-1, -1});
    a.emplace_back(std::vector<long long>{1, 0});
    a.emplace_back(std::vector<long long>{0, 1});
    std::vector<long long> b = {-3, 5, 5};
    std::vector<long long> c = {1, 1};

    auto result = m1une::optimization::integer_lp_minimize(a, b, c);
    check_optimal(a, b, c, result, 3);
}

void test_integer_infeasible_fractional_relaxation() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{2});
    a.emplace_back(std::vector<long long>{-2});
    std::vector<long long> b = {1, -1};
    std::vector<long long> c = {1};

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    assert(result.is_infeasible());
}

void test_unbounded() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{-1});
    std::vector<long long> b = {-1};
    std::vector<long long> c = {1};

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    assert(result.is_unbounded());
    assert(feasible(a, b, result.variables));
}

void test_unbounded_relaxation_but_integer_infeasible() {
    std::vector<std::vector<long long>> a;
    a.emplace_back(std::vector<long long>{2, 0});
    a.emplace_back(std::vector<long long>{-2, 0});
    std::vector<long long> b = {1, -1};
    std::vector<long long> c = {0, 1};

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    assert(result.is_infeasible());
}

void test_no_variables() {
    std::vector<std::vector<long long>> a(2);
    std::vector<long long> b = {0, 3};
    std::vector<long long> c;

    auto result = m1une::optimization::integer_lp_maximize(a, b, c);
    assert(result.is_optimal());
    assert(result.variables.empty());
    assert(result.objective_value == 0);

    std::vector<std::vector<long long>> bad_a(1);
    std::vector<long long> bad_b = {-1};
    auto bad_result = m1une::optimization::integer_lp_maximize(bad_a, bad_b, c);
    assert(bad_result.is_infeasible());
}

void test_against_bruteforce() {
    for (int t = 0; t < 20; t++) {
        std::vector<std::vector<long long>> a;
        std::vector<long long> b;
        std::vector<long long> limits;
        int variable_count = 3;

        for (int j = 0; j < variable_count; j++) {
            long long limit = 2 + (t + j * 2) % 4;
            limits.push_back(limit);
            std::vector<long long> row(variable_count, 0);
            row[j] = 1;
            a.push_back(row);
            b.push_back(limit);
        }

        for (int i = 0; i < 4; i++) {
            std::vector<long long> row(variable_count, 0);
            for (int j = 0; j < variable_count; j++) {
                row[j] = (t * 3 + i * 5 + j * 7) % 7 - 3;
            }
            long long rhs = 3 + (t * 2 + i * 4) % 9;
            a.push_back(row);
            b.push_back(rhs);
        }

        std::vector<long long> c(variable_count, 0);
        for (int j = 0; j < variable_count; j++) c[j] = (t * 5 + j * 3) % 11 - 5;

        long long expected_max = brute_solve(a, b, c, limits, true);
        auto max_result = m1une::optimization::integer_lp_maximize(a, b, c);
        check_optimal(a, b, c, max_result, expected_max);

        long long expected_min = brute_solve(a, b, c, limits, false);
        auto min_result = m1une::optimization::integer_lp_minimize(a, b, c);
        check_optimal(a, b, c, min_result, expected_min);
    }
}

int main() {
    test_basic_maximize();
    test_minimize();
    test_integer_infeasible_fractional_relaxation();
    test_unbounded();
    test_unbounded_relaxation_but_integer_infeasible();
    test_no_variables();
    test_against_bruteforce();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
