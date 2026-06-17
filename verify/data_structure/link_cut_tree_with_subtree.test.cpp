#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "data_structure/link_cut_tree_with_subtree.hpp"
#include "monoid/add.hpp"

struct StringConcat {
    using value_type = std::string;

    static std::string id() {
        return "";
    }

    static std::string op(const std::string& a, const std::string& b) {
        return a + b;
    }
};

void test_vertex_subtree_sum() {
    m1une::data_structure::LinkCutTreeWithSubtree<m1une::monoid::Add<long long>> lct(std::vector<int>{1, 2, 3, 4, 5});

    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    assert(lct.path_prod(2, 4) == 14);
    assert(lct.subtree_prod(0, 1) == 14);
    assert(lct.subtree_size(0, 1) == 4);

    lct.set(3, 40);
    assert(lct.path_prod(2, 4) == 50);
    assert(lct.subtree_prod(0, 1) == 50);

    assert(lct.cut(1, 3));
    assert(lct.subtree_prod(0, 1) == 5);
    assert(!lct.connected(2, 4));
    assert(lct.link(2, 4));
    assert(lct.subtree_prod(0, 1) == 50);
}

void test_non_commutative_subtree_order() {
    m1une::data_structure::LinkCutTreeWithSubtree<StringConcat> lct(std::vector<std::string>{"a", "b", "c", "d", "e"});

    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));

    assert(lct.subtree_prod(0, 1) == "bcde");
    assert((lct.subtree_vertices(0, 1) == std::vector<int>{1, 2, 3, 4}));
    assert(lct.path_prod(2, 4) == "cbde");
    assert(lct.subtree_prod(1) == "bade");
    assert(lct.subtree_prod(0, 1) == "bcde");

    lct.set(3, "D");
    assert(lct.subtree_prod(0, 1) == "bcDe");
}

void test_edge_nodes_subtree() {
    m1une::data_structure::LinkCutTreeWithSubtree<m1une::monoid::Add<long long>> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);

    assert(lct.path_prod(0, 2) == 12);
    assert(lct.subtree_prod(0, 0) == 12);
    assert(lct.subtree_prod(0, 1) == 7);
    assert(lct.subtree_size(0, 1) == 3);

    lct.set_edge(e12, 20);
    assert(lct.path_prod(0, 2) == 25);
    assert(lct.subtree_prod(0, 1) == 20);

    assert(lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
}

int main() {
    test_vertex_subtree_sum();
    test_non_commutative_subtree_order();
    test_edge_nodes_subtree();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
