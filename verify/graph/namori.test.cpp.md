---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/namori.hpp
    title: Namori Graph Decomposition
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/graph/namori.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"graph/namori.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
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
    \ m1une\n\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int component_count;\n\
    \    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/namori.test.cpp\"\n\
    \n#include <algorithm>\n#line 7 \"verify/graph/namori.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <numeric>\n#line 11 \"verify/graph/namori.test.cpp\"\
    \n#include <set>\n#line 14 \"verify/graph/namori.test.cpp\"\n\nnamespace {\n\n\
    void test_features() {\n    m1une::graph::Graph<long long> graph(7);\n    int\
    \ e01 = graph.add_edge(0, 1, 2);\n    int e12 = graph.add_edge(1, 2, 3);\n   \
    \ int e20 = graph.add_edge(2, 0, 4);\n    graph.add_edge(1, 3, 5);\n    graph.add_edge(3,\
    \ 4, 6);\n    int loop = graph.add_edge(5, 5, 7);\n    graph.add_edge(5, 6, 8);\n\
    \n    auto optional = m1une::graph::namori_decomposition(graph);\n    assert(optional.has_value());\n\
    \    const auto& result = *optional;\n    assert(result.component_count == 2);\n\
    \    assert(result.cycles.size() == 2);\n    assert(result.on_cycle[0]);\n   \
    \ assert(result.on_cycle[1]);\n    assert(result.on_cycle[2]);\n    assert(!result.on_cycle[3]);\n\
    \    assert(!result.on_cycle[4]);\n    assert(result.on_cycle[5]);\n    assert(!result.on_cycle[6]);\n\
    \    assert(result.same_component(0, 4));\n    assert(!result.same_component(0,\
    \ 5));\n    assert(result.same_tree(1, 4));\n    assert(!result.same_tree(0, 4));\n\
    \    assert(result.cycle_root[4] == 1);\n    assert(result.parent[4] == 3);\n\
    \    assert(result.parent[3] == 1);\n    assert(result.depth[4] == 2);\n    assert(result.dist_to_cycle[4]\
    \ == 11);\n    assert(result.cycle_root[6] == 5);\n    assert(result.dist_to_cycle[6]\
    \ == 8);\n\n    std::set<int> first_cycle_edges;\n    for (int id : result.cycle_edge_ids[result.component[0]])\
    \ first_cycle_edges.insert(id);\n    assert((first_cycle_edges == std::set<int>{e01,\
    \ e12, e20}));\n    int loop_component = result.component[5];\n    assert(result.cycles[loop_component]\
    \ == std::vector<int>({5}));\n    assert(result.cycle_edge_ids[loop_component]\
    \ == std::vector<int>({loop}));\n\n    m1une::graph::Graph<int> parallel(2);\n\
    \    int first = parallel.add_edge(0, 1);\n    int second = parallel.add_edge(0,\
    \ 1);\n    auto two_cycle = m1une::graph::decompose_namori(parallel);\n    assert(two_cycle.has_value());\n\
    \    assert(two_cycle->cycles[0].size() == 2);\n    std::set<int> parallel_ids(\n\
    \        two_cycle->cycle_edge_ids[0].begin(),\n        two_cycle->cycle_edge_ids[0].end()\n\
    \    );\n    assert((parallel_ids == std::set<int>{first, second}));\n\n    m1une::graph::Graph<int>\
    \ tree(3);\n    tree.add_edge(0, 1);\n    tree.add_edge(1, 2);\n    assert(!m1une::graph::namori_decomposition(tree).has_value());\n\
    \n    m1une::graph::Graph<int> bicyclic(5);\n    bicyclic.add_edge(0, 1);\n  \
    \  bicyclic.add_edge(1, 2);\n    bicyclic.add_edge(2, 0);\n    bicyclic.add_edge(2,\
    \ 3);\n    bicyclic.add_edge(3, 4);\n    int removable = bicyclic.add_edge(4,\
    \ 2);\n    assert(!m1une::graph::namori_decomposition(bicyclic).has_value());\n\
    \    bicyclic.erase_edge(removable);\n    auto inactive_ignored = m1une::graph::namori_decomposition(bicyclic);\n\
    \    assert(inactive_ignored.has_value());\n    assert(inactive_ignored->component_count\
    \ == 1);\n\n    m1une::graph::Graph<int> empty;\n    auto empty_result = m1une::graph::namori_decomposition(empty);\n\
    \    assert(empty_result.has_value());\n    assert(empty_result->component_count\
    \ == 0);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1000; trial++) {\n        int n = 1 + int(random() % 150);\n        int component_count\
    \ = 1 + int(random() % std::min(n, 10));\n        std::vector<int> component_size(component_count,\
    \ 1);\n        for (int i = component_count; i < n; i++) component_size[random()\
    \ % component_count]++;\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        std::vector<int> expected_component(n, -1);\n        int offset = 0;\n\
    \        for (int component = 0; component < component_count; component++) {\n\
    \            int size = component_size[component];\n            int cycle_size\
    \ = 1 + int(random() % size);\n            for (int i = 0; i < size; i++) expected_component[offset\
    \ + i] = component;\n\n            if (cycle_size == 1) {\n                graph.add_edge(offset,\
    \ offset, 1 + random() % 1000);\n            } else if (cycle_size == 2) {\n \
    \               graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n   \
    \             graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n     \
    \       } else {\n                for (int i = 0; i < cycle_size; i++) {\n   \
    \                 graph.add_edge(\n                        offset + i,\n     \
    \                   offset + (i + 1) % cycle_size,\n                        1\
    \ + random() % 1000\n                    );\n                }\n            }\n\
    \            for (int i = cycle_size; i < size; i++) {\n                int parent\
    \ = int(random() % i);\n                graph.add_edge(offset + i, offset + parent,\
    \ 1 + random() % 1000);\n            }\n            offset += size;\n        }\n\
    \n        auto optional = m1une::graph::namori_decomposition(graph);\n       \
    \ assert(optional.has_value());\n        const auto& result = *optional;\n   \
    \     assert(result.component_count == component_count);\n\n        int cycle_vertex_count\
    \ = 0;\n        for (int component = 0; component < result.component_count; component++)\
    \ {\n            const auto& cycle = result.cycles[component];\n            const\
    \ auto& edge_ids = result.cycle_edge_ids[component];\n            const auto&\
    \ edge_costs = result.cycle_edge_costs[component];\n            assert(!cycle.empty());\n\
    \            assert(cycle.size() == edge_ids.size());\n            assert(cycle.size()\
    \ == edge_costs.size());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int i = 0; i < int(cycle.size()); i++) {\n                int\
    \ from = cycle[i];\n                int to = cycle[(i + 1) % cycle.size()];\n\
    \                bool found = false;\n                for (const auto& edge :\
    \ graph[from]) {\n                    if (edge.id == edge_ids[i] && edge.to ==\
    \ to && edge.cost == edge_costs[i]) {\n                        found = true;\n\
    \                        break;\n                    }\n                }\n  \
    \              assert(found);\n            }\n        }\n\n        int counted_cycle_vertices\
    \ = 0;\n        for (int v = 0; v < n; v++) {\n            assert(0 <= result.component[v]\
    \ && result.component[v] < component_count);\n            assert(expected_component[v]\
    \ == expected_component[result.cycle_root[v]]);\n            assert(result.cycles[result.component[v]][result.cycle_position[v]]\
    \ == result.cycle_root[v]);\n            if (result.on_cycle[v]) {\n         \
    \       counted_cycle_vertices++;\n                assert(result.cycle_root[v]\
    \ == v);\n                assert(result.parent[v] == -1);\n                assert(result.parent_edge[v]\
    \ == -1);\n                assert(result.depth[v] == 0);\n                assert(result.dist_to_cycle[v]\
    \ == 0);\n            } else {\n                int parent = result.parent[v];\n\
    \                assert(parent != -1);\n                assert(result.depth[parent]\
    \ + 1 == result.depth[v]);\n                assert(result.cycle_root[parent] ==\
    \ result.cycle_root[v]);\n                bool found = false;\n              \
    \  for (const auto& edge : graph[v]) {\n                    if (edge.id == result.parent_edge[v]\
    \ && edge.to == parent) {\n                        assert(result.dist_to_cycle[v]\
    \ == result.dist_to_cycle[parent] + edge.cost);\n                        found\
    \ = true;\n                    }\n                }\n                assert(found);\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        std::vector<int> child_count(n, 0);\n        for (int v = 0; v < n;\
    \ v++) {\n            for (int child : result.children[v]) {\n               \
    \ assert(result.parent[child] == v);\n                child_count[child]++;\n\
    \            }\n        }\n        for (int v = 0; v < n; v++) {\n           \
    \ assert(child_count[v] == int(!result.on_cycle[v]));\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_features();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../graph/namori.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <numeric>\n#include <queue>\n#include\
    \ <set>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nvoid test_features()\
    \ {\n    m1une::graph::Graph<long long> graph(7);\n    int e01 = graph.add_edge(0,\
    \ 1, 2);\n    int e12 = graph.add_edge(1, 2, 3);\n    int e20 = graph.add_edge(2,\
    \ 0, 4);\n    graph.add_edge(1, 3, 5);\n    graph.add_edge(3, 4, 6);\n    int\
    \ loop = graph.add_edge(5, 5, 7);\n    graph.add_edge(5, 6, 8);\n\n    auto optional\
    \ = m1une::graph::namori_decomposition(graph);\n    assert(optional.has_value());\n\
    \    const auto& result = *optional;\n    assert(result.component_count == 2);\n\
    \    assert(result.cycles.size() == 2);\n    assert(result.on_cycle[0]);\n   \
    \ assert(result.on_cycle[1]);\n    assert(result.on_cycle[2]);\n    assert(!result.on_cycle[3]);\n\
    \    assert(!result.on_cycle[4]);\n    assert(result.on_cycle[5]);\n    assert(!result.on_cycle[6]);\n\
    \    assert(result.same_component(0, 4));\n    assert(!result.same_component(0,\
    \ 5));\n    assert(result.same_tree(1, 4));\n    assert(!result.same_tree(0, 4));\n\
    \    assert(result.cycle_root[4] == 1);\n    assert(result.parent[4] == 3);\n\
    \    assert(result.parent[3] == 1);\n    assert(result.depth[4] == 2);\n    assert(result.dist_to_cycle[4]\
    \ == 11);\n    assert(result.cycle_root[6] == 5);\n    assert(result.dist_to_cycle[6]\
    \ == 8);\n\n    std::set<int> first_cycle_edges;\n    for (int id : result.cycle_edge_ids[result.component[0]])\
    \ first_cycle_edges.insert(id);\n    assert((first_cycle_edges == std::set<int>{e01,\
    \ e12, e20}));\n    int loop_component = result.component[5];\n    assert(result.cycles[loop_component]\
    \ == std::vector<int>({5}));\n    assert(result.cycle_edge_ids[loop_component]\
    \ == std::vector<int>({loop}));\n\n    m1une::graph::Graph<int> parallel(2);\n\
    \    int first = parallel.add_edge(0, 1);\n    int second = parallel.add_edge(0,\
    \ 1);\n    auto two_cycle = m1une::graph::decompose_namori(parallel);\n    assert(two_cycle.has_value());\n\
    \    assert(two_cycle->cycles[0].size() == 2);\n    std::set<int> parallel_ids(\n\
    \        two_cycle->cycle_edge_ids[0].begin(),\n        two_cycle->cycle_edge_ids[0].end()\n\
    \    );\n    assert((parallel_ids == std::set<int>{first, second}));\n\n    m1une::graph::Graph<int>\
    \ tree(3);\n    tree.add_edge(0, 1);\n    tree.add_edge(1, 2);\n    assert(!m1une::graph::namori_decomposition(tree).has_value());\n\
    \n    m1une::graph::Graph<int> bicyclic(5);\n    bicyclic.add_edge(0, 1);\n  \
    \  bicyclic.add_edge(1, 2);\n    bicyclic.add_edge(2, 0);\n    bicyclic.add_edge(2,\
    \ 3);\n    bicyclic.add_edge(3, 4);\n    int removable = bicyclic.add_edge(4,\
    \ 2);\n    assert(!m1une::graph::namori_decomposition(bicyclic).has_value());\n\
    \    bicyclic.erase_edge(removable);\n    auto inactive_ignored = m1une::graph::namori_decomposition(bicyclic);\n\
    \    assert(inactive_ignored.has_value());\n    assert(inactive_ignored->component_count\
    \ == 1);\n\n    m1une::graph::Graph<int> empty;\n    auto empty_result = m1une::graph::namori_decomposition(empty);\n\
    \    assert(empty_result.has_value());\n    assert(empty_result->component_count\
    \ == 0);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1000; trial++) {\n        int n = 1 + int(random() % 150);\n        int component_count\
    \ = 1 + int(random() % std::min(n, 10));\n        std::vector<int> component_size(component_count,\
    \ 1);\n        for (int i = component_count; i < n; i++) component_size[random()\
    \ % component_count]++;\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        std::vector<int> expected_component(n, -1);\n        int offset = 0;\n\
    \        for (int component = 0; component < component_count; component++) {\n\
    \            int size = component_size[component];\n            int cycle_size\
    \ = 1 + int(random() % size);\n            for (int i = 0; i < size; i++) expected_component[offset\
    \ + i] = component;\n\n            if (cycle_size == 1) {\n                graph.add_edge(offset,\
    \ offset, 1 + random() % 1000);\n            } else if (cycle_size == 2) {\n \
    \               graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n   \
    \             graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n     \
    \       } else {\n                for (int i = 0; i < cycle_size; i++) {\n   \
    \                 graph.add_edge(\n                        offset + i,\n     \
    \                   offset + (i + 1) % cycle_size,\n                        1\
    \ + random() % 1000\n                    );\n                }\n            }\n\
    \            for (int i = cycle_size; i < size; i++) {\n                int parent\
    \ = int(random() % i);\n                graph.add_edge(offset + i, offset + parent,\
    \ 1 + random() % 1000);\n            }\n            offset += size;\n        }\n\
    \n        auto optional = m1une::graph::namori_decomposition(graph);\n       \
    \ assert(optional.has_value());\n        const auto& result = *optional;\n   \
    \     assert(result.component_count == component_count);\n\n        int cycle_vertex_count\
    \ = 0;\n        for (int component = 0; component < result.component_count; component++)\
    \ {\n            const auto& cycle = result.cycles[component];\n            const\
    \ auto& edge_ids = result.cycle_edge_ids[component];\n            const auto&\
    \ edge_costs = result.cycle_edge_costs[component];\n            assert(!cycle.empty());\n\
    \            assert(cycle.size() == edge_ids.size());\n            assert(cycle.size()\
    \ == edge_costs.size());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int i = 0; i < int(cycle.size()); i++) {\n                int\
    \ from = cycle[i];\n                int to = cycle[(i + 1) % cycle.size()];\n\
    \                bool found = false;\n                for (const auto& edge :\
    \ graph[from]) {\n                    if (edge.id == edge_ids[i] && edge.to ==\
    \ to && edge.cost == edge_costs[i]) {\n                        found = true;\n\
    \                        break;\n                    }\n                }\n  \
    \              assert(found);\n            }\n        }\n\n        int counted_cycle_vertices\
    \ = 0;\n        for (int v = 0; v < n; v++) {\n            assert(0 <= result.component[v]\
    \ && result.component[v] < component_count);\n            assert(expected_component[v]\
    \ == expected_component[result.cycle_root[v]]);\n            assert(result.cycles[result.component[v]][result.cycle_position[v]]\
    \ == result.cycle_root[v]);\n            if (result.on_cycle[v]) {\n         \
    \       counted_cycle_vertices++;\n                assert(result.cycle_root[v]\
    \ == v);\n                assert(result.parent[v] == -1);\n                assert(result.parent_edge[v]\
    \ == -1);\n                assert(result.depth[v] == 0);\n                assert(result.dist_to_cycle[v]\
    \ == 0);\n            } else {\n                int parent = result.parent[v];\n\
    \                assert(parent != -1);\n                assert(result.depth[parent]\
    \ + 1 == result.depth[v]);\n                assert(result.cycle_root[parent] ==\
    \ result.cycle_root[v]);\n                bool found = false;\n              \
    \  for (const auto& edge : graph[v]) {\n                    if (edge.id == result.parent_edge[v]\
    \ && edge.to == parent) {\n                        assert(result.dist_to_cycle[v]\
    \ == result.dist_to_cycle[parent] + edge.cost);\n                        found\
    \ = true;\n                    }\n                }\n                assert(found);\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        std::vector<int> child_count(n, 0);\n        for (int v = 0; v < n;\
    \ v++) {\n            for (int child : result.children[v]) {\n               \
    \ assert(result.parent[child] == v);\n                child_count[child]++;\n\
    \            }\n        }\n        for (int v = 0; v < n; v++) {\n           \
    \ assert(child_count[v] == int(!result.on_cycle[v]));\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_features();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - graph/namori.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/namori.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 12:19:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/namori.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/namori.test.cpp
- /verify/verify/graph/namori.test.cpp.html
title: verify/graph/namori.test.cpp
---
