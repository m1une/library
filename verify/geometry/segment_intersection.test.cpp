#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"

#include "geometry/line.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    int q;
    std::cin >> q;
    while (q--) {
        Segment<long long> first;
        Segment<long long> second;
        std::cin >> first.a.x >> first.a.y >> first.b.x >> first.b.y;
        std::cin >> second.a.x >> second.a.y >> second.b.x >> second.b.y;
        std::cout << intersects(first, second) << '\n';
    }
}
