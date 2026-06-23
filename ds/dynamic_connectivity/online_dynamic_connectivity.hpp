#ifndef M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP
#define M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "../../monoid/add.hpp"
#include "../dynamic_tree/link_cut_tree.hpp"

namespace m1une {
namespace ds {

struct OnlineDynamicConnectivity {
   private:
    using Forest = LinkCutTree<m1une::monoid::Add<int>>;

    struct Edge {
        int u;
        int v;
        bool alive;
        bool tree;
        int previous_u = -1;
        int next_u = -1;
        int previous_v = -1;
        int next_v = -1;
    };

    int _n;
    int _component_count;
    int _active_edge_count = 0;
    Forest _forest;
    std::vector<Edge> _edges;
    std::vector<int> _tree_head;
    std::vector<int> _non_tree_head;
    std::vector<std::uint32_t> _visited;
    std::vector<std::uint32_t> _edge_visited;
    std::uint32_t _visit_token = 0;
    std::vector<int> _stack;
    std::vector<int> _component;

    int endpoint_side(const Edge& edge, int v) const {
        return edge.u == v ? 0 : 1;
    }

    int& previous(Edge& edge, int side) {
        return side == 0 ? edge.previous_u : edge.previous_v;
    }

    int& next(Edge& edge, int side) {
        return side == 0 ? edge.next_u : edge.next_v;
    }

    int next(const Edge& edge, int side) const {
        return side == 0 ? edge.next_u : edge.next_v;
    }

    void insert_one(std::vector<int>& head, int edge_id, int v, int side) {
        Edge& edge = _edges[edge_id];
        int old_head = head[v];
        previous(edge, side) = -1;
        next(edge, side) = old_head;
        if (old_head != -1) {
            Edge& old_edge = _edges[old_head];
            previous(old_edge, endpoint_side(old_edge, v)) = edge_id;
        }
        head[v] = edge_id;
    }

    void erase_one(std::vector<int>& head, int edge_id, int v, int side) {
        Edge& edge = _edges[edge_id];
        int previous_id = previous(edge, side);
        int next_id = next(edge, side);
        if (previous_id == -1) {
            head[v] = next_id;
        } else {
            Edge& previous_edge = _edges[previous_id];
            next(previous_edge, endpoint_side(previous_edge, v)) = next_id;
        }
        if (next_id != -1) {
            Edge& next_edge = _edges[next_id];
            previous(next_edge, endpoint_side(next_edge, v)) = previous_id;
        }
        previous(edge, side) = -1;
        next(edge, side) = -1;
    }

    void insert_incident(std::vector<int>& head, int edge_id) {
        const Edge& edge = _edges[edge_id];
        int u = edge.u;
        int v = edge.v;
        insert_one(head, edge_id, u, 0);
        if (u != v) insert_one(head, edge_id, v, 1);
    }

    void erase_incident(std::vector<int>& head, int edge_id) {
        const Edge& edge = _edges[edge_id];
        int u = edge.u;
        int v = edge.v;
        erase_one(head, edge_id, u, 0);
        if (u != v) erase_one(head, edge_id, v, 1);
    }

    void make_tree_edge(int edge_id) {
        Edge& edge = _edges[edge_id];
        assert(edge.alive && !edge.tree && edge.u != edge.v);
        erase_incident(_non_tree_head, edge_id);
        bool linked = _forest.link(edge.u, edge.v);
        assert(linked);
        edge.tree = true;
        insert_incident(_tree_head, edge_id);
        _component_count--;
    }

    void collect_component(int start) {
        _visit_token++;
        if (_visit_token == 0) {
            std::fill(_visited.begin(), _visited.end(), 0);
            std::fill(_edge_visited.begin(), _edge_visited.end(), 0);
            _visit_token = 1;
        }
        _stack.clear();
        _component.clear();
        _visited[start] = _visit_token;
        _stack.push_back(start);
        while (!_stack.empty()) {
            int v = _stack.back();
            _stack.pop_back();
            _component.push_back(v);
            for (int edge_id = _tree_head[v]; edge_id != -1;) {
                const Edge& edge = _edges[edge_id];
                int edge_side = endpoint_side(edge, v);
                edge_id = next(edge, edge_side);
                int to = edge.u ^ edge.v ^ v;
                if (_visited[to] == _visit_token) continue;
                _visited[to] = _visit_token;
                _stack.push_back(to);
            }
        }
    }

    void reconnect(int u, int v) {
        int start = _forest.component_size(u) <= _forest.component_size(v) ? u : v;
        collect_component(start);
        int replacement = -1;
        for (int x : _component) {
            for (int edge_id = _non_tree_head[x]; edge_id != -1;) {
                const Edge& edge = _edges[edge_id];
                int edge_side = endpoint_side(edge, x);
                int current_edge = edge_id;
                edge_id = next(edge, edge_side);
                if (_edge_visited[current_edge] == _visit_token) continue;
                _edge_visited[current_edge] = _visit_token;
                if (_visited[edge.u] != _visit_token || _visited[edge.v] != _visit_token) {
                    replacement = current_edge;
                    break;
                }
            }
            if (replacement != -1) break;
        }
        if (replacement != -1) make_tree_edge(replacement);
    }

   public:
    OnlineDynamicConnectivity() : OnlineDynamicConnectivity(0) {}

    explicit OnlineDynamicConnectivity(int n)
        : _n(n),
          _component_count(n),
          _forest(n),
          _tree_head(n, -1),
          _non_tree_head(n, -1),
          _visited(n, 0) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int active_edge_count() const {
        return _active_edge_count;
    }

    int component_count() const {
        return _component_count;
    }

    void reserve_edges(int count) {
        assert(0 <= count);
        _edges.reserve(count);
        _edge_visited.reserve(count);
    }

    bool edge_alive(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
        return _edges[edge_id].alive;
    }

    std::pair<int, int> edge_endpoints(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
        return {_edges[edge_id].u, _edges[edge_id].v};
    }

    bool connected(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        return _forest.connected(u, v);
    }

    bool same(int u, int v) {
        return connected(u, v);
    }

    int component_size(int v) {
        assert(0 <= v && v < _n);
        return _forest.component_size(v);
    }

    int add_edge(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        bool is_tree = u != v && _forest.link(u, v);
        int edge_id = int(_edges.size());
        Edge edge;
        edge.u = u;
        edge.v = v;
        edge.alive = true;
        edge.tree = is_tree;
        _edges.push_back(edge);
        _edge_visited.push_back(0);
        _active_edge_count++;
        if (is_tree) {
            insert_incident(_tree_head, edge_id);
            _component_count--;
        } else {
            insert_incident(_non_tree_head, edge_id);
        }
        return edge_id;
    }

    bool erase_edge(int edge_id) {
        assert(0 <= edge_id && edge_id < int(_edges.size()));
        Edge& edge = _edges[edge_id];
        if (!edge.alive) return false;
        edge.alive = false;
        _active_edge_count--;
        if (!edge.tree) {
            erase_incident(_non_tree_head, edge_id);
            return true;
        }

        erase_incident(_tree_head, edge_id);
        bool cut = _forest.cut(edge.u, edge.v);
        assert(cut);
        _component_count++;
        reconnect(edge.u, edge.v);
        return true;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_ONLINE_DYNAMIC_CONNECTIVITY_HPP
