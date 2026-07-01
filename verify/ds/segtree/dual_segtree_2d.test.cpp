#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "../../../ds/segtree/dual_segtree_2d.hpp"
#include "../../../monoid/add.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

using Add = m1une::monoid::Add<long long>;

struct Rectangle {
    int left;
    int lower;
    int right;
    int upper;
    long long value;
};

struct Operation {
    int type;
    Rectangle rectangle;
    int x;
    int y;
};

#ifndef NDEBUG
void randomized_test() {
    m1une::ds::DualSegtree2D<Add> empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    empty.apply(-10, 10, -10, 10, 5);
    assert(empty.get(0, 0) == 0);
    assert(empty.to_vector().empty());

    std::mt19937 random(271828182);
    std::vector<std::pair<int, int>> points;
    std::map<std::pair<int, int>, long long> expected;
    for (int i = 0; i < 50; i++) {
        int x = int(random() % 17) - 8;
        int y = int(random() % 17) - 8;
        points.emplace_back(x, y);
        expected[{x, y}] = 0;
    }

    m1une::ds::DualSegtree2D<Add> seg(points);
    assert(seg.size() == int(expected.size()));
    assert(!seg.contains_point(100, 100));
    assert(seg.get(100, 100) == 0);

    std::vector<std::pair<int, int>> distinct_points;
    for (const auto& [point, value] : expected) {
        (void)value;
        distinct_points.push_back(point);
    }

    for (int operation = 0; operation < 1200; operation++) {
        if (random() % 4 == 0) {
            auto point = distinct_points[random() % distinct_points.size()];
            long long value = int(random() % 101) - 50;
            seg.apply(point.first, point.second, value);
            expected[point] += value;
        } else {
            int x_lower = int(random() % 21) - 10;
            int x_upper = int(random() % 21) - 10;
            int y_lower = int(random() % 21) - 10;
            int y_upper = int(random() % 21) - 10;
            if (x_upper < x_lower) std::swap(x_lower, x_upper);
            if (y_upper < y_lower) std::swap(y_lower, y_upper);
            long long value = int(random() % 101) - 50;

            seg.apply(x_lower, x_upper, y_lower, y_upper, value);
            for (auto& [point, current] : expected) {
                if (x_lower <= point.first && point.first < x_upper &&
                    y_lower <= point.second && point.second < y_upper) {
                    current += value;
                }
            }
        }

        auto point = distinct_points[random() % distinct_points.size()];
        assert(seg.get(point.first, point.second) == expected[point]);
        assert(seg(point.first, point.second) == expected[point]);
    }

    auto values = seg.to_vector();
    assert(values.size() == expected.size());
    for (const auto& [x, y, value] : values) {
        std::pair<int, int> point(x, y);
        assert(expected[point] == value);
    }

    std::vector<std::tuple<int, int, long long>> weighted;
    weighted.emplace_back(1, 2, 3);
    weighted.emplace_back(1, 2, 4);
    weighted.emplace_back(3, 4, 5);
    m1une::ds::DualSegtree2D<Add> initialized(weighted);
    assert(initialized.get(1, 2) == 7);
    assert(initialized.get(3, 4) == 5);
}
#endif

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifndef NDEBUG
    randomized_test();
#endif

    int n, q;
    std::cin >> n >> q;
    std::vector<Rectangle> initial(n);
    for (Rectangle& rectangle : initial) {
        std::cin >> rectangle.left >> rectangle.lower >> rectangle.right >> rectangle.upper
                 >> rectangle.value;
    }

    std::vector<Operation> operations(q);
    std::vector<std::pair<int, int>> points;
    points.reserve(q);
    for (Operation& operation : operations) {
        std::cin >> operation.type;
        if (operation.type == 0) {
            Rectangle& rectangle = operation.rectangle;
            std::cin >> rectangle.left >> rectangle.lower >> rectangle.right >> rectangle.upper
                     >> rectangle.value;
            operation.x = operation.y = 0;
        } else {
            std::cin >> operation.x >> operation.y;
            operation.rectangle = Rectangle{0, 0, 0, 0, 0};
            points.emplace_back(operation.x, operation.y);
        }
    }

    m1une::ds::DualSegtree2D<Add> seg(std::move(points));
    for (const Rectangle& rectangle : initial) {
        seg.apply(rectangle.left, rectangle.right, rectangle.lower, rectangle.upper,
                  rectangle.value);
    }

    for (const Operation& operation : operations) {
        if (operation.type == 0) {
            const Rectangle& rectangle = operation.rectangle;
            seg.apply(rectangle.left, rectangle.right, rectangle.lower, rectangle.upper,
                      rectangle.value);
        } else {
            std::cout << seg.get(operation.x, operation.y) << '\n';
        }
    }
}
