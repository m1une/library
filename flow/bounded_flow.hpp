#ifndef M1UNE_FLOW_BOUNDED_FLOW_HPP
#define M1UNE_FLOW_BOUNDED_FLOW_HPP 1

#include <cassert>
#include <optional>
#include <vector>

#include "max_flow.hpp"

namespace m1une {
namespace flow {

template <class Cap>
struct BoundedFlow {
    struct Edge {
        int from;
        int to;
        Cap lower;
        Cap upper;
    };

    struct ResultEdge {
        int from;
        int to;
        Cap lower;
        Cap upper;
        Cap flow;
    };

    struct Result {
        std::vector<ResultEdge> edges;
        std::vector<Cap> balance;

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
    BoundedFlow() : BoundedFlow(0) {}

    explicit BoundedFlow(int n) : _n(n), _balance(n, Cap(0)) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int from, int to, Cap lower, Cap upper) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(lower <= upper);
        int id = int(_edges.size());
        _edges.push_back(Edge{from, to, lower, upper});
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

    std::optional<Result> feasible_flow() const {
        return feasible_flow(_balance);
    }

    std::optional<Result> feasible_flow(const std::vector<Cap>& balance) const {
        assert(int(balance.size()) == _n);
        int ss = _n, tt = _n + 1;
        MaxFlow<Cap> mf(_n + 2);
        std::vector<int> edge_ids;
        edge_ids.reserve(_edges.size());

        std::vector<Cap> need = balance;
        for (const auto& e : _edges) {
            edge_ids.push_back(mf.add_edge(e.from, e.to, e.upper - e.lower));
            need[e.from] -= e.lower;
            need[e.to] += e.lower;
        }

        Cap positive_sum = Cap(0), negative_sum = Cap(0);
        for (int v = 0; v < _n; v++) {
            if (need[v] > Cap(0)) {
                positive_sum += need[v];
                mf.add_edge(ss, v, need[v]);
            } else if (need[v] < Cap(0)) {
                negative_sum += -need[v];
                mf.add_edge(v, tt, -need[v]);
            }
        }
        if (positive_sum != negative_sum) return std::nullopt;
        if (mf.max_flow(ss, tt) != positive_sum) return std::nullopt;

        Result result;
        result.balance = balance;
        result.edges.reserve(_edges.size());
        for (int i = 0; i < int(_edges.size()); i++) {
            auto used = mf.get_edge(edge_ids[i]).flow;
            const auto& e = _edges[i];
            result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, e.lower + used});
        }
        return result;
    }

    std::optional<Result> feasible_st_flow(int s, int t, Cap flow_value) const {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        std::vector<Cap> balance = _balance;
        balance[s] += flow_value;
        balance[t] -= flow_value;
        return feasible_flow(balance);
    }
};

template <class Cap>
using BFlow = BoundedFlow<Cap>;

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_BOUNDED_FLOW_HPP
