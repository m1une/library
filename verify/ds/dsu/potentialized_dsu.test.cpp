#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/dsu/potentialized_dsu.hpp"
#include "monoid/add.hpp"
#include "monoid/xor.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;

    m1une::ds::PotentializedDsu<Add> add_dsu(5);
    assert(add_dsu.size() == 5);
    assert(!add_dsu.empty());

    assert(add_dsu.merge(0, 1, 3));
    assert(add_dsu.merge(1, 2, 4));
    assert(add_dsu.same(0, 2));
    assert(add_dsu.diff(0, 1) == 3);
    assert(add_dsu.diff(1, 2) == 4);
    assert(add_dsu.diff(0, 2) == 7);
    assert(add_dsu.diff(2, 0) == -7);
    assert(add_dsu.merge(0, 2, 7));
    assert(!add_dsu.merge(0, 2, 8));

    assert(add_dsu.merge(4, 0, -1));
    assert(add_dsu.diff(4, 0) == -1);
    assert(add_dsu.diff(0, 4) == 1);
    assert(add_dsu.size(1) == 4);

    const auto& const_add_dsu = add_dsu;
    assert(const_add_dsu.same(4, 2));
    assert(const_add_dsu.diff(4, 2) == 6);

    std::vector<std::vector<int>> groups = add_dsu.groups();
    assert(groups.size() == 2);

    using Xor = m1une::monoid::Xor<int>;

    m1une::ds::PotentializedDsu<Xor> xor_dsu(4);
    assert(xor_dsu.merge(0, 1, 5));
    assert(xor_dsu.merge(1, 2, 6));
    assert(xor_dsu.diff(0, 1) == 5);
    assert(xor_dsu.diff(1, 2) == 6);
    assert(xor_dsu.diff(0, 2) == (5 ^ 6));
    assert(xor_dsu.merge(0, 2, 5 ^ 6));
    assert(!xor_dsu.merge(0, 2, 2));
    assert(xor_dsu.merge(3, 0, 9));
    assert(xor_dsu.diff(3, 2) == (9 ^ 5 ^ 6));

    m1une::ds::PotentializedDsu<Add> empty;
    assert(empty.size() == 0);
    assert(empty.empty());

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
