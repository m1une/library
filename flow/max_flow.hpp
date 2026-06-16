#ifndef M1UNE_FLOW_MAX_FLOW_HPP
#define M1UNE_FLOW_MAX_FLOW_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap>
struct MaxFlow {
    struct Edge {
        int from;
        int to;
        Cap cap;
        Cap flow;
    };

   private:
    struct InternalEdge {
        int to;
        int rev;
        Cap cap;
    };

    int _n;
    std::vector<std::pair<int, int>> _pos;
    std::vector<std::vector<InternalEdge>> _g;

   public:
    MaxFlow() : MaxFlow(0) {}

    explicit MaxFlow(int n) : _n(n), _g(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_pos.size());
    }

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(Cap(0) <= cap);
        int id = int(_pos.size());
        int from_id = int(_g[from].size());
        int to_id = int(_g[to].size());
        if (from == to) to_id++;
        _pos.emplace_back(from, from_id);
        _g[from].push_back(InternalEdge{to, to_id, cap});
        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_pos.size()));
        auto [from, idx] = _pos[i];
        const auto& e = _g[from][idx];
        const auto& re = _g[e.to][e.rev];
        return Edge{from, e.to, e.cap + re.cap, re.cap};
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        result.reserve(_pos.size());
        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));
        return result;
    }

    void change_edge(int i, Cap new_cap, Cap new_flow) {
        assert(0 <= i && i < int(_pos.size()));
        assert(Cap(0) <= new_flow && new_flow <= new_cap);
        auto [from, idx] = _pos[i];
        auto& e = _g[from][idx];
        auto& re = _g[e.to][e.rev];
        e.cap = new_cap - new_flow;
        re.cap = new_flow;
    }

    Cap max_flow(int s, int t) {
        return max_flow(s, t, std::numeric_limits<Cap>::max());
    }

    Cap max_flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> level(_n), iter(_n);
        auto bfs = [&]() -> bool {
            std::fill(level.begin(), level.end(), -1);
            std::queue<int> que;
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (const auto& e : _g[v]) {
                    if (e.cap == Cap(0) || level[e.to] != -1) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return true;
                    que.push(e.to);
                }
            }
            return level[t] != -1;
        };

        auto dfs = [&](auto self, int v, Cap up) -> Cap {
            if (v == t) return up;
            for (int& i = iter[v]; i < int(_g[v].size()); i++) {
                auto& e = _g[v][i];
                if (e.cap == Cap(0) || level[v] >= level[e.to]) continue;
                Cap d = self(self, e.to, std::min(up, e.cap));
                if (d == Cap(0)) continue;
                e.cap -= d;
                _g[e.to][e.rev].cap += d;
                return d;
            }
            return Cap(0);
        };

        Cap flow = 0;
        while (flow < flow_limit && bfs()) {
            std::fill(iter.begin(), iter.end(), 0);
            while (flow < flow_limit) {
                Cap f = dfs(dfs, s, flow_limit - flow);
                if (f == Cap(0)) break;
                flow += f;
            }
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) const {
        assert(0 <= s && s < _n);
        std::vector<bool> visited(_n, false);
        std::queue<int> que;
        visited[s] = true;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const auto& e : _g[v]) {
                if (e.cap == Cap(0) || visited[e.to]) continue;
                visited[e.to] = true;
                que.push(e.to);
            }
        }
        return visited;
    }
};

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_MAX_FLOW_HPP
