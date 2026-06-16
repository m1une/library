#ifndef M1UNE_FLOW_MIN_COST_FLOW_HPP
#define M1UNE_FLOW_MIN_COST_FLOW_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap, class Cost>
struct MinCostFlow {
    struct Edge {
        int from;
        int to;
        Cap cap;
        Cap flow;
        Cost cost;
    };

   private:
    struct InternalEdge {
        int to;
        int rev;
        Cap cap;
        Cost cost;
    };

    int _n;
    std::vector<std::pair<int, int>> _pos;
    std::vector<std::vector<InternalEdge>> _g;

    void init_potential(int s, std::vector<Cost>& potential, Cost cost_inf) const {
        potential.assign(_n, cost_inf);
        potential[s] = Cost(0);
        for (int iter = 0; iter < _n - 1; iter++) {
            bool updated = false;
            for (int v = 0; v < _n; v++) {
                if (potential[v] == cost_inf) continue;
                for (const auto& e : _g[v]) {
                    if (e.cap == Cap(0)) continue;
                    Cost nd = potential[v] + e.cost;
                    if (nd < potential[e.to]) {
                        potential[e.to] = nd;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
        for (int v = 0; v < _n; v++) {
            if (potential[v] == cost_inf) potential[v] = Cost(0);
        }
    }

   public:
    MinCostFlow() : MinCostFlow(0) {}

    explicit MinCostFlow(int n) : _n(n), _g(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_pos.size());
    }

    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(Cap(0) <= cap);
        int id = int(_pos.size());
        int from_id = int(_g[from].size());
        int to_id = int(_g[to].size());
        if (from == to) to_id++;
        _pos.emplace_back(from, from_id);
        _g[from].push_back(InternalEdge{to, to_id, cap, cost});
        _g[to].push_back(InternalEdge{from, from_id, Cap(0), -cost});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_pos.size()));
        auto [from, idx] = _pos[i];
        const auto& e = _g[from][idx];
        const auto& re = _g[e.to][e.rev];
        return Edge{from, e.to, e.cap + re.cap, re.cap, e.cost};
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        result.reserve(_pos.size());
        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));
        return result;
    }

    std::pair<Cap, Cost> flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }

    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {
        auto result = slope(s, t, flow_limit);
        return result.back();
    }

    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {
        return slope(s, t, std::numeric_limits<Cap>::max());
    }

    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        const Cost cost_inf = std::numeric_limits<Cost>::max() / Cost(4);
        std::vector<Cost> potential, dist(_n);
        std::vector<int> prev_v(_n), prev_e(_n);
        init_potential(s, potential, cost_inf);

        std::vector<std::pair<Cap, Cost>> result;
        result.emplace_back(Cap(0), Cost(0));
        Cap flow = 0;
        Cost cost = 0;

        while (flow < flow_limit) {
            std::fill(dist.begin(), dist.end(), cost_inf);
            dist[s] = Cost(0);
            using P = std::pair<Cost, int>;
            std::priority_queue<P, std::vector<P>, std::greater<P>> que;
            que.emplace(Cost(0), s);

            while (!que.empty()) {
                auto [d, v] = que.top();
                que.pop();
                if (dist[v] != d) continue;
                for (int i = 0; i < int(_g[v].size()); i++) {
                    const auto& e = _g[v][i];
                    if (e.cap == Cap(0)) continue;
                    Cost nd = d + e.cost + potential[v] - potential[e.to];
                    if (nd >= dist[e.to]) continue;
                    dist[e.to] = nd;
                    prev_v[e.to] = v;
                    prev_e[e.to] = i;
                    que.emplace(nd, e.to);
                }
            }

            if (dist[t] == cost_inf) break;
            for (int v = 0; v < _n; v++) {
                if (dist[v] != cost_inf) potential[v] += dist[v];
            }

            Cap add = flow_limit - flow;
            for (int v = t; v != s; v = prev_v[v]) {
                add = std::min(add, _g[prev_v[v]][prev_e[v]].cap);
            }
            Cost path_cost = potential[t] - potential[s];
            for (int v = t; v != s; v = prev_v[v]) {
                auto& e = _g[prev_v[v]][prev_e[v]];
                e.cap -= add;
                _g[e.to][e.rev].cap += add;
            }

            flow += add;
            cost += Cost(add) * path_cost;
            result.emplace_back(flow, cost);
        }

        return result;
    }
};

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_MIN_COST_FLOW_HPP
