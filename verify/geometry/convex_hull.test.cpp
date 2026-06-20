#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"

#include "geometry/polygon.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    int n;
    std::cin >> n;
    std::vector<Point<long long>> points(n);
    for (auto& point : points) std::cin >> point.x >> point.y;

    std::vector<Point<long long>> hull = convex_hull(points, true);
    int start = int(std::min_element(
        hull.begin(),
        hull.end(),
        [](const auto& a, const auto& b) {
            if (a.y != b.y) return a.y < b.y;
            return a.x < b.x;
        }
    ) - hull.begin());

    std::cout << hull.size() << '\n';
    for (int offset = 0; offset < int(hull.size()); offset++) {
        const auto& point = hull[(start + offset) % hull.size()];
        std::cout << point.x << " " << point.y << '\n';
    }
}
