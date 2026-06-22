#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"

#include "../../geometry/manhattan_mst.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "../../ds/dsu/dsu.hpp"

namespace {

using Point = m1une::geometry::Point<long long>;
using Wide = __int128_t;

Wide distance(const Point& a, const Point& b) {
    Wide dx = Wide(a.x) - Wide(b.x);
    Wide dy = Wide(a.y) - Wide(b.y);
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx + dy;
}

Wide brute_force_cost(const std::vector<Point>& points) {
    struct Edge {
        int from;
        int to;
        Wide cost;
    };

    std::vector<Edge> edges;
    for (int i = 0; i < int(points.size()); i++) {
        for (int j = 0; j < i; j++) {
            edges.push_back(Edge{i, j, distance(points[i], points[j])});
        }
    }
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    m1une::ds::Dsu dsu(int(points.size()));
    Wide result = 0;
    for (const auto& edge : edges) {
        if (dsu.same(edge.from, edge.to)) continue;
        dsu.merge(edge.from, edge.to);
        result += edge.cost;
    }
    return result;
}

void check(const std::vector<Point>& points) {
    auto candidates = m1une::geometry::manhattan_mst_edges(points);
    assert(candidates.size() <= 4 * points.size());
    for (const auto& edge : candidates) {
        assert(0 <= edge.from && edge.from < int(points.size()));
        assert(0 <= edge.to && edge.to < int(points.size()));
        assert(edge.cost == distance(points[edge.from], points[edge.to]));
    }

    auto mst = m1une::geometry::manhattan_mst(points);
    assert(mst.cost == brute_force_cost(points));
    assert(mst.edges.size() == (points.empty() ? 0 : points.size() - 1));

    m1une::ds::Dsu dsu(int(points.size()));
    Wide selected_cost = 0;
    for (const auto& edge : mst.edges) {
        assert(!dsu.same(edge.from, edge.to));
        dsu.merge(edge.from, edge.to);
        selected_cost += edge.cost;
    }
    assert(selected_cost == mst.cost);
}

void test_fixed() {
    check({});
    check({Point(4, -7)});
    check({Point(0, 0), Point(0, 0), Point(3, -2), Point(-5, 4)});
    check({
        Point(std::numeric_limits<long long>::min(), 0),
        Point(std::numeric_limits<long long>::max(), 0),
    });
}

void test_randomized() {
    std::uint64_t state = 91;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; trial++) {
        int n = int(random() % 15);
        std::vector<Point> points;
        points.reserve(n);
        for (int i = 0; i < n; i++) {
            points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        check(points);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    int n;
    std::cin >> n;
    std::vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; i++) {
        long long x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }

    auto mst = m1une::geometry::manhattan_mst(points);
    std::cout << static_cast<long long>(mst.cost) << '\n';
    for (const auto& edge : mst.edges) {
        std::cout << edge.from << ' ' << edge.to << '\n';
    }
}
