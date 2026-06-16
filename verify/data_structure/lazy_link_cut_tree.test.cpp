#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree.hpp"

using AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Node = AddSum::value_type;

void test_vertex_path_updates() {
    m1une::data_structure::LazyLinkCutTree<AddSum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    assert(lct.size() == 5);
    assert(!lct.empty());
    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    Node path = lct.prod(2, 4);
    assert(path.sum == 14);
    assert(path.size == 4);
    assert(lct.path_size(2, 4) == 4);
    assert(lct.kth_vertex(2, 4, 2) == 3);

    lct.apply(2, 4, 10);
    path = lct.prod(2, 4);
    assert(path.sum == 54);
    assert(path.size == 4);
    assert(lct.get(1).sum == 12);
    assert(lct.get(0).sum == 1);

    lct.apply(0, 3);
    assert(lct[0].sum == 4);
    lct.set(3, 100);
    path = lct.path_prod(2, 4);
    assert(path.sum == 140);

    assert(lct.cut(1, 3));
    assert(!lct.connected(2, 4));
}

void test_edge_path_updates() {
    m1une::data_structure::LazyLinkCutTree<AddSum> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);
    assert(lct.edge_count() == 2);
    assert(lct.edge_alive(e01));
    assert(lct.edge_node(e01) >= 3);
    assert((lct.edge_endpoints(e12) == std::pair<int, int>(1, 2)));
    assert(lct.link_edge(0, 2, 100) == -1);

    Node path = lct.prod(0, 2);
    assert(path.sum == 12);
    assert(path.size == 2);
    assert(lct.path_size(0, 2) == 5);

    lct.apply(0, 2, 3);
    assert(lct.get_edge(e01).sum == 8);
    assert(lct.get_edge(e12).sum == 10);
    path = lct.prod(0, 2);
    assert(path.sum == 18);
    assert(path.size == 2);

    lct.set_edge(e12, 100);
    assert(lct.prod(0, 2).sum == 108);
    lct.apply_edge(e01, 2);
    assert(lct.get_edge(e01).sum == 10);
    assert(lct.prod(0, 2).sum == 110);

    assert(lct.cut_edge(e01));
    assert(!lct.edge_alive(e01));
    assert(!lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
}

int main() {
    test_vertex_path_updates();
    test_edge_path_updates();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
