#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../optimization/all.hpp"

using SlopeTrick = m1une::optimization::SlopeTrick<long long>;

constexpr int coordinate_limit = 300;
constexpr long long inf = std::numeric_limits<long long>::max() / 4;

int index_of(int x) {
    return x + coordinate_limit;
}

void check_values(const SlopeTrick& slope, const std::vector<long long>& value) {
    long long expected_minimum = *std::min_element(value.begin(), value.end());
    assert(slope.minimum() == expected_minimum);
    for (int x = -100; x <= 100; x++) {
        assert(slope.evaluate(x) == value[index_of(x)]);
    }

    auto range = slope.argmin();
    int first = -coordinate_limit;
    while (first <= coordinate_limit && value[index_of(first)] != expected_minimum) first++;
    int last = coordinate_limit;
    while (last >= -coordinate_limit && value[index_of(last)] != expected_minimum) last--;
    if (range.left.has_value()) assert(*range.left == first);
    if (range.right.has_value()) assert(*range.right == last);
}

void test_basic() {
    SlopeTrick slope;
    assert(slope.minimum() == 0);
    assert(!slope.argmin().left.has_value());
    assert(!slope.argmin().right.has_value());

    slope.add_abs(3);
    slope.add_x_minus_a(-2);
    slope.add_a_minus_x(7);
    slope.add_constant(5);
    assert(slope.minimum() == 14);
    assert(slope.evaluate(3) == 14);
    auto range = slope.argmin();
    assert(range.left == std::optional<long long>(3));
    assert(range.right == std::optional<long long>(3));
    assert(slope.breakpoint_count() == 4);

    SlopeTrick right_hinge;
    right_hinge.add_x_minus_a(5);
    assert(!right_hinge.argmin().left.has_value());
    assert(right_hinge.argmin().right == std::optional<long long>(5));

    SlopeTrick left_hinge;
    left_hinge.add_a_minus_x(-4);
    assert(left_hinge.argmin().left == std::optional<long long>(-4));
    assert(!left_hinge.argmin().right.has_value());
}

void test_operations_against_explicit_function() {
    for (int test = 0; test < 80; test++) {
        SlopeTrick slope;
        std::vector<long long> value(coordinate_limit * 2 + 1, 0);

        for (int operation = 0; operation < 80; operation++) {
            int type = (test * 11 + operation * 7) % 8;
            int a = (test * 17 + operation * 13) % 61 - 30;

            if (type == 0) {
                long long constant = (test + operation * 3) % 17 - 8;
                slope.add_constant(constant);
                for (auto& current : value) current += constant;
            } else if (type == 1) {
                slope.add_x_minus_a(a);
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    value[index_of(x)] += std::max(0, x - a);
                }
            } else if (type == 2) {
                slope.add_a_minus_x(a);
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    value[index_of(x)] += std::max(0, a - x);
                }
            } else if (type == 3) {
                slope.add_abs(a);
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    value[index_of(x)] += std::abs(x - a);
                }
            } else if (type == 4) {
                int delta = (test + operation) % 7 - 3;
                slope.shift(delta);
                std::vector<long long> next(value.size(), inf);
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    int source = x - delta;
                    if (-coordinate_limit <= source && source <= coordinate_limit) {
                        next[index_of(x)] = value[index_of(source)];
                    }
                }
                value.swap(next);
            } else if (type == 5) {
                int left = (test + operation * 2) % 4 - 3;
                int right = left + 1 + (test * 3 + operation) % 4;
                slope.shift(left, right);
                std::vector<long long> next(value.size(), inf);
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    for (int y = x - right; y <= x - left; y++) {
                        if (-coordinate_limit <= y && y <= coordinate_limit) {
                            next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);
                        }
                    }
                }
                value.swap(next);
            } else if (type == 6) {
                slope.prefix_minimum();
                long long best = inf;
                for (int x = -coordinate_limit; x <= coordinate_limit; x++) {
                    best = std::min(best, value[index_of(x)]);
                    value[index_of(x)] = best;
                }
            } else {
                slope.suffix_minimum();
                long long best = inf;
                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {
                    best = std::min(best, value[index_of(x)]);
                    value[index_of(x)] = best;
                }
            }
            check_values(slope, value);
        }
    }
}

void test_merge() {
    for (int test = 0; test < 100; test++) {
        SlopeTrick first;
        SlopeTrick second;
        for (int i = 0; i < 20; i++) {
            int a = (test * 7 + i * 11) % 41 - 20;
            int b = (test * 13 + i * 5) % 41 - 20;
            if (i % 3 == 0) {
                first.add_abs(a);
                second.add_abs(b);
            } else if (i % 3 == 1) {
                first.add_x_minus_a(a);
                second.add_a_minus_x(b);
            } else {
                first.add_a_minus_x(a);
                second.add_x_minus_a(b);
            }
        }
        first.add_constant(test - 50);
        second.add_constant(30 - test);
        first.shift(-2, 1);
        second.shift(3);
        if (test % 2 == 0) first.clear_right();
        if (test % 3 == 0) second.clear_left();

        std::vector<long long> expected(201);
        for (int x = -100; x <= 100; x++) {
            expected[x + 100] = first.evaluate(x) + second.evaluate(x);
        }
        first.merge(second);
        for (int x = -100; x <= 100; x++) {
            assert(first.evaluate(x) == expected[x + 100]);
        }
    }
}

int main() {
    test_basic();
    test_operations_against_explicit_function();
    test_merge();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
