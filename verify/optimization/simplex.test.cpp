#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "optimization/all.hpp"

constexpr long double EPS = 1e-8L;

long double abs_ld(long double x) {
    return x < 0 ? -x : x;
}

bool approx(long double a, long double b) {
    return abs_ld(a - b) <= EPS;
}

void check_feasible(const std::vector<std::vector<long double>>& a,
                    const std::vector<long double>& b, const std::vector<long double>& x) {
    assert(x.size() == (a.empty() ? x.size() : a[0].size()));
    for (long double value : x) assert(value >= -EPS);
    for (int i = 0; i < int(a.size()); i++) {
        long double lhs = 0;
        for (int j = 0; j < int(x.size()); j++) lhs += a[i][j] * x[j];
        assert(lhs <= b[i] + EPS);
    }
}

long double objective_value(const std::vector<long double>& c, const std::vector<long double>& x) {
    long double result = 0;
    for (int i = 0; i < int(c.size()); i++) result += c[i] * x[i];
    return result;
}

void test_basic_maximize() {
    std::vector<std::vector<long double>> a = {
        {1, 1},
        {1, 0},
        {0, 1},
    };
    std::vector<long double> b = {4, 2, 3};
    std::vector<long double> c = {3, 2};

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    assert(result.is_optimal());
    check_feasible(a, b, result.variables);
    assert(approx(result.objective_value, 10));
    assert(approx(objective_value(c, result.variables), result.objective_value));
    assert(approx(result.variables[0], 2));
    assert(approx(result.variables[1], 2));

    auto alias_result = m1une::optimization::simplex(a, b, c);
    assert(alias_result.is_optimal());
    assert(approx(alias_result.objective_value, 10));
}

void test_minimize() {
    std::vector<std::vector<long double>> a = {
        {-1, -1},
        {1, 0},
        {0, 1},
    };
    std::vector<long double> b = {-4, 10, 10};
    std::vector<long double> c = {1, 1};

    auto result = m1une::optimization::simplex_minimize(a, b, c);
    assert(result.is_optimal());
    check_feasible(a, b, result.variables);
    assert(approx(result.objective_value, 4));
    assert(approx(objective_value(c, result.variables), result.objective_value));
}

void test_negative_rhs() {
    std::vector<std::vector<long double>> a = {
        {-1},
        {1},
    };
    std::vector<long double> b = {-1, 3};
    std::vector<long double> c = {1};

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    assert(result.is_optimal());
    check_feasible(a, b, result.variables);
    assert(approx(result.objective_value, 3));
    assert(approx(result.variables[0], 3));
}

void test_infeasible() {
    std::vector<std::vector<long double>> a = {
        {1},
        {-1},
    };
    std::vector<long double> b = {0, -1};
    std::vector<long double> c = {1};

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    assert(result.is_infeasible());
}

void test_unbounded() {
    std::vector<std::vector<long double>> a;
    std::vector<long double> b;
    std::vector<long double> c = {1, 2};

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    assert(result.is_unbounded());
}

void test_no_variables() {
    std::vector<std::vector<long double>> a(2);
    std::vector<long double> b = {1, 2};
    std::vector<long double> c;

    auto result = m1une::optimization::simplex_maximize(a, b, c);
    assert(result.is_optimal());
    assert(result.variables.empty());
    assert(approx(result.objective_value, 0));

    std::vector<std::vector<long double>> bad_a(1);
    std::vector<long double> bad_b = {-1};
    auto bad_result = m1une::optimization::simplex_maximize(bad_a, bad_b, c);
    assert(bad_result.is_infeasible());
}

struct Line {
    long double x;
    long double y;
    long double rhs;
};

long double brute_max_2d(const std::vector<std::vector<long double>>& a,
                         const std::vector<long double>& b,
                         const std::vector<long double>& c) {
    std::vector<Line> lines;
    for (int i = 0; i < int(a.size()); i++) {
        Line line;
        line.x = a[i][0];
        line.y = a[i][1];
        line.rhs = b[i];
        lines.push_back(line);
    }

    Line x_axis;
    x_axis.x = 1;
    x_axis.y = 0;
    x_axis.rhs = 0;
    lines.push_back(x_axis);

    Line y_axis;
    y_axis.x = 0;
    y_axis.y = 1;
    y_axis.rhs = 0;
    lines.push_back(y_axis);

    bool found = false;
    long double best = -std::numeric_limits<long double>::infinity();
    for (int i = 0; i < int(lines.size()); i++) {
        for (int j = i + 1; j < int(lines.size()); j++) {
            const Line& p = lines[i];
            const Line& q = lines[j];
            long double det = p.x * q.y - q.x * p.y;
            if (abs_ld(det) <= EPS) continue;

            long double vx = (p.rhs * q.y - q.rhs * p.y) / det;
            long double vy = (p.x * q.rhs - q.x * p.rhs) / det;
            if (vx < -EPS || vy < -EPS) continue;

            bool feasible = true;
            for (int k = 0; k < int(a.size()); k++) {
                long double lhs = a[k][0] * vx + a[k][1] * vy;
                if (lhs > b[k] + EPS) feasible = false;
            }
            if (!feasible) continue;

            long double value = c[0] * vx + c[1] * vy;
            if (!found || value > best) {
                found = true;
                best = value;
            }
        }
    }
    assert(found);
    return best;
}

void test_against_vertices() {
    for (int t = 0; t < 30; t++) {
        std::vector<std::vector<long double>> a;
        std::vector<long double> b;

        int upper_x = 3 + t % 5;
        int upper_y = 4 + t * 2 % 5;
        a.emplace_back(std::vector<long double>{1, 0});
        b.push_back(upper_x);
        a.emplace_back(std::vector<long double>{0, 1});
        b.push_back(upper_y);

        for (int k = 0; k < 4; k++) {
            long double p = (t + k * 3) % 7 - 3;
            long double q = (t * 2 + k * 5) % 7 - 3;
            if (abs_ld(p) + abs_ld(q) == 0) q = 1;
            long double rhs = 2 + (t * 3 + k * 4) % 9;
            a.emplace_back(std::vector<long double>{p, q});
            b.push_back(rhs);
        }

        long double first_objective = (t * 5) % 11 - 5;
        long double second_objective = (t * 7 + 3) % 11 - 5;
        std::vector<long double> c = {first_objective, second_objective};
        if (abs_ld(c[0]) + abs_ld(c[1]) == 0) c[0] = 1;

        auto result = m1une::optimization::simplex_maximize(a, b, c);
        assert(result.is_optimal());
        check_feasible(a, b, result.variables);
        long double expected = brute_max_2d(a, b, c);
        assert(approx(result.objective_value, expected));
        assert(approx(objective_value(c, result.variables), result.objective_value));
    }
}

int main() {
    test_basic_maximize();
    test_minimize();
    test_negative_rhs();
    test_infeasible();
    test_unbounded();
    test_no_variables();
    test_against_vertices();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
