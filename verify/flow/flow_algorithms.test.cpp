#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

#include "../../flow/flow.hpp"

void test_max_flow() {
    m1une::flow::MaxFlow<long long> mf(4);
    int e0 = mf.add_edge(0, 1, 2);
    int e1 = mf.add_edge(0, 2, 1);
    int e2 = mf.add_edge(1, 2, 1);
    int e3 = mf.add_edge(1, 3, 1);
    int e4 = mf.add_edge(2, 3, 2);
    (void)e1;
    (void)e2;
    (void)e3;
    (void)e4;

    assert(mf.size() == 4);
    assert(mf.edge_count() == 5);
    assert(mf.max_flow(0, 3) == 3);
    auto edges = mf.edges();
    long long outgoing = 0;
    for (const auto& e : edges) {
        if (e.from == 0) outgoing += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(outgoing == 3);
    assert(mf.get_edge(e0).cap == 2);

    auto cut = mf.min_cut(0);
    assert(cut[0]);
    assert(!cut[3]);

    mf.change_edge(e0, 3, 1);
    auto changed = mf.get_edge(e0);
    assert(changed.cap == 3);
    assert(changed.flow == 1);
}

void test_bounded_flow() {
    m1une::flow::BoundedFlow<long long> st(4);
    int a = st.add_edge(0, 1, 1, 3);
    int b = st.add_edge(0, 2, 0, 2);
    int c = st.add_edge(1, 3, 1, 2);
    int d = st.add_edge(2, 3, 0, 2);
    int e = st.add_edge(1, 2, 0, 1);
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;

    auto exact = st.feasible_st_flow(0, 3, 3);
    assert(exact.has_value());
    std::vector<long long> balance(4, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, 0, -3}));

    auto too_much = st.feasible_st_flow(0, 3, 6);
    assert(!too_much.has_value());

    m1une::flow::BoundedFlow<long long> bf(3);
    int f01 = bf.add_edge(0, 1, 1, 3);
    int f02 = bf.add_edge(0, 2, 0, 4);
    bf.add_edge(1, 2, 0, 2);
    bf.add_supply(0, 4);
    bf.add_demand(1, 1);
    bf.add_demand(2, 3);
    assert(bf.balance(0) == 4);
    auto bflow = bf.feasible_flow();
    assert(bflow.has_value());
    assert(bflow->get_edge(f01).flow >= 1);
    assert(bflow->get_edge(f02).flow >= 0);
    std::vector<long long> b_balance(3, 0);
    for (const auto& edge : bflow->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        b_balance[edge.from] += edge.flow;
        b_balance[edge.to] -= edge.flow;
    }
    assert((b_balance == std::vector<long long>{4, -1, -3}));

    m1une::flow::BoundedFlow<long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.feasible_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);

    m1une::flow::BoundedFlow<long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.feasible_flow().has_value());

    m1une::flow::BFlow<long long> alias(1);
    assert(alias.size() == 1);
}

void test_bounded_min_cost_flow() {
    m1une::flow::BoundedMinCostFlow<long long, long long> st(3);
    int e01 = st.add_edge(0, 1, 1, 3, 2);
    int e12 = st.add_edge(1, 2, 1, 3, 1);
    int e02 = st.add_edge(0, 2, 0, 3, 10);

    auto exact = st.min_cost_st_flow(0, 2, 3);
    assert(exact.has_value());
    assert(exact->cost == 9);
    assert(exact->flow(e01) == 3);
    assert(exact->flow(e12) == 3);
    assert(exact->flow(e02) == 0);
    std::vector<long long> balance(3, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, -3}));

    m1une::flow::BoundedMinCostFlow<long long, long long> bf(3);
    int p01 = bf.add_edge(0, 1, 0, 2, 1);
    int p12 = bf.add_edge(1, 2, 0, 2, 1);
    int p02 = bf.add_edge(0, 2, 0, 2, 5);
    bf.add_supply(0, 2);
    bf.add_demand(2, 2);
    auto bflow = bf.min_cost_flow();
    assert(bflow.has_value());
    assert(bflow->cost == 4);
    assert(bflow->flow(p01) == 2);
    assert(bflow->flow(p12) == 2);
    assert(bflow->flow(p02) == 0);

    m1une::flow::BoundedMinCostFlow<long long, long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5, 2);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.min_cost_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);
    assert(negative_flow->cost == -6);

    m1une::flow::BoundedMinCostFlow<long long, long long> cycle(2);
    int c01 = cycle.add_edge(0, 1, 0, 1, -5);
    int c10 = cycle.add_edge(1, 0, 0, 1, 3);
    auto circulation = cycle.min_cost_flow();
    assert(circulation.has_value());
    assert(circulation->flow(c01) == 1);
    assert(circulation->flow(c10) == 1);
    assert(circulation->cost == -2);

    m1une::flow::BoundedMinCostFlow<long long, long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1, 0);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.min_cost_flow().has_value());

    m1une::flow::BMinCostFlow<long long, long long> alias(1);
    assert(alias.size() == 1);
}

void test_min_cost_flow() {
    m1une::flow::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto result = mcf.flow(0, 3, 2);
    assert(result.first == 2);
    assert(result.second == 5);
    auto edges = mcf.edges();
    long long total_source_flow = 0;
    for (const auto& e : edges) {
        if (e.from == 0) total_source_flow += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(total_source_flow == 2);

    m1une::flow::MinCostFlow<long long, long long> negative(3);
    negative.add_edge(0, 1, 1, -5);
    negative.add_edge(1, 2, 1, 2);
    negative.add_edge(0, 2, 1, 10);
    auto slope = negative.slope(0, 2, 2);
    std::vector<std::pair<long long, long long>> expected_slope = {
        std::pair<long long, long long>{0, 0},
        std::pair<long long, long long>{1, -3},
        std::pair<long long, long long>{2, 7},
    };
    assert(slope == expected_slope);
}

int main() {
    test_max_flow();
    test_bounded_flow();
    test_bounded_min_cost_flow();
    test_min_cost_flow();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
