#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "ds/dynamic_tree/path_link_cut_tree.hpp"
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

void test_vertex_sum() {
    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long long>> lct(std::vector<int>{1, 2, 3, 4, 5});

    assert(lct.size() == 5);
    assert(!lct.empty());
    assert(lct[2] == 3);
    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));
    assert(lct.link(3, 4));
    assert(!lct.link(0, 4));

    assert(lct.connected(0, 4));
    assert(lct.same(2, 4));
    assert(lct.prod(0, 2) == 6);
    assert(lct.path_prod(2, 4) == 14);
    assert(lct.path_size(2, 4) == 4);
    assert(lct.kth_vertex(2, 4, 0) == 2);
    assert(lct.kth_vertex(2, 4, 1) == 1);
    assert(lct.kth_vertex(2, 4, 2) == 3);
    assert(lct.kth_vertex(2, 4, 3) == 4);

    lct.set(1, 10);
    assert(lct.get(1) == 10);
    assert(lct.prod(2, 4) == 22);

    assert(!lct.cut(0, 2));
    assert(lct.cut(1, 3));
    assert(!lct.connected(2, 4));
    assert(lct.link(2, 4));
    assert(lct.prod(0, 3) == 23);

    lct.evert(0);
    assert(lct.component_root(3) == 0);
    assert(lct.lca(2, 3) == 2);
}

void test_path_order() {
    m1une::ds::PathLinkCutTree<StringConcat> lct(std::vector<std::string>{"a", "b", "c", "d"});
    assert(lct.link(0, 1));
    assert(lct.link(1, 2));
    assert(lct.link(1, 3));

    assert(lct.prod(0, 2) == "abc");
    assert(lct.prod(2, 0) == "cba");
    assert(lct.prod(3, 2) == "dbc");
    lct.set(1, "B");
    assert(lct.prod(0, 3) == "aBd");
}

void test_edge_nodes() {
    m1une::ds::PathLinkCutTree<m1une::monoid::Add<long long>> lct(3);

    int e01 = lct.link_edge(0, 1, 5);
    int e12 = lct.link_edge(1, 2, 7);
    assert(e01 == 0);
    assert(e12 == 1);
    assert(lct.edge_count() == 2);
    assert(lct.edge_alive(e01));
    assert((lct.edge_endpoints(e01) == std::pair<int, int>(0, 1)));
    assert(lct.get_edge(e01) == 5);
    assert(lct.link_edge(0, 2, 100) == -1);
    assert(lct.prod(0, 2) == 12);

    lct.set_edge(e01, 10);
    assert(lct.prod(0, 2) == 17);
    lct.set_edge(e12, 20);
    assert(lct.get_edge(e12) == 20);
    assert(lct.prod(0, 2) == 30);
    assert(lct.cut_edge(e01));
    assert(!lct.edge_alive(e01));
    assert(!lct.cut_edge(e01));
    assert(!lct.connected(0, 2));
    int e02 = lct.link_edge(0, 2, 1);
    assert(e02 == 2);
    assert(lct.prod(0, 1) == 21);
}

int main() {
    test_vertex_sum();
    test_path_order();
    test_edge_nodes();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
