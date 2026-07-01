#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../../../ds/segtree/segtree_2d.hpp"
#include "../../../monoid/add.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

using Sum = m1une::monoid::Add<long long>;

struct Query {
    int type;
    int first;
    int second;
    int third;
    int fourth;
    long long value;
};

#ifndef NDEBUG
void randomized_test() {
    std::mt19937 random(314159265);
    std::vector<std::pair<int, int>> points;
    std::map<std::pair<int, int>, long long> expected;
    for (int i = 0; i < 40; i++) {
        int x = int(random() % 15) - 7;
        int y = int(random() % 15) - 7;
        points.emplace_back(x, y);
        expected[{x, y}] = 0;
    }

    m1une::ds::Segtree2D<Sum> seg(points);
    assert(seg.size() == int(expected.size()));
    assert(!seg.contains_point(100, 100));
    assert(seg.get(100, 100) == 0);

    std::vector<std::pair<int, int>> distinct_points;
    for (const auto& [point, value] : expected) {
        (void)value;
        distinct_points.push_back(point);
    }

    for (int operation = 0; operation < 1000; operation++) {
        if (random() % 3 == 0) {
            auto point = distinct_points[random() % distinct_points.size()];
            long long value = int(random() % 101) - 50;
            seg.set(point.first, point.second, value);
            expected[point] = value;
            assert(seg(point.first, point.second) == value);
        } else {
            int x_lower = int(random() % 19) - 9;
            int x_upper = int(random() % 19) - 9;
            int y_lower = int(random() % 19) - 9;
            int y_upper = int(random() % 19) - 9;
            if (x_upper < x_lower) std::swap(x_lower, x_upper);
            if (y_upper < y_lower) std::swap(y_lower, y_upper);

            long long answer = 0;
            for (const auto& [point, value] : expected) {
                if (x_lower <= point.first && point.first < x_upper &&
                    y_lower <= point.second && point.second < y_upper) {
                    answer += value;
                }
            }
            assert(seg.prod(x_lower, x_upper, y_lower, y_upper) == answer);
        }
    }

    long long total = 0;
    for (const auto& [point, value] : expected) {
        (void)point;
        total += value;
    }
    assert(seg.all_prod() == total);
    auto values = seg.to_vector();
    assert(values.size() == expected.size());
    for (const auto& [x, y, value] : values) {
        std::pair<int, int> point(x, y);
        assert(expected[point] == value);
    }
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
    std::vector<std::tuple<int, int, long long>> initial(n);
    std::vector<std::pair<int, int>> points;
    points.reserve(n + q);
    for (auto& [x, y, weight] : initial) {
        std::cin >> x >> y >> weight;
        points.emplace_back(x, y);
    }

    std::vector<Query> queries(q);
    for (Query& query : queries) {
        std::cin >> query.type;
        if (query.type == 0) {
            std::cin >> query.first >> query.second >> query.value;
            query.third = query.fourth = 0;
            points.emplace_back(query.first, query.second);
        } else {
            std::cin >> query.first >> query.second >> query.third >> query.fourth;
            query.value = 0;
        }
    }

    m1une::ds::Segtree2D<Sum> seg(std::move(points));
    for (const auto& [x, y, weight] : initial) {
        seg.set(x, y, seg.get(x, y) + weight);
    }

    for (const Query& query : queries) {
        if (query.type == 0) {
            long long current = seg.get(query.first, query.second);
            seg.set(query.first, query.second, current + query.value);
        } else {
            std::cout << seg.prod(query.first, query.third, query.second, query.fourth)
                      << '\n';
        }
    }
}
