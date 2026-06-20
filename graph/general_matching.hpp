#ifndef M1UNE_GRAPH_GENERAL_MATCHING_HPP
#define M1UNE_GRAPH_GENERAL_MATCHING_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "graph.hpp"

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

    bool is_matched_edge(int id) const {
        const auto& e = _edges[id];
        return _mate[e.from] == e.to && _mate_edge[e.from] == id;
    }

    enum MatchingLabel : char {
        even_label,
        odd_label,
        unlabeled
    };

    struct MutablePartition {
        std::vector<int> parent;
        std::vector<int> rank;
        std::vector<int> representative;

        MutablePartition() = default;

        explicit MutablePartition(int n) {
            reset(n);
        }

        void reset(int n) {
            parent.resize(n);
            rank.assign(n, 0);
            representative.resize(n);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                representative[i] = i;
            }
        }

        int root(int v) {
            if (parent[v] == v) return v;
            return parent[v] = root(parent[v]);
        }

        int operator()(int v) {
            return representative[root(v)];
        }

        void unite(int a, int b) {
            int ra = root(a);
            int rb = root(b);
            if (ra == rb) return;
            if (rank[ra] < rank[rb]) std::swap(ra, rb);
            parent[rb] = ra;
            if (rank[ra] == rank[rb]) rank[ra]++;
        }

        void make_rep(int v) {
            representative[root(v)] = v;
        }
    };

    struct EdgeBucketQueue {
        std::vector<std::vector<int>> bucket;
        std::vector<int> head;

        void reset(int n) {
            bucket.assign(n + 3, {});
            head.assign(n + 3, 0);
        }

        void insert(int edge_id, int key) {
            if (key < 0 || int(bucket.size()) <= key) return;
            bucket[key].push_back(edge_id);
        }

        int pop(int key) {
            if (key < 0 || int(bucket.size()) <= key) return -1;
            if (head[key] == int(bucket[key].size())) return -1;
            return bucket[key][head[key]++];
        }
    };

    struct NewMatchingPair {
        int from;
        int to;
        int edge_id;
    };

    // General-graph shortest augmenting path phase solver.
    struct MicaliVaziraniSolver {
        GeneralMatching& graph;
        int n;
        int matching_size;
        int delta;
        int visit_token;
        int even_time_token;
        MutablePartition base;
        MutablePartition delayed_base;
        EdgeBucketQueue queue;
        std::vector<MatchingLabel> label;
        std::vector<MatchingLabel> h_label;
        std::vector<int> parent;
        std::vector<int> parent_edge;
        std::vector<int> source_bridge;
        std::vector<int> target_bridge;
        std::vector<int> bridge_edge;
        std::vector<int> lcp;
        std::vector<int> path_mark_1;
        std::vector<int> path_mark_2;
        std::vector<int> restore_vertex;
        std::vector<int> restore_value;
        std::vector<int> rep;
        std::vector<int> h_mate;
        std::vector<char> is_h_edge;
        std::vector<std::vector<int>> contracted_into;
        std::vector<int> h_parent_edge;
        std::vector<int> h_even_time;
        std::vector<int> h_bridge_edge;
        std::vector<int> h_bridge_dir;

        explicit MicaliVaziraniSolver(GeneralMatching& graph_)
            : graph(graph_),
              n(graph_._n),
              matching_size(0),
              delta(0),
              visit_token(0),
              even_time_token(0),
              base(n),
              delayed_base(n),
              label(n, unlabeled),
              h_label(n, unlabeled),
              parent(n, -1),
              parent_edge(n, -1),
              source_bridge(n, -1),
              target_bridge(n, -1),
              bridge_edge(n, -1),
              lcp(n, 0),
              path_mark_1(n, 0),
              path_mark_2(n, 0),
              rep(n, -1),
              h_mate(n, -1),
              is_h_edge(graph_._edges.size(), false),
              contracted_into(n),
              h_parent_edge(n, -1),
              h_even_time(n, 0),
              h_bridge_edge(n, -1),
              h_bridge_dir(n, 0) {}

        bool active(int edge_id) const {
            return graph._edges[edge_id].alive;
        }

        int other(int edge_id, int v) const {
            return graph._edges[edge_id].other(v);
        }

        int edge_weight(int edge_id) const {
            return graph.is_matched_edge(edge_id) ? 2 : 0;
        }

        void set_match(int edge_id) {
            const auto& e = graph._edges[edge_id];
            graph._mate[e.from] = e.to;
            graph._mate[e.to] = e.from;
            graph._mate_edge[e.from] = edge_id;
            graph._mate_edge[e.to] = edge_id;
        }

        void initialize_greedy_matching() {
            graph._mate.assign(n, -1);
            graph._mate_edge.assign(n, -1);
            matching_size = 0;
            for (const auto& e : graph._edges) {
                if (!e.alive) continue;
                if (graph._mate[e.from] != -1 || graph._mate[e.to] != -1) continue;
                set_match(e.id);
                matching_size++;
            }
        }

        void scan_edge(int edge_id, int from) {
            if (!active(edge_id)) return;
            int to = other(edge_id, from);
            if (to == from || graph._mate[to] == from || label[base(to)] == odd_label) return;
            if (label[to] == unlabeled) {
                queue.insert(edge_id, lcp[from] + 2);
            } else {
                queue.insert(edge_id, (lcp[from] + lcp[to]) / 2 + 1);
            }
        }

        void shrink_path(int blossom_base, int x, int y, int edge_id,
                         std::vector<std::pair<int, int>>& delayed_unions) {
            int v = base(x);
            while (v != blossom_base) {
                base.unite(v, blossom_base);
                delayed_unions.push_back({v, blossom_base});

                v = graph._mate[v];
                assert(v != -1);
                base.unite(v, blossom_base);
                delayed_unions.push_back({v, blossom_base});
                base.make_rep(blossom_base);

                source_bridge[v] = x;
                target_bridge[v] = y;
                bridge_edge[v] = edge_id;
                restore_vertex.push_back(v);
                restore_value.push_back(lcp[v]);
                lcp[v] = lcp[x] + lcp[y] - lcp[graph._mate[v]] + 2;

                for (int id : graph._adj[v]) scan_edge(id, v);
                assert(parent[v] != -1);
                v = base(parent[v]);
            }
            delayed_unions.push_back({blossom_base, blossom_base});
        }

        void build_phase_graph() {
            std::fill(h_mate.begin(), h_mate.end(), -1);
            std::fill(is_h_edge.begin(), is_h_edge.end(), false);
            for (auto& vertices : contracted_into) vertices.clear();

            for (int v = 0; v < n; v++) contracted_into[delayed_base(v)].push_back(v);

            for (const auto& e : graph._edges) {
                if (!e.alive) continue;
                int u = e.from;
                int v = e.to;
                int uh = delayed_base(u);
                int vh = delayed_base(v);
                if (uh == vh) continue;
                if (label[uh] == odd_label && label[vh] == odd_label) continue;

                int w = edge_weight(e.id);
                bool even_odd =
                    (label[uh] == even_label && label[vh] == odd_label && lcp[v] == lcp[u] + 1 - w) ||
                    (label[vh] == even_label && label[uh] == odd_label && lcp[u] == lcp[v] + 1 - w);
                bool unlabeled_unlabeled = label[uh] == unlabeled && label[vh] == unlabeled && w == 2;
                bool even_unlabeled =
                    (label[uh] == even_label && label[vh] == unlabeled && lcp[u] == delta - 2) ||
                    (label[vh] == even_label && label[uh] == unlabeled && lcp[v] == delta - 2);
                bool even_even = label[uh] == even_label && label[vh] == even_label;
                bool tight_even_even = even_even && lcp[u] + lcp[v] == 2 * delta + w - 2;

                if (even_odd || unlabeled_unlabeled || even_unlabeled || tight_even_even) {
                    is_h_edge[e.id] = true;
                    if (w == 2) {
                        h_mate[uh] = vh;
                        h_mate[vh] = uh;
                    }
                }
            }
        }

        bool phase_one() {
            delta = 0;
            base.reset(n);
            delayed_base.reset(n);
            queue.reset(n);
            std::fill(label.begin(), label.end(), unlabeled);
            std::fill(parent.begin(), parent.end(), -1);
            std::fill(parent_edge.begin(), parent_edge.end(), -1);
            std::fill(source_bridge.begin(), source_bridge.end(), -1);
            std::fill(target_bridge.begin(), target_bridge.end(), -1);
            std::fill(bridge_edge.begin(), bridge_edge.end(), -1);
            std::fill(lcp.begin(), lcp.end(), 0);

            for (int v = 0; v < n; v++) {
                if (graph._mate[v] == -1) label[v] = even_label;
            }
            for (int v = 0; v < n; v++) {
                if (label[v] != even_label) continue;
                for (int id : graph._adj[v]) scan_edge(id, v);
            }

            std::vector<std::pair<int, int>> delayed_unions;
            while (delta <= n + 1) {
                restore_vertex.clear();
                restore_value.clear();

                while (true) {
                    int edge_id = queue.pop(delta);
                    if (edge_id == -1) break;
                    if (!active(edge_id)) continue;

                    int x = graph._edges[edge_id].from;
                    int y = graph._edges[edge_id].to;
                    if (label[base(x)] != even_label) std::swap(x, y);
                    if (label[base(x)] != even_label) continue;
                    if (graph._mate[x] == y || base(x) == base(y) || label[base(y)] == odd_label) continue;

                    if (label[base(y)] == unlabeled) {
                        int z = graph._mate[y];
                        assert(z != -1);
                        lcp[y] = lcp[x] + 1;
                        lcp[z] = lcp[x] + 2;
                        parent[y] = x;
                        parent_edge[y] = edge_id;
                        parent[z] = y;
                        parent_edge[z] = graph._mate_edge[z];
                        label[y] = odd_label;
                        label[z] = even_label;
                        for (int id : graph._adj[z]) scan_edge(id, z);
                        continue;
                    }

                    if (label[base(y)] != even_label || lcp[x] + lcp[y] != 2 * delta - 2) continue;

                    ++visit_token;
                    int hx = base(x);
                    int hy = base(y);
                    path_mark_1[hx] = visit_token;
                    path_mark_2[hy] = visit_token;
                    while (path_mark_1[hy] != visit_token && path_mark_2[hx] != visit_token &&
                           (graph._mate[hx] != -1 || graph._mate[hy] != -1)) {
                        if (graph._mate[hx] != -1) {
                            assert(parent[graph._mate[hx]] != -1);
                            hx = base(parent[graph._mate[hx]]);
                            path_mark_1[hx] = visit_token;
                        }
                        if (graph._mate[hy] != -1) {
                            assert(parent[graph._mate[hy]] != -1);
                            hy = base(parent[graph._mate[hy]]);
                            path_mark_2[hy] = visit_token;
                        }
                    }

                    if (path_mark_1[hy] == visit_token || path_mark_2[hx] == visit_token) {
                        int blossom_base = path_mark_1[hy] == visit_token ? hy : hx;
                        shrink_path(blossom_base, x, y, edge_id, delayed_unions);
                        shrink_path(blossom_base, y, x, edge_id, delayed_unions);
                    } else {
                        for (int i = int(restore_vertex.size()) - 1; i >= 0; i--) {
                            lcp[restore_vertex[i]] = restore_value[i];
                        }
                        build_phase_graph();
                        return true;
                    }
                }

                for (auto [a, b] : delayed_unions) {
                    if (a == b) {
                        delayed_base.make_rep(a);
                    } else {
                        delayed_base.unite(a, b);
                    }
                }
                delayed_unions.clear();
                delta++;
            }
            return false;
        }

        int next_h_vertex_through_edge(int edge_id, int current_h) const {
            const auto& e = graph._edges[edge_id];
            return rep[rep[e.from] == current_h ? e.to : e.from];
        }

        int find_path_in_h(int h_vertex) {
            for (int v : contracted_into[h_vertex]) {
                for (int edge_id : graph._adj[v]) {
                    if (!is_h_edge[edge_id]) continue;
                    int uh = rep[other(edge_id, v)];
                    if (h_mate[h_vertex] == uh) continue;

                    if (h_label[uh] == unlabeled) {
                        int mate_uh = h_mate[uh];
                        h_label[uh] = odd_label;
                        h_parent_edge[uh] = edge_id;
                        if (mate_uh == -1) return uh;

                        h_label[mate_uh] = even_label;
                        h_even_time[mate_uh] = even_time_token++;
                        int found = find_path_in_h(mate_uh);
                        if (found != -1) return found;
                    } else {
                        int bh = delayed_base(h_vertex);
                        int zh = delayed_base(uh);
                        if (h_even_time[bh] >= h_even_time[zh]) continue;

                        std::vector<int> blossom_path;
                        std::vector<int> blossom_vertices;
                        while (zh != bh) {
                            blossom_vertices.push_back(zh);
                            zh = h_mate[zh];
                            assert(zh != -1);
                            blossom_vertices.push_back(zh);
                            blossom_path.push_back(zh);
                            assert(h_parent_edge[zh] != -1);
                            zh = delayed_base(next_h_vertex_through_edge(h_parent_edge[zh], zh));
                        }

                        for (int x : blossom_vertices) delayed_base.unite(x, bh);
                        delayed_base.make_rep(bh);

                        std::reverse(blossom_path.begin(), blossom_path.end());
                        for (int x : blossom_path) {
                            h_bridge_edge[x] = edge_id;
                            h_bridge_dir[x] = graph._edges[edge_id].to == v ? 1 : -1;
                        }
                        for (int x : blossom_path) {
                            int found = find_path_in_h(x);
                            if (found != -1) return found;
                        }
                    }
                }
            }
            return -1;
        }

        void collect_path_in_h(std::vector<int>& path, int from_h, int to_h) {
            if (from_h == to_h) return;
            if (h_label[from_h] == even_label) {
                int mate_from = h_mate[from_h];
                assert(mate_from != -1);
                int edge_id = h_parent_edge[mate_from];
                assert(edge_id != -1);
                path.push_back(edge_id);
                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, mate_from), to_h);
            } else {
                int edge_id = h_bridge_edge[from_h];
                assert(edge_id != -1);
                const auto& e = graph._edges[edge_id];
                int first = rep[h_bridge_dir[from_h] == 1 ? e.from : e.to];
                int second = rep[h_bridge_dir[from_h] == 1 ? e.to : e.from];
                collect_path_in_h(path, first, rep[h_mate[from_h]]);
                path.push_back(edge_id);
                collect_path_in_h(path, second, to_h);
            }
        }

        void add_new_pair(std::vector<NewMatchingPair>& pairs, int from, int to, int edge_id) const {
            const auto& e = graph._edges[edge_id];
            assert(e.alive);
            assert((e.from == from && e.to == to) || (e.from == to && e.to == from));
            pairs.push_back(NewMatchingPair{from, to, edge_id});
        }

        void collect_path_in_graph(std::vector<NewMatchingPair>& pairs, int from, int to) {
            if (from == to) return;
            if (label[from] == even_label) {
                int mate_from = graph._mate[from];
                assert(mate_from != -1);
                int parent_of_mate = parent[mate_from];
                int edge_id = parent_edge[mate_from];
                assert(parent_of_mate != -1 && edge_id != -1);
                add_new_pair(pairs, mate_from, parent_of_mate, edge_id);
                collect_path_in_graph(pairs, parent_of_mate, to);
            } else {
                assert(source_bridge[from] != -1 && target_bridge[from] != -1 && bridge_edge[from] != -1);
                collect_path_in_graph(pairs, source_bridge[from], graph._mate[from]);
                add_new_pair(pairs, source_bridge[from], target_bridge[from], bridge_edge[from]);
                collect_path_in_graph(pairs, target_bridge[from], to);
            }
        }

        void augment_path(const std::vector<int>& h_path) {
            std::vector<NewMatchingPair> pairs;
            for (int edge_id : h_path) {
                const auto& e = graph._edges[edge_id];
                add_new_pair(pairs, e.from, e.to, edge_id);
                collect_path_in_graph(pairs, e.from, rep[e.from]);
                collect_path_in_graph(pairs, e.to, rep[e.to]);
            }

            for (const auto& p : pairs) {
                if (graph._mate[p.from] != -1) {
                    int old = graph._mate[p.from];
                    graph._mate[old] = -1;
                    graph._mate_edge[old] = -1;
                }
                if (graph._mate[p.to] != -1) {
                    int old = graph._mate[p.to];
                    graph._mate[old] = -1;
                    graph._mate_edge[old] = -1;
                }
                graph._mate[p.from] = graph._mate[p.to] = -1;
                graph._mate_edge[p.from] = graph._mate_edge[p.to] = -1;
            }
            for (const auto& p : pairs) {
                assert(graph._mate[p.from] == -1 && graph._mate[p.to] == -1);
                graph._mate[p.from] = p.to;
                graph._mate[p.to] = p.from;
                graph._mate_edge[p.from] = p.edge_id;
                graph._mate_edge[p.to] = p.edge_id;
            }
            matching_size++;
        }

        void phase_two() {
            std::fill(h_label.begin(), h_label.end(), unlabeled);
            std::fill(h_parent_edge.begin(), h_parent_edge.end(), -1);
            std::fill(h_bridge_edge.begin(), h_bridge_edge.end(), -1);
            std::fill(h_bridge_dir.begin(), h_bridge_dir.end(), 0);
            for (int v = 0; v < n; v++) rep[v] = delayed_base(v);

            std::vector<std::vector<int>> paths;
            for (int h_vertex = 0; h_vertex < n; h_vertex++) {
                if (rep[h_vertex] != h_vertex) continue;
                if (h_label[h_vertex] != unlabeled || h_mate[h_vertex] != -1) continue;

                h_label[h_vertex] = even_label;
                h_even_time[h_vertex] = even_time_token++;
                int free_h = find_path_in_h(h_vertex);
                if (free_h == -1) continue;

                std::vector<int> path;
                int edge_id = h_parent_edge[free_h];
                assert(edge_id != -1);
                path.push_back(edge_id);
                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, free_h), h_vertex);
                paths.push_back(path);
            }

            assert(!paths.empty());
            for (const auto& path : paths) augment_path(path);
            for (auto& vertices : contracted_into) vertices.clear();
        }

        int solve() {
            initialize_greedy_matching();
            while (phase_one()) phase_two();
            return matching_size;
        }
    };

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
        MicaliVaziraniSolver solver(*this);
        int result = solver.solve();

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
