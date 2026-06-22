---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/library_checker_maximum_independent_set.test.cpp
    title: verify/graph/library_checker_maximum_independent_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/maximum_clique.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ m1une\n\n\n#line 9 \"graph/maximum_clique.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct MaximumCliqueResult {\n    std::vector<int> vertices;\n\n\
    \    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MaximumIndependentSetResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nstruct MinimumVertexCoverResult {\n    std::vector<int> vertices;\n\
    \n    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nnamespace detail\
    \ {\n\nstruct MaximumIndependentSetBranching {\n    int n;\n    std::vector<std::vector<char>>\
    \ adjacent;\n    std::vector<std::vector<int>> graph;\n\n    explicit MaximumIndependentSetBranching(const\
    \ std::vector<std::vector<char>>& adjacent_)\n        : n(int(adjacent_.size())),\
    \ adjacent(adjacent_), graph(n) {\n        for (int v = 0; v < n; v++) {\n   \
    \         for (int to = 0; to < n; to++) {\n                if (adjacent[v][to])\
    \ graph[v].push_back(to);\n            }\n        }\n    }\n\n    std::vector<int>\
    \ solve_path(const std::vector<int>& order) const {\n        int m = int(order.size());\n\
    \        if (m == 0) return {};\n\n        std::vector<int> dp0(m, 0), dp1(m,\
    \ 0);\n        dp1[0] = 1;\n        for (int i = 1; i < m; i++) {\n          \
    \  dp0[i] = std::max(dp0[i - 1], dp1[i - 1]);\n            dp1[i] = dp0[i - 1]\
    \ + 1;\n        }\n\n        std::vector<int> result;\n        int state = (dp1[m\
    \ - 1] > dp0[m - 1] ? 1 : 0);\n        for (int i = m - 1; i >= 0; i--) {\n  \
    \          if (state == 1) {\n                result.push_back(order[i]);\n  \
    \              state = 0;\n            } else if (i > 0) {\n                state\
    \ = (dp1[i - 1] > dp0[i - 1] ? 1 : 0);\n            }\n        }\n        return\
    \ result;\n    }\n\n    std::vector<int> solve_cycle(const std::vector<int>& order)\
    \ const {\n        int m = int(order.size());\n        if (m == 0) return {};\n\
    \        if (m == 1) return {order[0]};\n\n        std::vector<int> without_first(order.begin()\
    \ + 1, order.end());\n        auto result_without = solve_path(without_first);\n\
    \n        std::vector<int> result_with = {order[0]};\n        if (m >= 4) {\n\
    \            std::vector<int> middle(order.begin() + 2, order.end() - 1);\n  \
    \          auto middle_result = solve_path(middle);\n            result_with.insert(result_with.end(),\
    \ middle_result.begin(), middle_result.end());\n        }\n\n        return (result_with.size()\
    \ > result_without.size() ? result_with : result_without);\n    }\n\n    std::vector<int>\
    \ solve_degree_at_most_two(const std::vector<char>& active,\n                \
    \                              const std::vector<int>& degree) const {\n     \
    \   std::vector<int> result;\n        std::vector<char> visited(n, false);\n\n\
    \        for (int s = 0; s < n; s++) {\n            if (!active[s] || visited[s])\
    \ continue;\n\n            std::vector<int> component;\n            std::vector<int>\
    \ stack = {s};\n            visited[s] = true;\n            for (int it = 0; it\
    \ < int(stack.size()); it++) {\n                int v = stack[it];\n         \
    \       component.push_back(v);\n                for (int to : graph[v]) {\n \
    \                   if (!active[to] || visited[to]) continue;\n              \
    \      visited[to] = true;\n                    stack.push_back(to);\n       \
    \         }\n            }\n\n            if (component.size() == 1) {\n     \
    \           result.push_back(component[0]);\n                continue;\n     \
    \       }\n\n            int endpoint = -1;\n            for (int v : component)\
    \ {\n                if (degree[v] <= 1) {\n                    endpoint = v;\n\
    \                    break;\n                }\n            }\n\n            std::vector<int>\
    \ order;\n            if (endpoint != -1) {\n                int prev = -1, cur\
    \ = endpoint;\n                while (cur != -1) {\n                    order.push_back(cur);\n\
    \                    int next = -1;\n                    for (int to : graph[cur])\
    \ {\n                        if (active[to] && to != prev) {\n               \
    \             next = to;\n                            break;\n               \
    \         }\n                    }\n                    prev = cur;\n        \
    \            cur = next;\n                }\n                auto part = solve_path(order);\n\
    \                result.insert(result.end(), part.begin(), part.end());\n    \
    \        } else {\n                int start = component[0];\n               \
    \ int first = -1;\n                for (int to : graph[start]) {\n           \
    \         if (active[to]) {\n                        first = to;\n           \
    \             break;\n                    }\n                }\n             \
    \   assert(first != -1);\n\n                order.push_back(start);\n        \
    \        int prev = start, cur = first;\n                while (cur != start)\
    \ {\n                    order.push_back(cur);\n                    int next =\
    \ -1;\n                    for (int to : graph[cur]) {\n                     \
    \   if (active[to] && to != prev) {\n                            next = to;\n\
    \                            break;\n                        }\n             \
    \       }\n                    assert(next != -1);\n                    prev =\
    \ cur;\n                    cur = next;\n                }\n                auto\
    \ part = solve_cycle(order);\n                result.insert(result.end(), part.begin(),\
    \ part.end());\n            }\n        }\n\n        return result;\n    }\n\n\
    \    std::vector<int> solve(std::vector<char> active) const {\n        int active_count\
    \ = 0;\n        int max_degree = -1;\n        int branch_vertex = -1;\n      \
    \  std::vector<int> degree(n, 0);\n\n        for (int v = 0; v < n; v++) {\n \
    \           if (!active[v]) continue;\n            active_count++;\n         \
    \   for (int to : graph[v]) {\n                if (active[to]) degree[v]++;\n\
    \            }\n            if (degree[v] > max_degree) {\n                max_degree\
    \ = degree[v];\n                branch_vertex = v;\n            }\n        }\n\
    \n        if (active_count == 0) return {};\n        if (max_degree <= 2) {\n\
    \            auto result = solve_degree_at_most_two(active, degree);\n       \
    \     std::sort(result.begin(), result.end());\n            return result;\n \
    \       }\n\n        auto without = active;\n        without[branch_vertex] =\
    \ false;\n        auto result_without = solve(without);\n\n        auto with =\
    \ active;\n        with[branch_vertex] = false;\n        for (int to : graph[branch_vertex])\
    \ with[to] = false;\n        auto result_with = solve(with);\n        result_with.push_back(branch_vertex);\n\
    \n        auto result = (result_with.size() > result_without.size() ? result_with\
    \ : result_without);\n        std::sort(result.begin(), result.end());\n     \
    \   return result;\n    }\n\n    std::vector<int> solve() const {\n        std::vector<char>\
    \ active(n, true);\n        return solve(active);\n    }\n};\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<std::vector<char>> adjacent(n,\
    \ std::vector<char>(n, false));\n    for (const auto& e : g.edges()) {\n     \
    \   if (e.from == e.to) continue;\n        adjacent[e.from][e.to] = true;\n  \
    \      adjacent[e.to][e.from] = true;\n    }\n    return adjacent;\n}\n\nstd::vector<std::vector<char>>\
    \ complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent)\
    \ {\n    int n = int(adjacent.size());\n    std::vector<std::vector<char>> complement(n,\
    \ std::vector<char>(n, false));\n    for (int i = 0; i < n; i++) {\n        for\
    \ (int j = i + 1; j < n; j++) {\n            if (adjacent[i][j]) continue;\n \
    \           complement[i][j] = true;\n            complement[j][i] = true;\n \
    \       }\n    }\n    return complement;\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class T>\nbool is_clique(const Graph<T>& g, const std::vector<int>& vertices)\
    \ {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    for (int\
    \ v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n    for (int\
    \ i = 0; i < int(vertices.size()); i++) {\n        for (int j = i + 1; j < int(vertices.size());\
    \ j++) {\n            if (!adjacent[vertices[i]][vertices[j]]) return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {\n\
    \    std::vector<char> selected(g.size(), false);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        selected[v] = true;\n  \
    \  }\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        if (!selected[e.from] && !selected[e.to]) return false;\n    }\n    return\
    \ true;\n}\n\ntemplate <class T>\nMaximumCliqueResult maximum_clique(const Graph<T>&\
    \ g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    auto\
    \ complement = detail::complement_adjacency_matrix(adjacent);\n    detail::MaximumIndependentSetBranching\
    \ solver(complement);\n    return MaximumCliqueResult{solver.solve()};\n}\n\n\
    template <class T>\nint maximum_clique_size(const Graph<T>& g) {\n    return maximum_clique(g).size();\n\
    }\n\ntemplate <class T>\nMaximumIndependentSetResult maximum_independent_set(const\
    \ Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumIndependentSetBranching solver(adjacent);\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\ntemplate <class T>\nMinimumVertexCoverResult\
    \ minimum_vertex_cover(const Graph<T>& g) {\n    auto independent = maximum_independent_set(g);\n\
    \    std::vector<char> in_independent(g.size(), false);\n    for (int v : independent.vertices)\
    \ in_independent[v] = true;\n\n    MinimumVertexCoverResult result;\n    for (int\
    \ v = 0; v < g.size(); v++) {\n        if (!in_independent[v]) result.vertices.push_back(v);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nint minimum_vertex_cover_size(const\
    \ Graph<T>& g) {\n    return minimum_vertex_cover(g).size();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\n#define M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include\
    \ \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct MaximumCliqueResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nstruct MaximumIndependentSetResult {\n    std::vector<int> vertices;\n\
    \n    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MinimumVertexCoverResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nnamespace detail {\n\nstruct MaximumIndependentSetBranching {\n\
    \    int n;\n    std::vector<std::vector<char>> adjacent;\n    std::vector<std::vector<int>>\
    \ graph;\n\n    explicit MaximumIndependentSetBranching(const std::vector<std::vector<char>>&\
    \ adjacent_)\n        : n(int(adjacent_.size())), adjacent(adjacent_), graph(n)\
    \ {\n        for (int v = 0; v < n; v++) {\n            for (int to = 0; to <\
    \ n; to++) {\n                if (adjacent[v][to]) graph[v].push_back(to);\n \
    \           }\n        }\n    }\n\n    std::vector<int> solve_path(const std::vector<int>&\
    \ order) const {\n        int m = int(order.size());\n        if (m == 0) return\
    \ {};\n\n        std::vector<int> dp0(m, 0), dp1(m, 0);\n        dp1[0] = 1;\n\
    \        for (int i = 1; i < m; i++) {\n            dp0[i] = std::max(dp0[i -\
    \ 1], dp1[i - 1]);\n            dp1[i] = dp0[i - 1] + 1;\n        }\n\n      \
    \  std::vector<int> result;\n        int state = (dp1[m - 1] > dp0[m - 1] ? 1\
    \ : 0);\n        for (int i = m - 1; i >= 0; i--) {\n            if (state ==\
    \ 1) {\n                result.push_back(order[i]);\n                state = 0;\n\
    \            } else if (i > 0) {\n                state = (dp1[i - 1] > dp0[i\
    \ - 1] ? 1 : 0);\n            }\n        }\n        return result;\n    }\n\n\
    \    std::vector<int> solve_cycle(const std::vector<int>& order) const {\n   \
    \     int m = int(order.size());\n        if (m == 0) return {};\n        if (m\
    \ == 1) return {order[0]};\n\n        std::vector<int> without_first(order.begin()\
    \ + 1, order.end());\n        auto result_without = solve_path(without_first);\n\
    \n        std::vector<int> result_with = {order[0]};\n        if (m >= 4) {\n\
    \            std::vector<int> middle(order.begin() + 2, order.end() - 1);\n  \
    \          auto middle_result = solve_path(middle);\n            result_with.insert(result_with.end(),\
    \ middle_result.begin(), middle_result.end());\n        }\n\n        return (result_with.size()\
    \ > result_without.size() ? result_with : result_without);\n    }\n\n    std::vector<int>\
    \ solve_degree_at_most_two(const std::vector<char>& active,\n                \
    \                              const std::vector<int>& degree) const {\n     \
    \   std::vector<int> result;\n        std::vector<char> visited(n, false);\n\n\
    \        for (int s = 0; s < n; s++) {\n            if (!active[s] || visited[s])\
    \ continue;\n\n            std::vector<int> component;\n            std::vector<int>\
    \ stack = {s};\n            visited[s] = true;\n            for (int it = 0; it\
    \ < int(stack.size()); it++) {\n                int v = stack[it];\n         \
    \       component.push_back(v);\n                for (int to : graph[v]) {\n \
    \                   if (!active[to] || visited[to]) continue;\n              \
    \      visited[to] = true;\n                    stack.push_back(to);\n       \
    \         }\n            }\n\n            if (component.size() == 1) {\n     \
    \           result.push_back(component[0]);\n                continue;\n     \
    \       }\n\n            int endpoint = -1;\n            for (int v : component)\
    \ {\n                if (degree[v] <= 1) {\n                    endpoint = v;\n\
    \                    break;\n                }\n            }\n\n            std::vector<int>\
    \ order;\n            if (endpoint != -1) {\n                int prev = -1, cur\
    \ = endpoint;\n                while (cur != -1) {\n                    order.push_back(cur);\n\
    \                    int next = -1;\n                    for (int to : graph[cur])\
    \ {\n                        if (active[to] && to != prev) {\n               \
    \             next = to;\n                            break;\n               \
    \         }\n                    }\n                    prev = cur;\n        \
    \            cur = next;\n                }\n                auto part = solve_path(order);\n\
    \                result.insert(result.end(), part.begin(), part.end());\n    \
    \        } else {\n                int start = component[0];\n               \
    \ int first = -1;\n                for (int to : graph[start]) {\n           \
    \         if (active[to]) {\n                        first = to;\n           \
    \             break;\n                    }\n                }\n             \
    \   assert(first != -1);\n\n                order.push_back(start);\n        \
    \        int prev = start, cur = first;\n                while (cur != start)\
    \ {\n                    order.push_back(cur);\n                    int next =\
    \ -1;\n                    for (int to : graph[cur]) {\n                     \
    \   if (active[to] && to != prev) {\n                            next = to;\n\
    \                            break;\n                        }\n             \
    \       }\n                    assert(next != -1);\n                    prev =\
    \ cur;\n                    cur = next;\n                }\n                auto\
    \ part = solve_cycle(order);\n                result.insert(result.end(), part.begin(),\
    \ part.end());\n            }\n        }\n\n        return result;\n    }\n\n\
    \    std::vector<int> solve(std::vector<char> active) const {\n        int active_count\
    \ = 0;\n        int max_degree = -1;\n        int branch_vertex = -1;\n      \
    \  std::vector<int> degree(n, 0);\n\n        for (int v = 0; v < n; v++) {\n \
    \           if (!active[v]) continue;\n            active_count++;\n         \
    \   for (int to : graph[v]) {\n                if (active[to]) degree[v]++;\n\
    \            }\n            if (degree[v] > max_degree) {\n                max_degree\
    \ = degree[v];\n                branch_vertex = v;\n            }\n        }\n\
    \n        if (active_count == 0) return {};\n        if (max_degree <= 2) {\n\
    \            auto result = solve_degree_at_most_two(active, degree);\n       \
    \     std::sort(result.begin(), result.end());\n            return result;\n \
    \       }\n\n        auto without = active;\n        without[branch_vertex] =\
    \ false;\n        auto result_without = solve(without);\n\n        auto with =\
    \ active;\n        with[branch_vertex] = false;\n        for (int to : graph[branch_vertex])\
    \ with[to] = false;\n        auto result_with = solve(with);\n        result_with.push_back(branch_vertex);\n\
    \n        auto result = (result_with.size() > result_without.size() ? result_with\
    \ : result_without);\n        std::sort(result.begin(), result.end());\n     \
    \   return result;\n    }\n\n    std::vector<int> solve() const {\n        std::vector<char>\
    \ active(n, true);\n        return solve(active);\n    }\n};\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<std::vector<char>> adjacent(n,\
    \ std::vector<char>(n, false));\n    for (const auto& e : g.edges()) {\n     \
    \   if (e.from == e.to) continue;\n        adjacent[e.from][e.to] = true;\n  \
    \      adjacent[e.to][e.from] = true;\n    }\n    return adjacent;\n}\n\nstd::vector<std::vector<char>>\
    \ complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent)\
    \ {\n    int n = int(adjacent.size());\n    std::vector<std::vector<char>> complement(n,\
    \ std::vector<char>(n, false));\n    for (int i = 0; i < n; i++) {\n        for\
    \ (int j = i + 1; j < n; j++) {\n            if (adjacent[i][j]) continue;\n \
    \           complement[i][j] = true;\n            complement[j][i] = true;\n \
    \       }\n    }\n    return complement;\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class T>\nbool is_clique(const Graph<T>& g, const std::vector<int>& vertices)\
    \ {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    for (int\
    \ v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n    for (int\
    \ i = 0; i < int(vertices.size()); i++) {\n        for (int j = i + 1; j < int(vertices.size());\
    \ j++) {\n            if (!adjacent[vertices[i]][vertices[j]]) return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {\n\
    \    std::vector<char> selected(g.size(), false);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        selected[v] = true;\n  \
    \  }\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        if (!selected[e.from] && !selected[e.to]) return false;\n    }\n    return\
    \ true;\n}\n\ntemplate <class T>\nMaximumCliqueResult maximum_clique(const Graph<T>&\
    \ g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    auto\
    \ complement = detail::complement_adjacency_matrix(adjacent);\n    detail::MaximumIndependentSetBranching\
    \ solver(complement);\n    return MaximumCliqueResult{solver.solve()};\n}\n\n\
    template <class T>\nint maximum_clique_size(const Graph<T>& g) {\n    return maximum_clique(g).size();\n\
    }\n\ntemplate <class T>\nMaximumIndependentSetResult maximum_independent_set(const\
    \ Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumIndependentSetBranching solver(adjacent);\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\ntemplate <class T>\nMinimumVertexCoverResult\
    \ minimum_vertex_cover(const Graph<T>& g) {\n    auto independent = maximum_independent_set(g);\n\
    \    std::vector<char> in_independent(g.size(), false);\n    for (int v : independent.vertices)\
    \ in_independent[v] = true;\n\n    MinimumVertexCoverResult result;\n    for (int\
    \ v = 0; v < g.size(); v++) {\n        if (!in_independent[v]) result.vertices.push_back(v);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nint minimum_vertex_cover_size(const\
    \ Graph<T>& g) {\n    return minimum_vertex_cover(g).size();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/maximum_clique.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/library_checker_maximum_independent_set.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/maximum_clique.hpp
layout: document
title: Maximum Clique, Independent Set, and Vertex Cover
---

## Overview

This header solves three exact NP-hard problems on general undirected graphs:

* maximum clique;
* maximum independent set;
* minimum vertex cover.

A clique is a vertex set where every pair of vertices has an edge. An
independent set is a vertex set where no pair of vertices has an edge.
A vertex cover is a vertex set that touches every edge.

These problems are still exponential in the worst case. The implementation is
not a naive `2^N` subset scan: it uses a branching maximum independent set
solver. Maximum clique is computed as maximum independent set in the complement
graph.

## Graph Orientation

Direction is ignored. Every active edge of `Graph<T>` is treated as an
undirected edge between its endpoints. Self-loops are ignored because they do
not help a clique or an independent set.

## How It Works

The core solver is for maximum independent set.

If every remaining vertex has degree at most `2`, each connected component is a
path, a cycle, or an isolated vertex. Those components are solved directly by
dynamic programming.

Otherwise, let `v` be a maximum-degree vertex. Since the maximum degree is at
least `3`, the solver branches into these two cases:

* do not use `v`, so only `v` is removed;
* use `v`, so `v` and all its neighbors are removed.

The second branch removes at least `4` vertices.

For maximum clique, the solver builds the complement graph: two vertices are
connected in the complement exactly when they are not connected in the original
graph. An independent set in the complement is a clique in the original graph.

For minimum vertex cover, the solver uses the fact that a set `C` is a vertex
cover exactly when its complement `V - C` is an independent set. Therefore, the
minimum vertex cover is the complement of a maximum independent set.

## Complexity Note

Let `N` be the number of vertices. This implementation is exact and has
exponential worst-case complexity. The branching step gives the recurrence

```cpp
T(N) <= T(N - 1) + T(N - 4)
```

The positive root of `x^4 = x^3 + 1` is about `1.381`, so the search tree is
bounded by $O(1.381^N)$. With the polynomial work in each node, the usual bound
for this branching algorithm is written as $O(1.381^N \cdot N)$ when adjacency
bookkeeping is implemented linearly.

The implementation follows that branching algorithm. It stores adjacency lists
and copies the active-vertex set during recursion, so the simple header
implementation may have a slightly larger polynomial constant than a
hand-tuned contest implementation with incremental degree bookkeeping, but the
exponential part is the `1.381^N` branching bound.

## Result Types

`MaximumCliqueResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum clique. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

`MaximumIndependentSetResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one maximum independent set. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

`MinimumVertexCoverResult` contains these members:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | Vertices in one minimum vertex cover. |
| `size` | `int size() const` | Returns `vertices.size()`. |
| `empty` | `bool empty() const` | Returns whether `vertices` is empty. |

Returned vertices are sorted in increasing order.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `maximum_clique` | `template <class T> MaximumCliqueResult maximum_clique(const Graph<T>& g)` | Returns one maximum clique. | $O(1.381^N \cdot N)$ branching bound |
| `maximum_clique_size` | `template <class T> int maximum_clique_size(const Graph<T>& g)` | Returns the size of a maximum clique. | $O(1.381^N \cdot N)$ branching bound |
| `maximum_independent_set` | `template <class T> MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g)` | Returns one maximum independent set. | $O(1.381^N \cdot N)$ branching bound |
| `maximum_independent_set_size` | `template <class T> int maximum_independent_set_size(const Graph<T>& g)` | Returns the size of a maximum independent set. | $O(1.381^N \cdot N)$ branching bound |
| `minimum_vertex_cover` | `template <class T> MinimumVertexCoverResult minimum_vertex_cover(const Graph<T>& g)` | Returns one minimum vertex cover. | $O(1.381^N \cdot N)$ branching bound |
| `minimum_vertex_cover_size` | `template <class T> int minimum_vertex_cover_size(const Graph<T>& g)` | Returns the size of a minimum vertex cover. | $O(1.381^N \cdot N)$ branching bound |
| `is_clique` | `template <class T> bool is_clique(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a clique. | $O(N + M + K^2)$ |
| `is_independent_set` | `template <class T> bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is an independent set. | $O(N + M + K^2)$ |
| `is_vertex_cover` | `template <class T> bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices)` | Checks whether `vertices` is a vertex cover. | $O(N + M + K)$ |

Here, `K = vertices.size()`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/maximum_clique.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    auto clique = m1une::graph::maximum_clique(g);
    auto independent = m1une::graph::maximum_independent_set(g);
    auto cover = m1une::graph::minimum_vertex_cover(g);

    std::cout << clique.size() << "\n";       // 3
    std::cout << independent.size() << "\n";  // 2
    std::cout << cover.size() << "\n";        // 2
}
```
