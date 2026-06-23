---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: flow/flow.hpp
    title: Flow
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/flow/flow_algorithms.test.cpp
    title: verify/flow/flow_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"flow/gomory_hu.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct GomoryHu {\n    struct\
    \ Edge {\n        int u;\n        int v;\n        Cap cap;\n    };\n\n   private:\n\
    \    struct FlowEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \        Cap initial_cap;\n    };\n\n    int _n;\n    bool _built = false;\n \
    \   std::vector<Edge> _edges;\n    std::vector<Edge> _tree_edges;\n    std::vector<int>\
    \ _parent;\n    std::vector<Cap> _cut_value;\n    std::vector<std::vector<std::pair<int,\
    \ Cap>>> _tree;\n    std::vector<std::vector<int>> _up;\n    std::vector<std::vector<Cap>>\
    \ _minimum;\n    std::vector<int> _depth;\n\n    std::vector<std::vector<FlowEdge>>\
    \ _graph;\n    std::vector<Cap> _excess;\n    std::vector<int> _height;\n    std::vector<int>\
    \ _height_count;\n    std::vector<int> _current;\n    std::vector<bool> _active;\n\
    \    std::vector<std::vector<int>> _buckets;\n    std::vector<int> _queue;\n \
    \   int _highest;\n    long long _work;\n    long long _work_limit;\n\n    void\
    \ add_flow_edge(int u, int v, Cap cap) {\n        if (u == v || cap == Cap(0))\
    \ return;\n        int ui = int(_graph[u].size());\n        int vi = int(_graph[v].size());\n\
    \        _graph[u].push_back(FlowEdge{v, vi, cap, cap});\n        _graph[v].push_back(FlowEdge{u,\
    \ ui, cap, cap});\n    }\n\n    void reset_flow() {\n        for (auto& edges\
    \ : _graph) {\n            for (auto& edge : edges) edge.cap = edge.initial_cap;\n\
    \        }\n    }\n\n    void activate(int v, int s, int t) {\n        int dead\
    \ = 2 * _n;\n        if (v == s || v == t || _active[v] || _excess[v] == Cap(0)\
    \ || _height[v] >= dead) return;\n        _active[v] = true;\n        _buckets[_height[v]].push_back(v);\n\
    \        _highest = std::max(_highest, _height[v]);\n    }\n\n    void rebuild_buckets(int\
    \ s, int t) {\n        for (auto& bucket : _buckets) bucket.clear();\n       \
    \ std::fill(_active.begin(), _active.end(), false);\n        _highest = -1;\n\
    \        for (int v = 0; v < _n; v++) activate(v, s, t);\n    }\n\n    void global_relabel(int\
    \ s, int t) {\n        int dead = 2 * _n;\n        int unreachable = _n + 1;\n\
    \        std::fill(_height.begin(), _height.end(), unreachable);\n        std::fill(_height_count.begin(),\
    \ _height_count.end(), 0);\n        std::fill(_current.begin(), _current.end(),\
    \ 0);\n\n        int head = 0;\n        int tail = 0;\n        _height[t] = 0;\n\
    \        _height[s] = _n;\n        _queue[tail++] = t;\n        while (head <\
    \ tail) {\n            int v = _queue[head++];\n            for (const auto& edge\
    \ : _graph[v]) {\n                const FlowEdge& reverse = _graph[edge.to][edge.rev];\n\
    \                if (reverse.cap == Cap(0) || _height[edge.to] != unreachable)\
    \ continue;\n                _height[edge.to] = _height[v] + 1;\n            \
    \    _queue[tail++] = edge.to;\n            }\n        }\n        for (int v =\
    \ 0; v < _n; v++) {\n            _height[v] = std::min(_height[v], dead);\n  \
    \          _height_count[_height[v]]++;\n        }\n        rebuild_buckets(s,\
    \ t);\n        _work = 0;\n    }\n\n    void push(int v, FlowEdge& edge, int s,\
    \ int t) {\n        if (edge.cap == Cap(0) || _height[v] != _height[edge.to] +\
    \ 1) return;\n        Cap sent = std::min(_excess[v], edge.cap);\n        if (sent\
    \ == Cap(0)) return;\n        bool was_zero = _excess[edge.to] == Cap(0);\n  \
    \      edge.cap -= sent;\n        _graph[edge.to][edge.rev].cap += sent;\n   \
    \     _excess[v] -= sent;\n        _excess[edge.to] += sent;\n        if (was_zero)\
    \ activate(edge.to, s, t);\n    }\n\n    void gap(int height, int s, int t) {\n\
    \        int unreachable = _n + 1;\n        for (int v = 0; v < _n; v++) {\n \
    \           if (v == s || v == t || _height[v] <= height || _height[v] >= _n)\
    \ continue;\n            _height_count[_height[v]]--;\n            _height[v]\
    \ = unreachable;\n            _height_count[_height[v]]++;\n            _current[v]\
    \ = 0;\n        }\n        rebuild_buckets(s, t);\n    }\n\n    bool relabel(int\
    \ v, int s, int t) {\n        int dead = 2 * _n;\n        int old_height = _height[v];\n\
    \        int new_height = dead;\n        _work += int(_graph[v].size());\n   \
    \     for (const auto& edge : _graph[v]) {\n            if (edge.cap != Cap(0))\
    \ new_height = std::min(new_height, _height[edge.to] + 1);\n        }\n      \
    \  _height_count[old_height]--;\n        _height[v] = std::min(new_height, dead);\n\
    \        _height_count[_height[v]]++;\n        _current[v] = 0;\n        if (old_height\
    \ < _n && _height_count[old_height] == 0) {\n            gap(old_height, s, t);\n\
    \            return true;\n        }\n        return false;\n    }\n\n    void\
    \ discharge(int v, int s, int t) {\n        while (_excess[v] != Cap(0) && _height[v]\
    \ < 2 * _n) {\n            if (_current[v] == int(_graph[v].size())) {\n     \
    \           if (relabel(v, s, t)) return;\n                continue;\n       \
    \     }\n            FlowEdge& edge = _graph[v][_current[v]];\n            _work++;\n\
    \            if (edge.cap != Cap(0) && _height[v] == _height[edge.to] + 1) {\n\
    \                push(v, edge, s, t);\n            } else {\n                _current[v]++;\n\
    \            }\n        }\n        activate(v, s, t);\n    }\n\n    Cap max_flow(int\
    \ s, int t) {\n        reset_flow();\n        std::fill(_excess.begin(), _excess.end(),\
    \ Cap(0));\n        for (auto& edge : _graph[s]) {\n            Cap sent = edge.cap;\n\
    \            if (sent == Cap(0)) continue;\n            edge.cap = Cap(0);\n \
    \           _graph[edge.to][edge.rev].cap += sent;\n            _excess[edge.to]\
    \ += sent;\n        }\n        global_relabel(s, t);\n\n        while (_highest\
    \ >= 0) {\n            if (_buckets[_highest].empty()) {\n                _highest--;\n\
    \                continue;\n            }\n            int v = _buckets[_highest].back();\n\
    \            _buckets[_highest].pop_back();\n            if (!_active[v] || _height[v]\
    \ != _highest) continue;\n            _active[v] = false;\n            discharge(v,\
    \ s, t);\n            if (_work >= _work_limit) global_relabel(s, t);\n      \
    \  }\n        return _excess[t];\n    }\n\n    std::vector<bool> source_side(int\
    \ s) {\n        std::vector<bool> visited(_n, false);\n        int head = 0;\n\
    \        int tail = 0;\n        visited[s] = true;\n        _queue[tail++] = s;\n\
    \        while (head < tail) {\n            int v = _queue[head++];\n        \
    \    for (const auto& edge : _graph[v]) {\n                if (edge.cap == Cap(0)\
    \ || visited[edge.to]) continue;\n                visited[edge.to] = true;\n \
    \               _queue[tail++] = edge.to;\n            }\n        }\n        return\
    \ visited;\n    }\n\n    void build_query_table() {\n        int log = 1;\n  \
    \      while ((1LL << log) <= std::max(1, _n)) log++;\n        const Cap infinity\
    \ = std::numeric_limits<Cap>::max();\n        _up.assign(log, std::vector<int>(_n,\
    \ 0));\n        _minimum.assign(log, std::vector<Cap>(_n, infinity));\n      \
    \  _depth.assign(_n, 0);\n        if (_n == 0) return;\n\n        std::vector<int>\
    \ order;\n        order.reserve(_n);\n        order.push_back(0);\n        for\
    \ (int i = 0; i < int(order.size()); i++) {\n            int v = order[i];\n \
    \           for (auto [to, cap] : _tree[v]) {\n                if (to == _up[0][v]\
    \ && v != 0) continue;\n                _up[0][to] = v;\n                _minimum[0][to]\
    \ = cap;\n                _depth[to] = _depth[v] + 1;\n                order.push_back(to);\n\
    \            }\n        }\n        for (int k = 1; k < log; k++) {\n         \
    \   for (int v = 0; v < _n; v++) {\n                int middle = _up[k - 1][v];\n\
    \                _up[k][v] = _up[k - 1][middle];\n                _minimum[k][v]\
    \ = std::min(_minimum[k - 1][v], _minimum[k - 1][middle]);\n            }\n  \
    \      }\n    }\n\n   public:\n    GomoryHu() : GomoryHu(0) {}\n\n    explicit\
    \ GomoryHu(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int u, int v, Cap cap)\
    \ {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n  \
    \      assert(Cap(0) <= cap);\n        _built = false;\n        int id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, cap});\n        return id;\n    }\n\n   \
    \ void build() {\n        std::vector<Edge> flow_edges;\n        flow_edges.reserve(_edges.size());\n\
    \        for (auto edge : _edges) {\n            if (edge.u == edge.v || edge.cap\
    \ == Cap(0)) continue;\n            if (edge.u > edge.v) std::swap(edge.u, edge.v);\n\
    \            flow_edges.push_back(edge);\n        }\n        std::sort(flow_edges.begin(),\
    \ flow_edges.end(), [](const Edge& lhs, const Edge& rhs) {\n            return\
    \ std::pair<int, int>(lhs.u, lhs.v) < std::pair<int, int>(rhs.u, rhs.v);\n   \
    \     });\n        int unique_edges = 0;\n        for (const auto& edge : flow_edges)\
    \ {\n            if (unique_edges > 0 && flow_edges[unique_edges - 1].u == edge.u\
    \ &&\n                flow_edges[unique_edges - 1].v == edge.v) {\n          \
    \      flow_edges[unique_edges - 1].cap += edge.cap;\n            } else {\n \
    \               flow_edges[unique_edges++] = edge;\n            }\n        }\n\
    \        flow_edges.resize(unique_edges);\n\n        _graph.assign(_n, {});\n\
    \        std::vector<int> degree(_n, 0);\n        for (const auto& edge : flow_edges)\
    \ {\n            degree[edge.u]++;\n            degree[edge.v]++;\n        }\n\
    \        for (int v = 0; v < _n; v++) _graph[v].reserve(degree[v]);\n        for\
    \ (const auto& edge : flow_edges) add_flow_edge(edge.u, edge.v, edge.cap);\n \
    \       _excess.resize(_n);\n        _height.resize(_n);\n        _height_count.resize(2\
    \ * _n + 1);\n        _current.resize(_n);\n        _active.resize(_n);\n    \
    \    _buckets.resize(2 * _n + 1);\n        _queue.resize(_n);\n        long long\
    \ arc_count = 0;\n        for (const auto& edges : _graph) arc_count += int(edges.size());\n\
    \        _work_limit = std::max(1LL, 4 * arc_count + _n);\n\n        _parent.assign(_n,\
    \ 0);\n        _cut_value.assign(_n, std::numeric_limits<Cap>::max());\n     \
    \   for (int s = 1; s < _n; s++) {\n            int t = _parent[s];\n        \
    \    Cap flow = max_flow(s, t);\n            std::vector<bool> cut = source_side(s);\n\
    \            for (int v = s + 1; v < _n; v++) {\n                if (_parent[v]\
    \ == t && cut[v]) _parent[v] = s;\n            }\n            if (cut[_parent[t]])\
    \ {\n                _parent[s] = _parent[t];\n                _parent[t] = s;\n\
    \                _cut_value[s] = _cut_value[t];\n                _cut_value[t]\
    \ = flow;\n            } else {\n                _cut_value[s] = flow;\n     \
    \       }\n        }\n\n        _tree.assign(_n, {});\n        _tree_edges.clear();\n\
    \        if (_n > 0) _tree_edges.reserve(_n - 1);\n        for (int v = 1; v <\
    \ _n; v++) {\n            int p = _parent[v];\n            Cap cap = _cut_value[v];\n\
    \            _tree_edges.push_back(Edge{v, p, cap});\n            _tree[v].emplace_back(p,\
    \ cap);\n            _tree[p].emplace_back(v, cap);\n        }\n        build_query_table();\n\
    \        _built = true;\n    }\n\n    const std::vector<Edge>& tree_edges() const\
    \ {\n        assert(_built);\n        return _tree_edges;\n    }\n\n    const\
    \ std::vector<int>& parent() const {\n        assert(_built);\n        return\
    \ _parent;\n    }\n\n    const std::vector<Cap>& cut_values() const {\n      \
    \  assert(_built);\n        return _cut_value;\n    }\n\n    Cap min_cut(int u,\
    \ int v) const {\n        assert(_built);\n        assert(0 <= u && u < _n);\n\
    \        assert(0 <= v && v < _n);\n        assert(u != v);\n        Cap result\
    \ = std::numeric_limits<Cap>::max();\n        if (_depth[u] < _depth[v]) std::swap(u,\
    \ v);\n        int difference = _depth[u] - _depth[v];\n        for (int k = 0;\
    \ difference > 0; k++, difference >>= 1) {\n            if ((difference & 1) ==\
    \ 0) continue;\n            result = std::min(result, _minimum[k][u]);\n     \
    \       u = _up[k][u];\n        }\n        if (u == v) return result;\n      \
    \  for (int k = int(_up.size()) - 1; k >= 0; k--) {\n            if (_up[k][u]\
    \ == _up[k][v]) continue;\n            result = std::min(result, _minimum[k][u]);\n\
    \            result = std::min(result, _minimum[k][v]);\n            u = _up[k][u];\n\
    \            v = _up[k][v];\n        }\n        result = std::min(result, _minimum[0][u]);\n\
    \        result = std::min(result, _minimum[0][v]);\n        return result;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_GOMORY_HU_HPP\n#define M1UNE_FLOW_GOMORY_HU_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\n\
    struct GomoryHu {\n    struct Edge {\n        int u;\n        int v;\n       \
    \ Cap cap;\n    };\n\n   private:\n    struct FlowEdge {\n        int to;\n  \
    \      int rev;\n        Cap cap;\n        Cap initial_cap;\n    };\n\n    int\
    \ _n;\n    bool _built = false;\n    std::vector<Edge> _edges;\n    std::vector<Edge>\
    \ _tree_edges;\n    std::vector<int> _parent;\n    std::vector<Cap> _cut_value;\n\
    \    std::vector<std::vector<std::pair<int, Cap>>> _tree;\n    std::vector<std::vector<int>>\
    \ _up;\n    std::vector<std::vector<Cap>> _minimum;\n    std::vector<int> _depth;\n\
    \n    std::vector<std::vector<FlowEdge>> _graph;\n    std::vector<Cap> _excess;\n\
    \    std::vector<int> _height;\n    std::vector<int> _height_count;\n    std::vector<int>\
    \ _current;\n    std::vector<bool> _active;\n    std::vector<std::vector<int>>\
    \ _buckets;\n    std::vector<int> _queue;\n    int _highest;\n    long long _work;\n\
    \    long long _work_limit;\n\n    void add_flow_edge(int u, int v, Cap cap) {\n\
    \        if (u == v || cap == Cap(0)) return;\n        int ui = int(_graph[u].size());\n\
    \        int vi = int(_graph[v].size());\n        _graph[u].push_back(FlowEdge{v,\
    \ vi, cap, cap});\n        _graph[v].push_back(FlowEdge{u, ui, cap, cap});\n \
    \   }\n\n    void reset_flow() {\n        for (auto& edges : _graph) {\n     \
    \       for (auto& edge : edges) edge.cap = edge.initial_cap;\n        }\n   \
    \ }\n\n    void activate(int v, int s, int t) {\n        int dead = 2 * _n;\n\
    \        if (v == s || v == t || _active[v] || _excess[v] == Cap(0) || _height[v]\
    \ >= dead) return;\n        _active[v] = true;\n        _buckets[_height[v]].push_back(v);\n\
    \        _highest = std::max(_highest, _height[v]);\n    }\n\n    void rebuild_buckets(int\
    \ s, int t) {\n        for (auto& bucket : _buckets) bucket.clear();\n       \
    \ std::fill(_active.begin(), _active.end(), false);\n        _highest = -1;\n\
    \        for (int v = 0; v < _n; v++) activate(v, s, t);\n    }\n\n    void global_relabel(int\
    \ s, int t) {\n        int dead = 2 * _n;\n        int unreachable = _n + 1;\n\
    \        std::fill(_height.begin(), _height.end(), unreachable);\n        std::fill(_height_count.begin(),\
    \ _height_count.end(), 0);\n        std::fill(_current.begin(), _current.end(),\
    \ 0);\n\n        int head = 0;\n        int tail = 0;\n        _height[t] = 0;\n\
    \        _height[s] = _n;\n        _queue[tail++] = t;\n        while (head <\
    \ tail) {\n            int v = _queue[head++];\n            for (const auto& edge\
    \ : _graph[v]) {\n                const FlowEdge& reverse = _graph[edge.to][edge.rev];\n\
    \                if (reverse.cap == Cap(0) || _height[edge.to] != unreachable)\
    \ continue;\n                _height[edge.to] = _height[v] + 1;\n            \
    \    _queue[tail++] = edge.to;\n            }\n        }\n        for (int v =\
    \ 0; v < _n; v++) {\n            _height[v] = std::min(_height[v], dead);\n  \
    \          _height_count[_height[v]]++;\n        }\n        rebuild_buckets(s,\
    \ t);\n        _work = 0;\n    }\n\n    void push(int v, FlowEdge& edge, int s,\
    \ int t) {\n        if (edge.cap == Cap(0) || _height[v] != _height[edge.to] +\
    \ 1) return;\n        Cap sent = std::min(_excess[v], edge.cap);\n        if (sent\
    \ == Cap(0)) return;\n        bool was_zero = _excess[edge.to] == Cap(0);\n  \
    \      edge.cap -= sent;\n        _graph[edge.to][edge.rev].cap += sent;\n   \
    \     _excess[v] -= sent;\n        _excess[edge.to] += sent;\n        if (was_zero)\
    \ activate(edge.to, s, t);\n    }\n\n    void gap(int height, int s, int t) {\n\
    \        int unreachable = _n + 1;\n        for (int v = 0; v < _n; v++) {\n \
    \           if (v == s || v == t || _height[v] <= height || _height[v] >= _n)\
    \ continue;\n            _height_count[_height[v]]--;\n            _height[v]\
    \ = unreachable;\n            _height_count[_height[v]]++;\n            _current[v]\
    \ = 0;\n        }\n        rebuild_buckets(s, t);\n    }\n\n    bool relabel(int\
    \ v, int s, int t) {\n        int dead = 2 * _n;\n        int old_height = _height[v];\n\
    \        int new_height = dead;\n        _work += int(_graph[v].size());\n   \
    \     for (const auto& edge : _graph[v]) {\n            if (edge.cap != Cap(0))\
    \ new_height = std::min(new_height, _height[edge.to] + 1);\n        }\n      \
    \  _height_count[old_height]--;\n        _height[v] = std::min(new_height, dead);\n\
    \        _height_count[_height[v]]++;\n        _current[v] = 0;\n        if (old_height\
    \ < _n && _height_count[old_height] == 0) {\n            gap(old_height, s, t);\n\
    \            return true;\n        }\n        return false;\n    }\n\n    void\
    \ discharge(int v, int s, int t) {\n        while (_excess[v] != Cap(0) && _height[v]\
    \ < 2 * _n) {\n            if (_current[v] == int(_graph[v].size())) {\n     \
    \           if (relabel(v, s, t)) return;\n                continue;\n       \
    \     }\n            FlowEdge& edge = _graph[v][_current[v]];\n            _work++;\n\
    \            if (edge.cap != Cap(0) && _height[v] == _height[edge.to] + 1) {\n\
    \                push(v, edge, s, t);\n            } else {\n                _current[v]++;\n\
    \            }\n        }\n        activate(v, s, t);\n    }\n\n    Cap max_flow(int\
    \ s, int t) {\n        reset_flow();\n        std::fill(_excess.begin(), _excess.end(),\
    \ Cap(0));\n        for (auto& edge : _graph[s]) {\n            Cap sent = edge.cap;\n\
    \            if (sent == Cap(0)) continue;\n            edge.cap = Cap(0);\n \
    \           _graph[edge.to][edge.rev].cap += sent;\n            _excess[edge.to]\
    \ += sent;\n        }\n        global_relabel(s, t);\n\n        while (_highest\
    \ >= 0) {\n            if (_buckets[_highest].empty()) {\n                _highest--;\n\
    \                continue;\n            }\n            int v = _buckets[_highest].back();\n\
    \            _buckets[_highest].pop_back();\n            if (!_active[v] || _height[v]\
    \ != _highest) continue;\n            _active[v] = false;\n            discharge(v,\
    \ s, t);\n            if (_work >= _work_limit) global_relabel(s, t);\n      \
    \  }\n        return _excess[t];\n    }\n\n    std::vector<bool> source_side(int\
    \ s) {\n        std::vector<bool> visited(_n, false);\n        int head = 0;\n\
    \        int tail = 0;\n        visited[s] = true;\n        _queue[tail++] = s;\n\
    \        while (head < tail) {\n            int v = _queue[head++];\n        \
    \    for (const auto& edge : _graph[v]) {\n                if (edge.cap == Cap(0)\
    \ || visited[edge.to]) continue;\n                visited[edge.to] = true;\n \
    \               _queue[tail++] = edge.to;\n            }\n        }\n        return\
    \ visited;\n    }\n\n    void build_query_table() {\n        int log = 1;\n  \
    \      while ((1LL << log) <= std::max(1, _n)) log++;\n        const Cap infinity\
    \ = std::numeric_limits<Cap>::max();\n        _up.assign(log, std::vector<int>(_n,\
    \ 0));\n        _minimum.assign(log, std::vector<Cap>(_n, infinity));\n      \
    \  _depth.assign(_n, 0);\n        if (_n == 0) return;\n\n        std::vector<int>\
    \ order;\n        order.reserve(_n);\n        order.push_back(0);\n        for\
    \ (int i = 0; i < int(order.size()); i++) {\n            int v = order[i];\n \
    \           for (auto [to, cap] : _tree[v]) {\n                if (to == _up[0][v]\
    \ && v != 0) continue;\n                _up[0][to] = v;\n                _minimum[0][to]\
    \ = cap;\n                _depth[to] = _depth[v] + 1;\n                order.push_back(to);\n\
    \            }\n        }\n        for (int k = 1; k < log; k++) {\n         \
    \   for (int v = 0; v < _n; v++) {\n                int middle = _up[k - 1][v];\n\
    \                _up[k][v] = _up[k - 1][middle];\n                _minimum[k][v]\
    \ = std::min(_minimum[k - 1][v], _minimum[k - 1][middle]);\n            }\n  \
    \      }\n    }\n\n   public:\n    GomoryHu() : GomoryHu(0) {}\n\n    explicit\
    \ GomoryHu(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int u, int v, Cap cap)\
    \ {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n  \
    \      assert(Cap(0) <= cap);\n        _built = false;\n        int id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, cap});\n        return id;\n    }\n\n   \
    \ void build() {\n        std::vector<Edge> flow_edges;\n        flow_edges.reserve(_edges.size());\n\
    \        for (auto edge : _edges) {\n            if (edge.u == edge.v || edge.cap\
    \ == Cap(0)) continue;\n            if (edge.u > edge.v) std::swap(edge.u, edge.v);\n\
    \            flow_edges.push_back(edge);\n        }\n        std::sort(flow_edges.begin(),\
    \ flow_edges.end(), [](const Edge& lhs, const Edge& rhs) {\n            return\
    \ std::pair<int, int>(lhs.u, lhs.v) < std::pair<int, int>(rhs.u, rhs.v);\n   \
    \     });\n        int unique_edges = 0;\n        for (const auto& edge : flow_edges)\
    \ {\n            if (unique_edges > 0 && flow_edges[unique_edges - 1].u == edge.u\
    \ &&\n                flow_edges[unique_edges - 1].v == edge.v) {\n          \
    \      flow_edges[unique_edges - 1].cap += edge.cap;\n            } else {\n \
    \               flow_edges[unique_edges++] = edge;\n            }\n        }\n\
    \        flow_edges.resize(unique_edges);\n\n        _graph.assign(_n, {});\n\
    \        std::vector<int> degree(_n, 0);\n        for (const auto& edge : flow_edges)\
    \ {\n            degree[edge.u]++;\n            degree[edge.v]++;\n        }\n\
    \        for (int v = 0; v < _n; v++) _graph[v].reserve(degree[v]);\n        for\
    \ (const auto& edge : flow_edges) add_flow_edge(edge.u, edge.v, edge.cap);\n \
    \       _excess.resize(_n);\n        _height.resize(_n);\n        _height_count.resize(2\
    \ * _n + 1);\n        _current.resize(_n);\n        _active.resize(_n);\n    \
    \    _buckets.resize(2 * _n + 1);\n        _queue.resize(_n);\n        long long\
    \ arc_count = 0;\n        for (const auto& edges : _graph) arc_count += int(edges.size());\n\
    \        _work_limit = std::max(1LL, 4 * arc_count + _n);\n\n        _parent.assign(_n,\
    \ 0);\n        _cut_value.assign(_n, std::numeric_limits<Cap>::max());\n     \
    \   for (int s = 1; s < _n; s++) {\n            int t = _parent[s];\n        \
    \    Cap flow = max_flow(s, t);\n            std::vector<bool> cut = source_side(s);\n\
    \            for (int v = s + 1; v < _n; v++) {\n                if (_parent[v]\
    \ == t && cut[v]) _parent[v] = s;\n            }\n            if (cut[_parent[t]])\
    \ {\n                _parent[s] = _parent[t];\n                _parent[t] = s;\n\
    \                _cut_value[s] = _cut_value[t];\n                _cut_value[t]\
    \ = flow;\n            } else {\n                _cut_value[s] = flow;\n     \
    \       }\n        }\n\n        _tree.assign(_n, {});\n        _tree_edges.clear();\n\
    \        if (_n > 0) _tree_edges.reserve(_n - 1);\n        for (int v = 1; v <\
    \ _n; v++) {\n            int p = _parent[v];\n            Cap cap = _cut_value[v];\n\
    \            _tree_edges.push_back(Edge{v, p, cap});\n            _tree[v].emplace_back(p,\
    \ cap);\n            _tree[p].emplace_back(v, cap);\n        }\n        build_query_table();\n\
    \        _built = true;\n    }\n\n    const std::vector<Edge>& tree_edges() const\
    \ {\n        assert(_built);\n        return _tree_edges;\n    }\n\n    const\
    \ std::vector<int>& parent() const {\n        assert(_built);\n        return\
    \ _parent;\n    }\n\n    const std::vector<Cap>& cut_values() const {\n      \
    \  assert(_built);\n        return _cut_value;\n    }\n\n    Cap min_cut(int u,\
    \ int v) const {\n        assert(_built);\n        assert(0 <= u && u < _n);\n\
    \        assert(0 <= v && v < _n);\n        assert(u != v);\n        Cap result\
    \ = std::numeric_limits<Cap>::max();\n        if (_depth[u] < _depth[v]) std::swap(u,\
    \ v);\n        int difference = _depth[u] - _depth[v];\n        for (int k = 0;\
    \ difference > 0; k++, difference >>= 1) {\n            if ((difference & 1) ==\
    \ 0) continue;\n            result = std::min(result, _minimum[k][u]);\n     \
    \       u = _up[k][u];\n        }\n        if (u == v) return result;\n      \
    \  for (int k = int(_up.size()) - 1; k >= 0; k--) {\n            if (_up[k][u]\
    \ == _up[k][v]) continue;\n            result = std::min(result, _minimum[k][u]);\n\
    \            result = std::min(result, _minimum[k][v]);\n            u = _up[k][u];\n\
    \            v = _up[k][v];\n        }\n        result = std::min(result, _minimum[0][u]);\n\
    \        result = std::min(result, _minimum[0][v]);\n        return result;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_GOMORY_HU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/gomory_hu.hpp
  requiredBy:
  - flow/flow.hpp
  timestamp: '2026-06-23 11:16:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/flow/flow_algorithms.test.cpp
documentation_of: flow/gomory_hu.hpp
layout: document
title: Gomory-Hu Tree
---

## Overview

`GomoryHu<Cap>` builds a cut-equivalent tree of an undirected capacitated graph.
For every two distinct vertices `u` and `v`, their minimum-cut value in the
original graph equals the minimum edge capacity on the tree path from `u` to
`v`.

The implementation runs highest-label push-relabel maximum flow `N - 1` times.
Global relabeling periodically restores exact sink distances, and the gap
heuristic skips dead height ranges. The residual graph is allocated once,
undirected edges use a single pair of residual arcs, and each run resets
capacities in place. Parallel edges are coalesced before the flow runs. This is
particularly fast on dense graphs. After construction, binary lifting answers
pairwise minimum-cut queries in `O(log N)`.

Parallel edges, zero-capacity edges, self-loops, and disconnected graphs are
allowed. A disconnected pair has minimum-cut value zero.

## How to Use It

Create `GomoryHu<Cap> gh(n)`, add each undirected edge once with
`gh.add_edge(u, v, cap)`, and call `gh.build()`.

After building:

- `gh.tree_edges()` returns the `N - 1` edges of the cut tree.
- `gh.min_cut(u, v)` returns the minimum-cut value for distinct vertices.
- `gh.parent()` and `gh.cut_values()` expose the rooted tree representation.
  For `v > 0`, the edge from `v` to `parent()[v]` has capacity
  `cut_values()[v]`. The root is vertex zero.

Adding another edge invalidates the built tree; call `build()` again before
querying it.

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `GomoryHu()` | Creates an empty graph. | `O(1)` |
| Constructor | `explicit GomoryHu(int n)` | Creates a graph with `n` vertices. | `O(1)` |
| `size` | `int size() const` | Returns the number of vertices. | `O(1)` |
| `edge_count` | `int edge_count() const` | Returns the number of added undirected edges. | `O(1)` |
| `add_edge` | `int add_edge(int u, int v, Cap cap)` | Adds an undirected edge and returns its id. | Amortized `O(1)` |
| `build` | `void build()` | Builds the Gomory-Hu tree and query table. | `N - 1` maximum-flow runs plus `O(N log N)` |
| `tree_edges` | `const std::vector<Edge>& tree_edges() const` | Returns cut-tree edges `{u, v, cap}`. | `O(1)` |
| `parent` | `const std::vector<int>& parent() const` | Returns rooted cut-tree parents. | `O(1)` |
| `cut_values` | `const std::vector<Cap>& cut_values() const` | Returns capacities of edges to parents. | `O(1)` |
| `min_cut` | `Cap min_cut(int u, int v) const` | Returns the pairwise minimum-cut value. | `O(log N)` |

The maximum-flow phase uses highest-label push-relabel with a general
`O(N^2 M)` bound per run. Its global relabel and gap heuristics are intended to
make it substantially faster in practice than a plain Dinic-based Gomory-Hu
implementation.

All capacities and intermediate sums must fit in `Cap`. Signed integer types
such as `long long` are recommended.

## Example

```cpp
#include "flow/gomory_hu.hpp"
#include <iostream>

int main() {
    m1une::flow::GomoryHu<long long> gh(4);
    gh.add_edge(0, 1, 3);
    gh.add_edge(1, 2, 2);
    gh.add_edge(0, 2, 1);
    gh.add_edge(2, 3, 4);
    gh.build();

    std::cout << gh.min_cut(0, 2) << '\n';  // 3
    std::cout << gh.min_cut(0, 3) << '\n';  // 3

    for (const auto& edge : gh.tree_edges()) {
        std::cout << edge.u << ' ' << edge.v << ' ' << edge.cap << '\n';
    }
}
```
