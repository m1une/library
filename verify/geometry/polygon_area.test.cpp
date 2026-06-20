#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"

#include "geometry/polygon.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    int n;
    std::cin >> n;
    std::vector<Point<long long>> polygon(n);
    for (auto& point : polygon) std::cin >> point.x >> point.y;
    std::cout << std::fixed << std::setprecision(1)
              << polygon_area(polygon) << '\n';
}
