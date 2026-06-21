---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.hpp
    title: General Matching
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/general_matching
    links:
    - https://judge.yosupo.jp/problem/general_matching
  bundledCode: "#line 1 \"verify/graph/library_checker_general_matching.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n\
    #line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/general_matching.hpp\"\n\n\n\n#line 6 \"graph/general_matching.hpp\"\
    \n#include <optional>\n#line 9 \"graph/general_matching.hpp\"\n\n#line 11 \"graph/general_matching.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct GeneralMatching {\n    struct\
    \ Edge {\n        int from;\n        int to;\n        int id;\n        bool alive;\n\
    \n        int other(int v) const {\n            assert(v == from || v == to);\n\
    \            return from ^ to ^ v;\n        }\n    };\n\n    struct Pair {\n \
    \       int from;\n        int to;\n        int edge_id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<int> _mate;\n    std::vector<int> _mate_edge;\n    bool\
    \ _calculated;\n\n    void invalidate() {\n        _calculated = false;\n    }\n\
    \n    void ensure_matching() {\n        if (!_calculated) max_matching();\n  \
    \  }\n\n    bool is_matched_edge(int id) const {\n        const auto& e = _edges[id];\n\
    \        return _mate[e.from] == e.to && _mate_edge[e.from] == id;\n    }\n\n\
    \    enum MatchingLabel : char {\n        even_label,\n        odd_label,\n  \
    \      unlabeled\n    };\n\n    struct MutablePartition {\n        std::vector<int>\
    \ parent;\n        std::vector<int> rank;\n        std::vector<int> representative;\n\
    \n        MutablePartition() = default;\n\n        explicit MutablePartition(int\
    \ n) {\n            reset(n);\n        }\n\n        void reset(int n) {\n    \
    \        parent.resize(n);\n            rank.assign(n, 0);\n            representative.resize(n);\n\
    \            for (int i = 0; i < n; i++) {\n                parent[i] = i;\n \
    \               representative[i] = i;\n            }\n        }\n\n        int\
    \ root(int v) {\n            if (parent[v] == v) return v;\n            return\
    \ parent[v] = root(parent[v]);\n        }\n\n        int operator()(int v) {\n\
    \            return representative[root(v)];\n        }\n\n        void unite(int\
    \ a, int b) {\n            int ra = root(a);\n            int rb = root(b);\n\
    \            if (ra == rb) return;\n            if (rank[ra] < rank[rb]) std::swap(ra,\
    \ rb);\n            parent[rb] = ra;\n            if (rank[ra] == rank[rb]) rank[ra]++;\n\
    \        }\n\n        void make_rep(int v) {\n            representative[root(v)]\
    \ = v;\n        }\n    };\n\n    struct EdgeBucketQueue {\n        std::vector<std::vector<int>>\
    \ bucket;\n        std::vector<int> head;\n\n        void reset(int n) {\n   \
    \         bucket.assign(n + 3, {});\n            head.assign(n + 3, 0);\n    \
    \    }\n\n        void insert(int edge_id, int key) {\n            if (key < 0\
    \ || int(bucket.size()) <= key) return;\n            bucket[key].push_back(edge_id);\n\
    \        }\n\n        int pop(int key) {\n            if (key < 0 || int(bucket.size())\
    \ <= key) return -1;\n            if (head[key] == int(bucket[key].size())) return\
    \ -1;\n            return bucket[key][head[key]++];\n        }\n    };\n\n   \
    \ struct NewMatchingPair {\n        int from;\n        int to;\n        int edge_id;\n\
    \    };\n\n    // General-graph shortest augmenting path phase solver.\n    struct\
    \ MicaliVaziraniSolver {\n        GeneralMatching& graph;\n        int n;\n  \
    \      int matching_size;\n        int delta;\n        int visit_token;\n    \
    \    int even_time_token;\n        MutablePartition base;\n        MutablePartition\
    \ delayed_base;\n        EdgeBucketQueue queue;\n        std::vector<MatchingLabel>\
    \ label;\n        std::vector<MatchingLabel> h_label;\n        std::vector<int>\
    \ parent;\n        std::vector<int> parent_edge;\n        std::vector<int> source_bridge;\n\
    \        std::vector<int> target_bridge;\n        std::vector<int> bridge_edge;\n\
    \        std::vector<int> lcp;\n        std::vector<int> path_mark_1;\n      \
    \  std::vector<int> path_mark_2;\n        std::vector<int> restore_vertex;\n \
    \       std::vector<int> restore_value;\n        std::vector<int> rep;\n     \
    \   std::vector<int> h_mate;\n        std::vector<char> is_h_edge;\n        std::vector<std::vector<int>>\
    \ contracted_into;\n        std::vector<int> h_parent_edge;\n        std::vector<int>\
    \ h_even_time;\n        std::vector<int> h_bridge_edge;\n        std::vector<int>\
    \ h_bridge_dir;\n\n        explicit MicaliVaziraniSolver(GeneralMatching& graph_)\n\
    \            : graph(graph_),\n              n(graph_._n),\n              matching_size(0),\n\
    \              delta(0),\n              visit_token(0),\n              even_time_token(0),\n\
    \              base(n),\n              delayed_base(n),\n              label(n,\
    \ unlabeled),\n              h_label(n, unlabeled),\n              parent(n, -1),\n\
    \              parent_edge(n, -1),\n              source_bridge(n, -1),\n    \
    \          target_bridge(n, -1),\n              bridge_edge(n, -1),\n        \
    \      lcp(n, 0),\n              path_mark_1(n, 0),\n              path_mark_2(n,\
    \ 0),\n              rep(n, -1),\n              h_mate(n, -1),\n             \
    \ is_h_edge(graph_._edges.size(), false),\n              contracted_into(n),\n\
    \              h_parent_edge(n, -1),\n              h_even_time(n, 0),\n     \
    \         h_bridge_edge(n, -1),\n              h_bridge_dir(n, 0) {}\n\n     \
    \   bool active(int edge_id) const {\n            return graph._edges[edge_id].alive;\n\
    \        }\n\n        int other(int edge_id, int v) const {\n            return\
    \ graph._edges[edge_id].other(v);\n        }\n\n        int edge_weight(int edge_id)\
    \ const {\n            return graph.is_matched_edge(edge_id) ? 2 : 0;\n      \
    \  }\n\n        void set_match(int edge_id) {\n            const auto& e = graph._edges[edge_id];\n\
    \            graph._mate[e.from] = e.to;\n            graph._mate[e.to] = e.from;\n\
    \            graph._mate_edge[e.from] = edge_id;\n            graph._mate_edge[e.to]\
    \ = edge_id;\n        }\n\n        void initialize_greedy_matching() {\n     \
    \       graph._mate.assign(n, -1);\n            graph._mate_edge.assign(n, -1);\n\
    \            matching_size = 0;\n            for (const auto& e : graph._edges)\
    \ {\n                if (!e.alive) continue;\n                if (graph._mate[e.from]\
    \ != -1 || graph._mate[e.to] != -1) continue;\n                set_match(e.id);\n\
    \                matching_size++;\n            }\n        }\n\n        void scan_edge(int\
    \ edge_id, int from) {\n            if (!active(edge_id)) return;\n          \
    \  int to = other(edge_id, from);\n            if (to == from || graph._mate[to]\
    \ == from || label[base(to)] == odd_label) return;\n            if (label[to]\
    \ == unlabeled) {\n                queue.insert(edge_id, lcp[from] + 2);\n   \
    \         } else {\n                queue.insert(edge_id, (lcp[from] + lcp[to])\
    \ / 2 + 1);\n            }\n        }\n\n        void shrink_path(int blossom_base,\
    \ int x, int y, int edge_id,\n                         std::vector<std::pair<int,\
    \ int>>& delayed_unions) {\n            int v = base(x);\n            while (v\
    \ != blossom_base) {\n                base.unite(v, blossom_base);\n         \
    \       delayed_unions.push_back({v, blossom_base});\n\n                v = graph._mate[v];\n\
    \                assert(v != -1);\n                base.unite(v, blossom_base);\n\
    \                delayed_unions.push_back({v, blossom_base});\n              \
    \  base.make_rep(blossom_base);\n\n                source_bridge[v] = x;\n   \
    \             target_bridge[v] = y;\n                bridge_edge[v] = edge_id;\n\
    \                restore_vertex.push_back(v);\n                restore_value.push_back(lcp[v]);\n\
    \                lcp[v] = lcp[x] + lcp[y] - lcp[graph._mate[v]] + 2;\n\n     \
    \           for (int id : graph._adj[v]) scan_edge(id, v);\n                assert(parent[v]\
    \ != -1);\n                v = base(parent[v]);\n            }\n            delayed_unions.push_back({blossom_base,\
    \ blossom_base});\n        }\n\n        void build_phase_graph() {\n         \
    \   std::fill(h_mate.begin(), h_mate.end(), -1);\n            std::fill(is_h_edge.begin(),\
    \ is_h_edge.end(), false);\n            for (auto& vertices : contracted_into)\
    \ vertices.clear();\n\n            for (int v = 0; v < n; v++) contracted_into[delayed_base(v)].push_back(v);\n\
    \n            for (const auto& e : graph._edges) {\n                if (!e.alive)\
    \ continue;\n                int u = e.from;\n                int v = e.to;\n\
    \                int uh = delayed_base(u);\n                int vh = delayed_base(v);\n\
    \                if (uh == vh) continue;\n                if (label[uh] == odd_label\
    \ && label[vh] == odd_label) continue;\n\n                int w = edge_weight(e.id);\n\
    \                bool even_odd =\n                    (label[uh] == even_label\
    \ && label[vh] == odd_label && lcp[v] == lcp[u] + 1 - w) ||\n                \
    \    (label[vh] == even_label && label[uh] == odd_label && lcp[u] == lcp[v] +\
    \ 1 - w);\n                bool unlabeled_unlabeled = label[uh] == unlabeled &&\
    \ label[vh] == unlabeled && w == 2;\n                bool even_unlabeled =\n \
    \                   (label[uh] == even_label && label[vh] == unlabeled && lcp[u]\
    \ == delta - 2) ||\n                    (label[vh] == even_label && label[uh]\
    \ == unlabeled && lcp[v] == delta - 2);\n                bool even_even = label[uh]\
    \ == even_label && label[vh] == even_label;\n                bool tight_even_even\
    \ = even_even && lcp[u] + lcp[v] == 2 * delta + w - 2;\n\n                if (even_odd\
    \ || unlabeled_unlabeled || even_unlabeled || tight_even_even) {\n           \
    \         is_h_edge[e.id] = true;\n                    if (w == 2) {\n       \
    \                 h_mate[uh] = vh;\n                        h_mate[vh] = uh;\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  bool phase_one() {\n            delta = 0;\n            base.reset(n);\n  \
    \          delayed_base.reset(n);\n            queue.reset(n);\n            std::fill(label.begin(),\
    \ label.end(), unlabeled);\n            std::fill(parent.begin(), parent.end(),\
    \ -1);\n            std::fill(parent_edge.begin(), parent_edge.end(), -1);\n \
    \           std::fill(source_bridge.begin(), source_bridge.end(), -1);\n     \
    \       std::fill(target_bridge.begin(), target_bridge.end(), -1);\n         \
    \   std::fill(bridge_edge.begin(), bridge_edge.end(), -1);\n            std::fill(lcp.begin(),\
    \ lcp.end(), 0);\n\n            for (int v = 0; v < n; v++) {\n              \
    \  if (graph._mate[v] == -1) label[v] = even_label;\n            }\n         \
    \   for (int v = 0; v < n; v++) {\n                if (label[v] != even_label)\
    \ continue;\n                for (int id : graph._adj[v]) scan_edge(id, v);\n\
    \            }\n\n            std::vector<std::pair<int, int>> delayed_unions;\n\
    \            while (delta <= n + 1) {\n                restore_vertex.clear();\n\
    \                restore_value.clear();\n\n                while (true) {\n  \
    \                  int edge_id = queue.pop(delta);\n                    if (edge_id\
    \ == -1) break;\n                    if (!active(edge_id)) continue;\n\n     \
    \               int x = graph._edges[edge_id].from;\n                    int y\
    \ = graph._edges[edge_id].to;\n                    if (label[base(x)] != even_label)\
    \ std::swap(x, y);\n                    if (label[base(x)] != even_label) continue;\n\
    \                    if (graph._mate[x] == y || base(x) == base(y) || label[base(y)]\
    \ == odd_label) continue;\n\n                    if (label[base(y)] == unlabeled)\
    \ {\n                        int z = graph._mate[y];\n                       \
    \ assert(z != -1);\n                        lcp[y] = lcp[x] + 1;\n           \
    \             lcp[z] = lcp[x] + 2;\n                        parent[y] = x;\n \
    \                       parent_edge[y] = edge_id;\n                        parent[z]\
    \ = y;\n                        parent_edge[z] = graph._mate_edge[z];\n      \
    \                  label[y] = odd_label;\n                        label[z] = even_label;\n\
    \                        for (int id : graph._adj[z]) scan_edge(id, z);\n    \
    \                    continue;\n                    }\n\n                    if\
    \ (label[base(y)] != even_label || lcp[x] + lcp[y] != 2 * delta - 2) continue;\n\
    \n                    ++visit_token;\n                    int hx = base(x);\n\
    \                    int hy = base(y);\n                    path_mark_1[hx] =\
    \ visit_token;\n                    path_mark_2[hy] = visit_token;\n         \
    \           while (path_mark_1[hy] != visit_token && path_mark_2[hx] != visit_token\
    \ &&\n                           (graph._mate[hx] != -1 || graph._mate[hy] !=\
    \ -1)) {\n                        if (graph._mate[hx] != -1) {\n             \
    \               assert(parent[graph._mate[hx]] != -1);\n                     \
    \       hx = base(parent[graph._mate[hx]]);\n                            path_mark_1[hx]\
    \ = visit_token;\n                        }\n                        if (graph._mate[hy]\
    \ != -1) {\n                            assert(parent[graph._mate[hy]] != -1);\n\
    \                            hy = base(parent[graph._mate[hy]]);\n           \
    \                 path_mark_2[hy] = visit_token;\n                        }\n\
    \                    }\n\n                    if (path_mark_1[hy] == visit_token\
    \ || path_mark_2[hx] == visit_token) {\n                        int blossom_base\
    \ = path_mark_1[hy] == visit_token ? hy : hx;\n                        shrink_path(blossom_base,\
    \ x, y, edge_id, delayed_unions);\n                        shrink_path(blossom_base,\
    \ y, x, edge_id, delayed_unions);\n                    } else {\n            \
    \            for (int i = int(restore_vertex.size()) - 1; i >= 0; i--) {\n   \
    \                         lcp[restore_vertex[i]] = restore_value[i];\n       \
    \                 }\n                        build_phase_graph();\n          \
    \              return true;\n                    }\n                }\n\n    \
    \            for (auto [a, b] : delayed_unions) {\n                    if (a ==\
    \ b) {\n                        delayed_base.make_rep(a);\n                  \
    \  } else {\n                        delayed_base.unite(a, b);\n             \
    \       }\n                }\n                delayed_unions.clear();\n      \
    \          delta++;\n            }\n            return false;\n        }\n\n \
    \       int next_h_vertex_through_edge(int edge_id, int current_h) const {\n \
    \           const auto& e = graph._edges[edge_id];\n            return rep[rep[e.from]\
    \ == current_h ? e.to : e.from];\n        }\n\n        int find_path_in_h(int\
    \ h_vertex) {\n            for (int v : contracted_into[h_vertex]) {\n       \
    \         for (int edge_id : graph._adj[v]) {\n                    if (!is_h_edge[edge_id])\
    \ continue;\n                    int uh = rep[other(edge_id, v)];\n          \
    \          if (h_mate[h_vertex] == uh) continue;\n\n                    if (h_label[uh]\
    \ == unlabeled) {\n                        int mate_uh = h_mate[uh];\n       \
    \                 h_label[uh] = odd_label;\n                        h_parent_edge[uh]\
    \ = edge_id;\n                        if (mate_uh == -1) return uh;\n\n      \
    \                  h_label[mate_uh] = even_label;\n                        h_even_time[mate_uh]\
    \ = even_time_token++;\n                        int found = find_path_in_h(mate_uh);\n\
    \                        if (found != -1) return found;\n                    }\
    \ else {\n                        int bh = delayed_base(h_vertex);\n         \
    \               int zh = delayed_base(uh);\n                        if (h_even_time[bh]\
    \ >= h_even_time[zh]) continue;\n\n                        std::vector<int> blossom_path;\n\
    \                        std::vector<int> blossom_vertices;\n                \
    \        while (zh != bh) {\n                            blossom_vertices.push_back(zh);\n\
    \                            zh = h_mate[zh];\n                            assert(zh\
    \ != -1);\n                            blossom_vertices.push_back(zh);\n     \
    \                       blossom_path.push_back(zh);\n                        \
    \    assert(h_parent_edge[zh] != -1);\n                            zh = delayed_base(next_h_vertex_through_edge(h_parent_edge[zh],\
    \ zh));\n                        }\n\n                        for (int x : blossom_vertices)\
    \ delayed_base.unite(x, bh);\n                        delayed_base.make_rep(bh);\n\
    \n                        std::reverse(blossom_path.begin(), blossom_path.end());\n\
    \                        for (int x : blossom_path) {\n                      \
    \      h_bridge_edge[x] = edge_id;\n                            h_bridge_dir[x]\
    \ = graph._edges[edge_id].to == v ? 1 : -1;\n                        }\n     \
    \                   for (int x : blossom_path) {\n                           \
    \ int found = find_path_in_h(x);\n                            if (found != -1)\
    \ return found;\n                        }\n                    }\n          \
    \      }\n            }\n            return -1;\n        }\n\n        void collect_path_in_h(std::vector<int>&\
    \ path, int from_h, int to_h) {\n            if (from_h == to_h) return;\n   \
    \         if (h_label[from_h] == even_label) {\n                int mate_from\
    \ = h_mate[from_h];\n                assert(mate_from != -1);\n              \
    \  int edge_id = h_parent_edge[mate_from];\n                assert(edge_id !=\
    \ -1);\n                path.push_back(edge_id);\n                collect_path_in_h(path,\
    \ next_h_vertex_through_edge(edge_id, mate_from), to_h);\n            } else {\n\
    \                int edge_id = h_bridge_edge[from_h];\n                assert(edge_id\
    \ != -1);\n                const auto& e = graph._edges[edge_id];\n          \
    \      int first = rep[h_bridge_dir[from_h] == 1 ? e.from : e.to];\n         \
    \       int second = rep[h_bridge_dir[from_h] == 1 ? e.to : e.from];\n       \
    \         collect_path_in_h(path, first, rep[h_mate[from_h]]);\n             \
    \   path.push_back(edge_id);\n                collect_path_in_h(path, second,\
    \ to_h);\n            }\n        }\n\n        void add_new_pair(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to, int edge_id) const {\n            const auto& e = graph._edges[edge_id];\n\
    \            assert(e.alive);\n            assert((e.from == from && e.to == to)\
    \ || (e.from == to && e.to == from));\n            pairs.push_back(NewMatchingPair{from,\
    \ to, edge_id});\n        }\n\n        void collect_path_in_graph(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to) {\n            if (from == to) return;\n          \
    \  if (label[from] == even_label) {\n                int mate_from = graph._mate[from];\n\
    \                assert(mate_from != -1);\n                int parent_of_mate\
    \ = parent[mate_from];\n                int edge_id = parent_edge[mate_from];\n\
    \                assert(parent_of_mate != -1 && edge_id != -1);\n            \
    \    add_new_pair(pairs, mate_from, parent_of_mate, edge_id);\n              \
    \  collect_path_in_graph(pairs, parent_of_mate, to);\n            } else {\n \
    \               assert(source_bridge[from] != -1 && target_bridge[from] != -1\
    \ && bridge_edge[from] != -1);\n                collect_path_in_graph(pairs, source_bridge[from],\
    \ graph._mate[from]);\n                add_new_pair(pairs, source_bridge[from],\
    \ target_bridge[from], bridge_edge[from]);\n                collect_path_in_graph(pairs,\
    \ target_bridge[from], to);\n            }\n        }\n\n        void augment_path(const\
    \ std::vector<int>& h_path) {\n            std::vector<NewMatchingPair> pairs;\n\
    \            for (int edge_id : h_path) {\n                const auto& e = graph._edges[edge_id];\n\
    \                add_new_pair(pairs, e.from, e.to, edge_id);\n               \
    \ collect_path_in_graph(pairs, e.from, rep[e.from]);\n                collect_path_in_graph(pairs,\
    \ e.to, rep[e.to]);\n            }\n\n            for (const auto& p : pairs)\
    \ {\n                if (graph._mate[p.from] != -1) {\n                    int\
    \ old = graph._mate[p.from];\n                    graph._mate[old] = -1;\n   \
    \                 graph._mate_edge[old] = -1;\n                }\n           \
    \     if (graph._mate[p.to] != -1) {\n                    int old = graph._mate[p.to];\n\
    \                    graph._mate[old] = -1;\n                    graph._mate_edge[old]\
    \ = -1;\n                }\n                graph._mate[p.from] = graph._mate[p.to]\
    \ = -1;\n                graph._mate_edge[p.from] = graph._mate_edge[p.to] = -1;\n\
    \            }\n            for (const auto& p : pairs) {\n                assert(graph._mate[p.from]\
    \ == -1 && graph._mate[p.to] == -1);\n                graph._mate[p.from] = p.to;\n\
    \                graph._mate[p.to] = p.from;\n                graph._mate_edge[p.from]\
    \ = p.edge_id;\n                graph._mate_edge[p.to] = p.edge_id;\n        \
    \    }\n            matching_size++;\n        }\n\n        void phase_two() {\n\
    \            std::fill(h_label.begin(), h_label.end(), unlabeled);\n         \
    \   std::fill(h_parent_edge.begin(), h_parent_edge.end(), -1);\n            std::fill(h_bridge_edge.begin(),\
    \ h_bridge_edge.end(), -1);\n            std::fill(h_bridge_dir.begin(), h_bridge_dir.end(),\
    \ 0);\n            for (int v = 0; v < n; v++) rep[v] = delayed_base(v);\n\n \
    \           std::vector<std::vector<int>> paths;\n            for (int h_vertex\
    \ = 0; h_vertex < n; h_vertex++) {\n                if (rep[h_vertex] != h_vertex)\
    \ continue;\n                if (h_label[h_vertex] != unlabeled || h_mate[h_vertex]\
    \ != -1) continue;\n\n                h_label[h_vertex] = even_label;\n      \
    \          h_even_time[h_vertex] = even_time_token++;\n                int free_h\
    \ = find_path_in_h(h_vertex);\n                if (free_h == -1) continue;\n\n\
    \                std::vector<int> path;\n                int edge_id = h_parent_edge[free_h];\n\
    \                assert(edge_id != -1);\n                path.push_back(edge_id);\n\
    \                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, free_h),\
    \ h_vertex);\n                paths.push_back(path);\n            }\n\n      \
    \      assert(!paths.empty());\n            for (const auto& path : paths) augment_path(path);\n\
    \            for (auto& vertices : contracted_into) vertices.clear();\n      \
    \  }\n\n        int solve() {\n            initialize_greedy_matching();\n   \
    \         while (phase_one()) phase_two();\n            return matching_size;\n\
    \        }\n    };\n\n   public:\n    GeneralMatching() : GeneralMatching(0) {}\n\
    \n    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n,\
    \ -1), _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int from, int to) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        MicaliVaziraniSolver\
    \ solver(*this);\n        int result = solver.solve();\n\n        _calculated\
    \ = true;\n        return result;\n    }\n\n    int matching_size() {\n      \
    \  ensure_matching();\n        int result = 0;\n        for (int v = 0; v < _n;\
    \ v++) {\n            if (v < _mate[v]) result++;\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n        return\
    \ _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (v < _mate[v]) result.push_back(Pair{v,\
    \ _mate[v], _mate_edge[v]});\n        }\n        return result;\n    }\n\n   \
    \ std::optional<std::vector<int>> minimum_edge_cover() {\n        ensure_matching();\n\
    \n        std::vector<int> result;\n        std::vector<char> covered(_n, false),\
    \ used_edge(_edges.size(), false);\n\n        auto use_edge = [&](int id) {\n\
    \            if (used_edge[id]) return;\n            used_edge[id] = true;\n \
    \           result.push_back(id);\n            covered[_edges[id].from] = true;\n\
    \            covered[_edges[id].to] = true;\n        };\n\n        for (int v\
    \ = 0; v < _n; v++) {\n            if (v < _mate[v]) use_edge(_mate_edge[v]);\n\
    \        }\n\n        for (int v = 0; v < _n; v++) {\n            if (covered[v])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[v])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct GeneralMatchingGraph {\n    GeneralMatching\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralMatchingGraph make_general_matching(const Graph<T>& g) {\n    GeneralMatchingGraph\
    \ result;\n    result.matching = GeneralMatching(g.size());\n    for (const auto&\
    \ e : g.edges()) {\n        int id = result.matching.add_edge(e.from, e.to);\n\
    \        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id\
    \ + 1);\n        result.original_edge_id[id] = e.id;\n    }\n    return result;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 8 \"verify/graph/library_checker_general_matching.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n\
    \    int N, M;\n    cin >> N >> M;\n    m1une::graph::GeneralMatching gm(N);\n\
    \    while (M--) {\n        int u, v;\n        cin >> u >> v;\n        gm.add_edge(u,\
    \ v);\n    }\n    cout << gm.max_matching() << '\\n';\n    for (auto p : gm.matching())\
    \ {\n        cout << p.from << ' ' << p.to << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\n\
    #include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../graph/graph.hpp\"\
    \n#include \"../../graph/general_matching.hpp\"\n\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n\n    int N, M;\n    cin >> N >> M;\n    m1une::graph::GeneralMatching\
    \ gm(N);\n    while (M--) {\n        int u, v;\n        cin >> u >> v;\n     \
    \   gm.add_edge(u, v);\n    }\n    cout << gm.max_matching() << '\\n';\n    for\
    \ (auto p : gm.matching()) {\n        cout << p.from << ' ' << p.to << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/general_matching.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/library_checker_general_matching.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/library_checker_general_matching.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/library_checker_general_matching.test.cpp
- /verify/verify/graph/library_checker_general_matching.test.cpp.html
title: verify/graph/library_checker_general_matching.test.cpp
---
