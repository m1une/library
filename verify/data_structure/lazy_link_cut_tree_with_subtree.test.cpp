#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "acted_monoid/range_add_range_sum.hpp"
#include "data_structure/lazy_link_cut_tree_with_subtree.hpp"

using AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Node = AddSum::value_type;

void test_vertex_path_and_subtree_updates() {
    m1une::data_structure::LazyLinkCutTreeWithSubtree<AddSum> lct(std::vector<long long>{1, 2, 3, 4, 5});

    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    Node subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 14);
    assert(subtree.size == 4);
    assert(lct.subtree_size(0, 1) == 4);

    lct.apply(2, 4, 10);
    Node path = lct.path_prod(2, 4);
    assert(path.sum == 54);
    assert(path.size == 4);
    subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 54);
    assert(subtree.size == 4);
    assert(lct.get(0).sum == 1);

    lct.apply_subtree(0, 1, 5);
    subtree = lct.subtree_prod(0, 1);
    assert(subtree.sum == 74);
    assert(subtree.size == 4);
    assert(lct.path_prod(2, 4).sum == 74);

    subtree = lct.subtree_prod(2, 1);
    assert(subtree.sum == 57);
    assert(subtree.size == 4);
}

void test_edge_path_and_subtree_updates() {
    m1une::data_structure::LazyLinkCutTreeWithSubtree<AddSum> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);

    Node full = lct.subtree_prod(0, 0);
    assert(full.sum == 12);
    assert(full.size == 2);
    Node child = lct.subtree_prod(0, 1);
    assert(child.sum == 7);
    assert(child.size == 1);
    assert(lct.subtree_size(0, 1) == 3);

    lct.apply(0, 2, 3);
    assert(lct.path_prod(0, 2).sum == 18);
    assert(lct.subtree_prod(0, 1).sum == 10);

    lct.apply_subtree(0, 1, 2);
    assert(lct.get_edge(e01).sum == 8);
    assert(lct.get_edge(e12).sum == 12);
    assert(lct.subtree_prod(0, 0).sum == 20);

    assert(lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
}

int main() {
    test_vertex_path_and_subtree_updates();
    test_edge_path_and_subtree_updates();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
