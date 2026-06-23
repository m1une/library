#ifndef M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP
#define M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

struct OfflineDynamicConnectivity {
   private:
    struct Edge {
        int u;
        int v;
        int begin;
        int end;
        bool alive;
    };

    struct Query {
        int u;
        int v;
        int time;
    };

    struct RollbackDsu {
        std::vector<int> parent_or_size;
        std::vector<std::pair<int, int>> history;

        explicit RollbackDsu(int n) : parent_or_size(n, -1) {}

        int leader(int v) const {
            while (parent_or_size[v] >= 0) v = parent_or_size[v];
            return v;
        }

        bool same(int u, int v) const {
            return leader(u) == leader(v);
        }

        void merge(int u, int v) {
            u = leader(u);
            v = leader(v);
            if (u == v) return;
            if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);
            history.emplace_back(v, parent_or_size[v]);
            parent_or_size[u] += parent_or_size[v];
            parent_or_size[v] = u;
        }

        int snapshot() const {
            return int(history.size());
        }

        void rollback(int snapshot) {
            while (int(history.size()) > snapshot) {
                auto [v, old_size] = history.back();
                history.pop_back();
                int parent = parent_or_size[v];
                parent_or_size[parent] -= old_size;
                parent_or_size[v] = old_size;
            }
        }
    };

    int _n;
    int _time = 0;
    std::vector<Edge> _edges;
    std::vector<Query> _queries;

    void dfs(
        const std::vector<int>& offset,
        const std::vector<std::pair<int, int>>& stored_edges,
        const std::vector<int>& query_at,
        std::vector<bool>& answer,
        RollbackDsu& dsu,
        int node,
        int base
    ) const {
        int snapshot = dsu.snapshot();
        for (int i = offset[node]; i < offset[node + 1]; i++) {
            auto [u, v] = stored_edges[i];
            dsu.merge(u, v);
        }
        if (node >= base) {
            int query_id = query_at[node - base];
            if (query_id != -1) {
                const Query& query = _queries[query_id];
                answer[query_id] = dsu.same(query.u, query.v);
            }
        } else {
            dfs(offset, stored_edges, query_at, answer, dsu, 2 * node, base);
            dfs(offset, stored_edges, query_at, answer, dsu, 2 * node + 1, base);
        }
        dsu.rollback(snapshot);
    }

   public:
    OfflineDynamicConnectivity() : OfflineDynamicConnectivity(0) {}

    explicit OfflineDynamicConnectivity(int n) : _n(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int query_count() const {
        return int(_queries.size());
    }

    int operation_count() const {
        return _time;
    }

    void reserve_edges(int count) {
        assert(0 <= count);
        _edges.reserve(count);
    }

    void reserve_queries(int count) {
        assert(0 <= count);
        _queries.reserve(count);
    }

    bool edge_alive(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
        return _edges[edge_id].alive;
    }

    int add_edge(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int edge_id = int(_edges.size());
        _edges.push_back(Edge{u, v, _time, -1, true});
        _time++;
        return edge_id;
    }

    bool erase_edge(int edge_id) {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
        Edge& edge = _edges[edge_id];
        if (!edge.alive) return false;
        edge.end = _time;
        edge.alive = false;
        _time++;
        return true;
    }

    int add_query(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int query_id = int(_queries.size());
        _queries.push_back(Query{u, v, _time});
        _time++;
        return query_id;
    }

    std::vector<bool> solve() const {
        std::vector<bool> answer(_queries.size(), false);
        if (_queries.empty()) return answer;
        if (_edges.empty()) {
            for (int query_id = 0; query_id < int(_queries.size()); query_id++) {
                answer[query_id] = _queries[query_id].u == _queries[query_id].v;
            }
            return answer;
        }

        int base = 1;
        while (base < _time) base *= 2;
        int node_count = 2 * base;
        std::vector<int> count(node_count, 0);
        for (const Edge& edge : _edges) {
            int end = edge.alive ? _time : edge.end;
            if (edge.begin < end && edge.u != edge.v) {
                int left = edge.begin + base;
                int right = end + base;
                while (left < right) {
                    if (left & 1) count[left++]++;
                    if (right & 1) count[--right]++;
                    left /= 2;
                    right /= 2;
                }
            }
        }
        std::vector<int> offset(node_count + 1, 0);
        for (int node = 1; node < node_count; node++) offset[node + 1] = offset[node] + count[node];
        std::vector<int> cursor = offset;
        std::vector<std::pair<int, int>> stored_edges(offset[node_count]);
        for (const Edge& edge : _edges) {
            int end = edge.alive ? _time : edge.end;
            if (edge.begin >= end || edge.u == edge.v) continue;
            int left = edge.begin + base;
            int right = end + base;
            while (left < right) {
                if (left & 1) stored_edges[cursor[left]++] = {edge.u, edge.v}, left++;
                if (right & 1) --right, stored_edges[cursor[right]++] = {edge.u, edge.v};
                left /= 2;
                right /= 2;
            }
        }
        std::vector<int> query_at(base, -1);
        for (int query_id = 0; query_id < int(_queries.size()); query_id++) {
            query_at[_queries[query_id].time] = query_id;
        }
        RollbackDsu dsu(_n);
        dsu.history.reserve(std::min<std::size_t>(_n, stored_edges.size()));
        dfs(offset, stored_edges, query_at, answer, dsu, 1, base);
        return answer;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP
