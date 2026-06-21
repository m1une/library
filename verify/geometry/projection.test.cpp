#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"

#include "../../geometry/line.hpp"

#include <iomanip>
#include <iostream>

int main() {
    using namespace m1une::geometry;
    Line<long double> line;
    std::cin >> line.a.x >> line.a.y >> line.b.x >> line.b.y;

    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(10);
    while (q--) {
        Point<long double> point;
        std::cin >> point.x >> point.y;
        Point<long double> result = projection(line, point);
        std::cout << result.x << " " << result.y << '\n';
    }
}
