#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

#include <iomanip>
#include <iostream>

int main() {
    using namespace m1une::geometry;
    Circle<long double> circle;
    std::cin >> circle.center.x >> circle.center.y >> circle.radius;

    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(15);
    while (q--) {
        Line<long double> line;
        std::cin >> line.a.x >> line.a.y >> line.b.x >> line.b.y;
        auto points = circle_line_intersections(circle, line);
        if (points.size() == 1) points.push_back(points[0]);
        std::cout << points[0].x << " " << points[0].y << " "
                  << points[1].x << " " << points[1].y << '\n';
    }
}
