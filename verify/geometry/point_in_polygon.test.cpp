#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"

#include "geometry/polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    int n;
    std::cin >> n;
    std::vector<Point<long long>> polygon(n);
    for (auto& point : polygon) std::cin >> point.x >> point.y;

    int q;
    std::cin >> q;
    while (q--) {
        Point<long long> point;
        std::cin >> point.x >> point.y;
        std::cout << int(point_in_polygon(polygon, point)) << '\n';
    }
}
