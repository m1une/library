#ifndef M1UNE_GRAPH_GENERAL_MATCHING_HPP
#define M1UNE_GRAPH_GENERAL_MATCHING_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <queue>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct GeneralMatching {
    struct Edge {
        int from;
        int to;
        int id;
        bool alive;

        int other(int v) const {
            assert(v == from || v == to);
            return from ^ to ^ v;
        }
    };

    struct Pair {
        int from;
        int to;
        int edge_id;
    };

   private:
    int _n;
    std::vector<Edge> _edges;
    std::vector<std::vector<int>> _adj;
    std::vector<int> _mate;
    std::vector<int> _mate_edge;
    bool _calculated;

    void invalidate() {
        _calculated = false;
    }

    void ensure_matching() {
        if (!_calculated) max_matching();
    }

    int lca(int a, int b, const std::vector<int>& base, const std::vector<int>& parent) const {
        std::vector<char> used(_n, false);
        while (true) {
            a = base[a];
            used[a] = true;
            if (_mate[a] == -1) break;
            a = parent[_mate[a]];
        }
        while (true) {
            b = base[b];
            if (used[b]) return b;
            b = parent[_mate[b]];
        }
    }

    void mark_path(int v, int b, int child, int child_edge, std::vector<int>& base, std::vector<int>& parent,
                   std::vector<int>& parent_edge, std::vector<char>& blossom) const {
        while (base[v] != b) {
            blossom[base[v]] = true;
            blossom[base[_mate[v]]] = true;
            parent[v] = child;
            parent_edge[v] = child_edge;

            int matched = _mate[v];
            int next_v = parent[matched];
            int next_edge = parent_edge[matched];
            child = matched;
            child_edge = next_edge;
            v = next_v;
        }
    }

    int find_augmenting_path(int root, std::vector<int>& parent, std::vector<int>& parent_edge) const {
        std::vector<char> used(_n, false), blossom(_n, false);
        std::vector<int> base(_n);
        std::queue<int> que;

        parent.assign(_n, -1);
        parent_edge.assign(_n, -1);
        for (int i = 0; i < _n; i++) base[i] = i;

        used[root] = true;
        que.push(root);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int id : _adj[v]) {
                const auto& e = _edges[id];
                if (!e.alive) continue;
                int u = e.other(v);
                if (base[v] == base[u] || _mate[v] == u) continue;

                if (u == root || (_mate[u] != -1 && parent[_mate[u]] != -1)) {
                    int cur_base = lca(v, u, base, parent);
                    std::fill(blossom.begin(), blossom.end(), false);
                    mark_path(v, cur_base, u, id, base, parent, parent_edge, blossom);
                    mark_path(u, cur_base, v, id, base, parent, parent_edge, blossom);
                    for (int i = 0; i < _n; i++) {
                        if (!blossom[base[i]]) continue;
                        base[i] = cur_base;
                        if (!used[i]) {
                            used[i] = true;
                            que.push(i);
                        }
                    }
                } else if (parent[u] == -1) {
                    parent[u] = v;
                    parent_edge[u] = id;
                    if (_mate[u] == -1) return u;
                    int next = _mate[u];
                    used[next] = true;
                    que.push(next);
                }
            }
        }
        return -1;
    }

   public:
    GeneralMatching() : GeneralMatching(0) {}

    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n, -1), _calculated(false) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int from, int to) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(from != to);
        int id = int(_edges.size());
        _edges.push_back(Edge{from, to, id, true});
        _adj[from].push_back(id);
        _adj[to].push_back(id);
        invalidate();
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_edges.size()));
        return _edges[i];
    }

    std::vector<Edge> edges(bool include_inactive = false) const {
        std::vector<Edge> result;
        result.reserve(_edges.size());
        for (const auto& e : _edges) {
            if (include_inactive || e.alive) result.push_back(e);
        }
        return result;
    }

    void set_edge_alive(int id, bool alive) {
        assert(0 <= id && id < int(_edges.size()));
        _edges[id].alive = alive;
        invalidate();
    }

    void erase_edge(int id) {
        set_edge_alive(id, false);
    }

    void revive_edge(int id) {
        set_edge_alive(id, true);
    }

    bool is_edge_alive(int id) const {
        assert(0 <= id && id < int(_edges.size()));
        return _edges[id].alive;
    }

    int max_matching() {
        _mate.assign(_n, -1);
        _mate_edge.assign(_n, -1);

        int result = 0;
        std::vector<int> parent, parent_edge;
        for (int root = 0; root < _n; root++) {
            if (_mate[root] != -1) continue;
            int finish = find_augmenting_path(root, parent, parent_edge);
            if (finish == -1) continue;

            result++;
            while (finish != -1) {
                int prev = parent[finish];
                int next = _mate[prev];
                int edge_id = parent_edge[finish];
                _mate[finish] = prev;
                _mate[prev] = finish;
                _mate_edge[finish] = edge_id;
                _mate_edge[prev] = edge_id;
                finish = next;
            }
        }

        _calculated = true;
        return result;
    }

    int matching_size() {
        ensure_matching();
        int result = 0;
        for (int v = 0; v < _n; v++) {
            if (v < _mate[v]) result++;
        }
        return result;
    }

    std::vector<int> mate() {
        ensure_matching();
        return _mate;
    }

    std::vector<int> mate_edge() {
        ensure_matching();
        return _mate_edge;
    }

    std::vector<Pair> matching() {
        ensure_matching();
        std::vector<Pair> result;
        for (int v = 0; v < _n; v++) {
            if (v < _mate[v]) result.push_back(Pair{v, _mate[v], _mate_edge[v]});
        }
        return result;
    }

    std::optional<std::vector<int>> minimum_edge_cover() {
        ensure_matching();

        std::vector<int> result;
        std::vector<char> covered(_n, false), used_edge(_edges.size(), false);

        auto use_edge = [&](int id) {
            if (used_edge[id]) return;
            used_edge[id] = true;
            result.push_back(id);
            covered[_edges[id].from] = true;
            covered[_edges[id].to] = true;
        };

        for (int v = 0; v < _n; v++) {
            if (v < _mate[v]) use_edge(_mate_edge[v]);
        }

        for (int v = 0; v < _n; v++) {
            if (covered[v]) continue;
            int id = -1;
            for (int edge_id : _adj[v]) {
                if (_edges[edge_id].alive) {
                    id = edge_id;
                    break;
                }
            }
            if (id == -1) return std::nullopt;
            use_edge(id);
        }

        return result;
    }
};

struct GeneralMatchingGraph {
    GeneralMatching matching;
    std::vector<int> original_edge_id;

    int original_edge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));
        return original_edge_id[edge_id];
    }
};

template <class T>
GeneralMatchingGraph make_general_matching(const Graph<T>& g) {
    GeneralMatchingGraph result;
    result.matching = GeneralMatching(g.size());
    for (const auto& e : g.edges()) {
        int id = result.matching.add_edge(e.from, e.to);
        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id + 1);
        result.original_edge_id[id] = e.id;
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_GENERAL_MATCHING_HPP
