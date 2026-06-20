#ifndef M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
#define M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP 1

#include <cassert>
#include <optional>
#include <vector>

#include "min_cost_flow.hpp"

namespace m1une {
namespace flow {

template <class Cap, class Cost>
struct BoundedMinCostFlow {
    struct Edge {
        int from;
        int to;
        Cap lower;
        Cap upper;
        Cost cost;
    };

    struct ResultEdge {
        int from;
        int to;
        Cap lower;
        Cap upper;
        Cap flow;
        Cost cost;
    };

    struct Result {
        std::vector<ResultEdge> edges;
        std::vector<Cap> balance;
        Cost cost;

        ResultEdge get_edge(int i) const {
            assert(0 <= i && i < int(edges.size()));
            return edges[i];
        }

        Cap flow(int i) const {
            assert(0 <= i && i < int(edges.size()));
            return edges[i].flow;
        }
    };

   private:
    int _n;
    std::vector<Edge> _edges;
    std::vector<Cap> _balance;

   public:
    BoundedMinCostFlow() : BoundedMinCostFlow(0) {}

    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(lower <= upper);
        int id = int(_edges.size());
        _edges.push_back(Edge{from, to, lower, upper, cost});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_edges.size()));
        return _edges[i];
    }

    std::vector<Edge> edges() const {
        return _edges;
    }

    void set_balance(int v, Cap b) {
        assert(0 <= v && v < _n);
        _balance[v] = b;
    }

    void add_balance(int v, Cap b) {
        assert(0 <= v && v < _n);
        _balance[v] += b;
    }

    void add_supply(int v, Cap supply) {
        assert(Cap(0) <= supply);
        add_balance(v, supply);
    }

    void add_demand(int v, Cap demand) {
        assert(Cap(0) <= demand);
        add_balance(v, -demand);
    }

    Cap balance(int v) const {
        assert(0 <= v && v < _n);
        return _balance[v];
    }

    const std::vector<Cap>& balances() const {
        return _balance;
    }

    std::optional<Result> min_cost_flow() const {
        return min_cost_flow(_balance);
    }

    std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const {
        assert(int(balance.size()) == _n);
        int ss = _n, tt = _n + 1;
        MinCostFlow<Cap, Cost> mcf(_n + 2);

        std::vector<Cap> need = balance;
        std::vector<Cap> initial(_edges.size(), Cap(0));
        std::vector<int> edge_ids(_edges.size(), -1);
        std::vector<char> reversed(_edges.size(), false);

        for (int i = 0; i < int(_edges.size()); i++) {
            const auto& e = _edges[i];
            Cap cap = e.upper - e.lower;
            need[e.from] -= e.lower;
            need[e.to] += e.lower;
            if (e.cost < Cost(0)) {
                initial[i] = cap;
                need[e.from] -= cap;
                need[e.to] += cap;
                edge_ids[i] = mcf.add_edge(e.to, e.from, cap, -e.cost);
                reversed[i] = true;
            } else {
                edge_ids[i] = mcf.add_edge(e.from, e.to, cap, e.cost);
            }
        }

        Cap positive_sum = Cap(0), negative_sum = Cap(0);
        for (int v = 0; v < _n; v++) {
            if (need[v] > Cap(0)) {
                positive_sum += need[v];
                mcf.add_edge(ss, v, need[v], Cost(0));
            } else if (need[v] < Cap(0)) {
                negative_sum += -need[v];
                mcf.add_edge(v, tt, -need[v], Cost(0));
            }
        }
        if (positive_sum != negative_sum) return std::nullopt;

        auto [sent, extra_cost] = mcf.flow(ss, tt, positive_sum);
        (void)extra_cost;
        if (sent != positive_sum) return std::nullopt;

        Result result;
        result.balance = balance;
        result.cost = Cost(0);
        result.edges.reserve(_edges.size());
        for (int i = 0; i < int(_edges.size()); i++) {
            const auto& e = _edges[i];
            Cap used = mcf.get_edge(edge_ids[i]).flow;
            Cap residual_flow = reversed[i] ? initial[i] - used : used;
            Cap flow = e.lower + residual_flow;
            result.cost += Cost(flow) * e.cost;
            result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, flow, e.cost});
        }
        return result;
    }

    std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        std::vector<Cap> balance = _balance;
        balance[s] += flow_value;
        balance[t] -= flow_value;
        return min_cost_flow(balance);
    }
};

template <class Cap, class Cost>
using BMinCostFlow = BoundedMinCostFlow<Cap, Cost>;

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
