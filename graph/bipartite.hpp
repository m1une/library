#ifndef M1UNE_GRAPH_BIPARTITE_HPP
#define M1UNE_GRAPH_BIPARTITE_HPP 1

#include <cassert>
#include <optional>
#include <queue>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct BipartiteResult {
    bool is_bipartite;
    std::vector<int> color;
    std::vector<int> left_vertices;
    std::vector<int> right_vertices;
    std::vector<int> left_id;
    std::vector<int> right_id;
};

template <class T>
BipartiteResult bipartite(const Graph<T>& g) {
    int n = g.size();
    BipartiteResult result;
    result.is_bipartite = true;
    result.color.assign(n, -1);
    result.left_id.assign(n, -1);
    result.right_id.assign(n, -1);

    std::vector<std::vector<int>> adjacency(n);
    for (const auto& e : g.edges()) {
        adjacency[e.from].push_back(e.to);
        adjacency[e.to].push_back(e.from);
    }

    std::queue<int> que;
    for (int s = 0; s < n; s++) {
        if (result.color[s] != -1) continue;
        result.color[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int to : adjacency[v]) {
                if (result.color[to] == -1) {
                    result.color[to] = result.color[v] ^ 1;
                    que.push(to);
                } else if (result.color[to] == result.color[v]) {
                    result.is_bipartite = false;
                    return result;
                }
            }
        }
    }

    for (int v = 0; v < n; v++) {
        if (result.color[v] == 0) {
            result.left_id[v] = int(result.left_vertices.size());
            result.left_vertices.push_back(v);
        } else {
            result.right_id[v] = int(result.right_vertices.size());
            result.right_vertices.push_back(v);
        }
    }

    return result;
}

template <class T>
bool is_bipartite(const Graph<T>& g) {
    return bipartite(g).is_bipartite;
}

struct BipartiteVertexSet {
    std::vector<int> left;
    std::vector<int> right;

    int size() const {
        return int(left.size() + right.size());
    }
};

struct BipartiteMatching {
    struct Edge {
        int left;
        int right;
        int id;
        bool alive;
    };

    struct Pair {
        int left;
        int right;
        int edge_id;
    };

   private:
    int _left_size;
    int _right_size;
    std::vector<Edge> _edges;
    std::vector<std::vector<int>> _adj;
    std::vector<std::vector<int>> _radj;
    std::vector<int> _left_match;
    std::vector<int> _right_match;
    std::vector<int> _left_match_edge;
    std::vector<int> _right_match_edge;
    bool _calculated;

    void invalidate() {
        _calculated = false;
    }

    void ensure_matching() {
        if (!_calculated) max_matching();
    }

   public:
    BipartiteMatching() : BipartiteMatching(0, 0) {}

    BipartiteMatching(int left_size, int right_size)
        : _left_size(left_size),
          _right_size(right_size),
          _adj(left_size),
          _radj(right_size),
          _left_match(left_size, -1),
          _right_match(right_size, -1),
          _left_match_edge(left_size, -1),
          _right_match_edge(right_size, -1),
          _calculated(false) {
        assert(0 <= left_size);
        assert(0 <= right_size);
    }

    int left_size() const {
        return _left_size;
    }

    int right_size() const {
        return _right_size;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int left, int right) {
        assert(0 <= left && left < _left_size);
        assert(0 <= right && right < _right_size);
        int id = int(_edges.size());
        _edges.push_back(Edge{left, right, id, true});
        _adj[left].push_back(id);
        _radj[right].push_back(id);
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
        _left_match.assign(_left_size, -1);
        _right_match.assign(_right_size, -1);
        _left_match_edge.assign(_left_size, -1);
        _right_match_edge.assign(_right_size, -1);

        std::vector<int> dist(_left_size);
        auto bfs = [&]() -> bool {
            std::queue<int> que;
            bool found = false;
            for (int l = 0; l < _left_size; l++) {
                if (_left_match[l] == -1) {
                    dist[l] = 0;
                    que.push(l);
                } else {
                    dist[l] = -1;
                }
            }

            while (!que.empty()) {
                int l = que.front();
                que.pop();
                for (int id : _adj[l]) {
                    const auto& e = _edges[id];
                    if (!e.alive) continue;
                    int next_left = _right_match[e.right];
                    if (next_left == -1) {
                        found = true;
                    } else if (dist[next_left] == -1) {
                        dist[next_left] = dist[l] + 1;
                        que.push(next_left);
                    }
                }
            }
            return found;
        };

        auto dfs = [&](auto self, int l) -> bool {
            for (int id : _adj[l]) {
                const auto& e = _edges[id];
                if (!e.alive) continue;
                int next_left = _right_match[e.right];
                if (next_left != -1 && (dist[next_left] != dist[l] + 1 || !self(self, next_left))) {
                    continue;
                }
                _left_match[l] = e.right;
                _right_match[e.right] = l;
                _left_match_edge[l] = id;
                _right_match_edge[e.right] = id;
                return true;
            }
            dist[l] = -1;
            return false;
        };

        int result = 0;
        while (bfs()) {
            for (int l = 0; l < _left_size; l++) {
                if (_left_match[l] == -1 && dfs(dfs, l)) result++;
            }
        }

        _calculated = true;
        return result;
    }

    int matching_size() {
        ensure_matching();
        int result = 0;
        for (int right : _left_match) {
            if (right != -1) result++;
        }
        return result;
    }

    std::vector<int> left_match() {
        ensure_matching();
        return _left_match;
    }

    std::vector<int> right_match() {
        ensure_matching();
        return _right_match;
    }

    std::vector<Pair> matching() {
        ensure_matching();
        std::vector<Pair> result;
        for (int l = 0; l < _left_size; l++) {
            if (_left_match[l] != -1) result.push_back(Pair{l, _left_match[l], _left_match_edge[l]});
        }
        return result;
    }

    BipartiteVertexSet minimum_vertex_cover() {
        ensure_matching();

        std::vector<char> visited_left(_left_size, false), visited_right(_right_size, false);
        std::queue<int> que;
        for (int l = 0; l < _left_size; l++) {
            if (_left_match[l] == -1) {
                visited_left[l] = true;
                que.push(l);
            }
        }

        while (!que.empty()) {
            int l = que.front();
            que.pop();
            for (int id : _adj[l]) {
                const auto& e = _edges[id];
                if (!e.alive || _left_match_edge[l] == id || visited_right[e.right]) continue;
                visited_right[e.right] = true;
                int next_left = _right_match[e.right];
                if (next_left != -1 && !visited_left[next_left]) {
                    visited_left[next_left] = true;
                    que.push(next_left);
                }
            }
        }

        BipartiteVertexSet result;
        for (int l = 0; l < _left_size; l++) {
            if (!visited_left[l]) result.left.push_back(l);
        }
        for (int r = 0; r < _right_size; r++) {
            if (visited_right[r]) result.right.push_back(r);
        }
        return result;
    }

    BipartiteVertexSet maximum_independent_set() {
        auto cover = minimum_vertex_cover();
        std::vector<char> in_left_cover(_left_size, false), in_right_cover(_right_size, false);
        for (int l : cover.left) in_left_cover[l] = true;
        for (int r : cover.right) in_right_cover[r] = true;

        BipartiteVertexSet result;
        for (int l = 0; l < _left_size; l++) {
            if (!in_left_cover[l]) result.left.push_back(l);
        }
        for (int r = 0; r < _right_size; r++) {
            if (!in_right_cover[r]) result.right.push_back(r);
        }
        return result;
    }

    std::optional<std::vector<int>> minimum_edge_cover() {
        ensure_matching();

        std::vector<int> result;
        std::vector<char> covered_left(_left_size, false), covered_right(_right_size, false);
        std::vector<char> used_edge(_edges.size(), false);

        auto use_edge = [&](int id) {
            if (used_edge[id]) return;
            used_edge[id] = true;
            result.push_back(id);
            covered_left[_edges[id].left] = true;
            covered_right[_edges[id].right] = true;
        };

        for (int l = 0; l < _left_size; l++) {
            if (_left_match_edge[l] != -1) use_edge(_left_match_edge[l]);
        }

        for (int l = 0; l < _left_size; l++) {
            if (covered_left[l]) continue;
            int id = -1;
            for (int edge_id : _adj[l]) {
                if (_edges[edge_id].alive) {
                    id = edge_id;
                    break;
                }
            }
            if (id == -1) return std::nullopt;
            use_edge(id);
        }

        for (int r = 0; r < _right_size; r++) {
            if (covered_right[r]) continue;
            int id = -1;
            for (int edge_id : _radj[r]) {
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

struct BipartiteMatchingGraph {
    BipartiteResult parts;
    BipartiteMatching matching;
    std::vector<int> original_edge_id;

    int left_vertex(int left) const {
        assert(0 <= left && left < int(parts.left_vertices.size()));
        return parts.left_vertices[left];
    }

    int right_vertex(int right) const {
        assert(0 <= right && right < int(parts.right_vertices.size()));
        return parts.right_vertices[right];
    }

    int original_edge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));
        return original_edge_id[edge_id];
    }
};

template <class T>
std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>& g) {
    auto parts = bipartite(g);
    if (!parts.is_bipartite) return std::nullopt;

    BipartiteMatchingGraph result;
    result.parts = parts;
    result.matching = BipartiteMatching(int(parts.left_vertices.size()), int(parts.right_vertices.size()));

    for (const auto& e : g.edges()) {
        int left, right;
        if (parts.color[e.from] == 0) {
            left = parts.left_id[e.from];
            right = parts.right_id[e.to];
        } else {
            left = parts.left_id[e.to];
            right = parts.right_id[e.from];
        }
        int id = result.matching.add_edge(left, right);
        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id + 1);
        result.original_edge_id[id] = e.id;
    }

    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BIPARTITE_HPP
