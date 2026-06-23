#ifndef M1UNE_FLOW_GOMORY_HU_HPP
#define M1UNE_FLOW_GOMORY_HU_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap>
struct GomoryHu {
    struct Edge {
        int u;
        int v;
        Cap cap;
    };

   private:
    struct FlowEdge {
        int to;
        int rev;
        Cap cap;
        Cap initial_cap;
    };

    int _n;
    bool _built = false;
    std::vector<Edge> _edges;
    std::vector<Edge> _tree_edges;
    std::vector<int> _parent;
    std::vector<Cap> _cut_value;
    std::vector<std::vector<std::pair<int, Cap>>> _tree;
    std::vector<std::vector<int>> _up;
    std::vector<std::vector<Cap>> _minimum;
    std::vector<int> _depth;

    std::vector<std::vector<FlowEdge>> _graph;
    std::vector<Cap> _excess;
    std::vector<int> _height;
    std::vector<int> _height_count;
    std::vector<int> _current;
    std::vector<bool> _active;
    std::vector<std::vector<int>> _buckets;
    std::vector<int> _queue;
    int _highest;
    long long _work;
    long long _work_limit;

    void add_flow_edge(int u, int v, Cap cap) {
        if (u == v || cap == Cap(0)) return;
        int ui = int(_graph[u].size());
        int vi = int(_graph[v].size());
        _graph[u].push_back(FlowEdge{v, vi, cap, cap});
        _graph[v].push_back(FlowEdge{u, ui, cap, cap});
    }

    void reset_flow() {
        for (auto& edges : _graph) {
            for (auto& edge : edges) edge.cap = edge.initial_cap;
        }
    }

    void activate(int v, int s, int t) {
        int dead = 2 * _n;
        if (v == s || v == t || _active[v] || _excess[v] == Cap(0) || _height[v] >= dead) return;
        _active[v] = true;
        _buckets[_height[v]].push_back(v);
        _highest = std::max(_highest, _height[v]);
    }

    void rebuild_buckets(int s, int t) {
        for (auto& bucket : _buckets) bucket.clear();
        std::fill(_active.begin(), _active.end(), false);
        _highest = -1;
        for (int v = 0; v < _n; v++) activate(v, s, t);
    }

    void global_relabel(int s, int t) {
        int dead = 2 * _n;
        int unreachable = _n + 1;
        std::fill(_height.begin(), _height.end(), unreachable);
        std::fill(_height_count.begin(), _height_count.end(), 0);
        std::fill(_current.begin(), _current.end(), 0);

        int head = 0;
        int tail = 0;
        _height[t] = 0;
        _height[s] = _n;
        _queue[tail++] = t;
        while (head < tail) {
            int v = _queue[head++];
            for (const auto& edge : _graph[v]) {
                const FlowEdge& reverse = _graph[edge.to][edge.rev];
                if (reverse.cap == Cap(0) || _height[edge.to] != unreachable) continue;
                _height[edge.to] = _height[v] + 1;
                _queue[tail++] = edge.to;
            }
        }
        for (int v = 0; v < _n; v++) {
            _height[v] = std::min(_height[v], dead);
            _height_count[_height[v]]++;
        }
        rebuild_buckets(s, t);
        _work = 0;
    }

    void push(int v, FlowEdge& edge, int s, int t) {
        if (edge.cap == Cap(0) || _height[v] != _height[edge.to] + 1) return;
        Cap sent = std::min(_excess[v], edge.cap);
        if (sent == Cap(0)) return;
        bool was_zero = _excess[edge.to] == Cap(0);
        edge.cap -= sent;
        _graph[edge.to][edge.rev].cap += sent;
        _excess[v] -= sent;
        _excess[edge.to] += sent;
        if (was_zero) activate(edge.to, s, t);
    }

    void gap(int height, int s, int t) {
        int unreachable = _n + 1;
        for (int v = 0; v < _n; v++) {
            if (v == s || v == t || _height[v] <= height || _height[v] >= _n) continue;
            _height_count[_height[v]]--;
            _height[v] = unreachable;
            _height_count[_height[v]]++;
            _current[v] = 0;
        }
        rebuild_buckets(s, t);
    }

    bool relabel(int v, int s, int t) {
        int dead = 2 * _n;
        int old_height = _height[v];
        int new_height = dead;
        _work += int(_graph[v].size());
        for (const auto& edge : _graph[v]) {
            if (edge.cap != Cap(0)) new_height = std::min(new_height, _height[edge.to] + 1);
        }
        _height_count[old_height]--;
        _height[v] = std::min(new_height, dead);
        _height_count[_height[v]]++;
        _current[v] = 0;
        if (old_height < _n && _height_count[old_height] == 0) {
            gap(old_height, s, t);
            return true;
        }
        return false;
    }

    void discharge(int v, int s, int t) {
        while (_excess[v] != Cap(0) && _height[v] < 2 * _n) {
            if (_current[v] == int(_graph[v].size())) {
                if (relabel(v, s, t)) return;
                continue;
            }
            FlowEdge& edge = _graph[v][_current[v]];
            _work++;
            if (edge.cap != Cap(0) && _height[v] == _height[edge.to] + 1) {
                push(v, edge, s, t);
            } else {
                _current[v]++;
            }
        }
        activate(v, s, t);
    }

    Cap max_flow(int s, int t) {
        reset_flow();
        std::fill(_excess.begin(), _excess.end(), Cap(0));
        for (auto& edge : _graph[s]) {
            Cap sent = edge.cap;
            if (sent == Cap(0)) continue;
            edge.cap = Cap(0);
            _graph[edge.to][edge.rev].cap += sent;
            _excess[edge.to] += sent;
        }
        global_relabel(s, t);

        while (_highest >= 0) {
            if (_buckets[_highest].empty()) {
                _highest--;
                continue;
            }
            int v = _buckets[_highest].back();
            _buckets[_highest].pop_back();
            if (!_active[v] || _height[v] != _highest) continue;
            _active[v] = false;
            discharge(v, s, t);
            if (_work >= _work_limit) global_relabel(s, t);
        }
        return _excess[t];
    }

    std::vector<bool> source_side(int s) {
        std::vector<bool> visited(_n, false);
        int head = 0;
        int tail = 0;
        visited[s] = true;
        _queue[tail++] = s;
        while (head < tail) {
            int v = _queue[head++];
            for (const auto& edge : _graph[v]) {
                if (edge.cap == Cap(0) || visited[edge.to]) continue;
                visited[edge.to] = true;
                _queue[tail++] = edge.to;
            }
        }
        return visited;
    }

    void build_query_table() {
        int log = 1;
        while ((1LL << log) <= std::max(1, _n)) log++;
        const Cap infinity = std::numeric_limits<Cap>::max();
        _up.assign(log, std::vector<int>(_n, 0));
        _minimum.assign(log, std::vector<Cap>(_n, infinity));
        _depth.assign(_n, 0);
        if (_n == 0) return;

        std::vector<int> order;
        order.reserve(_n);
        order.push_back(0);
        for (int i = 0; i < int(order.size()); i++) {
            int v = order[i];
            for (auto [to, cap] : _tree[v]) {
                if (to == _up[0][v] && v != 0) continue;
                _up[0][to] = v;
                _minimum[0][to] = cap;
                _depth[to] = _depth[v] + 1;
                order.push_back(to);
            }
        }
        for (int k = 1; k < log; k++) {
            for (int v = 0; v < _n; v++) {
                int middle = _up[k - 1][v];
                _up[k][v] = _up[k - 1][middle];
                _minimum[k][v] = std::min(_minimum[k - 1][v], _minimum[k - 1][middle]);
            }
        }
    }

   public:
    GomoryHu() : GomoryHu(0) {}

    explicit GomoryHu(int n) : _n(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int u, int v, Cap cap) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        assert(Cap(0) <= cap);
        _built = false;
        int id = int(_edges.size());
        _edges.push_back(Edge{u, v, cap});
        return id;
    }

    void build() {
        std::vector<Edge> flow_edges;
        flow_edges.reserve(_edges.size());
        for (auto edge : _edges) {
            if (edge.u == edge.v || edge.cap == Cap(0)) continue;
            if (edge.u > edge.v) std::swap(edge.u, edge.v);
            flow_edges.push_back(edge);
        }
        std::sort(flow_edges.begin(), flow_edges.end(), [](const Edge& lhs, const Edge& rhs) {
            return std::pair<int, int>(lhs.u, lhs.v) < std::pair<int, int>(rhs.u, rhs.v);
        });
        int unique_edges = 0;
        for (const auto& edge : flow_edges) {
            if (unique_edges > 0 && flow_edges[unique_edges - 1].u == edge.u &&
                flow_edges[unique_edges - 1].v == edge.v) {
                flow_edges[unique_edges - 1].cap += edge.cap;
            } else {
                flow_edges[unique_edges++] = edge;
            }
        }
        flow_edges.resize(unique_edges);

        _graph.assign(_n, {});
        std::vector<int> degree(_n, 0);
        for (const auto& edge : flow_edges) {
            degree[edge.u]++;
            degree[edge.v]++;
        }
        for (int v = 0; v < _n; v++) _graph[v].reserve(degree[v]);
        for (const auto& edge : flow_edges) add_flow_edge(edge.u, edge.v, edge.cap);
        _excess.resize(_n);
        _height.resize(_n);
        _height_count.resize(2 * _n + 1);
        _current.resize(_n);
        _active.resize(_n);
        _buckets.resize(2 * _n + 1);
        _queue.resize(_n);
        long long arc_count = 0;
        for (const auto& edges : _graph) arc_count += int(edges.size());
        _work_limit = std::max(1LL, 4 * arc_count + _n);

        _parent.assign(_n, 0);
        _cut_value.assign(_n, std::numeric_limits<Cap>::max());
        for (int s = 1; s < _n; s++) {
            int t = _parent[s];
            Cap flow = max_flow(s, t);
            std::vector<bool> cut = source_side(s);
            for (int v = s + 1; v < _n; v++) {
                if (_parent[v] == t && cut[v]) _parent[v] = s;
            }
            if (cut[_parent[t]]) {
                _parent[s] = _parent[t];
                _parent[t] = s;
                _cut_value[s] = _cut_value[t];
                _cut_value[t] = flow;
            } else {
                _cut_value[s] = flow;
            }
        }

        _tree.assign(_n, {});
        _tree_edges.clear();
        if (_n > 0) _tree_edges.reserve(_n - 1);
        for (int v = 1; v < _n; v++) {
            int p = _parent[v];
            Cap cap = _cut_value[v];
            _tree_edges.push_back(Edge{v, p, cap});
            _tree[v].emplace_back(p, cap);
            _tree[p].emplace_back(v, cap);
        }
        build_query_table();
        _built = true;
    }

    const std::vector<Edge>& tree_edges() const {
        assert(_built);
        return _tree_edges;
    }

    const std::vector<int>& parent() const {
        assert(_built);
        return _parent;
    }

    const std::vector<Cap>& cut_values() const {
        assert(_built);
        return _cut_value;
    }

    Cap min_cut(int u, int v) const {
        assert(_built);
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        assert(u != v);
        Cap result = std::numeric_limits<Cap>::max();
        if (_depth[u] < _depth[v]) std::swap(u, v);
        int difference = _depth[u] - _depth[v];
        for (int k = 0; difference > 0; k++, difference >>= 1) {
            if ((difference & 1) == 0) continue;
            result = std::min(result, _minimum[k][u]);
            u = _up[k][u];
        }
        if (u == v) return result;
        for (int k = int(_up.size()) - 1; k >= 0; k--) {
            if (_up[k][u] == _up[k][v]) continue;
            result = std::min(result, _minimum[k][u]);
            result = std::min(result, _minimum[k][v]);
            u = _up[k][u];
            v = _up[k][v];
        }
        result = std::min(result, _minimum[0][u]);
        result = std::min(result, _minimum[0][v]);
        return result;
    }
};

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_GOMORY_HU_HPP
