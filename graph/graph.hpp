#ifndef M1UNE_GRAPH_GRAPH_HPP
#define M1UNE_GRAPH_GRAPH_HPP 1

#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace graph {

template <class T = int>
struct Edge {
    using cost_type = T;

    int from;
    int to;
    T cost;
    int id;
    bool alive;

    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}
    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)
        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}

    int other(int v) const {
        assert(v == from || v == to);
        return from ^ to ^ v;
    }
};

template <class T = int>
struct Graph {
    using edge_type = Edge<T>;
    using cost_type = T;

   private:
    int _n;
    int _edge_count;
    std::vector<std::vector<edge_type>> _g;
    std::vector<std::vector<std::pair<int, int>>> _edge_positions;

   public:
    Graph() : _n(0), _edge_count(0) {}
    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int edge_count() const {
        return _edge_count;
    }

    int add_vertex() {
        _g.emplace_back();
        return _n++;
    }

    int add_directed_edge(int from, int to, T cost = T(1)) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        int id = _edge_count++;
        int idx = int(_g[from].size());
        _g[from].push_back(edge_type(from, to, cost, id));
        _edge_positions.emplace_back();
        _edge_positions.back().push_back({from, idx});
        return id;
    }

    int add_edge(int u, int v, T cost = T(1)) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int id = _edge_count++;
        int u_idx = int(_g[u].size());
        int v_idx = int(_g[v].size());
        _g[u].push_back(edge_type(u, v, cost, id));
        _g[v].push_back(edge_type(v, u, cost, id));
        _edge_positions.emplace_back();
        _edge_positions.back().push_back({u, u_idx});
        _edge_positions.back().push_back({v, v_idx});
        return id;
    }

    void set_edge_alive(int id, bool alive) {
        assert(0 <= id && id < _edge_count);
        for (auto [v, idx] : _edge_positions[id]) {
            _g[v][idx].alive = alive;
        }
    }

    void erase_edge(int id) {
        set_edge_alive(id, false);
    }

    void revive_edge(int id) {
        set_edge_alive(id, true);
    }

    bool is_edge_alive(int id) const {
        assert(0 <= id && id < _edge_count);
        assert(!_edge_positions[id].empty());
        auto [v, idx] = _edge_positions[id][0];
        return _g[v][idx].alive;
    }

    const std::vector<edge_type>& operator[](int v) const {
        assert(0 <= v && v < _n);
        return _g[v];
    }

    std::vector<edge_type>& operator[](int v) {
        assert(0 <= v && v < _n);
        return _g[v];
    }

    const std::vector<std::vector<edge_type>>& adjacency() const {
        return _g;
    }

    std::vector<std::vector<edge_type>>& adjacency() {
        return _g;
    }

    std::vector<edge_type> edges(bool include_inactive = false) const {
        std::vector<edge_type> result;
        result.reserve(_edge_count);
        std::vector<char> used(_edge_count, false);
        for (int v = 0; v < _n; v++) {
            for (const auto& e : _g[v]) {
                if (!include_inactive && !e.alive) continue;
                if (0 <= e.id && e.id < _edge_count) {
                    if (used[e.id]) continue;
                    used[e.id] = true;
                }
                result.push_back(e);
            }
        }
        return result;
    }

    Graph reversed() const {
        Graph result(_n);
        result._edge_count = _edge_count;
        result._edge_positions.assign(_edge_count, {});
        for (int v = 0; v < _n; v++) {
            for (const auto& e : _g[v]) {
                int idx = int(result._g[e.to].size());
                result._g[e.to].push_back(edge_type(e.to, e.from, e.cost, e.id, e.alive));
                if (0 <= e.id && e.id < _edge_count) result._edge_positions[e.id].push_back({e.to, idx});
            }
        }
        return result;
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_GRAPH_HPP
